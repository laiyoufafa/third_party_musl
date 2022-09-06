/**
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include "functionalext.h"

typedef void (*TEST_FUN)();

/*
 * @tc.name      : prctl_0100
 * @tc.desc      : Verify that the thread can be given a name and get the name
 * @tc.level     : Level 0
 */
void prctl_0100(void)
{
    char buff[100] = {0};
    int prc = prctl(PR_SET_NAME, (unsigned long)"TestThread");
    int data = prctl(PR_GET_NAME, (unsigned long)buff);
    EXPECT_EQ("prctl_0100", prc, 0);
    EXPECT_EQ("prctl_0100", data, 0);
    EXPECT_STREQ("prctl_0100", buff, "TestThread");
}

TEST_FUN G_Fun_Array[] = {
    prctl_0100,
};

int main()
{
    int num = sizeof(G_Fun_Array) / sizeof(TEST_FUN);
    for (int pos = 0; pos < num; ++pos) {
        G_Fun_Array[pos]();
    }

    return t_status;
}