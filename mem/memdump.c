
#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("Memory Dump", 0x1000, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

int nkThreadSuspend(SceUID thId);
int nkThreadResume(SceUID thId);

/***************************************

メモリをファイルに保存

****************************************/
void dump(void){
	static int count = 0;
	char file[20];
	
	sprintf(file, "ms0:/mem%02d.bin", count);
	
	int fd = sceIoOpen(file, PSP_O_CREAT|PSP_O_WRONLY|PSP_O_TRUNC, 0777);
	if(fd < 0) return;
	
	sceIoWrite(fd, (void*) 0x08800000, 24*1024*1024);
	sceIoClose(fd);
	count++;
/*
	int handle = sceIoOpen("ms0:/boot.BIN", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	sceIoWrite(handle, (void*) 0xBFC00000 , 0x100000);
	sceIoClose(handle);
	handle = sceIoOpen("ms0:/kmem.BIN", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	sceIoWrite(handle, (void*) 0x88000000 , 0x400000);
	sceIoClose(handle);
	handle = sceIoOpen("ms0:/klib.BIN", PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	sceIoWrite(handle, (void*) 0x88800000 , 0x100000);
	sceIoClose(handle);
*/
}

/***************************************

メインスレッド

****************************************/
int mainThread (SceSize args, void *argp){
	unsigned int paddata_old = 0;
	SceCtrlData paddata;

	while(1){
		sceCtrlPeekBufferPositive(&paddata, 1);
		
		if(paddata.Buttons != paddata_old){
			//メモリダンプ
			if((paddata.Buttons & (PSP_CTRL_RTRIGGER | 0x00100000)) == (PSP_CTRL_RTRIGGER | 0x00100000)){

				nkThreadSuspend(sceKernelGetThreadId());

				dump();
				
				nkThreadResume(sceKernelGetThreadId());
			}
		}
		paddata_old = paddata.Buttons;
		sceKernelDelayThread(10000);
	}
	return 0;
}

/***************************************

モジュールスタート

****************************************/
SceUID thid;
int module_start (SceSize args, void *argp)
{

	thid = sceKernelCreateThread("memdump", mainThread, 0x18, 0x800, 0, NULL);
	if (thid >= 0) sceKernelStartThread(thid, args, argp);

	return 0;
}

/***************************************

モジュールストップ

****************************************/
int module_stop (void)
{
	sceKernelDeleteThread(thid);
	return 0;
}
