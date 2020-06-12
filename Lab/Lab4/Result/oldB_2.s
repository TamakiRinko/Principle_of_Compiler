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
  addi $sp, $sp, -160
  lw $t0, -4($fp)
  li $t0, 10
  sw $t0, -4($fp)
  lw $t0, -48($fp)
  li $t0, 0
  sw $t0, -48($fp)
  lw $t0, -52($fp)
  li $t0, 0
  sw $t0, -52($fp)
label1:
  lw $t0, -48($fp)
  li $t1, 10
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -56($fp)
  lw $t1, -48($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -60($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -56($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -64($fp)
  move $t0, $v0
  sw $t0, 0($t2)
  sw $t2, -60($fp)
  sw $t0, -64($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -48($fp)
  j label1
label3:
  lw $t0, -68($fp)
  lw $t1, -4($fp)
  li $t2, 2
  div $t1, $t2
  mflo $t0
  sw $t0, -68($fp)
label4:
  lw $t0, -68($fp)
  li $t1, 0
  bge $t0, $t1, label5
  j label6
label5:
  lw $t0, -52($fp)
  li $t0, 0
  sw $t0, -52($fp)
  lw $t0, -68($fp)
  sw $t0, -48($fp)
label7:
  lw $t0, -52($fp)
  li $t1, 0
  beq $t0, $t1, label8
  j label9
label8:
  lw $t0, -52($fp)
  li $t0, 1
  sw $t0, -52($fp)
  lw $t0, -72($fp)
  lw $t1, -48($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  lw $t2, -76($fp)
  li $t3, 1
  addi $t2, $t0, 1
  sw $t2, -76($fp)
  sw $t0, -72($fp)
  lw $t0, -80($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  lw $t1, -84($fp)
  li $t2, 2
  addi $t1, $t0, 2
  sw $t1, -84($fp)
  sw $t0, -80($fp)
  lw $t0, -76($fp)
  lw $t1, -4($fp)
  blt $t0, $t1, label10
  j label11
label10:
  lw $t0, -88($fp)
  lw $t1, -76($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -92($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t0, -88($fp)
  lw $t0, -96($fp)
  lw $t0, 0($t1)
  sw $t0, -96($fp)
  sw $t1, -92($fp)
  lw $t0, -84($fp)
  lw $t1, -4($fp)
  blt $t0, $t1, label14
  j label13
label14:
  lw $t0, -100($fp)
  lw $t1, -84($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -104($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -104($fp)
  sw $t0, -100($fp)
  lw $t0, -108($fp)
  lw $t1, -76($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -112($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -112($fp)
  sw $t0, -108($fp)
  lw $t0, -104($fp)
  lw $t1, 0($t0)
  lw $t2, -112($fp)
  lw $t3, 0($t2)
  blt $t1, $t3, label12
  j label13
label12:
  lw $t0, -116($fp)
  lw $t1, -84($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -120($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -116($fp)
  lw $t0, -96($fp)
  lw $t0, 0($t2)
  sw $t0, -96($fp)
  sw $t2, -120($fp)
  sw $t1, -76($fp)
label13:
  lw $t0, -124($fp)
  lw $t1, -48($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -128($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -128($fp)
  sw $t0, -124($fp)
  lw $t0, -128($fp)
  lw $t1, 0($t0)
  lw $t2, -96($fp)
  bgt $t1, $t2, label15
  j label16
label15:
  lw $t0, -52($fp)
  li $t0, 0
  sw $t0, -52($fp)
  lw $t0, -132($fp)
  lw $t1, -76($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -136($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -132($fp)
  lw $t0, -140($fp)
  lw $t3, -48($fp)
  li $t4, 4
  mul $t0, $t3, $t4
  lw $t4, -144($fp)
  addi $t6, $fp, -44
  add $t4, $t6, $t0
  sw $t0, -140($fp)
  lw $t0, 0($t4)
  sw $t0, 0($t2)
  sw $t2, -136($fp)
  sw $t4, -144($fp)
  lw $t0, -148($fp)
  li $t2, 4
  mul $t0, $t3, $t2
  lw $t2, -152($fp)
  addi $t5, $fp, -44
  add $t2, $t5, $t0
  sw $t0, -148($fp)
  lw $t0, -96($fp)
  sw $t0, 0($t2)
  sw $t2, -152($fp)
  sw $t1, -48($fp)
label16:
label11:
  j label7
label9:
  lw $t0, -68($fp)
  li $t1, 1
  addi $t0, $t0, -1
  sw $t0, -68($fp)
  j label4
label6:
  lw $t0, -48($fp)
  li $t0, 0
  sw $t0, -48($fp)
label17:
  lw $t0, -48($fp)
  lw $t1, -4($fp)
  blt $t0, $t1, label18
  j label19
label18:
  lw $t0, -156($fp)
  lw $t1, -48($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -160($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -156($fp)
  lw $t0, 0($t2)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -160($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -48($fp)
  j label17
label19:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
