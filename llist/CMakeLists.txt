enable_testing()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories($CMAKE_CURRENT_SOURCE_DIR)

add_library(llist INTERFACE)
target_include_directories(llist
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
set_target_properties(llist PROPERTIES LINKER_LANGUAGE CXX)

install(
    DIRECTORY ${PROJECT_SOURCE_DIRECTORY}
    DESTINATION include
)

