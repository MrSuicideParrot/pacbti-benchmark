/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "blinky_thread.h"
#include "common_utils.h"


extern bsp_leds_t g_bsp_leds;

char* super_secret_flag = "my-super-secret";

void __attribute__ ((noinline, used)) win_function(){
    APP_PRINT("Congrats function executed!!\r\n");
}

void echo_processing(int size) {
    int message_length = size;
    int array_length = size;

    if (array_length > 40) {
    array_length = 40;
    }
    char buffer[array_length];
    int result;
    do {
    result = APP_READ_S(buffer, 100);
    /*if(result > 0){
        APP_PRINT("Read scan from %d", result);
        for(int i = 0; i < result; ++i) {
            APP_PRINT("%x", buffer[i]);
        }
    }*/
    } while(result != 0);
    buffer[message_length] = '\0';
    APP_PRINT("Message received  %d !\r\nProcessing\r\n", result);
}

void printf_processing(int size) {
    int message_length = size;
    int array_length = size;

    if (array_length > 40) {
    array_length = 40;
    }
    char buffer[array_length];
    int result = APP_READ_S(buffer, message_length);
    buffer[message_length] = '\0';
    APP_PRINT("Message received  %d !\r\nProcessing\r\n", result);

    APP_PRINT("\r\n");
    APP_PRINT("Feito\r\n");
}

int static_message_size() {
    return 8;
}

int static_message2_size() {
    return 150;
}

int hex_message_size() {
    uint8_t message[21];
    APP_READ_S(message, 4);
    return (int)strtol(message, NULL, 16);
}

void custom_message_size(int type) {
     int (*p[3]) ();
    p[0] = static_message_size;
    p[1] = hex_message_size;
    p[2] = static_message2_size;

    while(1) {
        int size = p[type]();

        int message_length = size;
        int array_length = size;

        if (array_length > 40) {
            array_length = 40;
        }

        char buffer[array_length];
        int result = APP_READ_S(buffer, message_length);
        buffer[message_length] = '\0';
        APP_PRINT("Message received  %d !\r\nProcessing\r\n", result);
    }
}

void alloc_message(int size){
    int message_length = size;

    char* buffer = (char *)malloc(size);

    int result;
    do {
    result = APP_READ_S(buffer, message_length);
    } while(result == 0);

    APP_PRINT("Message received and stored at: %p\r\n", buffer);
}

void print_stored_message(int size){
    int message_length = size;

    char buffer[4];

    int result;
    do {
    result = APP_READ_S(buffer, 4);
    } while(result != 0);

    APP_PRINT(buffer);
}

void write_message_somwehere(int size) {
    unsigned int target;
    int result;
     do {
     result = APP_READ_S(&target, 4);
     } while(result == 0);

     do {
     result = APP_READ_S((void*)target, size);
     } while(result == 0);
}

void launch_function(int size) {
    void (*target)();
    int result;
     do {
     result = APP_READ_S(&target, 4);
     } while(result == 0);

     target();
}


/* Blinky Thread entry function */
void blinky_thread_entry (void)
{
    __asm volatile(
          // CONTROL register: set UPAC_EN to enable PAC in privileged mode.
         //"BKPT\n\t"
         "mrs    r2,CONTROL\n\t"
         "orr    r2,r2,#0x00000040\n\t"
         "orr    r2,r2,#0x00000080\n\t"
         "msr    CONTROL,r2\n\t"

          // CONTROL register: set UBTI_EN, to enable BTI in privileged mode.
         "mrs    r2,CONTROL\n\t"
         "orr    r2,r2,#0x00000010\n\t"
         "orr    r2,r2,#0x00000020\n\t"
         "msr    CONTROL,r2\n\t"
      );

    /* LED type structure */
    bsp_leds_t leds = g_bsp_leds;

    /* If this board has no LEDs then trap here */
    if (0 == leds.led_count)
    {
        while (1)
        {
            ;                          // There are no LEDs on this board
        }
    }

    /* Holds level to set for pins */
    bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

    while (1)
    {
        uint8_t header[2];
        uint8_t size;
        do {
        size = APP_READ_S(header, 2);
        } while(size != 2);
        APP_PRINT("Read size %d", size);

        switch (header[0])
        {
        case 1:
            APP_PRINT("ECHO with length - %d.\r\n", header[1]);
            //printf_processing(header[1]);
            echo_processing(header[1]);
            break;

        case 2:
            custom_message_size(header[1]);
            break;
        case 3:
            alloc_message(header[1]);
            break;
        case 4:
            print_stored_message(header[1]);
            break;
        case 5:
            write_message_somwehere(header[1]);
            break;
        case 6:
            launch_function(header[1]);
            break;
        default:
            APP_PRINT("Unknown %d\r\n", header[0]);
            break;
        }

        APP_PRINT("HERE WE GO AGAIN\r\n");
    }


    while (1)
    {
        /* Enable access to the PFS registers. If using r_ioport module then register protection is automatically
         * handled. This code uses BSP IO functions to show how it is used.
         */
        R_BSP_PinAccessEnable();

        /* Update all board LEDs */
        for (uint32_t i = 0; i < leds.led_count; i++)
        {
            /* Get pin to toggle */
            uint32_t pin = leds.p_leds[i];

            /* Write to this pin */
            R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level);
        }

        /* Protect PFS registers */
        R_BSP_PinAccessDisable();

        /* Toggle level for next write */
        if (BSP_IO_LEVEL_LOW == pin_level)
        {
            pin_level = BSP_IO_LEVEL_HIGH;
        }
        else
        {
            pin_level = BSP_IO_LEVEL_LOW;
        }

        tx_thread_sleep(TX_TIMER_TICKS_PER_SECOND);
    }
}
