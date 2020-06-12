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
DigitSum:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -20
  lw $t0, -4($fp)
  li $t1, 0
  beq $t0, $t1, label1
  j label2
label1:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
label2:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  li $t0, 10
  sw $t0, -16($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal mod
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -8($fp)
  move $t0, $v0
  sw $t0, -8($fp)
  lw $t0, -12($fp)
  lw $t1, -4($fp)
  li $t2, 10
  div $t1, $t2
  mflo $t0
  sw $t0, -12($sp)
  sw $t0, -12($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal DigitSum
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
  lw $t0, -20($fp)
  lw $t1, -8($fp)
  lw $t2, -16($fp)
  add $t0, $t1, $t2
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
  addi $sp, $sp, -12
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($fp)
  move $t0, $v0
  sw $t0, -4($fp)
  lw $t0, -4($fp)
  li $t1, 0
  blt $t0, $t1, label3
  j label4
label3:
  lw $t0, -8($fp)
  li $t1, 0
  li $t2, 1
  addi $t0, $t1, -1
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -8($fp)
  j label5
label4:
  lw $t0, -4($fp)
  sw $t0, -12($sp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal DigitSum
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -12($fp)
  move $t0, $v0
  sw $t0, -12($fp)
  lw $t0, -12($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
label5:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
