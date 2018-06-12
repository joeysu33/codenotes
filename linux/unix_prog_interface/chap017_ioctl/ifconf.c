/*!
 * 使用ioctl来获取当前网络接口的配置
 * 获取接口的相关信息
 * 标志位
 * 索引
 * 广播地址
 * MTU等
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
