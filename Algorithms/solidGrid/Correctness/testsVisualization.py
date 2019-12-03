import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

def loadFile(fileName):
    timeList = []
    totalTestsList = []
    correctTestsList = []
    with open(fileName) as file:
        line = file.readline()
        while line:
            s = line.split(' ')
            total = int(s[0])
            correct = int(s[1])            
            time = float(s[2])/1000000000.0


            totalTestsList.append(total)
            correctTestsList.append(correct)
            timeList.append(time)

            line = file.readline()
    return totalTestsList, correctTestsList, timeList

############################## Execution  ##################################
total,correct,time = loadFile('CorrectnessReport.txt')
############################################################################

print(total)
print(correct)
print(time)


x = []
for i in range(20,31):
    x.append(i)

f = interpolate.interp1d(x,time,kind='cubic',fill_value="extrapolate")

xInterp = np.arange(20,max(x)+1)
yInterp = f(xInterp)

plt.scatter(x,time,edgecolors='r')
algorithmLine, = plt.plot(xInterp,yInterp, label='Tester Execution Time')

plt.xlabel('Vertex Set Size', labelpad=7)
plt.ylabel('Execution Time (s)', labelpad=7)
plt.title('Implementation Test')
plt.legend(handles=[algorithmLine])
plt.savefig("correctnessTestTime.svg")
plt.show()