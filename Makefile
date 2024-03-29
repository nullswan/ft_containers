# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: c3b5aw <dev@c3b5aw.dev>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 17:01:52 by c3b5aw            #+#    #+#              #
#    Updated: 2022/01/04 17:43:58 by c3b5aw           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= ft_containers
CC		:= clang++

CFLAGS	:= -Wall -Wextra -Werror -std=c++98
DFLAGS	= -MMD -MF $(@:.o=.d)

FILES	= main.cpp

OBJS_DIR	:= ./objs/
SRCS_DIR	:= ./srcs/

SRCS	:=	$(addprefix $(SRCS_DIR), $(FILES))
OBJS	:=	$(addprefix $(OBJS_DIR), $(FILES:.cpp=.o))
DEPS	:=	$(addprefix $(OBJS_DIR), $(FILES:.cpp=.d))

.PHONY	: all
all		: $(NAME)

-include $(DEPS)
$(NAME)	: $(OBJS)
	@	printf "Compiling $(NAME)\n"
ifeq ($(MODE), benchmark)
	@	$(CC) $(CFLAGS) $^ -o $@ -O3 -D FT_BENCHMARK=1
else
	@	$(CC) $(CFLAGS) $^ -o $@
endif

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	@	mkdir -p $(dir $@)
	@	printf "Compiling: $<"
ifeq ($(MODE), benchmark)
	@	$(CC) $(CFLAGS) -c $< -o $@ $(DFLAGS) -O3 -D FT_BENCHMARK=1
else
	@	$(CC) $(CFLAGS) -c $< -o $@ $(DFLAGS)
endif
	@	printf " -> OK\n"

.PHONY	: clean
clean	:
	@	printf "Deleting $(OBJS_DIR)\n"
	@	rm -rf $(OBJS_DIR)

.PHONY	: fclean
fclean	: clean
	@	printf "Deleting $(NAME) binary\n"
	@	rm -f $(NAME)

.PHONY	: re
re		: fclean all

.PHONY	: valgrind
valgrind: all
	@	valgrind --leak-check=full --track-fds=yes ./ft_containers

.PHONY	: lint
lint	:
	@	cpplint --recursive --root=srcs \
		--filter=-whitespace/tab,-legal/copyright,-build/explicit_make_pair,-build/include_what_you_use,-build/storage_class,-runtime/int \
		srcs/

.PHONY	: tests
tests	: re
	@	valgrind ./ft_containers