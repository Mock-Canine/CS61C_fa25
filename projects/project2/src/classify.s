.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
    li t0 5
    bne a0 t0 command_error
    addi sp sp -52
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw s7 28(sp)
    sw s8 32(sp)
    sw s9 36(sp)
    sw s10 40(sp)
    sw s11 44(sp)
    sw ra 48(sp)
    
    lw s0 4(a1) # s is path pointer m0
    lw s1 8(a1) # m1
    lw s2 12(a1) # input
    lw s3 16(a1) # output
    mv s4 a2 # silent mode
    
    # allocate memory
    li a0 24 
    jal malloc
    # do not handle the allocated memory if fail??
    beqz a0 malloc_error 
    mv s5 a0 # s5=&allocated
    # Read pretrained m0
    mv a0 s0
    mv a1 s5
    addi a2 s5 4
    jal read_matrix
    mv s6 a0 # s6=&m0
    # Read pretrained m1
    mv a0 s1
    addi a1 s5 8
    addi a2 s5 12
    jal read_matrix
    mv s7 a0 # s7=&m1
    # Read input matrix
    mv a0 s2
    addi a1 s5 16
    addi a2 s5 20
    jal read_matrix
    mv s8 a0 # s8=&m_input
    # Compute h = matmul(m0, input)
    lw t0 0(s5) 
    lw t1 20(s5)
    mul a0 t0 t1
    slli a0 a0 2
    jal malloc
    beqz a0 malloc_error 
    mv s9 a0 # s9=&h
    
    mv a0 s6
    lw a1 0(s5) # n
    lw a2 4(s5) # m
    mv a3 s8
    lw a4 16(s5) # m
    lw a5 20(s5) # k
    mv a6 s9
    jal matmul
    # Compute h = relu(h)
    mv a0 s9
    lw t0 0(s5)
    lw t1 20(s5)
    mul a1 t0 t1
    jal relu
    # Compute o = matmul(m1, h)
    lw t0 8(s5) 
    lw t1 20(s5)
    mul a0 t0 t1
    slli a0 a0 2
    jal malloc
    beqz a0 malloc_error 
    mv s10 a0 # s10=&o
    
    mv a0 s7
    lw a1 8(s5)
    lw a2 12(s5)
    mv a3 s9
    lw a4 0(s5) # demension of h 
    lw a5 20(s5)
    mv a6 s10
    jal matmul  
    # Write output matrix o
    mv a0 s3
    mv a1 s10
    lw a2 8(s5)
    lw a3 20(s5)
    jal write_matrix
    # Compute and return argmax(o)
    mv a0 s10
    lw t0 8(s5)
    lw t1 20(s5)
    mul a1 t0 t1
    jal argmax
    mv s11 a0 # s11=argmax_return
    # If enabled, print argmax(o) and newline
    bnez s4 return
    mv a0 s11
    jal print_int
    li a0 '\n'
    jal print_char
return:
    # free data
    mv a0 s5
    jal free
    mv a0 s6
    jal free
    mv a0 s7
    jal free
    mv a0 s8
    jal free
    mv a0 s9
    jal free
    mv a0 s10
    jal free
    
    # prepare return value
    mv a0 s11
    
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw s7 28(sp)
    lw s8 32(sp)
    lw s9 36(sp)
    lw s10 40(sp)
    lw s11 44(sp)
    lw ra 48(sp)
    addi sp sp 52
    jr ra
command_error:
    li a0 31
    j exit
malloc_error:
    li a0 26
    j exit