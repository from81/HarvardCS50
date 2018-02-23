height = int(input("Height: "))
while (height < 0) or (height > 23):  # set constraints
    height = int(input("Height: "))

width = height + 1  # set width of the bottom row

for i in range(2, height + 2):  # shifted range by +2 to set width
    print(' ' * (width - i), end='')
    print('#' * i)