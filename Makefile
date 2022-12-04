SRC = pipex.c utils_00.c utils_01.c ft_split.c\

OBJ = $(SRC:.c=.o)

NAME = pipex
RM = rm -rf
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m
CFLAGES = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) :$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(BLUE)██████████████████████ Compiling is DONE ███████████████████████$(RESET)"
	@make clean
%.o:%.c
	@echo "$(BLUE)██████████████████████     Compiling     ███████████████████████$(RESET)"
	@echo "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)████████████████████  Object files cleaned  ████████████████████$(RESET)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(RED)████████████████████     Game cleaned       ████████████████████$(RESET)"	
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re