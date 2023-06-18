.include "macros_io.asm"

.data
filename: .asciiz "atv7ex4dados.txt"
oFilename: .asciiz "atv7ex4saida.txt"
error: .asciiz "ERRO: arquivo não encontrado!\n"
buffer: .space 1

.text

# $a3: ponteiro para o vetor de números lidos no arquivo
# $s1: dimensão m da matriz
# $s2: dimensão n da matriz
# $s3: quantidade de posições que serão anuladas
# $s4: variável auxiliar para linha
# $s5: variável auxiliar para coluna
# $s6: ponteiro para o arquivo de escrita
# $s7: ponteiro para o arquivo de leitura

main:
	li $t0, 100
	calloc($t0, $a3) # $a3: ponteiro
	
file_read:
	file_openR(filename, $s7) # $s7 ponteiro
	
	# leitura do arquivo
	print_str("Valores lidos no arquivo: ")
	la $a1, buffer # $a1 =  buffer de entrada
	li $a2, 1 # 1 caractere por leitura
	
	reading:
		move $a0, $s7 # $a0 = file descriptor
		li $v0, 14 # código para leitura do arquivo
		syscall # realiza a leitura de um caractere
		beqz $v0, next # se EOF, termina a leitura
		lb $t0, ($a1) # carrega o caractere lido
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
		store:
			sw $t1, 0($t4)
			addi $t3, $t3, 1
	
		reset:
			li $t1, 0
			beqz $t2, return
			j reading
	return:
		file_close($s7)

search_array:
	li $t3, 0 # $t3: contador
	
	print_str("\nValores dentro do array:\n")
	store_dimensions:
		store_m:
			sll $t4, $t3, 2
			add $t4, $t4, $a3
			lw $s1, 0($t4)
			print_int($s1)
			print_str(" ")
			add $t3, $t3, 1
		store_n:
			sll $t4, $t3, 2
			add $t4, $t4, $a3
			lw $s2, 0($t4)
			print_int($s2)
			print_str(" ")
			add $t3, $t3, 1
		store_pos:
			sll $t4, $t3, 2
			add $t4, $t4, $a3
			lw $s3, 0($t4)
			print_int($s3)
			print_str("\n")
			add $t3, $t3, 1
	
	file_openW(oFilename) # $s6: ponteiro
	li $t6, 48
	li $t7, 49
	li $t1, 0 # $t1: i = 0
			
	li $t5, 0 # $t5: contador para qntd de posições
	load_pos_array:
		bge $t5, $s3, update_for_j
		sll $t4, $t3, 2
		add $t4, $t4, $a3
		lw $s4, 0($t4) # $s4: auxiliar
		print_int($s4)
		print_str(" ")
		add $t3, $t3, 1
		
		sll $t4, $t3, 2
		add $t4, $t4, $a3
		lw $s5, 0($t4) # $s5: auxiliar
		print_int($s5)
		print_str("\n")
		add $t3, $t3, 1
		add $t5, $t5, 1
		bnez $t9, update_for_j
		
	for_print_m:
		bge $t1, $s1, end
		li $t2, 0 # $t2: j = 0
		for_print_n:
			bge $t2, $s2, update_for_i
			beq $t1, $s4, check_column
			default:
				file_write_chr($s6, $t7)
				li $t8, 32
				file_write_chr($s6, $t8)
				add $t9, $t9, 1
			update_for_j:
				add $t2, $t2, 1
				j for_print_n
		update_for_i:
			li $t8, 10
			file_write_chr($s6, $t8)
			add $t1, $t1, 1
			j for_print_m
			
check_column:
	bne $t2, $s5, default
	file_write_chr($s6, $t6)
	li $t8, 32
	file_write_chr($s6, $t8)
	add $t9, $t9, 1
	j load_pos_array
												
end:	
	file_close($s6)
	terminate
