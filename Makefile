# Nombre del programa
NAME       = minishell
# Flags de compilacion
FLAGS      = -Wall -Wextra -Werror -g -MD
# Directorios
SRC_DIR    = ./srcs/
OBJ_DIR    = ./obj/
INC_DIR    = ./includes/
LIBFT_DIR  = ./libft/
# Archivos fuentes y objetos
SRC_FILES  = $(wildcard $(SRC_DIR)*.c)
OBJ_FILES  = $(notdir $(SRC_FILES:.c=.o))
# Direcciones
SRC        = $(addprefix $(SRC_DIR),$(SRC_FILES))
OBJ        = $(addprefix $(OBJ_DIR),$(OBJ_FILES))
LIBFT      = $(addprefix $(LIBFT_DIR),libft.a)

BREW_LIB = "/Users/$(USER)/.brew/opt/readline/lib"
BREW_INCLUDE = "/Users/$(USER)/.brew/opt/readline/include/readline"

-include $(OBJ_FILES:.o=.d)

# Se compila el archivo binario (ejecutable).
all: obj $(LIBFT) $(NAME)
# Crea la carpeta donde estará los objetos.
obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -o $@ -c $(SRC_DIR)$(notdir $<)
# Compila la biblioteca libft.a
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Se compila los objetos con las librerías y archivos
$(NAME): $(OBJ)
	@echo "(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compilando, espere unos segundos..."
	@gcc $(OBJ) -o $(NAME) $(LIBFT) -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include/readline -lreadline
	@echo "(•̀ᴗ•́)و $(NAME) generado!"
# Remueve todos los archivos objetos
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "¯\_(ツ)_/¯ Objetos removidos!"
# Remueve todos los archivos objetos, binarios y sus respectivas carpetas
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "(╯°□°）╯︵ ┻━┻ $(NAME) removido!"
# Hace un re-make (como si se hubiera ejecutado Make por primera vez)
re: fclean all
# Le dice al make que estos nombres no son archivos
.PHONY: all clean fclean re