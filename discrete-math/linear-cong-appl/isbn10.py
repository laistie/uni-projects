import random


def menu():
    print('\n[0]Descrição\n[1]Gerar ISBN aleatório\n[2]Verificar ISBN válido\n[3]Gerar dígito de controle de um determinado ISBN\n[4]Sair\n')


def description():
    print('O ISBN 10 (International Standard Book Number) é um conjunto responsável por individualizar obras e publicações. Ele é composto por 10 números, dentre os quais o último (dígito de controle) é calculado através da congruência módulo 11 envolvendo operações matemáticas com os outros 9 dígitos.')


def generate_code(code):
    n = 0
    for i in range(10, 1, -1):
        n += code[10 - i] * i
    if n % 11 == 0:
        cd = 0
    elif n % 11 == 1:
        cd = 'X'
    else:
        cd = 11 - n % 11
    code.append(cd)


def random_code():
    n = random.randint(0, 9)
    code = [n]
    for i in range(1, 9):
        n = random.randint(0, 9)
        code.append(n)
    generate_code(code)
    code.insert(9, '-')
    print('' .join(map(str, code)))


def generate_cd(code):
    numbers = list(code)
    n = 0
    for i in range(10, 1, -1):
        if i == 2:
            print('{} = '.format(int(numbers[10 - i]) * i), end='')
        else:
            print('{} + '.format(int(numbers[10 - i]) * i), end='')
        n += int(numbers[10 - i]) * i
    print('{}' .format(n))
    cd = 11 - n % 11
    if cd == 10:
        cd = 'X'
    if cd == 11:
        cd = 0
    print('{} ≡ {}(mod 11)' .format(n, n % 11))
    print('Dígito de controle: {}' .format(cd))
    return cd


def verify_len(code):
    if len(str(code)) == 10:
        return True
    else:
        return False


def verify(code):
    cd = generate_cd(code)
    if str(cd) == code[9]:
        print('ISBN válido\n')
    else:
        print('ISBN inválido. Dígito de controle esperado: {}\n' .format(cd))


def verify_lencd(code):
    if len(str(code)) == 9:
        return True
    else:
        return False


def generate_last(code):
    cd = generate_cd(code)
