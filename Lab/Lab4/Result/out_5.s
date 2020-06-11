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

compare:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -8
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  ble $t0, $t1, label2
  lw $t0, -4($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label2:
  lw $t0, -4($fp)
  lw $t1, -8($fp)
  bge $t0, $t1, label4
  lw $t0, -8($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label4:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
myadd:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -12
  lw $t0, -12($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  add $t0, $t1, $t2
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  sw $t0, -12($fp)
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -148
  lw $t0, -64($fp)
  li $t0, 0
  sw $t0, -64($fp)
label5:
  lw $t0, -64($fp)
  li $t1, 10
  bge $t0, $t1, label7
  lw $t0, -68($fp)
  lw $t1, -64($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -72($fp)
  addi $t4, $fp, -40
  add $t2, $t4, $t0
  sw $t0, -68($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -76($fp)
  move $t0, $v0
  sw $t0, 0($t2)
  sw $t2, -72($fp)
  sw $t0, -76($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -64($fp)
  j label5
label7:
  lw $t0, -64($fp)
  li $t0, 0
  sw $t0, -64($fp)
  lw $t0, -80($fp)
  li $t0, 0
  sw $t0, -80($fp)
label8:
  lw $t0, -64($fp)
  li $t1, 10
  bge $t0, $t1, label10
  lw $t0, -84($fp)
  lw $t1, -80($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -88($fp)
  addi $t3, $fp, -60
  add $t1, $t3, $t0
  sw $t1, -88($fp)
  sw $t0, -84($fp)
  lw $t0, -92($fp)
  lw $t1, -64($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -96($fp)
  addi $t4, $fp, -40
  add $t2, $t4, $t0
  sw $t0, -92($fp)
  lw $t0, -100($fp)
  li $t3, 1
  addi $t0, $t1, 1
  lw $t1, -104($fp)
  li $t3, 4
  mul $t1, $t0, $t3
  sw $t0, -100($fp)
  lw $t0, -108($fp)
  addi $t4, $fp, -40
  add $t0, $t4, $t1
  sw $t1, -104($fp)
  lw $t1, 0($t2)
  sw $t1, -12($sp)
  sw $t2, -96($fp)
  lw $t1, 0($t0)
  sw $t1, -16($sp)
  sw $t0, -108($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal compare
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -112($fp)
  move $t0, $v0
  sw $t0, -112($fp)
  lw $t0, -88($fp)
  lw $t1, -112($fp)
  sw $t1, 0($t0)
  lw $t0, -64($fp)
  li $t1, 2
  addi $t0, $t0, 2
  sw $t0, -64($fp)
  lw $t0, -80($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -80($fp)
  j label8
label10:
  lw $t0, -64($fp)
  li $t0, 0
  sw $t0, -64($fp)
label11:
  lw $t0, -64($fp)
  li $t1, 5
  bge $t0, $t1, label13
  lw $t0, -116($fp)
  lw $t1, -64($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -120($fp)
  addi $t4, $fp, -60
  add $t2, $t4, $t0
  sw $t2, -120($fp)
  sw $t0, -116($fp)
  lw $t0, -124($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -128($fp)
  addi $t4, $fp, -60
  add $t2, $t4, $t0
  sw $t0, -124($fp)
  lw $t0, -132($fp)
  li $t3, 4
  mul $t0, $t1, $t3
  lw $t1, -136($fp)
  addi $t4, $fp, -40
  add $t1, $t4, $t0
  sw $t0, -132($fp)
  lw $t0, 0($t2)
  sw $t0, -12($sp)
  sw $t2, -128($fp)
  lw $t0, 0($t1)
  sw $t0, -16($sp)
  sw $t1, -136($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal myadd
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -140($fp)
  move $t0, $v0
  sw $t0, -140($fp)
  lw $t0, -120($fp)
  lw $t1, -140($fp)
  sw $t1, 0($t0)
  lw $t0, -144($fp)
  lw $t1, -64($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -148($fp)
  addi $t4, $fp, -60
  add $t2, $t4, $t0
  sw $t0, -144($fp)
  lw $t0, 0($t2)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -148($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -64($fp)
  j label11
label13:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra