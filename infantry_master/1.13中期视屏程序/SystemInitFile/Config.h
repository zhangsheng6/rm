#ifndef __CONFIG_H_
#define __CONFIG_H_

//���岽������   
#define INFANTRY    2




#if INFANTRY==1  //1�Ų��� ������һ��

#define Yaw_LeftOFFEST   0.0f
#define Yaw_RightOFFEST  0.0f  //�ϵ糬ǰ��
#define CHASSISMAXPOWERRATE  0.85f
#define CHASSISMAXPOWER      80.0F       //���������

#elif INFANTRY==2  //2�Ų���  �²���

#define Yaw_LeftOFFEST   0.0f
#define Yaw_RightOFFEST  0.0f  //�ϵ糬ǰ��
#define CHASSISMAXPOWERRATE  0.85f
#define CHASSISMAXPOWER      80.0F       //���������
    

#elif  INFANTRY==3  //3�Ų��� 

#define Yaw_LeftOFFEST   0.0f
#define Yaw_RightOFFEST  0.0f  //�ϵ糬ǰ��
#define CHASSISMAXPOWERRATE  0.82f
#define CHASSISMAXPOWER      80.0F       //���������



#elif  INFANTRY==4  //�ڱ�

#define CHASSISMAXPOWERRATE  0.92
#define CHASSISMAXPOWER      200.0F       //���������


#endif


#endif
