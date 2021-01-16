cmake_minimum_required (VERSION 3.15)

project ("GRPCCountService")

set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET x64-windows)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH}) # custom module for grpc plugin

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(GRPCPlugin REQUIRED)

find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin) # Get full path to plugin


file(GLOB PROTO_FILES "proto/*.proto")
file(GLOB CPP_FILES 
    "cpp/*.cpp"
    "cpp/*.hpp"
)


protobuf_generate_cpp(PROTO_SRC PROTO_HDRS ${PROTO_FILES})
PROTOBUF_GENERATE_GRPC_CPP(PROTO_GRPC_SRC PROTO_GRPC_HDRS ${PROTO_FILES})

add_executable (${PROJECT_NAME} ${CPP_FILES} 
			${PROTO_SRC} ${PROTO_HDRS} # protobuf files
			${PROTO_GRPC_SRC} ${PROTO_GRPC_HDRS} # grpc protobuf files
)

target_link_libraries(${PROJECT_NAME} gRPC::grpc++)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})

add_custom_target(proto_python ALL DEPENDS ${PROTO_PYS})


# disable protobuf warnings as done here https://github.com/protocolbuffers/protobuf/blob/master/cmake/CMakeLists.txt
if (MSVC)
  # Build with multiple processes
  add_definitions(/MP)
  # MSVC warning suppressions
  add_definitions(
    /wd4018 # 'expression' : signed/unsigned mismatch
    /wd4065 # switch statement contains 'default' but no 'case' labels
    /wd4146 # unary minus operator applied to unsigned type, result still unsigned
    /wd4244 # 'conversion' conversion from 'type1' to 'type2', possible loss of data
    /wd4251 # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
    /wd4267 # 'var' : conversion from 'size_t' to 'type', possible loss of data
    /wd4305 # 'identifier' : truncation from 'type1' to 'type2'
    /wd4307 # 'operator' : integral constant overflow
    /wd4309 # 'conversion' : truncation of constant value
    /wd4334 # 'operator' : result of 32-bit shift implicitly converted to 64 bits (was 64-bit shift intended?)
    /wd4355 # 'this' : used in base member initializer list
    /wd4506 # no definition for inline function 'function'
    /wd4800 # 'type' : forcing value to bool 'true' or 'false' (performance warning)
    /wd4996 # The compiler encountered a deprecated declaration.
  )
endif()

