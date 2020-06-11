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
  addi $sp, $sp, -304
  lw $t0, -4($fp)
  li $t0, 10
  sw $t0, -4($fp)
  lw $t0, -88($fp)
  li $t0, 0
  sw $t0, -88($fp)
  lw $t0, -92($fp)
  li $t0, 0
  sw $t0, -92($fp)
label1:
  lw $t0, -88($fp)
  li $t1, 10
  bge $t0, $t1, label3
  lw $t0, -96($fp)
  lw $t1, -88($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -100($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -96($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -104($fp)
  move $t0, $v0
  sw $t0, 0($t2)
  sw $t2, -100($fp)
  sw $t0, -104($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -88($fp)
  j label1
label3:
  lw $t0, -108($fp)
  lw $t1, -4($fp)
  li $t2, 2
  div $t1, $t2
  mflo $t0
  sw $t0, -108($fp)
label4:
  lw $t0, -108($fp)
  li $t1, 0
  blt $t0, $t1, label6
  lw $t0, -92($fp)
  li $t0, 0
  sw $t0, -92($fp)
  lw $t0, -108($fp)
  sw $t0, -88($fp)
label7:
  lw $t0, -92($fp)
  li $t1, 0
  bne $t0, $t1, label9
  lw $t0, -92($fp)
  li $t0, 1
  sw $t0, -92($fp)
  lw $t0, -112($fp)
  lw $t1, -88($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  lw $t2, -116($fp)
  li $t3, 1
  addi $t2, $t0, 1
  sw $t2, -116($fp)
  sw $t0, -112($fp)
  lw $t0, -120($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  lw $t1, -124($fp)
  li $t2, 2
  addi $t1, $t0, 2
  sw $t1, -124($fp)
  sw $t0, -120($fp)
  lw $t0, -116($fp)
  lw $t1, -4($fp)
  bge $t0, $t1, label11
  lw $t0, -128($fp)
  lw $t1, -116($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -132($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t0, -128($fp)
  lw $t0, -136($fp)
  lw $t0, 0($t1)
  sw $t0, -136($fp)
  sw $t1, -132($fp)
  lw $t0, -124($fp)
  lw $t1, -4($fp)
  bge $t0, $t1, label13
  lw $t0, -140($fp)
  lw $t1, -124($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -144($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -144($fp)
  sw $t0, -140($fp)
  lw $t0, -148($fp)
  lw $t1, -116($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -152($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -152($fp)
  sw $t0, -148($fp)
  lw $t0, -144($fp)
  lw $t1, 0($t0)
  lw $t2, -152($fp)
  lw $t3, 0($t2)
  bge $t1, $t3, label13
  lw $t0, -156($fp)
  lw $t1, -124($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -160($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -156($fp)
  lw $t0, -136($fp)
  lw $t0, 0($t2)
  sw $t0, -136($fp)
  sw $t2, -160($fp)
  sw $t1, -116($fp)
label13:
  lw $t0, -164($fp)
  lw $t1, -88($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -168($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -168($fp)
  sw $t0, -164($fp)
  lw $t0, -168($fp)
  lw $t1, 0($t0)
  lw $t2, -136($fp)
  ble $t1, $t2, label16
  lw $t0, -92($fp)
  li $t0, 0
  sw $t0, -92($fp)
  lw $t0, -172($fp)
  lw $t1, -116($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -176($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -172($fp)
  lw $t0, -180($fp)
  lw $t3, -88($fp)
  li $t4, 4
  mul $t0, $t3, $t4
  lw $t4, -184($fp)
  addi $t6, $fp, -44
  add $t4, $t6, $t0
  sw $t0, -180($fp)
  lw $t0, 0($t4)
  sw $t0, 0($t2)
  sw $t2, -176($fp)
  sw $t4, -184($fp)
  lw $t0, -188($fp)
  li $t2, 4
  mul $t0, $t3, $t2
  lw $t2, -192($fp)
  addi $t5, $fp, -44
  add $t2, $t5, $t0
  sw $t0, -188($fp)
  lw $t0, -136($fp)
  sw $t0, 0($t2)
  sw $t2, -192($fp)
  sw $t1, -88($fp)
label16:
label11:
  j label7
label9:
  lw $t0, -108($fp)
  li $t1, 1
  addi $t0, $t0, -1
  sw $t0, -108($fp)
  j label4
label6:
  lw $t0, -108($fp)
  li $t0, 10
  sw $t0, -108($fp)
  lw $t0, -88($fp)
  li $t0, 0
  sw $t0, -88($fp)
label17:
  lw $t0, -88($fp)
  lw $t1, -4($fp)
  bge $t0, $t1, label19
  lw $t0, -196($fp)
  lw $t1, -88($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -200($fp)
  addi $t4, $fp, -84
  add $t2, $t4, $t0
  sw $t0, -196($fp)
  lw $t0, -204($fp)
  addi $t4, $fp, -44
  li $t5, 0
  addi $t0, $t4, 0
  lw $t3, 0($t0)
  sw $t3, 0($t2)
  sw $t2, -200($fp)
  sw $t0, -204($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -88($fp)
  lw $t0, -208($fp)
  addi $t2, $fp, -44
  li $t3, 0
  addi $t0, $t2, 0
  lw $t1, -212($fp)
  lw $t2, -108($fp)
  li $t3, 1
  addi $t1, $t2, -1
  lw $t3, -216($fp)
  li $t4, 4
  mul $t3, $t1, $t4
  sw $t1, -212($fp)
  lw $t1, -220($fp)
  addi $t5, $fp, -44
  add $t1, $t5, $t3
  sw $t3, -216($fp)
  lw $t3, 0($t1)
  sw $t3, 0($t0)
  sw $t0, -208($fp)
  sw $t1, -220($fp)
  lw $t0, -92($fp)
  li $t0, 0
  sw $t0, -92($fp)
  li $t0, 1
  addi $t2, $t2, -1
  sw $t2, -108($fp)
  lw $t0, -224($fp)
  li $t0, 0
  sw $t0, -224($fp)
label20:
  lw $t0, -92($fp)
  li $t1, 0
  bne $t0, $t1, label22
  lw $t0, -92($fp)
  li $t0, 1
  sw $t0, -92($fp)
  lw $t0, -228($fp)
  lw $t1, -224($fp)
  li $t2, 2
  mul $t0, $t1, $t2
  lw $t2, -116($fp)
  li $t3, 1
  addi $t2, $t0, 1
  sw $t0, -228($fp)
  lw $t0, -232($fp)
  li $t3, 2
  mul $t0, $t1, $t3
  lw $t1, -124($fp)
  li $t3, 2
  addi $t1, $t0, 2
  sw $t1, -124($fp)
  sw $t0, -232($fp)
  lw $t0, -108($fp)
  bge $t2, $t0, label24
  sw $t2, -116($fp)
  lw $t0, -236($fp)
  lw $t1, -116($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -240($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t0, -236($fp)
  lw $t0, -136($fp)
  lw $t0, 0($t1)
  sw $t0, -136($fp)
  sw $t1, -240($fp)
  lw $t0, -124($fp)
  lw $t1, -108($fp)
  bge $t0, $t1, label26
  lw $t0, -244($fp)
  lw $t1, -124($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -248($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -248($fp)
  sw $t0, -244($fp)
  lw $t0, -252($fp)
  lw $t1, -116($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -256($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -256($fp)
  sw $t0, -252($fp)
  lw $t0, -248($fp)
  lw $t1, 0($t0)
  lw $t2, -256($fp)
  lw $t3, 0($t2)
  bge $t1, $t3, label26
  lw $t0, -260($fp)
  lw $t1, -124($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -264($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -260($fp)
  lw $t0, -136($fp)
  lw $t0, 0($t2)
  sw $t0, -136($fp)
  sw $t2, -264($fp)
  sw $t1, -116($fp)
label26:
  lw $t0, -268($fp)
  lw $t1, -224($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -272($fp)
  addi $t3, $fp, -44
  add $t1, $t3, $t0
  sw $t1, -272($fp)
  sw $t0, -268($fp)
  lw $t0, -272($fp)
  lw $t1, 0($t0)
  lw $t2, -136($fp)
  ble $t1, $t2, label29
  lw $t0, -92($fp)
  li $t0, 0
  sw $t0, -92($fp)
  lw $t0, -276($fp)
  lw $t1, -116($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -280($fp)
  addi $t4, $fp, -44
  add $t2, $t4, $t0
  sw $t0, -276($fp)
  lw $t0, -284($fp)
  lw $t3, -224($fp)
  li $t4, 4
  mul $t0, $t3, $t4
  lw $t4, -288($fp)
  addi $t6, $fp, -44
  add $t4, $t6, $t0
  sw $t0, -284($fp)
  lw $t0, 0($t4)
  sw $t0, 0($t2)
  sw $t2, -280($fp)
  sw $t4, -288($fp)
  lw $t0, -292($fp)
  li $t2, 4
  mul $t0, $t3, $t2
  lw $t2, -296($fp)
  addi $t5, $fp, -44
  add $t2, $t5, $t0
  sw $t0, -292($fp)
  lw $t0, -136($fp)
  sw $t0, 0($t2)
  sw $t2, -296($fp)
  sw $t1, -224($fp)
label29:
label24:
  j label20
label22:
  j label17
label19:
  lw $t0, -88($fp)
  li $t0, 0
  sw $t0, -88($fp)
label30:
  lw $t0, -88($fp)
  lw $t1, -4($fp)
  bge $t0, $t1, label32
  lw $t0, -300($fp)
  lw $t1, -88($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -304($fp)
  addi $t4, $fp, -84
  add $t2, $t4, $t0
  sw $t0, -300($fp)
  lw $t0, 0($t2)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -304($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -88($fp)
  j label30
label32:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra