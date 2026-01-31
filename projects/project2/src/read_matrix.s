.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:
    # Prologue
    addi sp sp -28
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw ra 24(sp)
       
    mv s0 a1 # s0 = &row
    mv s1 a2 # s1 = &col
    
    li a1 0
    jal fopen
    addi t0 x0 -1
    beq a0 t0 fopen_error
    mv s4 a0 # file descriptor
    # read row and col
    mv a0 s4
    mv a1 s0
    addi a2 x0 4
    jal fread
    addi t0 x0 4
    bne a0 t0 fread_error0
    mv a0 s4
    mv a1 s1
    addi a2 x0 4
    jal fread
    addi t0 x0 4
    bne a0 t0 fread_error0
    lw t0 0(s0)
    lw t1 0(s1)
    mul s3 t0 t1 # elements
    # malloc
    slli a0 s3 2
    jal malloc
    beq a0 x0 malloc_error
    mv s5 a0 # s5 = &arrd
    mv a0 s4
    mv a1 s5
    slli a2 s3 2
    jal fread
    slli t0 s3 2
    bne a0 t0 fread_error1
    mv a0 s4
    jal fclose
    bne a0 x0 fclose_error
    mv a0 s5
    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw ra 24(sp)
    addi sp sp 28
    jr ra
malloc_error:
    li a0 26
    j exit
fopen_error:
    li a0 27
    j exit
fclose_error:
    mv a0 s5
    jal free
    li a0 28
    j exit
fread_error0:
    li a0 29 
    j exit
fread_error1:
    mv a0 s5
    jal free
    li a0 29 
    j exit