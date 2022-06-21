
check: test/test
	./test/test

test/test: test/test.c
	gcc test/test.c -o test/test