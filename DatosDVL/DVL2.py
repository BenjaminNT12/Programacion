import matplotlib.pyplot as plt
from matplotlib import cm

def leer_archivo(nombre_archivo):
    columnas = []
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
        for linea in lineas:
            columnas.append(linea.strip().split(','))
    return columnas

nombre_archivo = '/home/nicolas/Github/Programacion/DatosDVL/dvl7.txt'  # Reemplaza 'archivo.txt' con el nombre de tu archivo

datos = leer_archivo(nombre_archivo)

datosLimpios = []


for i in range(len(datos)):
    if datos[i][0] == '$DVPDL' and len(datos[i][:]) == 10:
        datosLimpios.append(datos[i])
  
columnaX = [columna[6] for columna in datosLimpios]
columnaY = [columna[7] for columna in datosLimpios]
columnaZ = [columna[8] for columna in datosLimpios]

carryX = []
carryY = []
carryZ = []

for i in range(len(columnaX)):
    columnaX[i] = float(columnaX[i])
    columnaY[i] = float(columnaY[i])
    columnaZ[i] = float(columnaZ[i])

    if i == 0:
        carryX.append(columnaX[i]) 
        carryY.append(columnaY[i]) 
        carryZ.append(columnaX[i]) 
    else:
        carryX.append(carryX[i-1] + columnaX[i])
        carryY.append(carryY[i-1] + columnaY[i])
        carryZ.append(carryZ[i-1] + columnaZ[i])


ax = plt.figure().add_subplot(projection='3d')

ax.plot(carryX, carryY, carryZ, label='DATOS DVL')
ax.set_xlim([0, 5])
ax.set_ylim([-2.5, 2.5])
ax.set_zlim([0, 5])
ax.set_xlabel("X Axis")
ax.set_ylabel("Y Axis")
ax.set_zlabel("Z Axis")
ax.legend()

plt.show()
