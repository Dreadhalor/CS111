CC = gcc
CFLAGS = -g -o2 -Wall -Wextra
ID = 404491101
ARCHIVE = lab0-$(ID).tar.gz
sources = Makefile lab0.c errors.c README backtrace.png breakpoint.png

all:
	@$(CC) $(CFLAGS) -o lab0 lab0.c

check: clean all test

test:
	@./lab0 --input=nonexist.txt > output.txt 2> /dev/null ; \
	if [ $$? -ne 2 ] ; \
	then \
		echo "Return value for input error is incorrect! It is: $$?" ; \
		exit 1 ; \
	fi

	@echo "Hello, world!" > output.txt
	@chmod -w output.txt
	@echo "Goodbye, world!" | ./lab0 --output=output.txt 2> /dev/null ; \
	if [ $$? -ne 3 ] ; \
	then \
		echo "Return value for output error is incorrect! It is: $$?" ; \
		exit 1 ; \
	fi
	@chmod +w output.txt
	@rm -f output.txt
	
	@./lab0 --segfault --catch 2> /dev/null ; \
	if [ $$? -ne 4 ] ; \
	then \
		echo "Return value for --catch is incorrect! It is: $?" ; \
		exit 1 ; \
	fi

	@echo "All test cases passed"

dist:
	@tar -czf $(ARCHIVE) $(sources)

clean:
	@rm -f lab0