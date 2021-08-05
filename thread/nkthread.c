
#include <pspthreadman.h>
#include <pspsysmem.h>

PSP_MODULE_INFO("nkThread", 0x1000, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

#define MAX_THREAD	64

typedef struct THREAD{
	int count;
	SceUID pThread;
	SceUID *Thread;
} THREAD;

THREAD bufStart, bufNow;

/***************************************

���W���[���X�^�[�g

****************************************/
int module_start (SceSize args, void *argp)
{
	bufStart.pThread = sceKernelAllocPartitionMemory(2, "th", 0, MAX_THREAD*sizeof(SceUID), NULL);
	bufStart.Thread = (SceUID*)sceKernelGetBlockHeadAddr(bufStart.pThread);

	//�J�n���̃X���b�h�ꗗ�̎擾
	sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, (bufStart.Thread), MAX_THREAD, &(bufStart.count));

	memset(&bufNow, 0, sizeof(THREAD));

	return 0;
}


/***************************************

�X���b�h���ꎞ��~

****************************************/
int nkThreadSuspend(SceUID thId){

	int i, j;
	SceUID myThread;

	if(bufNow.pThread != 0) return 1;

	bufNow.pThread = sceKernelAllocPartitionMemory(2, "th", 0, MAX_THREAD*sizeof(SceUID), NULL);
	bufNow.Thread = (SceUID*)sceKernelGetBlockHeadAddr(bufNow.pThread);

	//���݂̃X���b�h�ꗗ�̎擾
	sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, (bufNow.Thread), MAX_THREAD, &(bufNow.count));
	myThread = sceKernelGetThreadId();

	for(i = 0; i < bufNow.count; i++){
		unsigned char match = 0;
		SceUID tmp_thid = bufNow.Thread[i];
		
		for(j = 0; j < bufStart.count; j++){
			if((tmp_thid == bufStart.Thread[j]) || (tmp_thid == thId) || (tmp_thid == myThread)){
				match = 1;
				j = bufStart.count;
			}
		}
	//	if(bufStart.count == 0) match = 1;
		if(match == 0){
			sceKernelSuspendThread(tmp_thid);
		}
	}

	return 0;
}

/***************************************

�X���b�h���ĊJ

****************************************/
int nkThreadResume(SceUID thId){

	int i, j;
	SceUID myThread;

	if(bufNow.pThread == 0) return 1;

	//���݂̃X���b�h�ꗗ�̎擾
	myThread = sceKernelGetThreadId();

	for(i = 0; i < bufNow.count; i++){
		unsigned char match = 0;
		SceUID tmp_thid = bufNow.Thread[i];
		
		for(j = 0; j < bufStart.count; j++){
			if((tmp_thid == bufStart.Thread[j]) || (tmp_thid == thId) || (tmp_thid == myThread)){
				match = 1;
				j = bufStart.count;
			}
		}
	//	if(bufStart.count == 0) match = 1;
		if(match == 0){
			sceKernelResumeThread(tmp_thid);
		}
	}
	
	sceKernelFreePartitionMemory(bufNow.pThread);
	memset(&bufNow, 0, sizeof(THREAD));

	return 0;
}

/***************************************

���W���[���X�g�b�v

****************************************/
int module_stop (SceSize args, void *argp)
{
	sceKernelFreePartitionMemory(bufStart.pThread);
	sceKernelFreePartitionMemory(bufNow.pThread);

	return 0;
}
