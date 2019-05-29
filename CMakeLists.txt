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
add_executable( hello source/main.cpp )

# Link to opencv.js precompiled libraries
file( GLOB opencv_js "/third-party/opencv/build_wasm/lib/*.a" )
target_link_libraries( hello ${opencv_js} )

# Specify linker arguments
# set_target_properties( hello PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --preload-file assets --bind" )

set(COMPILE_FLAGS "-Wno-missing-prototypes")
set_target_properties( hello PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --memory-init-file 0")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s TOTAL_MEMORY=134217728")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s FORCE_FILESYSTEM=1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --use-preload-plugins")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s MODULARIZE=1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s SINGLE_FILE=1")
set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s DEMANGLE_SUPPORT=1")
# set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0")
# set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -s EXPORT_NAME=\"'pbn'\"")
# set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --bind --post-js ${JS_HELPER} ${COMPILE_FLAGS}")
# set_target_properties(${the_module} PROPERTIES LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}")

set_target_properties( hello PROPERTIES LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} --bind" )
