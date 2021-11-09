CC=gcc
CFLAGS=-I. -g
CPPFLAGS=-I. -g -std=c++17
DEPS =
OBJ = page.o store.o cache.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CPPFLAGS)

default: $(OBJ)
	$(CC) -o cache_sim $^ $(CFLAGS)

clean:
	rm -f *.o *.out

run: default
	./cache_sim

test-build: $(OBJ) test/test_main.o
	g++ page.o store.o cache.o test/test_main.o -o cache_test -lgtest -lgtest_main -lpthread

test-create: test-build
	./cache_test --gtest_filter=Cache.Creating

test-fifo: test-build
	./cache_test --gtest_filter=Cache.FIFO

test-lru: test-build
	./cache_test --gtest_filter=Cache.LRU

test-mru: test-build
	./cache_test --gtest_filter=Cache.MRU

test: test-build
	./cache_test
