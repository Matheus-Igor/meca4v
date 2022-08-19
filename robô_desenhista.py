import pandas as pd
import csv
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation
from IPython import display

ratio = plt.gca()
ratio.set_aspect(1)
url = 'https://raw.githubusercontent.com/Matheus-Igor/meca4v/main/pontos.csv'
df = pd.read_csv(url)
print(df)

x = df.X
y = df.Y

plt.plot(x, y)
plt.show()

fig = plt.figure()
traco, = plt.plot([],[],'-')
plt.xlim(-12,0)
plt.ylim(3,10)
def animate(frame_num):
    
    traco.set_data(x[:frame_num + 1], y[:frame_num + 1]) 
    return traco
ani = FuncAnimation(fig, animate, frames=448, interval=20)

video = ani.to_html5_video()
html = display.HTML(video)
display.display(html)
plt.close()
