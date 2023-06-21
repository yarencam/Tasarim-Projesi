/*
 * app.c
 *
 *  Created on: Jun 17, 2023
 *      Author: Yaren CAM/Elif Altiparmak
 *
 *  Basınç Sensörü: https://wiki.dfrobot.com/Gravity__Water_Pressure_Sensor_SKU__SEN0257
 *  STM32 DMA ADC : http://www.elektrobot.net/stm32-adc-kullanimi-polling-interrupt-ve-dma/
 */

#include "app.h"
#include "main.h"
#include "gsm.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

#define BUFF_SIZE 100
uint8_t convEnd = 0;

uint16_t adcBuff[BUFF_SIZE] = { 0 };
uint16_t adcData[BUFF_SIZE] = { 0 };

const float offSet = 0.483;
float V, P;

/*
 * Alarm oluşturmak için değer aralığı
 *
 * Örnek olarak verilmiştir, gerçek değerler kullanıcının sisteminden alınmalıdır.
 */
float min = 0.3;
float max = 0.7;

int is_active = 0;
uint16_t adcDeger = 0;

void app_init()
{
	V = 0;
	P = 0;

	// Varsayılan durum aktif değil
	HAL_GPIO_WritePin(LED_ACT_GPIO_Port, LED_ACT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_DEACT_GPIO_Port, LED_DEACT_Pin, GPIO_PIN_SET);

	// Varsayılan Role durumu AÇIK (Kullanılacak yakıt kesicinin özelliğine göre değişebilir.)
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcBuff, BUFF_SIZE);

	gsm_init();
}

void app_process()
{
	if (is_active) {
		HAL_GPIO_WritePin(LED_ACT_GPIO_Port, LED_ACT_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_DEACT_GPIO_Port, LED_DEACT_Pin, GPIO_PIN_RESET);
		if (convEnd == 1) {
			V = 0;
			// Okunan değerlerin ortalamasını al
			for (int i = 0; i < BUFF_SIZE; i++)
				V += adcData[i];			// Okunan Değerlerin toplamını bul
			V /= BUFF_SIZE;					// Değer sayısına böl
			V *= 5.00 / 1024;				// Voltaj değerini hesapla
			P = (V - offSet) * 250;			// Basınç değerini hesapla

			if (P < min) {
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
				gsm_send_message("Basinc cok düsük. Sistem durduruldu!");
			} else if (P > max) {
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
				gsm_send_message("Basinc cok yuksek. Sistem durduruldu!");
			} else
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);

			convEnd = 0;
		}

	} else {
		HAL_GPIO_WritePin(LED_ACT_GPIO_Port, LED_ACT_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_DEACT_GPIO_Port, LED_DEACT_Pin, GPIO_PIN_SET);
	}
}

/*
 * Buton basılma olayını yakalar ve gerekli değişkeni ayarlar.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin) {
	case BTN_ACTIVATE_Pin:
		is_active = 1;
		break;
	case BTN_DEACTIVATE_Pin:
		is_active = 0;
		break;
	default:
		break;
	}
}

/*
 * ADC Okuma yaptığında bu fonksiyon çağırılacak
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if (hadc == &hadc1) {
		for (int i = 0; i < BUFF_SIZE; i++) {
			adcData[i] = adcBuff[i];
		}
		convEnd = 1;
	}
}
