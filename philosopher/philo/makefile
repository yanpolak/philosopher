# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymarival <ymarival@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 11:04:43 by ymarival          #+#    #+#              #
#    Updated: 2023/03/30 11:45:58 by ymarival         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= 	main.c parser.c printing.c time.c init.c

					
OBJ			= $(SRC:.c=.o)

OBJB			= $(SRCB:.c=.o)

NAME			= philo

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror 


RM				= rm -f


all:			$(NAME)

$(NAME):		$(OBJ) 
				${CC} ${CFLAGS} -o $(NAME) $(OBJ) 

clean:
				$(RM) $(OBJ) $(OBJB) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:		$(OBJB)
			${CC} ${CFLAGS} -o $(NAME) $(OBJB)

.PHONY:			all clean fclean re bonus
