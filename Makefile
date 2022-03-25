all: main

main: main.o FASTAreadset_HT.o FASTAreadset_LL.o
	g++ -g -Wall -o main main.o FASTAreadset_HT.o FASTAreadset_LL.o

main.o:
	g++ -g -Wall -o main.o -c main.cpp
FASTAreadset_HT.o:
	g++ -g -Wall -o FASTAreadset_HT.o -c FASTAreadset_HT.cpp
FASTAreadset_LL.o:
	g++ -g -Wall -o FASTAreadset_LL.o -c FASTAreadset_LL.cpp

clean:
	rm main main.o FASTAreadset_HT.o FASTAreadset_LL.o