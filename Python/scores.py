import useful_func

scores = [89, 92, 79, 93, 85]

mean = useful_func.mean(scores)
add_five = useful_func.add_five(scores)

print(f"mean: {mean} ")
print(f"add_five: {add_five} ")

print(__name__)
print(useful_func.__name__)