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

#include "stdio.h"
#include "ssm_test.h"
#include "curl_test.h"
#include "aws/core/Aws.h"
#include "aws/ssm/SSMClient.h"
#include "aws/ssm/model/GetParameterRequest.h"

int ssm_test(const char* ssm_path, bool run_curl_with_aws) {
    int ret_val = 0;

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::Client::ClientConfiguration config;
        config.region = "us-east-1";

        Aws::SSM::SSMClient ssm_client(config);
        Aws::SSM::Model::GetParameterRequest request;
        request.SetName(ssm_path);

        auto response = ssm_client.GetParameter(request);
        if (response.IsSuccess()) {
            printf("SSM Parameter %s has value: %s", ssm_path, response.GetResult().GetParameter().GetValue().c_str());
        } else {
            printf("Failed to get the SSM Parameter. SSM Parameter Path: %s\n", ssm_path);
            printf("Error Message: %s\n", response.GetError().GetMessage().c_str());
            ret_val = 1;
        }

        if (run_curl_with_aws) {
            test_curl("https://amazon.com");
        }
    }
    Aws::ShutdownAPI(options);

    return ret_val;
}
