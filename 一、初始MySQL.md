## 一、MySQL架构

C/S和B/S是软件发展过程中出现的两种软件架构方式。

### 1.1 C/S架构（Client/Server 客户端/服务器）

![image-20210922105805366](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210922105805366.png)

特点：必须在客户端安装特定软件；

优点：图像效果显示较好（如：3D游戏）；

缺点：服务器的软件和功能进行升级，客户端也必须升级、不利于维护；

常见的C/S程序：qq、微信等；

### 1.2 B/S架构（Browser/Server 浏览器/服务器）

![image-20210922110314125](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210922110314125.png)

特点：无需安装客户端，任何浏览器都可以直接访问；

优点：涉及到功能的升级，只需要升级服务器端；

缺点：图形显示效果不如C/S架构；

需要通过HTTP协议访问。

### 1.3 MySQL的架构

MySQL采用的是客户端/服务端架构。它的服务器程序直接与要存储的数据打交道，多个客户端程序可以连接到这这个服务器程序，向服务器发送增删改查的请求，然后服务器程序根据这些请求，对存储的数据进行相应的处理。

要登陆到服务器，MySQL的每一个客户端都需要使用用户名和密码才行。只有登录之后，才能向服务器发送某些请求来操作数据。

## 二、启动和关闭MySQL服务器

### 2.1 通过系统服务器

打开运行窗口（win+R），输入services.msc回车，打开系统服务器，并找到mysql服务，右击启动即可，停止的话也只需右击停止。

![image-20210922112017520](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210922112017520.png)

### 2.2 通过命令提示符

运行窗口输入cmd，进入命令提示符窗口，

启动：`net start mysql;`

停止：`net stop mysql;`

## 三、MySQL客服端启动

启动服务器后，就可以启动客户端程序来连接到这个服务器了。在运行窗口输入：`mysql -h 主机名 -u用户名 -p`  ，然后输入密码。服务器运行在本机，可以不用-h。可以直接在p后面输入密码，但会不安全。

![image-20210922131836377](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210922131836377.png)

如果想断开客户端与服务器的连接并且关闭客户端，可以输入：`quit;`  `exit;`  `\q;`。

**注意事项**：

- 直接在p后输入密码，可能会被同一台机器上的其他用户通过诸如ps之类的命令看到；
- 如果一定要在-p后输入密码，如，-p123456，p与数字直接不能加空格，而-u root 可以有空格；
- -h，-u，-p的顺序可以改变

## 四、MySQL逻辑架构

前面说到MySQL是C/S架构，具体点如下：

<img src="https://static001.geekbang.org/resource/image/0d/d9/0d2070e8f84c4801adbfa03bda1f98d9.png" alt="img" style="zoom: 33%;" />

从图中可以看到，MySQL 大体分为 Server 层和存储引擎层两部分。多个存储引擎共用一个Server层。

Server 层：包括连接器、查询缓存、分析器、优化器、执行器等，涵盖 MySQL 的大多数核心服务功能，以及所有的内置函数（如日期、时间、数学和加密函数等），所有跨存储引擎的功能都在这一层实现，比如存储过程、触发器、视图等。

存储引擎层：负责数据的存储和提取。其架构模式是插件式的，支持 InnoDB、MyISAM、Memory 等多个存储引擎。MySQL 5.5.5之后，create table 建表的时候，如果不指定引擎类型，默认使用的就是 InnoDB。

具体的介绍可以看：

[MySQL基础架构]: https://blog.csdn.net/qq_43352723/article/details/120262195?spm=1001.2014.3001.5502

