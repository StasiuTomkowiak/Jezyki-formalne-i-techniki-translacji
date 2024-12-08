from lexer import *
from parser import *
from sys import stdin
if __name__ == "__main__":
    acc = ''
    for line in stdin:
        if line.strip().endswith('\\'):
            acc += line.strip()[:-1]
        elif acc:
            acc += line.strip()
            yacc.parse(acc)
            acc = ''
        else:
            yacc.parse(line.strip())
