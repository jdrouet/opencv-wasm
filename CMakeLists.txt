cmake_minimum_required( VERSION 3.1 )
project( HelloCV )

# Use C++ 11 by default
set( CMAKE_CXX_STANDARD 11 )

# Set Release as default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

# Needed for opencv2/opencv.hpp
include_directories( /third-party/opencv/include )

# Needed by opencv.hpp for opencv2/opencv_modules.hpp
include_directories( /third-party/opencv/build_wasm )

# Needed by opencv_modules.hpp for every module
file( GLOB opencv_include_modules "/third-party/opencv/modules/*/include" )
include_directories( ${opencv_include_modules} )

# Our hello world executable
add_executable( hello source/main.cpp source/resizer.cpp )

# Link to opencv.js precompiled libraries
file( GLOB opencv_js "/third-party/opencv/build_wasm/lib/*.a" )

target_link_libraries( hello ${opencv_js} )

set(COMPILE_FLAGS "-Wno-missing-prototypes")
set_target_properties( hello PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s WASM=1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -std=c++1z -O3 --llvm-lto 1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s ASSERTIONS=2")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --memory-init-file 0 -s TOTAL_MEMORY=134217728 -s ALLOW_MEMORY_GROWTH=1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --bind")

set_target_properties( hello PROPERTIES LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --bind" )
