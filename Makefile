NAME	=	minishell

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -g

SYS = $(shell uname -s)
ifeq ($(SYS), Darwin)
EXTERNAL_INCLUDES = -Iinclude -I libft -I /opt/homebrew/Cellar/readline/8.2.1/include -I /opt/vagrant/embedded/include
EXTERNAL_LIBS	= -L libft -lreadline -L/opt/vagrant/embedded/lib
endif
ifeq ($(SYS), Linux)
EXTERNAL_INCLUDES = -Iinclude -I libft -I /usr/include/readline
EXTERNAL_LIBS	= -L libft -lreadline -L /usr/lib
endif

#directories
SRC_DIR					=	src/
OBJ_DIR					=	obj/
INC_DIR					=	include/
LIBFT_DIR				=	libft/
CURRENT_PATH			=	$(shell pwd)
CURRENT_DIRECTORY_NAME	=	$(shell basename $(CURRENT_PATH))
CURRENT_DIRECTORY		:=	./$(CURRENT_DIRECTORY_NAME)

#controll codes
RESET			=	\033[0m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
RED				=	\033[31m
UP				=	\033[A
CUT				=	\033[K

#source files
SRC_FILES = builtins_2.c \
			builtins.c \
			cd.c \
			echo.c \
			execute.c \
			expand.c \
			export.c \
			ft_free.c \
			heredoc.c \
			init.c \
			main.c \
			pipe_redirect_separator_2.c \
			pipe_redirect_separator.c \
			pipe.c \
			qvalidate.c \
			redirection.c \
			rvalidate_2.c \
			rvalidate.c \
			signals.c \
			start_exit.c \
			to_double_pointer.c \
			unset.c \
			utils_2.c \
			utils.c \
			where.c

OBJ_FILES	=	$(SRC_FILES:.c=.o)

#paths
SRC 		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT		=	$(addprefix $(LIBFT_DIR), libft.a)

all: $(LIBFT) $(NAME) 

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

#compile the executable
$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(EXTERNAL_LIBS) -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(FLAGS) -I $(INC_DIR) -I $(EXTERNAL_INCLUDES) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"


#clean rule
clean:
	$(MAKE) -C libft clean
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects from $(CURRENT_DIRECTORY)...$(RESET)"; else \
	echo "No objects to remove from $(CURRENT_DIRECTORY)."; \
	fi;

#fclean rule
fclean: clean
	$(MAKE) -C libft fclean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	echo "$(BLUE)Deleting $(RED)$(NAME)$(BLUE) binary from $(CURRENT_DIRECTORY)$(RESET)"; else \
	echo "No Executable to remove from $(CURRENT_DIRECTORY)."; \
	fi;

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re
