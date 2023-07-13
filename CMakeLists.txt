cmake_minimum_required(VERSION 3.21)

set(VCPKG_FEATURE_FLAGS "versions")

# Main Project for the whole repo
project( AWSSDKCurlIssue )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_C_STANDARD 90 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

add_subdirectory(src)
