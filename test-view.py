import matplotlib.pyplot as plt
import h5py as h5
import numpy as np
from sys import argv

f=h5.File(argv[1],'r')

img = np.array(f['images'][int(argv[2])])

plt.matshow(img)
plt.show()
