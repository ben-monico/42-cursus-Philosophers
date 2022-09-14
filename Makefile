NAME = philo

SRCS =	main.c\
		simulation.c\
		utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc 


INCLUDES = -I .

LINKERS = -lpthread

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

.c.o:
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(LINKERS) $(OBJS) -o $(NAME)


all: $(NAME)

re: fclean all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean