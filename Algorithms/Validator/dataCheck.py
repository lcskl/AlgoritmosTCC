import out
import numpy as np
from matplotlib import pyplot as plt 
from scipy import interpolate

x1 = np.squeeze(np.asarray(out.dataN2[:, 0]))
y1 = np.squeeze(np.asarray(out.dataN2[:, 1]))

f1 = interpolate.interp1d(x1,y1)

xN2 = np.arange(x1[0],out.data[out.data.shape[0]-1,0] ,1)
yN2 = f1(xN2)

print(out.data.shape[0],out.data.shape[1])

plt.plot(out.data[:, 0],out.data[:, 1],'.',xN2,yN2,'-')
plt.legend()
plt.show()
