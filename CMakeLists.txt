cmake_minimum_required(VERSION 3.12)

project(tsg)

# Enable grouping targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### TSG library section ###
file(GLOB TSG_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tsg/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/tsg/*.h"
)


add_library(tsg SHARED ${TSG_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/include)

# add necessary simbols to export the dll
add_compile_definitions(TSG_EXPORT)
target_compile_features(tsg PRIVATE cxx_std_20)

### Lessons section ###
file(GLOB LESSONS_SOURCES 
		"${CMAKE_CURRENT_SOURCE_DIR}/lessons/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/lessons/*.h"
)
add_executable(lessons ${LESSONS_SOURCES})
set_target_properties(lessons PROPERTIES FOLDER lessons)
#target_link_libraries(lessons PRIVATE tsg)
target_compile_features(lessons PRIVATE cxx_std_20)
add_compile_definitions(ENABLE=1)
add_compile_definitions(DISABLE=0)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")
