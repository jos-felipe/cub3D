#!/bin/bash

STATUS=0
VALGRIND_LOG=valgrind.log
VALGRIND_STATUS=$(cat $VALGRIND_LOG)
if [ "$VALGRIND_STATUS" ]; then
	cat $VALGRIND_LOG
	echo MKO
	STATUS=1
else
	echo MOK
fi
rm -f $VALGRIND_LOG
exit $STATUS
