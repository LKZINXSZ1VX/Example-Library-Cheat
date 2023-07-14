#include <pthread.h>
#include <jni.h>
#include "KittyMemory/MemoryPatch.h"
#include "KittyMemory/Memory.h"
#include "Substrate/SubstrateHook.h"
#include "Unity/Quaternion.hpp"
#include "Unity/Vector2.hpp"
#include "Unity/Vector3.hpp"
#include "Unity/Unity.h"
#include "hook.h"
#include "Includes/Utils.h"
#include "Unity/obfuscate.h"

#define LOG_TAG OBFUSCATE("LKZINXS Z1")
#define targetLibrary OBFUSCATE("libil2cpp.so")

using namespace std;

//Variable
float _float;
int _int;
bool _bool;

//Hook Fields
void (*hook_example)(void* _thiz);
void _hook_example(void *_thiz)
{
	
	/*float*/ *(float*)((uintptr_t)_thiz + 0x123) = _float; /*value / variable*/
	/*int*/ *(int*)((uintptr_t)_thiz + 0x123) = _int; /*value / variable*/
	/*bool*/ *(bool*)((uintptr_t)_thiz + 0x123) = _bool; /*boolean / variable*/
	
	hook_example(_thiz);
}

//start the thread
void *thread_start(void *) {
	ProcMap2 libMap;
	do {
		libMap = KittyMemory::getLibraryMap(targetLibrary);
		sleep(1);
		
	} while(!libMap.isValid());

	if(libMap.isValid()){
		
		//Example get offset
		MSHookFunction((void *)getRealOffset(targetLibrary, 0x123456), (void *)_hook_example, (void **)&hook_example);
		
	}
    return NULL;
}

extern "C"

void __attribute__ ((constructor)) start_thread() {
	
	pthread_t ptid1;
	pthread_create(&ptid1, nullptr, thread_start, nullptr);

}
