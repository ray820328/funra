/**
 * Copyright (c) 2014 ray
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 *
 * @author: Ray
 */

#ifndef RINTERFACE_H
#define RINTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

struct rdata_handler_s;
typedef struct rdata_handler_s rdata_handler_t;

typedef int (*rdata_handler_on_before_func)(rdata_handler_t* handler, void* ds, void* data);
typedef int (*rdata_handler_process_func)(rdata_handler_t* handler, void* ds, void* data);
typedef int (*rdata_handler_on_code_func)(rdata_handler_t* handler, void* ds, void* data, int code);
typedef int (*rdata_handler_on_after_func)(rdata_handler_t* handler, void* ds, void* data);
typedef void (*rdata_handler_on_next_func)(rdata_handler_t* handler, void* ds, void* data);

typedef void (*rdata_handler_on_notify)(rdata_handler_t* handler, void* ds, void* data);
typedef void (*rdata_handler_notify)(rdata_handler_t* handler, void* ds, void* data);

struct rdata_handler_s {
    struct rdata_handler_s* prev;
    struct rdata_handler_s* next;

    rdata_handler_on_before_func on_before;
    rdata_handler_process_func process;
    rdata_handler_on_code_func on_code;
    rdata_handler_on_after_func on_after;
    rdata_handler_on_next_func on_next;

    rdata_handler_on_notify on_notify;// 被通知
    rdata_handler_notify notify; // 通知其他
};

#ifdef __cplusplus
}
#endif

#endif //RBASE_H
