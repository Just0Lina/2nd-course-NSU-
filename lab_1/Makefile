OS=$(shell uname)
ifeq ($(OS), Linux)
	CXXFLAGS=-lgtest -g  -lpthread
	LEAKS = valgrind --leak-check=full
else
	CXXFLAGS = -lgtest -g
	LEAKS = CK_FORK=no leaks --atExit --
endif

CXX=g++ -std=c++17

all: gcov_report check

tests: clean 
		$(CXX) --coverage -O0 -C bigInt_tests.cpp bigInt.cpp -o bigInt_tests $(CXXFLAGS) && ./bigInt_tests


leaks: clean tests
	$(LEAKS) ./bigInt_tests

gcov_report: tests
	lcov -t "gcov_report" --no-external -o all_tests.info -c -d .
	genhtml -o all_report all_tests.info
	@open -a "Safari" all_report/index.html

clean:
	rm -rf *.gcda *.gcno *.o *.info *_tests *report

check:
	cppcheck --enable=all  --language=c++ 

 
.PHONY:  check clean gcov_report tests
