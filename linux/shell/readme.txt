shell的工作方式分为交互模式和非交互模式
非交互模式主要是指使用命令行直接执行，或通过命令脚本cmd.sh
在交互模式下默认启用别名，在非交互模式下默认不启用别名
shell操作的属性设置

shopt -s <opt_name> #启用选项 set
shopt -u <opt_name> #不启用选项 unset
shopt <opt_name>    #查看选项的当前状态

