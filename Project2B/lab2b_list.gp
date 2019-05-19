#! /usr/bin/gnuplot
# input: lab2b_list.csv
#	1. test name
#	2. # threads
#	3. # iterations per thread
#	4. # lists
#	5. # operations performed (threads x iterations x (ins + lookup + delete))
#	6. run time (ns)
#	7. run time per operation (ns)
#   8. wait-lock time
#
# output:
# 	1. lab2b_1.png: throughput(total number of operations per second) for Mutex and Spin-lock
#   2. lab2b_2.png: wait-for-lock and average time per operation vs Threads
#   3. lab2b_3.png: Unprotected/protected Threads and Iterations that run without failure
#   4. lab2b_4.png: Throughput vs Threads (sync=m)
#   5. lab2b_5.png: Throughput vs Threads (sync=s)

# general plot parameters
set terminal png
set datafile separator ","

# throughput(total number of operations per second) for Mutex and Spin-lock
set title "1: Throughput vs Threads"
set xlabel "Threads"
set logscale x 10
set ylabel "Throughput (operations / ns)"
set logscale y 10
set output 'lab2b_1.png'

plot \
     "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title 'spinlock' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title 'mutex' with linespoints lc rgb 'green'

# wait-for-lock time and average time per operation vs thread num
set title "2: wait-for-lock and average time per operation vs Threads"
set xlabel "Threads"
set logscale x 2
set ylabel "time"
set logscale y 10
set output 'lab2b_2.png'

plot \
"< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($7) \
title 'avg time per operation(ns)' with linespoints lc rgb 'red', \
"< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($8) \
title 'wait-for-lock time(ns)' with linespoints lc rgb 'green'

# Unprotected and protected threads and iterations
set title "3: Unprotected/protected Threads and Iterations that run without failure"
set xlabel "Threads"
set logscale x 2
set xrange [0.75:]
set ylabel "Successful Iterations"
set logscale y 10
set output 'lab2b_3.png'
# note that unsuccessful runs should have produced no output
plot \
"< grep -e 'list-id-none,[0-9]*,[0-9]*,4' lab2b_list.csv" using ($2):($3) \
title 'no sync' with points lc rgb 'green', \
"< grep -e 'list-id-s,[0-9]*,[0-9]*,4' lab2b_list.csv" using ($2):($3) \
title 'sync=s' with points lc rgb 'red', \
"< grep -e 'list-id-m,[0-9]*,[0-9]*,4' lab2b_list.csv" using ($2):($3) \
title 'sync=m' with points lc rgb 'violet', \

# Sublist aggregated throughput vs number of threads

set title "4: Throughput vs Threads (sync=m)"
set xlabel "Threads"
set logscale x 2
set ylabel "Throughput (operations / ns)"
set logscale y 10
set output 'lab2b_4.png'

plot \
    "< grep -e 'list-none-m,[0-9]*,1000,1' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=1' with linespoints lc rgb 'red', \
    "< grep -e 'list-none-m,[0-9]*,1000,4' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=4' with linespoints lc rgb 'green', \
    "< grep -e 'list-none-m,[0-9]*,1000,8' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=8' with linespoints lc rgb 'blue', \
    "< grep -e 'list-none-m,[0-9]*,1000,16' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=16' with linespoints lc rgb 'violet', \


# Sublist aggregated throughput vs number of threads

set title "5: Throughput vs Threads (sync=s)"
set xlabel "Threads"
set logscale x 2
set ylabel "Throughput (operations / ns)"
set logscale y 10
set output 'lab2b_5.png'

plot \
    "< grep -e 'list-none-s,[0-9]*,1000,1' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=1' with linespoints lc rgb 'red', \
    "< grep -e 'list-none-s,[0-9]*,1000,4' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=4' with linespoints lc rgb 'green', \
    "< grep -e 'list-none-s,[0-9]*,1000,8' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=8' with linespoints lc rgb 'blue', \
    "< grep -e 'list-none-s,[0-9]*,1000,16' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=16' with linespoints lc rgb 'violet'