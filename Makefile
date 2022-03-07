MSG=Default commit message

init:
	chmod 777 init.sh
	./init.sh

clean:
	@rm -rf containers_test test

git: clean
	@git add .
	@git commit -m "$(MSG)"
	git push

.PHONY: all clean re git
