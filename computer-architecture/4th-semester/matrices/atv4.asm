.data
	readN: .asciiz "Insira o tamanho n da matriz quadrada nxm (n >= m): "
	readM: .asciiz "Insira o tamanho m da matriz quadrada nxm (n >= m): "
	comma: .asciiz ", "
	colon: .asciiz ": "
	space: .asciiz " "
	newLine: .asciiz "\n"
	matrix: .asciiz "===MATRIZ DE ENTRADA==="
	vowels: .byte 'a', 'e', 'i', 'o', 'u'
	upperText: .asciiz  "===MATRIZ COM VOGAIS EM MAIÚSCULO==="
	vowelsText: .asciiz "Número do vogais da matriz de entrada: "
	repetitionText: .asciiz "Caracteres que se repetem mais de 3x na matriz de entrada: "
	notSquareText: .asciiz "A matriz não é de ordem nxn, então não é possível imprimir a diagonal principal"
	diagonal: .asciiz "Diagonal principal: "
	
.text
	main:
		jal leituraN
		jal leituraM
		
		j leitura
		
		li $v0, 1
		move $a0, $t0				
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
		
		li $v0, 1
		move $a0, $t1				
		syscall
	
	fim: #fim do programa
		li $v0, 10
		syscall
		
	leituraN: #leitura do número de linhas da matriz
		#print do texto "Insira o tamanho n da matriz nxm:"
		li $v0, 4
		la $a0, readN
		syscall
		#armazenamento do numero n em t0
		li $v0, 5
		syscall
		move $t0, $v0
		jr $ra
	
	leituraM: #leitura do número de colunas da matriz
		#print do texto "Insira o tamanho m da matriz nxm:"
		li $v0, 4
		la $a0, readM
		syscall
		#armazenamento do numero n em t1
		li $v0, 5
		syscall
		move $t1, $v0
		aloca:
			#alocação dinamica de memoria para matriz
			mul $a0, $t0, $t1
			li $v0, 9
			syscall
			move $s0, $v0 #$s0 -> endereco de memoria da matriz
		jr $ra
		
	leitura: #leitura dos elementos da matriz 
		li $t2, 0 #$t2 = 0, atualizacao do contador para linha
		forLine:
			li $t3, 0 #$t3 = 0, atualizacao do contador para coluna
			forColumn:
				jal indice
				jal escrita
				jal printNewLine
				add $t3, $t3, 1 #atualiza o contador do loop
				blt $t3, $t1, forColumn #verificacao da condicao do loop
			add $t2, $t2, 1 
			blt $t2, $t0, forLine
		j print
	
	indice: #print do índice do elemento atual da matriz
		#print da atual linha
		li $v0, 1
		move $a0, $t2
		syscall
		#print da vírgula
		li $v0, 4
		la $a0, comma
		syscall
		#print da atual coluna
		li $v0, 1
		move $a0, $t3
		syscall
		#print dos dois pontos
		li $v0, 4
		la $a0, colon
		syscall
	
		jr $ra
	
	escrita: #leitura e escrita do elemento da matriz
		mul $t5, $t2, $t0 #$t5 = n * posicao atual da linha
		add $t5, $t5, $t3 #$t5 = $t5 + posicao atual da coluna
		add $t5, $s0, $t5 #$t5 = $t5 + $s0
		#leitura do elemento
		li $v0, 12
		syscall
		sb $v0, 0($t5) #armazenamento do caracter lido
		jr $ra
	
	print:	
		jal printNewLine
		jal printNewLine
		#print do texto "===MATRIZ DE ENTRADA==="
		li $v0, 4
		la $a0, matrix
		syscall
		jal printNewLine
		li $t2, 0 #$t2 = 0, atualizacao do contador para linha
		forLinePrint:
			li $t3, 0 #$t3 = 0, atualizacao do contador para coluna
			forColumnPrint:
				jal alignMatrix
				#print do elemento atual da matriz
				li $v0, 11
				lb $a0, 0($t5)
				syscall
				#print do espaço
				li $v0, 4
				la $a0, space
				syscall
	
				add $t3, $t3, 1 #atualiza o contador do loop
				blt $t3, $t1, forColumnPrint #verificacao da condicao do loop
			jal printNewLine
			add $t2, $t2, 1 
			blt $t2, $t0, forLinePrint
		j to_upper
			
	alignMatrix:
		mul $t5, $t2, $t0 #$t5 = n * posicao atual da linha
		add $t5, $t5, $t3 #$t5 = $t5 + posicao atual da coluna
		add $t5, $s0, $t5 #$t5 = $t5 + $s0
		jr $ra

	printNewLine: #print de nova linha
		li $v0, 4
		la $a0, newLine
		syscall
		jr $ra
	
	to_upper:
		jal printNewLine
		#print do texto "===MATRIZ COM VOGAIS EM MAIÚSCULO==="
		li $v0, 4
		la $a0, upperText
		syscall
		jal printNewLine
		li $t2, 0 #$t2 = 0, atualizacao do contador para linha
		forLineUpper:
			li $t3, 0 #$t3 = 0, atualizacao do contador para coluna
			forColumnUpper:
				jal alignMatrix
				#print do elemento atual da matriz
				li $v0, 11
				lb $a0, 0($t5)
				jal to_upper_vowel
				
				#print do espaço
				li $v0, 4
				la $a0, space
				syscall
	
				add $t3, $t3, 1 #atualiza o contador do loop
				blt $t3, $t1, forColumnUpper #verificacao da condicao do loop
			jal printNewLine
			add $t2, $t2, 1 
			blt $t2, $t0, forLineUpper
		j number_vowels

	to_upper_vowel:
		li $t4, 0 #$t4 = 0, atualicazao do contador do array de vogais
		li $t6, 5 #$t6 = 5, número de vogais
		for_upper:
			lb $a1, vowels($t4)
			beq $a0, $a1, uppercase
			add $t4, $t4, 1
			blt $t4, $t6, for_upper
		not_vowel: #subrotina para retornar ao loop
			syscall
			jr $ra
		uppercase: #subrotina caso a letra seja vogal
			sub $a0, $a0, 32
			syscall
			jr $ra
	
	number_vowels:
		jal printNewLine
		#print do texto "Número de vogais da matriz de entrada: "
		li $v0, 4
		la $a0, vowelsText
		syscall
		li $t2, 0 #$t2 = 0, atualizacao do contador para linha
		li $t7, 0 #$t7 = 0, acumulador do número de vogais
		forLineNumVowels:
			li $t3, 0 #$t3 = 0, atualizacao do contador para coluna
			forColumnNumVowels:
				jal alignMatrix
				#load do elemento atual da matriz
				li $v0, 11
				lb $a0, 0($t5)
				jal is_vowel
				add $t3, $t3, 1 #atualiza o contador do loop
				blt $t3, $t1, forColumnNumVowels #verificacao da condicao do loop
			add $t2, $t2, 1 
			blt $t2, $t0, forLineNumVowels
		li $v0, 1
		move $a0, $t7
		syscall
		jal printNewLine
		j charsRepetition
		
	is_vowel:
		li $t4, 0 #$t4 = 0, atualicazao do contador do array de vogais
		li $t6, 5 #$t6 = 5, número de vogais
		for_vowel:
			lb $a1, vowels($t4)
			beq $a0, $a1, add_vowel
			add $t4, $t4, 1
			blt $t4, $t6, for_vowel
			jr $ra
		add_vowel:
			add $t7, $t7, 1
			jr $ra
	
	charsRepetition:
		#print do texto "Caracteres que se repetem mais de 3x na matriz de entrada: "
		li $v0, 4
		la $a0, repetitionText
		syscall
		li $t2, 0 #$t2 = 0, atualizacao do contador para linha
		li $t3, 0 #$t3 = 0, atualizacao do contador para coluna
		forLineRepetition: #loop para percorrer a matriz
			forColumnRepetition:
				jal alignMatrix
				lb $a0, 0($t5) #load do elemento atual da matriz
				move $t4, $t2 #$t4 = i, armazenamento do número da linha do elemento a ser comparado
				move $t6, $t3 #$t4 = j, armazenamento do número da coluna do elemento a ser comparado
				li $t7, 0 #$t7 = 0, atualizacao do acumulador de repeticoes	
				j addLoopRep
				forRepCompare:
					jal alignMatrix
					lb $a1, 0($t5)
					beq $a0, $a1, addRepetition #comparacao do elemento atual com o fixo armazenado em $a0
					j addLoopRep
			forEndRepColumn:	
			move $t3, $t6
			add $t3, $t3, 1
			bge $t3, $t1, addColumnRep #jump caso o elemento de comparacao tenha chego no final da linha atual da matriz
			forEndRepLine:
			move $t2, $t4
			add $t2, $t2, 1 
			blt $t2, $t0, forLineRepetition #jump caso o elemento de comparacao tenha chego no final da matriz
			
			jal printNewLine
			beq $t0, $t1, printDP
			j notSquare

	addLoopRep: #atualizacao dos contadores de indice da matriz
		add $t3, $t3, 1 
		blt $t3, $t1, forRepCompare #jump caso ainda nao tenha chego no final da linha atual da matriz
		li $t3, 0 #fim da linha atual, reset do contador de coluna
		add $t2, $t2, 1
		blt $t2, $t0, forRepCompare #jump caso ainda nao tenha chego no final da matriz
		j forEndRepColumn #jump de atualizacao, fim da matriz atingido
	
	addColumnRep: 
		li $t3, 0
		add $t2, $t2, 1
		blt $t2, $t0, forLineRepetition
		j forEndRepLine
		
	addRepetition:
		add $t7, $t7, 1
		bge $t7, 3, printRep
		j forRepCompare
	
	printRep:
		li $v0, 11
		syscall
		#print do espaço	
		li $v0, 4
		la $a0, space
		syscall
	
		j forEndRepColumn
	
	printDP:
		#print do texto "Diagonal principal: "
		li $v0, 4
		la $a0, diagonal
		syscall
		li $t2, 0 #$t2 = 0, atualização do contador para linha
		forDP:
			move $t3, $t2
			jal alignMatrix
			li $v0, 11
			lb $a0, 0($t5)
			syscall
			li $v0, 4
			la $a0, space
			syscall
			add $t2, $t2, 1 
			blt $t2, $t0, forDP
		j fim
	
	notSquare: #print do texto "A matriz não é de ordem nxn, então não é possível imprimir a diagonal principal"
		li $v0, 4
		la $a0, notSquareText
		syscall
