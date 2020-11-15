set terminal png
set output "graph3.png"
set title "TCP Throughput 3 vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 2.25264
30 2.66897
40 2.81388
50 2.88348
60 2.92698
70 2.95477
80 2.9752
90 2.9901
100 3.00218
e
