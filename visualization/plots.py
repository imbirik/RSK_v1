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
def x_trace(trace, N, step = 100, color = 'blue'):
    x = []
    it = 0
    tableau_size = N 
    for pair in trace:
        val = pair[0]
        size = pair[1]
        while(it < size):
            x.append(val/(2*np.sqrt(tableau_size)))
            #if x[-1] > 2:
                #x = x[:-1]
            tableau_size += step
            it += step
        it = it-size
    x = np.asarray(x)
    x_len = x.shape[0]
    plt.scatter(x=range(x_len),y=x, c=color, linewidths=0.01, alpha=0.01)