import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

def loadTimeFile(fileName):
    totalList = []
    correctList = []
    with open(fileName) as file:
        line = file.readline()
        while line:
            s1, s2 = line.split(' ')
            t = int(s1)
            c = int(s2)
            totalList.append(t)
            correctList.append(c)

            line = file.readline()
    return totalList, correctList

############################## Execution  ##################################
total,correct = loadTimeFile('correctnessReport.txt')
############################################################################

labels = ['G1', 'G2', 'G3', 'G4', 'G5','G6']

x = np.arange(len(labels))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, total, width, label='Total Tests', color='b')
rects2 = ax.bar(x + width/2, correct, width, label='Correct Responses', color='g')

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Tests')
ax.set_title('Correctness Tests')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()


def autolabel(rects,offsetX):
    """Attach a text label above each bar in *rects*, displaying its height."""
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(offsetX, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')


autolabel(rects1,-2)
autolabel(rects2,2)

fig.tight_layout()
plt.savefig("correctness.svg")
plt.show()



