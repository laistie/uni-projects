.data
	inputA: .asciiz "A: "
	inputB: .asciiz "B: "
	textMult: .asciiz "múltiplos de A até AxB: "
	textSpace: .asciiz " "
	
.text

	main:
	li $t0, 1 #$t0 = 1, contador do loop
	j getA
	
	doMult:
		li $v0, 4
		la $a0, textMult #print do texto dos múltiplos
		syscall
		j loop
	
	loop:
		bgt $t0, $t2, exitProgram #encerra programa se $t0 > $t2
		mult $t1, $t0
		mflo $t4 #$t4 = $t1 * $t0
		li $v0, 1
		move $a0, $t4 #print de múltiplo de A
		syscall
		li $v0, 4
		la $a0, textSpace #print de espaço
		syscall
		addi $t0, $t0, 1 #$t0 = $t0 + 1
		j loop
	
	exitProgram: #sair do programa
		li $v0, 10
    		syscall
    	
    	getA: 
		li $v0, 4
		la $a0, inputA #print de texto "A: "
		syscall
		li $v0, 5 #lê input A
		syscall
		move $t1, $v0 #$t1 = A
		j checkA
    		
    	
	checkA: #verifica se A <= 0
		ble $t1, $zero, getA
		j getB
		
	getB:
		li $v0, 4
		la $a0, inputB #print de texto "B: "
		syscall	
		li $v0, 5 #lê input B
		syscall
		move $t2, $v0 #$t2 = B
		j checkB
		
	checkB: #verifica se B <= 0
		ble $t2, $zero, getB
		j doMult
