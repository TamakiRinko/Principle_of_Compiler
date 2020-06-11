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
  addi $sp, $sp, -20
  lw $t0, -4($fp)
  li $t0, 1
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t0, 1
  sw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -12($fp)
  li $t1, 1
  blt $t0, $t1, label1
  j label2
label1:
  li $t0, 0
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label3
label2:
  lw $t0, -12($fp)
  li $t1, 1
  beq $t0, $t1, label4
  j label6
label6:
  lw $t0, -12($fp)
  li $t1, 2
  beq $t0, $t1, label4
  j label5
label4:
  li $t0, 1
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label7
label5:
  lw $t0, -12($fp)
  li $t1, 2
  bgt $t0, $t1, label8
  j label9
label8:
  lw $t0, -16($fp)
  li $t0, 3
  sw $t0, -16($fp)
label10:
  lw $t0, -16($fp)
  lw $t1, -12($fp)
  ble $t0, $t1, label11
  j label12
label11:
  lw $t0, -20($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  add $t0, $t1, $t2
  sw $t0, -8($fp)
  sw $t0, -20($fp)
  sw $t2, -4($fp)
  lw $t0, -16($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -16($fp)
  j label10
label12:
  lw $t0, -20($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
label9:
label7:
label3:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra