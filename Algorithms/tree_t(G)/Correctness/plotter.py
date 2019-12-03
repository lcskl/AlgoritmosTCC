import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

def loadFile(fileName):
    totalList = []
    correctList = []
    with open(fileName) as file:
        line = file.readline()
        while line:
            s = line.split(' ')
            print(s)
            total = int(s[1])
            correct = int(s[2])            
            v = int(s[0])

            totalList.append(total)
            correctList.append(correct)

            line = file.readline()
    return totalList, correctList

############################## Execution  ##################################
total,correct = loadFile('testReport.txt')
############################################################################

print(total)
print(correct)

labels = []
for i in range(5,24):
    labels.append(str(i))

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


autolabel(rects1,2)

fig.tight_layout()
plt.ylim(top=650)
plt.savefig("correctness.svg")
plt.show()