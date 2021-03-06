/*
   YOUR NAME HERE
CSE 351 - Winter 2013
Lab 4 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 262144 bytes
    associativity = 1
mystery1:
    block size = 8 bytes
    cache size = 16384 bytes
    associativity = 4
mystery2:
    block size = 16 bytes
    cache size = 65536 bytes
    associativity = 16
mystery3:
    block size = 2 bytes
    cache size = 131072 bytes
    associativity = 2
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
	int block_counter = 0;
	flush_cache();
	access_cache(0);

	for(block_counter = 0; access_cache(block_counter);block_counter++)
	{
	}

  	return block_counter;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {

	int possible_cache_size;
	int tmp = 0;
	flush_cache();

	for(possible_cache_size = 1; 1 ;possible_cache_size<<=1)
	{
		for(tmp = 0;tmp <= possible_cache_size;tmp += block_size)
		{
			access_cache(tmp);
		}

		if(!access_cache(0))
		{
			break;
		}
	}

	return possible_cache_size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {

	int tmp = cache_size;
	int addr = 0;
	
	flush_cache();

	for(addr = 0; 1; addr += cache_size)
	{
		access_cache(addr);
		for(tmp = 0;tmp <= addr;tmp += cache_size)
		{
			if(!access_cache(tmp))
			{
				return addr/cache_size;
			}
		}
	}
	return -1;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
