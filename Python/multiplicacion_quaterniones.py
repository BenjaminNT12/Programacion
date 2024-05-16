import numpy as np
import quaternion

# Crear dos cuaterniones
q1 = np.quaternion(1, 1, 1, 1)
q2 = np.quaternion(0, 1, 0, 0)

# Multiplicar los cuaterniones
q_product = q1 * q2
r = np.array([0.25, 0, 0])

# Convert the vector to a quaternion
quaternion1 = np.quaternion(0, *r)
quaternion2 = quaternion1

q3 = q1 - quaternion2

print(f"abs(q3) = {abs(q2.w)}")

print(q3)
print(type(q3))

print(quaternion1)
print(type(quaternion1))
print(quaternion2)
print(type(quaternion2))

# Imprimir el resultado
print(q_product)
print(type(q_product))

tmp = np.zeros([4,])

print(tmp)
print(2*q1)