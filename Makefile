ROOT = ./test_srcs/

NAME = test

CXX = g++
#CXXFLAGS = -fsanitize=address -g3 -Wall -Werror -Wextra
CXXFLAGS = -fsanitize=address -g3

SRC =	$(ROOT)main.cpp \
		$(ROOT)exec.cpp \
		#$(ROOT)vector_test.cpp\

OBJ =	$(SRC:.cpp=.o)

MSG = Default commit message
#MSG="message" to change message

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean
	@rm -rf $(OBJ)

re: fclean $(NAME)

t: re
	@./$(NAME)

git: fclean
	@git add .
	@git commit -m "$(MSG)"
	git push
