/*
 * printf_uart.c
 *
 *  Created on: Dec 22, 2021
 *      Author: User
 */
#include <stdio.h>
#include <printf_uart.h>
#include "usart.h"

int __io_putchar(int ch)
{
  if (ch == '\n') {
    __io_putchar('\r');
  }

  HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

  return 1;
}
