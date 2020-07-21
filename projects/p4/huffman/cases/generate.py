import random

random.seed(280)

chars = 'abcdefghijklmnopqrstuwxyz \n'

with open('textfile.txt', 'w') as f:
    for i in range(100000):
        a = random.randint(0, len(chars) - 1)
        f.write(chars[a])
    f.write('\n')
