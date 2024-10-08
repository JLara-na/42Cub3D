# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 01:23:47 by jlara-na          #+#    #+#              #
#    Updated: 2024/10/07 19:28:37 by jlara-na         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-----------EXECUTABLE-----------
NAME			:=		cub3D
#-----------DIR PATHS------------
SRC_DIR			:=		src/
SUB_DIR_1		:=		main/
SUB_DIR_2		:=		hooks/
SUB_DIR_3		:=		raycasting/
SUB_DIR_4		:=		cam/
SUB_DIR_5		:=		parse/
SUB_DIR_5_1		:=		parse/automata/
SUB_DIR_6		:=		minimap/
OBJ_DIR			:=		obj/
LIB_DIR			:=		lib/
INC_DIR			:=		inc/
LFT_DIR			:=		$(LIB_DIR)libft/
MLX_DIR			:=		$(LIB_DIR)minilibx-linux/
#-----------CMP PARAM------------
MAKEFLAGS		:=		--no-print-directory
CC				:=		gcc
CFLAGS			:=		-g -O3 -Wall -Wextra -Werror -fsanitize=address -lm
HEADER			:=		-I$(INC_DIR) -I$(LFT_DIR) -I$(MLX_DIR)
MLXCC			:=		-I mlx -L $(MLX_DIR) -lmlx -lXext -lX11
#-----------ARCHIVE LIB----------
LIBFT			:=		$(LFT_DIR)libft.a
MLX				:=		$(MLX_DIR)libmlx.a
#-----------SHORT CUTS-----------
RM				:=		rm -f
#------------ANSI DEF------------
CLEAR			=		\033[H\033[J
DEF_COLOR		=		\033[m
RETURN			=		\033[1A
CLEAN_LINE		=		\033[2K
BLACK			=		\033[0;30m
BLACK_BL		=		\033[0;30;5m
GRAY			=		\033[0;90m
GRAY_BL			=		\033[0;90;5m
RED				=		\033[0;31m
RED_BL			=		\033[0;31;5m
RED_B			=		\033[0;91m
RED_BBL			=		\033[0;91;5m
GREEN			=		\033[0;32m
GREEN_BL		=		\033[0;32;5m
GREEN_B			=		\033[0;92m
GREEN_BBL		=		\033[0;92;5m
YELLOW			=		\033[0;33m
YELLOW_BL		=		\033[0;33;5m
YELLOW_B		=		\033[0;93m
YELLOW_BBL		=		\033[0;93;5m
BLUE			=		\033[0;34m
BLUE_BL			=		\033[0;34;5m
BLUE_B			=		\033[0;94m
BLUE_BBL		=		\033[0;94;5m
MAGENTA			=		\033[0;35m
MAGENTA_BL		=		\033[0;35;5m
MAGENTA_B		=		\033[0;95m
MAGENTA_BBL		=		\033[0;95;5m
CYAN			=		\033[0;36m
CYAN_BL			=		\033[0;36;5m
CYAN_B			=		\033[0;96m
CYAN_BBL		=		\033[0;96;5m
WHITE			=		\033[0;37m
WHITE_BL		=		\033[0;37;5m
WHITE_B			=		\033[0;97m
WHITE_BBL		=		\033[0;97;5m
CUSTOM_1		=		\033[38:5:177m
CUSTOM_2		=		\033[38:5:208m
CUSTOM_3		=		\033[38:5:112m
CUSTOM_4		=		\033[38:5:101m
#---------SRC OBJ DEP INC---------
SRC_FILES		=		$(SUB_DIR_1)main					\
						$(SUB_DIR_1)init					\
						$(SUB_DIR_1)testing					\
						$(SUB_DIR_2)loop_and_hooks			\
						$(SUB_DIR_3)cast_ray				\
						$(SUB_DIR_3)pick_collision			\
						$(SUB_DIR_3)raycast_frame			\
						$(SUB_DIR_3)utils					\
						$(SUB_DIR_3)wall					\
						$(SUB_DIR_4)cam_movements			\
						$(SUB_DIR_5)file_parse				\
						$(SUB_DIR_5)map_checker				\
						$(SUB_DIR_5)utils					\
						$(SUB_DIR_5_1)action_utils			\
						$(SUB_DIR_5_1)actions				\
						$(SUB_DIR_5_1)evaluate				\
						$(SUB_DIR_5_1)init					\
						$(SUB_DIR_5_1)state_matrix			\
						$(SUB_DIR_6)minimap					\

SRC 			= 		$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 		$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 		$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS			= 		$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))
#----------CACHE----------
OBJF			=		.cache_exists
#---------------------------------	
all:	
			@$(MAKE) $(NAME)

makelibs:
			@$(MAKE) -C $(LFT_DIR)
			@$(MAKE)  --silent -C $(MLX_DIR)
			
-include	${DEPS}
$(NAME):	$(OBJ) makelibs
			@$(CC) $(CFLAGS) $(OBJ) $(MLXCC) $(LIBFT) $(MLX) -o $(NAME)
			@echo "$(CLEAN_LINE)$(CUSTOM_4)FLAGS USED		$(CUSTOM_1)$(CC)$(CFLAGS)$(MLXCC)$(DEF_COLOR)"
			@echo "$(CLEAN_LINE)$(CUSTOM_4)CUB3D			$(GREEN)✔ COMPILED CORRECTLY$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "$(CLEAN_LINE)$(YELLOW_BL)COMPILING:		⚙ $<$(RETURN)"
			@$(CC) $(CFLAGS) -MMD -c $< -o $@
#			@sleep 0.02

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_1)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_2)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_3)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_4)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_5)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_5_1)
			@mkdir -p $(OBJ_DIR)$(SUB_DIR_6)

$(LIBFT):
			@make -C $(LFT_DIR)
			@echo "$(GREEN)LIBFT	COMPILED$(DEF_COLOR)"

clean:
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(CUSTOM_4)OBJ FILES		$(GREEN)✔ CLEANED$(DEF_COLOR)"
			@make clean -sC $(LFT_DIR)
			@echo "$(CUSTOM_4)LIBFT			$(GREEN)✔ CLEANED$(DEF_COLOR)"
			@make clean -sC $(MLX_DIR)
			@echo "$(CUSTOM_4)MLX			$(GREEN)✔ CLEANED$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(LIBFT)
			@echo "$(CUSTOM_4)LIBFT.a			$(GREEN)✔ CLEANED$(DEF_COLOR)"
			@$(RM) -f $(MLX)
			@echo "$(CUSTOM_4)MLX.a			$(GREEN)✔ CLEANED$(DEF_COLOR)"
			@$(RM) -f $(NAME)
			@echo "$(CUSTOM_4)CUB3D EXECUTABLE	$(GREEN)✔ CLEANED$(DEF_COLOR)"

re:			fclean
			@$(MAKE)
			@echo "$(CLEAN_LINE)$(CUSTOM_4)CUB3D			$(GREEN)✔ CLEANED, REBUILT & READY TO USE$(DEF_COLOR)"

norminette:
			@echo "$(CLEAR)"
			@echo "\n$(YELLOW)SRC FILES	$(YELLOW_B)NORMINETTED\n$(DEF_COLOR)"
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true
			@echo "\n$(YELLOW)INCLUDE FILES	$(YELLOW_B)NORMINETTED\n$(DEF_COLOR)"
			@norminette $(INC_DIR) | grep -v Norme -B1 || true
			@echo "\n$(YELLOW)LIBFT FILES	$(YELLOW_B)NORMINETTED\n$(DEF_COLOR)"
			@norminette $(LFT_DIR) | grep -v Norme -B1 || true

PHONY: default all makelibs bonus clean fclean re norminette
