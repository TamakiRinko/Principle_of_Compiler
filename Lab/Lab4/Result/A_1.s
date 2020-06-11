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
  addi $sp, $sp, -72
  lw $t0, -4($fp)
  li $t0, 3
  lw $t1, -8($fp)
  li $t1, 8
  lw $t2, -12($fp)
  li $t2, 24
  lw $t3, -16($fp)
  mul $t3, $t0, $t0
  lw $t4, -20($fp)
  div $t2, $t1
  mflo $t4
  lw $t5, -24($fp)
  add $t5, $t3, $t4
  sw $t3, -16($fp)
  sw $t4, -20($fp)
  li $t3, 4
  mul $t1, $t5, $t3
  sw $t5, -24($fp)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t3, -28($fp)
  li $t4, 3
  mul $t3, $t4, $t0
  lw $t4, -32($fp)
  add $t4, $t1, $t3
  sw $t3, -28($fp)
  lw $t3, -36($fp)
  sub $t3, $t4, $t2
  sw $t4, -32($fp)
  lw $t4, -40($fp)
  li $t5, 55
  mul $t4, $t3, $t5
  sw $t3, -36($fp)
  div $t4, $t0
  mflo $t2
  sw $t4, -40($fp)
  move $a0, $t2
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t3, -44($fp)
  li $t4, 10
  mul $t3, $t4, $t0
  lw $t4, -48($fp)
  mul $t4, $t3, $t1
  sw $t3, -44($fp)
  lw $t3, -52($fp)
  add $t3, $t0, $t4
  sw $t4, -48($fp)
  lw $t4, -56($fp)
  li $t5, 4
  mul $t4, $t2, $t5
  sw $t2, -12($fp)
  lw $t2, -60($fp)
  add $t2, $t3, $t4
  sw $t3, -52($fp)
  sw $t4, -56($fp)
  lw $t3, -64($fp)
  div $t1, $t0
  mflo $t3
  sw $t1, -8($fp)
  sw $t0, -4($fp)
  lw $t0, -68($fp)
  li $t1, 6
  addi $t0, $t3, -6
  sw $t3, -64($fp)
  lw $t1, -72($fp)
  add $t1, $t2, $t0
  sw $t2, -60($fp)
  sw $t0, -68($fp)
  move $a0, $t1
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t1, -72($fp)
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra