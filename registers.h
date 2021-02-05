#ifndef REGISTERS_H
#define REGISTERS_H

/* GPIO */

#define ODR_OFF 0x0000
#define IDR_OFF 0x0001
#define DDR_OFF 0x0002
#define CR1_OFF 0x0003
#define CR2_OFF 0x0004

#define PA_BASE 0x5000
#define PB_BASE 0x5005
#define PC_BASE 0x500A
#define PD_BASE 0x500F
#define PE_BASE 0x5014
#define PF_BASE 0x5019

#define PA_ODR (PA_BASE + ODR_OFF)
#define PA_IDR (PA_BASE + IDR_OFF)
#define PA_DDR (PA_BASE + DDR_OFF)
#define PA_CR1 (PA_BASE + CR1_OFF)
#define PA_CR2 (PA_BASE + CR2_OFF)

#define PB_ODR (PB_BASE + ODR_OFF)
#define PB_IDR (PB_BASE + IDR_OFF)
#define PB_DDR (PB_BASE + DDR_OFF)
#define PB_CR1 (PB_BASE + CR1_OFF)
#define PB_CR2 (PB_BASE + CR2_OFF)

#define PC_ODR (PC_BASE + ODR_OFF)
#define PC_IDR (PC_BASE + IDR_OFF)
#define PC_DDR (PC_BASE + DDR_OFF)
#define PC_CR1 (PC_BASE + CR1_OFF)
#define PC_CR2 (PC_BASE + CR2_OFF)

#define PD_ODR (PD_BASE + ODR_OFF)
#define PD_IDR (PD_BASE + IDR_OFF)
#define PD_DDR (PD_BASE + DDR_OFF)
#define PD_CR1 (PD_BASE + CR1_OFF)
#define PD_CR2 (PD_BASE + CR2_OFF)

#define PE_ODR (PE_BASE + ODR_OFF)
#define PE_IDR (PE_BASE + IDR_OFF)
#define PE_DDR (PE_BASE + DDR_OFF)
#define PE_CR1 (PE_BASE + CR1_OFF)
#define PE_CR2 (PE_BASE + CR2_OFF)

#define PF_ODR (PF_BASE + ODR_OFF)
#define PF_IDR (PF_BASE + IDR_OFF)
#define PF_DDR (PF_BASE + DDR_OFF)
#define PF_CR1 (PF_BASE + CR1_OFF)
#define PF_CR2 (PF_BASE + CR2_OFF)

/* UART */

#define UART1_BASE      0x005230
/* #define UART2_BASE      0x005230  */
/* #define UART3_BASE      0x005230 */
/* #define UART4_BASE      0x005230 */
#define UART_SR_OFF     0x00     // Status
#define UART_DR_OFF     0x01     // Data
#define UART_BRR1_OFF   0x02     // Clock divider 1
#define UART_BRR2_OFF   0x03     // Clock divider 2
#define UART_CR1_OFF    0x04     // Control 1
#define UART_CR2_OFF    0x05     // Control 2

/* CLOCK */
#define CLK_BASE        0x0050C0
#define CLK_CKDIVR_OFF  0x000006

#define CLK_CKDIVR      (uint8_t*) (CLK_BASE + CLK_CKDIVR_OFF)

#endif
