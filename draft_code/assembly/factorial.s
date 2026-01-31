.text
main:
    li a0 3
    jal ra factorial
    j exit
factorial:
    addi sp sp -8
    sw ra 0(sp)
    sw s0 4(sp)
    mv s0 a0
    li t0 1
    bne s0 t0 recurse
    li a0 1
    j epilogue
recurse:
    addi a0 s0 -1
    jal ra factorial
    mul a0 s0 a0
epilogue:
    lw ra 0(sp)
    lw s0 4(sp)
    addi sp sp 8
    jr ra

exit:
    mv a1 a0 # print the result of factorial
    li a0 1
    ecall 

    addi a0 x0 17
    addi a1 x0 0
    ecall
