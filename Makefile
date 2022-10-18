NAME = philo

SRCS =	main.c\
		simulation.c\
		actions.c\
		utils.c\
		death.c

OBJS = $(SRCS:.c=.o)

CC = gcc 


INCLUDES = -I .

LINKERS = -pthread

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