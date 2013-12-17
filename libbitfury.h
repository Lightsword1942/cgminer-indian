/**
 * libbitfury.h - library for Bitfury chip/board
 *
 * Copyright (c) 2013 bitfury
 * Copyright (c) 2013 legkodymov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
**/

#ifndef __LIBBITFURY_H__
#define __LIBBITFURY_H__

#include "miner.h"

#define BITFURY_STAT_N 1024
#define MAX_SLOTS 4

struct bitfury_payload {
	unsigned char midstate[32];
	unsigned int junk[8];
	unsigned m7;
	unsigned ntime;
	unsigned nbits;
	unsigned nnonce;
};
struct bitfury_work {
	struct work * work;
	int results_n;
	int results_sent;
	struct bitfury_payload payload;
	unsigned int results[64];
};
struct bitfury_device {
	unsigned char osc6_bits;
	unsigned newbuf[17];
	unsigned oldbuf[17];
	int job_switched;

	struct bitfury_work bfwork;
	struct bitfury_work obfwork;
	struct bitfury_work o2bfwork;
	time_t stat_ts[BITFURY_STAT_N];
	unsigned int stat_counter;
	int rate; //per msec
	int osc_slow;
	int osc_fast;
	int req1_done, req2_done;
	double mhz;
	double ns;
	unsigned slot;
	unsigned fasync;
	unsigned nonces_found;
	unsigned nonce_errors;
	int chip_buf_offset;
};

int libbitfury_readHashData(unsigned int *res);
int libbitfury_sendHashData(struct bitfury_device *bf, int chip_n);
void work_to_payload(struct bitfury_payload *p, struct work *w);
struct timespec t_diff(struct timespec start, struct timespec end);
int libbitfury_detectChips(struct bitfury_device *devices);
int libbitfury_shutdownChips(struct bitfury_device *devices, int chip_n);


#endif /* __LIBBITFURY_H__ */
