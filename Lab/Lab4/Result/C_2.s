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

mod:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -20
  lw $t0, -12($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  div $t1, $t2
  mflo $t0
  lw $t3, -16($fp)
  mul $t3, $t0, $t2
  sw $t0, -12($fp)
  lw $t0, -20($fp)
  sub $t0, $t1, $t3
  sw $t3, -16($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  sw $t0, -20($fp)
IsLeap:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -16
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  li $t0, 400
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -8($fp)
  move $t0, $v0
  sw $t0, -8($fp)
  lw $t0, -8($fp)
  li $t1, 0
  beq $t0, $t1, label1
  j label3
label3:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  li $t0, 4
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -12($fp)
  li $t1, 0
  beq $t0, $t1, label4
  j label2
label4:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  li $t0, 100
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
  lw $t0, -16($fp)
  li $t1, 0
  bne $t0, $t1, label1
  j label2
label1:
  li $t0, 1
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  j label5
label2:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label5:
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -84
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t0, 0
  sw $t0, -8($fp)
  lw $t0, -32($fp)
  addi $t2, $fp, -28
  li $t3, 0
  addi $t0, $t2, 0
  li $t1, 0
  sw $t1, 0($t0)
  sw $t0, -32($fp)
  lw $t0, -36($fp)
  addi $t2, $fp, -28
  li $t3, 4
  addi $t0, $t2, 4
  li $t1, 31
  sw $t1, 0($t0)
  sw $t0, -36($fp)
  lw $t0, -40($fp)
  addi $t2, $fp, -28
  li $t3, 8
  addi $t0, $t2, 8
  li $t1, 28
  sw $t1, 0($t0)
  sw $t0, -40($fp)
  lw $t0, -44($fp)
  addi $t2, $fp, -28
  li $t3, 12
  addi $t0, $t2, 12
  li $t1, 31
  sw $t1, 0($t0)
  sw $t0, -44($fp)
  lw $t0, -48($fp)
  addi $t2, $fp, -28
  li $t3, 16
  addi $t0, $t2, 16
  li $t1, 30
  sw $t1, 0($t0)
  sw $t0, -48($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -52($fp)
  move $t0, $v0
  sw $t0, -52($fp)
  lw $t0, -56($fp)
  li $t0, 1900
  sw $t0, -56($fp)
label6:
  lw $t0, -56($fp)
  lw $t1, -52($fp)
  blt $t0, $t1, label7
  j label8
label7:
  lw $t0, -56($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal IsLeap
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -60($fp)
  move $t0, $v0
  sw $t0, -60($fp)
  lw $t0, -60($fp)
  li $t1, 0
  bne $t0, $t1, label9
  j label10
label9:
  lw $t0, -4($fp)
  li $t1, 366
  addi $t0, $t0, 366
  sw $t0, -4($fp)
  j label11
label10:
  lw $t0, -4($fp)
  li $t1, 365
  addi $t0, $t0, 365
  sw $t0, -4($fp)
label11:
  lw $t0, -56($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -56($fp)
  j label6
label8:
  lw $t0, -52($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal IsLeap
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -64($fp)
  move $t0, $v0
  sw $t0, -64($fp)
  lw $t0, -64($fp)
  li $t1, 0
  bne $t0, $t1, label12
  j label13
label12:
  lw $t0, -68($fp)
  addi $t2, $fp, -28
  li $t3, 8
  addi $t0, $t2, 8
  li $t1, 29
  sw $t1, 0($t0)
  sw $t0, -68($fp)
label13:
  lw $t0, -56($fp)
  li $t0, 1
  sw $t0, -56($fp)
label14:
  lw $t0, -56($fp)
  li $t1, 5
  blt $t0, $t1, label15
  j label16
label15:
  lw $t0, -72($fp)
  lw $t1, -56($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -76($fp)
  addi $t4, $fp, -28
  add $t2, $t4, $t0
  sw $t0, -72($fp)
  lw $t0, -4($fp)
  lw $t3, 0($t2)
  add $t0, $t0, $t3
  sw $t0, -4($fp)
  sw $t2, -76($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -56($fp)
  j label14
label16:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  li $t0, 7
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -80($fp)
  move $t0, $v0
  sw $t0, -80($fp)
  lw $t0, -84($fp)
  li $t1, 14
  lw $t2, -80($fp)
  sub $t0, $t1, $t2
  li $t1, 5
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -84($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra