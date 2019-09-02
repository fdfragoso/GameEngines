//! Profiler
/*! Keeps track of physical and virtual memory usage in KBytes. */
/*! Records the highest value of memory reached. */
/*! Values can be seen from GUI in debug mode */
/*! We are not sure if Profiler works on MAC. */

#ifndef PROFILER_H
#define PROFILER_H

#include <memory>
#include <string>
#include <vector>
#include "GameObject.hpp"

#ifdef __APPLE__
#include<mach/mach.h>
#elif defined _WIN32
#include "windows.h"
#include "psapi.h"
#endif


class Profiler {
public:
	/**
	* Returns the current virtual memory usage by the game in KBytes.
    * @returns {SIZE_T}
	**/
	SIZE_T getVirtualMemUse();
	/**
	* Returns the current physical memory usage by the game in KBytes.
	* @returns {SIZE_T}
	**/
	SIZE_T getPhysicalMemUse();
	SIZE_T maxVirtualMem = 0;
	SIZE_T maxPhysicalMem = 0;

private:
#ifdef __APPLE__
	struct task_basic_info t_info;
#elif defined _WIN32
	PROCESS_MEMORY_COUNTERS_EX pmc;
#endif
};

#endif