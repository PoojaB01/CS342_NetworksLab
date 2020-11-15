# NS-3 NETWORK STIMULATOR FOR APPLICATION-4 

GROUP-67 COMPUTER NETWORKS LAB

Creators:
  * Pooja Gajendra Bhagat, Department: CSE, Roll number: 180101057
  * Saurabh Baranwal, Department: CSE, Roll number: 180101072

The first tep is to install NS-3. That can be done through this site: https://www.nsnam.org/
Further, the following tutorial can be used to understand how it works: https://www.nsnam.org/docs/release/3.31/tutorial/ns-3-tutorial.pdf

### Running the Code

Copy the file NetworkA4.cc inside the 'scratch' folder of ns3
Run the following command just outside the scratch folder in the Linux terminal:

```bash
$ ./waf --run scratch/NetworkA4
```

The above command will generate .plt files for all graphs. To obtain the image file of respective graph (in .png format), run the following command from outside the 'scratch' folder:

```bash
$ gnuplot <filename>
```
Do the above command for every .plt file to obtain the respective graph in .png format.

We generate the following graphs in each part of the assignment:

Part A (when UDP-2 rate is changed):
  * TCP Throughput vs UDP-2 Rate
  * TCP Throughput of individual TCP Connections vs UDP-2 Rate
  * UDP Throughput vs UDP-2 Rate
  * UDP Throughput of individual UDP Connections vs UDP-2 Rate
  
Part B (when Buffer size is changed):
  * Fairness index vs Buffer Size
  * TCP Throughput vs Buffer Size
  * UDP Throughput vs Buffer Size
  
Finally we have also made a report analysing our observations and implications from this Assignment by considering all graphs. The report is named as: G67_report.pdf
  


