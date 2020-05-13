
//欧拉角
/*

yaw：偏航角：围绕Z轴旋转，
	 角度范围为：顺时针旋转增加360度
	 
pitch：俯仰角：围绕X轴旋转,远离我的方向旋转角度增加
	 角度范围为：-90度到+360度
	 
row：翻滚角：围绕Z轴旋转,数学坐标方向+-角度
	 角度范围为：-180度到+180度

*/

/*

通过CAN2接受到信息 触发CAN2接受中断
在中断里面：
    先储存PID参数等信息在CAN接受消息结构体里
    在CanReceiveIO（） 函数里面
	对于获取的ID及其数据读取,存在Saved结构体里面，并设置校准标志
	
在校准线程循环里面：
     CalibrateLoop(void）：对于中断里面已设置的校准标志，在相应的分支
	把数据参数从Saved的结构体 复制到gAppParamStruct结构体里面
	更新保存数据参数到FLASH文件里面
    Sensor_Offset_Param_Init(AppParam_t *appParam)：
  把FLASH结构体gAppParamStruct的数据参数 复制到Saved结构体里面

*/


