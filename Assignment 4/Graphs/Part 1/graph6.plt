set terminal png
set output "graph6.png"
set title "UDP Throughput 2 vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 19.0453
30 23.9944
40 28.8843
50 33.7568
60 38.6224
70 43.4868
80 47.4776
90 50.4289
100 52.6855
e
