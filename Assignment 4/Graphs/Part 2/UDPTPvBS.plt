set terminal png
set output "UDPTPvBS.png"
set title "UDP Throughput vs Buffer Size"
set xlabel "Buffer Size (no. of packets)"
set ylabel "Throughput (Mbps)"

set xrange [0:800]
plot "-"  title "Throughput" with linespoints
10 27.9754
25 27.571
40 27.6045
55 27.5242
70 27.5205
85 27.4916
100 27.5319
200 27.5184
300 27.5184
400 27.5184
500 27.5184
600 27.5184
700 27.5184
800 27.5184
e
