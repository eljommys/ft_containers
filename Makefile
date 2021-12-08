all:
	chmod 777 init.sh
	./init.sh

vector:
	./containers_test/do.sh vector
	
stack:
	./containers_test/do.sh stack

map:
	./containers_test/do.sh vector

clean:
	@rm -rf containers_test

re: all clean

git: clean
	@git add .
	@git commit -m "$(MSG)"
	git push

.PHONY: all clean re git
