
add_executable(
        AWSSDKCurlIssue
        main.cpp
        ssm_test.cpp
        ssm_test.h
        curl_test.cpp
        curl_test.h
)

find_package(CURL CONFIG REQUIRED)

# Add include library for headers resolving
include_directories(SYSTEM "${CURL_INCLUDE_DIRS}" )

find_package(AWSSDK REQUIRED COMPONENTS secretsmanager ssm)
find_package(ZLIB)

set(AWS_LIBRARIES ${AWSSDK_LINK_LIBRARIES} ZLIB::ZLIB)



target_link_libraries(
        AWSSDKCurlIssue
        PUBLIC
        PRIVATE
        ${CURL_LIBRARIES}
        ${AWS_LIBRARIES}
)