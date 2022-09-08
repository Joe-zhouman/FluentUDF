/*
 * * Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
 */

#ifndef _BUFFERED_READER_H
#define _BUFFERED_READER_H

#include "global.h"

struct buffered_reader_type
{
  char *buffer1;
  char *buffer2;
  char *current_buffer;
  char *current_pos;
  char **buffer_end;
  int size_buf;
  FILE *stream;
  int data_valid_1;
  int data_valid_2;
  int bytes_read_1;
  int bytes_read_2;
  char *buffer_end_1;
  char *buffer_end_2;
  int window_size;
  char *window_scratch;
  int thread_running;
  int thread_exit;

  int buf_start_1;
  int buf_start_2;
  long global_offset;
  long global_data_limit;
  long initial_file_offset;

  int *data_valid;
  int *current_bytes;
};


extern void msleep(unsigned int ms); /* from multiport */
#define thread_sleep(t) msleep(t)


void init_buffered_reader(struct buffered_reader_type *reader, FILE *fp, int size, long limit);
void free_buffered_read_buffers(struct buffered_reader_type *reader);
void switch_read_buffer(struct buffered_reader_type *reader);
long get_current_reader_offset(struct buffered_reader_type *reader);
void buffered_read_bytes_bin(struct buffered_reader_type *reader, int *ptr, int bytes);
char *buffered_read_get_some_bytes(struct buffered_reader_type *reader);
int *buffered_read_bin_ints(struct buffered_reader_type *reader, int *ptr, int n);
long *buffered_read_bin_longs(struct buffered_reader_type *reader, long *ptr, int n);
cxindex *buffered_read_bin_indexes(struct buffered_reader_type *reader, cxindex *ptr, int n);
float *buffered_read_bin_floats(struct buffered_reader_type *reader, float *ptr, int n);
double *buffered_read_bin_doubles(struct buffered_reader_type *reader, double *ptr, int n);
real *buffered_read_bin_reals(struct buffered_reader_type *reader, real *ptr, int n, cxboolean double_data);
int buffered_read_char(struct buffered_reader_type *reader, char *c);
int buffered_read_advance_position(struct buffered_reader_type *reader, int bytes);
int buffered_read_intx(struct buffered_reader_type *reader, int *ptr, int *status);
int buffered_read_cxindexx(struct buffered_reader_type *reader, cxindex *ptr, int *status);
int buffered_read_longx(struct buffered_reader_type *reader, long *ptr, int *status);
int buffered_read_intd(struct buffered_reader_type *reader, int *ptr, int *status);
int buffered_read_cxindexd(struct buffered_reader_type *reader, cxindex *ptr, int *status);
int buffered_read_longd(struct buffered_reader_type *reader, long *ptr, int *status);
int buffered_read_indexx(struct buffered_reader_type *reader, cxindex *index, int *status);
int buffered_read_indexd(struct buffered_reader_type *reader, cxindex *index, int *status);
int buffered_flush_binary_data(struct buffered_reader_type *reader);
int buffered_flush_ws(struct buffered_reader_type *reader);
int buffered_flush_line(struct buffered_reader_type *reader);
int buffered_flush_string(struct buffered_reader_type *reader);
int buffered_flush_pexp(struct buffered_reader_type *reader);
int buffered_advance_pexp(struct buffered_reader_type *reader);
int buffered_flush_binary_section(struct buffered_reader_type *reader);
void buffered_flush_section(struct buffered_reader_type *reader, int section);
int buffered_read_intsx(struct buffered_reader_type *reader, int *ptr, int n);
int buffered_read_intsd(struct buffered_reader_type *reader, int *ptr, int n);
int buffered_read_cxindexsx(struct buffered_reader_type *reader, cxindex *ptr, int n);
int buffered_read_cxindexsd(struct buffered_reader_type *reader, cxindex *ptr, int n);
int buffered_read_longsx(struct buffered_reader_type *reader, long *ptr, int n);
int buffered_read_longsd(struct buffered_reader_type *reader, long *ptr, int n);
int buffered_read_indexesx(struct buffered_reader_type *reader, cxindex *ptr, int n);
int buffered_read_indexesd(struct buffered_reader_type *reader, cxindex *ptr, int n);
int buffered_read_reals(struct buffered_reader_type *reader, real *ptr, int n);
int buffered_read_doubles(struct buffered_reader_type *reader, double *ptr, int n);
int buffered_read_floats(struct buffered_reader_type *reader, float *ptr, int n);
void switch_reader_from_node0_to_host(struct buffered_reader_type *reader, int buffer_size);
void switch_reader_from_host_to_node0(struct buffered_reader_type *reader, int buffer_size);
int buffered_reader_function(void *handle, char *result, int n);
#endif
