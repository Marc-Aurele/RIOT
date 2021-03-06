/*
 * Copyright (C) 2014 Freie Universität Berlin, Hinnerk van Bruinehsen
 *               2016 Laurent Navet <laurent.navet@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/*
 * @defgroup    boards_common_arduino-atmega Arduino Atmega Common
 * @ingroup     boards_common
 * @brief       Shared files and configuration for Arduino Atmega boards.
 * @{
 *
 * @file
 * @brief       Common board configuration for Arduino Atmega boards
 *
 * @author      Hinnerk van Bruinehsen <h.v.bruinehsen@fu-berlin.de>
 * @author      Laurent Navet <laurent.navet@gmail.com>
 */

#ifndef BOARD_COMMON_H
#define BOARD_COMMON_H

#include "cpu.h"
#include "arduino_pinmap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    STDIO configuration
 *
 * As the CPU is too slow to handle 115200 baud, we set the default
 * baudrate to 9600 for this board
 * @{
 */
#define UART_STDIO_BAUDRATE (9600U)
/** @} */

/**
 * @name    LED pin definitions and handlers
 * @{
 */
#ifdef CPU_ATMEGA328P
#define LED0_PIN            GPIO_PIN(1, 5)
#define LED0_MASK           (1 << DDB5)
#endif

#ifdef CPU_ATMEGA2560
#define LED0_PIN            GPIO_PIN(1, 7)
#define LED0_MASK           (1 << DDB7)
#endif

#define LED0_ON             (PORTB |=  LED0_MASK)
#define LED0_OFF            (PORTB &= ~LED0_MASK)
#define LED0_TOGGLE         (PORTB ^=  LED0_MASK)
/** @} */

/**
 * @brief   Context swap defines
 *
 * Setup to use PC5 which is pin change interrupt 13 (PCINT13)
 * This emulates a software triggered interrupt
 */
#ifdef CPU_ATMEGA328P
#define AVR_CONTEXT_SWAP_INIT do { \
            DDRD |= (1 << PD7); \
            PCICR |= (1 << PCIE2); \
            PCMSK2 |= (1 << PCINT23); \
} while (0)
#define AVR_CONTEXT_SWAP_INTERRUPT_VECT  PCINT2_vect
#define AVR_CONTEXT_SWAP_TRIGGER   PORTD ^= (1 << PD7)
#endif

#ifdef CPU_ATMEGA2560
#define AVR_CONTEXT_SWAP_INIT do { \
    DDRJ |= (1 << PJ6); \
    PCICR |= (1 << PCIE1); \
    PCMSK1 |= (1 << PCINT15); \
} while (0)
#define AVR_CONTEXT_SWAP_INTERRUPT_VECT  PCINT1_vect
#define AVR_CONTEXT_SWAP_TRIGGER   PORTJ ^= (1 << PJ6)
#endif

/**
 * @name    xtimer configuration values
 * @{
 */
#define XTIMER_WIDTH                (16)
#define XTIMER_HZ                   (250000UL)
#define XTIMER_BACKOFF              (40)
/** @} */

/**
 * @brief   Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_COMMON_H */
/** @} */
