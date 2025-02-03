# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 14:19:08 by ebonutto          #+#    #+#              #
#    Updated: 2025/02/03 14:18:29 by maecarva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                              VARIABLES PROGRAM                               #
################################################################################

# Nom du programme final
NAME = minishell

# Compilateur et flags de compilation
CC = cc
CFLAGS = -Werror -Wextra -Wall -g

################################################################################
#                              DIRECTORY PATHS                                 #
################################################################################

# Chemins des sources et objets
SRC_PATH = src_minishell/
OBJ_PATH = obj_minishell/

# Dossier des bibliothèques externes
LIBS_PATH = libs
GNL_PATH = $(LIBS_PATH)/gnl
LIBFT_PATH = $(LIBS_PATH)/libft

################################################################################
#                              FICHIERS SOURCES                                #
################################################################################

# Liste des fichiers sources
SRC = src_minishell/main.c \
	  src_minishell/init/init.c \
	  src_minishell/init/env.c \
	  src_minishell/init/env_utils.c \
	  src_minishell/clear/clear.c

# Conversion des .c en .o dans le dossier obj
OBJ = $(SRC:.c=.o)

################################################################################
#                              INCLUDES AND LIBRARIES                          #
################################################################################

# Headers
INCLUDE = -I include_minishell -I $(GNL_PATH)/include_gnl -I $(LIBFT_PATH)/include_libft

# Bibliothèques statiques
GNL = $(GNL_PATH)/gnl.a
LIBFT = $(LIBFT_PATH)/libft.a

################################################################################
#                              COMPILING RULES                                 #
################################################################################

# Règle par défaut
all: $(NAME)

# Alias pour la règle all
bonus: all

# Compilation des fichiers sources en objets
%.o: %.c
	# mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

# Compilation des fichiers bonus en objets
$(OBJ_PATH)%.o: $(SRC_BONUS_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

################################################################################
#                              COMPILING LIBS                                  #
################################################################################

# Compilation de la libft
$(LIBFT):
	make -sC $(LIBFT_PATH) all

# Compilation de la GNL (dépend de la libft)
$(GNL): $(LIBFT)
	make -sC $(GNL_PATH)

################################################################################
#                              CREATING THE EXECUTABLE                         #
################################################################################

# Création de l'exécutable final
$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(GNL) $(LIBFT) $(INCLUDE) -lreadline

################################################################################
#                              	CLEANING RULES                                 #
################################################################################

# Suppression des fichiers objets
clean:
	make -sC $(LIBFT_PATH) clean
	make -sC $(GNL_PATH) clean
	rm -rf $(OBJ_PATH)

# Suppression des fichiers objets et des exécutables
fclean: clean
	make -sC $(LIBFT_PATH) fclean
	make -sC $(GNL_PATH) fclean
	rm -f $(NAME)

# Recompilation complète
re: fclean all

# Déclaration des règles spéciales
.PHONY: all clean fclean re bonus
