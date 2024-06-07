# string.title()  --> para poner en mayusculas la primera letra de cada palabra
# string.islower() --> para saber si una cadena esta en minusculas
# string.count('string objetive') --> para contar el numero de veces que aparece el string objetive en el string

# string methods --> https://www.w3schools.com/python/python_ref_string.asp
# len("string") --> retorna la longitud de la cadena
# type(12) --> retorna el tipo de dato
# print("Helo") --> imprime en consola

# ejemplo: 
my_string = "sebastian thrun"

# my_string.capitalize() --> Sebastian Thrun -- > pone en mayuscula la primera letra
# my_string.casefold() --> sebastian thrun --> convierte la cadena a minusculas
# my_string.center(20) --> "  sebastian thrun   " --> centra la cadena en 20 caracteres
# my_string.count("a") --> 2 --> cuenta el numero de veces que aparece la letra a
# my_string.encode() --> b'sebastian thrun' --> codifica la cadena
# my_string.endswith("n") --> True --> retorna True si la cadena termina con la letra n
# my_string.expandtabs(2) --> "sebastian thrun" --> expande los tabs
# my_string.find("t") --> 3 --> retorna la posicion de la primera ocurrencia de la letra t
# my_string.format() --> "sebastian thrun" --> formatea la cadena
# my_string.format_map() --> "sebastian thrun" --> formatea la cadena
# my_string.index("t") --> 3 --> retorna la posicion de la primera ocurrencia de la letra t
# my_string.isalnum() --> False --> retorna True si la cadena contiene solo letras y numeros
# my_string.isalpha() # --> False --> retorna True si la cadena contiene solo letras
# my_string.isdecimal() --> False --> retorna True si la cadena contiene solo numeros
# my_string.isdigit() --> False --> retorna True si la cadena contiene solo digitos
# my_string.isidentifier() --> False --> retorna True si la cadena es un identificador valido
# my_string.islower() --> True --> retorna True si la cadena esta en minusculas
# my_string.isnumeric() --> False --> retorna True si la cadena contiene solo caracteres numericos
# my_string.isprintable() --> True --> retorna True si todos los caracteres de la cadena son imprimibles
# my_string.isspace() --> False --> retorna True si la cadena contiene solo espacios en blanco
# my_string.istitle() --> False --> retorna True si la cadena sigue el formato de titulo
# my_string.isupper() --> False --> retorna True si la cadena esta en mayusculas
# my_string.join("t") --> "tsebastian thrun" --> une los elementos de la cadena con el string objetivo
# my_string.ljust(20) --> "sebastian thrun    " --> justifica la cadena a la izquierda

print(my_string.index("t"))

print("Hola este es un mensaje de prueba con el numero {} de {} digitos".format(35,2))

mensaje_prueba = "Hola este es un mensaje de prueba con el numero {} de {} digitos".format(35,2)

print(mensaje_prueba)

mensaje_prueba_2 = "Hola este es un mensaje de prueba con el numero {} de {} digitos"

print(mensaje_prueba_2.format(35,2))


animal = "dog" 
action = "bite" 
number = 25 
print("Does your {} {} plus a number {}?".format(animal, action, number))


new_string = "Hola como, estas hoy es 5 de junio de 2024"
split_string = new_string.split(maxsplit=1)
print(split_string)
print(type(split_string))

verse = "If you can keep your head when all about you\n  Are losing theirs and blaming it on you,\nIf you can trust yourself when all men doubt you,\n  But make allowance for their doubting too;\nIf you can wait and not be tired by waiting,\n  Or being lied about, don’t deal in lies,\nOr being hated, don’t give way to hating,\n  And yet don’t look too good, nor talk too wise:"
print(len(verse))
print(verse.find('and'))
print(verse.rfind('you'))
print(verse.count('you'))

# Understanding Common Error Messages

greeting = "hello"
print(greeting.upper())
