// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef NANOARROW_INTEGRATION_C_DATA_INTEGRATION_H_INCLUDED
#define NANOARROW_INTEGRATION_C_DATA_INTEGRATION_H_INCLUDED

#include <stdint.h>

#if (defined _WIN32 || defined __CYGWIN__) && defined(NANOARROW_BUILD_DLL)
#if defined(NANOARROW_EXPORT_DLL)
#define NANOARROW_DLL __declspec(dllexport)
#else
#define NANOARROW_DLL __declspec(dllimport)
#endif  // defined(NANOARROW_EXPORT_DLL)
#elif !defined(NANOARROW_DLL)
#if __GNUC__ >= 4
#define NANOARROW_DLL __attribute__((visibility("default")))
#else
#define NANOARROW_DLL
#endif  // __GNUC__ >= 4
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Extra guard for versions of Arrow without the canonical guard
#ifndef ARROW_FLAG_DICTIONARY_ORDERED

#ifndef ARROW_C_DATA_INTERFACE
#define ARROW_C_DATA_INTERFACE

#define ARROW_FLAG_DICTIONARY_ORDERED 1
#define ARROW_FLAG_NULLABLE 2
#define ARROW_FLAG_MAP_KEYS_SORTED 4

struct ArrowSchema {
  // Array type description
  const char* format;
  const char* name;
  const char* metadata;
  int64_t flags;
  int64_t n_children;
  struct ArrowSchema** children;
  struct ArrowSchema* dictionary;

  // Release callback
  void (*release)(struct ArrowSchema*);
  // Opaque producer-specific data
  void* private_data;
};

struct ArrowArray {
  // Array data description
  int64_t length;
  int64_t null_count;
  int64_t offset;
  int64_t n_buffers;
  int64_t n_children;
  const void** buffers;
  struct ArrowArray** children;
  struct ArrowArray* dictionary;

  // Release callback
  void (*release)(struct ArrowArray*);
  // Opaque producer-specific data
  void* private_data;
};

#endif  // ARROW_C_DATA_INTERFACE
#endif  // ARROW_FLAG_DICTIONARY_ORDERED

NANOARROW_DLL const char* nanoarrow_CDataIntegration_ExportSchemaFromJson(
    const char* json_path, struct ArrowSchema* out);

NANOARROW_DLL const char* nanoarrow_CDataIntegration_ImportSchemaAndCompareToJson(
    const char* json_path, struct ArrowSchema* schema);

NANOARROW_DLL const char* nanoarrow_CDataIntegration_ExportBatchFromJson(
    const char* json_path, int num_batch, struct ArrowArray* out);

NANOARROW_DLL const char* nanoarrow_CDataIntegration_ImportBatchAndCompareToJson(
    const char* json_path, int num_batch, struct ArrowArray* batch);

NANOARROW_DLL int64_t nanoarrow_BytesAllocated(void);

#ifdef __cplusplus
}
#endif

#endif
