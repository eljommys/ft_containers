MSG=Default commit message

all:
	chmod 777 init.sh
	./init.sh

vector: all
	cd containers_test ; ./do.sh vector
	
stack:
	cd containers_test ; ./do.sh stack

map:
	cd containers_test ; ./do.sh vector

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
