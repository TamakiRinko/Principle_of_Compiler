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

Joseph:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -456
  lw $t0, -408($fp)
  li $t0, 0
  sw $t0, -408($fp)
  lw $t0, -4($fp)
  sw $t0, -412($fp)
  lw $t0, -416($fp)
  li $t0, 0
  sw $t0, -416($fp)
  lw $t0, -420($fp)
  li $t0, 0
  sw $t0, -420($fp)
label1:
  lw $t0, -408($fp)
  lw $t1, -4($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -424($fp)
  lw $t1, -408($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -428($fp)
  addi $t4, $fp, -404
  add $t2, $t4, $t0
  sw $t0, -424($fp)
  li $t0, 1
  sw $t0, 0($t2)
  sw $t2, -428($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -408($fp)
  j label1
label3:
label4:
  lw $t0, -412($fp)
  li $t1, 2
  bgt $t0, $t1, label5
  j label6
label5:
  lw $t0, -432($fp)
  lw $t1, -416($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -436($fp)
  addi $t3, $fp, -404
  add $t1, $t3, $t0
  sw $t1, -436($fp)
  sw $t0, -432($fp)
  lw $t0, -436($fp)
  lw $t1, 0($t0)
  li $t2, 1
  beq $t1, $t2, label7
  j label8
label7:
  lw $t0, -420($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -420($fp)
  li $t0, 3
  lw $t1, -420($fp)
  beq $t0, $t1, label9
  j label10
label9:
  lw $t0, -440($fp)
  lw $t1, -416($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -444($fp)
  addi $t3, $fp, -404
  add $t1, $t3, $t0
  sw $t0, -440($fp)
  li $t0, 0
  sw $t0, 0($t1)
  sw $t1, -444($fp)
  lw $t0, -420($fp)
  li $t0, 0
  sw $t0, -420($fp)
  lw $t0, -412($fp)
  li $t1, 1
  addi $t0, $t0, -1
  sw $t0, -412($fp)
label10:
label8:
  lw $t0, -416($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -416($fp)
  lw $t0, -416($fp)
  lw $t1, -4($fp)
  beq $t0, $t1, label11
  j label12
label11:
  lw $t0, -416($fp)
  li $t0, 0
  sw $t0, -416($fp)
label12:
  j label4
label6:
  lw $t0, -408($fp)
  li $t0, 0
  sw $t0, -408($fp)
label13:
  lw $t0, -408($fp)
  lw $t1, -4($fp)
  blt $t0, $t1, label14
  j label15
label14:
  lw $t0, -448($fp)
  lw $t1, -408($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -452($fp)
  addi $t3, $fp, -404
  add $t1, $t3, $t0
  sw $t1, -452($fp)
  sw $t0, -448($fp)
  li $t0, 1
  lw $t1, -452($fp)
  lw $t2, 0($t1)
  beq $t0, $t2, label16
  j label17
label16:
  lw $t0, -456($fp)
  lw $t1, -408($fp)
  li $t2, 1
  addi $t0, $t1, 1
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -456($fp)
label17:
  lw $t0, -408($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -408($fp)
  j label13
label15:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -16
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($fp)
  move $t0, $v0
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t0, 0
  sw $t0, -8($fp)
  lw $t0, -4($fp)
  li $t1, 3
  bgt $t0, $t1, label22
  j label21
label22:
  lw $t0, -4($fp)
  li $t1, 100
  ble $t0, $t1, label20
  j label21
label20:
  lw $t0, -8($fp)
  li $t0, 1
  sw $t0, -8($fp)
label21:
  lw $t0, -8($fp)
  li $t1, 0
  bne $t0, $t1, label19
  j label18
label18:
  lw $t0, -12($fp)
  li $t1, 0
  li $t2, 1
  addi $t0, $t1, -1
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -12($fp)
  j label23
label19:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal Joseph
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
label23:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
