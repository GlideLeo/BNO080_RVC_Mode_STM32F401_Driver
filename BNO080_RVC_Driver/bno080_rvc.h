#ifndef __BNO080_RVC_H__
#define __BNO080_RVC_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_FRAME_LEN (19)         // UART-RVC 模式帧长度 
#define RX_BUFFER_SIZE (64)        // 串口接收缓存

#define RESET_DELAY    (10)          // 

typedef struct __BNO080_DATA
{
	 unsigned char index;
	 float yaw_deg;
	 float pitch_deg;
	 float roll_deg; 
	 float acc_x_g; 
	 float acc_y_g; 
	 float acc_z_g; 
} BNO080_DATA;

// 接收相关
extern  uint8_t rxBuffer[RX_BUFFER_SIZE]; // 串口接收缓存
extern  uint32_t rxIndex;             // 下一个接收
extern  uint8_t rxFrame[MAX_FRAME_LEN];  // BNO080 数据帧
extern  uint32_t rxFrameLen;         // 目前帧长度
extern  float yaw_deg_global; 
extern  unsigned char data_update_flag; //数据更新标志

extern BNO080_DATA myBNO080_DATA;



//和校验
bool checksumOk(void); 

//处理BNO080数据帧
void processFrame(void);

//串口接收BNO080数据 
//传入为一个字节
void rx080Char(uint8_t c);

#endif
