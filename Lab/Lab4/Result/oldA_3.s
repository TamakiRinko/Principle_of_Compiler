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
  addi $sp, $sp, -36
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -8($fp)
  move $t0, $v0
  sw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  bgt $t0, $t1, label1
  j label2
label1:
  lw $t0, -8($fp)
  sw $t0, -16($fp)
  j label3
label2:
  lw $t0, -12($fp)
  sw $t0, -16($fp)
label3:
label4:
  lw $t0, -4($fp)
  li $t1, 0
  beq $t0, $t1, label5
  j label6
label5:
  lw $t0, -20($fp)
  lw $t1, -16($fp)
  lw $t2, -8($fp)
  div $t1, $t2
  mflo $t0
  lw $t1, -24($fp)
  mul $t1, $t0, $t2
  sw $t1, -24($fp)
  sw $t0, -20($fp)
  lw $t0, -16($fp)
  lw $t1, -24($fp)
  beq $t0, $t1, label7
  j label8
label7:
  lw $t0, -28($fp)
  lw $t1, -16($fp)
  lw $t2, -12($fp)
  div $t1, $t2
  mflo $t0
  lw $t1, -32($fp)
  mul $t1, $t0, $t2
  sw $t1, -32($fp)
  sw $t0, -28($fp)
  lw $t0, -16($fp)
  lw $t1, -32($fp)
  beq $t0, $t1, label9
  j label10
label9:
  lw $t0, -16($fp)
  sw $t0, -36($fp)
  lw $t0, -4($fp)
  li $t0, 1
  sw $t0, -4($fp)
  j label11
label10:
  lw $t0, -16($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -16($fp)
label11:
  j label12
label8:
  lw $t0, -16($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -16($fp)
label12:
  j label4
label6:
  lw $t0, -36($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
