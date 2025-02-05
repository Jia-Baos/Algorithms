cmake_minimum_required(VERSION 3.27)

project(kalman_filters)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Armadillo REQUIRED)

add_executable(KF_example examples/kf_example.cpp kalman_filter.h)
target_include_directories(KF_example PRIVATE ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(KF_example ${ARMADILLO_LIBRARIES})

add_executable(EKF_example examples/ekf_example.cpp extended_kalman_filter.h)
target_include_directories(KF_example PRIVATE ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(EKF_example ${ARMADILLO_LIBRARIES})

add_executable(UKF_example examples/ukf_example.cpp unscented_kalman_filter.h)
target_include_directories(KF_example PRIVATE ${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(UKF_example ${ARMADILLO_LIBRARIES})

install(TARGETS KF_example
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(TARGETS EKF_example
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(TARGETS UKF_example
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})
