from random import random
import sys
import subprocess
import numpy as np
from scipy.misc import imsave
import matplotlib.pyplot as plt

def output2array():
    array = np.genfromtxt("output.txt")
    array += 128.0
    plt.bar(np.arange(1024*1024), array.flatten())
    plt.show()
    return array

def output2image(width, height, gain, octaves, hgrid):
    gainer = lambda: str(float(gain) * random())
    subprocess.call(["./perlgen", width, height, gainer(), octaves, hgrid])
    r = output2array()
    subprocess.call(["./perlgen", width, height, gainer(), octaves, hgrid])
    g = output2array()
    subprocess.call(["./perlgen", width, height, gainer(), octaves, hgrid])
    b = output2array()
    color = np.dstack((r, g, b))
    imsave("output.png", color)
    #print(color)

if __name__ == "__main__":
    if len(sys.argv) == 6:
        output2image(*sys.argv[1:])
    else:
        print("Usage:\nperl2png.py [, <width>, <height>, <gain>, <octaves>, <hgrid>]")
