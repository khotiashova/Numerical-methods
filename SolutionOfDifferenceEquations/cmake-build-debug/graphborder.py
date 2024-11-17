import matplotlib.pyplot as plt
import sys

file_x = open("xoutput", "r")
x = [float(line) for line in file_x]

file_y = open("youtput", "r")
y = [float(line) for line in file_y]

s = 2;

plt.scatter(x, y, label = 'Solution', color = 'b', s = s)
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.savefig("graph2.png")

file_x.close()
file_y.close()
