//串级PID

//电机，舵机区别：
/*
电机：
    给一个PWM，会一直转，PWM值越大，转速越快
舵机：
    给一个PWM，固定一个角度，
		eg：飞卡小车，PWM=0,舵机固定在最右边，	                 
									PWM=500,舵机固定在边中间	                 
									PWM=0,舵机固定在最左边，	                 
     产生周期为20ms，宽度为1.5ms的基准信号，将获得的直流偏置电压与电位器的电压比较，
获得电压差输出。最后，电压差的正负输出到电机驱动芯片决定电机的正反转
*/



















