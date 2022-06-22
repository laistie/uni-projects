import isbn10
import code13
import cpf


def verify_choice(value):
    if value != 1 and value != 2 and value != 3 and value != 4:
        return False
    else:
        return True


def verify_option(value):
    if value != 0 and value != 1 and value != 2 and value != 3 and value != 4:
        return False
    else:
        return True


print('\nAPLICAÇÕES DE CONGRUÊNCIA\n'
      '\n[1]ISBN 10\n[2]CÓDIGO DE BARRAS EAN-13\n[3]CPF\n[4]Sair\n')
choice = int(input('Selecione uma opção: '))
while not verify_choice(choice):
    choice = int(input('Favor inserir uma opção válida: '))

while choice != 4:
    # ISBN 10
    if choice == 1:
        print('\nISBN 10')
        isbn10.menu()
        option = int(input('Selecione uma opção: '))
        while not verify_option(option):
            option = int(input('Favor inserir uma opção válida: '))
        while option != 4:
            if option == 0:
                isbn10.description()
                isbn10.menu()
                option = int(input('Selecione uma opção: '))
                while not verify_option(option):
                    option = int(input('Favor inserir uma opção válida: '))
            elif option == 1:
                isbn10.random_code()
            elif option == 2:
                code = str(input('Insira o código ISBN (apenas números): '))
                while not isbn10.verify_len(code):
                    code = str(input('Leitura inválida. Insira o código ISBN (apenas números): '))
                isbn10.verify(code)
            else:
                code = str(input('Insira o código ISBN (apenas números): '))
                while not isbn10.verify_lencd(code):
                    code = str(input('Leitura inválida. Insira o código ISBN (apenas números): '))
                isbn10.generate_last(code)
            isbn10.menu()
            option = int(input('Selecione uma opção: '))
            while not verify_option(option):
                option = int(input('Favor inserir uma opção válida: '))

    # CÓDIGO DE BARRAS EAN-13
    elif choice == 2:
        print('\nCÓDIGO DE BARRAS EAN-13')
        code13.menu()
        option = int(input('Selecione uma opção: '))
        while not verify_option(option):
            option = int(input('Favor inserir uma opção válida: '))
        while option != 4:
            if option == 0:
                code13.description()
                code13.menu()
                option = int(input('Selecione uma opção: '))
                while not verify_option(option):
                    option = int(input('Favor inserir uma opção válida: '))
            elif option == 1:
                code13.random_code()
            elif option == 2:
                code = int(input('Insira o código de barras (apenas números): '))
                while not code13.verify_len(code):
                    code = int(input('Leitura inválida. Insira o código de barras (apenas números): '))
                code13.verify(code)
            else:
                code = int(input('Insira o código de barras (apenas números): '))
                while not code13.verify_lencd(code):
                    code = int(input('Leitura inválida. Insira o código de barras (apenas números) '))
                code13.generate_last(code)
            code13.menu()
            option = int(input('Selecione uma opção: '))
            while not verify_option(option):
                option = int(input('Favor inserir uma opção válida: '))

    # CPF
    else:
        print('\nCPF')
        cpf.menu()
        option = int(input('Selecione uma opção: '))
        while not verify_option(option):
            option = int(input('Favor inserir uma opção válida: '))
        while option != 4:
            if option == 0:
                cpf.description()
                cpf.menu()
                option = int(input('Selecione uma opção: '))
                while not verify_option(option):
                    option = int(input('Favor inserir uma opção válida: '))
            elif option == 1:
                cpf.random_cpf()
            elif option == 2:
                code = int(input('Insira o CPF (apenas números): '))
                while not cpf.verify_len(code):
                    code = int(input('Leitura inválida. Insira o CPF (apenas números): '))
                cpf.verify(code)
            else:
                code = int(input('Insira o CPF (apenas números): '))
                while not cpf.verify_lencd(code):
                    code = int(input('Leitura inválida. Insira o CPF (apenas números): '))
                cpf.generate_last(code)
            cpf.menu()
            option = int(input('Selecione uma opção: '))
            while not verify_option(option):
                option = int(input('Favor inserir uma opção válida: '))

    print('\nAPLICAÇÕES DE CONGRUÊNCIA\n'
          '\n[1]ISBN 10\n[2]CÓDIGO DE BARRAS EAN-13\n[3]CPF\n[4]Sair\n')
    choice = int(input('Selecione uma opção: '))
    while not verify_choice(choice):
        choice = int(input('Favor inserir uma opção válida: '))
