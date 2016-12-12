compile: semaphone.o scntl.o
	gcc -g -o telephone.out telephone.o && gcc -g -o control.out control.o

semaphone.o: telephone.c
	gcc -g -c telephone.c

scntl.o: control.c
	gcc -g -c control.c

run: telephone.out
	./telephone.out

clean:
	./control.out -r \ 
	rm -f *~ *.out *.o *.txt