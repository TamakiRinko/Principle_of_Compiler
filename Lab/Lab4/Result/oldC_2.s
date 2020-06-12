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
  addi $sp, $sp, -28
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
  sw $t0, -28($fp)
  sw $t0, -24($fp)
  sw $t0, -20($fp)
power:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -56
  lw $t0, -12($fp)
  li $t1, 1
  lw $t2, -8($fp)
  addi $t0, $t2, 1
  lw $t1, -16($fp)
  sub $t1, $t0, $t2
  sw $t0, -12($fp)
  sw $t1, -20($fp)
  sw $t1, -16($fp)
label1:
  lw $t0, -24($fp)
  lw $t1, -20($fp)
  sub $t0, $t1, $t1
  lw $t1, -28($fp)
  li $t2, 90
  addi $t1, $t0, 90
  sw $t0, -24($fp)
  lw $t0, -32($fp)
  li $t2, 89
  addi $t0, $t1, -89
  sw $t1, -28($fp)
  lw $t1, -36($fp)
  li $t2, 1
  addi $t1, $t0, 1
  sw $t0, -32($fp)
  lw $t0, -40($fp)
  li $t2, 2
  addi $t0, $t1, -2
  sw $t0, -40($fp)
  sw $t1, -36($fp)
  lw $t0, -8($fp)
  lw $t1, -40($fp)
  bgt $t0, $t1, label2
  j label3
label2:
  lw $t0, -20($fp)
  lw $t1, -4($fp)
  mul $t0, $t0, $t1
  sw $t0, -20($fp)
  lw $t0, -44($fp)
  li $t1, 2
  li $t2, 1
  mul $t0, $t1, $t2
  lw $t1, -48($fp)
  lw $t2, -8($fp)
  mul $t1, $t0, $t2
  sw $t0, -44($fp)
  lw $t0, -52($fp)
  li $t3, 1
  mul $t0, $t3, $t2
  lw $t3, -56($fp)
  sub $t3, $t1, $t0
  sw $t1, -48($fp)
  sw $t0, -52($fp)
  li $t0, 1
  addi $t2, $t3, -1
  sw $t2, -8($fp)
  sw $t3, -56($fp)
  j label1
label3:
  lw $t0, -20($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
getNumDigits:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -12
  lw $t0, -8($fp)
  li $t0, 0
  sw $t0, -8($fp)
  lw $t0, -4($fp)
  li $t1, 0
  blt $t0, $t1, label4
  j label5
label4:
  lw $t0, -12($fp)
  li $t1, 0
  li $t2, 1
  addi $t0, $t1, -1
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  sw $t0, -12($fp)
label5:
label6:
  lw $t0, -4($fp)
  li $t1, 0
  bgt $t0, $t1, label7
  j label8
label7:
  lw $t0, -4($fp)
  li $t1, 10
  div $t0, $t1
  mflo $t0
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t1, 2
  addi $t0, $t0, 2
  li $t1, 2
  addi $t0, $t0, 2
  li $t1, 3
  addi $t0, $t0, -3
  sw $t0, -8($fp)
  j label6
label8:
  lw $t0, -8($fp)
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
isNarcissistic:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -40
  lw $t0, -8($fp)
  li $t1, 1
  lw $t2, -4($fp)
  addi $t0, $t2, 1
  lw $t1, -12($fp)
  li $t2, 1
  addi $t1, $t0, -1
  sw $t0, -8($fp)
  sw $t1, -12($sp)
  sw $t1, -12($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal getNumDigits
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
  lw $t0, -16($fp)
  sw $t0, -20($fp)
  lw $t0, -24($fp)
  li $t0, 0
  sw $t0, -24($fp)
  lw $t0, -4($fp)
  sw $t0, -28($fp)
label9:
  lw $t0, -28($fp)
  li $t1, 0
  bgt $t0, $t1, label10
  j label11
label10:
  lw $t0, -28($fp)
  sw $t0, -12($sp)
  li $t0, 10
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -32($fp)
  move $t0, $v0
  sw $t0, -32($fp)
  lw $t0, -36($fp)
  lw $t1, -28($fp)
  lw $t2, -32($fp)
  sub $t0, $t1, $t2
  li $t3, 10
  div $t0, $t3
  mflo $t1
  sw $t1, -28($fp)
  sw $t0, -36($fp)
  sw $t2, -12($sp)
  lw $t0, -20($fp)
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal power
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -40($fp)
  move $t0, $v0
  sw $t0, -40($fp)
  lw $t0, -24($fp)
  lw $t1, -40($fp)
  add $t0, $t0, $t1
  sw $t0, -24($fp)
  j label9
label11:
  lw $t0, -24($fp)
  lw $t1, -4($fp)
  beq $t0, $t1, label12
  j label13
label12:
  li $t0, 1
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
  j label14
label13:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label14:
main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -12
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t0, 300
  sw $t0, -8($fp)
label15:
  lw $t0, -8($fp)
  li $t1, 500
  blt $t0, $t1, label16
  j label17
label16:
  lw $t0, -8($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal isNarcissistic
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -12($fp)
  li $t1, 1
  beq $t0, $t1, label18
  j label19
label18:
  lw $t0, -8($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -4($fp)
label19:
  lw $t0, -8($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -8($fp)
  j label15
label17:
  lw $t0, -4($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
