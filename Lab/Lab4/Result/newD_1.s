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
  li $t0, 4
  lw $t1, -12($fp)
  lw $t2, -4($fp)
  li $t3, 12
  addi $t1, $t2, 12
  li $t3, 12
  addi $t1, $t2, 12
  sw $t1, -12($fp)
  lw $t1, -16($fp)
  li $t3, 0
  addi $t1, $t0, 0
  li $t3, 0
  addi $t0, $t1, 0
  sw $t1, -16($fp)
  lw $t1, -20($fp)
  li $t3, 1
  mul $t1, $t0, $t3
  li $t3, 1
  div $t1, $t3
  mflo $t0
  sw $t1, -20($fp)
  lw $t1, -24($fp)
  li $t3, 32
  addi $t1, $t0, 32
  lw $t3, -28($fp)
  li $t4, 4
  li $t5, 7
  mul $t3, $t4, $t5
  lw $t4, -32($fp)
  li $t5, 10
  div $t3, $t5
  mflo $t4
  sw $t3, -28($fp)
  sub $t0, $t1, $t4
  sw $t1, -24($fp)
  sw $t4, -32($fp)
  lw $t1, -36($fp)
  mul $t1, $t2, $t0
  lw $t3, -40($fp)
  mul $t3, $t2, $t0
  lw $t4, -44($fp)
  add $t4, $t1, $t3
  sw $t1, -36($fp)
  sw $t3, -40($fp)
  lw $t1, -48($fp)
  mul $t1, $t0, $t2
  lw $t3, -52($fp)
  sub $t3, $t4, $t1
  sw $t4, -44($fp)
  sw $t1, -48($fp)
  lw $t1, -56($fp)
  sub $t1, $t3, $t2
  sw $t3, -52($fp)
  lw $t3, -60($fp)
  mul $t3, $t0, $t2
  lw $t4, -64($fp)
  add $t4, $t1, $t3
  sw $t1, -56($fp)
  sw $t3, -60($fp)
  lw $t1, -68($fp)
  mul $t1, $t0, $t0
  lw $t3, -72($fp)
  add $t3, $t4, $t1
  sw $t4, -64($fp)
  sw $t1, -68($fp)
  lw $t1, -76($fp)
  div $t2, $t2
  mflo $t1
  lw $t4, -80($fp)
  add $t4, $t3, $t1
  sw $t3, -72($fp)
  sw $t1, -76($fp)
  lw $t1, -84($fp)
  li $t3, 12
  addi $t1, $t4, -12
  sw $t4, -80($fp)
  lw $t3, -88($fp)
  li $t4, 59
  li $t5, 2
  div $t4, $t5
  mflo $t3
  add $t0, $t1, $t3
  sw $t1, -84($fp)
  sw $t3, -88($fp)
  lw $t1, -92($fp)
  li $t3, 3
  mul $t1, $t0, $t3
  lw $t3, -96($fp)
  li $t4, 14
  li $t5, 24
  mul $t3, $t4, $t5
  lw $t4, -100($fp)
  add $t4, $t1, $t3
  sw $t1, -92($fp)
  sw $t3, -96($fp)
  lw $t1, -104($fp)
  li $t3, 12
  mul $t1, $t2, $t3
  lw $t2, -108($fp)
  li $t3, 4
  div $t1, $t3
  mflo $t2
  sw $t1, -104($fp)
  lw $t1, -112($fp)
  sub $t1, $t4, $t2
  sw $t4, -100($fp)
  sw $t2, -108($fp)
  lw $t2, -116($fp)
  li $t3, 4
  li $t4, 5
  mul $t2, $t3, $t4
  lw $t3, -120($fp)
  add $t3, $t1, $t2
  sw $t1, -112($fp)
  sw $t2, -116($fp)
  lw $t1, -124($fp)
  li $t2, 10
  li $t4, 2
  mul $t1, $t2, $t4
  lw $t2, -128($fp)
  sub $t2, $t3, $t1
  sw $t3, -120($fp)
  sw $t1, -124($fp)
  lw $t1, -132($fp)
  li $t3, 5
  li $t4, 6
  div $t3, $t4
  mflo $t1
  sub $t0, $t2, $t1
  sw $t2, -128($fp)
  sw $t1, -132($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  sw $t0, -8($fp)
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
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -296
  lw $t0, -4($fp)
  li $t1, 4
  li $t2, 2
  mul $t0, $t1, $t2
  lw $t1, -8($fp)
  li $t2, 0
  sub $t1, $t2, $t0
  sw $t0, -4($fp)
  lw $t0, -12($fp)
  li $t2, 108
  addi $t0, $t1, 108
  sw $t1, -8($fp)
  lw $t1, -16($fp)
  li $t2, 17
  div $t0, $t2
  mflo $t1
  sw $t0, -12($fp)
  lw $t0, -24($fp)
  li $t2, 32
  li $t3, 8
  div $t2, $t3
  mflo $t0
  lw $t2, -28($fp)
  li $t3, 2
  mul $t2, $t0, $t3
  sw $t0, -24($fp)
  lw $t0, -32($fp)
  li $t3, 1
  addi $t0, $t2, -1
  sw $t2, -28($fp)
  lw $t2, -40($fp)
  li $t3, 1
  li $t4, 4
  mul $t2, $t3, $t4
  lw $t3, -44($fp)
  li $t4, 2
  div $t2, $t4
  mflo $t3
  sw $t2, -40($fp)
  lw $t2, -48($fp)
  li $t4, 13
  sub $t2, $t4, $t3
  sw $t3, -44($fp)
  lw $t3, -56($fp)
  add $t3, $t1, $t0
  sw $t3, -60($fp)
  sw $t3, -56($fp)
  lw $t3, -64($fp)
  add $t3, $t1, $t0
  lw $t4, -68($fp)
  li $t5, 1
  div $t2, $t5
  mflo $t4
  lw $t5, -72($fp)
  add $t5, $t3, $t4
  sw $t3, -64($fp)
  sw $t4, -68($fp)
  sw $t5, -76($fp)
  sw $t5, -72($fp)
  lw $t3, -80($fp)
  mul $t3, $t1, $t0
  lw $t4, -84($fp)
  sub $t4, $t3, $t2
  sw $t3, -80($fp)
  lw $t3, -92($fp)
  li $t3, 42
  sw $t3, -92($fp)
  lw $t3, -96($fp)
  li $t3, 4
  sw $t3, -96($fp)
  lw $t3, -100($fp)
  li $t3, 0
  sw $t3, -100($fp)
  lw $t3, -104($fp)
  li $t3, 0
  sw $t3, -104($fp)
  lw $t3, -124($fp)
  add $t3, $t1, $t0
  sw $t1, -20($fp)
  sw $t1, -16($fp)
  sw $t0, -36($fp)
  sw $t0, -32($fp)
  lw $t0, -128($fp)
  add $t0, $t3, $t2
  sw $t3, -124($fp)
  sw $t2, -52($fp)
  sw $t2, -48($fp)
  lw $t1, -132($fp)
  li $t2, 1500
  addi $t1, $t0, 1500
  sw $t0, -128($fp)
  sub $t4, $t1, $t4
  sw $t4, -88($fp)
  sw $t4, -84($fp)
  sw $t1, -132($fp)
label1:
  lw $t0, -100($fp)
  li $t1, 4
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -104($fp)
  li $t1, 15
  lw $t2, -100($fp)
  mul $t0, $t1, $t2
  lw $t1, -136($fp)
  li $t3, 4
  mul $t1, $t2, $t3
  lw $t3, -140($fp)
  addi $t5, $fp, -120
  add $t3, $t5, $t1
  sw $t1, -136($fp)
  sw $t0, 0($t3)
  sw $t3, -140($fp)
  sw $t0, -104($fp)
  li $t0, 1
  addi $t2, $t2, 1
  sw $t2, -100($fp)
  j label1
label3:
label4:
  lw $t0, -100($fp)
  lw $t1, -88($fp)
  blt $t0, $t1, label5
  j label6
label5:
  lw $t0, -144($fp)
  lw $t1, -96($fp)
  mul $t0, $t1, $t1
  lw $t2, -148($fp)
  lw $t3, -92($fp)
  add $t2, $t3, $t0
  sw $t0, -144($fp)
  lw $t0, -152($fp)
  lw $t4, -100($fp)
  li $t5, 12
  mul $t0, $t4, $t5
  lw $t4, -156($fp)
  add $t4, $t2, $t0
  sw $t2, -148($fp)
  sw $t0, -152($fp)
  lw $t0, -160($fp)
  li $t2, 4
  mul $t0, $t2, $t1
  lw $t1, -164($fp)
  sub $t1, $t4, $t0
  sw $t4, -156($fp)
  sw $t0, -160($fp)
  lw $t0, -168($fp)
  li $t2, 5
  addi $t0, $t1, 5
  sw $t1, -164($fp)
  lw $t1, -172($fp)
  li $t2, 7
  li $t4, 3
  div $t2, $t4
  mflo $t1
  add $t3, $t0, $t1
  sw $t3, -92($fp)
  sw $t0, -168($fp)
  sw $t1, -172($fp)
  lw $t0, -88($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -176($fp)
  move $t0, $v0
  sw $t0, -176($fp)
  lw $t0, -180($fp)
  li $t1, 2
  lw $t2, -20($fp)
  mul $t0, $t1, $t2
  lw $t1, -184($fp)
  lw $t2, -176($fp)
  add $t1, $t2, $t0
  sw $t0, -180($fp)
  lw $t0, -188($fp)
  lw $t2, -88($fp)
  sub $t0, $t1, $t2
  sw $t1, -184($fp)
  lw $t1, -192($fp)
  lw $t3, -52($fp)
  lw $t4, -60($fp)
  mul $t1, $t3, $t4
  lw $t3, -196($fp)
  add $t3, $t0, $t1
  sw $t3, -196($fp)
  sw $t0, -188($fp)
  sw $t1, -192($fp)
  sw $t2, -12($sp)
  li $t0, 2
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -200($fp)
  move $t0, $v0
  sw $t0, -200($fp)
  lw $t0, -200($fp)
  li $t1, 0
  bgt $t0, $t1, label7
  j label8
label7:
  lw $t0, -204($fp)
  lw $t1, -100($fp)
  li $t2, 3
  addi $t0, $t1, 3
  li $t1, 1
  addi $t0, $t0, -1
  li $t1, 3
  addi $t0, $t0, 3
  lw $t1, -208($fp)
  li $t2, 3
  li $t3, 2
  mul $t1, $t2, $t3
  sub $t0, $t0, $t1
  sw $t0, -204($fp)
  sw $t1, -208($fp)
label8:
  lw $t0, -20($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -212($fp)
  move $t0, $v0
  sw $t0, -212($fp)
  lw $t0, -216($fp)
  lw $t1, -20($fp)
  li $t2, 3
  addi $t0, $t1, 3
  lw $t1, -220($fp)
  li $t2, 2
  addi $t1, $t0, -2
  sw $t0, -216($fp)
  lw $t0, -224($fp)
  li $t2, 1
  addi $t0, $t1, -1
  sw $t1, -220($fp)
  sw $t0, -12($sp)
  sw $t0, -224($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal process
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -228($fp)
  move $t0, $v0
  sw $t0, -228($fp)
  lw $t0, -212($fp)
  lw $t1, -228($fp)
  beq $t0, $t1, label9
  j label10
label9:
  lw $t0, -232($fp)
  lw $t1, -88($fp)
  li $t2, 2
  addi $t0, $t1, -2
  li $t2, 1
  addi $t1, $t0, 1
  sw $t0, -232($fp)
  sw $t1, -12($sp)
  sw $t1, -88($fp)
  li $t0, 4
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -236($fp)
  move $t0, $v0
  sw $t0, -236($fp)
  lw $t0, -240($fp)
  lw $t1, -236($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -244($fp)
  addi $t3, $fp, -120
  add $t1, $t3, $t0
  sw $t1, -244($fp)
  sw $t0, -240($fp)
  lw $t0, -88($fp)
  sw $t0, -12($sp)
  li $t0, 4
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -248($fp)
  move $t0, $v0
  sw $t0, -248($fp)
  lw $t0, -252($fp)
  lw $t1, -248($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -256($fp)
  addi $t3, $fp, -120
  add $t1, $t3, $t0
  sw $t0, -252($fp)
  lw $t0, -260($fp)
  lw $t2, 0($t1)
  lw $t3, -204($fp)
  add $t0, $t2, $t3
  sw $t1, -256($fp)
  lw $t1, -264($fp)
  lw $t2, -196($fp)
  add $t1, $t0, $t2
  sw $t0, -260($fp)
  lw $t0, -268($fp)
  lw $t2, -76($fp)
  sub $t0, $t1, $t2
  sw $t1, -264($fp)
  lw $t1, -244($fp)
  sw $t0, 0($t1)
  sw $t0, -268($fp)
label10:
  lw $t0, -272($fp)
  lw $t1, -20($fp)
  li $t2, 2
  addi $t0, $t1, 2
  li $t2, 1
  addi $t1, $t0, 1
  sw $t1, -20($fp)
  sw $t0, -272($fp)
  lw $t0, -100($fp)
  li $t1, 1
  addi $t0, $t0, 1
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -100($fp)
  j label4
label6:
  lw $t0, -20($fp)
  lw $t1, -36($fp)
  add $t0, $t0, $t1
  add $t1, $t0, $t1
  lw $t2, -52($fp)
  add $t2, $t0, $t1
  lw $t3, -88($fp)
  add $t3, $t0, $t1
  lw $t4, -196($fp)
  add $t4, $t0, $t1
  sw $t0, -20($fp)
  sw $t1, -36($fp)
  lw $t0, -276($fp)
  add $t0, $t2, $t3
  sw $t2, -52($fp)
  sw $t3, -88($fp)
  lw $t1, -280($fp)
  add $t1, $t0, $t4
  sw $t0, -276($fp)
  sw $t4, -196($fp)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t1, -280($fp)
  lw $t0, -284($fp)
  addi $t2, $fp, -120
  li $t3, 0
  addi $t0, $t2, 0
  lw $t1, 0($t0)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -284($fp)
  lw $t0, -288($fp)
  addi $t2, $fp, -120
  li $t3, 4
  addi $t0, $t2, 4
  lw $t1, 0($t0)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -288($fp)
  lw $t0, -292($fp)
  addi $t2, $fp, -120
  li $t3, 8
  addi $t0, $t2, 8
  lw $t1, 0($t0)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -292($fp)
  lw $t0, -296($fp)
  addi $t2, $fp, -120
  li $t3, 12
  addi $t0, $t2, 12
  lw $t1, 0($t0)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -296($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
