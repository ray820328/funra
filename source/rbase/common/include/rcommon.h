﻿/**
 * Copyright (c) 2014 ray
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 *
 * @author: Ray
 */

#ifndef RCOMMON_H
#define RCOMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "rbase.h"

#define sizeptr 8
#define LPRId64 L"lld"

#define rcheck_value(b, value) (value)

#define macro_print_macro_helper(x)   #x  
#define macro_print_macro(x)          #x"="macro_print_macro_helper(x)

#define rvoid(x) (void)(x)

    //#define rassert(expr, rv) 
    //	if(!(expr)) { 
    //		rerror(#expr" is null or 0"); 
    //		return rv; 
    //	}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4319 4819)
#endif //_MSC_VER

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif //__GNUC__
#if defined(_WIN32) || defined(_WIN64)
#pragma message("Platform info: "macro_print_macro(_WIN64))

#define rattribute_unused(declaration) declaration

#pragma setlocale("chs")

#include <io.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <mstcpip.h>
#include <iphlpapi.h>
#include <mswsock.h>
#include <climits>

#define get_filename(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#define likely(x) x
#define unlikely(x) x

#define access(param1, param2) _access(param1, param2)

#if defined(RAY_BUILD_AS_DLL)

#if defined(RAY_CORE) || defined(RAY_LIB)
#define R_API __declspec(dllexport)
#else
#define R_API __declspec(dllimport)
#endif

#else //RAY_BUILD_AS_DLL

#define R_API extern

#endif //RAY_BUILD_AS_DLL

#else //WIN32

#include "execinfo.h"
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <libgen.h>

#define rattribute_unused(declaration) __attribute__((unused)) declaration

#define get_filename(x) basename(x)
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define R_API extern

#endif //WIN32

//析构宏，二级指针难看
#define rdestroy_object(obejectPrt, destroyFunc) \
    if ((obejectPrt)) { \
        (destroyFunc)((obejectPrt)); \
        (obejectPrt) = NULL; \
    }


//#define RAY_USE_POOL

#ifdef RAY_USE_POOL
#define rnew_data(T) rcheck_value(true, rpool_get(T, rget_pool(T)))
#define rfree_data(T, data) \
            do { \
                rpool_free(T, data, rget_pool(T)); \
                data = NULL; \
            } while(0)

#define rnew_data_s(T, data)  data = rnew_data(T)

#else //RAY_USE_POOL
#define rnew_data(T) rcheck_value(true, raymalloc(sizeof(T)))
#define rfree_data(T, data) \
            do { \
			    rayfree(data); \
			    data = NULL; \
            } while(0)
#endif //RAY_USE_POOL

#define rmin(a,b) ((a)<(b)?(a):(b))
#define rmax(a, b) ((a)>(b)?(a):(b))

#define rcount_array(ptr, count) \
          do { \
            if ((ptr) != NULL) \
                (count) = sizeof((ptr)) / sizeof((ptr)[0]); \
            else \
                (count) = 0; \
          } while(0)


#define rassert(expr, msg)                                \
 do {                                                     \
  if (!(expr)) {                                          \
    fprintf(stderr,                                       \
            "Assertion failed in [ %s:%d (%s) ], [ %s ]\n", \
            __FILE__,                                     \
            __LINE__,                                     \
            #expr,                                        \
            (msg));                                         \
    abort();                                              \
  }                                                       \
 } while (0)

#define rassert_goto(expr, msg, code_int)                 \
 do {                                                     \
  if (!(expr)) {                                          \
    msg = msg ? msg : "";                                 \
    fprintf(stderr,                                       \
            "Assertion failed in [ %s:%d (%s) ], [%d - %s ]\n", \
            __FILE__,                                     \
            __LINE__,                                     \
            #expr,                                        \
            (code_int), (msg));                                   \
    goto exit##code_int;                                  \
  }                                                       \
 } while (0)


#if defined(_WIN32) || defined(_WIN64)
#define rmutex_t_def CRITICAL_SECTION
#else
#define rmutex_t_def pthread_mutex_t
#endif /* defined(_WIN32) || defined(_WIN64) */

    static inline void rmutex_init(void* rmutexObj)
    {
#if defined(_WIN32) || defined(_WIN64)
        InitializeCriticalSection(rmutexObj);
#else
        pthread_mutex_init(rmutexObj, NULL);
#endif /* defined(_WIN32) || defined(_WIN64) */
    }

    static inline void rmutex_lock(void* rmutexObj)
    {
#if defined(_WIN32) || defined(_WIN64)
        EnterCriticalSection(rmutexObj);
#else
        pthread_mutex_lock(rmutexObj);
#endif /* defined(_WIN32) || defined(_WIN64) */
    }

    static inline void rmutex_unlock(void* rmutexObj)
    {
#if defined(_WIN32) || defined(_WIN64)
        LeaveCriticalSection(rmutexObj);
#else
        pthread_mutex_unlock(rmutexObj);
#endif /* defined(_WIN32) || defined(_WIN64) */
    }

    static inline long get_cur_thread_id(void)
    {
#if defined(_WIN32) || defined(_WIN64)
        return GetCurrentThreadId();
#elif __linux__
        return (long)syscall(SYS_gettid);
#elif defined(__APPLE__) && defined(__MACH__)
        return (long)syscall(SYS_thread_selfid);
#else
        return (long)pthread_self();
#endif /* defined(_WIN32) || defined(_WIN64) */
    }

    static inline void wait_millsec(int ms)
    {   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
#if defined(_WIN32) || defined(_WIN64)
        Sleep(ms);
#else
        usleep(ms * 1000); //延迟挂起进程。进程被挂起放到reday queue, 库函数中实现的，调用alarm()
        //sleep(seconds);//秒

        //static struct timespec req;
        //static struct timespec rem;
        //int res = -1;

        //req.tv_sec = ms / 1000;
        //req.tv_nsec = ms % 1000 * 1000000;

        //while (res < 0) {
        //    res = clock_nanosleep(CLOCK_MONOTONIC, 0, &req, &rem); //多个系统时钟，需要使用相对于特定时钟的延迟
        //    if (res < 0) {
        //        if (errno == EINTR) {
        //            req = rem;
        //        }
        //        else {
        //            break;
        //        }
        //    }
        //}
#endif /* defined(_WIN32) || defined(_WIN64) */
    }

#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif //RCOMMON_H
