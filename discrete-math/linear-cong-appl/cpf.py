import random


def menu():
    print('\n[0]Descrição\n[1]Gerar CPF aleatório\n[2]Verificar CPF válido\n[3]Gerar dígitos de controle de um determinado CPF\n[4]Sair\n')


def description():
    print('O CPF (Cadastro de Pessoas Físicas), no Brasil, é constituído por 11 números, sendo um primeiro bloco com 9 algarismos e um segundo com mais 2, sendo estes os dígitos de controle. Nesse caso, o décimo dígito é resultado de uma congruência módulo 11 de uma operação com os primeiros n algarismos. Em seguida, calcula-se o segundo dígito de controle realizando a mesma congruência, mas com operação diferente entre os algarismos anteriores.')


def generate_cpf(cpf):
    n = 0
    for i in range(0, 9):
        n += cpf[i] * i
    cd1 = n % 11
    cpf.append(cd1)

    n = 0
    for i in range(0, 10):
        n += cpf[i] * i
    cd2 = n % 11
    cpf.append(cd2)


def random_cpf():
    n = random.randint(0, 9)
    cpf = [n]
    for i in range(1, 9):
        n = random.randint(0, 9)
        cpf.append(n)
    generate_cpf(cpf)
    cpf.insert(3, '.')
    cpf.insert(7, '.')
    cpf.insert(11, '-')
    print('' .join(map(str, cpf)))


def generate_cds(cpf):
    n = 0
    numbers = [int(x) for x in str(cpf)]
    for i in range(0, 9):
        if i == 8:
            print('{} = '.format(numbers[i] * (i + 1)), end='')
        else:
            print('{} + '.format(numbers[i] * (i + 1)), end='')
        n += numbers[i] * (i + 1)
    print('{}' .format(n))
    if n % 11 == 10:
        cds = [0]
    else:
        cds = [n % 11]
    print('{} ≡ {}(mod 11)\nDígito de controle 1: {}'.format(n, n % 11, cds[0]))

    n = 0
    for i in range(0, 10):
        if i == 9:
            print('{} = '.format(cds[0] * i), end='')
            n += cds[0] * i
        else:
            print('{} + '.format(numbers[i] * i), end='')
            n += numbers[i] * i
    print('{}'.format(n))
    if n % 11 == 10:
        cd2 = 0
    else:
        cd2 = n % 11
    print('{} ≡ {}(mod 11)\nDígito de controle 2: {}'.format(n, n % 11, n % 11))
    cds.append(cd2)
    return cds


def verify_len(cpf):
    if len(str(cpf)) == 11:
        return True
    else:
        return False


def verify(cpf):
    cds = generate_cds(cpf)
    numbers = [int(x) for x in str(cpf)]
    if cds[0] == numbers[9] and cds[1] == numbers[10]:
        print('CPF válido\n')
    else:
        print('CPF inválido. Dígitos de controle esperados: {}\n'.format(cds))


def verify_lencd(cpf):
    if len(str(cpf)) == 9:
        return True
    else:
        return False


def generate_last(cpf):
    generate_cds(cpf)
