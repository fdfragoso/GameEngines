//! LeakDetector
/*! We overload operators to know jow many times something was created or destroyed */
/*! After several tests, we decided to make a margin of 5 "memory leaks" */
/*! These leaks are not considered memory leaks, the memory will be free at the end of the program */
/*! We could not find a way to do it in runtime */
/*! For Example: */
/*! Using SRE::Texture::createFromFile() creates one memory leak per call */
/*! Using box2d CreateFixture() creates 3 memory leaks */


#ifndef LEAK_DETECTOR_HPP
#define LEAK_DETECTOR_HPP
#include <new>
#include <cstdlib>
#include <iostream>

int start_number_of_allocs = 0;
int number_of_allocs = 0;
int memoryMargin = 5;

void* operator new(std::size_t size) throw(std::bad_alloc) {
	++number_of_allocs;
	void *p = malloc(size);
	if (!p) throw std::bad_alloc();
	return p;
}

void* operator new  [](std::size_t size) throw(std::bad_alloc) {
	++number_of_allocs;
	void *p = malloc(size);
	if (!p) throw std::bad_alloc();
	return p;
}

void* operator new  [](std::size_t size, const std::nothrow_t&) throw() {
	++number_of_allocs;
	return malloc(size);
}
void* operator new   (std::size_t size, const std::nothrow_t&) throw() {
	++number_of_allocs;
	return malloc(size);
}

void operator delete(void* ptr) throw() { free(ptr); --number_of_allocs; }
void operator delete (void* ptr, const std::nothrow_t&) throw() { free(ptr); --number_of_allocs;}
void operator delete[](void* ptr) throw() { free(ptr); --number_of_allocs; }
void operator delete[](void* ptr, const std::nothrow_t&) throw() { free(ptr); --number_of_allocs; }
/**
* Creates a mark, so changes in allocation will be considered from now on
*/
void markPoint() {
	start_number_of_allocs = number_of_allocs;
}
/*! Compares the current number of allocations with the initial number of allocations */
/*! Prints in console if there are memory leaks */

void checkLeaks() {
	std::cout <<"Initial number of allocations: "<< start_number_of_allocs <<" Final number of allocations: "<< number_of_allocs<<std::endl;
	std::cout << "Memory margin: " << memoryMargin <<std::endl;
	int diff = number_of_allocs - start_number_of_allocs;
	if (diff <= memoryMargin) {
		std::cout << "NO Memory Leaks! :D - Diff: " << diff;
	} else {
		std::cout << "THERE ARE Memory Leaks! D: - Diff: "<< diff << " - Leaks: " << diff - memoryMargin;
	}
}
#endif