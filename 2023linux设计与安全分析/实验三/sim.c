#include <string.h>  
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <linux/input.h>  
#include <linux/uinput.h>  
#include <stdio.h>  
#include <sys/time.h>  
#include <sys/types.h>  
#include <unistd.h>  
void simulate_key(int fd, int kval)  
{  
    // 定义一个用于存储输入事件的结构体变量
    struct input_event event;  
    // 设置事件类型为键盘事件
    event.type = EV_KEY;  
    // 设置事件值为1，表示键被按下
    event.value = 1;  
    // 根据传入的键盘码设置事件码
    event.code = kval;  

    // 获取当前时间并存储在事件的时间戳中
    gettimeofday(&event.time, 0);  
    // 通过write函数将事件写入文件描述符所代表的设备文件中，模拟键盘按下操作
    write(fd, &event, sizeof(event));  

    // 设置事件类型为同步事件
    event.type = EV_SYN;  
    // 设置事件码为SYN_REPORT，表示发送同步报告
    event.code = SYN_REPORT;  
    // 设置事件值为0
    event.value = 0;  
    // 通过write函数将事件写入设备文件，完成按下操作的确认
    write(fd, &event, sizeof(event));  

    // 将事件的结构体清零，以便进行后续操作的设置
    memset(&event, 0, sizeof(event));  
    // 再次获取当前时间并存储在事件的时间戳中
    gettimeofday(&event.time, NULL);  
    // 设置事件类型为键盘事件
    event.type = EV_KEY;  
    // 根据传入的键盘码设置事件码，表示键被释放
    event.code = kval;  
    // 设置事件值为0
    event.value = 0;  
    // 通过write函数将事件写入设备文件，模拟键盘释放操作
    write(fd, &event, sizeof(event));  
    // 再次设置事件类型为同步事件
    event.type = EV_SYN;  
    // 设置事件码为SYN_REPORT，表示发送同步报告
    event.code = SYN_REPORT;  
    // 设置事件值为0
    event.value = 0;  
    // 通过write函数将事件写入设备文件，完成释放操作的确认
    write(fd, &event, sizeof(event));  
}

int main()  
{  
    int fd_kbd;   
    int fd_mouse;   
    fd_kbd = open("/dev/input/event1",O_RDWR);  
    if(fd_kbd<=0){  
        printf("error open keyboard:\n");  
        return -1;  
    }    
    int i = 0;  
    for(i=0; i< 10; i++)  
    {  
        simulate_key(fd_kbd, KEY_A + i);  
        sleep(1);  
    }  
    close(fd_kbd);  
}  
