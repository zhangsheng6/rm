#ifndef __CONFIG_H_
#define __CONFIG_H_

//定义步兵参数   
#define INFANTRY    2




#if INFANTRY==1  //1号步兵 分区赛一号

#define Yaw_LeftOFFEST   0.0f
#define Yaw_RightOFFEST  0.0f  //上电超前角
#define CHASSISMAXPOWERRATE  0.85f
#define CHASSISMAXPOWER      80.0F       //底盘最大功率

#elif INFANTRY==2  //2号步兵  新步兵

#define Yaw_LeftOFFEST   0.0f
#define Yaw_RightOFFEST  0.0f  //上电超前角
#define CHASSISMAXPOWERRATE  0.85f
#define CHASSISMAXPOWER      80.0F       //底盘最大功率
    

#elif  INFANTRY==3  //3号步兵 

#define Yaw_LeftOFFEST   0.0f
#define Yaw_RightOFFEST  0.0f  //上电超前角
#define CHASSISMAXPOWERRATE  0.82f
#define CHASSISMAXPOWER      80.0F       //底盘最大功率



#elif  INFANTRY==4  //哨兵

#define CHASSISMAXPOWERRATE  0.92
#define CHASSISMAXPOWER      200.0F       //底盘最大功率


#endif


#endif
