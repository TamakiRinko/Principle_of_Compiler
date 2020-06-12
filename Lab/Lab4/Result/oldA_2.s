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

main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -24
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($fp)
  move $t0, $v0
  sw $t0, -4($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -8($fp)
  move $t0, $v0
  sw $t0, -8($fp)
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  bgt $t0, $t1, label1
  j label2
label1:
  lw $t0, -12($fp)
  lw $t1, -8($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  sw $t0, -12($fp)
  lw $t0, -4($fp)
  lw $t1, -12($fp)
  bgt $t0, $t1, label3
  j label4
label3:
  lw $t0, -4($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label5
label4:
  lw $t0, -16($fp)
  lw $t1, -8($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -16($fp)
label5:
  j label6
label2:
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  beq $t0, $t1, label7
  j label8
label7:
  lw $t0, -8($fp)
  li $t1, 100
  bgt $t0, $t1, label9
  j label10
label9:
  li $t0, 100
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label11
label10:
  lw $t0, -8($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
label11:
  j label12
label8:
  lw $t0, -20($fp)
  lw $t1, -4($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  sw $t0, -20($fp)
  lw $t0, -20($fp)
  lw $t1, -8($fp)
  blt $t0, $t1, label13
  j label14
label13:
  lw $t0, -8($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label15
label14:
  lw $t0, -24($fp)
  lw $t1, -4($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -24($fp)
label15:
label12:
label6:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
