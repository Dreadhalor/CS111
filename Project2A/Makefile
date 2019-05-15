.SILENT:

#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

COMPILER = gcc
CFLAGS = -Wall -Wextra -pthread
FILE_1 = lab2_add
OUTPUT_1 = $(FILE_1)
INPUT_1 = $(FILE_1).c
CSV_1 = $(FILE_1).csv
GP_1 = $(FILE_1).gp
PNGS_1 = $(FILE_1)-1.png $(FILE_1)-2.png $(FILE_1)-3.png $(FILE_1)-4.png $(FILE_1)-5.png
FILE_2 = lab2_list
OUTPUT_2 = $(FILE_2)
INPUT_2 = $(FILE_2).c
CSV_2 = $(FILE_2).csv
GP_2 = $(FILE_2).gp
PNGS_2 = $(FILE_2)-1.png $(FILE_2)-2.png $(FILE_2)-3.png $(FILE_2)-4.png
CSV_PNG_GP = $(CSV_1) $(GP_1) $(PNGS_1) $(CSV_2) $(GP_2) $(PNGS_2)
SOURCES = lab2_add.c lab2_list.c imports.c SortedList.c SortedList.h README Makefile $(CSV_PNG_GP)
ID = 404491101
LAB = lab2
SUBLAB = a
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz
USER = hetrick@lnxsrv.seas.ucla.edu



default: build

build-add:
	$(COMPILER) $(CFLAGS) -o $(OUTPUT_1) $(INPUT_1)
build-list:
	$(COMPILER) $(CFLAGS) SortedList.c -o $(OUTPUT_2) $(INPUT_2)

build: build-add build-list

clean:
	rm -rf $(OUTPUT_1) $(OUTPUT_2) $(TARBALL_NAME) *.o

tests-add: build-add
	# add
	./lab2_add --threads=1 --iterations=100 > $(CSV_1)
	./lab2_add --threads=1 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=12 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=12 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=12 --iterations=100000 >> $(CSV_1)

	# lab2_add-1.png
	./lab2_add --threads=1 --iterations=10 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=20 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=40 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=80 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=20 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=40 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=80 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=20 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=40 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=80 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=20 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=40 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=80 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=20 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=40 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=80 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=12 --iterations=100000 --yield >> $(CSV_1)

	# lab3_add-3.png
	./lab2_add --threads=1 --iterations=10 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100000 >> $(CSV_1)

	# lab2_add-2.png
	./lab2_add --threads=1 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=1000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=1 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=2 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=4 --iterations=100000 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=1000 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --yield >> $(CSV_1)
	./lab2_add --threads=8 --iterations=100000 --yield >> $(CSV_1)

	# lab2_add-4.png
	./lab2_add --threads=2 --iterations=10000 --yield --sync=m >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --yield --sync=m >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --yield --sync=m >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> $(CSV_1)
	./lab2_add --threads=2 --iterations=1000 --yield --sync=s >> $(CSV_1)
	./lab2_add --threads=4 --iterations=1000 --yield --sync=s >> $(CSV_1)
	./lab2_add --threads=8 --iterations=1000 --yield --sync=s >> $(CSV_1)
	./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 --yield --sync=c >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --yield --sync=c >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --yield --sync=c >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> $(CSV_1)

	# lab2_add-5.png
	./lab2_add --threads=1 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 --sync=m >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 --sync=m >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --sync=m >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --sync=m >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 --sync=m >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 --sync=s >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 --sync=s >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --sync=s >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --sync=s >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 --sync=s >> $(CSV_1)
	./lab2_add --threads=1 --iterations=10000 --sync=c >> $(CSV_1)
	./lab2_add --threads=2 --iterations=10000 --sync=c >> $(CSV_1)
	./lab2_add --threads=4 --iterations=10000 --sync=c >> $(CSV_1)
	./lab2_add --threads=8 --iterations=10000 --sync=c >> $(CSV_1)
	./lab2_add --threads=12 --iterations=10000 --sync=c >> $(CSV_1)

tests-list: build-list
	# lab2_list-1.png
	./lab2_list --threads=1 --iterations=10 > $(CSV_2)
	./lab2_list --threads=1 --iterations=100 >> $(CSV_2)
	./lab2_list --threads=1 --iterations=1000 >> $(CSV_2)
	./lab2_list --threads=1 --iterations=10000 >> $(CSV_2)
	./lab2_list --threads=1 --iterations=20000 >> $(CSV_2)

	# lab2_list-2.png
	-./lab2_list --threads=2 --iterations=1 >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=10 >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=100 >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=1000 >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=1 >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=10 >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=100 >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=1000 >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=1 >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=10 >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=100 >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=1000 >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=1 >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=10 >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=100 >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=1000 >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=1 --yield=i >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=2 --yield=i >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=4 --yield=i >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=8 --yield=i >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=16 --yield=i >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=32 --yield=i >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=1 --yield=i >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=2 --yield=i >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=4 --yield=i >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=8 --yield=i >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=16 --yield=i >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=1 --yield=i >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=2 --yield=i >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=4 --yield=i >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=8 --yield=i >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=16 --yield=i >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=1 --yield=i >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=2 --yield=i >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=4 --yield=i >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=8 --yield=i >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=16 --yield=i >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=1 --yield=d >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=2 --yield=d >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=4 --yield=d >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=8 --yield=d >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=16 --yield=d >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=32 --yield=d >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=1 --yield=d >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=2 --yield=d >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=4 --yield=d >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=8 --yield=d >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=16 --yield=d >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=1 --yield=d >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=2 --yield=d >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=4 --yield=d >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=8 --yield=d >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=16 --yield=d >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=1 --yield=d >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=2 --yield=d >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=4 --yield=d >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=8 --yield=d >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=16 --yield=d >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=1 --yield=il >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=2 --yield=il >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=4 --yield=il >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=8 --yield=il >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=16 --yield=il >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=32 --yield=il >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=1 --yield=il >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=2 --yield=il >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=4 --yield=il >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=8 --yield=il >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=16 --yield=il >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=1 --yield=il >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=2 --yield=il >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=4 --yield=il >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=8 --yield=il >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=16 --yield=il >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=1 --yield=il >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=2 --yield=il >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=4 --yield=il >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=8 --yield=il >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=16 --yield=il >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=1 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=2 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=4 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=8 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=16 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=2 --iterations=32 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=1 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=2 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=4 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=8 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=4 --iterations=16 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=1 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=2 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=4 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=8 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=8 --iterations=16 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=1 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=2 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=4 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=8 --yield=dl >> $(CSV_2)
	-./lab2_list --threads=12 --iterations=16 --yield=dl >> $(CSV_2)

	# lab2_list-3.png
	./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> $(CSV_2)
	./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> $(CSV_2)

	# lab2_list-4.png
	./lab2_list --threads=1 --iterations=1000 >> $(CSV_2)
	./lab2_list --threads=1 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=2 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=4 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=8 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=12 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=16 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=24 --iterations=1000 --sync=m >> $(CSV_2)
	./lab2_list --threads=1 --iterations=1000 --sync=s >> $(CSV_2)
	./lab2_list --threads=2 --iterations=1000 --sync=s >> $(CSV_2)
	./lab2_list --threads=4 --iterations=1000 --sync=s >> $(CSV_2)
	./lab2_list --threads=8 --iterations=1000 --sync=s >> $(CSV_2)
	./lab2_list --threads=12 --iterations=1000 --sync=s >> $(CSV_2)
	./lab2_list --threads=16 --iterations=1000 --sync=s >> $(CSV_2)
	./lab2_list --threads=24 --iterations=1000 --sync=s >> $(CSV_2)

tests: build tests-add tests-list

graphs-add:
	gnuplot lab2_add.gp
graphs-list:
	gnuplot lab2_list.gp
graphs: graphs-add graphs-list

dist-nobuild:
	tar -czf $(TARBALL_NAME) $(SOURCES)
dist: build tests graphs dist-nobuild

untar:
	@tar -xf $(TARBALL_NAME)

transfer-nodist: dist-nobuild
	scp $(TARBALL_NAME) $(USER):CS111/$(LAB)$(SUBLAB)

transfer: dist transfer-nodist

transfer-script:
	@scp P2A_check.sh $(USER):CS111/$(LAB)$(SUBLAB)

transfer-make:
	@scp MakeFILE_1 $(USER):CS111/$(LAB)$(SUBLAB)