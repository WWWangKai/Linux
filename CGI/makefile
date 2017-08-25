.PHONY:all
all:d dup

dup:dup.c
	gcc -o $@ $^

d:d.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f dup d
