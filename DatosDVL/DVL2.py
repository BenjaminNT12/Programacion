import matplotlib.pyplot as plt
from matplotlib import cm

def leer_archivo(nombre_archivo):
    columnas = []
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
        for linea in lineas:
            columnas.append(linea.strip().split(','))
    return columnas


nombre_archivo = '/home/nicolas/Github/Programacion/DatosDVL/datosdvl.txt'  # Reemplaza 'archivo.txt' con el nombre de tu archivo
# nombre_archivo2 = '/home/nicolas/Github/Programacion/DatosDVL/datosdvl.txt'  # Reemplaza 'archivo.txt' con el nombre de tu archivo

datos = leer_archivo(nombre_archivo)
# datos2 = leer_archivo(nombre_archivo2)

# columna1 = [columna[0] for columna in datos]
columna2 = [columna[6] for columna in datos]
columna3 = [columna[7] for columna in datos]
columna4 = [columna[8] for columna in datos]

carryX = []
carryY = []
carryZ = []

for i in range(len(columna2)):
    # columna1[i] = float(columna1[i])
    columna2[i] = float(columna2[i])
    columna3[i] = float(columna3[i])
    columna4[i] = float(columna4[i])

    if i == 0:
        carryX.append(columna2[i]) 
        carryY.append(columna3[i]) 
        carryZ.append(columna4[i]) 
    else:
        carryX.append(carryX[i-1] + columna2[i])
        carryY.append(carryY[i-1] + columna3[i])
        carryZ.append(carryZ[i-1] + columna4[i])

ax = plt.figure().add_subplot(projection='3d')

ax.plot(carryX, carryY, carryZ, label='DATOS DVL')
ax.set_xlabel("X Axis")
ax.set_ylabel("Y Axis")
ax.set_zlabel("Z Axis")
ax.legend()

plt.show()

# 