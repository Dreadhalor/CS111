.SILENT:

default:
	gcc -g lab1b-client.c -o lab1b-client -Wall -Wextra
	gcc -g lab1b-server.c -o lab1b-server -Wall -Wextra

clean:
	rm -f lab1b-server lab1b-client lab1b-404491101.tar.gz

dist:
	tar -czf lab1b-404491101.tar.gz lab1b-client.c lab1b-server.c cslib.c fxns.c README my.key Makefile