/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:56:00 by josfelip          #+#    #+#             */
/*   Updated: 2024/11/19 18:56:15 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef struct s_texture {
    char *path;
} t_texture;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_map_config {
    t_texture north;
    t_texture south;
    t_texture east;
    t_texture west;
    t_color floor;
    t_color ceiling;
    char **map;
    int map_width;
    int map_height;
    char player_direction;
    int player_x;
    int player_y;
    int has_player;
} t_map_config;

// Função para limpar a memória em caso de erro
void cleanup_config(t_map_config *config) {
    if (config->north.path)
        free(config->north.path);
    if (config->south.path)
        free(config->south.path);
    if (config->east.path)
        free(config->east.path);
    if (config->west.path)
        free(config->west.path);
    
    if (config->map) {
        for (int i = 0; i < config->map_height; i++) {
            if (config->map[i])
                free(config->map[i]);
        }
        free(config->map);
    }
    memset(config, 0, sizeof(t_map_config));
}

// Função para validar a extensão do arquivo
int validate_file_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename || strcmp(dot, ".cub") != 0) {
        fprintf(stderr, "Error\nInvalid file extension. Expected .cub\n");
        return 0;
    }
    return 1;
}

// Função para validar uma cor RGB com mensagem de erro
int validate_color(char *color_str, t_color *color, const char *type) {
    char *token;
    char *str_copy;
    int values[3];
    int i = 0;
    
    if (!color_str) {
        fprintf(stderr, "Error\nMissing color definition for %s\n", type);
        return 0;
    }
    
    // Faz uma cópia da string para não modificar a original
    str_copy = strdup(color_str);
    if (!str_copy) {
        fprintf(stderr, "Error\nMemory allocation failed\n");
        return 0;
    }
    
    token = strtok(str_copy, ",");
    while (token && i < 3) {
        // Remove espaços em branco
        while (*token == ' ')
            token++;
            
        char *endptr;
        values[i] = strtol(token, &endptr, 10);
        
        if (*endptr != '\0' && *endptr != ' ') {
            fprintf(stderr, "Error\nInvalid color format for %s\n", type);
            free(str_copy);
            return 0;
        }
        
        if (values[i] < 0 || values[i] > 255) {
            fprintf(stderr, "Error\nColor value out of range (0-255) for %s\n", type);
            free(str_copy);
            return 0;
        }
        
        token = strtok(NULL, ",");
        i++;
    }
    
    free(str_copy);
    
    if (i != 3 || token != NULL) {
        fprintf(stderr, "Error\nInvalid color format for %s. Expected R,G,B\n", type);
        return 0;
    }
        
    color->r = values[0];
    color->g = values[1];
    color->b = values[2];
    return 1;
}

// Função para validar um caminho de textura com mensagem de erro
int validate_texture(char *path, t_texture *texture, const char *type) {
    if (!path) {
        fprintf(stderr, "Error\nMissing texture path for %s\n", type);
        return 0;
    }
    
    // Remove espaços em branco no início
    while (*path == ' ')
        path++;
        
    // Remove espaços em branco no final
    char *end = path + strlen(path) - 1;
    while (end > path && *end == ' ')
        *end-- = '\0';
    
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error\nCannot open texture file for %s: %s\n", 
                type, strerror(errno));
        return 0;
    }
    close(fd);
    
    texture->path = strdup(path);
    if (!texture->path) {
        fprintf(stderr, "Error\nMemory allocation failed for texture path\n");
        return 0;
    }
    return 1;
}

// Função principal de validação
int validate_map_file(const char *filename, t_map_config *config) {
    if (!filename || !config) {
        fprintf(stderr, "Error\nNull parameters passed to validator\n");
        return 0;
    }
    
    // Valida a extensão do arquivo
    if (!validate_file_extension(filename))
        return 0;
    
    // Tenta abrir o arquivo
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error\nCannot open map file: %s\n", strerror(errno));
        return 0;
    }
    
    // Inicializa a configuração com zeros
    memset(config, 0, sizeof(t_map_config));
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_number = 0;
    
    // Lê o arquivo linha por linha
    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        
        // Remove o newline
        if (read > 0 && line[read-1] == '\n')
            line[read-1] = '\0';
        
        // Ignora linhas vazias
        if (strlen(line) == 0)
            continue;
            
        // Valida cada tipo de elemento
        if (strncmp(line, "NO ", 3) == 0) {
            if (!validate_texture(line + 3, &config->north, "North texture")) {
                free(line);
                fclose(file);
                cleanup_config(config);
                return 0;
            }
        }
        else if (strncmp(line, "SO ", 3) == 0) {
            if (!validate_texture(line + 3, &config->south, "South texture")) {
                free(line);
                fclose(file);
                cleanup_config(config);
                return 0;
            }
        }
        // ... similiar para outras texturas e cores
        
        // Se houver erro de formato em qualquer linha
        else if (line[0] != '\0' && line[0] != ' ' && line[0] != '1' && line[0] != '0') {
            fprintf(stderr, "Error\nInvalid line format at line %d\n", line_number);
            free(line);
            fclose(file);
            cleanup_config(config);
            return 0;
        }
    }
    
    // Libera recursos
    free(line);
    fclose(file);
    
    // Valida se todos os elementos necessários foram encontrados
    if (!config->north.path || !config->south.path ||
        !config->east.path || !config->west.path) {
        fprintf(stderr, "Error\nMissing required texture definitions\n");
        cleanup_config(config);
        return 0;
    }
    
    return 1;
}

// Função para debug/teste
void print_config(t_map_config *config) {
    printf("Configuration:\n");
    printf("North texture: %s\n", config->north.path);
    printf("South texture: %s\n", config->south.path);
    printf("East texture: %s\n", config->east.path);
    printf("West texture: %s\n", config->west.path);
    printf("Floor color: RGB(%d,%d,%d)\n", 
           config->floor.r, config->floor.g, config->floor.b);
    printf("Ceiling color: RGB(%d,%d,%d)\n", 
           config->ceiling.r, config->ceiling.g, config->ceiling.b);
}