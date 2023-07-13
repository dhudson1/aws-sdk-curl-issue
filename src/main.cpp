// ============================================================================
// Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ============================================================================

#include <curl/curl.h>
#include "aws/core/Aws.h"
#include "aws/secretsmanager/SecretsManagerClient.h"
#include "aws/secretsmanager/model/GetSecretValueRequest.h"
#include "aws/ssm/SSMClient.h"
#include "aws/ssm/model/GetParameterRequest.h"
#include <string>
#include "stdio.h"
#include "ssm_test.h"
#include "curl_test.h"

int main(int argc, char* argv[]) {

    curl_global_init(CURL_GLOBAL_DEFAULT);

    const char* website_str = nullptr;
    const char* ssm_path_str = nullptr;
    bool run_curl_with_aws = false;
    for (int cur_arg = 0; cur_arg < argc; ++cur_arg) {
        if (strcmp(argv[cur_arg], "--curl") == 0) {
            if (cur_arg + 1 >= argc) {
                printf("Must specify a website after --curl!\n", nullptr);
                return 1;
            }
            website_str = argv[++cur_arg];
        } else if (strcmp(argv[cur_arg], "--ssm") == 0) {
            if (cur_arg + 1 >= argc) {
                printf("Must specify an SSM path after --ssm!\n", nullptr);
                return 1;
            }
            ssm_path_str = argv[++cur_arg];
        } else if (strcmp(argv[cur_arg], "--run-curl-with-aws") == 0) {
            run_curl_with_aws = true;
        }
    }

    int ret_val = 0;
    if (ssm_path_str != nullptr) {
        ret_val = ssm_test(ssm_path_str, run_curl_with_aws);
        if (ret_val != 0) goto RET;
    }

    if (website_str != nullptr) {
        ret_val = test_curl(website_str);
    }

RET:
    curl_global_cleanup();

    return ret_val;
}