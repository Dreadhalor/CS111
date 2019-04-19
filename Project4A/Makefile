#NAME: Scott Hetrick
#EMAIL: Scotthetrick2@yahoo.com
#ID: 404491101

.SILENT:

SOURCES = my_beaglebone.jpg connected.png copy.png build_run.png git.png Makefile README
ID = 404491101
LAB = lab4
SUBLAB = a
TARBALL_NAME = $(LAB)$(SUBLAB)-$(ID).tar.gz

default:
	tar -czf $(TARBALL_NAME) $(SOURCES)

transfer:
	@make && scp $(LAB)$(SUBLAB)-$(ID).tar.gz hetrick@lnxsrv.seas.ucla.edu:CS111/$(LAB)$(SUBLAB)

transfer-script:
	@scp P4A_check.sh hetrick@lnxsrv.seas.ucla.edu:CS111/$(LAB)$(SUBLAB)