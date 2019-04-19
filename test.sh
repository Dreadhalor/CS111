LAB="lab1a"
README="README"
MAKEFILE="Makefile"

EXPECTED=""
SUFFIXES="c"
PGM="./lab1a"
PGMS="$PGM"
PTY_TEST=pty_test
LIBRARY_URL="www.cs.ucla.edu/classes/cs111/Software"

echo "... confirming cr->nl mapping on shell input"
./$PTY_TEST ./$PGM --shell > STDOUT 2> STDERR <<-EOF
	# we do this to confirm that the shell is running
	PAUSE 1
	EXPECT "/bin/bash\r\n"
	SEND "echo \$SHELL\r"
	WAIT 1

	SEND "exit\r"
	SEND "^D"
	CLOSE
EOF
RC=$?
if [ $RC -ne 0 ]; then
	let errors+=1
	echo "... FAIL"
fi