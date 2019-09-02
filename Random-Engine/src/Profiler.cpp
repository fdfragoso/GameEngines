#include "Profiler.hpp"
#include <iostream>

using namespace std;

SIZE_T Profiler::getVirtualMemUse() {
	SIZE_T aux;
#ifdef __APPLE__
	mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
	if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
		(task_info_t)&info, &infoCount) != KERN_SUCCESS) {
		aux = 0;
	}
	aux = info.virtual_size >> 10;
#elif defined _WIN32
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	aux = pmc.PrivateUsage >> 10;
#endif
	maxVirtualMem = aux > maxVirtualMem ? aux : maxVirtualMem;
	return aux;
}

SIZE_T Profiler::getPhysicalMemUse() {
	SIZE_T aux;
#ifdef __APPLE__
	mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
	if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
		(task_info_t)&info, &infoCount) != KERN_SUCCESS) {
		aux = 0;
	}
	aux = info.resident_size >> 10;

	struct rusage rusage;
	getrusage(RUSAGE_SELF, &rusage);
	maxPhysicalMem = rusage.ru_maxrss >> 10;
#elif defined _WIN32
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	aux = pmc.WorkingSetSize >> 10;
	maxPhysicalMem = pmc.PeakWorkingSetSize >> 10;
#endif
	return aux;
}
