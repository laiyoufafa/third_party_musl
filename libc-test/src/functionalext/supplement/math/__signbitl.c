/*
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
#include <stdint.h>
#include "functionalext.h"

const int32_t COUNT_ZERO = 0;
const int32_t COUNT_ONE = 1;

/**
 * @tc.name      : signbitl_0100
 * @tc.desc      : the sign bit of the returned argument is 0 (The value of the argument of type long is 0)
 * @tc.level     : Level 0
 */
void signbitl_0100(void)
{
    long double x = 0;
    int result;
    result = __signbitl(x);
    EXPECT_EQ("signbitl_0100", result, COUNT_ZERO);
}

/**
 * @tc.name      : signbitl_0200
 * @tc.desc      : the sign bit of the returned argument is 0 (The value of the argument of type long is positive)
 * @tc.level     : Level 0
 */
void signbitl_0200(void)
{
    long double x = 10;
    int result;
    result = __signbitl(x);
    EXPECT_EQ("signbitl_0200", result, COUNT_ZERO);
}

/**
 * @tc.name      : signbitl_0300
 * @tc.desc      : the sign bit of the returned parameter is 1
 *                  (The parameter value of type long is negative)
 * @tc.level     : Level 0
 */
void signbitl_0300(void)
{
    long double x = -10;
    int result;
    result = __signbitl(x);
    EXPECT_EQ("signbitl_0300", result, COUNT_ONE);
}

int main()
{
    signbitl_0100();
    signbitl_0200();
    signbitl_0300();
    return t_status;
}