.SILENT:

#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

COMPILER = gcc
CFLAGS = -Wall -Wextra -pthread
FILE = lab2_list
EH = lab2b
FILE_b = $(EH)_list
OUTPUT = $(FILE)
INPUT = $(FILE).c
CSV = $(FILE_b).csv
GP = $(FILE_b).gp
PNG = $(EH)_1.png $(EH)_2.png $(EH)_3.png $(EH)_4.png $(EH)_5.png
PROFILE = profile.out
SOURCES = $(INPUT) imports.c SortedList.c SortedList.h README Makefile $(CSV) $(GP) $(PNG) $(PROFILE)
ID = 404491101
LAB = lab2
SUBLAB = b
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz
USER = hetrick@lnxsrv.seas.ucla.edu



default: build

build:
	$(COMPILER) $(CFLAGS) SortedList.c -o $(OUTPUT) $(INPUT)
b-two:
	$(COMPILER) $(CFLAGS) SortedList.c -o lab2_list_2 list2.c

clean:
	rm -rf $(OUTPUT) $(OUTPUT_2) $(TARBALL_NAME) *.o

tests: build
	# lab2b_1.png
	./lab2_list --threads=1 --iterations=1000 --sync=s > lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv

	# lab2b_2.png
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv

	# lab2b_3.png
	-./lab2_list --threads=1 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=1 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=1 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=1 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=1 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=20 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=40 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=80 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=10 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=20 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=40 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=80 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=10 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=20 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=40 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=80 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=10 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=20 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=40 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=80 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=10 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=20 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=40 --sync=s --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=80 --sync=s --yield=id --lists=4 >> lab2b_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=20 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=40 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=80 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=10 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=20 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=40 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=80 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=10 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=20 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=40 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=80 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=10 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=20 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=40 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=80 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=10 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=20 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=40 --sync=m --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=80 --sync=m --yield=id --lists=4 >> lab2b_list.csv

	# lab2b_4.png
	./lab2_list --threads=1 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv

	# lab2b_5.png
	./lab2_list --threads=1 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	

graphs:
	gnuplot lab2b_list.gp

dist-nobuild:
	tar -czf $(TARBALL_NAME) $(SOURCES)
dist: build tests graphs dist-nobuild

profile:
	rm -f lab2_list.prof
	LD_PRELOAD=/usr/lib64/libprofiler.so CPUPROFILE=lab2_list.prof ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./lab2_list.prof > profile.out
	pprof --list=run_thread ./lab2_list ./lab2_list.prof >> profile.out
	rm -f lab2_list.prof

untar:
	@tar -xf $(TARBALL_NAME)

transfer-nodist: dist-nobuild
	scp $(TARBALL_NAME) $(USER):CS111/$(LAB)$(SUBLAB)

transfer: dist transfer-nodist

transfer-script:
	@scp P2B_check.sh $(USER):CS111/$(LAB)$(SUBLAB)

transfer-make:
	@scp Makefile $(USER):CS111/$(LAB)$(SUBLAB)

transfer-back-tests:
	@scp $(USER):CS111/$(LAB)$(SUBLAB)/lab2b_list.csv .

transfer-back-profile:
	@scp $(USER):CS111/$(LAB)$(SUBLAB)/profile.out .