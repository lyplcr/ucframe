log_debug https://www.amobbs.com/thread-5687433-1-1.html
lcd菜单 https://www.amobbs.com/thread-5603220-1-1.html
傻孩子菜单技术https://www.amobbs.com/forum.php?mod=viewthread&tid=5688720&page=1&authorid=261204

参数结构体：pt
数据结构体：dt
接口结构体：it

配置寄存器结构体：mt
控制寄存器结构体：ct
状态寄存器结构体：st

通信接口协议、通用万用fifo、

typedef struct
{
} nfc_t;

typedef struct
{
} wifi_t;

typedef struct
{
	uint32_t v;
	uint32_t i;
	uint32_t dianliang;
} power_t;

typedef struct
{
	uint32_t v;
	uint32_t i;
	uint32_t sudu;
	uint32_t jiaodu;
	uint32_t jiasudu;
	uint32_t maxsudu;
} motor_t;

typedef struct
{
	uint32_t pinglv;
	uint32_t sudu;
	uint32_t lenth;
} rf_t;

typedef struct
{
} gui_t;

typedef struct
{

} touch_t;



typedef struct
{
	uint32_t systick;
	
} bootloarder_t;

typedef struct
{
	uint32_t systick;
	void (*ProcessSwitch);
	void (*ThreadSwtich)
	void (*JumpToApp);
} app_t;

