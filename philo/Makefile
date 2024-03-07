NAME	= philo
SRCS	= dispose.c first_loop.c main.c op.c print.c state.c utils.c

CC		= @gcc
CFLAGS	= -Wall -Werror -Wextra -pthread

all: $(NAME)

$(NAME): $(SRCS) philo.h
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean
	@rm -rf philo.dSYM

re: fclean all

.PHONY: all clean fclean re