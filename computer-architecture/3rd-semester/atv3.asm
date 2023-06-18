.data
	insertText: .asciiz "Insira um número n: "
	notText: .asciiz " não"
	perfectText: .asciiz " é número perfeito"
	
.text
	main:
		li $t1, 1 #$t1 = 1, contador do loop
		move $t3, $zero #$t3 = zero, acumulador para divisores de n
		
		#print do texto "Insira um número n"
		li $v0, 4
		la $a0, insertText
		syscall
		
		#armazenamento do número n
		li $v0, 5
		syscall
		move $t0, $v0
		sub $t2, $t0, $t1 #t2 = n - 1, limite do loop
		
		j divisores
		
	divisores: #loop
		bgt $t1, $t2, verifica
		div $t0, $t1
		mfhi $s1 #$s1 = resto de n / posição atual do loop
		beq $s1, $zero, addDivisor #se resto = 0, então n é divisível por $t1
		add $t1, $t1, 1 #senão, apenas atualiza contador do loop
		j divisores
		
	addDivisor:
		add $t3, $t3, $t1 #acumula valor atual do contador do loop em $t3
		add $t1, $t1, 1 #atualiza o contador do loop
		j divisores #volta para o loop
		
	verifica:
		#print do número n
		li $v0, 1
		move $a0, $t0
		syscall
		
		beq $t3, $t0, posVerifica #se o valor no acumulador é igual, printa direto a mensagem
		
		#senão, printa "não" antes da mensagem
		li $v0, 4
		la $a0, notText
		syscall
		
		j posVerifica
		
	posVerifica:
		#print do texto "é número perfeito"
		li $v0, 4
		la $a0, perfectText
		syscall
		
		#fim do programa
		li $v0, 10
		syscall
