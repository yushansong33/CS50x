from cs50 import get_string

text = get_string("Text: ")

word_count = 0
letter_count = 0
sentence_count = 0
a = ".!?"

for n in text:
    if n == " ":
        word_count += 1
    if n.isalpha() == True:
        letter_count += 1
    if n in a:
        sentence_count += 1

word_count += 1

L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")

