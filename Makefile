NAME = test

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra

SRCS = main.cpp

MSG = Default commit message
#MSG="message" to change message

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

git:
	git add .
	git commit -m "$(MSG)"
	git push
