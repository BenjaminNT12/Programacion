import matplotlib.pyplot as plt
import numpy as np
import math

# Crear un array de valores de tiempo
_time = np.arange(0, 500, 0.1)  # 500 puntos de tiempo entre 0 y 10

# Calcular dephDesired para cada punto de tiempo
dephDesired = 0.4*(180/math.pi)*(0.4*np.sin(0.08*_time) + 1.2*np.cos(0.03*_time))+790

# Crear la gráfica
plt.figure()
plt.plot(_time, dephDesired)
plt.xlabel('Time')
plt.ylabel('Deph Desired')
plt.title('Deph Desired vs Time')
plt.grid(True)
plt.show()