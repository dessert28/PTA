a = input().strip()
re = input().strip()
word = input().strip()
words = a.split()
for i in range(len(words)):
    if words[i].lower() == re.lower():
        words[i] = word
output = ' '.join(words)
print(output)
