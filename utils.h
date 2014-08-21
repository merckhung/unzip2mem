/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <iostream>

#include "fd_file.h"
#include "stringprintf.h"
#include "ScopedFd.h"
#include "UniquePtr.h"

#define lseek64	lseek

namespace art {

const int VERBOSE = 0, DEBUG = 1, INFO = 2, WARNING = 3, ERROR = 4, FATAL = 5;
const int INTERNAL_FATAL = 6;  // For Runtime::Abort.

#define LOG(severity) std::cout
#define PLOG(severity) std::cout
#define LG LOG(INFO)

#define CHECK(x) std::cout
#define CHECK_OP(LHS, RHS, OP) std::cout

#define CHECK_EQ(x, y) CHECK_OP(x, y, ==)
#define CHECK_NE(x, y) CHECK_OP(x, y, !=)
#define CHECK_LE(x, y) CHECK_OP(x, y, <=)
#define CHECK_LT(x, y) CHECK_OP(x, y, <)
#define CHECK_GE(x, y) CHECK_OP(x, y, >=)
#define CHECK_GT(x, y) CHECK_OP(x, y, >)

#define CHECK_STROP(s1, s2, sense) \
  if (UNLIKELY((strcmp(s1, s2) == 0) != sense)) \
    LOG(FATAL) << "Check failed: " \
               << "\"" << s1 << "\"" \
               << (sense ? " == " : " != ") \
               << "\"" << s2 << "\""

#define CHECK_STREQ(s1, s2) CHECK_STROP(s1, s2, true)
#define CHECK_STRNE(s1, s2) CHECK_STROP(s1, s2, false)

#define CHECK_PTHREAD_CALL(call, args, what) \
  do { \
    int rc = call args; \
    if (rc != 0) { \
      errno = rc; \
      PLOG(FATAL) << # call << " failed for " << what; \
    } \
  } while (false)

#ifndef NDEBUG

#define DCHECK(x) CHECK(x)
#define DCHECK_EQ(x, y) CHECK_EQ(x, y)
#define DCHECK_NE(x, y) CHECK_NE(x, y)
#define DCHECK_LE(x, y) CHECK_LE(x, y)
#define DCHECK_LT(x, y) CHECK_LT(x, y)
#define DCHECK_GE(x, y) CHECK_GE(x, y)
#define DCHECK_GT(x, y) CHECK_GT(x, y)
#define DCHECK_STREQ(s1, s2) CHECK_STREQ(s1, s2)
#define DCHECK_STRNE(s1, s2) CHECK_STRNE(s1, s2)

#else  // NDEBUG

#define DCHECK(condition) \
  while (false) \
    CHECK(condition)

#define DCHECK_EQ(val1, val2) \
  while (false) \
    CHECK_EQ(val1, val2)

#define DCHECK_NE(val1, val2) \
  while (false) \
    CHECK_NE(val1, val2)

#define DCHECK_LE(val1, val2) \
  while (false) \
    CHECK_LE(val1, val2)

#define DCHECK_LT(val1, val2) \
  while (false) \
    CHECK_LT(val1, val2)

#define DCHECK_GE(val1, val2) \
  while (false) \
    CHECK_GE(val1, val2)

#define DCHECK_GT(val1, val2) \
  while (false) \
    CHECK_GT(val1, val2)

#define DCHECK_STREQ(str1, str2) \
  while (false) \
    CHECK_STREQ(str1, str2)

#define DCHECK_STRNE(str1, str2) \
  while (false) \
    CHECK_STRNE(str1, str2)

#endif

typedef ::unix_file::FdFile File;

template<typename T>
static inline T RoundDown(T x, int n) {
  CHECK(IsPowerOfTwo(n));
  return (x & -n);
}

template<typename T>
static inline T RoundUp(T x, int n) {
  return RoundDown(x + n - 1, n);
}


inline bool ReadFileToString(const std::string& file_name, std::string* result) {
  UniquePtr<File> file(new File);
  if (!file->Open(file_name, O_RDONLY)) {
    return false;
  }

  std::vector<char> buf(8 * KB);
  while (true) {
    int64_t n = TEMP_FAILURE_RETRY(read(file->Fd(), &buf[0], buf.size()));
    if (n == -1) {
      return false;
    }
    if (n == 0) {
      return true;
    }
    result->append(&buf[0], n);
  }
}

}  // namespace art
