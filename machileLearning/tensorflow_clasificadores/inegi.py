import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# Cargar datos del censo (ejemplo ficticio)
censo_data = pd.read_csv('/home/nicolas/Github/Programacion/machileLearning/tensorflow_clasificadores/ageb_mza_urbana_27_cpv2020_csv/ageb_mza_urbana_27_cpv2020/conjunto_de_datos/conjunto_de_datos_ageb_urbana_27_cpv2020.csv')

diccionario_de_datos = pd.read_csv('/home/nicolas/Github/Programacion/machileLearning/tensorflow_clasificadores/ageb_mza_urbana_27_cpv2020_csv/ageb_mza_urbana_27_cpv2020/diccionario_de_datos/diccionario_datos_ageb_urbana_27_cpv2020.csv')

cabecera_diccionario = diccionario_de_datos.iloc[3,:]
print(f"cabecera_diccionario: {cabecera_diccionario}")

print(diccionario_de_datos.head(100))

print(censo_data.head())

cabecera_datos = censo_data.columns.tolist()

# print(cabecera_datos)
# Población femenina :      POBFEM
# Población masculina :      POBMAS
# Población de 0 a 2 años :                 P_0A2
# Población femenina de 0 a 2 años :      P_0A2_F
# Población masculina de 0 a 2 años :      P_0A2_M
# Población femenina de 3 a 5 años :      P_3A5_F
# Población masculina de 3 a 5 años :      P_3A5_M
# Población de 6 a 11 años :                P_6A11
# Población femenina de 6 a 11 años :      P_6A11_F
# Población masculina de 6 a 11 años :      P_6A11_M
# Población de 8 a 14 años :                P_8A14
# Población femenina de 8 a 14 años :      P_8A14_F
# Población masculina de 8 a 14 años :      P_8A14_M
# Población de 12 a 14 años :               P_12A14
# Población femenina de 12 a 14 años :      P_12A14_F
# Población masculina de 12 a 14 años :      P_12A14_M

interest_list = ['P_0A2', 'P_0A2_F', 'P_0A2_M', 'P_3A5', 'P_3A5_F', 'P_3A5_M', 'P_6A11', 'P_6A11_F', 'P_6A11_M', 'P_8A14', 'P_8A14_F', 'P_8A14_M', 'P_12A14', 'P_12A14_F', 'P_12A14_M']
# interest_list = ['P_0A2_F', 'P_0A2_M', 'P_3A5_F', 'P_3A5_M', 'P_6A11_F', 'P_6A11_M', 'P_8A14_F', 'P_8A14_M', 'P_12A14_F', 'P_12A14_M']


# Población de 3 años y más :      P_3YMAS
# Población femenina de 3 años y más :      P_3YMAS_F
# Población masculina de 3 años y más :      P_3YMAS_M
# Población de 5 años y más :      P_5YMAS
# Población femenina de 5 años y más :      P_5YMAS_F
# Población masculina de 5 años y más :      P_5YMAS_M
# Población de 12 años y más :      P_12YMAS
# Población femenina de 12 años y más :      P_12YMAS_F
# Población masculina de 12 años y más :      P_12YMAS_M
# Población de 15 años y más :      P_15YMAS
# Población femenina de 15 años y más :      P_15YMAS_F
# Población masculina de 15 años y más :      P_15YMAS_M
# Población de 18 años y más :      P_18YMAS
# Población femenina de 18 años y más :      P_18YMAS_F
# Población masculina de 18 años y más :      P_18YMAS_M
# Población de 3 a 5 años :      P_3A5


# interest_list = ['P_0A2', 'P_0A2_F', 'P_0A2_M', 'P_3YMAS', 'P_3YMAS_F', 'P_3YMAS_M', 'P_5YMAS', 'P_5YMAS_F', 'P_5YMAS_M', 'P_12YMAS', 'P_12YMAS_F', 'P_12YMAS_M']
# interest_list = ['P_0A2', 'P_0A2_F', 'P_0A2_M', 'P_3YMAS', 'P_3YMAS_F', 'P_3YMAS_M', 'P_5YMAS', 'P_5YMAS_F']

contador = 0

personas_en_rango = {}

for index, row in censo_data.iterrows():
    if row['NOM_LOC'] == 'Total de la localidad urbana' and censo_data.iloc[index+3, 5] == 'Villahermosa':
        info_str = f"NOM_LOC: {row['NOM_LOC']}"
        for col in interest_list:
            info_str += f", {col}: {row[col]}"
            personas_en_rango[col] = int(row[col])
        info_str += f", contador: {contador}, index: {index}"
        # for i in range(index, index + 10):
        #         print('censo_data.iloc[i, 5]')
        print(info_str)
        contador += 1
        

print(personas_en_rango)

# # Suponiendo que personas_en_rango es un diccionario previamente definido
# categorias = list(personas_en_rango.keys())
# valores = list(personas_en_rango.values())

# # Número de grupos de categorías (hombre/mujer)
# n_grupos = len(categorias) // 3

# # Crear posiciones para cada grupo y un ancho para las barras
# posiciones = np.arange(n_grupos)
# ancho = 0.35  # Ancho de las barras

# # Separar valores en hombres y mujeres (asumiendo orden alternado)
# valores_hombres = valores[0::2]
# valores_mujeres = valores[1::2]

# # Crear las barras para hombres y mujeres
# barras_hombres = plt.bar(posiciones - ancho/2, valores_hombres, ancho, label='Hombres')
# barras_mujeres = plt.bar(posiciones + ancho/2, valores_mujeres, ancho, label='Mujeres')

# # Añadir títulos y etiquetas
# plt.title('Distribución de Personas por Rango de Edad y Género\n en la ciudad de Villahermosa Tabasco')
# plt.xlabel('Rango de Edad')
# plt.ylabel('Número de Personas')

# # Mejorar la presentación de las etiquetas del eje X
# # Asumiendo que las categorías para hombres y mujeres son las mismas y alternadas
# etiquetas_x = [categorias[i] for i in range(0, len(categorias), 2)]
# etiquetas_x = ['Niños de\n 0 a 2 años', 'Niños de\n 3 a 3 años', 'Niños de\n 6 a 11 años', 'Niños de\n 8 a 14 años', 'Niños de\n 12 a 14 años']
# plt.xticks(posiciones, etiquetas_x, rotation=0, ha="right")

# # Añadir leyenda
# plt.legend()

# plt.show()
# # print(cabecera_datos)
# # diccionario_de_datos = diccionario_de_datos.drop(diccionario_de_datos.index[0:2])
# # print(censo_data.head(100))

etiqueta_list = diccionario_de_datos.iloc[:, 3].tolist()
indicadores_list = diccionario_de_datos.iloc[:, 1].tolist()


for i in range(len(indicadores_list)):
    print(f"{indicadores_list[i]} :      {etiqueta_list[i]}")

# Suponiendo que personas_en_rango es un diccionario con tus datos
# Y que contiene valores para cada elemento en interest_list
categorias = ['0-2', '3-5', '6-11', '8-14', '12-14']  # Rangos de edad simplificados para el eje X
categorias = ['Niños de\n 0 a 2 años', 'Niños de\n 3 a 3 años', 'Niños de\n 6 a 11 años', 'Niños de\n 8 a 14 años', 'Niños de\n 12 a 14 años']
valores_totales = [personas_en_rango[cat] for cat in interest_list[0::3]]  # Valores totales
valores_hombres = [personas_en_rango[cat] for cat in interest_list[2::3]]  # Valores de hombres
valores_mujeres = [personas_en_rango[cat] for cat in interest_list[1::3]]  # Valores de mujeres

# Número de grupos de categorías
n_grupos = len(categorias)

# Crear posiciones para cada grupo y un ancho para las barras
posiciones = np.arange(n_grupos)
ancho = 0.2  # Ancho de las barras

# Crear las barras para totales, hombres y mujeres
barras_totales = plt.bar(posiciones - ancho, valores_totales, ancho, label='Total')
barras_hombres = plt.bar(posiciones, valores_hombres, ancho, label='Hombres')
barras_mujeres = plt.bar(posiciones + ancho, valores_mujeres, ancho, label='Mujeres')

# Añadir títulos y etiquetas
plt.title('Distribución de Personas por Rango de Edad y Género\n en la ciudad de Villahermosa Tabasco \n Fueten: INEGI Censo de poblacion 2020')
plt.xlabel('Rango de Edad')
plt.ylabel('Número de Personas')

# Mejorar la presentación de las etiquetas del eje X
plt.xticks(posiciones, categorias, rotation=45, ha="right")

# Añadir leyenda
plt.legend()

plt.show()

# localidad_list = ['Villahermosa']

# print(censo_data.head())
# municipios = []
# localidades = []

# # for i in range(len(interest_list)):
# #     for datos_clave in censo_data[interest_list[i]]:
# #         for localidad in censo_data['NOM_LOC']:
# #             if localidad in localidad_list:
# #                 print(localidad)

    
# # Asumiendo que censo_data es un DataFrame de pandas
# dato_P_0A2 = censo_data.loc[censo_data['NOM_LOC'].str.lower() == 'villahermosa', 'P_3YMAS'].values[0]
# print(f"dato_vph_spmvpi: {dato_P_0A2}")

# # print(censo_data.columns.drop('ENTIDAD'))
# print(censo_data.head('ENTIDAD',axis=1,inplace=True))
# # print(f"Localidad: {localidades}")

