CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c thread.c utils.c init.c monitoring.c finish.c \
		acting.c eating.c 
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC = philo.h
NAME = philo

all : $(NAME) $(INC)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	@ rm -rf $(OBJ_DIR)

fclean :
	@ make clean
	@ rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re