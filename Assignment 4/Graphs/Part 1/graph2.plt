set terminal png
set output "graph2.png"
set title "TCP Throughput 2 vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 0.0192368
30 0.0506035
40 0.130418
50 0.19801
60 0.244388
70 0.274533
80 0.292621
90 0.306196
100 0.315032
e
