import matplotlib.pyplot as plt
import matplotlib.patches
import numpy as np
#import ffmpeg
import json
import os
import matplotlib.animation as animation
#import imagemagick
import ffmpeg
import anim
def speed_plot(elem_trace, step = 1):
    x = np.asarray(elem_trace[0])
    y = np.asarray(elem_trace[1])
    scale = np.asarray(elem_trace[2])
    scale = 2*np.sqrt(scale)
    x = x/scale
    y = y/scale
    size = x.shape[0]
    plot = []
    for i in range(1, size//step):
        pos = i*step
        dist = x[pos]
        plot.append(dist)
    plt.scatter(range(size//step-1),plot)
    plt.show()
def tableau_line_plot(tableau, row, accuracy=1000):
    height = len(tableau)
    step = height//row
    for i in range(height//step):
        data = tableau[i*step]
        plt.plot(data, label=str(i*row))
    #plt.hist(data,bins=accuracy)
    plt.legend()
    plt.show()
     