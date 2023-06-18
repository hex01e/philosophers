# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:31:24 by houmanso          #+#    #+#              #
#    Updated: 2023/05/13 20:43:36 by houmanso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CFLAGS = -Werror -Wall -Wextra -g
SRC = philo_bonus.c\
		activity_bonus.c\
		check_args_bonus.c\
		get_num_bonus.c\
		heap_bonus.c\
		sem_gen.c\
		utils_bonus.c
OBJ = $(SRC:.c=.o)

ifeq ($(s), 1)
	CFLAGS += -fsanitize=thread
endif

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@

%.o : %.c philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
