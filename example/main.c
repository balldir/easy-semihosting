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

int main()
{
	esem_write0("Debug chanel string : TEST \n");
	esem_write0("Debug chanel char (T): ");
	esem_writec('T');
	esem_write0("\n");

	int std_out = esem_open(HOST_STDOUT_PATH, HOST_STDOUT_OPEN_MODE, sizeof(HOST_STDOUT_OPEN_MODE));
	esem_write(std_out, "Stdout chanel string : TEST \n", sizeof("Stdout chanel string : TEST \n"));
	
	esem_write(std_out, "Checking test file \" something.txt \" \n", sizeof("Checking test file \" something.txt \" \n"));
	int file = esem_open("something.txt", OPEN_MODE_R, sizeof("something.txt"));
	if (-1 != file) {
		esem_write(std_out, "Test file found\n", sizeof("Test file found\n"));
		char buf[128];
		int read = esem_read(file,buf,sizeof(buf));
		esem_write(std_out, "Test file content (up to 128 chars)\n", sizeof("Test file content (up to 128 chars)\n"));
		esem_write(std_out, buf, read);
		esem_close(file);
		esem_write(std_out, "Removing test file\n", sizeof("Removing test file\n"));
		esem_remove("something.txt", sizeof("something.txt"));
	}
	else {
		esem_write(std_out, "Test file is not found\n", sizeof("Test file is not found\n"));
		esem_write(std_out, "Creating test file \" something.txt \" \n", sizeof("Creating test file \" something.txt \" \n"));
		file = esem_open("something.txt", OPEN_MODE_W, sizeof("something.txt"));
		esem_write(std_out, "Writing to \"Test string\\n\" to test file \" something.txt \" \n", sizeof("Writing to \"Test string\\n\" to test file \" something.txt \" \n"));
		esem_write(file, "Test string\n", sizeof("Test string\n"));
		esem_close(file);
	}
	esem_write(std_out, "Trying to execute command (will work only on Ubuntu base)", sizeof("Trying to execute command (will work only on Ubuntu base)"));
	esem_system("notify-send Semihosting test", sizeof("notify-send Semihosting test"));

	for(;;) {};
	return 0;
}

#ifndef __NO_SYSTEM_INIT
void SystemInit()
{}
#endif
