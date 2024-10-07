SRCS := main.c utils.c atoi.c philo.c thread_run.c thread_check.c
OBJS := $(SRCS:.c=.o)

CFLAGS := -Wall -Wextra -Werror 
#-fsanitize=thread -g
#-fsanitize=address -g

CC := cc
NAME := philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -I ./philo.h $(OBJS) -o $(NAME)
	
	
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus