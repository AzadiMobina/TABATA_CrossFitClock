






/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
 
 
 
 
 
 

#include "initialization.h"


uint8_t irRemote_feedback;


main()
{
	
	uint8_t irRemote_feedback;
	uint8_t segments_value_present[7];
	uint8_t segments_value_last[7];
	int8_t i;
	int8_t j;
	uint8_t flag_tempreture_read = 0;
	int8_t tempreture = 25;
	uint8_t dotpint_state = 1;
	uint8_t dotpint_state_last = 0;
	//uint8_t part=10;

	Initializer();

	DS3231_GetTime(&time_Hour , &time_Minute , &time_Second);

	enableInterrupts();

	StartUp_Show();

	while (1)
	{
		if(work_Mode == MODE_NORMAL)
		{
			if ((mode_show_12 == 1) && (time_Hour > 12))
			{
				segments_value_present[0] = (time_Hour-12)/10;
				segments_value_present[1] = (time_Hour-12)%10;
			}
			else
			{
				segments_value_present[0] = time_Hour/10;
				segments_value_present[1] = time_Hour%10;

			}
			
			segments_value_present[2] = time_Minute/10;
			segments_value_present[3] = time_Minute%10;
			segments_value_present[4] = time_Second/10;
			segments_value_present[5] = time_Second%10;

			if(mode_show_OFF == 1)
				dotpint_state = 0;
			else
				dotpint_state = 1;

			
			if(((time_Second > 10) && (time_Second < 13)) || ((time_Second > 40) && (time_Second < 43)))
			{
				if(flag_tempreture_read == 0)
				{
					tempreture = NTC_Read();
					flag_tempreture_read = 1;
				}

				segments_value_present[0] = tempreture/10;
				segments_value_present[1] = tempreture%10;
				segments_value_present[2] = 'o';
				segments_value_present[3] = 'C';
				segments_value_present[4] = BLINK;
				segments_value_present[5] = BLINK;

				dotpint_state = 0;

			}
			else
			{
				flag_tempreture_read = 0;
			}

			/*if(GPIO_ReadInputPin() == RESET)
			{
				work_Mode =  MODE_COUNTER_UP;
				time_Minute_Cornometr = 0;
				time_Second_Cornometr = 0;
				Cornometr_run = 0;
				Buzz(200);

			}*/

			
			if(IRRemote_Ready)
			{
				irRemote_feedback = IRRemote_Read();
				if(irRemote_feedback == COLORCHANGE)
				{
					mode_show_OFF = 0;
					update_all = 1;
					Buzz(100);
				}
				else if(irRemote_feedback == KEY_1)
				{
					if(mode_show_12 == 1)
						mode_show_12 = 0;
					else
						mode_show_12 = 1;
					
					Buzz(100);
				}
				else if((irRemote_feedback == KEY_2))
				{
					work_Mode = MODE_SET_CLOCK_HOUR;
					time_Hour_settin = time_Hour;
					time_Minute_settin = time_Minute;
					time_UnNormal = 0;
					update_all = 1;
					Buzz(200);
				}
				
				else if(irRemote_feedback == KEY_3)
				{
					work_Mode = MODE_COUNTER_UP;
					time_Minute_Cornometr =0;
					time_Second_Cornometr = 0;
					Cornometr_run= 0;
					update_all = 1;
					Buzz(200);
				}
				

				else if(irRemote_feedback == ONN_STATUS)
				{
					mode_show_OFF = 0;
					update_all = 1;
					Buzz(100);
					delay_ms(200);
					Buzz(100);
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					mode_show_OFF = 1;
					update_all = 1;
					Buzz(300);
				}		
			}

			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(mode_show_OFF == 1)
					{
						Segment(i,segments_value_present[i],0,LEVEL_FULL);
					}
					else
					{
						if(segments_value_present[i] == BLINK)
							Segment(i,segments_value_present[i],0,LEVEL_FULL);
						else 
							Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);
							
					}
					segments_value_last[i] = segments_value_present[i];
					
				}
			}
			
			if((dotpint_state != dotpint_state_last) || (update_all == 1))
			{
				dotpint_state_last = dotpint_state;
				DotPoints(1,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
				//DotPoints(4,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
			}

			update_all = 0;
		}

		else if(work_Mode == MODE_SET_CLOCK_HOUR)
		{
			if(time_secbit == 0)
			{
				segments_value_present[0] = time_Hour_settin/10;
				segments_value_present[1] = time_Hour_settin%10;

			}
			else
			{
				segments_value_present[0] = BLINK;
				segments_value_present[1] = BLINK;
				
			}

			segments_value_present[2] = time_Minute_settin/10;
			segments_value_present[3] = time_Minute_settin%10;

			if(IRRemote_Ready)
			{
				time_UnNormal = 0;
				irRemote_feedback = IRRemote_Read();
				if(irRemote_feedback == INCREASE)
				{
					if(++time_Hour_settin > 23)
						time_Hour_settin = 0;
					
					Buzz(100);
				}
				else if(irRemote_feedback == DECREASE)
				{
					if(time_Hour_settin == 0)
						time_Hour_settin = 23;
					else
						time_Hour_settin--;
					
					Buzz(100);
				}
				else if(irRemote_feedback == KEY_1)
				{
					work_Mode = MODE_SET_CLOCK_MINUTE;
					Buzz(200);
				}
			}

			for (i = 0; i < 7; i++)
			{
				if(segments_value_present[i] != segments_value_last[i])
				{
					if(segments_value_present[i] == BLINK)
						Segment(i,segments_value_present[i],0,LEVEL_FULL);
					else
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);

					segments_value_last[i] = segments_value_present[i];
				}
			}

			dotpint_state = 1;
			if((dotpint_state != dotpint_state_last) || (update_all == 1))
			{
				dotpint_state_last = dotpint_state;
				DotPoints(1,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
				//DotPoints(4,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
			}
			update_all = 0;

		} 
		else if(work_Mode == MODE_SET_CLOCK_MINUTE)
		{
			if(time_secbit == 0)
			{
				segments_value_present[2] = time_Minute_settin/10;
				segments_value_present[3] = time_Minute_settin%10;
			}
			else
			{
				segments_value_present[2] = BLINK;
				segments_value_present[3] = BLINK;
			}

			segments_value_present[0] = time_Hour_settin/10;
			segments_value_present[1] = time_Hour_settin%10;
				

			if(IRRemote_Ready)
			{
				time_UnNormal = 0;
				irRemote_feedback = IRRemote_Read();
				if(irRemote_feedback == INCREASE)
				{
					if(++time_Minute_settin > 59)
						time_Minute_settin = 0;
					Buzz(100);
				}
				else if(irRemote_feedback == DECREASE)
				{
					if(time_Minute_settin == 0)
						time_Minute_settin = 59;
					else
						time_Minute_settin--;
					
					Buzz(100);
				}
				else if(irRemote_feedback == KEY_1)
				{
					work_Mode = MODE_NORMAL;
					time_Hour = time_Hour_settin;
					time_Minute = time_Minute_settin;
					DS3231_SetTime(time_Hour , time_Minute , (uint8_t)0);
					time_Second = 0;
					Buzz(300);
				}
			}

			for (i = 0; i < 7; i++)
			{
				if(segments_value_present[i] != segments_value_last[i])
				{
					if(segments_value_present[i] == BLINK)
						Segment(i,segments_value_present[i],0,LEVEL_FULL);
					else
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);

					segments_value_last[i] = segments_value_present[i];
				}
			}
		} 
		
		else if(work_Mode == MODE_COUNTER_UP)
		{
			time_UnNormal = 0;
			segments_value_present[0] = time_Minute_Cornometr/10;
			segments_value_present[1] = time_Minute_Cornometr%10;
			segments_value_present[2] = time_Second_Cornometr/10;
			segments_value_present[3] = time_Second_Cornometr%10;
			segments_value_present[4] = time_mili_Second_Cornometr/10;
			segments_value_present[5] = time_mili_Second_Cornometr%10;
			
			if(SETTING == DEFAULT)
			{
				
				if(Cornometr_run == 1)
				{
					
					time_mili_Second_Cornometr_temp+=13;
					if(time_mili_Second_Cornometr_temp>99)
					{
						time_mili_Second_Cornometr_temp = 0;
					}
					
					time_Second_Cornometr = time_Second_Cornometr_temp;
					time_Minute_Cornometr = time_Minute_Cornometr_temp;
					time_mili_Second_Cornometr = time_mili_Second_Cornometr_temp;
					if(GPIO_ReadInputPin() == RESET)
					{
						Cornometr_run = 0;
						time_Minute_Cornometr_temp = 0;
						time_Second_Cornometr_temp = 0;
						time_mili_Second_Cornometr_temp = 0;
						Buzz(500);
						delay_ms(50);
						Buzz(500);
					}
				}
			}

			if(IRRemote_Ready)
			{
				irRemote_feedback = IRRemote_Read();
				if(irRemote_feedback == COLORCHANGE)
				{
					update_all = 1;
					Buzz(100);
				}
				else if(irRemote_feedback == KEY_1)
				{
					Cornometr_run = 0;
					time_Minute_Cornometr= 0;
					time_Second_Cornometr = 0;
					Buzz(100);
					delay_ms(50);
					Buzz(100);

				}
				else if(irRemote_feedback == ONN_STATUS)
				{
					if(Cornometr_run == 0)
					{									
						Cornometr_run = 1;
						Buzz(200);
					}	
					else
					{
						Cornometr_run = 0;
						Buzz(200);
					}
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					Cornometr_run = 0;
					time_Minute_Cornometr = 0;
					time_Second_Cornometr = 0;
					work_Mode = MODE_NORMAL;
					Buzz(100);
				}


			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(i == 0)
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);
					else if(i == 1)
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);
					else
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);

					segments_value_last[i] = segments_value_present[i];
					
				}
			}

			dotpint_state = 1;
			if((dotpint_state != dotpint_state_last) || (update_all == 1))
			{
				dotpint_state_last = dotpint_state;
				DotPoints(1,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
				//DotPoints(4,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
			}

			update_all = 0;
			if(work_Mode != MODE_COUNTER_UP)
				update_all = 1;

		}
		
		


	
}

	}
}




























