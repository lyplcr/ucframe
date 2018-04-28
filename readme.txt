ucframe的目标是建立一个开放兼容标准的嵌入式框架，以节省（重复）开发时间
common文件夹包括一些简单常见的函数结构类对象等
component文件夹包括一些复杂的组件或者算法，比如文件系统、bldc算法等
drivers文件夹包括一些常见的外设驱动，比如spiflash等
middleware文件夹主要包括通用虚拟中间件，比如虚拟文件系统、虚拟操作系统、虚拟gui、虚拟接口等，这部分根据需要实现，用注册的模式？可以放在component里面
project文件夹包括单片机库函数和自己写的工程
ucboot文件夹放bootloader或IAP工程


log_debug https://www.amobbs.com/thread-5687433-1-1.html
lcd菜单 https://www.amobbs.com/thread-5603220-1-1.html
傻孩子菜单技术https://www.amobbs.com/forum.php?mod=viewthread&tid=5688720&page=1&authorid=261204

配置寄存器结构体：mt；控制寄存器结构体：ct；状态寄存器结构体：st；数据寄存器结构体：dt；

开源bootloader：支持串口，支持USB，支持菜单读SD，支持启动模式和下载模式

设备驱动架构模型
通信接口协议、通用万用fifo、
IRP(I/O Request Package I/O请求包)
I/O管理器

OSkernel:	嵌入式系统或者一些架构相关的程序
component；组件 （可复用的模块，或者其他组件的组成部分）
module：	这里应该包括USB等接口，常用模块，常用算法，（要不要分开？）


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







