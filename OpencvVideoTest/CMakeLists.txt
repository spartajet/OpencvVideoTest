# CMakeList.txt: OpencvVideoTest 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


#set(OpenCV_DIR "C:/OpenCV/build/x64/vc15/lib")  #OpenCVConfig.cmake所在的文件目录
set(OpenCV_DIR "C:/OpenCV/build")  #OpenCVConfig.cmake所在的文件目录
find_package(OpenCV 4.0 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 将源代码添加到此项目的可执行文件。
add_executable (OpencvVideoTest "OpencvVideoTest.cpp" "OpencvVideoTest.h")
target_link_libraries(OpencvVideoTest ${OpenCV_LIBS})

#"currentDir": "${workspaceRoot}"
# TODO: 如有需要，请添加测试并安装目标。
