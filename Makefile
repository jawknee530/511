stringsub: main.o customstream.o
	g++ -std=c++11 -g -Wall -pedantic -o stringsub main.o customstream.o

main.o: main.cpp customstream.h
	g++ -std=c++11 -Wall -c main.cpp

customstream.o: customstream.cpp customstream.h trackingdeque.h
	g++ -std=c++11 -Wall -c customstream.cpp

clean:
	rm *.o stringsub
