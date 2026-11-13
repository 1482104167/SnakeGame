# SnakeGame 贪吃蛇

一个使用 **C++23** 编写的 Windows 控制台贪吃蛇游戏，基于 **Visual Studio** 构建。

项目采用模块化设计，逻辑、渲染、输入、数据各自独立，没有使用任何第三方库，仅依赖 C++ 标准库、Win32 控制台 API 与 MSVC 运行库。

![language](https://img.shields.io/badge/language-C%2B%2B23-blue)
![platform](https://img.shields.io/badge/platform-Windows-lightgrey)
![ide](https://img.shields.io/badge/IDE-Visual%20Studio-purple)

---

## 游戏特性

- **页面式流程**：`LobbyPage`（大厅页）↔ `SettingsPage`（设置页）；`LobbyPage` → `PlayPage`（同一页面内包含准备/开始、游玩、结束信息）。游玩结束后可 `E` 重新开始（重新进入 `PlayPage` 准备界面）或 `Q` 返回大厅页
- **动态加速**：每吃到一个食物速度提升一档，最多提升 15 次，越玩越快
- **计分系统**：每个食物 +5 分
- **红色食物机制**：默认允许生成红色食物；蛇长达到初始长度 +15 节（即长度 ≥18）后，开始按计数器阈值随机间隔额外生成红色食物，首次达到长度门槛时会立即生成，可在设置页禁止。红色食物与普通食物一样 +5 分并提升速度，且地图上可同时存在多个红色食物
- **胜负判定**：默认撞墙或撞到蛇身即失败；无敌模式可免除；蛇体填满全部内部格子（22×18 = 396 格）即获胜
- **逐行动画**：地图墙体与文字输出带逐行延迟，界面呈现更平滑
- **中文界面**，支持彩色文本（颜色通过 Win32 控制台属性实现）
- **设置跨局保留**：当前代码中 `GameEngine::reset()` 不会重置 `Settings`，设置项在程序运行期间保留，在设置页修改后对后续游戏生效

### 可调设置

在设置页（进入后按 `R`）可切换以下四项。设置页显示的名称与默认值如下：

| 设置项 | 默认 | 说明 |
|---|---|---|
| 禁止生成红色食物 | 关 | 关闭时允许红色食物；开启后不再生成红色食物。红色食物在蛇长达到 18 节后开始按计数器阈值刷新 |
| 无界模式（穿墙回绕） | 关 | 从一侧边界穿出后从对侧内部进入，无边界墙体阻挡 |
| 允许游戏中暂停 | 关 | 开启后可用空格暂停/继续 |
| 无敌模式（谨慎开启） | 关 | 撞墙或撞到蛇身不会死亡；但不会穿越障碍，仍需转向离开 |

> 设置页中的“禁止生成红色食物”默认为 OFF，表示允许多食物/红色食物机制。

---

## 操作方式

游戏内所有按键均**不区分大小写**。

### 大厅页

| 按键 | 作用 |
|---|---|
| `E` | 进入 `PlayPage` 准备界面（开始页） |
| `R` | 打开设置页 |
| `Q` | 请求退出，再按一次 `Q` 确认；按其他键取消 |
| `空格` 连按两次 | 清屏并重绘大厅页（仅大厅页支持该快捷键） |

### 开始页（`PlayPage` 准备状态）

`E` 进入后，`PlayPage::onEnter` 会重置游戏、绘制地图并显示开始提示。

| 按键 | 作用 |
|---|---|
| `S` | 开始游戏 |
| `Q` | 返回大厅页 |

### 游玩中

| 按键 | 作用 |
|---|---|
| `W` `A` `S` `D` | 上 / 左 / 下 / 右 |
| `空格` | 暂停 / 继续（需在设置中开启“允许游戏中暂停”） |
| `Esc` | 结束本局并退出到大厅页（不显示结束信息） |

> 转向有输入缓冲：最多缓存 3 个有效方向，连续快速转向不会丢操作，同时会自动拦截反向与重复输入。暂停后继续时会清空暂停前缓存的待处理方向。

### 结束页

结束信息显示在 `PlayPage` 内。

| 按键 | 作用 |
|---|---|
| `E` | 回到 `PlayPage` 准备界面（开始页），再来一局 |
| `Q` | 返回大厅页 |

### 设置页

| 按键 | 作用 |
|---|---|
| `W` / `S` | 上下移动光标 |
| `A` / `D` | 切换当前项的开 / 关 |
| `Q` | 返回大厅页 |

---

## 编译与运行

### 环境要求

| 项目 | 要求 |
|---|---|
| 操作系统 | Windows 10 / 11 |
| IDE | Visual Studio（需支持 C++23 与 `import std;` 标准库模块；以项目实际工具集配置为准） |
| C++ 标准 | **C++23**（项目使用 `import std;` 标准库模块） |
| 关键编译选项 | `BuildStlModules` = true、`ConformanceMode` = true、`TreatWarningAsError` = true |
| 平台 | x64（推荐）或 Win32，Debug / Release 均可 |

> **注意**：项目源码使用 `import std;`，因此编译器必须开启 **C++23 标准库模块（Build STL Modules）** 支持。若 Visual Studio 版本较旧，可能在编译时报找不到模块 `std`。

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

- 游戏为**控制台程序**，请在**未满屏的窗口化控制台**中运行
- 窗口宽度需容纳约 48 列，高度约 24 行以上，否则界面会出现换行错位
- 建议通过 Visual Studio 直接运行（`F5`），或运行生成目录下的 `SnakeGame.exe`
- 窗口过小时，地图绘制会因自动换行而错乱；可返回大厅页后按空格连按两次清屏重绘，或重启程序

---

## 代码结构

```text
SnakeGame/
├── main.cpp              程序入口：设置控制台与计时器精度，驱动页面循环
├── PageBase.h            页面基类与 GameContext 上下文依赖
├── LobbyPage.cpp / .h    大厅页：进入游戏、设置、退出确认、空格双按刷新
├── PlayPage.cpp / .h     开始/游玩/结束页：准备界面、游玩主循环、结束信息
├── SettingsPage.cpp / .h 设置页：四项开关
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

- **页面驱动**：`main()` 持有一个 `std::unique_ptr<PageBase>`，循环调用 `PageBase::run()` 并根据返回值切换到下一页面；返回 `nullptr` 时退出
- **数据与表现分离**：`GameEngine` 只负责规则与状态，`Renderer` 只负责绘制，二者通过 `Map` / `Info` / `Settings` 交互
- **命令模式**：游玩中的按键先经 `toGameCommand()` 转成 `GameCommand` 枚举，再由引擎统一处理，输入层与逻辑层解耦
- **方向缓冲队列**：解决“快速连续转向导致丢输入”的经典问题，并拦截反向自杀式输入
- **帧时间补偿**：`PlayPage::mainLoop` 使用 `steady_clock`，按当前速度计算 `interval`；每次逻辑更新执行 `lastUpdate += interval` 以消除累计误差，若落后超过一个 `interval` 则跳过本帧渲染，优先保证游戏逻辑继续推进
- **高精度计时**：通过 `timeBeginPeriod` / `timeEndPeriod`（RAII 封装）提高 `sleep_for` 精度，让移动节奏稳定
- **输入轮询与主循环同线程**：游玩时主循环每 5ms 非阻塞轮询 `Input::pullKey()`，将按键转为 `GameCommand` 后调用 `GameEngine::handleCommand()`；方向队列和游戏状态均由主线程访问，没有独立输入线程
- **设置保留**：`GameEngine::reset()` 不重置 `Settings`，设置项在程序运行期间保留，修改后对后续游戏生效

---

## 可调整的参数

想改动玩法，可以直接修改以下常量（均有注释）：

| 参数 | 位置 | 当前值 | 含义 |
|---|---|---|---|
| `cols` / `rows` | `Map.h` | 24 / 20 | 地图列数 / 行数；内部格子数为 22×18 = 396 |
| `initSpeed` | `Info.h` | 3900 | 初始速度（每秒移动格数 × 1000，即约 3.9 格/秒） |
| `speedIncrement` | `Info.h` | 100 | 每吃一个食物提升的速度 |
| `increaseSpeedMaxTimes` | `Info.h` | 15 | 提速次数上限 |
| `maxSpeed` | `Info.h` | 5400 | 最大速度（约 5.4 格/秒，由 `initSpeed + speedIncrement × 15` 计算） |
| `scoreIncrement` | `Info.h` | 5 | 每个食物的分数 |
| `initLength` | `Snake.h` | 3 | 蛇的初始长度 |
| `pendingDirsMaxSize` | `Snake.h` | 3 | 转向缓冲队列长度 |
| `windowWidth` | `Renderer.h` | 47 | 界面统一宽度（居中文本用） |
| `mapDelay` / `textDelay` | `Renderer.h` | 13ms / 48ms | 地图墙体 / 文字的逐行绘制延迟 |
| 红色食物长度门槛 | `GameEngine.cpp` | 15 | 蛇长达到初始长度 + 15（即 ≥18）后开始生成红色食物 |
| 红色食物生成阈值 | `GameEngine.cpp` | 50~150 | 达到长度门槛后，计数器达到该随机阈值生成一个红色食物；首次达到长度门槛时会立即生成 |

---

## 已知限制

- 仅支持 Windows（依赖 `<Windows.h>` 与 `<conio.h>`）
- 界面为固定 24 × 20 网格的字符画，不支持自定义窗口尺寸适配
- 无存档、无排行榜功能
- 控制台窗口过小时会因自动换行导致界面错位；需要约 48 列宽、24 行高以上。大厅页支持空格双按刷新；其他页面可返回大厅页刷新或重启程序

---

## 许可

本项目暂未指定开源许可证。