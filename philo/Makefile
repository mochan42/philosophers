# **************************************************************************** #
# VARIABLES

NAME				:= philo

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror -pthread
DEBUG				:= none
ifeq ($(DEBUG), ON)
	CFLAGS			:= -Wall -Wextra -Werror -pthread -fsanitize=thread -g
endif

RM					:= rm -rf
INCS				:= -I ./inc/
HEADER				:= ./inc/philosophers.h

SRC_DIR				:= ./src/
OBJ_DIR				:= ./obj/

# **************************************************************************** #
# COLORS

GREEN				:= \033[0;92m
YELLOW				:= \033[0;93m
BLUE				:= \033[0;94m
END_COLOR			:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC_FILES			:=	philosophers.c check_input.c utils.c\
						init.c time.c routines.c death_management.c\

OBJ_FILES			:= ${SRC_FILES:.c=.o}

SRC					:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ					:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# **************************************************************************** #
# RULES

# all :	$(OBJ_DIR) $(NAME)
all : $(NAME)

$(NAME):  $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.


$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS)  -c $< -o $@ $(INCS)
# -c	:	gcc option to compile each .c file into .o file.
# $<	:	represents the first prerequisite of the rule (each .c file 
#			contained in the src folder).
# -o	:	gcc option to define the name of the program (output) file :
#			"push_swap".
# $@	:	represents the filename of the target of the rule, i.e. each output
#			file which will be linked with the so_long.h header file.

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

debug:  $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS_SANITIZE) $(OBJ) -o $(NAME)
	@echo "$(YELLOW)/!\ $(NAME) compiled with -fsanitize=thread -g flag!$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)

re: fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY:		all clean fclean re

