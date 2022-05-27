/*
 * scd30.c
 *
 *  Created on: 25 gru 2021
 *      Author: User
 */
#include "printf_uart.h"
#include "i2c.h"

static const uint8_t TMP102_ADDR = 0x61 << 1; // Use 8-bit address


HAL_StatusTypeDef ret;
uint8_t buf[18];  //for received data
uint8_t bufT[2]={0x03,0x00};  //read measurement command
uint8_t trigger[5]={0x00,0x10,0x00,0x00, 0x81}; //triger continous data
uint8_t stop[2] = {0x01,0x04};

//Odczyt Firmwearu
uint8_t frT[2]={0xd1,0x00};
uint8_t frR[3];

uint8_t TIntT[5]={0x46,0x00,0x00,0x02, 0xe3};
uint8_t RIntT[2]={0x46,0x00};
uint8_t RIntR[3];

uint8_t TascT[2]={0x53,0x06, 00, 00};
uint8_t RascT[2]={0x53,0x06};
uint8_t RascR[3];

uint8_t TfrcT[2]={0x52,0x04, 0x01, 0xc2};
uint8_t RfrcT[2]={0x52,0x04};
uint8_t RfrcR[3];

uint8_t startT[2]={0x02,0x02};
uint8_t startR[3];

//Altitude Compensation
uint8_t WaltT[5]={0x51,0x02, 0x01, 0x2C, 0x8E};
uint8_t RaltT[2]={0x51,0x02};
uint8_t RaltR[3];

//Odczyt Firmwearu

void readfirm()
{
  	 HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, &frT, 2, HAL_MAX_DELAY);
  	  HAL_Delay(5);
  	  HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, &frR, 3, HAL_MAX_DELAY);
  	  HAL_Delay(5);
  	  printf("\n");
  	  printf("Firmwear version: %d.%d\n",frR[0], frR[1]);
}


//Altitude Compensation

void altComp()
{
   /*   uint16_t AlComW = (uint16_t*)( (WaltT[2] << 8) | WaltT[3]);
  	  if(HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, &WaltT, 5, HAL_MAX_DELAY) == HAL_OK)
  	  {
  		  printf("Altitude compensation saved as %lu\n ", AlComW);
  	  }*/

  	  HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, &RaltT, 2, HAL_MAX_DELAY);
      HAL_Delay(5);
      HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, &RaltR, 3, HAL_MAX_DELAY);
      uint16_t AlCom = (uint16_t*)( (RaltR[0] << 8) | RaltR[1]);
      printf("Altitude compensation: %lu\n",AlCom);
      HAL_Delay(5);
}

//Odczyt interwalu
void interRead()
{
/*	  HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, TIntT, 5, HAL_MAX_DELAY);
	  HAL_Delay(5);*/

	  HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, RIntT, 2, HAL_MAX_DELAY);
  	  HAL_Delay(5);
  	  HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, RIntR, 3, HAL_MAX_DELAY);
  	  HAL_Delay(5);

  	  printf("\n");
      printf("Interwal = %d s\n", RIntR[1]);
}
      /*
 //Odczyt kalibracji ASC
      	  HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, &TascT, 4, HAL_MAX_DELAY);
          HAL_Delay(5);
      	  HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, &RascT, 2, HAL_MAX_DELAY);
          HAL_Delay(5);
          HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, &RascR, 3, HAL_MAX_DELAY);

        	printf("\n");
        	printf("Kalibracja ASC:\n", RascR[1]);

//Odczyt korekcji FR
          // HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, TascT, 4, HAL_MAX_DELAY);
           HAL_Delay(5);
           HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, &RfrcT, 2, HAL_MAX_DELAY);
           HAL_Delay(5);
           HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, &RfrcR, 3, HAL_MAX_DELAY);
           HAL_Delay(5);

           uint16_t korCO2 = (uint16_t*)((RfrcR[0] << 8) | RfrcR[1]);
           printf("\n");
           printf("Korekcja FRC: %lu ppm\n", korCO2);
*/
void triggerStart()
{
        HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, trigger, 5, HAL_MAX_DELAY);
}

void triggerStop()
{
  //      HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, stop, 2, HAL_MAX_DELAY);
}


//Test gotowosci

	/*    HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, startT, 2, HAL_MAX_DELAY);
	  HAL_Delay(5);
	  HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, startR, 3, HAL_MAX_DELAY);


		  if(startR[0] != 0)
		  {
		      printf("Dostepny odczyt:%d\n", startR[0]);
			  printf("Dostepny odczyt:%d\n", startR[1]);

		  }
*/
	  // Tell TMP102 that we want to read from the temperature register

void odczyt()
{
	       HAL_I2C_Master_Transmit(&hi2c1, TMP102_ADDR, bufT, 2, HAL_MAX_DELAY);

	    	  HAL_Delay(5);
	        // Read 2 bytes from the temperature register
	        HAL_I2C_Master_Receive(&hi2c1, TMP102_ADDR, buf, 18, HAL_MAX_DELAY);

	      uint32_t CO2 = (uint32_t*)((buf[0] << 24) |(buf[1] << 16) |(buf[3] << 8) | buf[4]);
	      uint32_t temp = (uint32_t)((buf[6] << 24) |(buf[7] << 16) |(buf[9] << 8) | buf[10]);
	      uint32_t wilg = (uint32_t)((buf[12] << 24) |(buf[13] << 16) |(buf[15] << 8) | buf[16]);

	      float CO2_f = *(float*)&CO2;
	      float temp_f = *(float*)&temp;
	      float wilg_f = *(float*)&wilg;


	      printf("\n");
	      printf("Stezenie CO2 = %f ppm\n", CO2_f);
	      printf("Temperatura = %f °C\n", temp_f);
	      printf("Wilgotnosc = %f %RH\n", wilg_f);
	      printf("\n");
}

