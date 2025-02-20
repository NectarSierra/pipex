FLAGS = -Wall -Wextra -Werror
FSAN = -fsanitize=address -g
NAME = pipex
LIBFT_A = ./libft/libft.a
SRCS = ./srcs/main.c\
	   ./srcs/redirect_cmd.c\
	   ./srcs/path_cmd.c\
	   ./srcs/errors_handler.c\
	   ./srcs/utils.c\

$(NAME): $(SRCS)
	cd ./libft/ && make bonus
	clear
	gcc -g $(FLAGS) $(SRCS) ./libft/libft.a -o $(NAME)

fsan: $(SRCS)
	cd ./libft/ && make bonus
	clear
	cc $(FSAN) $(SRCS) ./libft/libft.a -o $(NAME)

wof: $(SRCS)
	cd ./libft/ && make bonus
	clear
	cc $(SRCS) ./libft/libft.a -o $(NAME)

re: fclean $(NAME)

all: $(NAME)

clean:
	cd ./libft/ && make clean

fclean:
	cd ./libft/ && make fclean
	rm -rf $(NAME)
	