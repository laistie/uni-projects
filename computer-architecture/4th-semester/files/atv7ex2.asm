.include "macros_io.asm"

.data
filename: .asciiz "atv7ex2dados.txt"
copy: .asciiz "atv7ex2-copia.txt"
error: .asciiz "ERRO: arquivo não encontrado!\n"
vowelReplacement: .byte '*'
buffer: .space 1
vowels: .byte 'a', 'e', 'i', 'o', 'u'
blankSpace: .asciiz " "

.text

main:

file_read:
	file_openR(filename, $s7) # $s7: reading file descriptor
	file_openW(copy) # $s6: writing file descriptor
	
	# leitura do arquivo
	li $a2, 1 # 1 caractere por leitura
	
	reading:
		move $a0, $s7 # $a0 = reading file descriptor
		la $a1, buffer # $a1 =  buffer de entrada
		li $v0, 14 # código para leitura do arquivo
		syscall # realiza a leitura de um caractere
		beqz $v0, next # se EOF, termina a leitura
		lb $t0, ($a1) # carrega o caractere lido
		beq $t0, 13, next # /r -> ignora, carriage return
		move $s2, $zero # atualizacao do contador para vetor com vogais
		for_check_vowel:
			lb $t1, vowels($s2)
			bne $t0, $t1, not_vowel
			file_write_chr($s6, vowelReplacement)
			j next
			not_vowel:
				add $s2, $s2, 1
				blt $s2, 5, for_check_vowel
			file_write_buffer($s6)
	next:
		move $t2, $v0
		beqz $t2, return
		j reading
	return:
		file_close($s6)
		file_close($s7)
	terminate
