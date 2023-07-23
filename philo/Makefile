# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 17:32:32 by tlukanie          #+#    #+#              #
#    Updated: 2023/07/23 15:55:26 by tlukanie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -g -Wall -Werror -Wextra
THREADS = -pthread
BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
RESET	:= \033[0m
OBJ = obj/main.o obj/utils.o obj/philo_death.o \
		obj/philo_init.o obj/philo_routine.o
NAME_H = philo.h

all: $(NAME) 

$(NAME): $(OBJ) $(NAME_H) 
	$(CC) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Runable philo created...🤔💭📚$(RESET)"
	@echo "$(BOLD)Run as follows:$(RESET)"
	@echo "$(BOLD)./philo number_of_philo time_to_die time_to_eat time_to_sleep$(RESET)"
	@echo "$(BOLD)(optional argument) number_of_times_each_philosopher_must_eat$(RESET)"

obj/%.o: %.c
	@if  [ ! -d obj/ ]; then \
		mkdir -p obj/; \
	fi
	$(CC) $(FLAGS) $(THREADS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files🧹🧼🧽$(RESET)"
	@rm -rf $(OBJ)
	@rm -rf obj

fclean: clean
	@echo "$(RED)Cleaning🧻🚽$(RESET)"
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re 