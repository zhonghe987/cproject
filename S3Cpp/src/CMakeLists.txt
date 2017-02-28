# ----------------------------------------------
# Executable + define linking libraries

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
	add_executable(s3 main.cc op_s3.cc)
	add_dependencies(s3 ${DEPENDENCIES})
	target_link_libraries(s3 ${LIBRARIES} curl)