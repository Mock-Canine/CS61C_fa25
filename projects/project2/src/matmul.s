.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
    # Error checks
    li t0 1
    blt a1 t0 error
    blt a2 t0 error
    blt a4 t0 error
    blt a5 t0 error
    bne a2 a4 error
    # Prologue
    addi sp sp -32
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw ra 28(sp)
    
    mv s0 a0 # s0 = arr0
    mv s1 a1 # s1 = n
    mv s2 a2 # s2 = m
    mv s3 a3 # s3 = arr1
    mv s4 a5 # s4 = k
    mv s5 a6 # s5 = arrd
    li s6 1 # s6 = stride0
    li t0 0 # i = 0
outer_loop_start:
    beq t0 s1 outer_loop_end
    li t1 0 # forget to update j
inner_loop_start:
    beq t1 s4 inner_loop_end
    mul t2 t0 s2
    slli t2 t2 2
    add a0 s0 t2
    slli t2 t1 2 # need shift to increse pointer
    add a1 s3 t2
    mv a2 s2
    mv a3 s6
    mv a4 s4
    
    addi sp sp -8
    sw t0 0(sp)
    sw t1 4(sp)
    jal dot
    lw t0 0(sp)
    lw t1 4(sp)
    addi sp sp 8
    
    sw a0 0(s5)
    slli t2 s6 2
    add s5 s5 t2
    addi t1 t1 1
    j inner_loop_start
inner_loop_end:
    addi t0 t0 1
    j outer_loop_start
outer_loop_end:
    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw ra 28(sp)
    addi sp sp 32
    jr ra
error:
    li a0 38
    j exit
