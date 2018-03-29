1、限幅滤波法***************************************************
 *函数名称：AmplitudeLimiterFilter()-限幅滤波法
 *优点：能有效克服因偶然因素引起的脉冲干扰
 *缺点：无法抑制那种周期性的干扰，且平滑度差
 *说明：
 1、调用函数
 GetAD(),该函数用来取得当前值
 2、变量说明
 Value:最近一次有效采样的值，该变量为全局变量
 NewValue:当前采样的值
 ReturnValue:返回值
 3、常量说明
 A:两次采样的最大误差值，该值需要使用者根据实际情况设置
 *入口：Value,上一次有效的采样值，在主程序里赋值
 *出口：ReturnValue,返回值，本次滤波结果
 ****************************************************/
 #define A 10
 unsigned char Value
 unsigned char AmplitudeLimiterFilter()
 {
 unsigned char NewValue;
 unsigned char ReturnValue;
 NewValue=GatAD();
 if(((NewValue-Value)>A))||((Value-NewValue)>A)))
 ReturnValue=Value;
 else ReturnValue=NewValue;
 return(ReturnValue);
 }
 2、中位值滤波法

 /****************************************************
 *函数名称：MiddlevalueFilter()-中位值滤波法
 *优点：能有效克服因偶然因素引起的波动干扰；对温度、液
 位等变化缓慢的被测参数有良好的滤波效果
 *缺点：对流量，速度等快速变化的参数不宜
 *说明：
 1、调用函数
 GetAD(),该函数用来取得当前值
 Delay(),基本延时函数
 2、变量说明
 ArrDataBuffer[N]:用来存放一次性采集的N组数据
 Temp:完成冒泡法试用的临时寄存器
 i,j,k:循环试用的参数值
 3、常量说明
 N：数组长度
 *入口：
 *出口：value_buf[(N-1)/2],返回值，本次滤波结果
 *****************************************************/

 #define N 11

 unsigned char MiddlevalueFilter()

 {
 unsigned char value_buf[N];
 unsigned char i,j,k,temp;
 for(i=0;i<N;i++)
 {
 value_buf[i] = get_ad();
 delay();
 }
 for (j=0;j<N-1;j++)
 {
 for (k=0;k<N-j;k++)
 {
 if(value_buf[k]>value_buf[k+1])
 {
 temp = value_buf[k];
 value_buf[k] = value_buf[k+1];
 value_buf[k+1] = temp;
 }
 }
 }
 return value_buf[(N-1)/2];
 }


 3、算术平均滤波法

 /*********************************************************
 说明：连续取N个采样值进行算术平均运算
 优点：试用于对一般具有随机干扰的信号进行滤波。这种信号的特点是
 有一个平均值，信号在某一数值范围附近上下波动。
 缺点：对于测量速度较慢或要求数据计算较快的实时控制不适用。
 **********************************************************/

 #define N 12

 char filter()
 {
 unsigned int sum = 0;
 unsigned char i;

 for (i=0;i<N;i++)
 {
 sum + = get_ad();
 delay();
 }
 return(char)(sum/N);
 }

 4、递推平均滤波法（又称滑动平均滤波法）

 /***************************************************
 说明：把连续N个采样值看成一个队列，队列长度固定为N。
 每次采样到一个新数据放入队尾，并扔掉队首的一
 次数据。把队列中的N各数据进行平均运算，既获得
 新的滤波结果。
 优点：对周期性干扰有良好的抑制作用，平滑度高；试用于高频振荡的系统
 缺点：灵敏度低；对偶然出现的脉冲性干扰的抑制作用较差，不适于脉冲干
 扰较严重的场合
 ****************************************************/

 #define N 12

 unsigned char value_buf[N];

 unsigned char filter()
 {
 unsigned char i;
 unsigned char value;
 int sum=0;

 value_buf[i++] = get_ad(); //采集到的数据放入最高位
 for(i=0;i<N;i++)
 {
 value_buf[i]=value_buf[i+1]; //所有数据左移，低位扔掉
 sum += value_buf[i];
 }
 value = sum/N;
 return(value);
 }

 5、中位值平均滤波法（又称防脉冲干扰平均滤波法）

 /********************************************
 说明：采一组队列去掉最大值和最小值
 优点：融合了两种滤波的优点。对于偶然出现的脉冲性干扰，可消
 除有其引起的采样值偏差。对周期干扰有良好的抑制作用，
 平滑度高，适于高频振荡的系统。
 缺点：测量速度慢
 *********************************************/

 #define N 12

 uchar filter()

 {
 unsigned char i,j,k,l;
 unsigned char temp,sum=0,value;
 unsigned char value_buf[N],;

 for(i=0;i<N;i++)
 {
 value_buf[i] = get_ad();
 delay();
 }
 //采样值从小到大排列（冒泡法）
 for(j=0;j<N-1;j++)
 {
 for(i=0;i<N-j;i++)
 {
 if(value_buf[i]>value_buf[i+1])
 {
 temp = value_buf[i];
 value_buf[i] = value_buf[i+1];
 value_buf[i+1] = temp;
 }
 }
 }

 for(i=1;i<N-1;i++)
 sum += value_buf[i];

 value = sum/(N-2);
 return(value);
 }

 6、递推中位值滤波法
 /************************************************
 优点：对于偶然出现的脉冲性干扰，可消除由其引起的采样值偏差。
 对周期性干扰有良好的抑制作用，平滑度高；试用于高频振荡
 的系统
 缺点：测量速度慢
 *************************************************/

 char filter(char new_data,char queue[],char n)
 {
 char max,min;
 char sum;
 char i;

 queue[0]=new_data;
 max=queue[0];
 min=queue[0];
 sum=queue[0];

 for(i=n-1;i>0;i--)
 {
 if(queue[i]>max)
 max=queue[i];
 else if (queue[i]<min)
 min=queue[i];
 sum=sum+queue[i];
 queue[i]=queue[i-1];
 }

 i=n-2;
 sum=sum-max-min+i/2; //说明：+i/2的目的是为了四舍五入
 sum=sum/i;

 return(sum);
 }

 7、限幅平均滤波法

 /************************************************
 优点：对于偶然出现的脉冲性干扰，可消除有其引起的采样值偏差。
 *************************************************/
 #define A 10
 #define N 12

 unsigned char data[];
 unsigned char filter(data[])
 {
 unsigned char i;
 unsigned char value,sum;

 data[N]=GetAD();
 if(((data[N]-data[N-1])>A||((data[N-1]-data[N])>A))
 data[N]=data[N-1];
 //else data[N]=NewValue;
 for(i=0;i<N;i++)
 {
 data[i]=data[i+1];
 sum+=data[i];
 }
 value=sum/N;
 return(value);
 }


 8、一阶滞后滤波法

 /****************************************************
 *函数名称：filter()-一阶滞后滤波法
 *说明：
 1、调用函数
 GetAD(),该函数用来取得当前值
 Delay(),基本延时函数
 2、变量说明
 Or_data[N]:采集的数据
 Dr0_flag、Dr1_flag:前一次比较与当前比较的方向位
 coeff:滤波系数
 F_count：滤波计数器
 3、常量说明
 N：数组长度
 Thre_value：比较门槛值
 *入口：
 *出口：
 *****************************************************/

 #define Thre_value 10
 #define N 50

 float Or_data[N]；
 unsigned char Dr0_flag=0,Dr1_flag=0;

 void abs(float first,float second)
 {
 float abs;
 if(first>second)
 {
 abs=first-second;
 Dr1_flag=0;
 }
 else
 {
 abs=second-first;
 Dr1_flag=1;
 }
 return(abs);
 }

 void filter(void)
 {
 uchar i=0,F_count=0,coeff=0;
 float Abs=0.00;

 //确定一阶滤波系数
 for(i=1;i<N;i++)
 {
 Abs=abs(Or_data[i-1],Or_data[i]);
 if(!(Dr1_flag^Dr0_flag)) //前后数据变化方向一致
 { 
 F_count++;
 if(Abs>=Thre_value) 
 {
 F_count++;
 F_count++;
 }
 if(F_count>=12)
 F_count=12;
 coeff=20*F_count; 
 }
 else //去抖动
 coeff=5;
 //一阶滤波算法
 if(Dr1_flag==0) //当前值小于前一个值
 Or_data[i]=Or_data[i-1]-coeff*(Or_data[i-1]-Or_data[i])/256;
 else
 Or_data[i]=Or_data[i-1]+coeff*(Or_data[i]-Or_data[i-1])/256; 

 F_count=0; //滤波计数器清零
 Dr0_flag=Dr1_flag;
 }
 }

 9、加权递推平均滤波法

 /************************************************************
 coe:数组为加权系数表，存在程序存储区。
 sum_coe:加权系数和
 ************************************************************/

 #define N 12

 const char code coe[N] = {1,2,3,4,5,6,7,8,9,10,11,12};
 const char code sum_coe = 1+2+3+4+5+6+7+8+9+10+11+12;

 unsigned char filter()
 {
 unsigned char i;
 unsigned char value_buf[N];
 int sum=0;

 for (i=0;i<N;i++)
 {
 value_buf[i] = get_ad();
 delay();
 }

 for (i=0,i<N;i++)
 {
 value_buf[i]=value_buf[i+1];
 sum += value_buf[i]*coe[i];
 }

 sum/=sum_coe;
 value=sum/N;
 return(value);
 }

 10、消抖滤波法

 /************************************************

 *************************************************/
 #define N 12

 unsigned char filter()
 {
 unsigned char i=0;
 unsigned char new_value;
 new_value = get_ad();
 if(value !=new_value);
 {
 i++;
 if (i>N)
 {
 i=0;
 value=new_value;
 }
 }
 else i=0;
 return(value);
 
 
 、、、、、、、、、、、、、、、、、、、、、
 其实你这些全都属于FIR LPF，何苦呢，正儿八经的直接用个Biquad做IIR LPF，计算量小多了
 