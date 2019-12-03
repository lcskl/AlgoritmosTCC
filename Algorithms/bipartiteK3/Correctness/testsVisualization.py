import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

def loadTimeFile(fileName):
    size = []
    totalList = []
    correctList = []
    with open(fileName) as file:
        line = file.readline()
        while line:
            s1, s2, s3 = line.split(' ')
            s = int(s1)
            t = int(s2)
            c = int(s3)
            totalList.append(t)
            correctList.append(c)
            size.append(s)

            line = file.readline()
    return size,totalList, correctList

############################## Execution  ##################################
size,total,correct = loadTimeFile('CorrectnessReport.txt')
############################################################################

labels = []
for x in range(10,30):
    labels.append(str(x))

x = np.arange(len(labels))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2 , total, width, label='Total Tests', color='b')
rects2 = ax.bar(x + width/2 , correct, width, label='Correct Responses', color='g')



# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Tests')
ax.set_title('Correctness Tests')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()

plt.ylim(top=25)

def autolabel(rects,offsetX):
    """Attach a text label above each bar in *rects*, displaying its height."""
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(offsetX, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')


autolabel(rects1,2)


fig.tight_layout()
plt.savefig("correctness.svg")
plt.show()



