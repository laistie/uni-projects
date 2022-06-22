import random


def menu():
    print('\n[0]Descrição\n[1]Gerar código de barras aleatório\n[2]Verificar código de barras válido\n[3]Gerar dígito de controle de um determinado código de barras\n[4]Sair\n')


def description():
    print('O código de barras EAN 13 (European Article Number) é uma combinação de números. Ele é constituído por 13 dígitos e é utilizado para identificar um objeto ou produto com base em um sistema europeu. Nesse caso, o dígito de controle é definido usando a congruência módulo 10 e os fatores que compõem a base de multiplicação são 1 e 3, que vão se repetindo da esquerda para a direita.')


def generate_code(code):
    n = 0
    for i in range(0, 11):
        if i % 2 == 0:
            n += code[i] * 1
        else:
            n += code[i] * 3
    if n % 10 == 0:
        cd = 0
    else:
        cd = 10 - n % 10
    code.append(cd)


def random_code():
    n = random.randint(0, 9)
    code = [n]
    for i in range(1, 12):
        n = random.randint(0, 9)
        code.append(n)
    generate_code(code)
    print('' .join(map(str, code)))


def generate_cd(code):
    numbers = [int(x) for x in str(code)]
    n = 0
    for i in range(0, 12):
        if i % 2 == 0:
            print('{} + ' .format(numbers[i] * 1), end='')
            n += numbers[i] * 1
        else:
            if i == 11:
                print('{} = '.format(numbers[i] * 3), end='')
            else:
                print('{} + '.format(numbers[i] * 3), end='')
            n += numbers[i] * 3
    print('{}'.format(n))
    if n % 10 == 0:
        cd = 0
    else:
        cd = 10 - n % 10
    print('{} ≡ {}(mod 10)' .format(n, n % 10))
    return cd


def verify_len(code):
    if len(str(code)) == 13:
        return True
    else:
        return False


def verify(code):
    cd = generate_cd(code)
    numbers = [int(x) for x in str(code)]
    if cd == numbers[12]:
        print('Código de barras válido.\n')
    else:
        print('Código de barras inválido. Dígito de controle esperado: {}\n' .format(cd))


def verify_lencd(code):
    if len(str(code)) == 12:
        return True
    else:
        return False


def generate_last(code):
    cd = generate_cd(code)
    print('Dígito de controle: {}\n' .format(cd))
