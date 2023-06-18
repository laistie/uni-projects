.include "macros_io.asm"

.data
filename: .asciiz "atv6dados.txt"
error: .asciiz "ERRO: arquivo não encontrado!\n"
buffer: .space 1

.text
# $a3: ponteiro do vetor
# $s0: maior valor
# $s1: menor valor
# $s2: número de elementos pares
# $s3: número de elementos ímpares
# $s4: soma dos elementos
# $s5: produto dos elementos
# $s6: ponteiro do arquivo
# $s7: quantidade de caracteres lidos
# $t5: constante 2 e registrador auxiliar para armazenar o resto das divisoes
# $t7: tamanho do vetor

main:
	li $t0, 100
	calloc($t0, $a3) # $a3 = ponteiro para o vetor de números lidos no arquivo
	li $s1, 9999
	li $s5, 1
	
	jal file_read
	
	print_str("\n\nMaior valor: ")
	print_int($s0)
	
	print_str("\nMenor valor: ")
	print_int($s1)
	
	print_str("\nQuantidade de elementos impares: ")
	print_int($s3)
	
	print_str("\nQuantidade de elementos pares: ")
	print_int($s2)
	
	print_str("\nValores em ordem crescente: ")
	li $t3, 0
	sub $t6, $t7, 1
	jal sort_asc
	jal print_array
	
	print_str("\nValores em ordem decrescente: ")
	li $t3, 0
	jal sort_desc
	jal print_array
	
	print_str("\nSoma dos elementos: ")
	print_int($s4)
	
	print_str("\nProduto dos elementos: ")
	print_int($s5)
	
	print_str("\nNumero de caracteres do arquivo: ")
	print_int($s7)
	
	terminate
	
file_read:
	file_openR(filename)
	# leitura do arquivo
	print_str("Valores lidos no arquivo: ")
	la $a1, buffer # $a1 =  buffer de entrada
	li $a2, 1 # 1 caractere por leitura
	reading:
		move $a0, $s6 # $a0 = file descriptor
		li $v0, 14 # código para leitura do arquivo
		syscall # realiza a leitura de um caractere
		beqz $v0, next # se EOF, termina a leitura
		lb $t0, ($a1) # carrega o caractere lido
		add $s7, $s7, 1 # atualizacao do acumulador de caracteres
		beq $t0, 32, next # se houver espaco
		beq $t0, 10, next # /n
		beq $t0, 13, next # /r -> ignora, carriage return
		subi $t0, $t0, 48 # char -> int
		mul $t1, $t1, 10 # casa decimal para esquerda
		add $t1, $t1, $t0 # soma com o valor da unidade lido
		j reading
	next:
		move $t2, $v0
		print_int($t1)				
		print_str(" ")
		
		# armazenamento dos valores lidos no arquivo em um vetor alocado ($a3)
		sll $t4, $t3, 2
		add $t4, $t4, $a3
		blt $s0, $t1, maior # branch se elemento atual de $s0 < $t1
		back_menor:
			bgt $s1 $t1, menor # branch se elemento atual de $s1 > $t1
		store:
			sw $t1, 0($t4)
			addi $t3, $t3, 1
		
		add $s4, $s4, $t1 # acumulador de soma de valores lidos
		mul $s5, $s5, $t1 # acumulador de multiplicacao de valores lidos
		
		bnez $t1, parimpar # branch se elemento atual != 0, verificacao de pares e impares
		
		reset:
			add $t7, $t7, 1
			li $t1, 0
			beqz $t2, return
			j reading
	return:
		file_close($s6)
		jr $ra
		
maior:
	move $s0, $t1
	j back_menor
	
menor:
	move $s1, $t1
	j store
	
parimpar:		
	li $t5, 2
	div $t1, $t5
	mfhi $t5 # $t5 = resto da divisão	
	beqz $t5, par
	add $s3, $s3, 1
	j reset
	
par:
	add $s2, $s2, 1
	j reset
	
sort_asc:
	sll $t4, $t3, 2
	add $t4, $t4, $a3
	lw $t1, 0($t4)
	lw $t2, 4($t4)
	
	ble $t1, $t2, default_asc
	
	move $t5, $t1
	sw $t2, 0($t4)
	sw $t1, 4($t4) 
	
	default_asc:
		add $t3, $t3, 1
		blt $t3, $t6, sort_asc
	
	li $t3, 0
	add $t0, $t0, 1
	blt $t0, $t7, sort_asc
	li $t0, 0
	jr $ra
	
sort_desc:
	sll $t4, $t3, 2
	add $t4, $t4, $a3
	lw $t1, 0($t4)
	lw $t2, 4($t4)
	
	bge $t1, $t2, default_desc
	
	move $t5, $t1
	sw $t2, 0($t4)
	sw $t1, 4($t4) 
	
	default_desc:
		add $t3, $t3, 1
		blt $t3, $t6, sort_desc
	
	li $t3, 0
	add $t0, $t0, 1
	blt $t0, $t7, sort_desc
	li $t0, 0
	jr $ra	

print_array:
	li $t3, 0
	loop_print:
		sll $t4, $t3, 2
		add $t4, $t4, $a3
		lw $t1, 0($t4)
		print_int($t1)
		print_str(" ")
		add $t3, $t3, 1
		blt $t3, $t7, loop_print
	jr $ra
