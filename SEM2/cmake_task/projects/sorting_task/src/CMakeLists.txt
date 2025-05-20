target_sources(sorting_task_lib
    PRIVATE
	output.cpp
	sorting.cpp
    PUBLIC
        output.hpp
	sorting.hpp
)


target_include_directories(sorting_task_lib PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)