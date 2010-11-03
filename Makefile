CFLAGS=-Wall --pedantic -Wformat -s

all: libNewSock.so examples

libNewSock.so: src/Socket.cpp src/Error.cpp src/SetError.cpp
	g++ -fPIC $(CFLAGS) -c src/Socket.cpp -o src/Socket.o
	g++ -fPIC $(CFLAGS) -c src/Error.cpp -o src/Error.o
	g++ -fPIC $(CFLAGS) -c src/SetError.cpp -o src/SetError.o
	mkdir lib -p
	g++ -shared src/Socket.o src/Error.o src/SetError.o -o lib/libNewSock.so

examples: examples/example1.cpp examples/example2.cpp examples/example3.cpp examples/example4.cpp examples/example5.cpp
	g++ $(CFLAGS) examples/example1.cpp -o examples/example1.out -lNewSock -L./lib/
	g++ $(CFLAGS) examples/example2.cpp -o examples/example2.out -lNewSock -L./lib/
	g++ $(CFLAGS) examples/example3.cpp -o examples/example3.out -lNewSock -L./lib/
	g++ $(CFLAGS) examples/example4.cpp -o examples/example4.out -lNewSock -L./lib/
	g++ $(CFLAGS) examples/example5.cpp -o examples/example5.out -lNewSock -L./lib/
	g++ $(CFLAGS) examples/example6.cpp -o examples/example6.out -lNewSock -L./lib/
	g++ $(CFLAGS) examples/example7.cpp -o examples/example7.out -lNewSock -L./lib/

clean:
	rm lib -r -f
	rm src/*.o -f
	rm examples/*.out -f

.PHONY: all clean examples libNewSock.so

