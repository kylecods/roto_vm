lex:
	lex -t rasm.l >rasm.c


compile:
	gcc -o rasmv0.1 main.c rasm.c -Wall -Wextra -g

run:
	./rasmv0.1 test.txt newtest.rasm
