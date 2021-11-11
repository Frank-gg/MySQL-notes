## 一、启动选项和配置文件

启动选项：在程序启动时指定的设置项，这些选项控制着程序启动后的行为。

### 1.1 在命令行设置启动选项

通过win+R进入打开运行窗口，然后输入cmd进入终端窗口，连接到服务器后，

在启动服务器程序的命令行后指定启动选项的通用格式：

`--启动选项[=值] --启动选项[=值2]...`，可以没有值。如：

- 禁止客户端使用TCP/IP网络进行通信：`mysqld --skip-networking;` 等价于 `mysql --skip_networking;` 
- 设置默认存储引擎：`mysqld --default-storage-engine=InnoDB;`，**等号左右不能有空格**；
- 可以通过mysql --help查看mysql程序支持的启动选项。

```
mysqld：sql后台程序(即mysql服务器)。要想使用客户端程序，该程序必须运行，因为客户端通过连接服务器来访问数据库。
mysql：交互式输入sql语句或从文件以批处理模式执行它们的命令行工具。
```

启动选项有两种形式：长形式与短形式。

![image-20210922141759879](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210922141759879.png)

不管是长形式或短形式，跟密码有关的--password或者-p，--/-与p之间不能有空格，其他的可以有空格。

### 1.2 在配置文件中设置启动选项

配置文件一般在MySQL安装目录下，文件名为`my.ini`，也有可能为.cnf的扩展名。

与在命令行中指定启动选项不同的是，配置文件中的启动选项被划分为若干个组，每个组有一个组名，用中括号[] 扩起来，像这样：

```ini
# 启动选项将作用于所有的服务器程序
[server] 
(具体的启动选项...)
# 启动选项作用于mysqld服务器程序
[mysqld] 
(具体的启动选项...)
# 启动选项作用于所有的客户端程序
[client] 
(具体的启动选项...)
# 启动选项作用于mysql客户端程序
[mysql] 
(具体的启动选项...)
```

具体使用参考下：

![image-20210922142846951](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210922142846951.png)

若在命令行没有添加启动选项，但是在程序启动的时候，就会默认的到配置文件路径下查找配置文件，其中就包括/etc/mysql/my.ini。又由于mysqld 命令可以读取[server] 选项组的内容，所以skip-networking和default-storage-engine=MyISAM 这些选项依然是生效的。

MySQL 将在某些固定的路径下搜索配置文件，也可以通过在命令行上指定`defaults-extra-file`启动选项来指定额外的配置文件路径。MySQL 将按照下面给定的顺序依次读取各个配置文件。**如果在多个配置文件中设置了相同的启动选项，那以最后一个配置文件中的为准**。

读取顺序：mysqld——>mysqld_safe——>mysql.server——>mysql——>mysqladmin——>mysqldump

### 1.3 特定MySQL版本的专用选项组 

可以在选项组的名称后加上特定的MySQL 版本号，比如对于[mysqld] 选项组来说，我们可以定义一个[mysqld-5.7] 的选项组，它的含义和[mysqld] 一样，只不过只有版本号为5.7 的mysqld 程序才能使用这个选项组中的选项。

### 1.4 defaults-file的使用

如果我们不想让MySQL到默认路径下搜索配置文件，可以通过命令进行更改（针对UNIX系统）：

```sql
mysql --defaults-file=/tmp/myconfig.txt
```

### 1.5 命令行和配置文件中启动选项的区别

在命令行上指定的绝大部分启动选项都可以放到配置文件中，但是有一些选项是专门为命令行设计的，比方说`defaults-extra-file` 、`defaults-file` 这样的选项本身就是为了指定配置文件路径的，再放在配置文件中使用就没啥意义了。

需要特别注意，**如果同一个启动选项既出现在命令行中，又出现在配置文件中，那么以命令行中的启动选项为准**。如：

```sql
[server]
default-storage-engine=InnoDB
```

而启动命令是：

`mysql.server start --default-storage-engine=MyISAM`

那最后default-storage-engine 的值就是MyISAM ！

## 二、系统变量

### 2.1 系统变量简介

MySQL 服务器程序运行过程中会用到许多影响程序行为的变量，它们被称为MySQL 系统变量。

比如允许同时连入的客户端数量用系统变量`max_connections` 表示，表的默认存储引擎用系统变量`default_storage_engine` 表示，查询缓存的大小用系统变量`query_cache_size`表示等。

查看系统变量：`SHOW VARIABLES [LIKE 匹配的模式];`，如：`SHOW VARIABLES LIKE 'default%';`，查出所有以default 开头的系统变量的值。

### 2.2 设置系统变量

#### 2.2.1 通过启动选项设置

大部分的系统变量都可以通过启动服务器时传送启动选项的方式来进行设置。

- 通过命令行添加启动选项。

  `mysqld --default-storage-engine=MyISAM --max-connections=10`

- 通过配置文件添加启动选项。

  ```ini
  [server]
  default-storage-engine=MyISAM
  max-connections=10
  ```

对于启动选项来说，如果启动选项名由多个单词组成，各个单词之间用短划线- 或者下划线_ 连接起来都可以，但是对应的系统变量之间必须使用下划线_ 连接起来。

#### 2.2.2 服务器程序运行过程中设置

对于大部分系统变量来说，它们的值可以在服务器程序运行过程中进行动态修改而无需停止并重启服务器，不过系统变量有全局和当前会话作用域之分。

系统变量的作用范围与格式：

```sql
-- GLOBAL ：全局变量，影响服务器的整体操作。
-- SESSION(LOCAL) ：会话变量，影响某个客户端连接的操作。
-- 格式：
1. SET [GLOBAL|SESSION] 系统变量名 = 值;
2. SET [@@(GLOBAL|SESSION).]var_name = XXX;
```

例子：

```sql
-- global：
1. SET GLOBAL default_storage_engine = InnoDB;
2. SET @@GLOBAL.default_storage_engine = InnoDB;

-- session：
1. SET SESSION default_storage_engine = InnoDB;
2. SET @@SESSION.default_storage_engine = InnoDB;
3. SET default_storage_engine = InnoDB;//默认 session
```

查看系统变量：

```sql
SHOW VARIABLES [LIKE 匹配的模式];
-- 查看指定范围的系统变量
SHOW [GLOBAL|SESSION] VARIABLES [LIKE 匹配的模式];
-- 例子：查出所有以default开头的系统变量的值
1. SHOW SESSION VARIABLES LIKE 'default%';
2. SHOW GLOBAL VARIABLES LIKE 'default%';
```

在服务器启动时，会将每个全局变量初始化为其默认值（可以通过命令行或选项文件中指定的选项更改这些默认值）。然后服务器还为每个连接的客户端维护一组会话变量，客户端的会话变量在连接时使用相应全局变量的当前值初始化。

如果某个客户端改变了某个系统变量在`GLOBAL`作用范围的值，并不会影响该系统变量在当前已经连接的客户端作用范围为`SESSION`的值，只会影响后续连入的客户端在作用范围为`SESSION`的值。

#### 2.2.3 注意事项

**并不是所有系统变量都具有GLOBAL和SESSION的作用范围**：

- 有一些系统变量只具有GLOBAL作用范围，比方说max_connections，表示服务器程序支持同时最多有多少个客户端程序进行连接；
- 有一些系统变量只具有SESSION作用范围，比如insert_id，表示在对某个包含AUTO_INCREMENT列的表进行插入时，该列初始的值；
- 有一些系统变量的值既具有GLOBAL作用范围，也具有SESSION作用范围，比如我们前边用到的default_storage_engine，而且其实大部分的系统变量都是这样的。

**有些系统变量是只读的，并不能设置值**：

- 比方说version，表示当前MySQL的版本，客户端是不能设置它的值的，只能在SHOW VARIABLES语句里查看。

#### 2.2.4 启动选项与系统变量的关系

启动选项是在程序启动时我们传递的一些参数，而系统变量是影响服务器程序运行行为的变量：

- 大部分的系统变量都可以被当作启动选项传入；
- 有些系统变量是在程序运行过程中自动生成的，是不可以当作启动选项来设置，比如auto_increment_offset、character_set_client啥的；
- 有些启动选项也不是系统变量，比如defaults-file。

## 三、状态变量

为了让我们更好的了解服务器程序的运行情况，MySQL服务器程序中维护了好多关于程序运行状态的变量，它们被称为状态变量。

比方说Threads_connected表示当前有多少客户端与服务器建立了连接，Handler_update表示已经更新了多少行记录。由于状态变量是用来显示服务器程序运行状况的，所以它们的值只能由服务器程序自己来设置，我们程序员是不能设置的。

查看：

```sql
SHOW [GLOBAL|SESSION] STATUS [LIKE 匹配的模式];
-- 例子：
SHOW STATUS LIKE 'thread%';
```

