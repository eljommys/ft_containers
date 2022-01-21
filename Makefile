MSG=Default commit message

init:
	chmod 777 init.sh
	./init.sh

all: vector stack map

vector: init
	cd containers_test ; ./do.sh vector

stack: init
	cd containers_test ; ./do.sh stack

map: init
	cd containers_test ; ./do.sh map

clean:
	@rm -rf containers_test

re: all clean

do:
	cd containers_test ; ./one ../vector.hpp

git: clean
	@git add .
	@git commit -m "$(MSG)"
	git push

.PHONY: all clean re git
