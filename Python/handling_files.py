import time

f = open("/home/nicolas/Github/Programacion/Python/datos4error_ver2.txt", 'w')
data = f.write("4.37768 8.32163 0.4043273\n")
print(data)
f.close()

f2 = open("/home/nicolas/Github/Programacion/Python/datos4error_ver2.txt", 'r')
data_read = f2.read()
print(data_read)
f2.close()

try:
    f3 = open("/home/nicolas/Github/Programacion/Python/datos4error_ver2.txt", 'a')
    for i in range(1000):
        new_data = f3.write("4.37768 8.32163 0.4043273\n")
        print(new_data)
    f3.close()
except Exception as e:
    print(e)

f4 = open("/home/nicolas/Github/Programacion/Python/datos4error_ver2.txt", 'r')
data_read_append = f4.read()
print(data_read_append)
f4.close()

with open("/home/nicolas/Github/Programacion/Python/datos4error_ver4.txt", 'w') as f_datos_error:
    for i in range(1, 3003, 2):
        data_to_write = "{} : {} \n"
        data = f_datos_error.write(data_to_write.format(time.time(), i))
    print(data)

with open("/home/nicolas/Github/Programacion/Python/datos4error_ver4.txt", 'r') as f_datos_error_leidos:
    datos_leidos = f_datos_error_leidos.readline(12)
    print(datos_leidos)
    