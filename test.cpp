// #include <iostream>
#include <falcon/memory/range_allocator.hpp>
#include "test/A.h"

using namespace std;

int main(/*int argc, char **argv*/)
{
	std::cout.sync_with_stdio(false);

	constexpr size_t len = 500;
	falcon::byte_t memory[len];
	falcon::range_allocator<A> allocator(memory, &memory[0]+len);
	A * p = allocator.allocate(2);
	allocator.construct<>(p, 2);
	allocator.construct<>(p+1, 4);
	A * p2 = allocator.allocate(3);
	allocator.construct<>(p2, 12);
	allocator.construct<>(p2+1, 14);
	allocator.construct<>(p2+2, 15);
	allocator.destroy<>(p+1);
	allocator.destroy<>(p);
	allocator.deallocate(p,2);
	p = allocator.allocate(2);
	allocator.construct<>(p, 2);
	allocator.construct<>(p+1, 4);
	allocator.destroy<>(p2+2);
	allocator.destroy<>(p2+1);
	allocator.destroy(p2);
	allocator.deallocate(p2,3);
	allocator.destroy<>(p+1);
	allocator.destroy<>(p);
	allocator.deallocate(p,2);
}

