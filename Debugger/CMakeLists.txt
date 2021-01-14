project(Debugger)

# Add sub directories
include_directories(${PROJECT_SOURCE_DIR})
# Create the executable

file(GLOB core_src
    "./*/*.cpp"
    "./*.cpp"
)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
set(GLOB PROTOBUF_MODELS_INCLUDES "")
set(GLOB PROTOBUF_MODELS_SOURCES "")
file(GLOB PROTOBUF_DEFINITION_FILES ${PROJECT_SOURCE_DIR}/proto/*.proto)
foreach(file ${PROTOBUF_DEFINITION_FILES})
    set(proto_files "${proto_files} ${file}")
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${file})
    
    set(PROTOBUF_MODELS_INCLUDES "${PROTOBUF_MODELS_INCLUDES} ${PROTO_HDRS}")
    set(PROTOBUF_MODELS_SOURCES "${PROTOBUF_MODELS_SOURCES} ${PROTO_SRCS}")
    list(APPEND core_src ${PROTO_SRCS})
endforeach()

add_executable(${PROJECT_NAME} 
    ${core_src}
)

# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    phoenix
    ${Protobuf_LIBRARIES}
)