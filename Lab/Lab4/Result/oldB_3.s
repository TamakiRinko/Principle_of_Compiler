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

isPrime:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -24
  lw $t0, -8($fp)
  lw $t1, -4($fp)
  li $t2, 4
  div $t1, $t2
  mflo $t0
  sw $t0, -12($fp)
  sw $t0, -8($fp)
  lw $t0, -16($fp)
  li $t0, 2
  sw $t0, -16($fp)
label1:
  lw $t0, -16($fp)
  lw $t1, -12($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -20($fp)
  lw $t1, -4($fp)
  lw $t2, -16($fp)
  div $t1, $t2
  mflo $t0
  lw $t1, -24($fp)
  mul $t1, $t0, $t2
  sw $t1, -24($fp)
  sw $t0, -20($fp)
  lw $t0, -4($fp)
  lw $t1, -24($fp)
  beq $t0, $t1, label4
  j label5
label4:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label5:
  lw $t0, -16($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -16($fp)
  j label1
label3:
  li $t0, 1
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
isRever:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -92
  lw $t0, -4($fp)
  sw $t0, -8($fp)
  lw $t0, -52($fp)
  li $t0, 0
  sw $t0, -52($fp)
  lw $t0, -56($fp)
  li $t0, 0
  sw $t0, -56($fp)
label6:
  lw $t0, -8($fp)
  li $t1, 0
  bne $t0, $t1, label7
  j label8
label7:
  lw $t0, -60($fp)
  lw $t1, -52($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -64($fp)
  addi $t4, $fp, -48
  add $t2, $t4, $t0
  sw $t0, -60($fp)
  lw $t0, -68($fp)
  lw $t3, -8($fp)
  li $t4, 10
  div $t3, $t4
  mflo $t0
  lw $t4, -72($fp)
  li $t5, 10
  mul $t4, $t0, $t5
  sw $t0, -68($fp)
  lw $t0, -76($fp)
  sub $t0, $t3, $t4
  sw $t4, -72($fp)
  sw $t0, 0($t2)
  sw $t2, -64($fp)
  sw $t0, -76($fp)
  li $t0, 10
  div $t3, $t0
  mflo $t3
  sw $t3, -8($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -52($fp)
  j label6
label8:
  lw $t0, -52($fp)
  li $t1, 1
  addi $t0, $t0, -1
  sw $t0, -52($fp)
label9:
  lw $t0, -56($fp)
  lw $t1, -52($fp)
  bne $t0, $t1, label10
  j label11
label10:
  lw $t0, -80($fp)
  lw $t1, -56($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -84($fp)
  addi $t3, $fp, -48
  add $t1, $t3, $t0
  sw $t1, -84($fp)
  sw $t0, -80($fp)
  lw $t0, -88($fp)
  lw $t1, -52($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -92($fp)
  addi $t3, $fp, -48
  add $t1, $t3, $t0
  sw $t1, -92($fp)
  sw $t0, -88($fp)
  lw $t0, -84($fp)
  lw $t1, 0($t0)
  lw $t2, -92($fp)
  lw $t3, 0($t2)
  bne $t1, $t3, label12
  j label13
label12:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label13:
  lw $t0, -56($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -56($fp)
  lw $t0, -52($fp)
  li $t1, 1
  addi $t0, $t0, -1
  sw $t0, -52($fp)
  j label9
label11:
  li $t0, 1
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -24
  lw $t0, -4($fp)
  li $t0, 100
  lw $t1, -8($fp)
  li $t1, 110
  sw $t1, -8($fp)
  sw $t0, -12($fp)
  sw $t0, -4($fp)
label14:
  lw $t0, -12($fp)
  lw $t1, -8($fp)
  blt $t0, $t1, label15
  j label16
label15:
  lw $t0, -12($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal isPrime
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
  lw $t0, -16($fp)
  li $t1, 1
  beq $t0, $t1, label17
  j label18
label17:
  lw $t0, -12($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
label18:
  lw $t0, -12($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal isRever
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -20($fp)
  move $t0, $v0
  sw $t0, -20($fp)
  lw $t0, -20($fp)
  li $t1, 1
  beq $t0, $t1, label19
  j label20
label19:
  lw $t0, -24($fp)
  li $t1, 0
  lw $t2, -12($fp)
  sub $t0, $t1, $t2
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -24($fp)
label20:
  lw $t0, -12($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -12($fp)
  j label14
label16:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
