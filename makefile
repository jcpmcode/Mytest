default:procesa.o operaciones.o
	gcc procesa.o operaciones.o -o procesa
procesa:procesa.c
	gcc -c procesa.c
operaciones.o:operaciones.c
	gcc -c operaciones.c
todo:
	gcc procesa.c operaciones.c -o procesa
clean:
	rm *.o
