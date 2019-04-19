#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

COMPILER = gcc
CFLAGS = -Wall -Wextra
INPUT = lab1a.c
OUTPUT = lab1a
SOURCES = lab1a.c fxns.c README Makefile
ID = 404491101
LAB = lab1
SUBLAB = a
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz
USER = hetrick@lnxsrv.seas.ucla.edu

default:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT) $(INPUT)

clean:
	rm $(OUTPUT) $(TARBALL_NAME)

dist:
	@tar -czf $(TARBALL_NAME) $(SOURCES)

untar:
	@tar -xf $(TARBALL_NAME)

transfer:
	@make && make dist && scp $(TARBALL_NAME) $(USER):CS111/$(LAB)$(SUBLAB)