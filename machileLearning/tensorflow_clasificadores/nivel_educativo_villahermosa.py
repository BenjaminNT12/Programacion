import matplotlib.pyplot as plt

# Diccionario con la distribución porcentual de los niveles de educación
niveles_educacion = {
    "Sin escolaridad": 4.9,
    "Educación básica": 49.3,
    "Educación media superior": 24.0,
    "Educación superior": 21.6,
    "No especificada": 0.2
}

# Crear la gráfica de barras horizontal
plt.figure(figsize=(10, 6))
bars = plt.barh(list(niveles_educacion.keys()), list(niveles_educacion.values()), color='deepskyblue')
plt.xlabel('Porcentaje', fontweight = 'bold')
plt.ylabel('Nivel de Educación', fontweight = 'bold')
plt.title('Distribución Porcentual de los Niveles de Educación \n en la cuidad de Villahermosa Tabasco\n Fuente INEGI Censo de población 2020.', fontweight = 'bold')

# Agregar los porcentajes al final de cada barra
i = 0
for bar in bars:
    width = bar.get_width()
    if i == 4:
        plt.text(width + 1,  # Posición en X
                bar.get_y() + bar.get_height() / 2,  # Posición en Y
                f'{width}%',  # Texto
                va='center')  # Alineación vertical
    else:
        plt.text(width - 4,  # Posición en X
                bar.get_y() + bar.get_height() / 2,  # Posición en Y
                f'{width}%',  # Texto
                va='center')  # Alineación vertical
    i += 1

plt.tight_layout()  # Ajustar el layout para que no se corten las etiquetas
plt.show()