# SQL优化步骤

## 查看SQL执行频率

随着生产数据量的急剧增长，很多 SQL 语句逐渐显露出性能问题，对生产的影响也越来越大，此时有问题的 SQL 语句就成为整个系统性能的瓶颈，因此必须要进行优化

- MySQL 客户端连接成功后，查询服务器状态信息：

```sql
-- SESSION: 显示当前会话连接的统计结果，默认参数
-- GLOBAL: 显示自数据库上次启动至今的统计结果
SHOW [SESSION|GLOBAL] STATUS LIKE '';
```

- 查看SQL执行频率：

```sql
SHOW STATUS LIKE 'Com_____';
```
Com_xxx 表示每种语句执行的次数

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/113.png)

- 查询 SQL 语句影响的行数：

```sql
SHOW STATUS LIKE 'Innodb_rows_%';
```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/114.png)

Com_xxxx：这些参数对于所有存储引擎的表操作都会进行累计

Innodb_xxxx：这几个参数只是针对InnoDB 存储引擎的，累加的算法也略有不同

|         参数         |                             含义                             |
| :------------------: | :----------------------------------------------------------: |
|      Com_select      |           执行 SELECT 操作的次数，一次查询只累加 1           |
|      Com_insert      | 执行 INSERT 操作的次数，对于批量插入的 INSERT 操作，只累加一次 |
|      Com_update      |                    执行 UPDATE 操作的次数                    |
|      Com_delete      |                    执行 DELETE 操作的次数                    |
|   Innodb_rows_read   |                  执行 SELECT 查询返回的行数                  |
| Innodb_rows_inserted |                  执行 INSERT 操作插入的行数                  |
| Innodb_rows_updated  |                  执行 UPDATE 操作更新的行数                  |
| Innodb_rows_deleted  |                  执行 DELETE 操作删除的行数                  |
|     Connections      |                 试图连接 MySQL 服务器的次数                  |
|        Uptime        |                        服务器工作时间                        |
|     Slow_queries     |                         慢查询的次数                         |

------

## 定位低效率SQL

询性能超过1s的sql称为**慢sql**。要想知道哪些SQL是慢SQL，有两种方式，一种是开启本地MySQL的慢查询日志；另一种是阿里云提供的RDS（第三方部署的MySQL服务器），提供了查询慢SQL的功能。

SQL 执行慢有两种情况：

- 偶尔慢：DB 在刷新脏页
  - redo log 写满了
  - 内存不够用，要从 LRU 链表中淘汰
  - MySQL 认为系统空闲的时候
  - MySQL 关闭时
- 一直慢的原因：索引没有设计好、SQL 语句没写好、MySQL 选错了索引

通过以下两种方式定位执行效率较低的 SQL 语句

- 慢日志查询： 慢查询日志在查询结束以后才记录，执行效率出现问题时查询日志并不能定位问题

  配置文件修改：修改 .cnf 文件 `vim /etc/mysql/my.cnf`，重启 MySQL 服务器

  ```sql
  slow_query_log=ON
  slow_query_log_file=/usr/local/mysql/var/localhost-slow.log
  long_query_time=1	#记录超过long_query_time秒的SQL语句的日志
  log-queries-not-using-indexes = 1
  ```

  使用命令配置：

  ```sql
  mysql> SET slow_query_log=ON;
  mysql> SET GLOBAL slow_query_log=ON;
  ```

  查看是否配置成功：

  ```sql
  SHOW VARIABLES LIKE '%query%'
  ```

- `SHOW PROCESSLIST`：**实时查看**当前 MySQL 在进行的连接线程，包括线程的状态、是否锁表、SQL 的执行情况，同时对一些锁表操作进行优化

------

## EXPLAIN 执行计划

通过 EXPLAIN 命令获取执行 SQL 语句的信息，包括在 SELECT 语句执行过程中如何连接和连接的顺序，执行计划在优化器优化完成后、执行器之前生成，然后执行器会调用存储引擎检索数据

查询 SQL 语句的执行计划：

```sql
EXPLAIN sql语句;
```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/114.5.png)

|     字段      |                             含义                             |
| :-----------: | :----------------------------------------------------------: |
|      id       |  select查询的序列号，表示查询中执行select子句或操作表的顺序  |
|  select_type  |                      表示 SELECT 的类型                      |
|     table     | 输出结果集的表，显示这一步所访问数据库中表名称，有时不是真实的表名字，可能是简称 |
|     type      |                       表示表的连接类型                       |
| possible_keys |                  表示查询时，可能使用的索引                  |
|      key      |                      表示实际使用的索引                      |
|    key_len    |                        索引字段的长度                        |
|      ref      | 列与索引的比较，表示表的连接匹配条件，即哪些列或常量被用于查找索引列上的值 |
|     rows      | 扫描出的行数，表示 MySQL 根据表统计信息及索引选用情况，**估算**的找到所需的记录扫描的行数 |
|   filtered    |                    按表条件过滤的行百分比                    |
|     extra     |                     执行情况的说明和描述                     |

### id

id列的编号就是select 的序列号，可以理解为SQL执行顺序的标识，有几个select 就有几个id。

- id值不同：id值越大优先级越高，越先被执行；
- id值相同：从上往下依次执行；
- id列为null：表示这是一个结果集，不需要使用它来进行查询。

### select_type

查询的类型，主要用于区分普通查询、联合查询、子查询等复杂的查询。

- **simple**：表示查询中不包括union操作或者子查询，位于最外层的查询的select_type即为simple，且只有一个；

> ```sql
> explain select * from emp;
> ```

- **primary**：需要union操作或者含有子查询的select，位于最外层的查询的select_type即为primary，且只有一个；

> ```sql
> explain select staname,ename supname from (select ename staname,mgr from emp) t join emp on t.mgr=emp.empno ;
> ```

- **derived：**from列表中出现的子查询，也叫做派生表；mysql或者递归执行这些子查询，把结果放在临时表里；

> ```sql
> explain select staname,ename supname from (select ename staname,mgr from emp) t join emp on t.mgr=emp.empno ;
> ```

- **subquery：**除了from子句中包含的子查询外，其他地方出现的子查询都可能是subquery；

> ```sql
> explain select * from emp where sal > (select avg(sal) from emp) ;
> ```

- **union：**若第二个select出现在union之后，则被标记为union；若union包含在from子句的子查询中，外层select将被标记为derived；

> ```sql
> explain select * from emp where deptno = 10 union select * from emp where sal >2000;
> ```

- **union result：**从union表获取结果的select ，因为它不需要参与查询，所以id字段为null；

> ```sql
> explain select * from emp where deptno = 10 union select * from emp where sal >2000;
> ```

- **dependent union**：与union一样，出现在union 或union all语句中，但是这个查询要受到外部查询的影响；

> ```sql
> explain select * from emp e where e.empno  in ( select empno from emp where deptno = 10 union select empno from emp where sal >2000)
> ```

- **dependent subquery：**与dependent union类似，子查询中的第一个SELECT，这个subquery的查询要受到外部表查询的影响。

> ```sql
> explain select * from emp e where e.deptno in (select distinct deptno from dept);
> ```

### table

表示 explain 的一行正在访问哪个表。

- 如果查询使用了别名，那么这里显示的是别名；
- 如果不涉及对数据表的操作，那么这显示为null；
- 如果显示为尖括号括起来的 `<derived N>` 就表示这个是临时表，后边的N就是执行计划中的id，表示结果来自于这个查询产生；
- 如果是尖括号括起来的 `<union M,N>`，与`<derived N>`类似，也是一个临时表，表示这个结果来自于union查询的id为M,N的结果集。

### type

访问类型，即MySQL决定如何查找表中的行。

依次从好到差：**null>system > const > eq_ref > ref > fulltext > ref_or_null > index_merge > unique_subquery > index_subquery > range > index > all**，除了all之外，其他的 type类型 都可以使用到索引，除了 index_merge 之外，其他的type只可以用到一个索引。一般要求type为ref，范围查找需要达到 range。

- null：MySQL在优化过程中分解语句，执行时甚至不用访问表或索引

- **system**：表中只有一条元组匹配（等于系统表），这是 const 类型的特例，平时不会出现，可以忽略不计
- **const**：通过索引一次就找到了，表示使用主键索引或者唯一索引
- **eq_ref**：主键或者唯一索引中的所有字段被用于连接使用，只会返回一行匹配的数据。简单的select查询语句不会出现这种情况
- **ref**：普通索引扫描，可能返回多个符合查询条件的行
- fulltext：全文索引检索，全文索引的优先级很高，若全文索引和普通索引同时存在时，mysql不管代价，优先选择使用全文索引
- ref_or_null：与ref方法类似，只是增加了null值的比较
- index_merge：表示查询使用了两个以上的索引，索引合并的优化方法，最后取交集或者并集，常见and ，or的条件使用了不同的索引
- unique_subquery：用于where中的in形式子查询，子查询返回不重复值唯一值
- index_subquery：用于in形式子查询使用到了辅助索引或者in常数列表，子查询可能返回重复值，可以使用索引将子查询去重
- **range**：索引范围扫描，常见于使用>,<,between ,in ,like等运算符的查询中
- **index**：索引全表扫描，把索引树从头到尾扫描一遍
- **all**：遍历全表以找到匹配的行（Index与ALL虽然都是读全表，但index是从索引中读取，而ALL是从硬盘读取）

加粗的为常见的访问类型。

### possible_keys

- 指出 MySQL 能使用哪个索引在表中找到记录，查询涉及到的字段上若存在索引，则该索引将被列出，但不一定被查询使用
- 如果该列是 NULL，则没有相关的索引

### key

- 显示MySQL在查询中实际使用的索引，若没有使用索引，显示为 NULL
- 查询中若使用了**覆盖索引**，则该索引可能出现在 key 列表，不出现在 possible_keys

- 当select_type为index_merge时，这里可能出现两个以上的索引，其他的select_type这里只会出现一个

### key_len

- 索引中使用的字节数，**可通过该列计算命中了联合索引中的那几列**
- key_len 显示的值为索引字段的最大可能长度，并非实际使用长度，即 key_len 是根据表定义计算而得，不是通过表内检索出的
- 在不损失精确性的前提下，长度越短越好

> 计算规则：
>
> - 字符串
>
> 1. char(n)： n字节长度
> 2. varchar(n) ：2字节存储字符串长度，如果是utf-8，则长度3n + 2
>
> - 数值类型
>
> 1. tinyint：1字节
> 2. smallint：2字节
> 3. int：4字节
> 4. bigint：8字节
>
> - 时间类型
>
> 1. date：3字节
> 2. timestamp：4字节
> 3. datetime：8字节
>
> 如果字段允许为NULL，需要1字节记录是否为NULL
> 索引最大长度是768字节，当字符串过长时， mysql会做一个类似左前缀索引的处理，将前半部分的字符提取出来做索引

### ref

显示哪个字段或者常量与key一起被使用。

- 如果是使用的常量等值查询，这里会显示const。

- 如果是连接查询，被驱动表的执行计划这里会显示驱动表的关联字段。

- 如果是条件使用了表达式或者函数，或者条件列发生了内部隐式转换，这里可能显示为func。

### rows

表示MySQL根据表统计信息及索引选用情况，大致估算此处查询需要读取的行数，不是精确值。此参数很重要，在完成目的的情况下越少越好。

### extra

extra列提供了额外的信息，是能够帮助我们判断当前sql的是否使用了覆盖索引、文件排序、使用了索引进行查询条件等等的信息。

|             类型             |                             说明                             |
| :--------------------------: | :----------------------------------------------------------: |
|         using index          |                         使用覆盖索引                         |
|    using index condition     |      查询的列未被索引覆盖，where筛选条件是索引的前导列       |
|         using where          |      查询的列未被索引覆盖，where筛选条件非索引的前导列       |
|   using index;using where    |       查询的列被索引覆盖，where筛选条件非索引的前导列        |
|             NULL             | （既没有using index，也没有using where; using index，也没有using where）查询的列未被索引覆盖，并且where筛选条件是索引的前导列。<br>意味着用到了索引，但是部分字段未被索引覆盖，须通过“回表”来获取查询所需的字段 |
|       using temporary        | 用临时表保存中间结果，通常是在没有索引的列进行排序或者去重产生的。 |
|        using filesort        | MySQL有两种方式对查询结果进行排序，一种是使用索引，另一种是filesort（基于快排实现的外部排序，性能比较差），当数据量很大时，这将是一个CPU密集型的过程，所以可以通过建立合适的索引来优化排序的性能 |
|      using join buffer       | 使用了连接缓存： **Block Nested Loop：**连接算法是块嵌套循环连接;<br>**Batched Key Access：**连接算法是批量索引连接 |
|          Not exists          | MYSQL优化了LEFT JOIN，一旦它找到了匹配LEFT JOIN标准的行， 就不再搜索了 |
|       impossible where       |                    where子句的值总是false                    |
|           distinct           | 优化distinct操作，在找到第一匹配的元组后即停止找同样值的动作 |
| select tables optimized away | 在没有GROUP BY子句的情况下，基于索引优化MIN/MAX操作，或者对于MyISAM存储引擎优化COUNT(*)操作，不必等到执行阶段再进行计算，查询执行计划生成的阶段即完成优化 |

MySQL 执行计划的局限：

- 只是计划，不是执行 SQL 语句，可以随着底层优化器输入的更改而更改
- EXPLAIN 不会告诉显示关于触发器、存储过程的信息对查询的影响情况
- EXPLAIN 不考虑各种 Cache
- EXPLAIN 不能显示 MySQL 在执行查询时的动态，因为执行计划在执行查询之前生成
- EXPALIN 部分统计信息是估算的，并非精确值
- EXPALIN 只能解释 SELECT 操作，其他操作要重写为 SELECT 后查看执行计划
- EXPLAIN PLAN 显示的是在解释语句时数据库将如何运行 SQL 语句，由于执行环境和 EXPLAIN PLAN 环境的不同，此计划可能与 SQL 语句实际的执行计划不同

参考：[MySQL数据库：explain执行计划详解_张维鹏的博客-CSDN博客_数据库执行计划详解](https://blog.csdn.net/a745233700/article/details/84335453?spm=1001.2101.3001.6650.13&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~default-13.essearch_pc_relevant&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~default-13.essearch_pc_relevant)

------

## PROFILES分析SQL

SHOW PROFILES 能够在做 SQL 优化时分析当前会话中语句执行的**资源消耗**情况

- 通过 have_profiling 参数，能够看到当前 MySQL 是否支持 profile：

```sql
select @@have_profiling;
```

- 默认 profiling 是关闭的，可以通过 set 语句在 Session 级别开启 profiling：

```sql
SET profiling=1; -- 开启profiling 开关；
```

- 执行 SHOW PROFILES 指令， 来查看 SQL 语句执行的耗时：

```sql
SHOW PROFILES;
```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/115.png)

- 查看到该 SQL 执行过程中每个线程的状态和消耗的时间：

```sql
SHOW PROFILE FOR QUERY query_id;
```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/116.png)

**Sending data 状态**表示 MySQL 线程开始访问数据行并把结果返回给客户端，而不仅仅是返回给客户端。由于在 Sending data 状态下，MySQL 线程需要做大量磁盘读取操作，所以是整个查询中耗时最长的状态。

- 在获取到最消耗时间的线程状态后，MySQL 支持选择 all、cpu、block io 、context switch、page faults 等类型查看 MySQL 在使用什么资源上耗费了过高的时间。例如，选择查看 CPU 的耗费时间：

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/117.png)

|    字段    |              含义              |
| :--------: | :----------------------------: |
|   Status   |       sql 语句执行的状态       |
|  Duration  | sql 执行过程中每一个步骤的耗时 |
|  CPU_user  |       当前用户占有的cpu        |
| CPU_system |         系统占有的cpu          |

------

## Trace分析优化器执行计划

在执行计划中发现有的sql会走索引，有的sql即使明确使用了索引也不会走索引。这是因为mysql的内部优化器任务走索引的性能比不走索引全表扫描的性能要差，因此mysql内部优化器选择了使用全表扫描。

MySQL 提供了对 SQL 的跟踪， 通过 trace 文件能够进一步了解执行过程。

```sql
-- 开启trace
set session optimizer_trace="enabled=on", end_markers_in_json=on; 
-- 执行查询
select * from employees where name > 'a' order by position; 
-- 获得trace的分析结果
SELECT * FROM information_schema.OPTIMIZER_TRACE\G; -- \G代表竖列展示 
```

详细的看《跟上理解MySQL》第16章。

```sql
{
  "steps": [
    {
      "join_preparation": { -- 阶段1:进入到准备阶段
		...
      } /* join_preparation */
    },
    {
      "join_optimization": { -- 阶段2: 进入到优化阶段
        "select#": 1,
        "steps": [
          {
            "condition_processing": { -- 条件处理
                }
              ] /* steps */
            } /* condition_processing */
          },
          {
            "table_dependencies": [ -- 表依赖详情
          {
            "rows_estimation": [
              {
                  "potential_range_indexes": [ -- 可能使用到的索引
                    {
                      "index": "PRIMARY", -- 主键索引
                      "usable": false,
                      "cause": "not_applicable"
                    },
                    {
                      "index": "idx_name_age_position", -- 联合索引
                      "usable": true,
                      "key_parts": [
                        "name",
                        "age",
                        "position",
                        "id"
                      ] /* key_parts */
                    },
                  } /* skip_scan_range */,
                      
                  "analyzing_range_alternatives": { -- 分析各个索引使用的成本
                    "range_scan_alternatives": [
                      {
                        "index": "idx_name_age_position",
                        "ranges": [
                          "a < name"
                        ] /* ranges */,
                        "index_dives_for_eq_ranges": true,
                        "rowid_ordered": false,
                        "using_mrr": true,
                        "index_only": false, -- 是否使用了覆盖索引
                        "rows": 2799198, -- 要扫描的行数
                        "cost": 2.08e6, -- 要花费的时间
                        "chosen": false, -- 是否选择使用这个索引
                        "cause": "cost" -- 不选择的原因：开销比较大
                      }
                    ] /* range_scan_alternatives */,
                   
          {
            "considered_execution_plans": [
              {
                "plan_prefix": [
                ] /* plan_prefix */,
                "table": "`employees`",
                "best_access_path": { -- 最优访问路径
                  "considered_access_paths": [ -- 最后选择的访问路径
                    {
                      "rows_to_scan": 5598397, -- 全表扫描的行数
                      "access_type": "scan", -- 全表扫描
                      "resulting_rows": 5.6e6, -- 结果的行数
                      "cost": 576655, -- 花费的时间
                      "chosen": true, -- 选择这种方式
                      "use_tmp_table": true
                    }
                  ] /* considered_access_paths */
                } /* best_access_path */,

}
```

------

------

# SQL优化

## 工程优化

参考《MySQL军规升级版》：[58到家MySQL军规升级版 - 云+社区 - 腾讯云 (tencent.com)](https://cloud.tencent.com/developer/article/1102548)

### 1.基础规范

- 表存储引擎必须使用InnoDB
- 表字符集默认使用utf8，必要时候使用utf8mb4

解读：

（1）通用，无乱码风险，汉字3字节，英文1字节

（2）utf8mb4是utf8的超集，有存储4字节例如表情符号时，使用它

- 禁止使用存储过程，视图，触发器，Event

解读：

（1）对[数据库](https://cloud.tencent.com/solution/database?from=10680)性能影响较大，互联网业务，能让站点层和服务层干的事情，不要交到数据库层

（2）调试，排错，迁移都比较困难，扩展性较差

- 禁止在数据库中存储大文件，例如照片，可以将大[文件存储](https://cloud.tencent.com/product/cfs?from=10680)在对象存储系统，数据库中存储路径
- 禁止在线上环境做数据库压力测试
- 测试，开发，线上数据库环境必须隔离

### 2.命名规范

- 库名，表名，列名必须用小写，采用下划线分隔

解读：abc，Abc，ABC都是给自己埋坑

- 库名，表名，列名必须见名知义，长度不要超过32字符

解读：tmp，wushan谁TM知道这些库是干嘛的

- 库备份必须以bak为前缀，以日期为后缀
- 从库必须以-s为后缀
- 备库必须以-ss为后缀

### 3.表设计规范

- 单实例表个数必须控制在2000个以内
- 单表分表个数必须控制在1024个以内
- 表必须有主键，推荐使用UNSIGNED整数为主键

潜在坑：删除无主键的表，如果是row模式的主从架构，从库会挂住

- 禁止使用外键，如果要保证完整性，应由应用程式实现

解读：外键使得表之间相互耦合，影响update/delete等SQL性能，有可能造成死锁，高并发情况下容易成为数据库瓶颈

- 建议将大字段，访问频度低的字段拆分到单独的表中存储，分离冷热数据

解读：具体参加《[如何实施数据库垂直拆分](https://cloud.tencent.com/developer/article/1048618?from=10680)*》*

### 4.列设计规范

- 根据业务区分使用tinyint/int/bigint，分别会占用1/4/8字节
- 根据业务区分使用char/varchar

解读：

（1）字段长度固定，或者长度近似的业务场景，适合使用char，能够减少碎片，查询性能高

（2）字段长度相差较大，或者更新较少的业务场景，适合使用varchar，能够减少空间

- 根据业务区分使用datetime/timestamp

解读：前者占用5个字节，后者占用4个字节，存储年使用YEAR，存储日期使用DATE，存储时间使用datetime

- 必须把字段定义为NOT NULL并设默认值

解读：

（1）NULL的列使用索引，索引统计，值都更加复杂，[MySQL](https://cloud.tencent.com/product/cdb?from=10680)更难优化

（2）NULL需要更多的存储空间

（3）NULL只能采用IS NULL或者IS NOT NULL，而在=/!=/in/not in时有大坑

- 使用INT UNSIGNED存储IPv4，不要用char(15)
- 使用varchar(20)存储手机号，不要使用整数

解读：

（1）牵扯到国家代号，可能出现+/-/()等字符，例如+86

（2）手机号不会用来做数学运算

（3）varchar可以模糊查询，例如like ‘138%’

- 使用TINYINT来代替ENUM

解读：ENUM增加新值要进行DDL操作

### 5.索引规范

- 唯一索引使用uniq_[字段名]来命名
- 非唯一索引使用idx_[字段名]来命名
- 单张表索引数量建议控制在5个以内

解读：

（1）互联网高并发业务，太多索引会影响写性能

（2）生成执行计划时，如果索引太多，会降低性能，并可能导致MySQL选择不到最优索引

（3）异常复杂的查询需求，可以选择ES等更为适合的方式存储

- 组合索引字段数不建议超过5个

解读：如果5个字段还不能极大缩小row范围，八成是设计有问题

- 不建议在频繁更新的字段上建立索引
- 非必要不要进行JOIN查询，如果要进行JOIN查询，被JOIN的字段必须类型相同，并建立索引

解读：踩过因为JOIN字段类型不一致，而导致全表扫描的坑么？

- 理解组合索引最左前缀原则，避免重复建设索引，如果建立了(a,b,c)，相当于建立了(a), (a,b), (a,b,c)

### 6.SQL规范

- 禁止使用select *，只获取必要字段

解读：

（1）select 会增加cpu/io/内存/带宽的消耗

（2）指定字段能有效利用索引覆盖

（3）指定字段查询，在表结构变更时，能保证对应用程序无影响

- insert必须指定字段，禁止使用insert into T values()

解读：指定字段插入，在表结构变更时，能保证对应用程序无影响

- 隐式类型转换会使索引失效，导致全表扫描
- 禁止在where条件列使用函数或者表达式

解读：导致不能命中索引，全表扫描

- 禁止负向查询以及%开头的模糊查询

解读：导致不能命中索引，全表扫描

- 禁止大表JOIN和子查询
- 同一个字段上的OR必须改写问IN，IN的值必须少于50个
- 应用程序必须捕获SQL异常

解读：方便定位线上问题

------

## SQL语法的优化

### 大批量插入数据

当使用load 命令导入数据的时候，适当的设置可以提高导入的效率。

![image-20211115183138826](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/118.png)

对于 InnoDB 类型的表，有以下几种方式可以提高导入的效率：

- 主键顺序插入

因为InnoDB类型的表是按照主键的顺序保存的，所以将导入的数据按照主键的顺序排列，可以有效的提高导入数据的效率。如果InnoDB表没有主键，会采用unique列，如果unique列也没有，那么系统会自动默认创建一个内部列 `row_id` 作为主键。

- 关闭唯一性校验

在导入数据前执行 `SET UNIQUE_CHECKS=0`，关闭唯一性校验，在导入结束后执行`SET UNIQUE_CHECKS=1`，恢复唯一性校验，可以提高导入的效率。

- 手动提交事务

如果应用使用自动提交的方式，建议在导入前执行 `SET AUTOCOMMIT=0`，关闭自动提交，导入结束后再执行 `SET AUTOCOMMIT=1`，打开自动提交，也可以提高导入的效率。

### 优化insert语句

当进行数据的insert操作的时候，可以考虑采用以下几种优化方案。

- 如果需要同时对一张表插入很多行数据时，应该尽量使用一条insert语句完成多个值的插入，这种方式将大大的缩减客户端与数据库之间的连接、关闭等消耗。使得效率比分开执行的单个insert语句快。

- 在事务中进行数据插入。
- 数据有序插入

### 优化order by语句

通过对返回数据进行排序，所有不通过索引直接返回结果的排序都叫 FileSort 排序，会在内存中重新排序；通过有序索引顺序扫描直接返回**有序数据**，这种情况为 Using index，不需要额外排序，操作效率高

```sql
# 联合索引为(name, age, position)

# using filesort
Explain select * from employees where name='customer' order by position;
# 没有使用文件排序 
Explain select * from employees where name='customer' order by age, position;
# 不满足最左前缀法则，使用了文件排序
Explain select * from employees where name='customer' order by position, age;
# 满足最左前缀法则，使用索引排序
Explain select * from employees where name='customer' and age=20 order by position, age;
# 排序方向不同，没有使用索引排序 但没有使用文件排序
Explain select * from employees where name='customer' and age=20 order by age, position desc;
# 使用范围查询，使用了文件排序
Explain select * from employees where name in ('customer','aa') order by age, position;
# 使用范围查询（满足条件的记录条数太多了 效率还不如全表扫描），使用了文件排序
Explain select * from employees where name > 'a' order by name;
```

- 优化方案：

  - 尽量减少额外的排序，通过索引直接返回有序数据。
  - 如果排序的字段创建了联合索引，那么尽量在业务不冲突的情况下，遵循最左前缀法则来写排序语句。

  where 条件 和 Order by 使用相同的索引，并且Order By 的顺序和索引顺序相同以及要求Order  by 的字段都是升序、或者都是降序。否则肯定需要额外的操作，这样就会出现FileSort。

  - 如果文件排序没办法避免，那么尽量想办法使用覆盖索引。all -> index

### 优化Filesort

通过创建合适的索引，能够减少 Filesort 的出现，但是在某些情况下，条件限制不能让Filesort消失，那就需要加快 Filesort的排序操作。对于Filesort ， MySQL 有两种排序算法：

- 两次（双路）扫描算法 ：MySQL4.1 之前，使用该方式排序。首先根据条件取出排序字段和行指针信息，然后在排序区 sort buffer 中排序，如果sort buffer不够，则在临时表 temporary table 中存储排序结果。完成排序之后，再根据行指针回表读取记录，该操作可能会导致大量随机I/O操作。

- 一次（单路）扫描算法：一次性取出满足条件的所有字段，然后在排序区 sort  buffer 中排序后直接输出结果集。排序时内存开销较大，但是排序效率比两次扫描算法要高。

![image-20211115190336356](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/119.png)

MySQL 通过比较系统变量 `max_length_for_sort_data` 的大小和Query语句取出的字段总大小， 来判定是否那种排序算法，如果`max_length_for_sort_data` 更大，那么使用第二种优化之后的算法；否则使用第一种。

可以适当提高 `sort_buffer_size`  和 `max_length_for_sort_data`  系统变量，来增大排序区的大小，提高排序的效率。

### 优化group by语句

由于GROUP BY 实际上也同样会进行排序操作，而且与ORDER BY 相比，GROUP BY 主要只是多了排序之后的分组操作。当然，如果在分组的时候还使用了其他的一些聚合函数，那么还需要一些聚合函数的计算。所以，在GROUP BY 的实现过程中，与 ORDER BY 一样也可以利用到索引。

但多了一点，如果查询包含 group by 但是用户想要避免排序结果的消耗， 则可以执行order by null 禁止排序。

### 优化嵌套查询

Mysql4.1版本之后，开始支持SQL的子查询。这个技术可以使用SELECT语句来创建一个单列的查询结果，然后把这个结果作为过滤条件用在另一个查询中。使用子查询可以一次性的完成很多逻辑上需要多个步骤才能完成的SQL操作，同时也可以避免事务或者表锁死，并且写起来也很容易。但是，有些情况下，子查询是可以被更高效的连接（JOIN）替代。

连接(Join)查询之所以更有效率一些 ，是因为MySQL不需要在内存中创建临时表来完成这个逻辑上需要两个步骤的查询工作。

### 优化join连接

在join中会涉及到大表（数据量大）和小表（数据量小）的概念。MySQL内部优化器会根据关联字段是否创建了索引来使用不同的算法：

- Nlj（嵌套循环算法）：如果**关联字段使用了索引**，mysql会对小表做全表扫描，用小表的数据去和大表的数据去做索引字段的关联查询（type：ref）

- bnlj（块嵌套循环算法）：如果关联字段没有使用索引，mysql会提供一个join buffer缓冲区，先把小表放到缓冲区中，然后全表扫描大表，把大表的数据和缓冲区中的小表数据在内存中进行匹配。

结论：**使用join查询时，一定要建立关联字段的索引，且两张表的关联字段在设计之初就要做到字段类型、长度是一致的，否则索引失效**。并且，最好不要用 * 作为查询列表，而把真正用到的列作为查询条件。

### 优化OR条件

对于包含OR的查询子句，如果要利用索引，则OR之间的每个条件列都必须用到索引 ， 而且不能使用到复合索引； 如果没有索引，则应该考虑增加索引。

> 举例：
>
> 执行查询语句：
>
> ```sql
> EXPLAIN SELECT * FROM emp WHERE id = 1 OR age = 30;	-- 两个索引，并且不是复合索引
> ```
>
> ![image-20211115191243212](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/120.png)
>
> ![image-20211115191315982](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/121.png)
>
> 使用 union 替换 or ：
>
> ![image-20211115191329478](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/122.png)
>
> 比较下重要指标，发现主要差别是 type 和 ref 这两项
>
> type 显示的是访问类型，是较为重要的一个指标，结果值从好到坏依次是：
>
> ```
> system > const > eq_ref > ref > fulltext > ref_or_null  > index_merge > unique_subquery > index_subquery > range > index > ALL
> ```

看出 UNION 要优于 OR 的原因：

- UNION 语句的 type 值为 ref，OR 语句的 type 值为 range
- UNION 语句的 ref 值为 const，OR 语句的 ref 值为 null，const 表示是常量值引用，非常快

### 优化limit分页查询

一般分页查询时，通过创建覆盖索引能够比较好地提高性能。一个常见又非常头疼的问题就是 limit 2000000,10  ，此时需要MySQL排序前2000010 记录，仅仅返回2000000 - 2000010 的记录，其他记录丢弃，查询排序的代价非常大 。

优化方案：

- 在索引上完成排序分页操作，最后根据主键关联回原表查询所需要的其他列内容。
- 如果有主键自增的表（即主键连续），可以使用主键来做条件，把Limit 查询转换成某个位置的查询 。

> ```sql
> Explain select * from employees where id>2000000 limit 10
> ```

- 如果主键不连续，可以先通过覆盖索引的查找，然后在使用join做连接查询获取所有数据。这样比全表扫描要快。

> ```sql
> explain select * from employees a inner join (select id from employees order by name limit 2000000,10)  b on a.id = b.id;
> ```

### 优化in和exists语句

遵循小表驱动大表，关联字段建立索引。

在sql中如果A表是大表，B表是小表，那么使用in会更加合适，反之应该使用exists。

### 优化count语句

在不同的 MySQL 引擎中，count(*) 有不同的实现方式：

- MyISAM 引擎把一个表的总行数存在了磁盘上，因此执行 count(*) 的时候会直接返回这个数，效率很高，但不支持事务
- show table status 命令通过采样估算可以快速获取，但是不准确
- InnoDB 表执行 count(*) 会遍历全表，虽然结果准确，但会导致性能问题

对于count的优化应该是**架构层面的优化**，因为count的统计是在一个产品会经常出现，而且每个用户访问，所以对于访问频率过高的数据建议维护在缓存（redis等）中。

优化方案：

- 计数保存在 Redis 中，但是更新 MySQL 和 Redis 的操作不是原子的，会存在数据一致性的问题
- 计数直接放到数据库里单独的一张计数表中，利用事务解决计数精确问题

并发系统性能的角度考虑，应该先插入操作记录再更新计数表，因为更新计数表涉及到行锁的竞争，**先插入再更新能最大程度地减少事务之间的锁等待，提升并发度**。

count 函数的按照效率排序：`count(字段) < count(主键id) < count(1) ≈ count(*)`，所以建议尽量使用 count(*)

- count(主键 id)：InnoDB 引擎会遍历整张表，把每一行的 id 值都取出来返回给 Server 层，Server 判断 id 不为空就按行累加
- count(1)：InnoDB 引擎遍历整张表但不取值，Server 层对于返回的每一行，放一个数字 1 进去，判断不为空就按行累加
- count(字段)：如果这个字段是定义为 not null 的话，一行行地从记录里面读出这个字段，判断不能为 null，按行累加；如果这个字段定义允许为 null，那么执行的时候，判断到有可能是 null，还要把值取出来再判断一下，不是 null 才累加

### 使用SQL提示

SQL提示，是优化数据库的一个重要手段，简单来说，就是在SQL语句中加入一些人为的提示来达到优化操作的目的。

- USE INDEX：在查询语句中表名的后面，添加 use index 来提供希望MySQL去参考的索引列表，就可以让MySQL不再考虑其他可用的索引。

> ```sql
> CREATE INDEX idx_seller_name ON tb_seller(name);
> EXPLAIN SELECT * FROM tb_seller USE INDEX(idx_seller_name) WHERE name='小米科技';
> ```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/123.png)

- IGNORE INDEX：让 MySQL 忽略一个或者多个索引，则可以使用 IGNORE INDEX 作为提示

> ```sql
> EXPLAIN SELECT * FROM tb_seller IGNORE INDEX(idx_seller_name) WHERE name = '小米科技';
> ```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/124.png)

- FORCE INDEX：强制 MySQL 使用一个特定的索引

> ```sql
> EXPLAIN SELECT * FROM tb_seller FORCE INDEX(idx_seller_name_sta_addr) WHERE NAME='小米科技';
> ```

![](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/125.png)

------

------

# 其他优化汇总

## 应用优化

前面介绍了很多关于SQL语句的优化措施。但是在实际生产环境中，由于数据库本身的性能局限，就必须要对前台的应用进行一些优化，来降低数据库的访问压力。

### 使用连接池

对于访问数据库来说，建立连接的代价比较昂贵，频繁的创建关闭连接，比较耗费资源，可以通过建立数据库连接池，提高访问的性能。

### 减少对MySQL的访问

- 避免对数据进行重复检索

在编写应用代码时，需要能够理清对数据库的访问逻辑。能够一次连接就获取到结果的，就不用两次连接，这样可以大大减少对数据库无用的重复请求。但也要注意，不要使用过长的连接，不然会导致内存爆满。

- 增加cache层

在应用中，可以在应用中增加**缓存层**来达到减轻数据库负担的目的。因此可以部分数据从数据库中抽取出来放到应用端以文本方式存储， 或者使用框架(Mybatis, Hibernate)提供的一级缓存/二级缓存，或者使用redis数据库来缓存数据 。

### 负载均衡 

负载均衡是应用中使用非常普遍的一种优化方法，它的机制是利用某种均衡算法，将固定的负载量分布到不同的服务器上， 以此来降低单台服务器的负载，达到优化的效果。

- 利用MySQL复制分流查询

通过MySQL的主从复制，实现读写分离，使增删改操作走主节点，查询操作走从节点，从而可以降低单台服务器的读写压力。

![image-20211115224024092](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/126.png)

- 采用分布式数据库架构

分布式数据库架构适合大数据量、负载高的情况，具有良好的拓展性和高可用性。通过在多台服务器之间分布数据，可以实现在多台服务器之间的负载均衡，提高访问效率。

------

------

## Mysql中查询缓存优化

开启Mysql的查询缓存，当执行完全相同的SQL语句的时候，服务器就会直接从缓存中读取结果，当数据被修改，之前的缓存会失效，**修改比较频繁的表不适合做查询缓存**。MySQL 8.0之后就删除了这部分。

### 查询缓存配置

- 查看当前的MySQL数据库是否支持查询缓存

```sql
SHOW VARIABLES LIKE 'have_query_cache';	
```

![image-20211115224449578](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/127.png)

- 查看当前MySQL是否开启了查询缓存 

```sql
SHOW VARIABLES LIKE 'query_cache_type';
```

![image-20211115224542703](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/128.png)

- 查看查询缓存的占用大小

```sql
SHOW VARIABLES LIKE 'query_cache_size';
```

![image-20211115224607085](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/129.png)

- 查看查询缓存的状态变量

```sql
SHOW STATUS LIKE 'Qcache%';
```

![image-20211115224654046](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/130.png)

各个变量的含义如下：

|          参数           |                             含义                             |
| :---------------------: | :----------------------------------------------------------: |
|   Qcache_free_blocks    |                   查询缓存中的可用内存块数                   |
|   Qcache_free_memory    |                     查询缓存的可用内存量                     |
|       Qcache_hits       |                        查询缓存命中数                        |
|     Qcache_inserts      |                    添加到查询缓存的查询数                    |
|  Qcache_lowmen_prunes   |            由于内存不足而从查询缓存中删除的查询数            |
|    Qcache_not_cached    | 非缓存查询的数量（由于 query_cache_type 设置而无法缓存或未缓存） |
| Qcache_queries_in_cache |                    查询缓存中注册的查询数                    |
|   Qcache_total_blocks   |                      查询缓存中的块总数                      |

### 开启查询缓存

MySQL的查询缓存默认是关闭的，需要手动配置参数 query_cache_type ， 来开启查询缓存。query_cache_type 该参数的可取值有三个 ：

|     值      |                             含义                             |
| :---------: | :----------------------------------------------------------: |
|  OFF 或 0   |                       查询缓存功能关闭                       |
|   ON 或 1   | 查询缓存功能打开，SELECT的结果符合缓存条件即会缓存，否则，不予缓存，显式指定 SQL_NO_CACHE，不予缓存 |
| DEMAND 或 2 | 查询缓存功能按需进行，显式指定 SQL_CACHE 的SELECT语句才会缓存；其它均不予缓存 |

在 /usr/my.cnf 配置中，增加以下配置 ： 

![image-20211115224829099](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/131.png)

配置完毕之后，重启服务既可生效 ；

然后就可以在命令行执行SQL语句进行验证 ，执行一条比较耗时的SQL语句，然后再多执行几次，查看后面几次的执行时间；获取通过查看查询缓存的缓存命中数，来判定是否走查询缓存。

### 查询缓存SELECT选项

可以在SELECT语句中指定两个与查询缓存相关的选项 ：

- SQL_CACHE : 如果查询结果是可缓存的，并且 query_cache_type 系统变量的值为ON或 DEMAND ，则缓存查询结果 。

- SQL_NO_CACHE : 服务器不使用查询缓存。它既不检查查询缓存，也不检查结果是否已缓存，也不缓存查询结果。

### 查询缓存失效的情况

- SQL 语句不一致的情况， 要想命中查询缓存，查询的SQL语句必须一致

- 当查询语句中有一些不确定的时，则不会缓存。如 ： now() , current_date() , curdate() , curtime() , rand() , uuid() , user() , database() 
- 不使用任何表查询语句
- 查询 mysql， information_schema或  performance_schema 数据库中的表时，不会走查询缓存
- 在存储的函数，触发器或事件的主体内执行的查询
- 如果表更改，则使用该表的所有高速缓存查询都将变为无效并从高速缓存中删除。这包括使用`MERGE`映射到已更改表的表的查询。一个表可以被许多类型的语句，如被改变 INSERT， UPDATE， DELETE， TRUNCATE TABLE， ALTER TABLE， DROP TABLE，或 DROP DATABASE 

------

------

## Mysql内存管理及优化

### 内存优化原则

- 将尽量多的内存分配给MySQL做缓存，但要给操作系统和其他程序预留足够内存
- MyISAM 存储引擎的数据文件读取依赖于操作系统自身的IO缓存，如果有MyISAM表，就要预留更多的内存给操作系统做IO缓存
- 排序区、连接区等缓存是分配给每个数据库会话（session）专用的，其默认值的设置要根据最大连接数合理分配，如果设置太大，不但浪费资源，而且在并发连接较高时会导致物理内存耗尽

### MyISAM 内存优化

MyISAM 存储引擎使用 key_buffer 缓存索引块，加速 MyISAM 索引的读写速度。对于 MyISAM 表的数据块没有特别的缓存机制，完全依赖于操作系统的 IO 缓存

- key_buffer_size

key_buffer_size决定MyISAM索引块缓存区的大小，直接影响到MyISAM表的存取效率。

可以在MySQL参数文件中设置key_buffer_size的值，对于一般MyISAM数据库，建议至少将1/4可用内存分配给key_buffer_size。

在/usr/my.cnf 中做如下配置：

```sql
key_buffer_size=512M
```

- read_buffer_size

如果需要经常顺序扫描MyISAM表，可以通过增大read_buffer_size的值来改善性能。但需要注意的是read_buffer_size是每个session独占的，如果默认值设置太大，就会造成内存浪费。

- read_rnd_buffer_size

对于需要做排序的MyISAM表的查询，如带有order by子句的sql，适当增加 read_rnd_buffer_size 的值，可以改善此类的sql性能。但需要注意的是 read_rnd_buffer_size 是每个session独占的，如果默认值设置太大，就会造成内存浪费。

### InnoDB 内存优化

innodb用一块内存区做IO缓存池，该缓存池不仅用来缓存innodb的索引块，而且也用来缓存innodb的数据块。

- innodb_buffer_pool_size

该变量决定了 innodb 存储引擎表数据和索引数据的最大缓存区大小。在保证操作系统及其他程序有足够内存可用的情况下，innodb_buffer_pool_size 的值越大，缓存命中率越高，访问InnoDB表需要的磁盘I/O 就越少，性能也就越高。

```sql
innodb_buffer_pool_size=512M
```

- innodb_log_buffer_size

决定了innodb重做日志缓存的大小，对于可能产生大量更新记录的大事务，增加innodb_log_buffer_size的大小，可以避免innodb在事务提交前就执行不必要的日志写入磁盘操作。

```sql
innodb_log_buffer_size=10M
```

------

------

## MySQL并发参数调整

从实现上来说，MySQL Server 是多线程结构，包括后台线程和客户服务线程。多线程可以有效利用服务器资源，提高数据库的并发性能。

在Mysql中，控制并发连接和线程的主要参数包括 max_connections、back_log、thread_cache_size、table_open_cahce。

- max_connections：控制允许连接到MySQL数据库的最大数量，默认值是 151

如果状态变量 connection_errors_max_connections 不为零，并且一直增长，则说明不断有连接请求因数据库连接数已达到允许最大值而失败，这时可以考虑增大max_connections 的值。

- back_log：控制MySQL监听TCP端口时设置的积压请求栈大小

如果MySql的连接数达到max_connections时，新来的请求将会被存在堆栈中，以等待某一连接释放资源，该堆栈的数量即back_log，如果等待连接的数量超过back_log，将不被授予连接资源，将会报错。5.6.6 版本之前默认值为 50 ， 之后的版本默认为 50 + （max_connections / 5）， 但最大不超过900。

如果需要数据库在较短的时间内处理大量连接请求， 可以考虑适当增大back_log 的值。

- table_open_cache

该参数用来控制所有SQL语句执行线程可打开表缓存的数量， 而在执行SQL语句时，每一个SQL执行线程至少要打开 1 个表缓存。该参数的值应该根据设置的最大连接数 max_connections 以及每个连接执行关联查询中涉及的表的最大数量来设定 ：max_connections x N ；

- thread_cache_size

为了加快连接数据库的速度，MySQL 会缓存一定数量的客户服务线程以备重用，通过参数 thread_cache_size 可控制 MySQL 缓存客户服务线程的数量。

- innodb_lock_wait_timeout

该参数是用来设置InnoDB 事务等待行锁的时间，默认值是50ms ， 可以根据需要进行动态设置。对于需要快速反馈的业务系统来说，可以将行锁的等待时间调小，以避免事务长时间挂起； 对于后台运行的批量处理程序来说， 可以将行锁的等待时间调大， 以避免发生大的回滚操作。

------

------

# MySQL常用工具

## mysql

该mysql不是指mysql服务，而是指mysql的客户端工具。

语法 ：

```sql
mysql [options] [database]
```

连接选项：

```text
参数 ： 
	-u, --user=name			指定用户名
	-p, --password[=name]	指定密码
	-h, --host=name			指定服务器IP或域名
	-P, --port=#			指定连接端口
```

> 举例：
>
> ```sql
> mysql -h 127.0.0.1 -P 3306 -u root -p
> 	
> mysql -h127.0.0.1 -P3306 -uroot -p2143
> ```

执行选项：

```sql
-e, --execute=name 执行SQL语句并退出
```

此选项可以在Mysql客户端执行SQL语句，而不用连接到MySQL数据库再执行，对于一些批处理脚本，这种方式尤其方便。

```sql
mysql -uroot -p2143 db01 -e "select * from tb_book";
```

![1555325632715](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/132.png) 

------

## mysqladmin

mysqladmin 是一个执行管理操作的客户端程序。可以用它来检查服务器的配置和当前状态、创建并删除数据库等。

可以通过 ： mysqladmin --help  指令查看帮助文档

![1555326108697](https://github.com/Frank-gg/MySQL-notes/blob/master/MySQL%20Picture/134.png) 

> 举例：
>
> ```sql
> mysqladmin -uroot -p2143 create 'test01';  
> mysqladmin -uroot -p2143 drop 'test01';
> mysqladmin -uroot -p2143 version;
> ```
>

------

## mysqlbinlog

由于服务器生成的二进制日志文件以二进制格式保存，所以如果想要检查这些文本的文本格式，就会使用到mysqlbinlog 日志管理工具。

语法 ：

```
mysqlbinlog [options]  log-files1 log-files2 ...

选项：
	
	-d, --database=name : 指定数据库名称，只列出指定的数据库相关操作。
	
	-o, --offset=# : 忽略掉日志中的前n行命令。
	
	-r,--result-file=name : 将输出的文本格式日志输出到指定文件。
	
	-s, --short-form : 显示简单格式， 省略掉一些信息。
	
	--start-datatime=date1  --stop-datetime=date2 : 指定日期间隔内的所有日志。
	
	--start-position=pos1 --stop-position=pos2 : 指定位置间隔内的所有日志。
```

------

## mysqldump

mysqldump 客户端工具用来备份数据库或在不同数据库之间进行数据迁移。备份内容包含创建表，及插入表的SQL语句。

语法 ：

```
mysqldump [options] db_name [tables]

mysqldump [options] --database/-B db1 [db2 db3...]

mysqldump [options] --all-databases/-A
```

连接选项：

```
参数 ： 
	-u, --user=name			指定用户名
	-p, --password[=name]	指定密码
	-h, --host=name			指定服务器IP或域名
	-P, --port=#			指定连接端口
```

输出内容选项：

```text
参数：
	--add-drop-database		在每个数据库创建语句前加上 Drop database 语句
	--add-drop-table		在每个表创建语句前加上 Drop table 语句 , 默认开启 ; 不开启 (--skip-add-drop-table)
	
	-n, --no-create-db		不包含数据库的创建语句
	-t, --no-create-info	不包含数据表的创建语句
	-d --no-data			不包含数据
	-T, --tab=name			自动生成两个文件：一个.sql文件，创建表结构的语句；
	 						一个.txt文件，数据文件，相当于select into outfile  
```

> 举例
>
> ```sql
> mysqldump -uroot -p2143 db01 tb_book --add-drop-database --add-drop-table > a
> mysqldump -uroot -p2143 -T /tmp test city
> ```
>

------

## mysqlimport/source

mysqlimport 是客户端数据导入工具，用来导入mysqldump 加 -T 参数后导出的文本文件。

语法：

```sql
mysqlimport [options]  db_name  textfile1  [textfile2...]
```

> 举例：
>
> ```sql
> mysqlimport -uroot -p2143 test /tmp/city.txt
> ```
>

如果需要导入sql文件,可以使用mysql中的source 指令 : 

```sql
source /root/tb_book.sql
```

------

##  ysqlshow

mysqlshow 客户端对象查找工具，用来很快地查找存在哪些数据库、数据库中的表、表中的列或者索引。

语法：

```
mysqlshow [options] [db_name [table_name [col_name]]]
```

参数：

```
--count		显示数据库及表的统计信息（数据库，表 均可以不指定）

-i			显示指定数据库或者指定表的状态信息
```

> 举例：
>
> ```sql
> #查询每个数据库的表的数量及表中记录的数量
> mysqlshow -uroot -p2143 --count
> 
> #查询test库中每个表中的字段书，及行数
> mysqlshow -uroot -p2143 test --count
> 
> #查询test库中book表的详细情况
> mysqlshow -uroot -p2143 test book --count
> ```
>

