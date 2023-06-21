/*
 * gsm.c
 *
 *  Created on: Jun 19, 2023
 *      Author: Yaren CAM/Elif Altiparmak
 *
 *  SIM800L Kullanimi: https://mevihub.com/gsm-sms-stm32/
 *  SIM800L SMS SEND : https://mehmettopuz.net/stm32-ve-gsm-modul-ile-sms-gonderme/.html
 *  SIM800L AT CMD   : https://www.waveshare.com/w/upload/2/20/SIM800_Series_AT_Command_Manual_V1.09.pdf
 */

#include "gsm.h"
#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart1;

char cmd[30];
uint8_t buf[30] = { 0 };

char mobile[] = "Mobile Number";  // Buraya alıcı telefon no gelecek

void gsm_init()
{
	uint8_t flag = 1;

	while (flag) {
		sprintf(cmd, "AT\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*) cmd, strlen(cmd), 1000);
		HAL_UART_Receive_IT(&huart1, buf, 30);

		HAL_Delay(1000);

		if (strstr((char*) buf, "OK"))
			flag = 0;

		HAL_Delay(1000);
		memset(buf, 0, sizeof(buf));
	}
}

void gsm_send_message(const char *msg)
{
	// GSM Modülü TEXT moda al
	sprintf(cmd, "AT+CMGF=1\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*) cmd, strlen(cmd), 1000);
	HAL_UART_Receive_IT(&huart1, buf, 30);
	HAL_Delay(1000);

	// Mesaj gönderilecek alıcı numarasını bildir.
	sprintf(cmd, "AT+CMGS=\"%s\"\r\n", mobile);
	HAL_UART_Transmit(&huart1, (uint8_t*) cmd, strlen(cmd), 1000);
	HAL_Delay(100);

	// Mesajı gönder
	sprintf(cmd, "%s%c", msg, 0x1a);
	HAL_UART_Transmit(&huart1, (uint8_t*) cmd, strlen(cmd), 1000);

	HAL_UART_Receive_IT(&huart1, buf, 30);
	HAL_Delay(5000);
}
