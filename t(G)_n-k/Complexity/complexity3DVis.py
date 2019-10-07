from matplotlib import pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D

def loadTimeFile(fileName):
    timeList = []
    verticesList = []
    kList = []
    with open(fileName) as file:
        line = file.readline()
        while line:
            s1, s2, s3 = line.split(' ')
            n = int(s1)
            k = int(s2)
            time = float(s3)
            verticesList.append(n)
            kList.append(k)
            timeList.append(time)

            line = file.readline()
    return verticesList, kList, timeList


x,y,z = loadTimeFile('test.txt')

fig = plt.figure()
ax = Axes3D(fig)

ax.scatter(x,y,z)
plt.show()
