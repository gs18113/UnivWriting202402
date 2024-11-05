import matplotlib.pyplot as plt
import numpy as np

# read output.csv and plot the data
with open('output.csv', 'r') as f:
    data = f.read()

data = data.strip().split('\n')
y = [row.split(',')[0] for row in data]
x = [row.split(',')[1] for row in data]

# plot y-x graph, with x ticks [0, 1] and y ticks [0, 100]

fig, ax = plt.subplots()
ax.set_xticks([0.0, 1.0], [0.0, 1.0]) 
ax.set_yticks([0.0, 100.0]) 
ax.plot(x, y)
plt.show()
