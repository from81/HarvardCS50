height = int(input("Height: "))
while (height < 0) or (height > 23):
    height = int(input("Height: "))

width = height + 1
block = "##"

for i in range(height):
    print("{:>{a}s}".format(block, a=width))
    block += "#"