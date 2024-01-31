NAME	=	minishell
CC	=	cc
FLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address
FLAGS2	=	-lreadline

SRC_FILE =	minishell.c minishell_utils.c child_execute.c\
			executor.c fd_create.c fd_close.c signals.c errors.c ft_execve.c \
			env_list.c lexer.c lexer_list.c env_remove.c \
			lexer_utils1.c lexer_utils2.c lexer_utils3.c cmd_list.c \
			parser.c parser_utils1.c parser_utils2.c parser_utils3.c \
			builtins1.c builtins2.c builtins_output.c builtins_utils.c \

SRC	=	${addprefix src/, ${SRC_FILE}}

#LIBFT_PATH	= libft/
#LIBFT_NAME	= libft.a
#LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
LIB		=	libft/libft.a

Green=\033[0;32m        # Green
Cyan=\033[0;36m         # Cyan
White=\033[0;37m        # White

all: $(NAME)

$(NAME): $(LIB) $(SRC)
	@ cc $(FLAGS) $(FLAGS2) $(SRC) $(LIB) -o $(NAME)
	@ echo "${Green}minishell${White}is ready"

$(LIB):
	@ make -C ./libft --no-print-directory --silent
#	@ echo "${Green}libft${White}compiled"

clean:
	@ make clean -C ./libft --no-print-directory --silent
	@ /bin/rm -f $(OBJ)
	@ echo "${Cyan}object files${White}deleted"
	
fclean: clean
	@ make fclean -C ./libft --no-print-directory --silent
	@ /bin/rm -f $(NAME)
	@ echo "${Cyan}object and library files${White}deleted"
re: fclean all

# OBJ =		$(SRC:.c=.o)

# all: $(LIBFT) $(NAME) 

# $(LIBFT):
# 	@make -C $(LIBFT_PATH) --no-print-directory --silent
# 	#@ echo "${Green}libft${White}compiled"

# $(NAME): $(OBJ) 
# 	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(FLAGS2) $(LIBFT)
# 	@ echo "${Green}minishell${White}is ready"

# clean:
# 	@$(RM) $(OBJ)
# 	@make clean -C $(LIBFT_PATH) --no-print-directory --silent
# 	@ echo "${Cyan}object files${White}deleted"

# fclean: clean
# 	@ make fclean -C ./libft --no-print-directory --silent
# 	@ /bin/rm -f $(NAME)
# 	@ echo "${Cyan}all files${White}deleted"

# re: clean all

.PHONY: all clean fclean re 

