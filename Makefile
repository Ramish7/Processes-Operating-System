all: phistogram | thistogram

phistogram: phistogram.c
	gcc -o phistogram phistogram.c

thistogram: thistogram.c
	gcc -pthread -o thistogram thistogram.c	

clean:
	rm phistogram
	rm thistogram