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
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($fp)
  move $t0, $v0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t1, -8($fp)
  move $t1, $v0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t2, -12($fp)
  move $t2, $v0
  sw $t2, -12($fp)
  lw $t2, -16($fp)
  add $t2, $t0, $t1
  sw $t2, -16($fp)
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  lw $t0, -16($fp)
  lw $t1, -12($fp)
  bgt $t0, $t1, label4
  j label2
label4:
  lw $t0, -20($fp)
  lw $t1, -8($fp)
  lw $t2, -12($fp)
  add $t0, $t1, $t2
  sw $t0, -20($fp)
  lw $t0, -20($fp)
  lw $t1, -4($fp)
  bgt $t0, $t1, label3
  j label2
label3:
  lw $t0, -24($fp)
  lw $t1, -4($fp)
  lw $t2, -12($fp)
  add $t0, $t1, $t2
  sw $t0, -24($fp)
  lw $t0, -24($fp)
  lw $t1, -8($fp)
  bgt $t0, $t1, label1
  j label2
label1:
  lw $t0, -28($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  add $t0, $t1, $t2
  lw $t1, -32($fp)
  lw $t2, -12($fp)
  add $t1, $t0, $t2
  sw $t1, -32($fp)
  sw $t0, -28($fp)
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  beq $t0, $t1, label7
  j label6
label7:
  lw $t0, -4($fp)
  lw $t1, -12($fp)
  beq $t0, $t1, label5
  j label6
label5:
  lw $t0, -36($fp)
  li $t0, 1
  sw $t0, -36($fp)
  j label8
label6:
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  beq $t0, $t1, label9
  j label12
label12:
  lw $t0, -4($fp)
  lw $t1, -12($fp)
  beq $t0, $t1, label9
  j label11
label11:
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  beq $t0, $t1, label9
  j label10
label9:
  lw $t0, -36($fp)
  li $t0, 2
  sw $t0, -36($fp)
  j label13
label10:
  lw $t0, -40($fp)
  li $t0, 0
  sw $t0, -40($fp)
  lw $t0, -44($fp)
  lw $t1, -4($fp)
  mul $t0, $t1, $t1
  lw $t1, -48($fp)
  lw $t2, -8($fp)
  mul $t1, $t2, $t2
  lw $t2, -52($fp)
  add $t2, $t0, $t1
  sw $t2, -52($fp)
  sw $t0, -44($fp)
  sw $t1, -48($fp)
  lw $t0, -56($fp)
  lw $t1, -12($fp)
  mul $t0, $t1, $t1
  sw $t0, -56($fp)
  lw $t0, -52($fp)
  lw $t1, -56($fp)
  beq $t0, $t1, label18
  j label19
label18:
  lw $t0, -40($fp)
  li $t0, 1
  sw $t0, -40($fp)
label19:
  lw $t0, -40($fp)
  li $t1, 0
  bne $t0, $t1, label14
  j label17
label17:
  lw $t0, -60($fp)
  li $t0, 0
  sw $t0, -60($fp)
  lw $t0, -64($fp)
  lw $t1, -4($fp)
  mul $t0, $t1, $t1
  lw $t1, -68($fp)
  lw $t2, -12($fp)
  mul $t1, $t2, $t2
  lw $t2, -72($fp)
  add $t2, $t0, $t1
  sw $t2, -72($fp)
  sw $t0, -64($fp)
  sw $t1, -68($fp)
  lw $t0, -76($fp)
  lw $t1, -8($fp)
  mul $t0, $t1, $t1
  sw $t0, -76($fp)
  lw $t0, -72($fp)
  lw $t1, -76($fp)
  beq $t0, $t1, label20
  j label21
label20:
  lw $t0, -60($fp)
  li $t0, 1
  sw $t0, -60($fp)
label21:
  lw $t0, -60($fp)
  li $t1, 0
  bne $t0, $t1, label14
  j label16
label16:
  lw $t0, -80($fp)
  li $t0, 0
  sw $t0, -80($fp)
  lw $t0, -84($fp)
  lw $t1, -8($fp)
  mul $t0, $t1, $t1
  lw $t1, -88($fp)
  lw $t2, -12($fp)
  mul $t1, $t2, $t2
  lw $t2, -92($fp)
  add $t2, $t0, $t1
  sw $t2, -92($fp)
  sw $t0, -84($fp)
  sw $t1, -88($fp)
  lw $t0, -96($fp)
  lw $t1, -4($fp)
  mul $t0, $t1, $t1
  sw $t0, -96($fp)
  lw $t0, -92($fp)
  lw $t1, -96($fp)
  beq $t0, $t1, label22
  j label23
label22:
  lw $t0, -80($fp)
  li $t0, 1
  sw $t0, -80($fp)
label23:
  lw $t0, -80($fp)
  li $t1, 0
  bne $t0, $t1, label14
  j label15
label14:
  lw $t0, -36($fp)
  li $t0, 3
  sw $t0, -36($fp)
  j label24
label15:
  lw $t0, -36($fp)
  li $t0, 0
  sw $t0, -36($fp)
label24:
label13:
label8:
  lw $t0, -36($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -32($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label25
label2:
  lw $t0, -100($fp)
  li $t1, 0
  li $t2, 1
  addi $t0, $t1, -1
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -100($fp)
label25:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra