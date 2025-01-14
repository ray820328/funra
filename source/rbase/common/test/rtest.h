/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
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

#ifndef RTEST_H
#define RTEST_H

#include "rcommon.h"

#include "include/rtest_com.h"

int run_rtime_tests(int benchmark_output);
int run_rbuffer_tests(int benchmark_output);
int run_rpool_tests(int benchmark_output);
int run_rstring_tests(int benchmark_output);
int run_rthread_tests(int benchmark_output);
int run_rarray_tests(int benchmark_output);
int run_rdict_tests(int benchmark_output);
int run_rcommon_tests(int benchmark_output);
int run_rlog_tests(int benchmark_output);
int run_rfile_tests(int benchmark_output);
int run_rtools_tests(int benchmark_output);

#endif /* RTEST_H */
