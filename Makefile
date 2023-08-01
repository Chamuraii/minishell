CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ_DIR = obj
SYS = $(shell uname -s)
ifeq ($(SYS), Darwin)
INCLUDE_DIRS = include -I libft -I /opt/homebrew/Cellar/readline/8.2.1/include -I /opt/vagrant/embedded/include
LIBS    = -L libft -lreadline -L/opt/vagrant/embedded/lib
endif
SRC_FILES = srcs/builtins_2.c \
            srcs/builtins.c \
            srcs/cd.c \
            srcs/echo.c \
            srcs/execute.c \
            srcs/expand.c \
            srcs/export.c \
            srcs/ft_free.c \
            srcs/heredoc.c \
            srcs/init.c \
            srcs/main.c \
            srcs/pipe_redirect_separator_2.c \
            srcs/pipe_redirect_separator.c \
            srcs/pipe.c \
            srcs/qvalidate.c \
            srcs/redirection.c \
            srcs/rvalidate_2.c \
            srcs/rvalidate.c \
            srcs/signals.c \
            srcs/start_exit.c \
            srcs/to_double_pointer.c \
            srcs/unset.c \
            srcs/utils_2.c \
            srcs/utils.c \
            srcs/where.c
OBJ_FILES = $(SRC_FILES:srcs/%.c=obj/%.o)
LIBFT = libft/libft.a
NAME = minishell
.PHONY: all clean fclean re
all: $(NAME)
$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBS) -o $@ $^
	@echo Making $(NAME)
$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INCLUDE_DIRS) -c -o $@ $<
$(LIBFT):
	@make -C libft
clean:
	@make -C libft clean
	@rm -r $(OBJ_DIR)
fclean: clean
	@make -C libft fclean
	@rm $(NAME)
	@echo Deleting $(NAME)
re: fclean all