prog2: prog2new.o prog2driver.o
	g++ -o prog2 prog2new.o prog2driver.o

clean:
	/bin/rm -f *.o prog2
