all: firdemo

firdemo: firdemo.o
	g++ -g -o firdemo firdemo.o -lfir

firdemo.o: firdemo.cpp
	g++ -g -c firdemo.cpp

clean:
	rm -f *~ *.o firdemo
