/*
 * Auto generated Run-Time-Environment Component Configuration File
 *      *** Do not modify ! ***
 *
 * Project: Blinky (V2M-MPS3-SSE-310)
 * RTE configuration: Blinky (V2M-MPS3-SSE-310).rteconfig
*/
#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H

/*
 * Define the Device Header File:
*/
#define CMSIS_device_header "SSE310MPS3.h"

/* ARM::CMSIS Driver.I2C */
#define RTE_I2C0      1

/* ARM::CMSIS Driver.MPC */
#define RTE_SRAM_MPC      1
        #define RTE_ISRAM0_MPC    1
        #define RTE_ISRAM1_MPC    1
        #define RTE_QSPI_MPC      1
        #define RTE_DDR4_MPC      0
        #define RTE_VM0_MPC       1
        #define RTE_VM1_MPC       1
        #define RTE_SSRAM2_MPC    1
        #define RTE_SSRAM3_MPC    1
/* ARM::CMSIS Driver.PPC */
#define RTE_MAIN0_PPC_CORSTONE310            1
        #define RTE_MAIN_EXP0_PPC_CORSTONE310        1
        #define RTE_MAIN_EXP1_PPC_CORSTONE310        1
        #define RTE_MAIN_EXP2_PPC_CORSTONE310        1
        #define RTE_MAIN_EXP3_PPC_CORSTONE310        1
        #define RTE_PERIPH0_PPC_CORSTONE310          1
        #define RTE_PERIPH1_PPC_CORSTONE310          1
        #define RTE_PERIPH_EXP0_PPC_CORSTONE310      1
        #define RTE_PERIPH_EXP1_PPC_CORSTONE310      1
        #define RTE_PERIPH_EXP2_PPC_CORSTONE310      1
        #define RTE_PERIPH_EXP3_PPC_CORSTONE310      1
/* ARM::CMSIS Driver.SPI */
#define RTE_SPI0      0

/* ARM::CMSIS Driver.USART */
#define RTE_USART0      1
#define RTE_USART1      1

/* ARM::Native Driver.Audio I2S */
#define RTE_I2S      1
/* ARM::Native Driver.IO */
#define RTE_MPS3_IO      1
/* ARM::Native Driver.SysCounter */
#define RTE_SYSCOUNTER      1
/* ARM::Native Driver.Timeout */
#define RTE_TIMEOUT      1
/* ARM::Native Driver.Watchdog */
#define RTE_WATCHDOG      1
/* Keil.ARM Compiler::Compiler.I/O.STDOUT.User */
#define RTE_Compiler_IO_STDOUT          /* Compiler I/O: STDOUT */
          #define RTE_Compiler_IO_STDOUT_User     /* Compiler I/O: STDOUT User */

#endif /* RTE_COMPONENTS_H */
