def mean(num_list):
    return sum(num_list)/len(num_list)

def add_five(num_list):
    return [num + 5 for num in num_list]

def main():
    scores = [89, 92, 79, 93, 85]

    print(f"mean(scores): {mean(scores)}")
    print(f"add_five(scores): {add_five(scores)}")

if __name__ == "__main__":
    main()
