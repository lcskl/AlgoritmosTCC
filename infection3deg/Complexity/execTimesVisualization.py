import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

def loadTimeFile(fileName):
    timeList = []
    verticesList = []
    with open(fileName) as file:
        line = file.readline()
        while line:
            s1, s2 = line.split(' ')
            n = int(s1)
            time = float(s2)
            verticesList.append(n)
            timeList.append(time)

            line = file.readline()
    return verticesList, timeList

#### Execution Data and Interpolation ######################################
x,y = loadTimeFile('complexityExecTimes.txt')
f = interpolate.interp1d(x,y,kind='quadratic',fill_value="extrapolate")

xInterp = np.arange(0,max(x))
yInterp = f(xInterp)

############################################################################

#### O(n^2) Execution Time GuideLine #######################################
x2,y2 = loadTimeFile('complexityGuideOn2.txt')
f = interpolate.interp1d(x,y,kind='quadratic',fill_value="extrapolate")

xInterp = np.arange(0,max(x))
yInterp = f(xInterp)
#############################################################################


plt.scatter(x, y, edgecolors='r')
plt.plot(x2,y2,'r-')
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))
plt.plot(xInterp,yInterp)
plt.xlabel('Vertex Set Size')
plt.ylabel('Execution Time (s)')
plt.title('Complexity Test')
plt.show()
