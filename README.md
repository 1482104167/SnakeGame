# SnakeGame 贪吃蛇

一个使用 **C++23** 编写的 Windows 控制台贪吃蛇游戏，基于 **Visual Studio** 构建。

项目采用模块化设计，逻辑、渲染、输入、数据各自独立，没有使用任何第三方库，仅依赖 C++ 标准库与 Win32 控制台 API。

![language](https://img.shields.io/badge/language-C%2B%2B23-blue)
![platform](https://img.shields.io/badge/platform-Windows-lightgrey)
![ide](https://img.shields.io/badge/IDE-Visual%20Studio-purple)

---

## 游戏特性

- **页面式流程**：进入页 → 开始页 → 游玩页 → 结束页，另有独立的设置页
- **动态加速**：每吃到一个食物速度提升一档，上限 20 档，越玩越快
- **计分系统**：每个食物 +5 分
- **双食物机制**：可选开启"多食物"，蛇长达到一定程度后有概率刷新红色食物
- **胜负判定**：撞墙或撞到自己蛇身即失败；蛇体填满全部内部格子即获胜
- **逐行动画**：地图绘制与文字输出带逐行延迟，界面呈现更平滑
- **中文界面**，支持彩色文本（颜色通过 Win32 控制台属性实现）

### 可调设置

在设置页（进入后按 `R`）可切换以下四项：

| 设置项 | 默认 | 说明 |
|---|---|---|
| 多食物 | 开 | 蛇长超过初始长度 10 节后，有概率额外生成红色食物 |
| 无界模式 | 关 | 从一侧穿出后从对侧进入，无墙体阻挡 |
| 允许暂停 | 关 | 开启后可用空格暂停/继续 |
| 无敌模式 | 关 | 撞墙或撞到蛇身不会死亡 |

---

## 操作方式

游戏内所有按键均**不区分大小写**。

### 进入页

| 按键 | 作用 |
|---|---|
| `E` | 进入开始页 |
| `R` | 打开设置页 |
| `Q` | 请求退出，再按一次 `Q` 确认；按其他键取消 |
| `空格` 连按两次 | 清屏并重绘当前页 |

### 开始页

| 按键 | 作用 |
|---|---|
| `S` | 开始游戏 |
| `Q` | 返回进入页 |

### 游玩中

| 按键 | 作用 |
|---|---|
| `W` `A` `S` `D` | 上 / 左 / 下 / 右 |
| `空格` | 暂停 / 继续（需在设置中开启"允许暂停"） |
| `Esc` | 结束本局并退出到进入页 |

> 转向有输入缓冲：最多缓存 3 个有效方向，连续快速转向不会丢操作，同时会自动拦截反向与重复输入。

### 结束页

| 按键 | 作用 |
|---|---|
| `E` | 再来一局（回到开始页） |
| `Q` | 返回进入页 |

### 设置页

| 按键 | 作用 |
|---|---|
| `W` / `S` | 上下移动光标 |
| `A` / `D` | 切换当前项的开 / 关 |
| `Q` | 返回进入页 |

---

## 编译与运行

### 环境要求

| 项目 | 要求 |
|---|---|
| 操作系统 | Windows 10 / 11 |
| IDE | Visual Studio（需支持 C++23 与 MSVC v145 工具集，即较新版本的 VS） |
| C++ 标准 | **C++23**（项目使用 `import std;` 标准库模块） |
| 关键编译选项 | `BuildStlModules` = true、`ConformanceMode` = true、`TreatWarningAsError` = true |
| 平台 | x64（推荐）或 Win32，Debug / Release 均可 |

> **注意**：项目源码使用 `import std;`，因此编译器必须开启 **C++23 标准库模块（Build STL Modules）** 支持。若你的 Visual Studio 版本较旧，可能在编译时报找不到模块 `std`。

### 编译步骤

1. 克隆仓库：

   ```bash
   git clone https://github.com/1482104167/SnakeGame.git
   ```

2. 双击 `SnakeGame.slnx`，用 Visual Studio 打开解决方案
3. 选择配置（推荐 `x64` + `Debug` 或 `Release`）
4. 按 `Ctrl + Shift + B` 生成，或 `F5` 直接生成并运行

也可以直接用 MSBuild 命令行构建：

```powershell
msbuild SnakeGame.slnx /p:Configuration=Release /p:Platform=x64
```

### 运行注意

- 游戏为**控制台程序**，请在**未满屏的窗口化控制台**中运行，窗口宽度需容纳 47 列左右，否则界面会出现换行错位
- 建议通过 Visual Studio 直接运行（`F5`），或运行生成目录下的 `SnakeGame.exe`
- 窗口过小时，地图绘制会因自动换行而错乱；可放大窗口后按 `空格` 连按两次重绘

---

## 代码结构

```
SnakeGame/
├── main.cpp              程序入口，创建并运行 Game
├── Game.cpp / .h         页面流程与主循环（进入/开始/游玩/设置/结束）
├── GameEngine.cpp / .h   游戏规则核心：每帧更新、碰撞判定、吃食物、命令处理
├── Snake.cpp / .h        蛇体数据结构、方向缓冲与转向合法性判定
├── Map.cpp / .h          地图网格、单元格类型、食物随机生成
├── Info.cpp / .h         分数、速度、游戏状态
├── Settings.cpp / .h     四项可调设置
├── GameCommand.h         按键 → 游戏命令 的映射
├── Renderer.cpp / .h     全部界面绘制与逐行动画
├── Console.cpp / .h      控制台封装：清屏、光标、颜色、窗口尺寸
├── Input.cpp / .h        键盘输入：非阻塞读取、阻塞读取、回退、清空缓冲
├── SysTimerRes.cpp / .h  提升系统计时器分辨率，使帧间隔更精确
├── Point.h               二维坐标模板（含逐分量算术运算）
└── Utils.h               随机数工具
```

### 设计要点

- **数据与表现分离**：`GameEngine` 只负责规则与状态，`Renderer` 只负责画，二者通过 `Map` / `Info` / `Settings` 交互
- **命令模式**：按键先经 `toGameCommand()` 转成 `GameCommand` 枚举，再由引擎统一处理，输入层与逻辑层解耦
- **方向缓冲队列**：解决"快速连续转向导致丢输入"的经典问题，并拦截反向自杀式输入
- **帧时间补偿**：主循环用 `steady_clock` 累加固定步长并做二级检测，避免长时间卡顿后出现暴力追赶，同时消除累计误差
- **高精度计时**：通过 `timeBeginPeriod` / `timeEndPeriod`（RAII 封装）提高 `sleep_for` 精度，让移动节奏稳定
- **不可拷贝的数据类型**：`Map` / `Snake` / `Info` / `Settings` 均为不可拷贝、可移动，避免意外的大对象复制

---

## 可调整的参数

想改动玩法，可以直接修改以下常量（均有注释）：

| 参数 | 位置 | 当前值 | 含义 |
|---|---|---|---|
| `cols` / `rows` | `Map.h` | 24 / 20 | 地图列数 / 行数 |
| `initSpeed` | `Info.h` | 4125 | 初始速度（每秒移动格数 × 1000，即约 4.1 格/秒） |
| `speedIncrement` | `Info.h` | 75 | 每吃一个食物提升的速度 |
| `increaseSpeedMaxTimes` | `Info.h` | 20 | 提速次数上限 |
| `scoreIncrement` | `Info.h` | 5 | 每个食物的分数 |
| `initLength` | `Snake.h` | 3 | 蛇的初始长度 |
| `pendingDirsMaxSize` | `Snake.h` | 3 | 转向缓冲队列长度 |
| `windowWidth` | `Renderer.h` | 47 | 界面统一宽度（居中文本用） |
| `mapDelay` / `textDelay` | `Renderer.h` | 13ms / 48ms | 地图 / 文字的逐行绘制延迟 |

---

## 已知限制

- 仅支持 Windows（依赖 `<Windows.h>` 与 `<conio.h>`）
- 界面为固定 24 × 20 网格的字符画，不支持自定义窗口尺寸适配
- 无存档、无排行榜功能

---

## 许可

本项目暂未指定开源许可证。
