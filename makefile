
all:
	@gcc -o test test.c string_buffer.c -Wall
	@echo run test
	@./test
	@rm -f ./test