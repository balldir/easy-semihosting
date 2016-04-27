/*
 * Copyright (c) 2015 Max Asaulov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */

#include "esem.h"

enum {
	ESEM_OPEN = 0x01,
	ESEM_CLOSE = 0x02,
	ESEM_WRITEC = 0x03,
	ESEM_WRITE0 = 0x04,
	ESEM_WRITE = 0x05,
	ESEM_READ = 0x06,
	ESEM_READC = 0x07,
	ESEM_ISERROR = 0x08,
	ESEM_ISTTY = 0x09,
	ESEM_SEEK = 0x0A,
	ESEM_FLEN = 0x0C,
	ESEM_TMPNAM = 0x0D,
	ESEM_REMOVE = 0x0E,
	ESEM_RENAME = 0x0F,
	ESEM_CLOCK = 0x10,
	ESEM_TIME = 0x11,
	ESEM_SYSTEM = 0x12,
	ESEM_ERRNO = 0x13,
	ESEM_GET_CMDLINE = 0x15,
	ESEM_HEAPINFO = 0x16,
	ESEM_ELAPSED = 0x30,
	ESEM_TICKFREQ = 0x31,
};

static inline int semihosting_call (int R0, int R1)
{
  int rc;
  __asm__ volatile ("mov r0, %1\n\t;"
		            "mov r1, %2;\n\t "
                    "bkpt #0xAB\n\t;"
                    "mov %0, r0"
                    : "=r" (rc)
                    : "r" (R0), "r" (R1)
                    : "r0", "r1", "ip", "lr", "memory", "cc");
  return rc;
}

int esem_open(const char *path, open_mode_t mode, unsigned int path_len)
{
	unsigned int args[] = {
		(unsigned int) path,
		(unsigned int) mode,
		(unsigned int) path_len,
	};
	return semihosting_call(ESEM_OPEN, (int) args);
}

int esem_close(int handle)
{
	return semihosting_call(ESEM_CLOSE, (int) &handle);
}

void esem_writec(char symbol)
{
	semihosting_call(ESEM_WRITEC, (int) &symbol);
}

void esem_write0(char *string)
{
	semihosting_call(ESEM_WRITE0, (int) string);
}

int esem_write(int handle, void *buf, unsigned int count)
{
	unsigned int args[] = {
		(unsigned int) handle,
		(unsigned int) buf,
		(unsigned int) count,
	};
	return (count - semihosting_call(ESEM_WRITE, (int) args));
}

int esem_read(int handle, void *buf, unsigned int count)
{
	unsigned int args[] = {
		(unsigned int) handle,
		(unsigned int) buf,
		(unsigned int) count,
	};
	return (count - semihosting_call(ESEM_READ, (int) args));
}

char esem_readc()
{
	return (char) semihosting_call(ESEM_READC, 0);
}

int esem_iserror(int status)
{
	return semihosting_call(ESEM_ISERROR, (int) &status);
}

int esem_istty(int handle)
{
	return semihosting_call(ESEM_ISTTY, (int) &handle);
}

int esem_seek_absolute(int handle, int pos)
{
	unsigned int args[] = {
		(unsigned int) handle,
		(unsigned int) pos,
	};
	return semihosting_call(ESEM_SEEK, (int) args);
}

int esem_flen(int handle)
{
	return semihosting_call(ESEM_FLEN, (int) &handle);
}

int esem_tmpnam(void *buf, int target_indentifier, unsigned int buf_size)
{
	unsigned int args[] = {
		(unsigned int) buf,
		(unsigned int) target_indentifier,
		(unsigned int) buf_size,
	};
	return semihosting_call(ESEM_TMPNAM, (int) args);
}

int esem_remove(char *path, unsigned int path_len)
{
	unsigned int args[] = {
		(unsigned int) path,
		(unsigned int) path_len,
	};
	return semihosting_call(ESEM_REMOVE, (int) args);
}

int esem_rename(char *old_path, unsigned int old_path_len, char *new_path, unsigned int new_path_len)
{
	unsigned int args[] = {
		(unsigned int) old_path,
		(unsigned int) old_path_len,
		(unsigned int) new_path,
		(unsigned int) new_path_len,
	};
	return semihosting_call(ESEM_RENAME, (int) args);
}

int esem_clock()
{
	return semihosting_call(ESEM_CLOCK, 0);
}

unsigned int esem_time()
{
	return (unsigned int)semihosting_call(ESEM_TIME, 0);
}

int esem_system(const char* command,unsigned int length)
{
	unsigned int args[] = {
		(unsigned int) command,
		(unsigned int) length,
	};
	return semihosting_call(ESEM_SYSTEM, (int) args);
}

int esem_errno()
{
	return semihosting_call(ESEM_ERRNO, 0);
}

int esem_get_cmdline(void *buf, unsigned int size)
{
	unsigned int args[] = {
		(unsigned int) buf,
		(unsigned int) size,
	};
	return semihosting_call(ESEM_GET_CMDLINE, (int) args);
}

int esem_heapinfo(heapinfo_block_t *block)
{
	return semihosting_call(ESEM_HEAPINFO, (int) &block);
}

int esem_elapsed(int *least_significant_word, int *most_significant_word)
{
	unsigned int args[] = {
		(unsigned int) least_significant_word,
		(unsigned int) most_significant_word,
	};
	return semihosting_call(ESEM_ELAPSED, (int) args);
}

int esem_tickfreq()
{
	return semihosting_call(ESEM_TICKFREQ, 0);
}