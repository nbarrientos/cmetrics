/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  CMetrics
 *  ========
 *  Copyright 2021-2024 The CMetrics Authors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#ifndef CMT_DECODE_PROMETHEUS_REMOTE_WRITE_H
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_H

#include <cmetrics/cmetrics.h>
#include <prometheus_remote_write/remote.pb-c.h>

#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_ADD_METADATA           CMT_FALSE
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_CUTOFF_THRESHOLD       60L*60L*1000000000L

#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_SUCCESS                0
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_ALLOCATION_ERROR       1
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_UNEXPECTED_ERROR       2
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_INVALID_ARGUMENT_ERROR 3
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_UNEXPECTED_METRIC_TYPE 4
#define CMT_DECODE_PROMETHEUS_REMOTE_WRITE_DECODE_ERROR           5

static void *__cmt_allocator_alloc(void *data, size_t size) {
    return malloc(size);
}
static void __cmt_allocator_free(void *data, void *ptr) {
    free(ptr);
}

static ProtobufCAllocator __cmt_allocator = {
  .alloc = __cmt_allocator_alloc,
  .free = __cmt_allocator_free,
  .allocator_data = NULL
};

#define cmt_system_allocator __cmt_allocator

int cmt_decode_prometheus_remote_write_create(struct cmt **out_cmt, char *in_buf, size_t in_size);
void cmt_decode_prometheus_remote_write_destroy(struct cmt *cmt);

#endif
