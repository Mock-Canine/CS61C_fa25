.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    # Prologue
    addi t0 x0 1
    bge a2 t0 valid_num
    addi a0 x0 36
    j exit
valid_num:
    blt a3 t0 invalid_stride
    blt a4 t0 invalid_stride
    add t0 x0 x0 # i=0
    add t1 x0 x0 # sum=0
    slli t2 a3 2 # step_length
    slli t3 a4 2
    j loop_start
invalid_stride:
    addi a0 x0 37
    j exit
loop_start:
    beq t0 a2 loop_end
    lw t4 0(a0)
    lw t5 0(a1)
    mul t6 t4 t5
    add t1 t1 t6 # sum+=value
    addi t0 t0 1 # i++
    add a0 a0 t2
    add a1 a1 t3
    j loop_start
loop_end:
    # Epilogue
    mv a0 t1
    jr ra
