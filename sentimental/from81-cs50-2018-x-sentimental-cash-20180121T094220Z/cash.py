change = float(input("Cash owed: "))
while change < 0:  # only accept positive values
    change = float(input("Cash owed: "))

pennies = int(change * 100)  # convert change to pennies
coins = [25, 10, 5, 1]  # list of coins
total_coins = 0

for i in coins:  # iterate over the list of coins
    temp = 0
    if pennies >= i:
        temp += pennies // i
        total_coins += temp
        pennies -= temp * i

print(total_coins)