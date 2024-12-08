import ply.lex as lex

tokens = (
    'NUM', 'ADD', 'SUB', 'MUL', 'DIV', 'MOD', 'POW',
    'LNAW', 'PNAW', 'COMM'
)

t_COMM = r'\#.*'

t_ADD = r'\+'
t_SUB = r'\-'
t_MUL = r'\*'
t_DIV = r'\/'
t_MOD = r'\%'
t_POW = r'\^'
t_LNAW = r'\('
t_PNAW = r'\)'

def t_NUM(t):
    r'[0-9]+'
    t.value = int(t.value)
    return t

t_ignore = ' \t'

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value) 

def t_error(t):
    print(f"Nieprawidłowy znak: {t.value[0]!r}")
    t.lexer.skip(1)

lexer = lex.lex()
