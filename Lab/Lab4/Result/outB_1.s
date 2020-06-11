.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

hanoi:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -48
  lw $t0, -4($fp)
  li $t1, 1
  bne $t0, $t1, label2
  lw $t0, -20($fp)
  lw $t1, -8($fp)
  li $t2, 1000000000
  mul $t0, $t1, $t2
  lw $t1, -24($fp)
  lw $t2, -16($fp)
  add $t1, $t0, $t2
  sw $t0, -20($fp)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t1, -24($fp)
  j label3
label2:
  lw $t0, -28($fp)
  lw $t1, -4($fp)
  li $t2, 1
  addi $t0, $t1, -1
  sw $t0, -12($sp)
  sw $t0, -28($fp)
  lw $t0, -8($fp)
  sw $t0, -16($sp)
  lw $t0, -16($fp)
  sw $t0, -20($sp)
  lw $t0, -12($fp)
  sw $t0, -24($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal hanoi
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -32($fp)
  move $t0, $v0
  sw $t0, -32($fp)
  lw $t0, -36($fp)
  lw $t1, -8($fp)
  li $t2, 1000000000
  mul $t0, $t1, $t2
  lw $t2, -40($fp)
  lw $t3, -16($fp)
  add $t2, $t0, $t3
  sw $t0, -36($fp)
  move $a0, $t2
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -40($fp)
  lw $t0, -44($fp)
  lw $t2, -4($fp)
  li $t4, 1
  addi $t0, $t2, -1
  sw $t0, -12($sp)
  sw $t0, -44($fp)
  lw $t0, -12($fp)
  sw $t0, -16($sp)
  sw $t1, -20($sp)
  sw $t3, -24($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal hanoi
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -48($fp)
  move $t0, $v0
  sw $t0, -48($fp)
label3:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -8
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($fp)
  move $t0, $v0
  sw $t0, -12($sp)
  sw $t0, -4($fp)
  li $t0, 1
  sw $t0, -16($sp)
  li $t0, 2
  sw $t0, -20($sp)
  li $t0, 3
  sw $t0, -24($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal hanoi
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -8($fp)
  move $t0, $v0
  sw $t0, -8($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra