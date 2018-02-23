from nltk.tokenize import sent_tokenize


def substr(strng, n):
    """Convert string to substring of length n"""
    temp = []
    for i in range(len(strng) - n + 1):
        temp.append(strng[i:i + n])

    return temp


def lines(a, b):
    """Return lines in both a and b"""
    a = a.split("\n")
    b = b.split("\n")

    words = []
    for i in a:
        if i in b:
            words.append(i)

    return words


def sentences(a, b):
    """Return sentences in both a and b"""
    a = sent_tokenize(a)
    b = sent_tokenize(b)

    words = []
    for i in a:
        if i in b:
            b.remove(i)  # ensure no redundant matches
            words.append(i)

    return words


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a = substr(a, n)
    b = substr(b, n)

    words = []
    for i in a:
        if i in b:
            b.remove(i)  # ensure no redundant matches
            if i not in words:  # prevent duplicates in word list
                words.append(i)

    return words