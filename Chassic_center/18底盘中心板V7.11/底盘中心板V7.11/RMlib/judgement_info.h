/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file judgement_info.h
 *  @version 1.0
 *  @date June 2017
 *
 *  @brief the information from judgement system
 *
 *  @copyright 2017 DJI RoboMaster. All rights reserved.
 *
 */

#ifndef __JUDGEMENT_INFO_H__
#define __JUDGEMENT_INFO_H__

#include "stm32f10x.h"                  // Device header

#define JUDGE_FRAME_BUFLEN 200

/** 
  * @brief  judgement data command id
  */
typedef enum
{
  GAME_INFO_ID       = 0x0001,  //10Hz
  REAL_BLOOD_DATA_ID = 0x0002,
  REAL_SHOOT_DATA_ID = 0x0003,
	REAL_POWER_DATA_ID = 0x0004,
  REAL_RFID_DATA_ID  = 0x0005,  //10hZ
  GAME_RESULT_ID     = 0x0006,
  GAIN_BUFF_ID       = 0x0007,
	POSITION_ID				 = 0x0008,
  STU_CUSTOM_DATA_ID = 0x0100,
}judge_data_id_e;

/** 
  * @brief  game information structures definition(0x0001)
  *         this package send frequency is 50Hz
  */
typedef __packed struct
{
  uint16_t   stage_remain_time;
  uint8_t    game_process;
  /* current race stage
   0 not start
   1 preparation stage
   2 self-check stage
   3 5 seconds count down
   4 fighting stage
   5 result computing stage */
  uint8_t    level;
  uint16_t   remain_hp;
  uint16_t   max_hp;
} game_robot_state_t;

/** 
  * @brief  real time blood volume change data(0x0002)
  */
typedef __packed struct
{
  uint8_t armor_type:4;
 /* 0-3bits: the attacked armor id:
    0x00: 0 front
    0x01：1 left
    0x02：2 behind
    0x03：3 right
    others reserved*/
  uint8_t hurt_type:4;
 /* 4-7bits: blood volume change type
    0x00: armor attacked
    0x01：module offline
    0x02: bullet over speed
    0x03: bullet over frequency */
} robot_hurt_data_t;

/** 
  * @brief  real time shooting data(0x0003)
  */
typedef __packed struct
{
  uint8_t bullet_type;
	uint8_t bullet_freg;
  float   bullet_speed;
} real_shoot_t;

/** 
  * @brief  real time power and hoot data(0x0004)
  */
typedef __packed struct
{
	float chassisVolt;//底盘输出电压
	float chassisCurrent;//底盘输出电流
	float chassisPower;//底盘输出功率
	float chassisPowerBuffer;//底盘功率缓冲
	uint16_t shooterHeat0;//17mm枪口热量
	uint16_t shooterHeat1;//42mm枪口热量
}real_powerheat_t;

/** 
  * @brief  rfid detect data(0x0005)
  */
typedef __packed struct
{
  uint8_t card_type;
  uint8_t card_idx;
} rfid_detect_t;

/** 
  * @brief  game result data(0x0006)
  */
typedef __packed struct
{
  uint8_t winner;
} game_result_t;

/** 
  * @brief  the data of get field buff(0x0007)
  */
typedef __packed struct
{
	uint16_t buffMusk;
} get_buff_t;
/** 
  * @brief  position data
  */
typedef __packed struct
{
	float x;
	float y;
	float z;
	float yaw;
}gameRobotPos_t;

/** 
  * @brief  student custom data
  */
typedef __packed struct
{
  float data1;
  float data2;
  float data3;
	u8    mask;
} client_show_data_t;

typedef __packed struct
{
  uint8_t  data[64];
} user_to_server_t;

typedef __packed struct
{
  uint8_t  data[32];
} server_to_user_t;

/** 
  * @brief  the data structure receive from judgement
  */
typedef struct
{
  game_robot_state_t game_information;
  robot_hurt_data_t  blood_changed_data;
  real_shoot_t       real_shoot_data;
	real_powerheat_t   real_powerheat_data;
  rfid_detect_t      rfid_data;
  game_result_t      game_result_data;
  get_buff_t         get_buff_data;
	gameRobotPos_t		 gameRobotPos;
} receive_judge_t;

/* data send (forward) */
/* data receive */
extern receive_judge_t judge_rece_mesg;

void  judgement_data_handler(uint8_t *p_frame);

#endif
