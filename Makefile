NAME = philo

SRCS =	main.c\
		simulation.c\
		utils.c\
		asan.c

OBJS = $(SRCS:.c=.o)

CC = gcc 


INCLUDES = -I .

LINKERS = -lpthread


ASAN := -fsanitize=address -fsanitize-recover=address
ASAN += -fno-omit-frame-pointer -fno-common
ASAN += -fsanitize=pointer-subtract -fsanitize=pointer-compare
# Technicaly UBSan but works with ASan
ASAN += -fsanitize=undefined
# Technicaly LSan but works with ASan
ASAN += -fsanitize=leak
# Thread sanitizing flags
TSAN := -fsanitize=thread
# Memory sanitizing flags
MSAN := -fsanitize=memory -fsanitize-memory-track-origins

FLAGS = -Wall -Wextra -Werror ${TSAN} -g

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