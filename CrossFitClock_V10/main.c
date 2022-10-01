


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
				
				else if(irRemote_feedback == ONN_STATUS)
				{
					work_Mode = MENU;
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



		else if(work_Mode == MENU )
		{
			time_UnNormal = 0;

			segments_value_present[0] = 'F';
			segments_value_present[1] = CONDITION;
			segments_value_present[2] = 'N';
			segments_value_present[3] = 'N';
			segments_value_present[4] = 'N';
			segments_value_present[5] = 'N';

			if(IRRemote_Ready)
			{
				time_UnNormal = 0;
				irRemote_feedback = IRRemote_Read();
				if(irRemote_feedback == COLORCHANGE)
				{
					update_all = 1;
					Buzz(100);
				}
				else if(irRemote_feedback == INCREASE)
				{
					if(++CONDITION>5)
						CONDITION = 1;
					Buzz(100);
				}
				else if(irRemote_feedback == DECREASE)
				{
					if(CONDITION == 1)
						CONDITION = 5;
					else 
						CONDITION--;
					Buzz(100);
				}
				else if(irRemote_feedback == ONN_STATUS)
				{
					
				}
				else if (irRemote_feedback == KEY_1)
				{
					if(CONDITION == 1)
					{
						work_Mode = TABATA;
						Buzz(100);
					}
					else if(CONDITION == 2)
					{
						work_Mode = EMOM;
						Buzz(100);
					}
					else if(CONDITION == 3)
					{
						work_Mode = AMRAP ;
						Buzz(100);
					}
					else if(CONDITION == 4)
					{
						work_Mode = MODE_COUNTER_UP ;
						Buzz(100);
					}
					else if( CONDITION == 5)
					{
						work_Mode = MODE_COUNTER_DN;
						Buzz(100);
					}
				}
				else if (irRemote_feedback == OFF_STATUS)
				{
					work_Mode = MODE_NORMAL;
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

			segments_value_present[0] = 'H';
			segments_value_present[1] = 'I';
			segments_value_present[2] = time_Minute_Counter/10;
			segments_value_present[3] = time_Minute_Counter%10;
			segments_value_present[4] = time_Second_Counter/10;
			segments_value_present[5] = time_Second_Counter%10;
			
			if(SETTING == DEFAULT)
			{
				
				if(time_secbit == 1)
				{
					time_secbit = 0;
					if(counter_run == 1)
					{

						if(++time_Second_Counter > 59)
						{
							time_Second_Counter = 0;
							time_Minute_Counter++; 
							if((time_Minute_Counter == time_Minute_Counter_setting))
							{
							
								time_Minute_Counter = time_Minute_Counter_setting;
								time_Second_Counter = 0;
								Buzz(100);
								delay_ms(150);
								Buzz(100);
								delay_ms(150);
								Buzz(100);
								delay_ms(150);
								counter_run = 0;
							
								
							}
						}
					}
				}
				/*if(counter_start == 1)
				{
					
					if(part==0)
					{
						delay_ms(200);
						counter_start = 0;
						counter_run = 1;
						Buzz(500);
						delay_ms(50);
						
						
					}
					else 
					{
						part=part-1;
						time_Second_Counter = part;
						delay_ms(1000);
						Buzz(100);
					}	
				}*/
			}
			
			else if( SETTING == SET_M_COUNTER_UP)
			{
				if(time_secbit == 0)
				{
				segments_value_present[2] = time_Minute_Counter_setting/10;
				segments_value_present[3] = time_Minute_Counter_setting%10;

				}
				else
				{
				segments_value_present[2] = 'N';
				segments_value_present[3] = 'N';
				
				}
				segments_value_present[4] = time_Second_Counter_setting/10;
				segments_value_present[5] = time_Second_Counter_setting%10;
				
				if(IRRemote_Ready)
				{
					time_UnNormal = 0;
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == INCREASE)
					{
						if(++time_Minute_Counter_setting > 59)
							time_Minute_Counter_setting = 0;
						
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(time_Minute_Counter_setting == 0)
							time_Minute_Counter_setting = 59;
						else
							time_Minute_Counter_setting--;
						
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						
						SETTING = DEFAULT;
						time_Minute_Counter = 0;
						time_Second_Counter = 0;
						Buzz(200);
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
					counter_run = 0;
					time_Minute_Counter = 0;
					time_Second_Counter = 0;
					Buzz(100);
					delay_ms(50);
					Buzz(100);

				}
				else if(irRemote_feedback == ONN_STATUS)
				{
					if(counter_run == 0)
					{									
						counter_run = 1;
						Buzz(200);
					}	
					else
					{
						counter_run = 0;
						Buzz(200);
					}
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					counter_run = 0;
					time_Minute_Counter = 0;
					time_Second_Counter = 0;
					work_Mode = MODE_NORMAL;
					Buzz(100);
				}

				else if((irRemote_feedback == KEY_2))
				{
					SETTING = SET_M_COUNTER_UP;
					time_UnNormal = 0;
					//part = 10;
					time_Minute_Counter = time_Minute_Counter_setting;
					time_Second_Counter = 0;
					counter_run = 0;
					Buzz(300);

				}
				
			}

			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(i == 0)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 1)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
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
		
		else if(work_Mode == MODE_COUNTER_DN)
		{
			time_UnNormal = 0;

			segments_value_present[0] = 'L';
			segments_value_present[1] = 'O';
			segments_value_present[2] = time_Minute_Counter/10;
			segments_value_present[3] = time_Minute_Counter%10;
			segments_value_present[4] = time_Second_Counter/10;
			segments_value_present[5] = time_Second_Counter%10;
			
			if(SETTING == DEFAULT)
			{
				if(time_secbit == 1)
				{
					time_secbit = 0;
					if(counter_run == 1)
					{
						time_Second_Counter = time_Second_Counter - 1;
						if(time_Second_Counter < 0)
						{
							time_Second_Counter = 59;
							time_Minute_Counter = time_Minute_Counter - 1;
							if(time_Minute_Counter < 0)
							{
								//if(time_Second_Counter == 0)
								//{

									time_Minute_Counter = time_Minute_Counter_setting;
									time_Second_Counter = 0;
									Buzz(100);
									delay_ms(150);
									Buzz(100);
									delay_ms(150);
									Buzz(100);
									delay_ms(150);
									counter_run = 0;	
								//}
								
							}
						}
					}

				}

				/*if((counter_start == 1))
				{
					if(part>0)
					{
						time_Minute_dn = 0;
						segments_value_present[0] = 'L';
						segments_value_present[1] = 'O';
						segments_value_present[2] =  time_Minute_dn/10;
						segments_value_present[3] = time_Minute_dn%10;
						segments_value_present[4] = time_Second_dn/10;
						segments_value_present[5] = time_Second_dn%10;

					}
					
					
					if(part==0)
					{
						delay_ms(100);
						counter_start = 0;
						counter_run = 1;
						Buzz(500);
						delay_ms(50);
						
					}
					else 
					{
						part=part-1;
						time_Second_dn = part;
						delay_ms(1000);
						Buzz(100);
					}
					
					
				}*/

			}
			else if(SETTING == SET_M_COUNTER_DN)
			{
				if(time_secbit == 0)
				{
					segments_value_present[2] = time_Minute_Counter_setting/10;
					segments_value_present[3] = time_Minute_Counter_setting%10;

				}
				else
				{
					segments_value_present[2] = BLINK;
					segments_value_present[3] = BLINK;
					
				}

				segments_value_present[4] = time_Second_Counter_setting/10;
				segments_value_present[5] = time_Second_Counter_setting%10;
				if(IRRemote_Ready)
				{
					time_UnNormal = 0;
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == INCREASE)
					{
						if(++time_Minute_Counter_setting > 59)
							time_Minute_Counter_setting = 0;
						
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(time_Minute_Counter_setting == 0)
							time_Minute_Counter_setting = 23;
						else
							time_Minute_Counter_setting--;
						
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						time_Minute_Counter = time_Minute_Counter_setting;
						time_Second_Counter = 0;
						SETTING = DEFAULT;
						Buzz(200);
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
				else if(irRemote_feedback == ONN_STATUS)
				{
					if(counter_run == 0)
					{
						counter_run = 1;
						Buzz(200);
					}	
					else
					{
						counter_run = 0;
						Buzz(200);
					}
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					counter_run = 0;
					time_Minute_Counter = 0;
					time_Second_Counter = 0;
					work_Mode = MODE_NORMAL;
					Buzz(100);
				}
				else if(irRemote_feedback == KEY_1)
				{
					counter_run = 0;
					time_Minute_Counter = time_Minute_Counter_setting;
					time_Second_Counter = 0;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
				}
				else if((irRemote_feedback == KEY_2))
				{
					SETTING = SET_M_COUNTER_DN;
					//part = 10;
					time_UnNormal = 0;
					time_Minute_Counter = time_Minute_Counter_setting;
					time_Second_Counter = 0;
					counter_run = 0;
					Buzz(100);
					delay_ms(100);
					Buzz(100);

				}
			}

			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(i == 0)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 1)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
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
			//	DotPoints(4,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
			}

			update_all = 0;

		}	
		
		else if(work_Mode == TABATA)
		{
			time_UnNormal = 0;

			segments_value_present[0] = CYKEL/10;
			segments_value_present[1] = CYKEL%10;
			segments_value_present[2] = ACT/10;
			segments_value_present[3] = ACT%10;
			segments_value_present[4] = REST/10;
			segments_value_present[5] = REST%10;

			if(SETTING == SET_CYKEL)
			{
				if(time_secbit == 0)
				{
					segments_value_present[0] = CYKEL_setting/10;
					segments_value_present[1] = CYKEL_setting%10;

				}
				else
				{
					segments_value_present[0] = BLINK;
					segments_value_present[1] = BLINK;
					
				}
				if(IRRemote_Ready)
				{
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == COLORCHANGE)
					{
						update_all ;
						Buzz(100);
					}
					else if(irRemote_feedback == INCREASE)
					{
						if(++CYKEL_setting>30)
							CYKEL_setting = 0;
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(CYKEL_setting == 0)
							CYKEL_setting = 30;
						else 
							--CYKEL_setting;
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						CYKEL =CYKEL_setting;
						SETTING = DEFAULT;
						Buzz(200);
					}
					}
					
			}
			
			else if(SETTING == SET_ACT)
			{
				if(time_secbit == 0)
				{
					segments_value_present[2] = ACT_setting/10;
					segments_value_present[3] = ACT_setting%10;

				}
				else
				{
					segments_value_present[2] = BLINK;
					segments_value_present[3] = BLINK;
					
				}
				if(IRRemote_Ready)
				{
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == COLORCHANGE)
					{
						update_all ;
						Buzz(100);
					}
					else if(irRemote_feedback == INCREASE)
					{
						if(++ACT_setting>90)
							ACT_setting = 0;
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(ACT_setting == 0)
							ACT_setting = 90;
						else 
							--ACT_setting;
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						ACT= ACT_setting;
						SETTING = DEFAULT;
						Buzz(200);
					}
				}
					
			}
			
			else if(SETTING == SET_REST)
			{
				if(time_secbit == 0)
				{
					segments_value_present[4] = REST_setting/10;
					segments_value_present[5] = REST_setting%10;

				}
				else
				{
					segments_value_present[4] = BLINK;
					segments_value_present[5] = BLINK;
					
				}
				if(IRRemote_Ready)
				{
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == COLORCHANGE)
					{
						update_all ;
						Buzz(100);
					}
					else if(irRemote_feedback == INCREASE)
					{
						if(++REST_setting>60)
							REST_setting = 0;
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(REST_setting == 0)
							REST_setting = 60;
						else 
							--REST_setting;
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						REST = REST_setting;
						SETTING = DEFAULT;
						Buzz(200);
					}
					}
					
			}
			
			else if(SETTING == DEFAULT)
			{
				
				if(time_secbit==1)
				{
					time_secbit = 0;
					if(start == 1)
					{
						if(run == 1)
						{
							Starting_time --;
							REST = Starting_time;							
							if(Starting_time <4)
								Buzz(100);

							if(Starting_time<1)
							{
								
								REST = REST_setting;
								run = 0;
								Buzz(300);
								ACT_OK = 1;
							}
						}

						if(ACT_OK == 1)
						{
							
							--ACT;
							if(ACT < 1)
							{
								ACT = ACT_setting;
								ACT_OK = 0;
								REST_OK = 1;
								Buzz(200);
								delay_ms(50);
								Buzz(200);
							}									
						}

						if(REST_OK == 1)
						{
							
							--REST;
							if(REST <4)
								Buzz(100);

							if(REST<1)
							{
								--CYKEL;
								Buzz(400);
								REST = REST_setting;
								REST_OK = 0;
								ACT_OK= 1;
								
							}									
						}

						if(CYKEL < 1)
						{
							CYKEL = CYKEL_setting;
							ACT = ACT_setting;
							REST = REST_setting;
							Buzz(100);
							delay_ms(150);
							Buzz(100);
							delay_ms(150);
							Buzz(100);
							delay_ms(300);
							ACT_OK = 0;
							start = 0;

						}	
						
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
					start = 0;
					run = 1;
					Starting_time = 11;
					REST_OK =0;
					ACT_OK = 0;
					CYKEL = CYKEL_setting;
					ACT = ACT_setting ;
					REST = REST_setting ;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all ;
				}
				else if(irRemote_feedback == KEY_2)
				{
					start = 0;
					run = 0;
					SETTING = SET_CYKEL;
					REST = REST_setting ;
					ACT = ACT_setting;
					CYKEL = CYKEL_setting;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all = 1;


				}
				else if(irRemote_feedback == KEY_3)
				{
					start = 0;
					run = 0;
					SETTING = SET_ACT;
					REST = REST_setting ;
					ACT = ACT_setting;
					CYKEL = CYKEL_setting;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all = 1;
				}
				else if(irRemote_feedback == KEY_4)
				{
					start = 0;
					run = 0;
					SETTING = SET_REST;
					REST = REST_setting ;
					ACT = ACT_setting;
					CYKEL = CYKEL_setting;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all = 1;
				}
				else if(irRemote_feedback == ONN_STATUS)
				{
					if(start == 0)
					{									
						start = 1;
						Buzz(200);
					}	
					else
					{
						start = 0;
						Buzz(200);
					}
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					start = 0;
					run = 0;
					CYKEL = CYKEL_setting;
					ACT = ACT_setting ;
					REST = REST_setting ;
					work_Mode = MODE_NORMAL;
					update_all = 1;
					Buzz(100);
				}
			}

			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(i == 0)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 1)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 2)
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);
					else if(i == 3)
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
		
		}	

		else if(work_Mode == EMOM)
		{
			time_UnNormal = 0;

			segments_value_present[0] = ROUND/10;
			segments_value_present[1] = ROUND%10;
			segments_value_present[2] = TIMES/10;
			segments_value_present[3] = TIMES%10;
			segments_value_present[4] = WORK/10;
			segments_value_present[5] = WORK%10;

			if(SETTING == SET_ROUND)
			{
				if(time_secbit == 0)
				{
					segments_value_present[0] = ROUND_setting/10;
					segments_value_present[1] = ROUND_setting%10;

				}
				else
				{
					segments_value_present[0] = BLINK;
					segments_value_present[1] = BLINK;
					
				}
				if(IRRemote_Ready)
				{
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == COLORCHANGE)
					{
						update_all ;
						Buzz(100);
					}
					else if(irRemote_feedback == INCREASE)
					{
						if(++ROUND_setting>30)
							ROUND_setting = 0;
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(ROUND_setting == 0)
							ROUND_setting = 30;
						else 
							--ROUND_setting;
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						ROUND =ROUND_setting;
						WORK_setting = ((TIMES*60) / ROUND);
						
						if(WORK_setting>99)
							WORK_setting = 99;
						WORK = WORK_setting;
						Starting_time= 11;
						SETTING = DEFAULT;
						Buzz(200);
					}
				}
					
			}
			
			else if(SETTING == SET_TIMES)
			{
				if(time_secbit == 0)
				{
					segments_value_present[2] = TIMES_setting/10;
					segments_value_present[3] = TIMES_setting%10;

				}
				else
				{
					segments_value_present[2] = BLINK;
					segments_value_present[3] = BLINK;
					
				}
				if(IRRemote_Ready)
				{
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == COLORCHANGE)
					{
						update_all ;
						Buzz(100);
					}
					else if(irRemote_feedback == INCREASE)
					{
						if(++TIMES_setting>60)
							TIMES_setting = 0;
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(TIMES_setting == 0)
							TIMES_setting = 60;
						else 
							--TIMES_setting;
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						TIMES= TIMES_setting;
						WORK_setting = ((TIMES*60) / ROUND);
						if(WORK_setting>99)
							WORK_setting = 99;
						WORK = WORK_setting;
						Starting_time = 11;
						SETTING = DEFAULT;
						Buzz(100);
						delay_ms(50);
						Buzz(100);
					}
				}
					
			}
			
			else if(SETTING == DEFAULT)
			{
				
				if(time_secbit==1)
				{
					time_secbit = 0;
					if(start == 1)
					{
						if(run == 1)
						{
							Starting_time --;
							WORK = Starting_time;							
							if(Starting_time <4)
								Buzz(100);

							if(Starting_time<1)
							{
								run = 0;
								WORK = WORK_setting;
								TIMES_OK = 1;
								WORK_OK = 1;
								Buzz(300);
								
							}
						}

						if(TIMES_OK == 1)
						{
							
							tmp--;
							if((tmp%60)==0)
							{
								TIMES--;
							}
							if(tmp < TIMES_setting)
								TIMES = 1;
							
						}
						
						if(WORK_OK == 1)
						{
							
							--WORK;
							if(WORK <4)
								Buzz(100);

							if(WORK < 1)
							{
								WORK = (WORK_setting);
							//	WORK_OK = 0;
								ROUND--;
								Buzz(400);
								
							}									
						}

						

						if((ROUND < 1)) //&& (TIMES < TIMES_setting))
						{
							ROUND = ROUND_setting;
							WORK = WORK_setting;
							TIMES = TIMES_setting;
							tmp = (TIMES_setting * 60);
							Starting_time = 11;
							run = 1;
							WORK_OK = 0;
							start = 0;
							Buzz(100);
							delay_ms(150);
							Buzz(100);
							delay_ms(150);
							Buzz(100);
							delay_ms(300);
							

						}	
						
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
					start = 0;
					run = 1;
					Starting_time = 11;
					tmp = (TIMES_setting * 60);
					WORK_OK =0;
					TIMES_OK = 0;
					ROUND = ROUND_setting;
					WORK = WORK_setting ;
					TIMES = TIMES_setting ;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all ;
				}
				else if(irRemote_feedback == KEY_2)
				{
					start = 0;
					SETTING = SET_ROUND;
					ROUND = ROUND_setting;
					WORK = WORK_setting ;
					TIMES = TIMES_setting ;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all = 1;


				}
				else if(irRemote_feedback == KEY_3)
				{
					start = 0;
					SETTING = SET_TIMES;
					ROUND = ROUND_setting;
					WORK = WORK_setting ;
					TIMES = TIMES_setting ;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
					update_all = 1;
				}
				
				else if(irRemote_feedback == ONN_STATUS)
				{
					if(start == 0)
					{									
						start = 1;
						Buzz(200);
					}	
					else
					{
						start = 0;
						Buzz(200);
					}
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					start = 0;
					ROUND = ROUND_setting;
					WORK = WORK_setting ;
					TIMES = TIMES_setting ;
					Starting_time = 11;
					work_Mode = MODE_NORMAL;
					update_all = 1;
					Buzz(100);
				}
			}

			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(i == 0)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 1)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 2)
						Segment(i,segments_value_present[i],SYSTEMCOLOR,LEVEL_FULL);
					else if(i == 3)
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
		
		}

		else if(work_Mode == AMRAP) /// As Many Round As Possible
		{
			time_UnNormal = 0;


			segments_value_present[0] = 'F';
			segments_value_present[1] = 3;
			segments_value_present[2] = time_Minute_AMRAP/10;
			segments_value_present[3] = time_Minute_AMRAP%10;
			segments_value_present[4] = time_Second_AMRAP/10;
			segments_value_present[5] = time_Second_AMRAP%10;
			
			if(SETTING == DEFAULT)
			{
				if(time_secbit == 1)
				{
					time_secbit = 0;
					if(start == 1)
					{
						if(run == 1)
						{
							Starting_time --;
							time_Second_AMRAP = Starting_time;							
							if(Starting_time <4)
								Buzz(100);

							if(Starting_time<1)
							{
								run = 0;
								time_Second_AMRAP = time_Second_AMRAP_setting;
								AMRAP_run = 1;
								Buzz(300);
								
							}
						}
						else if(AMRAP_run == 1)
						{
							time_Second_AMRAP --;
							if(time_Second_AMRAP < 0)
							{
								time_Second_AMRAP = 59;
								time_Minute_AMRAP = time_Minute_AMRAP - 1;
								if(time_Minute_AMRAP < 0)
								{
									//if(time_Second_Counter == 0)
									//{

										time_Minute_AMRAP = time_Minute_AMRAP_setting;
										time_Second_AMRAP = time_Second_AMRAP_setting;
										AMRAP_run = 0;
										start = 0;	
										run = 1;
										Starting_time = 11;
										Buzz(100);
										delay_ms(150);
										Buzz(100);
										delay_ms(150);
										Buzz(100);
										delay_ms(150);
										
									//}
									
								}
							}
						}
					}
					

				}
			}
			else if(SETTING == SET_M_AMRAP_DN)
			{
				if(time_secbit == 0)
				{
					segments_value_present[2] = time_Minute_AMRAP_setting/10;
					segments_value_present[3] = time_Minute_AMRAP_setting%10;

				}
				else
				{
					segments_value_present[2] = BLINK;
					segments_value_present[3] = BLINK;
					
				}

				segments_value_present[4] = time_Second_AMRAP_setting/10;
				segments_value_present[5] = time_Second_AMRAP_setting%10;
				if(IRRemote_Ready)
				{
					time_UnNormal = 0;
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == INCREASE)
					{
						if(++time_Minute_AMRAP_setting > 90)
							time_Minute_AMRAP_setting = 0;
						
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(time_Minute_AMRAP_setting == 0)
							time_Minute_AMRAP_setting = 90;
						else
							time_Minute_AMRAP_setting--;
						
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						time_Minute_AMRAP = time_Minute_AMRAP_setting;
						time_Second_AMRAP = time_Second_AMRAP_setting;
						Starting_time= 11;
						SETTING = DEFAULT;
						Buzz(200);
					}
				}

			}
			
			else if(SETTING == SET_S_AMRAP_DN)
			{
				if(time_secbit == 0)
				{
					segments_value_present[4] = time_Second_AMRAP_setting/10;
					segments_value_present[5] = time_Second_AMRAP_setting%10;

				}
				else
				{
					segments_value_present[4] = BLINK;
					segments_value_present[5] = BLINK;
					
				}

				segments_value_present[2] = time_Minute_AMRAP_setting/10;
				segments_value_present[3] = time_Minute_AMRAP_setting%10;
				if(IRRemote_Ready)
				{
					time_UnNormal = 0;
					irRemote_feedback = IRRemote_Read();
					if(irRemote_feedback == INCREASE)
					{
						if(++time_Second_AMRAP_setting > 59)
							time_Second_AMRAP_setting = 0;
						
						Buzz(100);
					}
					else if(irRemote_feedback == DECREASE)
					{
						if(time_Second_AMRAP_setting == 0)
							time_Second_AMRAP_setting = 59;
						else
							time_Second_AMRAP_setting--;
						
						Buzz(100);
					}
					else if(irRemote_feedback == KEY_1)
					{
						time_Minute_AMRAP = time_Minute_AMRAP_setting;
						time_Second_AMRAP = time_Second_AMRAP_setting;
						Starting_time = 11;
						SETTING = DEFAULT;
						Buzz(200);
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
				else if(irRemote_feedback == ONN_STATUS)
				{
					if(start == 0)
					{
						start = 1;
						Buzz(200);
					}	
					else
					{
						start = 0;
						Buzz(200);
					}
				}
				else if(irRemote_feedback == OFF_STATUS)
				{
					start = 0;
					time_Minute_AMRAP = time_Minute_AMRAP_setting;
					time_Second_AMRAP = time_Second_AMRAP_setting;
					Starting_time = 11;
					work_Mode = MODE_NORMAL;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
				}
				else if(irRemote_feedback == KEY_1)
				{
					start = 0;
					run = 1;
					Starting_time = 11;
					time_Minute_AMRAP = time_Minute_AMRAP_setting;
					time_Second_AMRAP = time_Second_AMRAP_setting;
					Buzz(100);
					delay_ms(50);
					Buzz(100);
				}
				else if((irRemote_feedback == KEY_2))
				{
					SETTING = SET_M_AMRAP_DN;
					time_UnNormal = 0;
					time_Minute_AMRAP = time_Minute_AMRAP_setting;
					time_Second_AMRAP = time_Minute_AMRAP_setting;
					start = 0;
					Buzz(100);
					delay_ms(100);
					Buzz(100);

				}
				else if((irRemote_feedback == KEY_3))
				{
					SETTING = SET_S_AMRAP_DN;
					time_UnNormal = 0;
					time_Minute_AMRAP = time_Minute_AMRAP_setting;
					time_Second_AMRAP = time_Second_AMRAP_setting;
					start = 0;
					Buzz(100);
					delay_ms(100);
					Buzz(100);

				}
			}

			for (i = 0; i < 7; i++)
			{
				if((segments_value_present[i] != segments_value_last[i]) || (update_all == 1))
				{
					if(i == 0)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
					else if(i == 1)
						Segment(i,segments_value_present[i],COLOR_HISTORY_1,LEVEL_FULL);
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
			//	DotPoints(4,dotpint_state,SYSTEMCOLOR,LEVEL_FULL);
			}

			update_all = 0;

		}
	}

}





























