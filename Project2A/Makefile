.SILENT:

#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

COMPILER = gcc
CFLAGS = -Wall -Wextra -lpthread
FILE = lab2_add
OUTPUT = $(FILE)
INPUT = $(FILE).c
CSV = $(FILE).csv
PNGS = $(FILE)-1.png $(FILE)-2.png $(FILE)-3.png $(FILE)-4.png $(FILE)-5.png
SOURCES = lab2_add.c imports.c SortedList.c SortedList.h README Makefile $(CSV) $(PNGS)
ID = 404491101
LAB = lab2
SUBLAB = a
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz
USER = hetrick@lnxsrv.seas.ucla.edu

default: build

build:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT) $(INPUT)

clean:
	rm -f $(OUTPUT) $(TARBALL_NAME)

tests:
	make
	# add
	./lab2_add --threads=1 --iterations=100 > $(CSV)
	./lab2_add --threads=1 --iterations=1000 >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 >> $(CSV)
	./lab2_add --threads=1 --iterations=100000 >> $(CSV)
	./lab2_add --threads=2 --iterations=100 >> $(CSV)
	./lab2_add --threads=2 --iterations=1000 >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 >> $(CSV)
	./lab2_add --threads=2 --iterations=100000 >> $(CSV)
	./lab2_add --threads=4 --iterations=100 >> $(CSV)
	./lab2_add --threads=4 --iterations=1000 >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 >> $(CSV)
	./lab2_add --threads=4 --iterations=100000 >> $(CSV)
	./lab2_add --threads=8 --iterations=100 >> $(CSV)
	./lab2_add --threads=8 --iterations=1000 >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 >> $(CSV)
	./lab2_add --threads=8 --iterations=100000 >> $(CSV)
	./lab2_add --threads=12 --iterations=100 >> $(CSV)
	./lab2_add --threads=12 --iterations=1000 >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 >> $(CSV)
	./lab2_add --threads=12 --iterations=100000 >> $(CSV)

	# lab2_add-1.png
	./lab2_add --threads=1 --iterations=10 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=20 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=40 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=80 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=10 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=20 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=40 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=80 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=10 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=20 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=40 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=80 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=10 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=20 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=40 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=80 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=10 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=20 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=40 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=80 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=12 --iterations=100000 --yield >> $(CSV)

	# lab3_add-3.png
	./lab2_add --threads=1 --iterations=10 >> $(CSV)
	./lab2_add --threads=1 --iterations=100 >> $(CSV)
	./lab2_add --threads=1 --iterations=1000 >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 >> $(CSV)
	./lab2_add --threads=1 --iterations=100000 >> $(CSV)

	# lab2_add-2.png
	./lab2_add --threads=1 --iterations=100 >> $(CSV)
	./lab2_add --threads=1 --iterations=1000 >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 >> $(CSV)
	./lab2_add --threads=1 --iterations=100000 >> $(CSV)
	./lab2_add --threads=2 --iterations=100 >> $(CSV)
	./lab2_add --threads=2 --iterations=1000 >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 >> $(CSV)
	./lab2_add --threads=2 --iterations=100000 >> $(CSV)
	./lab2_add --threads=4 --iterations=100 >> $(CSV)
	./lab2_add --threads=4 --iterations=1000 >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 >> $(CSV)
	./lab2_add --threads=4 --iterations=100000 >> $(CSV)
	./lab2_add --threads=8 --iterations=100 >> $(CSV)
	./lab2_add --threads=8 --iterations=1000 >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 >> $(CSV)
	./lab2_add --threads=8 --iterations=100000 >> $(CSV)
	./lab2_add --threads=1 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=1 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=2 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=4 --iterations=100000 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=100 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=1000 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --yield >> $(CSV)
	./lab2_add --threads=8 --iterations=100000 --yield >> $(CSV)

	# lab2_add-4.png
	./lab2_add --threads=2 --iterations=10000 --yield --sync=m >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --yield --sync=m >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --yield --sync=m >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> $(CSV)
	./lab2_add --threads=2 --iterations=1000 --yield --sync=s >> $(CSV)
	./lab2_add --threads=4 --iterations=1000 --yield --sync=s >> $(CSV)
	./lab2_add --threads=8 --iterations=1000 --yield --sync=s >> $(CSV)
	./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 --yield --sync=c >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --yield --sync=c >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --yield --sync=c >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> $(CSV)

	# lab2_add-5.png
	./lab2_add --threads=1 --iterations=10000 >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 --sync=m >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 --sync=m >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --sync=m >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --sync=m >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 --sync=m >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 --sync=s >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 --sync=s >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --sync=s >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --sync=s >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 --sync=s >> $(CSV)
	./lab2_add --threads=1 --iterations=10000 --sync=c >> $(CSV)
	./lab2_add --threads=2 --iterations=10000 --sync=c >> $(CSV)
	./lab2_add --threads=4 --iterations=10000 --sync=c >> $(CSV)
	./lab2_add --threads=8 --iterations=10000 --sync=c >> $(CSV)
	./lab2_add --threads=12 --iterations=10000 --sync=c >> $(CSV)

graphs:
	gnuplot lab2_add.gp

dist: build
	@tar -czf $(TARBALL_NAME) $(SOURCES)

untar:
	@tar -xf $(TARBALL_NAME)

transfer: dist
	scp $(TARBALL_NAME) $(USER):CS111/$(LAB)$(SUBLAB)

transfer-script:
	@scp P2A_check.sh $(USER):CS111/$(LAB)$(SUBLAB)

transfer-make:
	@scp Makefile $(USER):CS111/$(LAB)$(SUBLAB)