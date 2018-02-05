default:copy.o operaciones.o
	gcc copy.o operaciones.o -o copy
copy.o:copy.c
	gcc -c copy.c
operaciones.o:operaciones.c
	gcc -c operaciones.c
todo:
	gcc copy.c operaciones.c -o copy
clean:
	rm *.o
