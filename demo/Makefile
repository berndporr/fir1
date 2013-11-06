all: firdemo fixeddemo

firdemo: firdemo.o
	g++ -g -o firdemo firdemo.o -lfir

firdemo.o: firdemo.cpp
	g++ -g -c firdemo.cpp

fixeddemo: fixeddemo.o
	g++ -g -o fixeddemo fixeddemo.o -lfir

fixeddemo.o: fixeddemo.cpp
	g++ -g -c fixeddemo.cpp

clean:
	rm -f *~ *.o firdemo fixeddemo
