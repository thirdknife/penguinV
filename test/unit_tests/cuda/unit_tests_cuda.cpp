// This application is designed to run unit tests on penguinV library
#include <iostream>
#include "unit_test_image_function_cuda.h"
#include "../unit_test_framework.h"
#include "../../../src/cuda/cuda_device.cuh"
#include "../../../src/cuda/cuda_helper.cuh"

int main()
{
    // The main purpose of this application is to test everything within library
    // To do this we need an engine (framework) and a bunch of tests
    if ( !multiCuda::isCudaSupported() ) {
        std::cout << "No CUDA devices in the system" << std::endl;
        return 0;
    }

    multiCuda::CudaDeviceManager & deviceManager = multiCuda::CudaDeviceManager::instance();
    deviceManager.initializeDevices();

    int returnValue = 0;
    for ( int deviceId = 0; deviceId < deviceManager.deviceCount(); ++deviceId ) {
        deviceManager.setActiveDevice( deviceId );

        const multiCuda::CudaDevice & device = deviceManager.device();
        std::cout << device.name() << ": " << device.computeCapability() << std::endl;

        // We preallocate memory (32 MB)
        multiCuda::MemoryManager::memory().reserve( 32 * 1024 * 1024 );

        // We create a framework and add tests
        UnitTestFramework framework;
        addTests_Image_Function_Cuda( framework );

        // Just run the framework what will handle all tests
        returnValue += framework.run();
    }

    return returnValue;
}
