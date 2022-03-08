MSG=Default commit message

SRCS			= main.cpp
OBJS			= $(SRCS:.cpp=.o)

CPP				= clang++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
NAME			= test

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CXXFLAGS) $(OBJS) -o $(NAME)

init:
	chmod 777 init.sh
	./init.sh

clean:
	@rm -rf containers_test $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)

git: clean
	@git add .
	@git commit -m "$(MSG)"
	git push



.PHONY: all clean re git
