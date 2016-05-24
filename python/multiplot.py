#
#  multiplot.py
#  

import sys
import os
import numpy as np
import matplotlib.pyplot as plt

# Read the file and convert each line into a double number
def read_line(file):
    with open(file) as f:
        for line in f:
            w=line.strip().split(' ')
            yield [float(i) for i in w]

def main(args):
    os.getcwd()
    n=(len(args)-1)
    mo, axarr = plt.subplots(n, sharex=True)
    count=0                                  
    
    for f in args:
        if('python/' in f):
            continue
        print 'plotting {} '.format(f)
        x=np.transpose(list(read_line(f)))
        axarr[count].plot(x[0],x[1])
        axarr[count].set_title(f)
        count+=1
    
    plt.show()

main(sys.argv)

