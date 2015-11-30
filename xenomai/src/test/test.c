#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#include <native/task.h>
#include <native/timer.h>

#include "sistema.h"
#include "test/test.h"

int mover(void * src_start, long src_size, void * dst_start, long dst_size)
{
	if (src_size != dst_size)
		return -1;

	/*printf("\n\nDireccion src_start: %p", src_start);
	printf("\nDireccion src_size: %ld", src_size);
	printf("\nDireccion dst_start: %p", dst_start);
	printf("\nDireccion dst_size: %ld", dst_size);*/

	const unsigned int *vectors_src = src_start;
	unsigned int *vectors_dst;

	vectors_dst = (unsigned int *)dst_start;

	long count = 0;

	while(count < src_size ) {
		*vectors_dst++ = *vectors_src++;
		count += sizeof(int);
	}

	return 0;
}

int copyData(void * src_start, long src_size, void * dst_start, long dst_size, const char* fileName)
{
	int count = 1;

	struct timeval tval_before, tval_after, tval_result;

	FILE *f = fopen(fileName, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}

	while(count <= 100) {
		gettimeofday(&tval_before, NULL);
		int ret = mover(src_start, src_size,
				dst_start, dst_size);

		gettimeofday(&tval_after, NULL);

		long int sec = (long int)tval_after.tv_sec - (long int)tval_before.tv_sec;
		long int usec = abs((long int)tval_after.tv_usec - (long int)tval_before.tv_usec);

		if(usec <= 0){
			printf("before_sec: %ld, before_usec: %ld\n",
				(long int)tval_before.tv_sec,
				(long int)tval_before.tv_usec);

			printf("after_sec: %ld, after_usec: %ld\n",
				(long int)tval_after.tv_sec,
				(long int)tval_after.tv_usec);
		}

		fprintf(f, "%d, %ld.%06ld\n",
			count,
			sec,
			usec);
		
		count++;
	}
	fclose(f);
	
	return 0;
}

void test(void *arg)
{
	RTIME now, previous;
	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, test_task_period);
	previous = rt_timer_read();
	while (1) {
		rt_task_wait_period(NULL);

		now = rt_timer_read();
		printf("Time since last turn: %ld.%06ld ms\n",
			(long)(now - previous) / 1000000,
			(long)(now - previous) % 1000000);
		previous = now;

		//Mover datos de diferentes tamaños (4K, 16K, 64K, 256K, 1M, 4M y 16M)

		static s_4k aK4, bK4;
		copyData(&aK4, 4*K, &bK4, 4*K, "out/4K.txt");

		static s_16k aK16, bK16;
		copyData(&aK16, 16*K, &bK16, 16*K, "out/16K.txt");

		static s_64k aK64, bK64;
		copyData(&aK64, 64*K, &bK64, 64*K, "out/64K.txt");

		static s_256k aK256, bK256;
		copyData(&aK256, 256*K, &bK256, 256*K, "out/256K.txt");

		static MegaByte aM1, bM1;
		copyData(&aM1, M, &bM1, M, "out/1M.txt");

		static s_4m aM4, bM4;
		copyData(&aM4, 4*M, &bM4, 4*M, "out/4M.txt");

		static s_16m aM16, bM16;
		copyData(&aM16, 16*M, &bM16, 16*M, "out/16M.txt");

		exit(0);
	}
}