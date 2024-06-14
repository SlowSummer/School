############################ data segment ################################
	.data
prompt1:	.asciiz "Enter the multiplicand: "

prompt2:	.asciiz "Enter the multiplier: "

multiplicand:	.word

multiplier:	.word	

resultmsg:	.asciiz "*"

equal:		.asciiz "="
############################ code segment ################################
	.text
	.globl main

main:
	la $a0, prompt1	#prompt multiplicand
	li $v0, 4
	syscall
	
	la $t1, multiplicand
	li $v0, 5	#read multiplicand
	syscall
	add $t1, $v0, $zero
	
	la $a0, prompt2	#prompt multiplier
	li $v0, 4
	syscall
	
	la $t2, multiplier
	li $v0, 5	#read multiplier
	syscall
	add $t2, $v0, $zero
		
	li $t0, 1
	li $t3, 2	
	
	move $a0, $t1
	move $a1, $t2
	
	beq $a1, $t0, base_case	#if multiplier is base case
	beq $a1, $t3, double	#if multiplier is 2
	
	jal recur	
	
bc_return:
	move $a0, $t1
	move $a1, $t2
	move $a2, $v0
	
	li $v0, 1
	syscall 
	
	la $a0, resultmsg
	li $v0, 4
	syscall 
	
	move $a0, $t2
	li $v0, 1
	syscall
	
	la $a0, equal 
	li $v0, 4
	syscall
	
	move $a0, $a2
	
	li $v0, 1
	syscall
	
	li $v0, 10	#exit
	syscall


recur:		
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	addi $sp, $sp, -4
	sw $a1, 0($sp)


	addi $a1, $a1, -1  #multiplier -= 1


	slti $t5, $a1, 1

	bne $t5, $zero, return

		
	jal recur	   #recursive call $a1 = multiplier - 1
	
	addi $v0, $zero, 1
	
	lw $a1, ($sp)	   
    	addi $sp, $sp, 4
    	
    	lw $ra, 0($sp)
    	addi $sp, $sp, 4
    	
    	mul $v0,$a0, $a1  #(multiplier - 1) * muliplicand 
	add $v0, $v0, $a0  #multiplicand + (multiplier - 1) * multiplicand

return:	
	lw $a1, 0($sp)
	addi $sp, $sp, 4
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
		

	jr $ra	
	
base_case:
	add $v0, $zero, $a0
	
	j bc_return	
	
double:
	add $v0, $a0, $a0
	
	j bc_return
	