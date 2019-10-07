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
import plots
tabluax = anim.read_tabluax(r'C:\Users\zaryd\source\repos\RSK_C++\tabluax.txt')  
plots.tableau_line_plot(tabluax[0][0],10,100)

#traces = read_traces(r'C:\Users\zaryd\source\repos\RSK_C++\traces.txt')
elem_trace = anim.read_elem_trace(r'C:\Users\zaryd\source\repos\RSK_C++\elem_traces.txt')
#plots.speed_plot(100)
#myanim = anim.BumpingTraceAnimation(elem_trace)
#myanim.create_animation()
print(1)
#my_creater = YoungAnimation(tabluax, traces, 66)
#my_creater.create_animation()

print(2)