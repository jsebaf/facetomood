cmake_minimum_required(VERSION 3.10)
set(OpenCV_DIR "../opencv/src/sdk/native/jni")
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

include_directories("../facetomood/native/jni/include")

add_library(moodsdk STATIC IMPORTED)

set_target_properties(moodsdk
        PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../facetomood/native/libs/${CMAKE_ANDROID_ARCH_ABI}/libmoodsdk.so)

add_library(
        native-lib
        SHARED
        src/main/cpp/native-lib.cpp)

target_link_libraries(
        native-lib
        -landroid
        ${OpenCV_LIBS}

        moodsdk

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

