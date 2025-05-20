set(SOURCES
	sorting_test.cpp
)

add_executable(sorting_test ${SOURCES})

target_link_libraries(sorting_test
	gtest_main
	gmock_main
	sorting_task_lib
)

add_test(sorting_test sorting_test)