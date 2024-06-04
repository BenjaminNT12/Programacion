import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
import matplotlib as plt
import matplotlib.pyplot as plt


x_tst = 0.1*np.arange(1,3,1).reshape(2,)  # (1 examples, 2 features)
W_tst = 0.1*np.arange(1,7,1).reshape(2,3) # (2 input features, 3 output features)
b_tst = 0.1*np.arange(1,4,1).reshape(3,)  # (3 features)
# A_tst = my_dense(x_tst, W_tst, b_tst, sigmoid)

print(f"x_tst: {x_tst}")
print(f"W_tst: {W_tst}")
print(f"b_tst: {b_tst}")
