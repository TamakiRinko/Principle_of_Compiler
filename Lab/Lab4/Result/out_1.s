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
  addi $sp, $sp, -24
  lw $t0, -4($fp)
  li $t0, 0
  sw $t0, -4($fp)
  lw $t0, -8($fp)
  li $t0, 1
  sw $t0, -8($fp)
  lw $t0, -12($fp)
  li $t0, 0
  sw $t0, -12($fp)
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -16($fp)
  move $t0, $v0
  sw $t0, -16($fp)
label1:
  lw $t0, -12($fp)
  lw $t1, -16($fp)
  bge $t0, $t1, label3
  lw $t0, -20($fp)
  lw $t1, -4($fp)
  lw $t2, -8($fp)
  add $t0, $t1, $t2
  move $a0, $t2
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t0, -8($fp)
  sw $t0, -24($fp)
  sw $t0, -20($fp)
  sw $t2, -4($fp)
  lw $t0, -12($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -12($fp)
  j label1
label3:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra