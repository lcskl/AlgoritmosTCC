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
f2 = interpolate.interp1d(x2,y2,kind='quadratic',fill_value="extrapolate")

xInterp_n2 = np.arange(0,max(x2))
yInterp_n2 = f2(xInterp_n2)
#############################################################################

#### O(n^2) Execution Time GuideLine #######################################
x3,y3 = loadTimeFile('complexityGuideOn3.txt')
f3 = interpolate.interp1d(x3,y3,kind='quadratic',fill_value="extrapolate")

m = -1
for i in np.arange(0,max(x),10):
    if( f3(i) > max(y) ):
        m = i
        break

xInterp_n3 = np.arange(0,m)
yInterp_n3 = f3(xInterp_n3)
#############################################################################


plt.scatter(x, y, edgecolors='r')
plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))

algorithmLine, = plt.plot(xInterp,yInterp, label='Algorithm')
guide_On2, = plt.plot(xInterp_n2,yInterp_n2, label='Guide Curve $O(n^2)$')
guide_On3, = plt.plot(xInterp_n3, yInterp_n3, label='Guide Curve $O(n^3)$')

plt.xlabel('Vertex Set Size', labelpad=7)
plt.ylabel('Execution Time (s)', labelpad=7)
plt.title('Complexity Test')
plt.legend(handles=[algorithmLine,guide_On2,guide_On3])
plt.savefig("complexity.svg")
plt.show()
