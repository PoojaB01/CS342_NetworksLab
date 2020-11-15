set terminal png
set output "FairnessvBS.png"
set title "Fairness vs Buffer Size"
set xlabel "Buffer Size (no. of packets)"
set ylabel "Fairness"

set xrange [0:800]
plot "-"  title "Fairness Index" with linespoints
10 0.43459
25 0.59323
40 0.675638
55 0.695586
70 0.691589
85 0.696861
100 0.696344
200 0.695658
300 0.694993
400 0.694322
500 0.69364
600 0.692952
700 0.692257
800 0.691553
e
