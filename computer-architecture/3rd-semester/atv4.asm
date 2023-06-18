.data
	array: .align 2 # alinhamento da palavra na posição correta
		.space 200 # array de no máximo 50 inteiros
	semiprimos: .word 4, 6, 9, 10, 14, 15, 21, 22, 25, 26, 33, 34, 35, 38, 39, 46, 49, 51, 55, 57, 58, 62, 65, 69, 74, 77, 82, 85, 86, 87, 91, 93, 94, 95
	inputTxt: .asciiz "Insira o valor n: "
	ordemTxt: .asciiz "Vetor ordenado: "
	somaParesTxt: .asciiz "A soma dos elementos pares do vetor é: "
	chaveTxt: .asciiz "Insira uma chave k: "
	cChaveTxt: .asciiz "O número de elementos que são maiores que k e menores que 2k é: "
	dChaveTxt: .asciiz "O número de elementos iguais à chave k é: "
	perfeitosTxt: .asciiz "Soma dos números perfeitos: "
	semiprimosTxt: .asciiz "Soma dos números semiprimos: "
	space: .asciiz " "
	newLine: .asciiz "\n"
		
.text
	main:
		# print do input Txt
		li $v0, 4
		la $a0, inputTxt
		syscall
		
		#leitura do número n
		li $v0, 5
		syscall
		move $t0, $v0 # t0 = n
		
		move $t1, $zero # contador do loop
		move $t4, $zero # contador alinhado para a posição atual do vetor
		
		jal leitura # leitura do vetor
		jal atualizaContadores # atualização dos contadores
		
		# a) ordene o vetor em ordem crescente e apresente o vetor ordenado
		jal ordenaVetor # ordenação do vetor
		jal atualizaContadores # atualização dos contadores
		li $v0, 4
		la $a0, newLine
		syscall	
		li $v0, 4
		la $a0, ordemTxt
		syscall
		jal print # apresentação do vetor ordenado
		jal atualizaContadores # atualização dos contadores
		
		# b) realize a soma dos elementos pares do vetor e apresente o valor
		jal somaPares # soma dos elementos pares do vetor
		jal atualizaContadores # atualização dos contadores
		
		# c) leia uma chave k e apresente o número de elementos do vetor que são maiores que k e menores que 2k
		li $v0, 4
		la $a0, newLine
		syscall	
		li $v0, 4
		la $a0, chaveTxt
		syscall
		li $v0, 5
		syscall
		move $t7, $v0 # t7 = n
		jal cChave
		jal atualizaContadores # atualização dos contadores
		
		# d) leia uma chave k e apresente o número de elementos iguais à chave lida
		li $v0, 4
		la $a0, newLine
		syscall
		li $v0, 4
		la $a0, chaveTxt
		syscall
		li $v0, 5
		syscall
		move $t7, $v0
		jal dChave
		jal atualizaContadores # atualização dos contadores
		
		# e) apresentar o resultado da soma dos números inteiros perfeitos menos a soma dos números inteiros semiprimos
		li $t1, 1
		move $t7, $zero
		jal verificaPerfeitos
		jal atualizaContadores # atualização dos contadores
		move $t7, $zero
		
		li $v0, 10
		syscall
		
	leitura:
		li $v0, 5
		syscall
		sw $v0, array($t4)
		addi $t1, $t1, 1 # $t1++
		addi $t4, $t4, 4 # $t4 += 4
		blt $t1, $t0, leitura
		jr $ra
		
	atualizaContadores:
		move $t1, $zero
		move $t3, $zero
		move $t4, $zero
		move $t5, $zero
		jr $ra
	
		
	ordenaVetor: # $t3 = i, $t4 = j
		for:
			lw $t2, array($t3)
			lw $t6, array($t4)
			blt $t2, $t6, if # if array[i] < array[j]
			atualiza:
				addi $t4, $t4, 4 # $t4 += 4
			addi $t5, $t5, 1 # $t5++
			blt $t5, $t0, for
		addi $t1, $t1, 1 # $t1++
		addi $t3, $t3, 4
		move $t4, $zero
		move $t5, $zero
		blt $t1, $t0, ordenaVetor
		jr $ra
	
	if:
		sw $t6, array($t3) # array[i] = array[j]
		sw $t2, array($t4) # array[j] = aux 
		j atualiza

	somaPares:
		addi $t6, $zero, 2
		lw $t2, array($t4)
		div $t2, $t6
		mfhi $s0
		beq $s0, $zero, addSomaPares
		atualizaSomaPares:
			addi $t4, $t4, 4
		addi $t1, $t1, 1 # t1++
		blt $t1, $t0, somaPares
		li $v0, 4
		la $a0, newLine
		syscall
		li $v0, 4
		la $a0, somaParesTxt
		syscall
		li $v0, 1
		move $a0, $t3
		syscall
		jr $ra
	
	addSomaPares:
		add $t3, $t3, $t2
		j atualizaSomaPares
		
		
	cChave:
		lw $t2, array($t4)
		bgt $t2, $t7, maiorK
		atualizaSomaC:
			addi $t4, $t4, 4
		addi $t1, $t1, 1 # t1++
		blt $t1, $t0, cChave
		li $v0, 4
		la $a0, cChaveTxt
		syscall
		li $v0, 1
		move $a0, $t3
		syscall
		jr $ra
	
	maiorK:
		addi $t6, $zero, 2
		mult $t7, $t6
		mflo $s0
		blt $t2, $s0, menor2K
		j atualizaSomaC
		
	menor2K:
		addi $t3, $t3, 1
		j atualizaSomaC
	
	dChave:
		lw $t2, array($t4)
		beq $t7, $t2, addDChave
		atualizaSomaD:
			addi $t4, $t4, 4
		addi $t1, $t1, 1
		blt $t1, $t0, dChave
		li $v0, 4
		la $a0, dChaveTxt
		syscall
		li $v0, 1
		move $a0, $t3
		syscall
		jr $ra
	
	addDChave:
		addi $t3, $t3, 1
		j atualizaSomaD
		
	verificaPerfeitos:
		lw $t2, array($t4)
		sub $s1, $t2, 1
		
		verificacao:	
			# verifica se o elemento da posição atual do vetor é perfeito
			bgt $t1, $s1, proxPerfeito # se $t1 (contador) > $s1 (n - 1)
			div $t2, $t1 # n / contador
			mfhi $s0 # $s0 = resto de n / posição atual do loop
			beq $s0, $zero, addDivisor # se resto = 0, então n é divisível por $t1
			addi $t1, $t1, 1 # senão, atualiza o contador do loop
			j verificacao # retorna para o começo do loop
		
		# atualiza variáveis para verificação do próximo elemento
		proxPerfeito:
			beq $t3, $t2, addPerfeito
		posVerifica: 
			addi $t4, $t4, 4
			move $t3, $zero
			addi $t7, $t7, 1 # $t7 contador de posições do vetor
			li $t1, 1 # reset de contador para loop
			blt $t7, $t0, verificaPerfeitos
	
		li $v0, 4
		la $a0, newLine
		syscall
		li $v0, 4
		la $a0, perfeitosTxt
		syscall
		li $v0, 1
		move $a0, $t5
		syscall
		jr $ra
		
	addDivisor:
		add $t3, $t3, $t1 # acumula valor atual do contador do loop em $t3
		addi $t1, $t1, 1 # atualiza o contador do loop
		j verificacao #volta para o loop
	
	addPerfeito:
		add $t5, $t5, $t2
		j posVerifica
	
	verificaSemiprimos:
		lw $t2, array($t4)
		
		verificaSP:
			lw $t6, semiprimos($t3)
			bgt $t6, $t2, proxSP
			beq $t2, $t6, addSemiprimo
			addi $t3, $t3, 4
			
		proxSP:
			addi $t3, $t3, 4
			j verificaSP
			
		posVerificaSP:
			addi $t4, $t4, 4 
			move $t3, $zero
			addi $t7, $t7, 1 # $t7 contador de posições do vetor
			blt $t7, $t0, verificaSemiprimos # se $t7 > $t0 (fim do vetor)
		
		li $v0, 4
		la $a0, newLine
		syscall
		li $v0, 4
		la $a0, semiprimosTxt
		syscall
		li $v0, 1
		move $a0, $t5
		syscall
		jr $ra
				
			
	addSemiprimo:
		add $t5, $t5, $t2
		addi $t3, $t3, 4
		j proxSP
	
	print:
		lw $t2, array($t4)
		li $v0, 1
		move $a0, $t2
		syscall
		addi $t1, $t1, 1 # $t1++
		addi $t4, $t4, 4 # $t4 += 4
		li $v0, 4
		la $a0, space
		syscall	
		blt $t1, $t0, print
		jr $ra
