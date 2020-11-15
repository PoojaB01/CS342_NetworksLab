set terminal png
set output "TCPTPvBS.png"
set title "TCP Throughput vs Buffer Size"
set xlabel "Buffer Size (no. of packets)"
set ylabel "Throughput (Mbps)"

set xrange [0:800]
plot "-"  title "Throughput" with linespoints
10 6.64084
25 15.8744
40 25.3551
55 34.2485
70 42.2186
85 42.5705
100 42.5664
200 42.8503
300 43.1234
400 43.3966
500 43.6696
600 43.9427
700 44.2158
800 44.4889
e
