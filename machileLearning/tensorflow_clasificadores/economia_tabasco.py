import matplotlib.pyplot as plt
import numpy as np

# Datos del diccionario
economia = {
    'Pobreza moderada': [['2010 año', 243000, 33.4], ['2015 año', 206000, 26.9], ['2020 año', 247000, 30.8]],
    'Extrema pobreza': [['2010 año', 38600, 5.3], ['2015 año', 26100, 3.42], ['2020 año', 58000, 7.24]],
    'Vulnerables por \ncarencias sociales': [['2010 año', 230000, 31.4], ['2015 año', 362000, 47.4], ['2020 año', 279000, 34.8]],
    'Vulnerables por \ningresos': [['2010 año', 45800, 6.28], ['2015 año', 26000, 3.41], ['2020 año', 45500, 5.69]],
    'No vulnerable': [['2010 año', 172000, 23.6], ['2015 año', 144000, 18.9], ['2020 año', 172000, 21.4]]
}

# Extraer datos para cada tipo de pobreza
tipos_pobreza = list(economia.keys())
años = ['2010', '2015', '2020']

# Preparar los datos para graficar
valores = {}
for tipo in tipos_pobreza:
    datos = economia[tipo]
    valores[tipo] = [dato[1] for dato in datos]

# Configurar la figura y ejes
fig, ax = plt.subplots(figsize=(10, 6))

# Definir el ancho de las barras
bar_width = 0.2

# Definir posición de las barras
posiciones = np.arange(len(tipos_pobreza))

# Graficar las barras para cada año
for i, año in enumerate(años):
    pos = [pos + i * bar_width for pos in posiciones]
    valores_año = [valores[tipo][i] for tipo in tipos_pobreza]
    ax.bar(pos, valores_año, bar_width, label=año)

# Añadir etiquetas, título y leyenda
ax.set_xlabel('Tipo de pobreza', fontweight='bold')
ax.set_ylabel('Número de personas', fontweight='bold')
ax.set_title('Evolución de la pobreza por tipo \n en la cuidad de Villahermosa Tabasco\n Fuente: INEGI 2020', fontweight='bold')
ax.set_xticks([p + 1.5 * bar_width for p in posiciones])
ax.set_xticklabels(tipos_pobreza)
ax.legend()

# Mostrar la gráfica
plt.tight_layout()
plt.show()
