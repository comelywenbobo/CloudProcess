# CloudProcess

CloudProcess是一个基于PCL（Point Cloud Library）的C++项目，用于将点云数据按Y坐标分割成多个帧。

## 功能描述

该项目主要实现以下功能：
- 加载PLY格式的点云文件
- 计算点云的Y坐标范围
- 将点云按Y坐标均匀分割成指定数量的帧
- 将分割后的每一帧保存为独立的PLY文件

## 依赖项

- C++ 11或更高版本
- PCL (Point Cloud Library) 1.8或更高版本
- CMake 3.10或更高版本
- Visual Studio 2022 (Windows环境)

## 构建说明

### Windows环境

1. 确保已安装PCL库和Visual Studio 2022
2. 克隆或下载项目到本地
3. 打开CMakePresets.json或使用CMake GUI配置项目
4. 选择合适的构建配置（Debug/Release）
5. 生成Visual Studio解决方案
6. 在Visual Studio中打开并构建项目

### 命令行构建

```bash
cd out/build
cmake ..
cmake --build . --config Release
```

## 使用方法

构建完成后，可通过以下方式运行程序：

```bash
CloudProcess.exe <input_ply_file>
```

### 参数说明

- `<input_ply_file>`: 输入的PLY格式点云文件路径

## 示例

```bash
CloudProcess.exe input.ply
```

执行上述命令后，程序将：
1. 加载input.ply文件
2. 将点云按Y坐标分割成10帧
3. 生成frame_0.ply到frame_9.ply共10个文件

## 程序输出

程序运行时会输出以下信息：
- 加载的点云总点数
- Y坐标的范围
- 每帧的高度
- 每一帧包含的点数
- 保存的文件名和点数

## 代码结构

- `main.cpp`: 主程序文件，包含所有功能实现

### 主要函数

1. `splitPointCloudByY`: 将点云按Y坐标分割成指定数量的帧
2. `savePointClouds`: 保存分割后的点云帧

## 输出文件

程序执行后会生成一系列PLY格式的点云文件，命名格式为：
```
frame_0.ply
frame_1.ply
...
frame_9.ply
```

## 注意事项

- 确保输入的点云文件格式为PLY
- 程序默认分割为10帧，可在代码中修改`numFrames`变量调整
- 分割是基于Y坐标的均匀分割，确保点云在Y方向上有足够的分布

## 许可证

本项目采用MIT许可证。