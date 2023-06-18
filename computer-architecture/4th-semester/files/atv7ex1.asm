.include "macros_io.asm"
.include "macros_nums.asm"

.data
filename: .asciiz "atv7dados.txt"
error: .asciiz "ERRO: arquivo não encontrado!\n"
blankSpace: .asciiz " "
buffer: .space 20

.text

main:
	print_str("Insira um numero n: ")
	scan_int($t0)
	file_openW(filename)
	
	li $t1, 1
	for:
		bgt $t1, $t0, abort
		nump_verify($t1) # verificação se atual é primo
		bne $s1, 2, update_for # $s1: armazenamento de resposta da verificacao, se $s1 != 2, então o número não é primo
		add $t3, $t1, 2 # $t3 = número primo atual + 2
		nump_verify($t3) # verificação se atual + 2 é primo
		bne $s1, 2, update_for # $s1: armazenamento de resposta da verificacao, se $s1 != 2, então o número + 2 não é primo
		
		move $a0, $t1
		la $a1, buffer
		move $v0, $zero
		move $s1, $zero 
		int_to_str($a0) # conversão do número atual para string
		file_write_buffer($s6) # escreve o número no arquivo
		
		la $a1, blankSpace
		li $a2, 1
		li $v0, 15
		syscall
		
		update_for:
			add $t1, $t1, 1 # atualizacao do contador do loop
		j for
	abort:
	file_close($s6)
	terminate
