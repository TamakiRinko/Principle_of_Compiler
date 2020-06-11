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
gcd:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -16
  lw $t0, -4($fp)
  li $t1, 0
  beq $t0, $t1, label1
  j label2
label1:
  lw $t0, -8($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label2:
  lw $t0, -8($fp)
  sw $t0, -12($sp)
  lw $t0, -4($fp)
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -12($fp)
  sw $t0, -12($sp)
  lw $t0, -4($fp)
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal gcd
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
  lw $t0, -16($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
lcm:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -20
  lw $t0, -12($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  mul $t0, $t1, $t2
  sw $t0, -12($fp)
  sw $t1, -12($sp)
  sw $t2, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal gcd
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
  lw $t0, -20($fp)
  lw $t1, -12($fp)
  lw $t2, -16($fp)
  div $t1, $t2
  mflo $t0
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
  addi $sp, $sp, -480
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -408($fp)
  move $t0, $v0
  sw $t0, -408($fp)
  lw $t0, -412($fp)
  li $t0, 0
  sw $t0, -412($fp)
label3:
  lw $t0, -412($fp)
  lw $t1, -408($fp)
  blt $t0, $t1, label4
  j label5
label4:
  lw $t0, -416($fp)
  lw $t1, -412($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -420($fp)
  addi $t4, $fp, -204
  add $t2, $t4, $t0
  sw $t0, -416($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -424($fp)
  move $t0, $v0
  sw $t0, 0($t2)
  sw $t2, -420($fp)
  sw $t0, -424($fp)
  lw $t0, -428($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -432($fp)
  addi $t4, $fp, -404
  add $t2, $t4, $t0
  sw $t0, -428($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -436($fp)
  move $t0, $v0
  sw $t0, 0($t2)
  sw $t2, -432($fp)
  sw $t0, -436($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -412($fp)
  j label3
label5:
  lw $t0, -440($fp)
  addi $t2, $fp, -404
  li $t3, 0
  addi $t0, $t2, 0
  lw $t1, -444($fp)
  lw $t1, 0($t0)
  sw $t1, -444($fp)
  sw $t0, -440($fp)
  lw $t0, -412($fp)
  li $t0, 1
  sw $t0, -412($fp)
label6:
  lw $t0, -412($fp)
  lw $t1, -408($fp)
  blt $t0, $t1, label7
  j label8
label7:
  lw $t0, -448($fp)
  lw $t1, -412($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t1, -452($fp)
  addi $t3, $fp, -404
  add $t1, $t3, $t0
  sw $t0, -448($fp)
  lw $t0, -444($fp)
  sw $t0, -12($sp)
  lw $t0, 0($t1)
  sw $t0, -16($sp)
  sw $t1, -452($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal lcm
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -444($fp)
  move $t0, $v0
  sw $t0, -444($fp)
  lw $t0, -412($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -412($fp)
  j label6
label8:
  lw $t0, -412($fp)
  li $t0, 0
  sw $t0, -412($fp)
label9:
  lw $t0, -412($fp)
  lw $t1, -408($fp)
  blt $t0, $t1, label10
  j label11
label10:
  lw $t0, -456($fp)
  lw $t1, -412($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -460($fp)
  addi $t4, $fp, -204
  add $t2, $t4, $t0
  sw $t0, -456($fp)
  lw $t0, -464($fp)
  li $t3, 4
  mul $t0, $t1, $t3
  lw $t3, -468($fp)
  addi $t5, $fp, -404
  add $t3, $t5, $t0
  sw $t0, -464($fp)
  lw $t0, -472($fp)
  lw $t4, -444($fp)
  lw $t5, 0($t3)
  div $t4, $t5
  mflo $t0
  sw $t3, -468($fp)
  lw $t3, -476($fp)
  lw $t4, 0($t2)
  mul $t3, $t4, $t0
  sw $t2, -460($fp)
  sw $t0, -472($fp)
  lw $t0, -4($fp)
  add $t0, $t0, $t3
  sw $t0, -4($fp)
  sw $t3, -476($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -412($fp)
  j label9
label11:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  lw $t0, -444($fp)
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal gcd
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -480($fp)
  move $t0, $v0
  sw $t0, -480($fp)
  lw $t0, -4($fp)
  lw $t1, -480($fp)
  div $t0, $t1
  mflo $t0
  sw $t0, -4($fp)
  lw $t0, -444($fp)
  div $t0, $t1
  mflo $t0
  sw $t0, -444($fp)
  lw $t0, -444($fp)
  li $t1, 1
  beq $t0, $t1, label12
  j label13
label12:
  lw $t0, -4($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  j label14
label13:
  lw $t0, -4($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -444($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
label14:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
