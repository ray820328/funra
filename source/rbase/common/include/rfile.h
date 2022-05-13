﻿/**
 * Copyright (c) 2014 ray
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 *
 * @author: Ray
 */

#ifndef RFILE_H
#define RFILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rcommon.h"
#include "rlist.h"

/* ------------------------------- Macros ------------------------------------*/

#define file_path_len_max 8192 


/* ------------------------------- APIs ------------------------------------*/

int rfile_copy_file(const char* src, const char* dst);

int rfile_move_file(const char* src, const char* dst);

int rfile_remove(const char* file);

int rfile_format_path(char* file);

rlist_t* rdir_list(const char* dir, bool only_file, bool sub_dir);


#ifdef __cplusplus
}
#endif

#endif //RFILE_H