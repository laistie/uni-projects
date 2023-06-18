.include "macros_io.asm"

.data
filename: .asciiz "atv7ex3dados.txt"
error: .asciiz "ERRO: arquivo não encontrado!\n"
buffer: .space 1
blankSpace: .asciiz " "

.text

# $t7: contador de numeros no vetor
# $s0: posição i
# $s7: ponteiro do arquivo

main:
	li $t0, 100
	calloc($t0, $a3) # $a3: ponteiro para o vetor de números lidos no arquivo
	print_str("Insira a posição i a ser lida: ")
	scan_int($s0)
	
file_read:
	file_openR(filename, $s7)
	
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
			add $t7, $t7, 1
			li $t1, 0
			beqz $t2, return
			j reading
	return:
		file_close($s7)
	
search_array:
	li $t3, 0
	file_openW(filename) # $s6: file descriptor
	
	print_str("\nValores do array até a posição i: ")
	li $t9, 10
	loop_array:
		sll $t4, $t3, 2
		add $t4, $t4, $a3
		lw $t1, 0($t4)
		print_int($t1)
		print_str(" ")
		bne $t3, $s0, copy
		add $t1, $t1, 1
	copy:
		blt $t1, 9, unitario
		blt $t1, 99, decimal
	update_loop:
		li $t1, 32
		file_write_chr($s6, $t1)
		add $t3, $t3, 1
		blt $t3, $t7, loop_array
	j end

unitario:
	add $t1, $t1, 48
	file_write_chr($s6, $t1)
	j update_loop

decimal:
	div $t1, $t9
	mflo $t2
	add $t2, $t2, 48
	file_write_chr($s6, $t2)
	mfhi $t1
	j unitario	
						
end:	
	file_close($s6)
	terminate
