set terminal png
set output "graph5.png"
set title "UDP Throughput 1 vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 7.88853
30 8.42137
40 8.52897
50 8.57061
60 8.5664
70 8.56936
80 8.58048
90 8.59113
100 8.60025
e
