#!/bin/bash

# Exit on error, but after printing the error message
trap 'echo "Error: $BASH_COMMAND failed with exit code $?"' ERR

# Find all ch*.sh files and store them in an array
mapfile -t scripts < <(find qa -maxdepth 1 -type f -name "ch*.sh")

if [ ${#scripts[@]} -eq 0 ]; then
    echo "No ch*.sh scripts found in qa directory"
    exit 0
fi

# Make sure all scripts are executable
for script in "${scripts[@]}"; do
    if [ ! -x "$script" ]; then
        chmod +x "$script"
        echo "Made $script executable"
    fi
done

# Array to store PIDs of running processes
pids=()

# Variable to track if any script failed
has_failures=0

# Run each script in parallel
for script in "${scripts[@]}"; do
    echo "Starting $script..."
    "./$script" &
    pids+=($!)
done

# Print summary of running scripts
echo -e "\nRunning ${#scripts[@]} scripts in parallel..."
for i in "${!scripts[@]}"; do
    echo "PID ${pids[$i]}: ${scripts[$i]}"
done

# Wait for all scripts to complete and check their status
for i in "${!pids[@]}"; do
    wait "${pids[$i]}"
    status=$?
    if [ $status -ne 0 ]; then
        echo "ERROR: ${scripts[$i]} (PID ${pids[$i]}) failed with status $status"
        has_failures=1
    else
        echo "SUCCESS: ${scripts[$i]} (PID ${pids[$i]}) completed"
    fi
done

echo -e "\nAll scripts completed"

# Exit with error if any script failed
if [ $has_failures -eq 1 ]; then
    echo "One or more scripts failed"
    exit 1
fi

echo "All scripts passed"
exit 0