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
  addi $sp, $sp, -56
  lw $t0, -4($fp)
  li $t0, 12
  lw $t1, -8($fp)
  li $t1, 4
  lw $t2, -12($fp)
  li $t2, 5
  lw $t3, -16($fp)
  mul $t3, $t0, $t1
  sw $t0, -4($fp)
  lw $t0, -20($fp)
  add $t0, $t3, $t2
  sw $t2, -12($fp)
  lw $t2, -24($fp)
  sub $t2, $t0, $t1
  sw $t0, -20($fp)
  lw $t0, -28($fp)
  mul $t0, $t2, $t1
  lw $t4, -32($fp)
  add $t4, $t3, $t0
  sw $t0, -28($fp)
  move $a0, $t4
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -36($fp)
  add $t0, $t3, $t2
  lw $t5, -40($fp)
  mul $t5, $t4, $t0
  sw $t0, -36($fp)
  li $t0, 25
  div $t5, $t0
  mflo $t4
  sw $t5, -40($fp)
  lw $t0, -44($fp)
  add $t0, $t2, $t4
  lw $t5, -48($fp)
  div $t3, $t4
  mflo $t5
  sw $t3, -16($fp)
  lw $t3, -52($fp)
  sub $t3, $t0, $t5
  sw $t0, -44($fp)
  sw $t5, -48($fp)
  lw $t0, -56($fp)
  li $t5, 12
  mul $t0, $t1, $t5
  sw $t1, -8($fp)
  add $t2, $t3, $t0
  sw $t3, -52($fp)
  sw $t0, -56($fp)
  move $a0, $t4
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t4, -32($fp)
  move $a0, $t2
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -24($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
