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

NAME = philo
CFLAGS = -Werror -Wall -Wextra
SRC = philo.c\
		setup_philos.c\
		check_args.c\
		activity.c\
		get_num.c\
		heap.c\
		utils.c
OBJ = $(SRC:.c=.o)

ifeq ($(s), 1)
	CFLAGS += -fsanitize=thread
endif

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@

%.o : %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all