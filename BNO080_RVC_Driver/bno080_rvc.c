
// Sensor Application
#include "bno080_rvc.h"

//数组长度
#ifndef ARRAY_LEN
#define ARRAY_LEN(a) (sizeof(a)/sizeof(a[0]))  
#endif	

const float scaleDegToRad = 3.14159265358 / 180.0;

// Offsets into rx frame
#define RVC_INDEX (2)
#define RVC_YAW_LSB (3)
#define RVC_YAW_MSB (4)
#define RVC_PITCH_LSB (5)
#define RVC_PITCH_MSB (6)
#define RVC_ROLL_LSB (7)
#define RVC_ROLL_MSB (8)
#define RVC_ACC_X_LSB (9)
#define RVC_ACC_X_MSB (10)
#define RVC_ACC_Y_LSB (11)
#define RVC_ACC_Y_MSB (12)
#define RVC_ACC_Z_LSB (13)
#define RVC_ACC_Z_MSB (14)

// 接收相关
static uint8_t rxFrame[MAX_FRAME_LEN];  // BNO080 数据帧
static uint32_t rxFrameLen = 0;         // 目前帧长度

unsigned char data_update_flag = 0 ; //数据更新标志

BNO080_DATA myBNO080_DATA;

//和校验
 bool checksumOk(void)
{
    uint8_t check = 0;

    for (int n = 2; n < MAX_FRAME_LEN-1; n++) {
        check += rxFrame[n];
    }

    return (check == rxFrame[MAX_FRAME_LEN-1]);
}

//处理BNO080数据帧
 void processFrame(void)
{
    myBNO080_DATA.index = rxFrame[RVC_INDEX];
    myBNO080_DATA.yaw_deg =   0.01  * (int16_t)((rxFrame[RVC_YAW_MSB] << 8) + rxFrame[RVC_YAW_LSB]);
    myBNO080_DATA.pitch_deg = 0.01  * (int16_t)((rxFrame[RVC_PITCH_MSB] << 8) + rxFrame[RVC_PITCH_LSB]);
    myBNO080_DATA.roll_deg =  0.01  * (int16_t)((rxFrame[RVC_ROLL_MSB] << 8) + rxFrame[RVC_ROLL_LSB]);
    myBNO080_DATA.acc_x_g =   0.001 * (int16_t)((rxFrame[RVC_ACC_X_MSB] << 8) + rxFrame[RVC_ACC_X_LSB]);
    myBNO080_DATA.acc_y_g =   0.001 * (int16_t)((rxFrame[RVC_ACC_Y_MSB] << 8) + rxFrame[RVC_ACC_Y_LSB]);
    myBNO080_DATA.acc_z_g =   0.001 * (int16_t)((rxFrame[RVC_ACC_Z_MSB] << 8) + rxFrame[RVC_ACC_Z_LSB]);	
		data_update_flag = 1;

//    printf("%3d : yaw:%0.2f pitch:%0.2f roll:%0.2f ax:%0.3f ay:%0.3f az:%0.3f\n",
//           index, yaw_deg, pitch_deg, roll_deg, acc_x_g, acc_y_g, acc_z_g);
}

//串口接收BNO080数据 
//传入为一个字节
 void rx080Char(uint8_t c)
{
    // If rx buffer is full, shift the data
    if (rxFrameLen == MAX_FRAME_LEN) {
        // Shift data
        for (int n = 0; n < MAX_FRAME_LEN-1; n++) {
            rxFrame[n] = rxFrame[n+1];
        }

        // Add newest char
        rxFrame[MAX_FRAME_LEN-1] = c;
    }
    else {
        // Add newest char
        rxFrame[rxFrameLen++] = c;
    }
    
    // If rx buffer is full, now, check framing
    if (rxFrameLen == MAX_FRAME_LEN) {
        if ((rxFrame[0] == 0xAA) && (rxFrame[1] == 0xAA)) {
            if (checksumOk()) {
                // Found a well formed frame, process frame
                processFrame();

                // Clear frame buffer
                rxFrameLen = 0;
            }
        }
    }
    
}



