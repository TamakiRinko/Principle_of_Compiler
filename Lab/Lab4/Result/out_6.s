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
  addi $sp, $sp, -116
  lw $t0, -24($fp)
  li $t0, 0
  sw $t0, -24($fp)
label1:
  lw $t0, -24($fp)
  li $t1, 5
  bge $t0, $t1, label3
  lw $t0, -28($fp)
  lw $t1, -24($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -32($fp)
  addi $t4, $fp, -20
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
  sw $t1, -24($fp)
  j label1
label3:
  lw $t0, -40($fp)
  li $t0, 1
  sw $t0, -40($fp)
label4:
  lw $t0, -40($fp)
  li $t1, 1
  bne $t0, $t1, label6
  lw $t0, -40($fp)
  li $t0, 0
  sw $t0, -40($fp)
  lw $t0, -24($fp)
  li $t0, 1
  sw $t0, -24($fp)
label7:
  lw $t0, -24($fp)
  li $t1, 5
  bge $t0, $t1, label9
  lw $t0, -24($fp)
  sw $t0, -44($fp)
label10:
  lw $t0, -44($fp)
  li $t1, 0
  ble $t0, $t1, label12
  lw $t0, -48($fp)
  lw $t1, -44($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -52($fp)
  addi $t4, $fp, -20
  add $t2, $t4, $t0
  sw $t2, -52($fp)
  sw $t0, -48($fp)
  lw $t0, -56($fp)
  li $t2, 1
  addi $t0, $t1, -1
  lw $t1, -60($fp)
  li $t2, 4
  mul $t1, $t0, $t2
  sw $t0, -56($fp)
  lw $t0, -64($fp)
  addi $t3, $fp, -20
  add $t0, $t3, $t1
  sw $t0, -64($fp)
  sw $t1, -60($fp)
  lw $t0, -52($fp)
  lw $t1, 0($t0)
  lw $t2, -64($fp)
  lw $t3, 0($t2)
  bge $t1, $t3, label12
  lw $t0, -68($fp)
  lw $t1, -44($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -72($fp)
  addi $t4, $fp, -20
  add $t2, $t4, $t0
  sw $t0, -68($fp)
  lw $t0, -76($fp)
  lw $t0, 0($t2)
  sw $t2, -72($fp)
  lw $t2, -80($fp)
  li $t3, 4
  mul $t2, $t1, $t3
  lw $t3, -84($fp)
  addi $t5, $fp, -20
  add $t3, $t5, $t2
  sw $t2, -80($fp)
  lw $t2, -88($fp)
  li $t4, 1
  addi $t2, $t1, -1
  lw $t4, -92($fp)
  li $t5, 4
  mul $t4, $t2, $t5
  sw $t2, -88($fp)
  lw $t2, -96($fp)
  addi $t6, $fp, -20
  add $t2, $t6, $t4
  sw $t4, -92($fp)
  lw $t4, 0($t2)
  sw $t4, 0($t3)
  sw $t3, -84($fp)
  sw $t2, -96($fp)
  lw $t2, -100($fp)
  li $t3, 1
  addi $t2, $t1, -1
  lw $t3, -104($fp)
  li $t4, 4
  mul $t3, $t2, $t4
  sw $t2, -100($fp)
  lw $t2, -108($fp)
  addi $t5, $fp, -20
  add $t2, $t5, $t3
  sw $t3, -104($fp)
  sw $t0, 0($t2)
  sw $t2, -108($fp)
  sw $t0, -76($fp)
  lw $t0, -40($fp)
  li $t0, 1
  sw $t0, -40($fp)
  li $t0, 1
  addi $t1, $t1, -1
  sw $t1, -44($fp)
  j label10
label12:
  lw $t0, -24($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -24($fp)
  j label7
label9:
  j label4
label6:
  lw $t0, -24($fp)
  li $t0, 0
  sw $t0, -24($fp)
label14:
  lw $t0, -24($fp)
  li $t1, 5
  bge $t0, $t1, label16
  lw $t0, -112($fp)
  lw $t1, -24($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -116($fp)
  addi $t4, $fp, -20
  add $t2, $t4, $t0
  sw $t0, -112($fp)
  lw $t0, 0($t2)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -116($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -24($fp)
  j label14
label16:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra