__attribute__((noreturn)) void _start(void) {
    static const char message[] = "Hello, world!\n";

    /* write(1, message, sizeof(message) - 1) */
    __asm__ (
        "syscall"
        :
        : "a"(1), /* SYS_write */
          "D"(1), /* stdout */
          "S"(message),
          "d"(sizeof(message) - 1)
        : "rcx", "r11", "memory"
    );

    /* exit(0) */
    __asm__ (
        "syscall"
        :
        : "a"(60), /* SYS_exit */
          "D"(0)
        : "rcx", "r11", "memory"
    );

    __builtin_unreachable();
}
