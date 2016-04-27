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

/**
 * STDOUT file path
 */
#define HOST_STDOUT_PATH       ":tt"
/**
 * STDOUT open mode
 */
#define HOST_STDOUT_OPEN_MODE  OPEN_MODE_W
/**
 * STDIN file path
 */
#define HOST_STDIN_PATH        ":tt"
/**
 * STDIN open mode
 */
#define HOST_STDIN_OPEN_MODE   OPEN_MODE_R

/**
 * Open modes for @ref esem_open
 */
typedef enum {
 OPEN_MODE_R   = 0,   /**< Read */
 OPEN_MODE_RB  = 1,   /**< Read binary */
 OPEN_MODE_RP  = 2,   /**< Read plus */
 OPEN_MODE_RPB = 3,   /**< Read plus binary */
 OPEN_MODE_W   = 4,   /**< Write */
 OPEN_MODE_WB  = 5,   /**< Write binary */
 OPEN_MODE_WP  = 6,   /**< Write plus */
 OPEN_MODE_WPB = 7,   /**< Write plus binary */
 OPEN_MODE_A   = 8,   /**< Append */
 OPEN_MODE_AB  = 9,   /**< Append binary */
 OPEN_MODE_AP  = 10,  /**< Append plus */
 OPEN_MODE_APB = 11,  /**< Append plus binary */
} open_mode_t;

/**
 * Heapinfo struct
 */
typedef struct heapinfo_block {
    int heap_base;
    int heap_limit;
    int stack_base;
    int stack_limit;
} heapinfo_block_t;

/**
 * Opens file on host file system.
 *
 * @param[in] path  Null terminated path
 * @param[in] mode  Open mode. See @ref open_mode_t
 * @param[in] path_len Length of path (without null)
 *
 * @retval -1 Error
 * @retval >0 Handle(file descriptor)
 */
int esem_open(const char *path, open_mode_t mode, unsigned int path_len);

/**
 * Closes file on host file system.
 *
 * @param[in] handle Handle to file previously opened by @ref esem_open
 *
 * @retval -1 Error
 * @retval 0  Success
 */
int esem_close(int handle);

/**
 * Puts a character to the debug channel.
 *
 * @param[in] symbol Char to put
 */
void esem_writec(char symbol);

/**
 * Puts a null terminated string to the debug channel.
 *
 * @param[in] string
 */
void esem_write0(char *string);

/**
 * Writes  up  to  count bytes from the buffer pointed buf to 
 * the file referred to by the handle.
 *
 * @param[in] handle File handle. See @ref esem_open
 * @param[in] buf    Pointer to buf
 * @param[in] count  Number of bytes to write
 *
 * @retval Number of written bytes
 */
int esem_write(int handle, void *buf, unsigned int count);

/**
 * Reads  up  to  count bytes from the file referred to by the handle to the
 * buffer.
 *
 * @param[in] handle File handle. See @ref esem_open
 * @param[in] buf    Pointer to data
 * @param[in] count  Number of bytes to write
 *
 * @retval Number of bytes read
 */
int esem_read(int handle, void *buf, unsigned int count);

/**
 * Reads a byte from the console.
 *
 * @return Byte that was read
 */
char esem_readc();

/**
 * Checks if the return code of another semihosting call indicates an error
 *
 * @param[in] status Return code of previous semihosting call
 * 
 * @retval 0   Is not an error
 * @retval !0  Error
 */
int esem_iserror(int status);

/**
 * Chacks if a file handle is a tty file handle.
 *
 * @param[in] handle File handle opened by @ref esem_open
 *
 * @retval 1 Handle is an interactive device
 * @retval 0 Handle is not an interactive device
 * @retval !0 && !1 Error
 */
int esem_istty(int handle);

/**
 * Seeks absolute pos in a file.
 *
 * @param[in] handle File handle opened by @ref esem_open
 * @param[in] pos    Absolute position
 *
 * @retval -1 Error
 * @retval 0  Success
 */
int esem_seek_absolute(int handle, int pos);

/**
 * Get length of a file.
 * 
 * @param[in] handle File handle opened by @ref esem_open
 *
 * @retval -1 Error
 * @return File size (in bytes)
 */
int esem_flen(int handle);

/**
 * Get temporary name for a file.
 *
 * @param[in,out] buf             Pointer to a buffer
 * @param[in] target_indentifier  A target identifier for this filename
 * @param[in] buf_size            Size of a buffer (in bytes)
 *
 * @retval -1 Error
 * @retval 0  Success
 */
int esem_tmpnam(void *buf, int target_indentifier, unsigned int buf_size);

/**
 * Deletes file on the host file system.
 *
 * @param[in] path  Null terminated path
 * @param[in] path_len Length of path (without null)
 *
 * @retval 0  Success
 * @retval !0 Error code
 */
int esem_remove(char *path, unsigned int path_len);

/**
 * Renames a file.
 *
 * @param[in] old_path     Old file name
 * @param[in] old_path_len Length of old path
 * @param[in] new_path     New file name
 * @param[in] new_path_len New file name
 *
 * @retval 0   Success
 * @retval !0  Error
 */
int esem_rename(char *old_path, unsigned int old_path_len, char *new_path, unsigned int new_path_len);

/**
 * Returns the number of centiseconds since the execution started.
 *
 * @return Number of centiseconds
 * @retval -1  Error
 */
int esem_clock();

/**
 * Return epoch time (time since 00:00 January 1, 1970)
 *
 * @reval Epoch time
 */
unsigned int esem_time();

/**
 * Executes command on the host
 *
 * @param[in] command String passed to host command-line interpreter
 * @param[in] length  Length of the string
 *
 * @return Status
 */
int esem_system(const char* command, unsigned int length);

/**
 * Returns host errno
 */
int esem_errno();

/**
 * Returns the command line
 *
 * @param[in,out]  buf  Pointer to a buffer
 * @param[in]      size Size of the buffer
 *
 * @return Status
 */
int esem_get_cmdline(void *buf, unsigned int size);

/**
 * Returns namber of elapsed target ticks
 *
 * @retval -1 Error
 */
int esem_elapsed(int *least_significant_word, int *most_significant_word);

/**
 * Returns the tick frequency
 *
 * @return Number of ticks per seccond
 * @retval -1 Error
 */
int esem_tickfreq();