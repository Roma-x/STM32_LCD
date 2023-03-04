#include "date.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>

extern RTC_HandleTypeDef hrtc;

int RTC_Set( uint8_t year, uint8_t month, uint8_t day,
			 uint8_t hour, uint8_t min,   uint8_t sec,
			 uint8_t dow) {
    HAL_StatusTypeDef res;
    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;

    memset(&time, 0, sizeof(time));
    memset(&date, 0, sizeof(date));

    date.WeekDay = dow;
    date.Year = year;
    date.Month = month;
    date.Date = day;

    res = HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);
    if(res != HAL_OK) {
        printf("HAL_RTC_SetDate failed: %d\r\n", res);
        return -1;
    }

    time.Hours = hour;
    time.Minutes = min;
    time.Seconds = sec;

    res = HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
    if(res != HAL_OK) {
        printf("HAL_RTC_SetTime failed: %d\r\n", res);
        return -2;
    }

    return 0;
}
void setDate(int year, int month, int date, int hours, int min, int sec)
{
	RTC_Set(year, month, date, hours, min, sec, 3);
}

void getDate(char *monthDay, char *timeNow)
{
	  RTC_TimeTypeDef time;
	  RTC_DateTypeDef date;
	  HAL_StatusTypeDef res;
	  char *weekDay;

	  res = HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	  if(res != HAL_OK) {
	      printf("HAL_RTC_GetTime failed: %d\r\n", res);
	      return;
	  }
	  sprintf(timeNow, "%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
	  res = HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
	  if(res != HAL_OK) {
	      printf("HAL_RTC_GetDate failed: %d\r\n", res);
	      return;
	  } else {
		  switch (date.WeekDay){
		  	  case 1:
		  		  weekDay = "Mon";
		  		  break;
		  	  case 2:
		  		  weekDay = "Tue";
		  		  break;
		  	  case 3:
		  		  weekDay = "Wed";
		  		  break;
		  	  case 4:
		  		  weekDay = "Thu";
		  		  break;
		  	  case 5:
		  		  weekDay = "Fri";
		  		  break;
		  	  case 6:
		  		  weekDay = "Sat";
		  		  break;
		  	  case 7:
		  		  weekDay = "Sun";
		  		  break;
		  	  default:
		  		  weekDay = NULL;
		  }
	  }
	  sprintf(monthDay, "%02d %s", date.Month, weekDay);
}
