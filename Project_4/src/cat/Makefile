CC = gcc
CFLAGS = -Wall -Werror -Wextra
all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat && rm -rf s21_cat.o

s21_cat.o:
	$(CC) $(CFLAGS) -c s21_cat.c

test:
	chmod 777 test.sh
	./test.sh

leak: rebuild
	sh test_leak_cat.sh

clang-fix:
	cp ../../materials/linters/.clang-format ./.clang-format
	clang-format -i *.c && clang-format -i *.h
	$(RM) .clang-format

clang-check:
	cp ../../materials/linters/.clang-format ./.clang-format
	clang-format -n *.c && clang-format -n *.h
	$(RM) .clang-format

clean:
	rm -rf *.o *.out s21_cat

rebuild: clean all
