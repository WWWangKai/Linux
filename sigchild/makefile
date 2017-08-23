.PHONY:all
all:sigchld test file

sigchld:sigchld.c
	gcc -o $@ $^

test:test.c
	gcc -o $@ $^

file:file.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f sigchld test clean
