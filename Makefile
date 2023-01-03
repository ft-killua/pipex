SRC = $(addprefix src/, pipex.c utils_00.c utils_01.c ft_split.c utils_main.c)
OBJ = $(SRC:.c=.o)

BSRC = $(addprefix bonus_src/, pipex_bonus.c utils_bonus_00.c utils_bonus_01.c \
ft_split_bonus.c utils_main_bonus.c)
BOBJ = $(BSRC:.c=.o)

NAME = pipex
B_NAME = pipex_bonus
RM = rm -rf
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m
CFLAGES = -Wall -Wextra -Werror

all: $(NAME)
bonus: $(B_NAME)
$(B_NAME): $(BOBJ)
	@$(CC) $(CFLAGS) $(BOBJ) -o $(B_NAME)
	@echo "$(GREEN)████████████████████Compiling Bonus is DONE ████████████████████$(RESET)"
	@make clean

$(NAME) :$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)██████████████████████ Compiling is DONE ███████████████████████$(RESET)"
	@make clean
	
%.o:%.c
	@echo "$(BLUE)██████████████████████     Compiling     ███████████████████████$(RESET)"
	@echo "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)████████████████████  Object files cleaned  ████████████████████$(RESET)"
	@$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@echo "$(RED)████████████████████     PIPEX cleaned      ████████████████████$(RESET)"
	@$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all bonus clean fclean re