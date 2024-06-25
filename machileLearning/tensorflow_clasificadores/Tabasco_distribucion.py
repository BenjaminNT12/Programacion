import matplotlib.pyplot as plt

# Datos proporcionados
datos_poblacion = {
    2010: 757000,
    2021: 914000,
    2022: 929000,
    2023: 944000,
    2024: 958000
}

# Tasas de crecimiento proporcionadas
tasas_crecimiento = {
    2021: 1.78,
    2022: 1.64,
    2023: 1.61,
    2024: 1.48
}

# Calcular la población para los años entre 2010 y 2021
for year in range(2011, 2021):
    if year - 1 in datos_poblacion:
        datos_poblacion[year] = datos_poblacion[year - 1] * (1 + (tasas_crecimiento[2021] / 100))

# Ordenar los datos de población por año
datos_poblacion = dict(sorted(datos_poblacion.items()))

# Mostrar los datos de población
for año, pob in datos_poblacion.items():
    print(f"Año: {año}, Población: {pob}")

# Crear listas de años y poblaciones para graficar
años = list(datos_poblacion.keys())
poblaciones = list(datos_poblacion.values())

# Graficar el crecimiento poblacional
plt.figure(figsize=(10, 6))
plt.plot(años, poblaciones, marker='o', linestyle='-', color='deepskyblue')
plt.xlabel('Año', fontweight='bold')
plt.ylabel('Población', fontweight='bold')
plt.title('Crecimiento Poblacional de Villahermosa (Centro) (2010-2024)',fontweight='bold')
plt.grid(True)
plt.show()
