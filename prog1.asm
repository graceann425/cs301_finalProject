addi $1, $1, 1
beq $1, $2, exit
j 0x400000
exit: sw $17, 4($4)
sw $17, -4($4)
lw $1, 4($4)
slt	$6, $2, $3
slt	$7, $3, $2
sub	$8, $3, $9
