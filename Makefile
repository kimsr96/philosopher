CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
SRCS = main.c thread.c utils.c acting.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	rm -f $(OBJS)

fclean :
	make clean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re