#include "date.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>

extern RTC_HandleTypeDef hrtc;

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
