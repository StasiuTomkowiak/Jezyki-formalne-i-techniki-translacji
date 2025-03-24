
import ply.yacc as yacc
from lexer import *
from sys import stdin

precedence = (
    ('left', 'ADD', 'SUB'),
    ('left', 'MUL', 'DIV', 'MOD'),
    ('right', 'POW'),
    ('nonassoc', 'LNAW', 'PNAW')  
)

polish_notation=[]
Z = 1234577
POW = 1234576


def to_Z(x):
    return ((x % Z) + Z) % Z

def to_POW(x):
    return ((x % POW) + POW) % POW

def inverse(a):
    m = Z
    x, y = 1, 0

    while a > 1:
        quotient = a // m
        a, m = m, a % m
        x, y = y, x - quotient * y

    return x + Z if x < 0 else x

def multiply(x, y):
    result = 0
    for _ in range(y):
        result = to_Z(result + x)
    return result

def divide(x, y):
    return multiply(x, inverse(y))

def modulo(x, y):
    return to_Z(to_Z(x) %to_Z(y) )

def power(x, y):
    result = 1
    for _ in range(y):
        result = to_Z(result * x)
    return result

def inverseP(a):
    m = POW
    x, y = 1, 0

    while a > 1:
        quotient = a // m
        a, m = m, a % m
        x, y = y, x - quotient * y

    return x + POW if x < 0 else x

def multiplyP(x, y):
    result = 0
    for _ in range(y):
        result = to_POW(result + x)
    return result

def divideP(x, y):
    return multiply(x, inverse(y))

def moduloP(x, y):
    return to_POW(to_POW(x) % to_POW(y) )



def p_STAR_EXPR(p):
    'STAR : exp'
    print(' '.join(polish_notation))
    print('Wynik: ', p[1])
    polish_notation.clear()

def p_STAR_COMM(p):
    'STAR : COMM'
    pass

def p_exp_ADD(p):
    'exp : exp ADD exp'
    p[0] = to_Z(to_Z(p[1]) + to_Z(p[3]))
    polish_notation.append('+')

def p_exp_SUB(p):
    'exp : exp SUB exp'
    p[0] = to_Z(to_Z(p[1]) - to_Z(p[3]))
    polish_notation.append('-')
def p_exp_MUL(p):
    'exp : exp MUL exp'
    p[0] = multiply(p[1], p[3])
    polish_notation.append('*')

def p_exp_DIV(p):
    'exp : exp DIV exp'
    if p[3]==0:
        print("div by zero")
        polish_notation.clear()
    else:
        p[0] = divide(p[1], p[3])
        polish_notation.append('/')

def p_exp_MOD(p):
    'exp : exp MOD exp'
    if p[3]==0:
        print("mod by zero")
        polish_notation.clear()
    else:
        p[0] = modulo(p[1], p[3])
        polish_notation.append('%')

def p_exp_POW(p):
    'exp : exp POW minus_num_pow'
    p[0] = power(p[1], p[3])
    polish_notation.append('^')

def p_exp_LNAW_PNAW(p):
    'exp : LNAW exp PNAW'
    p[0] = p[2]

def p_NUM(p):
    '''exp : NUM
    | SUB NUM %prec POW'''
    if len(p) == 2:  
        p[0] = to_Z(p[1])
        polish_notation.append(str(p[0]))
    elif len(p) == 3:
        p[0] = to_Z(to_Z(0) - to_Z(p[2]))
        polish_notation.append(str(p[0])+' ')


def p_minus_num_pow_ADD(p):
    'minus_num_pow : minus_num_pow ADD minus_num_pow'
    p[0] = to_POW(to_POW(p[1]) + to_POW(p[3]))
    polish_notation.append('+')

def p_minus_num_pow_SUB(p):
    'minus_num_pow : minus_num_pow SUB minus_num_pow'
    p[0] = to_POW(to_POW(p[1]) - to_POW(p[3]))
    polish_notation.append('-')

def p_minus_num_pow_MUL(p):
    'minus_num_pow : minus_num_pow MUL minus_num_pow'
    p[0] = multiplyP(p[1], p[3])
    polish_notation.append('*')

def p_minus_num_pow_DIV(p):
    'minus_num_pow : minus_num_pow DIV minus_num_pow'
    if p[3]==0:
        print("div by zero")
        polish_notation.clear()
    else:
        p[0] = divideP(p[1], p[3])
        polish_notation.append('/')

def p_minus_num_pow_MOD(p):
    'minus_num_pow : minus_num_pow MOD minus_num_pow'
    if p[3]==0:
        print("mod by zero")
        polish_notation.clear()
    else:
        p[0] = moduloP(p[1], p[3])
        polish_notation.append('%')

def p_minus_num_pow_LNAW_PNAW(p):
    'minus_num_pow : LNAW minus_num_pow PNAW'
    p[0] = p[2]
    
def p_minus_num_pow(p):
    '''minus_num_pow : NUM
                     | SUB NUM %prec POW'''
    if len(p) == 2:  
        p[0] = to_Z(p[1])
        polish_notation.append(str(p[0]))
    elif len(p) == 3:  
        p[0] = to_POW(to_POW(0) - to_POW(p[2]))
        polish_notation.append(str(p[0]))


def p_error(p):
    if p != None:
        print(f'\nsyntax error: ‘{p.value}’')
        polish_notation.clear()
    else:
        print(f'syntax error')
        polish_notation.clear()

# Tworzenie parsera
parser = yacc.yacc()
