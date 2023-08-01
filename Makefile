CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_PATH = libft
SRC_DIR = srcs
OBJ_DIR = obj
INCLUDE_DIRS = include -I $(LIBFT_PATH) -I /opt/homebrew/Cellar/readline/8.2.1/include
LIBS =  -L$(LIBFT_PATH) -lreadline

SYS	= $(shell uname -s)

ifeq ($(SYS), Darwin)
INCLUDE_DIRS +=	-I /opt/vagrant/embedded/include
LIBS	+= -L/opt/vagrant/embedded/lib
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

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFT_PATH)/libft.a

NAME = minishell

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBS) -o $@ $^
	@echo Making $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INCLUDE_DIRS) -c -o $@ $<

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)
	@echo Deleting $(NAME)

re: fclean all