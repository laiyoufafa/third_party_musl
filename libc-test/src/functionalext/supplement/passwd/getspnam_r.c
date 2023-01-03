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

#include <errno.h>
#include <shadow.h>
#include <string.h>
#include "test.h"

/**
 * @tc.name      : getspnam_r_0100
 * @tc.desc      : Get user database files. Test precondtions: /etc/shadow.
 * @tc.level     : Level 0
 */
void getspnam_r_0100(void)
{
    errno = 0;
    char buf[512];
    gid_t gid = 0;

    struct spwd *spwd;
    struct spwd spwd_storage;
    const char *spwd_name = "root";

    int result = getspnam_r(spwd_name, &spwd_storage, buf, sizeof(buf), &spwd);
    if (result != 0) {
        t_error("%s getgrnam_r failed\n", __func__);
    }
    if (!spwd) {
        t_error("%s failed, spwd is NULL\n", __func__);
    }
    if (strcmp(spwd_name, spwd->sp_namp)) {
        t_error("%s spwd->sp_namp is %s\n", __func__, spwd->sp_namp);
    }
}

int main(int argc, char *argv[])
{
    getspnam_r_0100();
    return t_status;
}