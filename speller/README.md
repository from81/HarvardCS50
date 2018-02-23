# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

An invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

Get resource usage.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Passing structs by value takes up a lot of memory.
Copies of the structs will be placed on the stack, and this can cause stack overflow.
That's why it's better to use pointers to refer to the address of structs.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop will start only if the file has been properly opened.
The loop will begin by initializing c by reading the first char from the file,
and read the next character on every iteration.

The program will check each character contained in variable c to make sure that it's either a letter
or an apostrophe, and if apostrophe, it doesn't appear at the beginning of the word.
If a letter is contained in c, it will be inserted into the "word" array at the INDEX position.
Then, INDEX increments up to go to the next position in the "word" array.

LENGTH defines the maximum permitted length of a word.
If the size of INDEX is greater than the maximum permitted length, or if a word contains a number,
then the program will go to the end of the word and check the next word and set index to 0.

If a word being checked satisfies all conditions (no apostrophes in the beginning or numbers, permitted length)
it receive a null terminator. The timber begins as the word is checked for any misspelling.
If it's not in the dictionary, it will be considered a misspelling.
The misspelled word will be printed out and the total number of misspelling caught is incremented by 1.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf requires us to allocate memory for the string before reading in from the file.
fscanf with a format string like "%s" will read all the characters until a whitespace is found, and skips the whitespace.
Whenever words are followed by punctuation signs, that will be considered to be part of the preceding word.
Also, if extremely long words are in the text, it could cause stack overflow or encounter segmentation fault.

fgetc will examine 1 character at a time, allowing us to flexibly specify constraints
and the subsequent actions, instead of reading in the word until whitespace is reached.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

const char*
- is a mutable pointer to an immutable character/string.
- you cannot change the contents of the location(s) this pointer points to.

This is useful for functions like load and check whose job is only to read the WORD array, and not change it.
This allows MAIN to pass a new string to the CHECK function, while ensuring that CHECK doesn't modify it.