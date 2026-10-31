.text

.extern main

.global _start
.type _start, @function
_start:
    call main
    movq %rax, %rdi
    movq $60, %rax
    syscall
    ret