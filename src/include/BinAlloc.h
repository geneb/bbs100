/*
    bbs100 3.0 WJ105
    Copyright (C) 2005  Walter de Jong <walter@heiho.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
/*
	BinAlloc.h	WJ105
*/

#ifndef BINALLOC_H_WJ105
#define BINALLOC_H_WJ105	1

#include "Types.h"

#define ROUND4(x)									\
	do {											\
		if (((x) & 3) > 0) {						\
			(x) &= ~3;								\
			(x) += 4;								\
		}											\
	} while(0)

#define ST_WORD(x,y,z)								\
	do {											\
		((char *)(x))[(y)] = ((z) >> 8) & 0xff;		\
		((char *)(x))[(y)+1] = (z) & 0xff;			\
	} while(0)

#define LD_WORD(x,y,z)								\
	do {											\
		(z) = (((char *)(x))[(y)] & 0xff) << 8;		\
		(z) |= ((char *)(x))[(y)+1] & 0xff;			\
	} while(0)

#define LD_ADDR(x,y,z)			LD_WORD((x),(y) << 2,(z))
#define LD_SIZE(x,y,z)			LD_WORD((x),((y) << 2)+2,(z))
#define ST_ADDR(x,y,z)			ST_WORD((x),(y) << 2,(z))
#define ST_SIZE(x,y,z)			ST_WORD((x),((y) << 2)+2,(z))
#define ST_ALLOC(x,y,z)			ST_ADDR((x),(y),(0xff00) | ((z) & 0xff))

#define OFFSET_CHUNK_SIZE		sizeof(BinChunk)
#define OFFSET_BYTES_FREE		(OFFSET_CHUNK_SIZE + 2)
#define OFFSET_FREE_LIST(x)		(OFFSET_BYTES_FREE + 2 + ((x) << 1))
#define REAL_ADDRESS(x,y)		((char *)(x) + (((y)+1) << 2))

#define CLEAR_MEM(x,y,z)		memset((char *)(x)+(((y)+1) << 2),0,(z) << 2)

typedef struct BinChunk_tag BinChunk;

struct BinChunk_tag {
	BinChunk *prev, *next;
/*
	This is in here, but it's not in the structure to prevent problems with
	struct padding that is done at compile time

	BinWord chunk_size, bytes_free;
	BinFree free_list[NUM_TYPES];
*/
};

int init_BinAlloc(void);

void *BinMalloc(unsigned long, int);
void BinFree(void *);

#endif	/* BINALLOC_H_WJ105 */

/* EOB */