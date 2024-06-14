	
############################ data segment ################################
	.data
prompt:	.asciiz "Enter your name (FIRST LAST):"
newline:.asciiz "\n"
name:	.space 101 
first:	.space 101
last:	.space 101
comma:	.asciiz ", "
space: 	.asciiz " "
msg: 	.asciiz " reversed is "
############################ code segment ################################

	.text
	.globl main

main: 
	la $a0, prompt	
	li $v0, 4	#print prompt to user
	syscall
	
	la $a0, name	
	li $a1, 101
	li $v0, 8	#read name string
	syscall
	
	la $a0, newline
	li $v0, 4	#print newline
	syscall
			
	la $a0, name	#load name into $a0
	la $a1, first	#load first into $a1
	
	lb $s0, ($a0)
	li $s1, 32	#asci value for space
	
first_loop: 			
	beq $s0, $s1, continue	#if space is found continue
	
	sb $s0, ($a1)
	
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	
	lb $s0, ($a0)

	j first_loop		
continue:
	li $a1, '\0'	#place NULL terminator
	
	addi $a0, $a0, 1 #skip space
	lb $s0, ($a0)

	la $a1, last	#load address of last into $a1
	li $s1, '\n'
	
last_loop:
	beq $s0, $s1, end	#if \n is found continue
	
	sb $s0, ($a1)
	
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	
	lb $s0, ($a0)

	j last_loop	
end:
	li $a1, '\0'	#place Null terminator
	
	
	la $a0, first	#print first name
	li $v0, 4
	syscall	
			
	la $a0, space
	li $v0, 4
	syscall
				
	la $a0, last	#print last name
	li $v0, 4
	syscall			
	
	la $a0, msg	#print msg
	li $v0, 4
	syscall
	
	la $a0, last
	li $v0, 4
	syscall
	
	la $a0, comma
	li $v0, 4
	syscall
	
	la $a0, first
	li $v0, 4
	syscall
	
	la $a0, newline
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall
	