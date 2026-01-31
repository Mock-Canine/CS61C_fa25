.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    li t0 1
    bge a1 t0 loop_start
    li a0 36
    j exit
loop_start:
    li t0 0
    li t1 0
    lw t2 0(a0)
    mv t3 a0
loop_continue:
    beq t0 a1 loop_end
    lw t4 0(t3)
    bge t2 t4 less
    mv t2 t4
    mv t1 t0
less:
    addi t0 t0 1
    addi t3 t3 4
    j loop_continue
loop_end:
    # Epilogue
    mv a0 t1
    jr ra
