set terminal png
set output "graph1.png"
set title "TCP Throughput 1 vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 2.25101
30 2.66961
40 2.81489
50 2.88425
60 2.92368
70 2.94667
80 2.89541
90 2.86187
100 2.83111
e
