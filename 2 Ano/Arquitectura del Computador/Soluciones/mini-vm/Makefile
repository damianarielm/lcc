all:
	bison -d parser.y
	flex parser.lex
	gcc *.c -g -o machine
