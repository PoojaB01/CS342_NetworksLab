set terminal png
set output "TCPTPvRate.png"
set title "TCP Throughput vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 4.54143
30 5.43905
40 5.88872
50 6.15955
60 6.3361
70 6.44757
80 6.4532
90 6.46256
100 6.46111
e
