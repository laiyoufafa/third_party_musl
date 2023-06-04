/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dlfcn.h>
#include <sys/time.h>
#include <stdio.h>
#include <iostream>

#define LIBACE_PATH "system/lib64/libace.z.so"

class ScopeTime {
public:
    explicit ScopeTime() : cost(0)
    {
        gettimeofday(&timeStart, nullptr);
    }

    void CurrentTime()
    {
        struct timeval timeCurrent;
        gettimeofday(&timeCurrent, nullptr);
        cost = (timeCurrent.tv_sec - timeStart.tv_sec) * 1000.0 +
            (double)(timeCurrent.tv_usec - timeStart.tv_usec) / 1000.0;
        printf("current cost %f ms.\n", cost);
    }

    ~ScopeTime()
    {
        gettimeofday(&timeEnd, nullptr);
        cost = (timeEnd.tv_sec - timeStart.tv_sec) * 1000.0 + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000.0;
        printf("dlopen cost %f ms.\n", cost);
    }
private:
    struct timeval timeStart, timeEnd;
    double cost;
};

static void DoDlopen(const char *fileName, int flags)
{
    ScopeTime st;
    void *handle = dlopen(fileName, flags);
    if (handle == nullptr) {
        printf("dlopen error: %s", dlerror());
        exit(-1);
    }
}

int main()
{
    DoDlopen(LIBACE_PATH, RTLD_LAZY);
    return 0;
}