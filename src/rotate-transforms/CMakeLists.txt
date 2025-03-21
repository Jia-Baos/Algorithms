cmake_minimum_required(VERSION 3.27)

project(rotate-transforms)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 将源代码添加到此项目的可执行文件。
aux_source_directory(. main_files)
add_executable(${PROJECT_NAME} ${main_files})

# Eigen3
find_package(Eigen3 REQUIRED)

# Opencv
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
        message(STATUS "OpenCV library status: ")
        message(STATUS " version: ${OpenCV_VERSION}")
        message(STATUS " library: ${OpenCV_LIBS}")
        message(STATUS " include path: ${OpenCV_INCLUDE_DIRS}")
else()
        message(STATUS "Could not find OpenCV library")
endif()

# PCL
find_package(PCL 1.10 REQUIRED)
add_definitions(${PCL_DEFINITIONS})

if(PCL_FOUND)
        message(STATUS "PCL library status: ")
        message(STATUS " version: ${PCL_VERSION}")
        message(STATUS " library: ${PCL_LIBRARIES}")
        message(STATUS " include path: ${PCL_INCLUDE_DIRS}")
else()
        message(STATUS "Could not find PCL library")
endif()

# 链接库头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})

# 链接库文件夹
target_include_directories(${PROJECT_NAME} PUBLIC ${PCL_LIBRARY_DIRS})

# 如果动态链接库和静态链接库同名，优先调用静态链接库
target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen ${OpenCV_LIBS} ${PCL_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})
