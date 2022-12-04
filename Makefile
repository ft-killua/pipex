SRC = src/pipex.c src/utils_00.c src/utils_01.c src/ft_split.c src/utils_main.c
OBJ = $(SRC:.c=.o)

BSRC = bonus_src/pipex_bonus.c bonus_src/utils_bonus_00.c bonus_src/utils_bonus_01.c \
bonus_src/ft_split_bonus.c bonus_src/utils_main_bonus.c
BOBJ = $(BSRC:.c=.o)

NAME = pipex
RM = rm -rf
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m
CFLAGES = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(BOBJ)
	@$(CC) $(CFLAGS) $(BOBJ) -o $(NAME)
	@echo "$(BLUE)████████████████████Compiling Bonus is DONE ████████████████████$(RESET)"
	@make clean

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
	@$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@echo "$(RED)████████████████████     PIPEX cleaned      ████████████████████$(RESET)"	
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re