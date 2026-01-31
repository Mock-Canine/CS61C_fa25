.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:
    # Prologue
    addi sp sp -24
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    # i initially store the s2 here and s2=a2, and use the old s2 below
    sw a2 12(sp)
    sw a3 16(sp)
    sw ra 20(sp)
    
    mul s0 a2 a3 # s0=elements
    mv s1 a1 # s1=&arr
    li a1 1
    jal fopen
    li t0 -1
    beq a0 t0 fopen_error
    mv s2 a0 # s2=descriptor
    
    # store the row and col
    mv a0 s2
    addi a1 sp 12
    li a2 1
    li a3 4
    jal fwrite
    li t0 1
    bne a0 t0 fwrite_error
    mv a0 s2
    addi a1 sp 16
    li a2 1
    li a3 4
    jal fwrite
    li t0 1
    bne a0 t0 fwrite_error
    
    # write the data  
    mv a0 s2
    mv a1 s1
    mv a2 s0
    li a3 4 # 4 bytes
    jal fwrite
    bne a0 s0 fwrite_error
    mv a0 s2
    jal fclose
    li t0 -1
    beq a0 t0 fclose_error
    # Epilogue  
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw a2 12(sp)
    lw a3 16(sp)
    lw ra 20(sp)
    addi sp sp 24
    jr ra
fopen_error:
    li a0 27
    j exit
fwrite_error:
    li a0 30
    j exit
fclose_error:
    li a0 28
    j exit