from cs50 import get_int

def get(prompt):
    while True:
        height = get_int(prompt)
        if height < 1 or height > 8:
            pass
        else:
            return height

def main():
    n = get("Height: ")
    for i in range(n):
        print(" " * (n - i - 1), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1))

main()
