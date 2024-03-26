CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread #-pthread
RM = rm -rf
NAME = philo
SRCS = main.c initialize_data.c parsing.c start_dinner.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	 $(CC)  $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

%.o: %.c philosopher.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all