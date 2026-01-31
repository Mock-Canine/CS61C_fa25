.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue
    li t0 1
    bge a1 t0 normal
    li a0 36
    j exit
normal:
    li t0 0
    mv t1 a0
loop_start:
    beq t0 a1 end
    lw t2 0(t1)
    bge t2 x0 loop_continue
    sw x0 0(t1)
loop_continue:
    addi t0 t0 1
    addi t1 t1 4
    j loop_start
    # Epilogue
end:
    jr ra
