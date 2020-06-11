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
  addi $sp, $sp, -100
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
label1:
  lw $t0, -4($fp)
  li $t1, 5
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -28($fp)
  lw $t1, -4($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -32($fp)
  addi $t4, $fp, -24
  add $t2, $t4, $t0
  sw $t0, -28($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -36($fp)
  move $t0, $v0
  sw $t0, 0($t2)
  sw $t2, -32($fp)
  sw $t0, -36($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -4($fp)
  j label1
label3:
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
label4:
  lw $t0, -4($fp)
  li $t1, 4
  blt $t0, $t1, label5
  j label6
label5:
  lw $t0, -40($fp)
  lw $t1, -4($fp)
  li $t2, 1
  addi $t0, $t1, 1
  sw $t0, -40($fp)
label7:
  lw $t0, -40($fp)
  li $t1, 5
  blt $t0, $t1, label8
  j label9
label8:
  lw $t0, -44($fp)
  lw $t1, -4($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -48($fp)
  addi $t3, $fp, -24
  add $t1, $t3, $t0
  sw $t1, -48($fp)
  sw $t0, -44($fp)
  lw $t0, -52($fp)
  lw $t1, -40($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -56($fp)
  addi $t3, $fp, -24
  add $t1, $t3, $t0
  sw $t1, -56($fp)
  sw $t0, -52($fp)
  lw $t0, -48($fp)
  lw $t1, 0($t0)
  lw $t2, -56($fp)
  lw $t3, 0($t2)
  bgt $t1, $t3, label10
  j label11
label10:
  lw $t0, -60($fp)
  lw $t1, -4($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -64($fp)
  addi $t4, $fp, -24
  add $t2, $t4, $t0
  sw $t0, -60($fp)
  lw $t0, -68($fp)
  lw $t0, 0($t2)
  sw $t2, -64($fp)
  lw $t2, -72($fp)
  li $t3, 4
  mul $t2, $t1, $t3
  lw $t1, -76($fp)
  addi $t4, $fp, -24
  add $t1, $t4, $t2
  sw $t2, -72($fp)
  lw $t2, -80($fp)
  lw $t3, -40($fp)
  li $t4, 4
  mul $t2, $t3, $t4
  lw $t4, -84($fp)
  addi $t6, $fp, -24
  add $t4, $t6, $t2
  sw $t2, -80($fp)
  lw $t2, 0($t4)
  sw $t2, 0($t1)
  sw $t1, -76($fp)
  sw $t4, -84($fp)
  lw $t1, -88($fp)
  li $t2, 4
  mul $t1, $t3, $t2
  lw $t2, -92($fp)
  addi $t4, $fp, -24
  add $t2, $t4, $t1
  sw $t1, -88($fp)
  sw $t0, 0($t2)
  sw $t2, -92($fp)
  sw $t0, -68($fp)
label11:
  lw $t0, -40($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -40($fp)
  j label7
label9:
  lw $t0, -4($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -4($fp)
  j label4
label6:
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
label12:
  lw $t0, -4($fp)
  li $t1, 5
  blt $t0, $t1, label13
  j label14
label13:
  lw $t0, -96($fp)
  lw $t1, -4($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -100($fp)
  addi $t4, $fp, -24
  add $t2, $t4, $t0
  sw $t0, -96($fp)
  lw $t0, 0($t2)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -100($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -4($fp)
  j label12
label14:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra