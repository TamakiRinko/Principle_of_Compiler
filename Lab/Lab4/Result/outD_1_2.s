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
  addi $sp, $sp, -132
  lw $t0, -8($fp)
  li $t0, 3
  lw $t1, -12($fp)
  li $t2, 11
  li $t3, 3
  mul $t1, $t2, $t3
  lw $t2, -16($fp)
  li $t3, 2
  addi $t2, $t1, -2
  sw $t1, -12($fp)
  li $t1, 5
  addi $t0, $t2, 5
  sw $t2, -16($fp)
  lw $t1, -20($fp)
  lw $t2, -4($fp)
  li $t3, 321
  mul $t1, $t2, $t3
  lw $t3, -24($fp)
  li $t4, 2
  mul $t3, $t1, $t4
  sw $t1, -20($fp)
  lw $t1, -28($fp)
  mul $t1, $t2, $t0
  lw $t4, -32($fp)
  add $t4, $t3, $t1
  sw $t3, -24($fp)
  sw $t1, -28($fp)
  lw $t1, -36($fp)
  sub $t1, $t4, $t2
  sw $t4, -32($fp)
  lw $t3, -40($fp)
  mul $t3, $t0, $t2
  lw $t4, -44($fp)
  add $t4, $t1, $t3
  sw $t1, -36($fp)
  sw $t3, -40($fp)
  lw $t1, -48($fp)
  mul $t1, $t0, $t0
  lw $t3, -52($fp)
  add $t3, $t4, $t1
  sw $t4, -44($fp)
  sw $t1, -48($fp)
  lw $t1, -56($fp)
  add $t1, $t3, $t2
  sw $t3, -52($fp)
  lw $t3, -60($fp)
  add $t3, $t1, $t2
  sw $t1, -56($fp)
  lw $t1, -64($fp)
  li $t4, 23
  addi $t1, $t3, -23
  sw $t3, -60($fp)
  li $t3, 45
  addi $t0, $t1, 45
  sw $t1, -64($fp)
  lw $t1, -68($fp)
  li $t3, 3
  div $t0, $t3
  mflo $t1
  lw $t3, -72($fp)
  li $t4, 14
  li $t5, 24
  mul $t3, $t4, $t5
  lw $t4, -76($fp)
  add $t4, $t1, $t3
  sw $t1, -68($fp)
  sw $t3, -72($fp)
  lw $t1, -80($fp)
  li $t3, 12
  mul $t1, $t2, $t3
  lw $t3, -84($fp)
  li $t5, 4
  div $t1, $t5
  mflo $t3
  sw $t1, -80($fp)
  lw $t1, -88($fp)
  sub $t1, $t4, $t3
  sw $t4, -76($fp)
  sw $t3, -84($fp)
  lw $t3, -92($fp)
  li $t4, 20
  li $t5, 3
  mul $t3, $t4, $t5
  lw $t4, -96($fp)
  sub $t4, $t1, $t3
  sw $t1, -88($fp)
  sw $t3, -92($fp)
  lw $t1, -100($fp)
  li $t3, 12
  div $t0, $t3
  mflo $t1
  lw $t3, -104($fp)
  li $t5, 24
  mul $t3, $t1, $t5
  sw $t1, -100($fp)
  lw $t1, -108($fp)
  add $t1, $t4, $t3
  sw $t4, -96($fp)
  sw $t3, -104($fp)
  lw $t3, -112($fp)
  li $t4, 12
  li $t5, 3
  mul $t3, $t4, $t5
  lw $t4, -116($fp)
  add $t4, $t1, $t3
  sw $t1, -108($fp)
  sw $t3, -112($fp)
  lw $t1, -120($fp)
  li $t3, 3
  li $t5, 2
  div $t3, $t5
  mflo $t1
  add $t0, $t4, $t1
  sw $t4, -116($fp)
  sw $t1, -120($fp)
  lw $t1, -124($fp)
  li $t3, 4
  li $t4, 6
  mul $t1, $t3, $t4
  lw $t3, -128($fp)
  add $t3, $t2, $t1
  sw $t1, -124($fp)
  lw $t1, -132($fp)
  li $t2, 3
  li $t4, 2
  div $t2, $t4
  mflo $t1
  add $t0, $t3, $t1
  sw $t3, -128($fp)
  sw $t1, -132($fp)
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
  addi $sp, $sp, -220
  lw $t0, -4($fp)
  li $t1, 5
  li $t2, 2
  div $t1, $t2
  mflo $t0
  lw $t1, -8($fp)
  li $t2, 14
  addi $t1, $t0, 14
  sw $t0, -4($fp)
  lw $t0, -12($fp)
  li $t2, 3
  addi $t0, $t1, -3
  sw $t1, -8($fp)
  lw $t1, -20($fp)
  li $t2, 7
  li $t3, 5
  mul $t1, $t2, $t3
  lw $t2, -24($fp)
  li $t3, 2
  div $t1, $t3
  mflo $t2
  sw $t1, -20($fp)
  lw $t1, -28($fp)
  li $t3, 3
  addi $t1, $t2, 3
  sw $t2, -24($fp)
  lw $t2, -36($fp)
  li $t3, 4
  li $t4, 5
  addi $t2, $t4, 4
  lw $t3, -40($fp)
  li $t4, 6
  addi $t3, $t2, 6
  sw $t2, -36($fp)
  lw $t2, -44($fp)
  li $t4, 1
  li $t5, 2
  div $t4, $t5
  mflo $t2
  lw $t4, -48($fp)
  sub $t4, $t3, $t2
  sw $t3, -40($fp)
  sw $t2, -44($fp)
  lw $t2, -56($fp)
  add $t2, $t0, $t1
  lw $t3, -60($fp)
  add $t3, $t2, $t4
  sw $t2, -56($fp)
  sw $t3, -64($fp)
  sw $t3, -60($fp)
  lw $t2, -68($fp)
  mul $t2, $t0, $t1
  lw $t3, -72($fp)
  li $t5, 2
  div $t4, $t5
  mflo $t3
  lw $t5, -76($fp)
  add $t5, $t2, $t3
  sw $t2, -68($fp)
  sw $t3, -72($fp)
  sw $t5, -80($fp)
  sw $t5, -76($fp)
  lw $t2, -84($fp)
  sub $t2, $t0, $t1
  lw $t3, -88($fp)
  sub $t3, $t2, $t4
  sw $t2, -84($fp)
  lw $t2, -96($fp)
  li $t2, 42
  sw $t2, -96($fp)
  lw $t2, -100($fp)
  li $t2, 0
  sw $t2, -100($fp)
  lw $t2, -104($fp)
  add $t2, $t0, $t1
  sw $t0, -16($fp)
  sw $t0, -12($fp)
  sw $t1, -32($fp)
  sw $t1, -28($fp)
  lw $t0, -108($fp)
  add $t0, $t2, $t4
  sw $t2, -104($fp)
  sw $t4, -52($fp)
  sw $t4, -48($fp)
  lw $t1, -112($fp)
  li $t2, 1000
  li $t4, 2
  mul $t1, $t2, $t4
  lw $t2, -116($fp)
  add $t2, $t0, $t1
  sw $t0, -108($fp)
  sw $t1, -112($fp)
  sub $t3, $t2, $t3
  sw $t3, -92($fp)
  sw $t3, -88($fp)
  sw $t2, -116($fp)
label1:
  lw $t0, -120($fp)
  lw $t1, -16($fp)
  lw $t2, -32($fp)
  add $t0, $t1, $t2
  sw $t0, -120($fp)
  lw $t0, -120($fp)
  lw $t1, -92($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -124($fp)
  lw $t1, -100($fp)
  li $t2, 12
  mul $t0, $t1, $t2
  lw $t1, -128($fp)
  lw $t2, -96($fp)
  add $t1, $t2, $t0
  sw $t0, -124($fp)
  lw $t0, -132($fp)
  li $t3, 4
  addi $t0, $t1, 4
  sw $t1, -128($fp)
  lw $t1, -136($fp)
  li $t3, 5
  addi $t1, $t0, 5
  sw $t0, -132($fp)
  lw $t0, -140($fp)
  li $t3, 7
  li $t4, 3
  div $t3, $t4
  mflo $t0
  add $t2, $t1, $t0
  sw $t2, -96($fp)
  sw $t1, -136($fp)
  sw $t0, -140($fp)
  lw $t0, -92($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -144($fp)
  move $t0, $v0
  sw $t0, -144($fp)
  lw $t0, -148($fp)
  li $t1, 2
  lw $t2, -16($fp)
  mul $t0, $t1, $t2
  lw $t1, -152($fp)
  lw $t3, -144($fp)
  add $t1, $t3, $t0
  sw $t0, -148($fp)
  lw $t0, -156($fp)
  lw $t3, -92($fp)
  sub $t0, $t1, $t3
  sw $t1, -152($fp)
  lw $t1, -160($fp)
  lw $t3, -52($fp)
  lw $t4, -64($fp)
  mul $t1, $t3, $t4
  lw $t3, -164($fp)
  add $t3, $t0, $t1
  sw $t3, -164($fp)
  sw $t0, -156($fp)
  sw $t1, -160($fp)
  lw $t0, -100($fp)
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  add $t0, $t0, $t0
  lw $t1, -168($fp)
  li $t3, 3
  addi $t1, $t0, 3
  sw $t0, -100($fp)
  li $t0, 1
  addi $t1, $t1, -1
  li $t0, 3
  addi $t1, $t1, 3
  lw $t0, -172($fp)
  li $t3, 3
  li $t4, 2
  mul $t0, $t3, $t4
  sub $t1, $t1, $t0
  sw $t1, -168($fp)
  sw $t0, -172($fp)
  sw $t2, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -176($fp)
  move $t0, $v0
  sw $t0, -176($fp)
  lw $t0, -180($fp)
  lw $t1, -16($fp)
  li $t2, 3
  addi $t0, $t1, 3
  lw $t1, -184($fp)
  li $t2, 2
  addi $t1, $t0, -2
  sw $t0, -180($fp)
  lw $t0, -188($fp)
  li $t2, 1
  addi $t0, $t1, -1
  sw $t1, -184($fp)
  sw $t0, -12($sp)
  sw $t0, -188($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -192($fp)
  move $t0, $v0
  sw $t0, -192($fp)
  lw $t0, -176($fp)
  lw $t1, -192($fp)
  beq $t0, $t1, label4
  j label5
label4:
  lw $t0, -196($fp)
  lw $t1, -92($fp)
  li $t2, 2
  addi $t0, $t1, -2
  li $t2, 1
  addi $t1, $t0, 1
  sw $t1, -92($fp)
  sw $t0, -196($fp)
label5:
  lw $t0, -200($fp)
  lw $t1, -16($fp)
  li $t2, 2
  addi $t0, $t1, 2
  li $t2, 1
  addi $t1, $t0, 1
  sw $t1, -16($fp)
  sw $t0, -200($fp)
  j label1
label3:
  lw $t0, -204($fp)
  li $t1, 3
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -168($fp)
  lw $t2, -96($fp)
  sub $t1, $t2, $t0
  sw $t1, -168($fp)
  sw $t0, -204($fp)
label6:
  lw $t0, -168($fp)
  lw $t1, -96($fp)
  blt $t0, $t1, label7
  j label8
label7:
  lw $t0, -208($fp)
  li $t1, 15
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -212($fp)
  li $t2, 2
  addi $t1, $t0, -2
  sw $t0, -208($fp)
  lw $t0, -92($fp)
  lw $t2, -16($fp)
  add $t0, $t1, $t2
  sw $t0, -92($fp)
  sw $t1, -212($fp)
  lw $t0, -164($fp)
  lw $t1, -96($fp)
  li $t3, 12
  addi $t0, $t1, -12
  lw $t3, -168($fp)
  li $t4, 1
  addi $t3, $t3, 1
  sw $t3, -168($fp)
  sw $t1, -164($fp)
  lw $t0, -100($fp)
  lw $t1, -32($fp)
  add $t0, $t2, $t1
  sw $t0, -100($fp)
  lw $t0, -52($fp)
  add $t0, $t2, $t1
  sw $t0, -52($fp)
  j label6
label8:
  lw $t0, -92($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t1, -16($fp)
  lw $t2, -32($fp)
  add $t1, $t1, $t2
  add $t2, $t1, $t2
  lw $t3, -52($fp)
  add $t3, $t1, $t2
  add $t0, $t1, $t2
  lw $t4, -164($fp)
  add $t4, $t1, $t2
  sw $t1, -16($fp)
  sw $t2, -32($fp)
  lw $t1, -216($fp)
  add $t1, $t3, $t0
  sw $t3, -52($fp)
  sw $t0, -92($fp)
  lw $t0, -220($fp)
  add $t0, $t1, $t4
  sw $t1, -216($fp)
  sw $t4, -164($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -220($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra