CPPFLAGS=-g -Wall -pedantic-errors
TESTS=test_00 test_01
test_00: test_00.cpp festival.o
test_01: test_01.cpp band.h
festival.o: festival.h band.h sortedlist.h library1.h faketree.h
tests: ${TESTS}
	./test_00
	./test_01
vg: $(TESTS)
	valgrind --leak-check=full ./test_00 > /dev/null
	valgrind --leak-check=full ./test_01 > /dev/null
clean:
	-rm test_00 test_01 *.o
