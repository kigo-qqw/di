add_executable(test)
target_sources(test
        PRIVATE main.cpp

        PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        config.cppm
)

target_link_libraries(test PRIVATE di::di)

add_test(NAME test COMMAND test)
