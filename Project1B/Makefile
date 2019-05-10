.SILENT:

#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

COMPILER = gcc
CFLAGS = -o2 -Wall -Wextra -D_POSIX_C_SOURCE -lz
OUTPUT-CLIENT = $(LAB)$(SUBLAB)-client
INPUT-CLIENT = $(OUTPUT-CLIENT).c
OUTPUT-SERVER = $(LAB)$(SUBLAB)-server
INPUT-SERVER = $(OUTPUT-SERVER).c
SOURCES = lab1b-client.c lab1b-server.c cslib.c fxns.c client-fxns.c server-fxns.c compression.c README Makefile
ID = 404491101
LAB = lab1
SUBLAB = b
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz
USER = hetrick@lnxsrv.seas.ucla.edu

default:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT-CLIENT) $(INPUT-CLIENT)
	$(COMPILER) $(CFLAGS) -o $(OUTPUT-SERVER) $(INPUT-SERVER)

clean:
	rm -f $(OUTPUT-SERVER) $(OUTPUT-CLIENT) $(TARBALL_NAME)

dist:
	@tar -czf $(TARBALL_NAME) $(SOURCES)

untar:
	@tar -xf $(TARBALL_NAME)

transfer:
	@make && make dist && scp $(TARBALL_NAME) $(USER):CS111/$(LAB)$(SUBLAB)

transfer-script:
	@scp P1B_check.sh $(USER):CS111/$(LAB)$(SUBLAB)