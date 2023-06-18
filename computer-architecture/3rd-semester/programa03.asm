.data
	inputText: .asciiz "Insira um valor n: "
	sumText: .asciiz "sum = "
	squares: #int squares[64]
		.align 2
		.space 256
	
.text
	main:
		#print do inputText
		li $v0, 4
		la $a0, inputText
		syscall
		
		#leitura do número n
		li $v0, 5
		syscall
		move $t0, $v0 #$t0 = n
		
		#set de variaveis auxiliares
		move $t1, $zero #contador dos loops
		move $t2, $zero #acumulador sum
		move $t4, $zero #contador alinhado para a posição atual do vetor squares
					
	storeValues:
		beq $t1, $t0, updateCounters #se $t1 = $t0, jump para updateCounters
		mul $a0, $t1, $t1 #$a0 = $t1 * $t1
		sw $a0, squares($t4) #squares[$t4] = $a0
		addi $t1, $t1, 1 #$t1++
		addi $t4, $t4, 4 #$t4 += 4
		j storeValues
	
	updateCounters:
		move $t1, $zero
		move $t4, $zero
	
	computeSum:
		beq  $t1, $t0, endProgram #se $t1 = $t0, jump para endProgram
		lw $a0, squares($t4) #$a0 = squares($t4)
		add $t2, $t2, $a0 #$t2 += $a0
		addi $t1, $t1, 1 #$t1++
		addi $t4, $t4, 4 #$t4 += 4
		j computeSum
		
	endProgram:
		#print de sumText
		li $v0, 4
		la $a0, sumText
		syscall
		
		#print de sum
		li $v0, 1
		move $a0, $t2
		syscall
		
		#fim do programa
		li $v0, 10
		syscall
