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

months = ['january', 'february', 'march', 'april', 'may', 'june', 
          'july', 'august', 'september', 'october', 'november', 'december']

print(months[-2])

list_of_random_things = [1, 3.4, 'a string', True]

print(type(list_of_random_things[3]))


print(months[len(months)-1])


half_months_of_year = months[6:11]
print(half_months_of_year)

# uso de memberships operators
# in --> evalua si existe un elemento en nuestra lista
# not in --> evalua si no existe un elemento en nuestra lista


print('this' in 'this is a string')
print('in' in 'this is a strings')
print('isa' in 'this is a strings')

print(5 not in [1, 2, 3, 4, 6])
print(5 in [1, 2, 3, 4, 6])

VINIX = ['C', 'MA', 'BA', 'PG', 'CSCO', 'VZ', 'PFE', 'HD', 'INTC', 'T', 'V', 
         'UNH', 'WFC', 'CVX', 'BAC', 'JNJ', 'GOOGL', 'GOOG', 'BRK.B', 'XOM', 
         'JPM', 'FB', 'AMZN', 'MSFT', 'AAPL']

print(VINIX[4])

print('GOOGL' in VINIX)

# mutability and order

my_list = [1, 2, 3, 4, 5]
print(my_list)
my_list[0] = 'String'
print(my_list)

try:
    greeting = "Hello there"
    greeting[0] = 'm'
except:
    print("Error: un string no permite index assigment, por lo que es inmutable")

# para cambiar un string es posible hacerlo de la siguiente manera
print(greeting)
greeting = "Hello Emily"
print(greeting)
# tanto listras como strings son "ordered", lo que quiere decir que es posible
# acceder a sus elementos
print(greeting[6])

# LIST's 
# list methods 
# en los list metods son funciones que funcionan con las listas
# por lo que el argumento de los list methods son la lista en si
grades = ["B", "A", "C", "D" , "B", "A"]
print(f"grades: {grades}")
scores = grades ## esta asignacion funciona similar a un puntero en c++
print(f"scores: {scores}")

grades[1] = "E"
print(f"grades: {grades}")
print(f"scores: {scores}")

list1 = [23, 4, 2, 234, 12, 665, 23, 45, 23, 634, 56, 23, 89]
print(list1)
print(max(list1))
print(sorted(list1))
print(min(list1))

list2 = [2 ,3 ,5 ,2, 23 , 23]
print(f"list2: {list2}")
list3 = list2*2
list4 = [list2[i]*2.3 for i in range(len(list2))]
print(f"list3: {list4}")
print(f"list3: {list3}")
print(f"list3: {list3 + list2}")

print(f"list3.pop(0): {list3.pop(0)}")
print(f"list3: {list3}")

# list methods "str".join
nautical_directions = "\n".join(["fore", "aft", "starboard", "port"])
print(f"nautical_directions: {nautical_directions}")


name = "-".join(["Garcia", "O'Kelly", "Davis"])
print(f"name: {name}")

# list methods "str".append(x)

letters = ["a", "b", "c", "d", "e", "f"]
print(f"letters: {letters}")
letters.append("g")
print(f"letters: {letters}")

names = ["Carol", "Albert", "Ben", "Donna"]
print(sorted(names))
print(names[2:4])

words = ["a", "b", "c", "d", "e", "f", "g"]

# slicing el primer indice es inclusivo pero el 
# ultimo es exclusivo
print(words[2:6])
print(words[:3])
print(words[4:])


location = (23.45125, 124.123562394)
print(f"location: {location}")
print(f"location(type): {type(location)}")

# las tuplas es posible definirlas con parentesis y 
# sin parentesis 

location2 = 23.45125, 12.123562394
sorted_location2 = sorted(location2)

print(f"location2: {location2}")
print(f"location2(type): {type(location2)}")
print(f"sorted(location2): {sorted_location2}")


# unpacking de una tupla

lattiude, longitude = location2

print(f"lattiude, longitude: {lattiude}, {longitude}")
print(f"locations2 : {location2[1]}")

# SET's (conjuntos) es una coleccion de elementos unicos, no pueden estar repetidos 
# los conjuntos no estan ordenados y son mutables


numbers = [99, 100, 1, 3, 4, 99, 100]
unique_numbers = set(numbers)
print(unique_numbers)
print(f"unique_numbers(type): {type(unique_numbers)}")

unique_numbers_list = list(unique_numbers)
print(unique_numbers_list)
print(f"unique_numbers_list(type): {type(unique_numbers_list)}")

fruit = {"apple", "banana", "orange", "grapefruit"}
print(fruit)
fruit.add("melon")
print(fruit)

if "apple" in fruit:
    print("si esta")

# remover un elemento con pop

fruit.pop()
print(fruit)


import time

# Sample data
set1 = set(range(1000))
set2 = set(range(500, 1500))
list1 = list(set1)
list2 = list(set2)

print(set1)
# print(set2)


union_sets = set1.union(set2)
print(f"len(union_sets): {len(union_sets)}")

intersection_sets = set1.intersection(set2)
print(f"len(intersection_sets): {len(intersection_sets)}")

diference_sets = set1.difference(set2)
print(f"len(diference_sets): {len(diference_sets)}")
print(diference_sets)


# Union
start_time = time.time()
union_set = set1.union(set2)
print("Set Union Time:", time.time() - start_time)

start_time = time.time()
union_list = list(set(list1 + list2))
print("List Union Time:", time.time() - start_time)

# Intersection
start_time = time.time()
intersection_set = set1.intersection(set2)
print("Set Intersection Time:", time.time() - start_time)

start_time = time.time()
intersection_list = [x for x in list1 if x in set2]
print("List Intersection Time:", time.time() - start_time)

# Difference
start_time = time.time()
difference_set = set1.difference(set2)
print("Set Difference Time:", time.time() - start_time)

start_time = time.time()
difference_list = [x for x in list1 if x not in set2]
print("List Difference Time:", time.time() - start_time)

# Dictionaries and Identity Operators

elements_dic = {"hidrogeno": 1, "Helio": 2, "lithium":3  }
print(f"elements_dic: {elements_dic}")
print(f"elements_dic(type): {type(elements_dic)}")

random_dict = {"abc": 1, 5: "hello"}

print(f"elements_dic[\'hidrogeno\']: {elements_dic['hidrogeno']}")
print(f"elements_dic.get(\'hidrogeno\'): {elements_dic.get('hidrogeno')}")

elements_dic['berilium'] = 4
print(f"elements_dic: {elements_dic}")

if 'berilium' in elements_dic:
    print(f"elements_dic.get(berilum): {elements_dic.get('berilium')}")
    print(f"'berilium' in elements_dic : {'berilium' in elements_dic}")

get_element = elements_dic.get('dilithium')

print(elements_dic.get('dilithium'))
if get_element is None:
    print("no esta el elemento dilithium")

# es mejor emplear el uso del metodo get(), que de los corchetes
# cuadrados

## mini prueba

a = [1, 2, 3]
b = a
c = [1, 2, 3]

print(a == b)
print(a is b)
print(c == b)
print(c is b)

# == se utiliza para comparar si 2 objetos son iguales
# 'is' se emplea para saber si dos obetos son examentamente
# iguales en memoria

population = {'Shanghai': 17.8,
              'Istanbul': 13.3,
              'Karachi': 13.0,
              'Mumbai': 12.5}

print(f"population: {population}")

animals = {'dogs': [20, 10, 15, 8, 32, 15], 
           'cats': [3,4,2,8,2,4], 
           'rabbits': [2, 3, 3], 
           'fish': [0.3, 0.5, 0.8, 0.3, 1],
           'dogs': [1.3, 0.5, 0.8, 0.3, 1]}
print(f"animals: {animals}")

print(f"animals.get(\'dogs\'): {animals.get('dogs')}")

animals['horses'] = [1, 3, 5, 2, 6]
animals['cow'] = 1

print(f"animals[cow]: {animals['cow']} ")
print(f"type(animals[cow]): {type(animals['cow'])} ")

print(f"animals.get(\'horses\'): {animals.get('horses')}")
print(f"animals[\'dogs\'][0]: {animals['dogs'][0]}")
print(f"animals: {animals}")

VINIX =  {'C': 0.74, 'MA': 0.78, 'BA': 0.79, 'PG': 0.85, 
          'CSCO': 0.88, 'VZ': 0.9, 'PFE': 0.92, 'HD': 0.97, 
          'INTC': 1.0, 'T': 1.01, 'V': 1.02, 'UNH': 1.02, 
          'WFC': 1.05, 'CVX': 1.05, 'BAC': 1.15, 'JNJ': 1.41, 
          'GOOGL': 1.46, 'GOOG': 1.47, 'BRK.B': 1.5, 
          'XOM': 1.52, 'JPM': 1.53, 'FB': 2.02, 'AMZN': 2.96, 
          'MSFT': 3.28, 'AAPL': 3.94}

print(VINIX)
VINIX['C'] = [VINIX['C']]
VINIX['C'].append(-6.51)
print(VINIX['C'])

# Compound Data Structures

print(elements_dic)

helium_dic = {"number": 2, "weight": 4.0062602, "symbol": 'He'}

print(helium_dic)
elements_dic["Helio"] = helium_dic

print(f"elements_dic: {elements_dic}")

elements_dic_2 = {"Hidrogeno": {"number": 1, "peso": 1.002, "simbolo": "H"},
                  "Helio": {"number": 2, "peso": 4.0502, "simbolo": "He"},
                  "berilio": {"number": 3, "peso": 3.0502, "simbolo": "be"}}

print(f"elements_dic_2: {elements_dic_2}")
print(f"elements_dic_2['Helio']['simbolo']: {elements_dic_2['Helio']['simbolo']}")

boro_dic = {"number": 4, "peso": 2.3502, "simbolo": "br"}

elements_dic_2['Boro'] = boro_dic
print(f"elements_dic_2: {elements_dic_2}")

student_records = {
    'John': {
        'age': 20,
        'major': 'Computer Science',
        'grades': [85, 90, 92]
    },
    'Emma': {
        'age': 19,
        'major': 'Mathematics',
        'grades': [95, 88, 91]
    }
}

print(student_records)

student_records['Benjamin Sebastian Nicolas Martinez'] = {'Age': 1, 
                                                          'major': "Computer science",
                                                          'grades': [100, 100, 100]}

student_records['Benjamin Sebastian Nicolas Martinez']['grades'].append(100)
print(student_records)



# quiz

verse = "if you can keep your head when all about you are losing theirs and blaming it on you   if you can trust yourself when all men doubt you     but make allowance for their doubting too   if you can wait and not be tired by waiting      or being lied about  don’t deal in lies   or being hated  don’t give way to hating      and yet don’t look too good  nor talk too wise"
print(verse, '\n')

# TODO: replace None with appropriate code
# split verse into list of words
verse_list = verse.split()
print(verse_list, '\n')

# TODO: replace None with appropriate code
# convert list to a data structure that stores unique elements
verse_set = set(verse_list)
print(verse_set, '\n')

# TODO: replace None with appropriate code
# find the number of unique words
num_unique = len(verse_set)
print(num_unique, '\n')

### Notebook grading
correct_answer = 51
if type(verse_list) != list:
    print("`verse_list` should be a list of all words in `verse`.")
elif type(verse_set) != set:
    print("`verse_set` should be a set of all unique words in `verse_list`")
elif type(num_unique) != int:
    print("Make sure you define `num_unique` with the number of unique words!")
elif num_unique != correct_answer:
    print("Not quite! Are you finding the length of the set correctly?")
else:
    print("Nice job! You can see my solution in the next page.")



verse_dict =  {'if': 3, 'you': 6, 'can': 3, 'keep': 1, 
               'your': 1, 'head': 1, 'when': 2, 'all': 2, 
               'about': 2, 'are': 1, 'losing': 1, 'theirs': 1, 
               'and': 3, 'blaming': 1, 'it': 1, 'on': 1, 
               'trust': 1, 'yourself': 1, 'men': 1, 'doubt': 1, 
               'but': 1, 'make': 1, 'allowance': 1, 'for': 1, 
               'their': 1, 'doubting': 1, 'too': 3, 'wait': 1, 
               'not': 1, 'be': 1, 'tired': 1, 'by': 1, 'waiting': 1, 
               'or': 2, 'being': 2, 'lied': 1, 'don\'t': 3, 
               'deal': 1, 'in': 1, 'lies': 1, 'hated': 1, 'give': 1, 
               'way': 1, 'to': 1, 'hating': 1, 'yet': 1, 'look': 1, 
               'good': 1, 'nor': 1, 'talk': 1, 'wise': 1}
print(verse_dict, '\n')


# find number of unique keys in the dictionary
num_keys = len(verse_dict)
print(f"unique keys in the dictionary: {num_keys}")

# find whether 'breathe' is a key in the dictionary
contains_breathe = 'breathe' in verse_dict 
print(f"\'breathe\' is a key in the dictionary: {contains_breathe}")


# create and sort a list of the dictionary's keys
# sorted_keys = sorted(list(verse_dict))
## create and sort a list of the dictionary's keys
sorted_keys = [k for k, v in sorted(verse_dict.items(), key=lambda item: item[1])]
print(sorted_keys)
print(sorted_keys[0])
print(sorted_keys[-1])

# max_value = 0
# max_value_key = 0
# for key, value in verse_dict.items():
#     if value > max_value:
#         max_value = value
#         max_value_key = key
# print(max_value_key ,max_value)
