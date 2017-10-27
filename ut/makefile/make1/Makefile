
#test:test.c max.c min.c
#	gcc -o test test.c min.c max.c

#clean:
#	rm test

test:test.o min.o max.o
	gcc -o test test.o min.o max.o
test.o:test.c
	gcc -o test.o -c test.c
min.o:min.c
	gcc -o min.o -c min.c
max.o:max.c
	gcc -o max.o -c max.c
clean:
	rm *.o test
