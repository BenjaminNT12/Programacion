import numpy as np
import matplotlib.pyplot as plt

x_train = np.array([0., 1, 2, 3, 4, 5])
y_train = np.array([0, 0, 0, 1, 1, 1])

x_train2 = np.array([[0.5, 1.5], 
                     [1  ,   1], 
                     [1.5, 0.5], 
                     [3  , 0.5], 
                     [2  ,   2], 
                     [1  , 2.5]])

y_train2 = np.array([0, 0, 0, 1, 1, 1])

fig, ax = plt.scatter(1, 2)

pos = x_train == 0
neg = y_train == 1

ax[0].scatter(x_train[:], y_train[])



