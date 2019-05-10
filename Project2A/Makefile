.SILENT:

#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

COMPILER = gcc
CFLAGS = -Wall -Wextra
FILE = lab2_add
OUTPUT = $(FILE)
INPUT = $(FILE).c
SOURCES = lab2_add.c
ID = 404491101
LAB = lab2
SUBLAB = a
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz
USER = hetrick@lnxsrv.seas.ucla.edu

default:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT) $(INPUT)

clean:
	rm -f $(OUTPUT) $(TARBALL_NAME)

dist:
	@tar -czf $(TARBALL_NAME) $(SOURCES)

untar:
	@tar -xf $(TARBALL_NAME)

transfer:
	@make && make dist && scp $(TARBALL_NAME) $(USER):CS111/$(LAB)$(SUBLAB)

transfer-script:
	@scp P2A_check.sh $(USER):CS111/$(LAB)$(SUBLAB)