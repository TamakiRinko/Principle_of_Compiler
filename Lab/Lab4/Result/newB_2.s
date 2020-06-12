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
  addi $sp, $sp, -120
  lw $t0, -44($fp)
  li $t0, 10
  sw $t0, -44($fp)
  lw $t0, -48($fp)
  addi $t2, $fp, -40
  li $t3, 0
  addi $t0, $t2, 0
  li $t1, 2
  sw $t1, 0($t0)
  sw $t0, -48($fp)
  lw $t0, -52($fp)
  li $t0, 1
  sw $t0, -52($fp)
  lw $t0, -56($fp)
  li $t0, 3
  sw $t0, -56($fp)
label1:
  lw $t0, -52($fp)
  lw $t1, -44($fp)
  blt $t0, $t1, label2
  j label3
label2:
  lw $t0, -60($fp)
  li $t0, 0
  sw $t0, -60($fp)
label4:
  lw $t0, -64($fp)
  lw $t1, -60($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -68($fp)
  addi $t4, $fp, -40
  add $t2, $t4, $t0
  sw $t0, -64($fp)
  lw $t0, -72($fp)
  li $t3, 4
  mul $t0, $t1, $t3
  lw $t1, -76($fp)
  addi $t4, $fp, -40
  add $t1, $t4, $t0
  sw $t0, -72($fp)
  lw $t0, -80($fp)
  lw $t3, 0($t2)
  lw $t4, 0($t1)
  mul $t0, $t3, $t4
  sw $t0, -80($fp)
  sw $t2, -68($fp)
  sw $t1, -76($fp)
  lw $t0, -80($fp)
  lw $t1, -56($fp)
  ble $t0, $t1, label5
  j label6
label5:
  lw $t0, -84($fp)
  lw $t1, -60($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -88($fp)
  addi $t4, $fp, -40
  add $t2, $t4, $t0
  sw $t0, -84($fp)
  lw $t0, -92($fp)
  li $t3, 4
  mul $t0, $t1, $t3
  lw $t1, -96($fp)
  addi $t4, $fp, -40
  add $t1, $t4, $t0
  sw $t0, -92($fp)
  lw $t0, -100($fp)
  lw $t3, -56($fp)
  lw $t4, 0($t1)
  div $t3, $t4
  mflo $t0
  sw $t1, -96($fp)
  lw $t1, -104($fp)
  lw $t3, 0($t2)
  mul $t1, $t3, $t0
  sw $t1, -104($fp)
  sw $t2, -88($fp)
  sw $t0, -100($fp)
  lw $t0, -56($fp)
  lw $t1, -104($fp)
  beq $t0, $t1, label7
  j label8
label7:
  lw $t0, -56($fp)
  li $t1, 2
  addi $t0, $t0, 2
  sw $t0, -56($fp)
  lw $t0, -60($fp)
  li $t0, 1
  sw $t0, -60($fp)
  j label9
label8:
  lw $t0, -60($fp)
  li $t1, 1
  addi $t0, $t0, 1
  sw $t0, -60($fp)
label9:
  j label4
label6:
  lw $t0, -108($fp)
  lw $t1, -52($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -112($fp)
  addi $t4, $fp, -40
  add $t2, $t4, $t0
  sw $t0, -108($fp)
  lw $t0, -56($fp)
  sw $t0, 0($t2)
  sw $t2, -112($fp)
  li $t2, 1
  addi $t1, $t1, 1
  sw $t1, -52($fp)
  li $t1, 2
  addi $t0, $t0, 2
  sw $t0, -56($fp)
  j label1
label3:
  lw $t0, -60($fp)
  li $t0, 0
  sw $t0, -60($fp)
label10:
  lw $t0, -60($fp)
  lw $t1, -52($fp)
  blt $t0, $t1, label11
  j label12
label11:
  lw $t0, -116($fp)
  lw $t1, -60($fp)
  li $t2, 4
  mul $t0, $t1, $t2
  lw $t2, -120($fp)
  addi $t4, $fp, -40
  add $t2, $t4, $t0
  sw $t0, -116($fp)
  lw $t0, 0($t2)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  sw $t2, -120($fp)
  li $t0, 1
  addi $t1, $t1, 1
  sw $t1, -60($fp)
  j label10
label12:
  li $t0, 0
  move $v0, $t0
  move $sp, $fp
  lw $fp, 0($sp)
  addi $sp, $sp, 4
  jr $ra
