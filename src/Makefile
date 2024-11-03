CC=g++
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-lstdc++ -std=c++17
LINUX_FLAGS=-lrt -lpthread -lm -lsubunit
TEST_LIBS=-lgtest
TEST_SRC=tests.cpp
GCOV_FLAGS=--coverage
VALGRIND_FLAGS=--tool=memcheck --leak-check=yes
FILES := $(wildcard */*.cpp) $(wildcard */*.hpp) $(wildcard */*.h) $(wildcard */*.tpp)
OS := $(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
  OPEN_CMD = open
endif

all: test

test: clean
ifeq ($(OS), Darwin)
	$(CC) $(TEST_LIBS) $(CPPFLAGS) $(TEST_SRC) -o tests.out
else
	${CC} ${TEST_SRC} $(CPPFLAGS) -o tests.out $(TEST_LIBS) $(LINUX_FLAGS)
endif
	./tests.out

gcov_report: clean
ifeq ($(OS), Darwin)
	$(CC) $(GCOV_FLAGS) $(TEST_LIBS) $(CPPFLAGS) $(TEST_SRC) -o gcov_report 
else
	$(CC) $(GCOV_FLAGS) $(TEST_SRC) -o gcov_report $(TEST_LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
endif
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

valgrind: clean
	${CC} ${TEST_SRC}  $(CPPFLAGS) -o valgrind.out $(TEST_LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=VALGRIND.txt ./valgrind.out

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf gcov_report
	rm -rf valgrind.out
	rm -rf *.dSYM
	rm -rf *.gcov
	rm -rf gcov
	rm -rf coverage
	rm -rf coverage-html


clean: clean_lib clean_lib clean_test clean_obj
	rm -rf tests.out
	rm -rf VALGRIND.txt

	
stylemake:
	clang-format -style=Google -i $(FILES)
stylecheck:
	clang-format -style=Google -n $(FILES)


