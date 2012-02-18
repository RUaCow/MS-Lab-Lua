cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")

project(MS-Lab-Lua)

find_package(Boost REQUIRED)
find_package(wxWidgets REQUIRED)
find_package(Lua51 REQUIRED)
find_package(Luabind REQUIRED)

if(WIN32)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin)

file(GLOB filelist "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
foreach(filename ${filelist})
    set(SRCS ${SRCS} ${filename})
endforeach(filename)

file(GLOB filelist "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")
foreach(filename ${filelist})
    set(INCS ${INCS} ${filename})
endforeach(filename)
	
include("${wxWidgets_USE_FILE}")

include_directories(${Boost_INCLUDE_DIRS} ${wxWidgets_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${LUABIND_INCLUDE_DIRS})
add_executable(MS-Lab-Lua WIN32 ${SRCS} ${INCS})
target_link_libraries(MS-Lab-Lua ${Boost_LIBRARIES} ${wxWidgets_LIBRARIES} ${LUA_LIBRARIES} ${LUABIND_LIBRARIES})
