import matplotlib.pyplot as plt


def leer_archivo(nombre_archivo):
    columnas = []
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
        for linea in lineas:
            columnas.append(linea.strip().split(','))
    return columnas

nombre_archivo = r'C:\Users\LENOVO\github\Programacion\DatosDVL\data_dvl521_filtrada.txt'  # Reemplaza 'archivo.txt' con el nombre de tu archivo

datos = leer_archivo(nombre_archivo)

# Supongamos que tienes 3 columnas en tu archivo de texto
columna1 = [fila[0] for fila in datos]
columna2 = [fila[7] for fila in datos]
columna3 = [fila[8] for fila in datos]
columna4 = [fila[9] for fila in datos]

carryX = 0.0
carryY = 0.0 
carryZ = 0.0

for i in range(len(columna1)):
    columna1[i] = float(columna1[i])
    columna2[i] = float(columna2[i])
    columna3[i] = float(columna3[i])
    columna4[i] = float(columna4[i])

    carryX[i+1] = float(carryX[i]) + columna2[i]
    carryY[i+1] = float(carryY[i]) + columna3[i]
    carryZ[i+1] = float(carryZ[i]) + columna4[i]
    #print(columna2[i])

print("Columna 1:", columna1)
print("Columna 2:", columna2)
print("Columna 3:", columna3)
print("Columna 4:", columna4)

plt.plot(columna1, columna2)
plt.xlabel('Columna 1')
plt.ylabel('Columna 2')
plt.title('Gráfico de x')
plt.show()

plt.plot(columna1, columna3)
plt.xlabel('Columna 1')
plt.ylabel('Columna 3')
plt.title('Gráfico de y')
plt.show()

plt.plot(columna1, columna4)
plt.xlabel('Columna 1')
plt.ylabel('Columna 4')
plt.title('Gráfico de z')
plt.show()
