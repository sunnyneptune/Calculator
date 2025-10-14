CC = gcc
CPPFLAGS = -Werror -Wextra -Wall -std=c11 
CFLAGS = -std=c11 -pedantic
LFLAGS = -lcheck -lm
OBJECTS = $(SOURCES:.c=.o)
SOURCES = calculator.c stack.c
TESTS = tests.c

all: clean test

calctry.a: $(OBJECTS)
	@$(CC) $(CPPFLAGS) $(SOURCES) -c
	@ar rcs calctry.a $(OBJECTS)
	@rm *.o

test: calctry.a $(TESTS)
	@$(CC) $(CPPFLAGS) $(TESTS) calctry.a -o test.out $(LFLAGS)
	@./test.out

install:
	mkdir build
	cd build&&qmake ../calctry.pro&&make&&mv calctry.app ../calctry.app
	rm -rf build
	open calctry.app
	qmake -project ../calctry.pro -o SmartCalc_v1.exe

uninstall:
	rm -rf build
	rm -rf SmartCalc_v1.exe
	rm -rf calctry.pro.user
	rm -rf html

check:
	clang-format -n -style=Google $(SOURCES) $(TESTS) *.cpp *.h 
	clang-format -i -style=Google $(SOURCES) $(TESTS) *.cpp *.h

dvi:
	open ../README_RUS.md

dist:
	cd .. && tar -czf SRC_C7_SmartCalc_v1.0-0.tgz src

gcov_report:
	gcc -o test $(TESTS) --coverage $(SOURCES) -lcheck -lm
	./test
	lcov -t "a.out" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf test *.o *.a *gcda *gcno *info

clean:
	rm -rf $(OBJECTS) calctry.a test *.gcda *.gcno *.html *.css report/ user_guide/
	rm -rf *.exe
	rm -rf SmartCalc_v1.exe
	rm -rf calctry.app
	rm -rf SmartCalc_v1.exe.pro
	rm -rf html
