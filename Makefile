CPPFLAGS=-g -Wall -pedantic-errors
TESTS=test_00
test_00: test_00.cpp festival.o
festival.o: festival.h band.h sortedlist.h library1.h faketree.h
tests: test_00
	./test_00
vg: $(TESTS)
	valgrind --leak-check=full ./test_00 > /dev/null
clean:
	-rm test_00 *.o
