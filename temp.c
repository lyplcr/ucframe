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


electronic：电子硬件资料相关
drivers：	各MCU底层库文件
OSkernel:	嵌入式系统或者一些架构相关的程序
component；组件 
middleware：中间件
module：	这里应该包括USB等接口，常用模块，常用算法，（要不要分开？）
bin:		可执行命令


_ct类型？

linux:
/bin 目录 存放普通的可执行命令,也就是任何用户都可以执行的命令。
/boot目录 用于存放linux操作系统启动时所需使用的文件。
/dev 目录 包含了Linux系统中所有的外部设备。像光盘驱动器、硬盘等。
/etc 目录 系统管理和配置文件
/home目录 普通用户主目录的基点，比如用户user的主目录就是/home/user，可以用~user表示
/lib 目录 标准程序设计库，又叫动态链接共享库，作用类似windows里的.dll文件
/lost+found这个目录平时是空的，系统非正常关机而留下“无家可归”的文件（windows下叫什么.chk）就在这里
/media 目录 即插即用型存储设备的挂载点自动在这个目录下创建
/mnt 目录 移动设备的挂载点,比如光驱等。
/opt 目录 测试软件的安装目录,测试完后可以直接删除,从而不影响系统的其他设置,非常方便。
/proc 虚拟的目录，是系统内存的映射。可直接访问这个目录来获取系统信息。
/root 系统管理员的主目录
/sbin 超级管理命令，这里存放的是系统管理员使用的管理程序
/tmp 目录 Linux的临时目录,大部分的命令程序都会在/tmp中存放临时执行文件。
/usr 目录 大型的系统应用程序和相关文件都会存放到这里面。
/var 目录 存放系统中运行时会经常更改的数据。比方说各种服务的日志文件
