import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
import sklearn 
import pandas as pd
import keras
import tensorflow as tf
from sklearn.metrics import ConfusionMatrixDisplay, confusion_matrix
from sklearn.preprocessing import MinMaxScaler


# leer los datos del dataset
data_file = pd.read_csv("/home/nicolas/Github/Programacion/machileLearning/tensorflow_clasificadores/heart_attack/heart.csv")

# con data_file.head() te muestra los primeros 5 datos
# esto normalmente se realiza para poder visualizar
# las columnas y estar familiarizado con los datos
print(data_file.head())

#    age  sex  cp  trtbps  chol  fbs  restecg  thalachh  exng  oldpeak  slp  caa  thall  output
# 0   63    1   3     145   233    1        0       150     0      2.3    0    0      1       1
# 1   37    1   2     130   250    0        1       187     0      3.5    0    0      2       1
# 2   41    0   1     130   204    0        0       172     0      1.4    2    0      2       1
# 3   56    1   1     120   236    0        1       178     0      0.8    2    0      2       1
# 4   57    0   0     120   354    0        1       163     1      0.6    2    0      2       1

# Donde: 
# age       :Edad
#
# sex       :Sexo del paciente donde: 1 -> para hombre y 0 -> para mujer
#
# cp        :Chest pain type -> indica el nivel del dolor en el pecho del paciente
#
# trtbps    :Resting Blood Pressure: la presion de paciente en reposo(en mm de 
#            Hg(mercurio)), al entrar al hospital
#
# chol      :Colestero serico: colesterol del paciente en mg/dl
#
# fbs       :Fasting blood sugar: si el azucar del paciente en ayunas es mayor a 120 mg/dl
#            (1 = True, 0 = False)
#
# restecg   :Resting Electrocardiographic Results: representa los resultados del 
#            electrocardiograma con 1 como normal, o 0 como alguna anomalia 
#
# thalachh  :frecuencia cardiaca maxima alcanzada, por el paciente
#   
# exgn      :Excercise Induced Angina -> angina inducida por el ejercicio 1 = si, 0 = no
#   
# oldpeak   :ST Depression induced by exercise Relative to rest: 
#            La depresión del ST inducida por el ejercicio en relación con el reposo, 
#            una medida de la salud del corazó durante el ejercicio.
#   
# slp       :The Slope of the Peak Exercise ST Segment : La pendiente del segmento 
#            ST del ejercicio máximo, con valores que indican la naturaleza de la 
#            pendiente durante el ejercicio máximo.
#   
# caa       :Number of Major Vessels : el número de vasos principales (0-3) coloreados
#            mediante fluoroscopia.
#   
# thall     :Thalassemia : Un trastorno sanguíneo llamado talasemia, representado 
#            como 3 = normal; 6 = defecto fijo; 7 = defecto reversible. La codificación 
#            puede variar.
#   
# output    :salida : La variable objetivo que indica la presencia de enfermedad 
#            cardíaca (1) o ausencia (0).




print(type(data_file))

# data_file.columns.drop('output') el metodo .drop elimina la columna con el 
# nombre dado, y retorna una lista con el nombre de las columnas
numerical_columns = data_file.columns.drop('output') # elimna la columna "output"

print(numerical_columns) # imprime la lista que contiene el nombre de las columnas

