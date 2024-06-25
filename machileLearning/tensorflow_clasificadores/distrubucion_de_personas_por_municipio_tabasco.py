import matplotlib.pyplot as plt

# Diccionario con la distribución porcentual de la población
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

# Crear la gráfica de pastel
plt.figure(figsize=(10, 8))
plt.pie(distribucion_poblacion.values(), labels=distribucion_poblacion.keys(), autopct='%1.1f%%', startangle=140)
plt.title('Distribución Porcentual de la Población por Municipio en Tabasco', fontweight='bold')
plt.axis('equal')  # Asegura que el pie chart sea un círculo
plt.show()
