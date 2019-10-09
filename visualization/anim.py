import matplotlib.pyplot as plt
import matplotlib.patches
import numpy as np
#import ffmpeg
import json
import os
import matplotlib.animation as animation
#import imagemagick
import ffmpeg


def read_tabluax(filename, Q_tabluax = False):
    with open(filename, 'r') as f:
        tabluaxes = json.loads(f.read())
    return tabluaxes

def read_traces(filename):
    with open(filename, 'r') as f:
        traces = json.loads(f.read())
    return traces

def read_elem_trace(filename):
    with open(filename, 'r') as f:
        elem_trace = json.loads(f.read())
    return elem_trace
 
def read_json(filename):
    with open(filename, 'r') as f:
        data = json.loads(f.read())
    return data
# def draw_PQ(tableaux, i, fig, ax, Q_tableau=False, show=True):
#     P = tabluax[i][0]
#     Q = tabluax[i][1]
#     if Q_tableau:
#         draw(P, fig=fig, ax=ax)
#         draw(Q, fig=fig, ax=ax, shift=len(P[0])+1)
#     else:
#         draw(P, fig=fig, ax=ax)
#     if show:
#       plt.show()

class BumpingTraceAnimation:


    def __init__(self, trace, ):
        self.x_trace = []
        self.y_trace = []
        self.fig = plt.figure()
        self.ax = plt.axes(xlim=(-1, 1), ylim=(0, 1))
        self.line, = self.ax.plot([], [], lw=1)
        self.ax.plot([0,1],[0,1], color='black', lw=1)
        self.ax.plot([-1,0],[1,0], color='black', lw=1)
        for i in range(len(trace[0])):
            x = trace[0][i]
            y = trace[1][i]
            scale = trace[2][i]
            scale = 2*np.sqrt(scale)
            x = x/scale
            y = y/scale
            x_rotated = x/np.sqrt(2) - y/np.sqrt(2)
            y_rotated = x/np.sqrt(2) + y/np.sqrt(2)
            self.x_trace.append(x_rotated)
            self.y_trace.append(y_rotated)
        self.dots_number = len(self.x_trace)

    def animate(self, i):
        print(i)
        self.line.set_data(self.x_trace[: 100*i], self.y_trace[: 100*i])

        return self.line,
    
    def create_animation(self):
        anim = animation.FuncAnimation(self.fig, self.animate, frames=self.dots_number//100, interval=5)
        anim.save(r'C:\Users\zaryd\source\repos\RSK_C++\trace_anim.gif', writer='ffmpeg')

class YoungAnimation:
    
    def __init__(self, tabluax, traces, size):
        self.tabluax = tabluax
        self.traces = traces
        self.size = size
        self.fig = plt.figure()
        self.ax = plt.axes(xlim=(0, self.size), ylim=(0, self.size))
    def draw(self, tableau, shift=0):
        y_shape = len(tableau)
        x_shape = len(tableau[0])
        rgb = np.zeros([y_shape, x_shape, 3])
        for i in range(len(tableau)):
            for j in range(len(tableau[i])):
                rgb[i][j][0] = 255/255
                rgb[i][j][1] = 0/255
                rgb[i][j][2] = 0/255
        for i in range(len(tableau)):
            for j in range(len(tableau[i])):
                text = ''#tableau[i][j]
                self.ax.text(j+shift+0.5, i+0.5, text, fontsize=20, ha="center", va="center")
                rectangle = matplotlib.patches.Rectangle((j+shift, i), color=rgb[i][j], alpha=0.2, width=1, height=1)
                self.ax.add_patch(rectangle)
    def add_trace(self, trace, shift=0):
        for i in range(len(trace)):
            rectangle = matplotlib.patches.Rectangle((trace[i]+shift, i), color='black', alpha=0.2, width=1, height=1)
            self.ax.add_patch(rectangle)
    def animate(self,i):
        print(i)
        self.ax.clear()
        self.ax.set_xlim(0,self.size)
        self.ax.set_ylim(0,self.size)
        self.draw(self.tabluax[i][0])
        self.add_trace(self.traces[i])

    def create_animation(self):
        anim = animation.FuncAnimation(self.fig, self.animate, frames=len(tabluax), interval = 1000)
        anim.save(r'C:\Users\zaryd\source\repos\RSK_C++\myanim.gif', writer='ffmpeg')
        print('Done')