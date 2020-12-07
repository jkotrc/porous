import matplotlib.pyplot as plt
import h5py as h5
import numpy as np
from sys import argv

f=h5.File("out_test.h5",'r')

img = np.array(f['images'][int(argv[1])])

plt.matshow(img)
plt.show()