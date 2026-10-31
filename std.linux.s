.text

.extern main
.extern __envp

.global _start
.type _start, @function
_start:
    xorq %rbp, %rbp
    movq (%rsp), %rdi              /* argc */
    leaq 8(%rsp), %rsi             /* argv */
    leaq 16(%rsp,%rdi,8), %rdx     /* envp follows argv's NIL terminator */
    movq %rdx, __envp(%rip)        /* also needed by cmd_run */
    call main
    movq %rax, %rdi
    movq $60, %rax                /* exit(main's return value) */
    syscall
    hlt
.size _start, .-_start

.section .note.GNU-stack,"",@progbits
