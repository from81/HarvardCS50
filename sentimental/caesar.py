import sys

if len(sys.argv) is not 2:  # exit if more than 2 args
    print(f"Usage: {sys.argv[0]} k")
    sys.exit(1)

k = int(sys.argv[1])  # initialize key as int
if k > 26:  # adjust to 0 - 26
    k = (k % 26)

plaintxt = input("plaintext: ")  # plaintext stored as string
strlist = []  # initialize list of char
for i in range(len(plaintxt)):
    strlist.append(plaintxt[i])  # append all char to strlist

for i in range(len(strlist)):
    if strlist[i].isalpha() is True:
        for g in range(k):
            if strlist[i] is 'Z' or strlist[i] is 'z':
                temp = ord(strlist[i]) - 25
                strlist[i] = chr(temp)
            elif strlist[i] >= 'A' or strlist[i] <= 'Z':
                temp = ord(strlist[i]) + 1
                strlist[i] = chr(temp)
            elif strlist[i] >= 'a' or strlist[i] <= 'z':
                temp = ord(strlist[i]) + 1
                strlist[i] = chr(temp)

plaintxt = ''.join(strlist)
print("ciphertext: " + plaintxt)