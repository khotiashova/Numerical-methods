import matplotlib.pyplot as plt
import sys

if int(sys.argv[1]) == 1:
    # точки сетки
    file_x = open("xoutput", "r")
    x = [float(line) for line in file_x]
    #значение Рунге-Кутта 2 порядка
    file_y1 = open("y1output", "r")
    y1 = [float(line) for line in file_y1]
    #значение Рунге-Кутта 4 порядка    
    file_y2 = open("y2output", "r")
    y2 = [float(line) for line in file_y2]
    
    s = 2;
    
    plt.scatter(x, y1, label = '2 accuracy', color = 'b', s = s)
    plt.scatter(x, y2, label = '4 accuracy', color = 'g', s = s)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.savefig("graph1.png")
    
    file_x.close()
    file_y1.close()
    file_y2.close()

if int(sys.argv[1]) == 2:

    file_x = open("xoutput", "r")
    x = [float(line) for line in file_x]
    
    file_u = open("uoutput", "r")
    u = [float(line) for line in file_u]
    
    file_v = open("voutput", "r")
    v = [float(line) for line in file_v]
    
    s = 2;
    
    plt.scatter(x, u, label = 'u', color = 'b', s = s)
    plt.scatter(x, v, label = 'v', color = 'g', s = s)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.savefig("graph.png")
    
    file_x.close()
    file_u.close()
    file_v.close()
