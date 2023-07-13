# aws-sdk-curl-issue
Demonstrates libcurl and aws-sdk-cpp incompatibility/clobbering

Requires VCPKG to be able to run:
```shell
cd path/to/srcs
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh
```

The `cmake` command requires a path to the VCPKG: `-DCMAKE_TOOLCHAIN_FILE=/path/to/src/vcpkg/scripts/buildsystems/vcpkg.cmake`
for the required packages to be installed and built.

The `--curl <<website_url>>` runs libcurl right before exiting with the curl verbose logging.

The `--ssm <<SSM_parameter_path>>` gets the SSM parameter at the given path, with `Aws::InitAPI` and `Aws::ShutdownAPI`.

If both the `--curl` and `--ssm` are set, then SSM will always run before curl.

The additional flag `--run-curl-with-aws` will run libcurl between when `Aws::InitAPI` and `Aws::ShutdownAPI`. This will
only be run when `--ssm` is also configured (Note: this libcurl will only connect to `https://amazon.com`).
