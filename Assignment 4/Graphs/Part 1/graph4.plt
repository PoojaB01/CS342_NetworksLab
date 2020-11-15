set terminal png
set output "graph4.png"
set title "TCP Throughput 4 vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 0.0185547
30 0.0498651
40 0.12952
50 0.193807
60 0.241061
70 0.271597
80 0.289973
90 0.304386
100 0.312795
e
