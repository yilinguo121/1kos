#pragma once

// 基本型別定義
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;
typedef uint32_t paddr_t; // 如果還沒有定義
paddr_t alloc_pages(uint32_t n);

void map_page(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);

// 定義物理地址型別，根據平台可以調整
typedef uint32_t paddr_t;

// 致命錯誤處理宏
#define PANIC(fmt, ...)                                                        \
    do {                                                                       \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);  \
        while (1) {}                                                           \
    } while (0)

// 頁面相關定義
#define PAGE_SIZE 4096
#define SATP_SV32 (1u << 31)
#define PAGE_V    (1 << 0)   // 有效位（表项已启用）
#define PAGE_R    (1 << 1)   // 可读
#define PAGE_W    (1 << 2)   // 可写
#define PAGE_X    (1 << 3)   // 可执行
#define PAGE_U    (1 << 4)   // 用户（用户模式可访问）
// 应用程序镜像的基础虚拟地址。这需要与 `user.ld` 中定义的起始地址匹配。
#define USER_BASE 0x1000000
#define SSTATUS_SPIE (1 << 5)

// 內核鏈接符號，由鏈接腳本定義
extern char __kernel_base[];
extern char __free_ram[];
extern char __free_ram_end[];

// 函式原型：分配 n 個物理頁
paddr_t alloc_pages(uint32_t n);

// 工具函式：檢查 addr 是否以 alignment 對齊
static inline int is_aligned(uint32_t addr, uint32_t alignment) {
    return (addr & (alignment - 1)) == 0;
}

#include "common.h"

// 進程的陷阱/異常保存上下文結構
struct trap_frame {
    uint32_t ra;
    uint32_t gp;
    uint32_t tp;
    uint32_t t0;
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;
    uint32_t t4;
    uint32_t t5;
    uint32_t t6;
    uint32_t a0;
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t a4;
    uint32_t a5;
    uint32_t a6;
    uint32_t a7;
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;
    uint32_t sp;
} __attribute__((packed));

// CSR 讀取與寫入宏
#define READ_CSR(reg)                                                          \
    ({                                                                         \
        unsigned long __tmp;                                                   \
        __asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp));                  \
        __tmp;                                                                 \
    })

#define WRITE_CSR(reg, value)                                                  \
    do {                                                                       \
        uint32_t __tmp = (value);                                              \
        __asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp));                \
    } while (0)

// 系统调用返回值结构
struct sbiret {
    long error;
    long value;
};

