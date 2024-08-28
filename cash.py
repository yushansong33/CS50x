from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Convert change to cents
cents = int(change * 100)

# Number of quarters
# // 整数除法取整运算
quarters = cents // 25
# % 整数除法余数运算
cents %= 25

# Number of dimes
dimes = cents // 10
cents %= 10

# Number of nickels
nickels = cents // 5
cents %= 5

# Number of pennies
pennies = cents

# Total number of coins
total = quarters + dimes + nickels + pennies
print(total)

