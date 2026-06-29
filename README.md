# StartupApp

Ubuntu22.04/20.04 桌面应用生成器。
可设置应用自启动等功能
![示例图片](doc/example.png)
## 功能

- 设置应用名
- 设置一个可以在终端中运行的命令或脚本
- 可选选择应用图片
- 可选生成开机自启动入口

生成位置：

- 应用入口：`~/.local/share/applications/<app-id>.desktop`
- 图标：`~/.local/share/icons/<app-id>.<ext>`
- 自启动：`~/.config/autostart/<app-id>.desktop`

生成的应用会自动打开 `gnome-terminal`，再用交互式 `bash` 执行用户填写的命令或脚本。这样会加载 `~/.bashrc`，适合依赖 ROS、conda 等终端环境的脚本。命令结束后会保留终端窗口，方便查看输出。

## 编译

```bash
cmake -S . -B build
cmake --build build
```

## 运行

```bash
./build/StartupApp
```
