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

process:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -100
  lw $t0, -8($fp)
  li $t0, 3
  li $t0, 36
  lw $t1, -12($fp)
  lw $t2, -4($fp)
  li $t3, 321
  mul $t1, $t2, $t3
  lw $t3, -16($fp)
  li $t4, 2
  mul $t3, $t1, $t4
  sw $t1, -12($fp)
  lw $t1, -20($fp)
  mul $t1, $t2, $t0
  lw $t4, -24($fp)
  add $t4, $t3, $t1
  sw $t3, -16($fp)
  sw $t1, -20($fp)
  lw $t1, -28($fp)
  sub $t1, $t4, $t2
  sw $t4, -24($fp)
  lw $t3, -32($fp)
  mul $t3, $t0, $t2
  lw $t4, -36($fp)
  add $t4, $t1, $t3
  sw $t1, -28($fp)
  sw $t3, -32($fp)
  lw $t1, -40($fp)
  mul $t1, $t0, $t0
  lw $t3, -44($fp)
  add $t3, $t4, $t1
  sw $t4, -36($fp)
  sw $t1, -40($fp)
  lw $t1, -48($fp)
  add $t1, $t3, $t2
  sw $t3, -44($fp)
  lw $t3, -52($fp)
  add $t3, $t1, $t2
  sw $t1, -48($fp)
  lw $t1, -56($fp)
  li $t4, 23
  addi $t1, $t3, -23
  sw $t3, -52($fp)
  li $t3, 45
  addi $t0, $t1, 45
  sw $t1, -56($fp)
  lw $t1, -60($fp)
  li $t3, 3
  div $t0, $t3
  mflo $t1
  lw $t3, -64($fp)
  li $t4, 336
  addi $t3, $t1, 336
  sw $t1, -60($fp)
  lw $t1, -68($fp)
  li $t4, 12
  mul $t1, $t2, $t4
  lw $t4, -72($fp)
  li $t5, 4
  div $t1, $t5
  mflo $t4
  sw $t1, -68($fp)
  lw $t1, -76($fp)
  sub $t1, $t3, $t4
  sw $t3, -64($fp)
  sw $t4, -72($fp)
  lw $t3, -80($fp)
  li $t4, 60
  addi $t3, $t1, -60
  sw $t1, -76($fp)
  lw $t1, -84($fp)
  li $t4, 12
  div $t0, $t4
  mflo $t1
  lw $t4, -88($fp)
  li $t5, 24
  mul $t4, $t1, $t5
  sw $t1, -84($fp)
  lw $t1, -92($fp)
  add $t1, $t3, $t4
  sw $t3, -80($fp)
  sw $t4, -88($fp)
  lw $t3, -96($fp)
  li $t4, 36
  addi $t3, $t1, 36
  sw $t1, -92($fp)
  li $t1, 1
  addi $t0, $t3, 1
  sw $t3, -96($fp)
  lw $t1, -100($fp)
  li $t3, 24
  addi $t1, $t2, 24
  li $t2, 1
  addi $t0, $t1, 1
  sw $t1, -100($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  sw $t0, -8($fp)
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -156
  lw $t0, -4($fp)
  li $t0, 13
  lw $t1, -8($fp)
  li $t1, 20
  lw $t2, -12($fp)
  li $t2, 15
  lw $t3, -16($fp)
  add $t3, $t0, $t1
  lw $t4, -20($fp)
  add $t4, $t3, $t2
  sw $t3, -16($fp)
  sw $t4, -24($fp)
  sw $t4, -20($fp)
  lw $t3, -28($fp)
  mul $t3, $t0, $t1
  lw $t4, -32($fp)
  li $t5, 2
  div $t2, $t5
  mflo $t4
  lw $t5, -36($fp)
  add $t5, $t3, $t4
  sw $t3, -28($fp)
  sw $t4, -32($fp)
  sw $t5, -40($fp)
  sw $t5, -36($fp)
  lw $t3, -44($fp)
  sub $t3, $t0, $t1
  lw $t4, -48($fp)
  sub $t4, $t3, $t2
  sw $t3, -44($fp)
  lw $t3, -56($fp)
  li $t3, 42
  sw $t3, -56($fp)
  lw $t3, -60($fp)
  li $t3, 0
  sw $t3, -60($fp)
  lw $t3, -64($fp)
  add $t3, $t0, $t1
  sw $t0, -4($fp)
  sw $t1, -8($fp)
  lw $t0, -68($fp)
  add $t0, $t3, $t2
  sw $t3, -64($fp)
  sw $t2, -12($fp)
  lw $t1, -72($fp)
  li $t2, 2000
  addi $t1, $t0, 2000
  sw $t0, -68($fp)
  sub $t4, $t1, $t4
  sw $t4, -52($fp)
  sw $t4, -48($fp)
  sw $t1, -72($fp)
label1:
  lw $t0, -76($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  add $t0, $t1, $t2
  sw $t0, -76($fp)
  lw $t0, -76($fp)
  lw $t1, -52($fp)
  bge $t0, $t1, label3
  lw $t0, -80($fp)
  lw $t1, -60($fp)
  li $t2, 12
  mul $t0, $t1, $t2
  lw $t1, -84($fp)
  lw $t2, -56($fp)
  add $t1, $t2, $t0
  sw $t0, -80($fp)
  lw $t0, -88($fp)
  li $t3, 4
  addi $t0, $t1, 4
  sw $t1, -84($fp)
  lw $t1, -92($fp)
  li $t3, 5
  addi $t1, $t0, 5
  sw $t0, -88($fp)
  li $t0, 2
  addi $t2, $t1, 2
  sw $t2, -56($fp)
  sw $t1, -92($fp)
  lw $t0, -52($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -96($fp)
  move $t0, $v0
  sw $t0, -96($fp)
  lw $t0, -100($fp)
  li $t1, 2
  lw $t2, -4($fp)
  mul $t0, $t1, $t2
  lw $t1, -104($fp)
  lw $t3, -96($fp)
  add $t1, $t3, $t0
  sw $t0, -100($fp)
  lw $t0, -108($fp)
  lw $t3, -52($fp)
  sub $t0, $t1, $t3
  sw $t1, -104($fp)
  lw $t1, -112($fp)
  lw $t3, -12($fp)
  lw $t4, -24($fp)
  mul $t1, $t3, $t4
  lw $t3, -116($fp)
  add $t3, $t0, $t1
  sw $t3, -116($fp)
  sw $t0, -108($fp)
  sw $t1, -112($fp)
  lw $t0, -60($fp)
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  lw $t1, -120($fp)
  li $t3, 3
  addi $t1, $t0, 3
  sw $t0, -60($fp)
  li $t0, 1
  addi $t1, $t1, -1
  li $t0, 3
  addi $t1, $t1, 3
  li $t0, 6
  addi $t1, $t1, -6
  sw $t1, -120($fp)
  sw $t2, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -124($fp)
  move $t0, $v0
  sw $t0, -124($fp)
  lw $t0, -128($fp)
  lw $t1, -4($fp)
  li $t2, 3
  addi $t0, $t1, 3
  lw $t1, -132($fp)
  li $t2, 2
  addi $t1, $t0, -2
  sw $t0, -128($fp)
  lw $t0, -136($fp)
  li $t2, 1
  addi $t0, $t1, -1
  sw $t1, -132($fp)
  sw $t0, -12($sp)
  sw $t0, -136($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -140($fp)
  move $t0, $v0
  sw $t0, -140($fp)
  lw $t0, -124($fp)
  lw $t1, -140($fp)
  bne $t0, $t1, label5
  lw $t0, -144($fp)
  lw $t1, -52($fp)
  li $t2, 2
  addi $t0, $t1, -2
  li $t2, 1
  addi $t1, $t0, 1
  sw $t1, -52($fp)
  sw $t0, -144($fp)
label5:
  lw $t0, -148($fp)
  lw $t1, -4($fp)
  li $t2, 2
  addi $t0, $t1, 2
  li $t2, 1
  addi $t1, $t0, 1
  sw $t1, -4($fp)
  sw $t0, -148($fp)
  j label1
label3:
  lw $t0, -120($fp)
  lw $t1, -56($fp)
  li $t2, 12
  addi $t0, $t1, -12
  sw $t0, -120($fp)
label6:
  lw $t0, -120($fp)
  lw $t1, -56($fp)
  bge $t0, $t1, label8
  lw $t0, -52($fp)
  li $t1, 58
  lw $t2, -4($fp)
  addi $t0, $t2, 58
  sw $t0, -52($fp)
  lw $t0, -116($fp)
  lw $t1, -56($fp)
  li $t3, 12
  addi $t0, $t1, -12
  lw $t3, -120($fp)
  li $t4, 1
  addi $t3, $t3, 1
  sw $t3, -120($fp)
  sw $t1, -116($fp)
  lw $t0, -60($fp)
  lw $t1, -8($fp)
  add $t0, $t2, $t1
  sw $t0, -60($fp)
  lw $t0, -12($fp)
  add $t0, $t2, $t1
  sw $t0, -12($fp)
  j label6
label8:
  lw $t0, -52($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  add $t1, $t1, $t2
  add $t2, $t1, $t2
  lw $t3, -12($fp)
  add $t3, $t1, $t2
  add $t0, $t1, $t2
  lw $t4, -116($fp)
  add $t4, $t1, $t2
  sw $t1, -4($fp)
  sw $t2, -8($fp)
  lw $t1, -152($fp)
  add $t1, $t3, $t0
  sw $t3, -12($fp)
  sw $t0, -52($fp)
  lw $t0, -156($fp)
  add $t0, $t1, $t4
  sw $t1, -152($fp)
  sw $t4, -116($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -156($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra