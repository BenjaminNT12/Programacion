import time

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

names = ["Joey Tribbiani", "Monica Geller", "Chandler Bing", "Phoebe Buffay"]
usernames = [name.replace(' ','_') for name in names]
print(usernames)


items = ['first string', 'second string']
html_str = "<ul>\n"          # The "\n" here is the end-of-line char, causing
                             # chars after this in html_str to be on next line

for item in items:
    html_str += "<li>{}</li>\n".format(item)
html_str += "</ul>"

print(html_str)

print(list(range(0, -5)))


book_title =  ['great', 'expectations','the', 'adventures', 'of', 'sherlock','holmes','the','great','gasby','hamlet','adventures','of','huckleberry','fin']

word_counter = {}

for word in book_title: 
    if word not in word_counter: 
        word_counter[word] = 1
    else:
        word_counter[word] += 1

print(word_counter)

word_counter2 = {}

for word in book_title:
    word_counter2[word] = word_counter2.get(word, 0) + 1
    # donde el argumento del metodo get es primero la palabra y
    # despues el valor que se desea retornar si la busqueda
    # no se localizas
print(word_counter2)

cast = {
           "Jerry Seinfeld": "Jerry Seinfeld",
           "Julia Louis-Dreyfus": "Elaine Benes",
           "Jason Alexander": "George Costanza",
           "Michael Richards": "Cosmo Kramer"
       }


# con el metodo items accedes a cada elemento del diccionario
for key, value in cast.items():
    print(f"key: {key}, value: {value}")


start_num = 5 #provide some start number, replace 5 with a number you choose
end_num = 1230#provide some end number that you stop when you hit, replace 100 with a number you choose
count_by = 3 #provide some number to count by, replace 2 with a number you choose 

# write a while loop that uses break_num as the ongoing number to 
break_num = start_num
while break_num <= end_num:
    break_num += count_by

print(f"break_num: {break_num}")

# check against end_num
x = count_by - ((end_num - start_num) % count_by) + end_num
print(f"x: {x}")
break_num = 5 #replace None with appropriate code

### Notebook grading

def get_solution(start_num, end_num, count_by):
    break_num = start_num
    while break_num < end_num:
        break_num += count_by
    
    return break_num

correct = get_solution(start_num, end_num, count_by)
print(f"correct: {correct}")

print(f"break_num == correct: {break_num == correct}")

if break_num == correct:
    print("Good job!")
else:
    print("Oops! It doesn't look like the expected answer.")

num_to_check = 90
prime = False

start = time.time()
for num in range(2, int(num_to_check**0.5)+1):
    if (num_to_check % num) == 0.0:
        prime = False
        break

if prime is True:
    print(f"{num_to_check} is prime number")
else:
    print(f"{num_to_check} is NOT a prime number, because {num} is a factor of {num_to_check}")

end = time.time()
print(f"Time: {end - start}")
    

# Use zip to transpose data from a 4-by-3 matrix to a 3-by-4 matrix. 
# There's actually a cool trick for this! Feel free to look at the 
# solutions if you can't figure it out.

data = ((0, 1, 2), (3, 4, 5), (6, 7, 8), (9, 10, 11))
# data_transpose = None # replace with your code
data = ((0, 1, 2), (3, 4, 5), (6, 7, 8), (9, 10, 11))

# Transponer la matriz a 3x4 usando zip y el operador de desempaquetado *
transposed_data = tuple(zip(*data))

print(transposed_data)

list1 = [3, 4, 1, 5, 2, 5, 8, 12, 1, 5]

list1 = [str(element) if element % 2 == 0 else element*2 for element in sorted(list1)]
print(list1)


# Crear una lista con las ciudades más importantes en minúsculas
important_cities = ["nueva york", "londres", "tokio", "parís", "berlín", "madrid", "sídney", "moscú", "pekin", "dubái"]
print(important_cities)

important_cities_uppercase = [city.capitalize() for city in sorted(important_cities, reverse=True) if city == "londres"]
print(important_cities_uppercase)


square_list = [x**2 for x in range(35) if x%2 == 0]
print(square_list)


scores = {
             "Rick Sanchez": 70,
             "Morty Smith": 35,
             "Summer Smith": 82,
             "Jerry Smith": 23,
             "Beth Smith": 98
          }

passed = [name for name, score in scores.items() if score >= 65] # write your list comprehension here
print(passed)

print(f"Rick Sanchez: {scores.get('Rick Sanchez')}")

### Notebook grading
correct_answer = ['Rick Sanchez', 'Summer Smith', 'Beth Smith']

if passed == correct_answer:
    print("Good job!")
else:
    print("Not quite! Did you use the corresponding score to filter each name?")















nominated = {1931: ['Norman Taurog', 'Wesley Ruggles', 'Clarence Brown', 'Lewis Milestone', 'Josef Von Sternberg'], 1932: ['Frank Borzage', 'King Vidor', 'Josef Von Sternberg'], 1933: ['Frank Lloyd', 'Frank Capra', 'George Cukor'], 1934: ['Frank Capra', 'Victor Schertzinger', 'W. S. Van Dyke'], 1935: ['John Ford', 'Michael Curtiz', 'Henry Hathaway', 'Frank Lloyd'], 1936: ['Frank Capra', 'William Wyler', 'Robert Z. Leonard', 'Gregory La Cava', 'W. S. Van Dyke'], 1937: ['Leo McCarey', 'Sidney Franklin', 'William Dieterle', 'Gregory La Cava', 'William Wellman'], 1938: ['Frank Capra', 'Michael Curtiz', 'Norman Taurog', 'King Vidor', 'Michael Curtiz'], 1939: ['Sam Wood', 'Frank Capra', 'John Ford', 'William Wyler', 'Victor Fleming'], 1940: ['John Ford', 'Sam Wood', 'William Wyler', 'George Cukor', 'Alfred Hitchcock'], 1941: ['John Ford', 'Orson Welles', 'Alexander Hall', 'William Wyler', 'Howard Hawks'], 1942: ['Sam Wood', 'Mervyn LeRoy', 'John Farrow', 'Michael Curtiz', 'William Wyler'], 1943: ['Michael Curtiz', 'Ernst Lubitsch', 'Clarence Brown', 'George Stevens', 'Henry King'], 1944: ['Leo McCarey', 'Billy Wilder', 'Otto Preminger', 'Alfred Hitchcock', 'Henry King'], 1945: ['Billy Wilder', 'Leo McCarey', 'Clarence Brown', 'Jean Renoir', 'Alfred Hitchcock'], 1946: ['David Lean', 'Frank Capra', 'Robert Siodmak', 'Clarence Brown', 'William Wyler'], 1947: ['Elia Kazan', 'Henry Koster', 'Edward Dmytryk', 'George Cukor', 'David Lean'], 1948: ['John Huston', 'Laurence Olivier', 'Jean Negulesco', 'Fred Zinnemann', 'Anatole Litvak'], 1949: ['Joseph L. Mankiewicz', 'Robert Rossen', 'William A. Wellman', 'Carol Reed', 'William Wyler'], 1950: ['Joseph L. Mankiewicz', 'John Huston', 'George Cukor', 'Billy Wilder', 'Carol Reed'], 1951: ['George Stevens', 'John Huston', 'Vincente Minnelli', 'William Wyler', 'Elia Kazan'], 1952: ['John Ford', 'Joseph L. Mankiewicz', 'Cecil B. DeMille', 'Fred Zinnemann', 'John Huston'], 1953: ['Fred Zinnemann', 'Charles Walters', 'William Wyler', 'George Stevens', 'Billy Wilder'], 1954: ['Elia Kazan', 'George Seaton', 'William Wellman', 'Alfred Hitchcock', 'Billy Wilder'], 1955: ['Delbert Mann', 'John Sturges', 'Elia Kazan', 'Joshua Logan', 'David Lean'], 1956: ['George Stevens', 'Michael Anderson', 'William Wyler', 'Walter Lang', 'King Vidor'], 1957: ['David Lean', 'Mark Robson', 'Joshua Logan', 'Sidney Lumet', 'Billy Wilder'], 1958: ['Richard Brooks', 'Stanley Kramer', 'Robert Wise', 'Mark Robson', 'Vincente Minnelli'], 1959: ['George Stevens', 'Fred Zinnemann', 'Jack Clayton', 'Billy Wilder', 'William Wyler'], 1960: ['Billy Wilder', 'Jules Dassin', 'Alfred Hitchcock', 'Jack Cardiff', 'Fred Zinnemann'], 1961: ['J. Lee Thompson', 'Robert Rossen', 'Stanley Kramer', 'Federico Fellini', 'Robert Wise', 'Jerome Robbins'], 1962: ['David Lean', 'Frank Perry', 'Pietro Germi', 'Arthur Penn', 'Robert Mulligan'], 1963: ['Elia Kazan', 'Otto Preminger', 'Federico Fellini', 'Martin Ritt', 'Tony Richardson'], 1964: ['George Cukor', 'Peter Glenville', 'Stanley Kubrick', 'Robert Stevenson', 'Michael Cacoyannis'], 1965: ['William Wyler', 'John Schlesinger', 'David Lean', 'Hiroshi Teshigahara', 'Robert Wise'], 1966: ['Fred Zinnemann', 'Michelangelo Antonioni', 'Claude Lelouch', 'Richard Brooks', 'Mike Nichols'], 1967: ['Arthur Penn', 'Stanley Kramer', 'Richard Brooks', 'Norman Jewison', 'Mike Nichols'], 1968: ['Carol Reed', 'Gillo Pontecorvo', 'Anthony Harvey', 'Franco Zeffirelli', 'Stanley Kubrick'], 1969: ['John Schlesinger', 'Arthur Penn', 'George Roy Hill', 'Sydney Pollack', 'Costa-Gavras'], 1970: ['Franklin J. Schaffner', 'Federico Fellini', 'Arthur Hiller', 'Robert Altman', 'Ken Russell'], 1971: ['Stanley Kubrick', 'Norman Jewison', 'Peter Bogdanovich', 'John Schlesinger', 'William Friedkin'], 1972: ['Bob Fosse', 'John Boorman', 'Jan Troell', 'Francis Ford Coppola', 'Joseph L. Mankiewicz'], 1973: ['George Roy Hill', 'George Lucas', 'Ingmar Bergman', 'William Friedkin', 'Bernardo Bertolucci'], 1974: ['Francis Ford Coppola', 'Roman Polanski', 'Francois Truffaut', 'Bob Fosse', 'John Cassavetes'], 1975: ['Federico Fellini', 'Stanley Kubrick', 'Sidney Lumet', 'Robert Altman', 'Milos Forman'], 1976: ['Alan J. Pakula', 'Ingmar Bergman', 'Sidney Lumet', 'Lina Wertmuller', 'John G. Avildsen'], 1977: ['Steven Spielberg', 'Fred Zinnemann', 'George Lucas', 'Herbert Ross', 'Woody Allen'], 1978: ['Hal Ashby', 'Warren Beatty', 'Buck Henry', 'Woody Allen', 'Alan Parker', 'Michael Cimino'], 1979: ['Bob Fosse', 'Francis Coppola', 'Peter Yates', 'Edouard Molinaro', 'Robert Benton'], 1980: ['David Lynch', 'Martin Scorsese', 'Richard Rush', 'Roman Polanski', 'Robert Redford'], 1981: ['Louis Malle', 'Hugh Hudson', 'Mark Rydell', 'Steven Spielberg', 'Warren Beatty'], 1982: ['Wolfgang Petersen', 'Steven Spielberg', 'Sydney Pollack', 'Sidney Lumet', 'Richard Attenborough'], 1983: ['Peter Yates', 'Ingmar Bergman', 'Mike Nichols', 'Bruce Beresford', 'James L. Brooks'], 1984: ['Woody Allen', 'Roland Joffe', 'David Lean', 'Robert Benton', 'Milos Forman'], 1985: ['Hector Babenco', 'John Huston', 'Akira Kurosawa', 'Peter Weir', 'Sydney Pollack'], 1986: ['David Lynch', 'Woody Allen', 'Roland Joffe', 'James Ivory', 'Oliver Stone'], 1987: ['Bernardo Bertolucci', 'Adrian Lyne', 'John Boorman', 'Norman Jewison', 'Lasse Hallstrom'], 1988: ['Barry Levinson', 'Charles Crichton', 'Martin Scorsese', 'Alan Parker', 'Mike Nichols'], 1989: ['Woody Allen', 'Peter Weir', 'Kenneth Branagh', 'Jim Sheridan', 'Oliver Stone'], 1990: ['Francis Ford Coppola', 'Martin Scorsese', 'Stephen Frears', 'Barbet Schroeder', 'Kevin Costner'], 1991: ['John Singleton', 'Barry Levinson', 'Oliver Stone', 'Ridley Scott', 'Jonathan Demme'], 1992: ['Clint Eastwood', 'Neil Jordan', 'James Ivory', 'Robert Altman', 'Martin Brest'], 1993: ['Jim Sheridan', 'Jane Campion', 'James Ivory', 'Robert Altman', 'Steven Spielberg'], 1994: ['Woody Allen', 'Quentin Tarantino', 'Robert Redford', 'Krzysztof Kieslowski', 'Robert Zemeckis'], 1995: ['Chris Noonan', 'Tim Robbins', 'Mike Figgis', 'Michael Radford', 'Mel Gibson'], 1996: ['Anthony Minghella', 'Joel Coen', 'Milos Forman', 'Mike Leigh', 'Scott Hicks'], 1997: ['Peter Cattaneo', 'Gus Van Sant', 'Curtis Hanson', 'Atom Egoyan', 'James Cameron'], 1998: ['Roberto Benigni', 'John Madden', 'Terrence Malick', 'Peter Weir', 'Steven Spielberg'], 1999: ['Spike Jonze', 'Lasse Hallstrom', 'Michael Mann', 'M. Night Shyamalan', 'Sam Mendes'], 2000: ['Stephen Daldry', 'Ang Lee', 'Steven Soderbergh', 'Ridley Scott', 'Steven Soderbergh'], 2001: ['Ridley Scott', 'Robert Altman', 'Peter Jackson', 'David Lynch', 'Ron Howard'], 2002: ['Rob Marshall', 'Martin Scorsese', 'Stephen Daldry', 'Pedro Almodovar', 'Roman Polanski'], 2003: ['Fernando Meirelles', 'Sofia Coppola', 'Peter Weir', 'Clint Eastwood', 'Peter Jackson'], 2004: ['Martin Scorsese', 'Taylor Hackford', 'Alexander Payne', 'Mike Leigh', 'Clint Eastwood'], 2005: ['Ang Lee', 'Bennett Miller', 'Paul Haggis', 'George Clooney', 'Steven Spielberg'], 2006: ['Alejandro Gonzaalez Inarritu', 'Clint Eastwood', 'Stephen Frears', 'Paul Greengrass', 'Martin Scorsese'], 2007: ['Julian Schnabel', 'Jason Reitman', 'Tony Gilroy', 'Paul Thomas Anderson', 'Joel Coen', 'Ethan Coen'], 2008: ['David Fincher', 'Ron Howard', 'Gus Van Sant', 'Stephen Daldry', 'Danny Boyle'], 2009: ['James Cameron', 'Quentin Tarantino', 'Lee Daniels', 'Jason Reitman', 'Kathryn Bigelow'], 2010: ['Darren Aronofsky', 'David O. Russell', 'David Fincher', 'Ethan Coen', 'Joel Coen', 'Tom Hooper']}
winners = {1931: ['Norman Taurog'], 1932: ['Frank Borzage'], 1933: ['Frank Lloyd'], 1934: ['Frank Capra'], 1935: ['John Ford'], 1936: ['Frank Capra'], 1937: ['Leo McCarey'], 1938: ['Frank Capra'], 1939: ['Victor Fleming'], 1940: ['John Ford'], 1941: ['John Ford'], 1942: ['William Wyler'], 1943: ['Michael Curtiz'], 1944: ['Leo McCarey'], 1945: ['Billy Wilder'], 1946: ['William Wyler'], 1947: ['Elia Kazan'], 1948: ['John Huston'], 1949: ['Joseph L. Mankiewicz'], 1950: ['Joseph L. Mankiewicz'], 1951: ['George Stevens'], 1952: ['John Ford'], 1953: ['Fred Zinnemann'], 1954: ['Elia Kazan'], 1955: ['Delbert Mann'], 1956: ['George Stevens'], 1957: ['David Lean'], 1958: ['Vincente Minnelli'], 1959: ['William Wyler'], 1960: ['Billy Wilder'], 1961: ['Jerome Robbins', 'Robert Wise'], 1962: ['David Lean'], 1963: ['Tony Richardson'], 1964: ['George Cukor'], 1965: ['Robert Wise'], 1966: ['Fred Zinnemann'], 1967: ['Mike Nichols'], 1968: ['Carol Reed'], 1969: ['John Schlesinger'], 1970: ['Franklin J. Schaffner'], 1971: ['William Friedkin'], 1972: ['Bob Fosse'], 1973: ['George Roy Hill'], 1974: ['Francis Ford Coppola'], 1975: ['Milos Forman'], 1976: ['John G. Avildsen'], 1977: ['Woody Allen'], 1978: ['Michael Cimino'], 1979: ['Robert Benton'], 1980: ['Robert Redford'], 1981: ['Warren Beatty'], 1982: ['Richard Attenborough'], 1983: ['James L. Brooks'], 1984: ['Milos Forman'], 1985: ['Sydney Pollack'], 1986: ['Oliver Stone'], 1987: ['Bernardo Bertolucci'], 1988: ['Barry Levinson'], 1989: ['Oliver Stone'], 1990: ['Kevin Costner'], 1991: ['Jonathan Demme'], 1992: ['Clint Eastwood'], 1993: ['Steven Spielberg'], 1994: ['Robert Zemeckis'], 1995: ['Mel Gibson'], 1996: ['Anthony Minghella'], 1997: ['James Cameron'], 1998: ['Steven Spielberg'], 1999: ['Sam Mendes'], 2000: ['Steven Soderbergh'], 2001: ['Ron Howard'], 2002: ['Roman Polanski'], 2003: ['Peter Jackson'], 2004: ['Clint Eastwood'], 2005: ['Ang Lee'], 2006: ['Martin Scorsese'], 2007: ['Ethan Coen', 'Joel Coen'], 2008: ['Danny Boyle'], 2009: ['Kathryn Bigelow'], 2010: ['Tom Hooper']}

# Question 1A: Create dictionary with the count of Oscar nominations for each director 
nom_count_dict = {} 
# Add your code here, make sure your result is stored in `nom_count_dict`

for key, names in nominated.items():
    print(f"key: {key}, names: {names}, type(names): {type(names)}")
    for name in names:
        print(name)
        if name in nom_count_dict:
            nom_count_dict[name] += 1
        else:
            nom_count_dict[name] = 1

print(nom_count_dict)        
### Notebook grading

correct_result1 = {'Norman Taurog': 2, 'Wesley Ruggles': 1, 'Clarence Brown': 4, 'Lewis Milestone': 1, 'Josef Von Sternberg': 2, 'Frank Borzage': 1, 'King Vidor': 3, 'Frank Lloyd': 2, 'Frank Capra': 6, 'George Cukor': 5, 'Victor Schertzinger': 1, 'W. S. Van Dyke': 2, 'John Ford': 5, 'Michael Curtiz': 5, 'Henry Hathaway': 1, 'William Wyler': 12, 'Robert Z. Leonard': 1, 'Gregory La Cava': 2, 'Leo McCarey': 3, 'Sidney Franklin': 1, 'William Dieterle': 1, 'William Wellman': 2, 'Sam Wood': 3, 'Victor Fleming': 1, 'Alfred Hitchcock': 5, 'Orson Welles': 1, 'Alexander Hall': 1, 'Howard Hawks': 1, 'Mervyn LeRoy': 1, 'John Farrow': 1, 'Ernst Lubitsch': 1, 'George Stevens': 5, 'Henry King': 2, 'Billy Wilder': 8, 'Otto Preminger': 2, 'Jean Renoir': 1, 'David Lean': 7, 'Robert Siodmak': 1, 'Elia Kazan': 5, 'Henry Koster': 1, 'Edward Dmytryk': 1, 'John Huston': 5, 'Laurence Olivier': 1, 'Jean Negulesco': 1, 'Fred Zinnemann': 7, 'Anatole Litvak': 1, 'Joseph L. Mankiewicz': 4, 'Robert Rossen': 2, 'William A. Wellman': 1, 'Carol Reed': 3, 'Vincente Minnelli': 2, 'Cecil B. DeMille': 1, 'Charles Walters': 1, 'George Seaton': 1, 'Delbert Mann': 1, 'John Sturges': 1, 'Joshua Logan': 2, 'Michael Anderson': 1, 'Walter Lang': 1, 'Mark Robson': 2, 'Sidney Lumet': 4, 'Richard Brooks': 3, 'Stanley Kramer': 3, 'Robert Wise': 3, 'Jack Clayton': 1, 'Jules Dassin': 1, 'Jack Cardiff': 1, 'J. Lee Thompson': 1, 'Federico Fellini': 4, 'Jerome Robbins': 1, 'Frank Perry': 1, 'Pietro Germi': 1, 'Arthur Penn': 3, 'Robert Mulligan': 1, 'Martin Ritt': 1, 'Tony Richardson': 1, 'Peter Glenville': 1, 'Stanley Kubrick': 4, 'Robert Stevenson': 1, 'Michael Cacoyannis': 1, 'John Schlesinger': 3, 'Hiroshi Teshigahara': 1, 'Michelangelo Antonioni': 1, 'Claude Lelouch': 1, 'Mike Nichols': 4, 'Norman Jewison': 3, 'Gillo Pontecorvo': 1, 'Anthony Harvey': 1, 'Franco Zeffirelli': 1, 'George Roy Hill': 2, 'Sydney Pollack': 3, 'Costa-Gavras': 1, 'Franklin J. Schaffner': 1, 'Arthur Hiller': 1, 'Robert Altman': 5, 'Ken Russell': 1, 'Peter Bogdanovich': 1, 'William Friedkin': 2, 'Bob Fosse': 3, 'John Boorman': 2, 'Jan Troell': 1, 'Francis Ford Coppola': 3, 'George Lucas': 2, 'Ingmar Bergman': 3, 'Bernardo Bertolucci': 2, 'Roman Polanski': 3, 'Francois Truffaut': 1, 'John Cassavetes': 1, 'Milos Forman': 3, 'Alan J. Pakula': 1, 'Lina Wertmuller': 1, 'John G. Avildsen': 1, 'Steven Spielberg': 6, 'Herbert Ross': 1, 'Woody Allen': 6, 'Hal Ashby': 1, 'Warren Beatty': 2, 'Buck Henry': 1, 'Alan Parker': 2, 'Michael Cimino': 1, 'Francis Coppola': 1, 'Peter Yates': 2, 'Edouard Molinaro': 1, 'Robert Benton': 2, 'David Lynch': 3, 'Martin Scorsese': 6, 'Richard Rush': 1, 'Robert Redford': 2, 'Louis Malle': 1, 'Hugh Hudson': 1, 'Mark Rydell': 1, 'Wolfgang Petersen': 1, 'Richard Attenborough': 1, 'Bruce Beresford': 1, 'James L. Brooks': 1, 'Roland Joffe': 2, 'Hector Babenco': 1, 'Akira Kurosawa': 1, 'Peter Weir': 4, 'James Ivory': 3, 'Oliver Stone': 3, 'Adrian Lyne': 1, 'Lasse Hallstrom': 2, 'Barry Levinson': 2, 'Charles Crichton': 1, 'Kenneth Branagh': 1, 'Jim Sheridan': 2, 'Stephen Frears': 2, 'Barbet Schroeder': 1, 'Kevin Costner': 1, 'John Singleton': 1, 'Ridley Scott': 3, 'Jonathan Demme': 1, 'Clint Eastwood': 4, 'Neil Jordan': 1, 'Martin Brest': 1, 'Jane Campion': 1, 'Quentin Tarantino': 2, 'Krzysztof Kieslowski': 1, 'Robert Zemeckis': 1, 'Chris Noonan': 1, 'Tim Robbins': 1, 'Mike Figgis': 1, 'Michael Radford': 1, 'Mel Gibson': 1, 'Anthony Minghella': 1, 'Joel Coen': 3, 'Mike Leigh': 2, 'Scott Hicks': 1, 'Peter Cattaneo': 1, 'Gus Van Sant': 2, 'Curtis Hanson': 1, 'Atom Egoyan': 1, 'James Cameron': 2, 'Roberto Benigni': 1, 'John Madden': 1, 'Terrence Malick': 1, 'Spike Jonze': 1, 'Michael Mann': 1, 'M. Night Shyamalan': 1, 'Sam Mendes': 1, 'Stephen Daldry': 3, 'Ang Lee': 2, 'Steven Soderbergh': 2, 'Peter Jackson': 2, 'Ron Howard': 2, 'Rob Marshall': 1, 'Pedro Almodovar': 1, 'Fernando Meirelles': 1, 'Sofia Coppola': 1, 'Taylor Hackford': 1, 'Alexander Payne': 1, 'Bennett Miller': 1, 'Paul Haggis': 1, 'George Clooney': 1, 'Alejandro Gonzaalez Inarritu': 1, 'Paul Greengrass': 1, 'Julian Schnabel': 1, 'Jason Reitman': 2, 'Tony Gilroy': 1, 'Paul Thomas Anderson': 1, 'Ethan Coen': 2, 'David Fincher': 2, 'Danny Boyle': 1, 'Lee Daniels': 1, 'Kathryn Bigelow': 1, 'Darren Aronofsky': 1, 'David O. Russell': 1, 'Tom Hooper': 1}
if nom_count_dict == correct_result1:
    print("Nice work!")
else:
    print("Make sure you are referencing the correct lists for input to create the dictionary.")




















# Question 1B: Create dictionary with the count of Oscar wins for each director
win_count_dict = {}
# Add your code here, make sure your result is stored in `win_count_dict`
for year, director in winners.items():
    #print(f"type(year){type(year)}, type(director): {type(director)}") 
    #print(director[0])
    if director[0] in win_count_dict:
        win_count_dict[director[0]] += 1
    else:
        win_count_dict[director[0]] = 1

print(f"win_count_dict: {win_count_dict}")

### Notebook grading
correct_result2 = {'Norman Taurog': 1, 'Frank Borzage': 1, 'Frank Lloyd': 1, 'Frank Capra': 3, 'John Ford': 4, 'Leo McCarey': 2, 'Victor Fleming': 1, 'William Wyler': 3, 'Michael Curtiz': 1, 'Billy Wilder': 2, 'Elia Kazan': 2, 'John Huston': 1, 'Joseph L. Mankiewicz': 2, 'George Stevens': 2, 'Fred Zinnemann': 2, 'Delbert Mann': 1, 'David Lean': 2, 'Vincente Minnelli': 1, 'Jerome Robbins': 1, 'Robert Wise': 2, 'Tony Richardson': 1, 'George Cukor': 1, 'Mike Nichols': 1, 'Carol Reed': 1, 'John Schlesinger': 1, 'Franklin J. Schaffner': 1, 'William Friedkin': 1, 'Bob Fosse': 1, 'George Roy Hill': 1, 'Francis Ford Coppola': 1, 'Milos Forman': 2, 'John G. Avildsen': 1, 'Woody Allen': 1, 'Michael Cimino': 1, 'Robert Benton': 1, 'Robert Redford': 1, 'Warren Beatty': 1, 'Richard Attenborough': 1, 'James L. Brooks': 1, 'Sydney Pollack': 1, 'Oliver Stone': 2, 'Bernardo Bertolucci': 1, 'Barry Levinson': 1, 'Kevin Costner': 1, 'Jonathan Demme': 1, 'Clint Eastwood': 2, 'Steven Spielberg': 2, 'Robert Zemeckis': 1, 'Mel Gibson': 1, 'Anthony Minghella': 1, 'James Cameron': 1, 'Sam Mendes': 1, 'Steven Soderbergh': 1, 'Ron Howard': 1, 'Roman Polanski': 1, 'Peter Jackson': 1, 'Ang Lee': 1, 'Martin Scorsese': 1, 'Ethan Coen': 1, 'Joel Coen': 1, 'Danny Boyle': 1, 'Kathryn Bigelow': 1, 'Tom Hooper': 1}


if win_count_dict == correct_result2:
    print("Nice work!")
else:
    print("Make sure you are referencing the correct lists for input to create the dictionary.")











winners = {1931: ['Norman Taurog'], 1932: ['Frank Borzage'], 1933: ['Frank Lloyd'], 1934: ['Frank Capra'], 1935: ['John Ford'], 1936: ['Frank Capra'], 1937: ['Leo McCarey'], 1938: ['Frank Capra'], 1939: ['Victor Fleming'], 1940: ['John Ford'], 1941: ['John Ford'], 1942: ['William Wyler'], 1943: ['Michael Curtiz'], 1944: ['Leo McCarey'], 1945: ['Billy Wilder'], 1946: ['William Wyler'], 1947: ['Elia Kazan'], 1948: ['John Huston'], 1949: ['Joseph L. Mankiewicz'], 1950: ['Joseph L. Mankiewicz'], 1951: ['George Stevens'], 1952: ['John Ford'], 1953: ['Fred Zinnemann'], 1954: ['Elia Kazan'], 1955: ['Delbert Mann'], 1956: ['George Stevens'], 1957: ['David Lean'], 1958: ['Vincente Minnelli'], 1959: ['William Wyler'], 1960: ['Billy Wilder'], 1961: ['Jerome Robbins', 'Robert Wise'], 1962: ['David Lean'], 1963: ['Tony Richardson'], 1964: ['George Cukor'], 1965: ['Robert Wise'], 1966: ['Fred Zinnemann'], 1967: ['Mike Nichols'], 1968: ['Carol Reed'], 1969: ['John Schlesinger'], 1970: ['Franklin J. Schaffner'], 1971: ['William Friedkin'], 1972: ['Bob Fosse'], 1973: ['George Roy Hill'], 1974: ['Francis Ford Coppola'], 1975: ['Milos Forman'], 1976: ['John G. Avildsen'], 1977: ['Woody Allen'], 1978: ['Michael Cimino'], 1979: ['Robert Benton'], 1980: ['Robert Redford'], 1981: ['Warren Beatty'], 1982: ['Richard Attenborough'], 1983: ['James L. Brooks'], 1984: ['Milos Forman'], 1985: ['Sydney Pollack'], 1986: ['Oliver Stone'], 1987: ['Bernardo Bertolucci'], 1988: ['Barry Levinson'], 1989: ['Oliver Stone'], 1990: ['Kevin Costner'], 1991: ['Jonathan Demme'], 1992: ['Clint Eastwood'], 1993: ['Steven Spielberg'], 1994: ['Robert Zemeckis'], 1995: ['Mel Gibson'], 1996: ['Anthony Minghella'], 1997: ['James Cameron'], 1998: ['Steven Spielberg'], 1999: ['Sam Mendes'], 2000: ['Steven Soderbergh'], 2001: ['Ron Howard'], 2002: ['Roman Polanski'], 2003: ['Peter Jackson'], 2004: ['Clint Eastwood'], 2005: ['Ang Lee'], 2006: ['Martin Scorsese'], 2007: ['Ethan Coen', 'Joel Coen'], 2008: ['Danny Boyle'], 2009: ['Kathryn Bigelow'], 2010: ['Tom Hooper'], 2011: ['Frank Capra']}

number_of_wins = {}
for year, list_director in winners.items():
    for director in list_director:
        number_of_wins[director] = number_of_wins.get(director, 0) + 1        


print(max(number_of_wins.values()))
max_wins = max(number_of_wins.values())

most_win_director = [director  for director, value in number_of_wins.items() if value == max_wins]

print(most_win_director)

### Notebook grading
correct_ans = ['Frank Capra','John Ford']

if most_win_director == correct_ans:
    print("Good job!")
else:
    print("Oops! That doesn't look like the expected answer. Make sure you are referencing the correct lists for input to create the list.")


list_number = [1, 3, 5, 7, 9, 11, 13, 15]

combinaciones = 0

for i in range(len(list_number)):
    for j in range(len(list_number)):
        for k in range(len(list_number)):
            combinaciones += 1 
            if list_number[i] + list_number[j] + list_number[k] == 30:
                print(f"los numeros son {list_number[i]} + {list_number[j]}+ {list_number[k]}")
            else:
                print(f"La convinacion de {list_number[i]} + {list_number[j]}+ {list_number[k]} da por resultado: {list_number[i] + list_number[j] + list_number[k]}")

print(f"Posibles combinaciones {combinaciones}")









numbers = [
              [34, 63, 88, 71, 29],
              [90, 78, 51, 27, 45],
              [63, 37, 85, 46, 22],
              [51, 22, 34, 11, 18]
           ]

num_list = lambda x: sum(x)/len(x)
averages = list(map( num_list, numbers))

### Notebook grading
correct_answer = [57.0, 58.2, 50.6, 27.2]
if 'mean' in locals():
    print("Your solution should not include the `mean` function. `mean` should be replaced by a lambda function.")
elif averages == correct_answer:
    print("Nice work! You can view my solution on the next page NICOLAS.")
elif type(averages) != list:
    print("Not quite! Did you convert the output of `map` to a list?")
else:
    print("Not quite! The value of `averages` should be {}".format(correct_answer))


how_many_snakes = 1
snake_string = """
Welcome to Python3!

             ____
            / . .\\
            \  ---<
             \  /
   __________/ /
-=:___________/

<3, Juno
"""


print(snake_string * how_many_snakes)




# name = input("Enter your name: ")
# print(f"Hello {name}")


# num = int(input("Enter a number: "))
# print(f"type(num): {type(num)}: num: {num}")

# result = eval(input("Enter an expresion: "))

# print(result)

next_student = True
names_list = []
assignments = []
grades = []

while next_student is True:
    names_list.append(input("Enter the student name: ")) # get and process input for a list of names
    print(f"type(names_list): {type(names_list)}, name: {names_list}")
    assignments.append(int(input("Insert number of missing assignments : "))) # get and process input for a list of the number of assignments
    grades.append(int(input("Insert current grade: "))) # get and process input for a list of grades
    next_student = input("New student? Y or N: ").strip().upper() == 'Y'
# el metodo strip elimina los espacios finales e iniciales en la entrada de datos 
# por si el usuario ingreso un espacio por error

# El metodo upper convierte la entrada a mayusculas para que sea 
# case sensitive


## message string to be used for each student
## HINT: use .format() with this string in your for loop
message = "Hi {},\n\nThis is a reminder that you have {} assignments left to \
submit before you can graduate. Your current grade is {} and can increase \
to {} if you submit all assignments before the due date.\n\n"

# students = (names, assignments, grades)

for i in range(len(names_list)):
    print(message.format(names_list[i], assignments[i], grades[i], assignments[i]*2 + grades[i]))

## write a for loop that iterates through each set of names, assignments, and grades to print each student's message


