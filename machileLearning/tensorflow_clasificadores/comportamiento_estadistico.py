import matplotlib.pyplot as plt
import numpy as np

# Datos de población por municipio
datos_poblacion = {
    "Balancán": 58524,
    "Cárdenas": 243229,
    "Centla": 107731,
    "Centro (Villahermosa)": 683607,
    "Comalcalco": 214877,
    "Cunduacán": 137257,
    "Emiliano Zapata": 32181,
    "Huimanguillo": 190885,
    "Jalapa": 37749,
    "Jalpa de Méndez": 91185,
    "Jonuta": 30798,
    "Macuspana": 158601,
    "Nacajuca": 150300,
    "Paraíso": 96741,
    "Tacotalpa": 47905,
    "Teapa": 58718,
    "Tenosique": 62310
}

# Distribución porcentual de la población por municipio
distribucion_poblacion = {
    "Balancán": 2.44,
    "Cárdenas": 10.12,
    "Centla": 4.48,
    "Centro (Villahermosa)": 28.45,
    "Comalcalco": 8.94,
    "Cunduacán": 5.71,
    "Emiliano Zapata": 1.34,
    "Huimanguillo": 7.95,
    "Jalapa": 1.57,
    "Jalpa de Méndez": 3.79,
    "Jonuta": 1.26,
    "Macuspana": 6.60,
    "Nacajuca": 6.25,
    "Paraíso": 4.02,
    "Tacotalpa": 1.99,
    "Teapa": 2.44,
    "Tenosique": 2.59
}

# Distribución porcentual de los niveles de educación
niveles_educacion = {
    "Sin escolaridad": 4.9,
    "Educación básica": 49.3,
    "Educación media superior": 24.0,
    "Educación superior": 21.6,
    "No especificada": 0.2
}

# Análisis estadístico de la población por municipio
total_poblacion = sum(datos_poblacion.values())
media_poblacion = np.mean(list(datos_poblacion.values()))
mediana_poblacion = np.median(list(datos_poblacion.values()))
desviacion_estandar_poblacion = np.std(list(datos_poblacion.values()))

print(f"Total de la población: {total_poblacion}")
print(f"Media de la población por municipio: {media_poblacion}")
print(f"Mediana de la población por municipio: {mediana_poblacion}")
print(f"Desviación estándar de la población por municipio: {desviacion_estandar_poblacion}")

# Gráfica de barras de la población por municipio
plt.figure(figsize=(12, 8))
plt.bar(datos_poblacion.keys(), datos_poblacion.values(), color='skyblue')
plt.xlabel('Municipios')
plt.ylabel('Población')
plt.title('Población por Municipio en Tabasco')
plt.xticks(rotation=90)
plt.tight_layout()
plt.show()

# Gráfica de pastel de la distribución porcentual de la población por municipio
plt.figure(figsize=(10, 8))
plt.pie(distribucion_poblacion.values(), labels=distribucion_poblacion.keys(), autopct='%1.1f%%', startangle=140)
plt.title('Distribución Porcentual de la Población por Municipio en Tabasco')
plt.axis('equal')
plt.show()

# Gráfica de barras horizontal de los niveles de educación
plt.figure(figsize=(10, 6))
plt.barh(list(niveles_educacion.keys()), list(niveles_educacion.values()), color='deepskyblue')
plt.xlabel('Porcentaje')
plt.ylabel('Nivel de Educación')
plt.title('Distribución Porcentual de los Niveles de Educación')
plt.tight_layout()
plt.show()
