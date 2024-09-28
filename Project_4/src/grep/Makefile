CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep && rm -rf s21_grep.o

s21_grep.o:
	$(CC) $(CFLAGS) -c s21_grep.c

test:
	chmod 777 test.sh
	./test.sh

leak: rebuild
	sh test_leak_grep.sh

clang-fix:
	cp ../../materials/linters/.clang-format ./.clang-format
	clang-format -i *.c && clang-format -i *.h
	$(RM) .clang-format

clang-check:
	cp ../../materials/linters/.clang-format ./.clang-format
	clang-format -n *.c && clang-format -n *.h
	$(RM) .clang-format

clean:
	rm -rf *.o *.out s21_grep

rebuild: clean all
