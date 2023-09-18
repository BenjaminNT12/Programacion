def solve(A):
    B = A[::-1]  # Reverse the entire string
    B = B.split()  # Split the string into words

    # Reverse each individual word
    for i in range(len(B)):
        B[i] = B[i][::-1]

    # Join the words back together
    A = " ".join(B)

    return A

# Example usage
A = "the sky is blue"
B = solve(A)
print(B)