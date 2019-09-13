import matplotlib.pyplot as plt
import matplotlib.patches
import numpy as np
import json
import os


def read(filename, Q_tabluax = False):
    with open(filename, 'r') as f:
        young = json.loads(f.read())
    fig, ax = plt.subplots()
    if Q_tabluax:
        draw(young[0], fig=fig, ax=ax)
        draw(young[1], fig=fig, ax=ax, shift=len(young[0][0])+1)
    else:
        draw(young, fig=fig, ax=ax)
    plt.show()


def draw(tabluax, fig, ax, shift=0,):
    y_shape = len(tabluax)
    x_shape = len(tabluax[0])
    rgb = np.zeros([y_shape, x_shape, 3])
    for i in range(len(tabluax)):
        for j in range(len(tabluax[i])):
            rgb[i][j][0] = 255/255
            rgb[i][j][1] = 0/255
            rgb[i][j][2] = 0/255
    for i in range(len(tabluax)):
        for j in range(len(tabluax[i])):
            text = ax.text(j+shift+0.5, i+0.5, tabluax[i][j], fontsize=20, ha="center", va="center")
            frame = matplotlib.patches.Rectangle((j+shift, i), color=rgb[i][j], alpha=0.2, width=1, height=1)
            ax.add_patch(frame)
    plt.xlim(left=0, right=x_shape+1+shift)
    plt.ylim(bottom=0, top=y_shape+1)


read('young.txt', Q_tabluax=True)
