#include "user.h"

extern char __stack_top[];

/* exit 函數，當程序結束時進入無限循環 */
__attribute__((noreturn)) void exit(void) {
    for (;;);
}

/* putchar 函數，用於輸出字符（此處暫未實作） */
void putchar(char ch) {
    /* TODO: 實現字符輸出 */
}

/* 程序入口函數 start，放到 .text.start 段 */
__attribute__((section(".text.start")))
__attribute__((naked))
void start(void) {
    __asm__ volatile (
        "mv sp, %[stack_top] \n"  /* 將棧指針設置為 __stack_top */
        "call main           \n"  /* 調用 main 函數 */
        "call exit           \n"  /* 調用 exit 函數結束程序 */
        :: [stack_top] "r" (__stack_top)
    );
}

