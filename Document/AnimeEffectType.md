# 1. 动画引擎使用

已知：
1. 顶层控制器，调用一次处理器的step后，导出动画数据，然后将动画数据导入动画引擎。此后，顶层控制器将调用动画引擎的refresh n次（n是固定的），然后再次调用处理器的step。
2. 涉及到坐标时，处理器导出的是“格子”的坐标，而不是屏幕像素点的坐标。
3. 如果某个要绘制的物体占据多个格子，那么坐标代表的是左上角坐标。横向向右为x坐标正方向，纵向向下为y坐标正方向

以下这些是处理器要求动画引擎实现的动画效果



## 1. 初始化

**接口：**`Info* init_draw();`

**使用方法：**

返回一个全局唯一的信息指针，用于存储和更新动画信息，应该在整个游戏最初就被创建



## 2. 更新背景

**接口：**`void renew_backgrounds(int **obstacles, int length);`

**绘制：**绘制出游戏的背景板

处理器提供的信息：

1. 所有障碍物（不可进入区域，不含边界）的数组，无障碍物是为null

   障碍物数组为一个n*3大小的数组，第0位为该障碍物的素材标号，第一位为素材的x值，第二位为素材的y值

2. 障碍物数组的长度

**使用方法：**

直接调用该函数即可



## 3. 更新玩家信息

**接口：**`void renew_status(Player players[2]);`

**绘制：**绘制出玩家状态栏

处理器提供信息：

1. 玩家数据数组

**使用方法：**

```c
typedef struct Player{
    int playerName;	//玩家编号 1或2
    int hp;			//玩家百分比血量，传入时为0~100
    int* skills;	//玩家拥有的技能的数组，存储的为技能的编号
    int skillNum;	//技能数组的大小
} Player;
```

直接调用即可

## 4. 导入信息

**接口：**`void import_info(Info *info,InfoMove *infomove, int lengthMove, InfoEffect *infoeffect, int lengthEffect);`

处理器提供的信息：

1. 信息指针
2. 移动信息数组
3. 移动信息数组长度
4. 效果信息数组
5. 效果信息数组长度

**使用方法：**

直接调用即可导入信息，info为全局信息指针（init创建），其余参数的详细信息移步该文档的1.6与1.7节

## 5. 更新游戏进程

**接口：**`void refresh(Info info, int cnt);`

**绘制：**绘制游戏过程动画

处理器提供的信息：

1. 信息指针
2. 计数器值

**使用方法：**

在计数周期内，每个周期都调用一个该函数，cnt为当前计数器的值，范围为`0 ~ MAX_TURN-1`

## 6. 静止物体

**接口：**`void draw_effect(InfoEffect infoEffect);（private）`

**绘制：**在显示时间内保持在某个坐标不动的物体
处理器提供的信息：

1. x坐标
2. y坐标
3. 素材标号

**使用方法：**

借助`import_info`函数，将数据导入`InfoEffect *infoeffect`数组中，内部会从中读取数据，并按照数组排序从小到大以此实现动画效果

```c
typedef struct InfoEffect{
    int tag;	//素材编号
    int x;		//x坐标
    int y;		//y坐标
}InfoEffect;
```

**特别说明：**出生效果请使用该接口传入信息

[传入数据]:传入数据永远使用`import_info`方法

## 7. 移动物体

**接口：**`void draw_move(InfoMove infoMove);（private）`

**绘制：给定初位置与末位置，显现时间与消失时间，要求物体从匀速移动到末位置**
处理器提供的信息：

1. 初位置x坐标
2. 初位置y坐标
3. 末位置x坐标
4. 末位置y坐标
5. 素材标号

**使用方法：**

借助`import_info`函数，将数据导入`InfoMove *infomove`数组中，内部会从中读取数据，并按照数组排序从小到大以此实现动画效果

```c
typedef struct InfoMove{
    int tag;		//素材标号
    int x_start;	//初始x位置
    int y_start;	//初始y位置
    int x_dest;		//末了x位置
    int y_dest;		//末了y位置	
}InfoMove;
```

[传入数据]:传入数据永远使用`import_info`方法

# 2. 控制器调用示例

当控制器每完成一个step之后，应该立即调用动画引擎更新画面

下面我将给出一个调用示例：

```c
new Info = init_draw();							//创建一个全局唯一的信息指针
……
// begin draw
import_info(infoM, lengthM, infoE, lengthE);	//导入输入
for(10){
    renew_backgrounds(obstacles, length);		//绘制基础背景
    refresh(info, cnt)							//绘制游戏过程中的场景
}
renew_status(players);							//绘制玩家状态栏
// end draw
```

按照以上示例所示运行，则会成功将该次传入的效果在屏幕上刷新10次

**调用应当遵循以下原则：**

1. 最先被调用的一定为`import_info`
2. `renew_backgrounds 和 refresh`两个函数一定为捆绑调用，且不可更改调用顺序
3. 循环次数应当从0开始完整经过一段循环，不应该中途退出

**注意：永远不要调用除了以上五个函数之外的函数**
