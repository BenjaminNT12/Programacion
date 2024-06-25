import matplotlib.pyplot as plt

# Diccionario con los datos de población
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

# Acceder a la población de Villahermosa
poblacion_villahermosa = datos_poblacion["Centro (Villahermosa)"]
print(f"Población de Villahermosa: {poblacion_villahermosa} habitantes")

# Crear la gráfica
plt.figure(figsize=(10, 8))
plt.bar(datos_poblacion.keys(), datos_poblacion.values(), color='dodgerblue')
plt.xlabel('Municipios')
plt.ylabel('Población')
plt.title('Población por Municipio en Tabasco')
plt.xticks(rotation=90)  # Rotar los nombres de los municipios para que se vean mejor
plt.tight_layout()  # Ajustar el layout para que no se corten las etiquetas
plt.show()
