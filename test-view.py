'''
tiny script for plotting the image at some index for the output HD5 file
'''
import matplotlib.pyplot as plt
import h5py as h5
import numpy as np
import sys

if len(sys.argv) != 3:
	print("USAGE: test-view.py <filename> <data index>")
	exit()

f=h5.File(sys.argv[1],'r')

img = np.array(f['images'][int(sys.argv[2])])

plt.matshow(img)
plt.show()
