/*
custom.ino

Gatsby Jan
gatsby.jan@ppt.com.tw

Copyright (c) 2018 Phoenix Pioneer technology

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ultrasound.h"
#include "acceler.h"
#include "bluetoothKey.h"

enum{
  BTN_MODE_GAMEPAD = 0,
  BTN_MODE_BT,
  BTN_MODE_NONE
};
volatile uint8_t btn_mode = BTN_MODE_NONE;

void custom_setup()
{
  us_init(PP_SENSOR_TYPE_ULTRASONIC_0);
  us_init(PP_SENSOR_TYPE_ULTRASONIC_1);
  us_init(PP_SENSOR_TYPE_ULTRASONIC_2);
  us_init(PP_SENSOR_TYPE_ULTRASONIC_3);

  acce_init(PP_SENSOR_TYPE_ACCELER);

  ir_init(PP_SENSOR_TYPE_IR_0);
  ir_init(PP_SENSOR_TYPE_IR_1);

  btkey_init(PP_SENSOR_TYPE_BTKEY);
}

void custom_loop()
{ 
  uint16_t btn_key = 0; 
  int16_t distance_0 = NO_DETECT, distance_1 = NO_DETECT;
  int16_t acce_x, acce_y, acce_z;
  int16_t ir_data_0, ir_data_1;
  int16_t time_cnt = 0;
  
  uart_disableMotor();

  // wait the key to start machine
  while((btn_key = GP_getkeyStatus()) < 1) {  
    if(uart_isConnectToPC() != 0){
      return;
    }
    
    if(btkey_getBtKey(PP_SENSOR_TYPE_BTKEY) == BTKEY_CMD_START){
      break;
    }

  }

  if(btn_key > 0){
    btn_mode = BTN_MODE_GAMEPAD;
  } else {
    btn_mode = BTN_MODE_BT;
  }
  
  while(uart_isUartMode == 0){  
    if(btn_mode == BTN_MODE_GAMEPAD){
      custom_gamepadKeyFun();
    } else {
      custom_btKeyFun();
    }

    // distance - sonar
    /*
    if(isMotorUpgarad == 1){
      isMotorUpgarad = 0;
      
      if(++time_cnt > 20){
        time_cnt = 1;
      }
    }
    if(time_cnt % 20 == 0){
	    distance_0 = us_getDistance(PP_SENSOR_TYPE_ULTRASONIC_0);
	    
      Serial.print("s0="); Serial.println(distance_0);
	  } else if(time_cnt % 10 == 0){
	    distance_1 = us_getDistance(PP_SENSOR_TYPE_ULTRASONIC_1);
	    
      Serial.print("s1="); Serial.println(distance_1);
	  }
	  */
	  
    // acce example
    /*
    acce_x = acce_getDirValue(PP_SENSOR_TYPE_ACCELER, ACCE_DIR_X);
    acce_y = acce_getDirValue(PP_SENSOR_TYPE_ACCELER, ACCE_DIR_Y);
    acce_z = acce_getDirValue(PP_SENSOR_TYPE_ACCELER, ACCE_DIR_Z);
    */

    // distance - ir
    /*
    if_data_0 = ir_getDirValue(PP_SENSOR_TYPE_IR_0);
    ir_data_1 = ir_getDirValue(PP_SENSOR_TYPE_IR_1);
    */

    
    if(uart_isConnectToPC() != 0){
      return;
    }    
  } 
}

int16_t custom_gamepadKeyFun()
{  
  uint16_t btn_key = 0, btn_dir = 0, btn_dirL = 0, btn_dirR = 0;

  if((btn_dir = GP_getDir4Way()) != 0){
    do{
      switch(btn_dir){
        case BTN_DIR_RIGHT:
          do {
            SetFrameRun(17, 100);
            SetFrameRun(15, 60);
          } while((btn_dir = GP_getDir4Way()) == BTN_DIR_RIGHT);
          SetFrameRun(1, 10);
        break;
        
        case BTN_DIR_BACKWARD:
          SetFrameRun(0, 100);
          SetFrameRun(57, 140);
          do {
            SetFrameRun(10, 150);
            SetFrameRun(11, 135);
            
            SetFrameRun(12, 150);
            SetFrameRun(13, 135);
          } while((btn_dir = GP_getDir4Way()) == BTN_DIR_BACKWARD);
          SetFrameRun(59, 145);
          SetFrameRun(56, 130);
          SetFrameRun(1, 10);
        break;
        
        case BTN_DIR_LEFT:
          do {
             SetFrameRun(16, 100);
             SetFrameRun(15, 60);
           } while((btn_dir = GP_getDir4Way()) == BTN_DIR_LEFT);
          SetFrameRun(1, 10);
        break;
        
        case BTN_DIR_FORWARD:
          SetFrameRun(0, 110);
          SetFrameRun(2, 150);
				  
          do {
            SetFrameRun(3, 145);
            SetFrameRun(3, 10); 
            SetFrameRun(4, 150);
             		 
            SetFrameRun(5, 145);
            SetFrameRun(5, 10);         
            SetFrameRun(6, 150);
          } while((btn_dir = GP_getDir4Way()) == BTN_DIR_FORWARD);
						
          SetFrameRun(58, 50);
          SetFrameRun(55, 100);
          SetFrameRun(1, 10);
		
        break;
        
      }
      btn_dir = 0;
    } while((btn_dir = GP_getDir4Way()) != 0);
    
  }

  
  if((btn_key = GP_getkeyStatus()) != 0){
    do{
      switch(btn_key){
        case BTN_KEY_TRIANGLE:
          SetFrameRun(50, 1000);         
          SetFrameRun(51, 1000);
          SetFrameRun(52, 1000);
          SetFrameRun(53, 1000);

          SetFrameRun(1, 220);
        break;

        case BTN_KEY_CIRCLES:
          SetFrameRun(21, 80);         
          SetFrameRun(22, 220);
          SetFrameRun(23, 240);
          do {
            SetFrameRun(23, 30);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_CIRCLES);        
          SetFrameRun(55, 120);
        break;

        case BTN_KEY_CROSS:
          do {
            SetFrameRun(54, 200);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_CROSS);  
          SetFrameRun(55, 120);
        break;

        case BTN_KEY_SQUARE:
          SetFrameRun(24, 80);         
          SetFrameRun(25, 220);
          SetFrameRun(26, 240);
          do {
            SetFrameRun(26, 30);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_SQUARE);        
          SetFrameRun(55, 120);
        break;

        case BTN_KEY_L1:
          SetFrameRun(30, 70);         
          SetFrameRun(31, 120);
          do {
            SetFrameRun(31, 40);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_L1);        
          SetFrameRun(55, 120);
        break;

        case BTN_KEY_R1:
          SetFrameRun(28, 70);         
          SetFrameRun(29, 120);
          do {
            SetFrameRun(29, 40);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_R1);        
          SetFrameRun(55, 120);
        break;

        case BTN_KEY_L2:
          do {
            SetFrameRun(20, 70);         
            SetFrameRun(18, 120);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_L2);
          SetFrameRun(55, 10);
        break;

        case BTN_KEY_R2:
          do {
            SetFrameRun(19,70);         
            SetFrameRun(18, 120);
          } while((btn_dir = GP_getkeyStatus()) == BTN_KEY_R2);
          SetFrameRun(55, 10);
        break;

        case BTN_KEY_SELECT:
          uart_disableMotor();
        break;
        
        case BTN_KEY_START:
          SetFrameRun(54, 300);
          SetFrameRun(55, 200);
        break;
        
        case BTN_KEY_L3:
          SetFrameRun(40, 400);
          SetFrameRun(41, 400);
          
          SetFrameRun(42, 700);
          
          SetFrameRun(43, 400);
          SetFrameRun(1, 400);
          SetFrameRun(55, 200);
        break;

        case BTN_KEY_R3:
          SetFrameRun(44, 400);
          SetFrameRun(45, 400);
          
          SetFrameRun(46, 800);
          
          SetFrameRun(47, 400);
          SetFrameRun(43, 400);
          SetFrameRun(1, 200);
          SetFrameRun(55, 200);
        break;
      }
      
    } while((btn_key = GP_getkeyStatus()) != 0);  

  }

  return 0;
}

int16_t custom_btKeyFun()
{
  uint16_t btn_key = 0;

  if((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) != 0){
    Serial.print("BTKEY=");  Serial.println(btn_key); 
    
    do{
      
      switch(btn_key){
        case BTKEY_CMD_RIGHT:
          do {
            SetFrameRun(17, 100);
            SetFrameRun(15, 60);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_RIGHT);
          SetFrameRun(1, 10);
        break;
        
        case BTKEY_CMD_BACKWARD:
          SetFrameRun(0, 100);
          SetFrameRun(57, 140);
          do {
            SetFrameRun(10, 150);
            SetFrameRun(11, 135);
            
            SetFrameRun(12, 150);
            SetFrameRun(13, 135);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_BACKWARD);
          SetFrameRun(59, 145);
          SetFrameRun(56, 130);
          SetFrameRun(1, 10);
        break;
        
        case BTKEY_CMD_LEFT:
          do {
             SetFrameRun(16, 100);
             SetFrameRun(15, 60);
           } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_LEFT);
           SetFrameRun(1, 10);
        break;
        
        case BTKEY_CMD_FORWARD:
          SetFrameRun(0, 110);
          SetFrameRun(2, 150);
				  
          do {
            SetFrameRun(3, 145);
            SetFrameRun(3, 10); 
            SetFrameRun(4, 150);
             		 
            SetFrameRun(5, 145);
            SetFrameRun(5, 10);         
            SetFrameRun(6, 150);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_FORWARD);
						
          SetFrameRun(58, 50);
          SetFrameRun(55, 100);
          SetFrameRun(1, 10);
		
        break;
        
        case BTKEY_CMD_SIDE_KICK:
        /*
          SetFrameRun(50, 80);         
          SetFrameRun(51, 110);
          SetFrameRun(52, 140);
          SetFrameRun(53, 380);         
        */
    
          SetFrameRun(1, 220);
          SetFrameRun(55, 240);
        break;

        case BTKEY_CMD_RIGHT_HOOK:
          SetFrameRun(21, 80);         
          SetFrameRun(22, 220);
          SetFrameRun(23, 240);
          do {
            SetFrameRun(23, 30);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_RIGHT_HOOK);        
          SetFrameRun(55, 120);
        break;

        case BTKEY_CMD_SEAT:
          do {
            SetFrameRun(54, 200);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_SEAT);  
          SetFrameRun(55, 120);
        break;

        case BTKEY_CMD_LEFT_HOOK:
          SetFrameRun(24, 80);         
          SetFrameRun(25, 220);
          SetFrameRun(26, 240);
          do {
            SetFrameRun(26, 30);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_LEFT_HOOK);        
          SetFrameRun(55, 120);
        break;

        case BTKEY_CMD_LEFT_PUNCH:
          SetFrameRun(30, 70);         
          SetFrameRun(31, 120);
          do {
            SetFrameRun(31, 40);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_LEFT_PUNCH);        
          SetFrameRun(55, 120);
        break;

        case BTKEY_CMD_RIGHT_PUNCH:
          SetFrameRun(28, 70);         
          SetFrameRun(29, 120);
          do {
            SetFrameRun(29, 40);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_RIGHT_PUNCH);        
          SetFrameRun(55, 120);
        break;

        case BTKEY_CMD_LEFT_SIDEWAY:
          do {
            SetFrameRun(20, 70);         
            SetFrameRun(18, 120);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_LEFT_SIDEWAY);
          SetFrameRun(55, 10);
        break;

        case BTKEY_CMD_RIGHT_SIDEWAY:
          do {
            SetFrameRun(19,70);         
            SetFrameRun(18, 120);
          } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) == BTKEY_CMD_RIGHT_SIDEWAY);
          SetFrameRun(55, 10);
        break;

        case BTKEY_CMD_SELECT:
          uart_disableMotor();
        break;
        
        case BTKEY_CMD_START:
          SetFrameRun(54, 300);
          SetFrameRun(55, 200);
        break;
        
        case BTKEY_CMD_GETUP_FORWARD:
          SetFrameRun(40, 400);
          SetFrameRun(41, 400);
          
          SetFrameRun(42, 700);
          
          SetFrameRun(43, 400);
          SetFrameRun(1, 400);
          SetFrameRun(55, 200);
        break;

        case BTKEY_CMD_GETUP_BACKWARD:
          SetFrameRun(44, 400);
          SetFrameRun(45, 400);
          
          SetFrameRun(46, 800);
          
          SetFrameRun(47, 400);
          SetFrameRun(43, 400);
          SetFrameRun(1, 200);
          SetFrameRun(55, 200);
        break;
      }
      
    } while((btn_key = btkey_getBtKey(PP_SENSOR_TYPE_BTKEY)) != 0);  

  }

  return 0;
}