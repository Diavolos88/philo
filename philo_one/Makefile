# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 12:37:09 by ealexa            #+#    #+#              #
#    Updated: 2021/03/01 18:18:11 by ealexa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
PATH_SRC = ./
HEADER = ./
FLAG = -Wall -Wextra -Werror
SRC = $(PATH_SRC)philo_one.c $(PATH_SRC)utils.c $(PATH_SRC)time.c  $(PATH_SRC)threads.c $(PATH_SRC)life.c $(PATH_SRC)others.c 
OBJ = philo_one.o

all: $(NAME)

$(NAME):
		@ gcc $(FLAG) $(SRC) -o ${NAME}

clean:
	@ /bin/rm -f $(OBJ_BONUS)
fclean: clean
	@ /bin/rm -f $(NAME)
	@ /bin/rm -f ./a.out

re: fclean all
