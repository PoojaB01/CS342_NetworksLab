set terminal png
set output "UDPTPvRate.png"
set title "UDP Throughput vs UDP Rate"
set xlabel "UDP Rate (Mbps)"
set ylabel "Throughput (Mbps)"

set xrange [10:100]
plot "-"  title "Throughput" with linespoints
20 26.9338
30 32.4158
40 37.4133
50 42.3274
60 47.1888
70 52.0561
80 56.0581
90 59.0201
100 61.2857
e
