add_definitions(-g -O0)

add_executable(knitter
knitter.cpp
calculator.cpp
pattern.cpp
test_gl_canvas.cpp)

find_package(wxWidgets COMPONENTS base core gl REQUIRED)

include(${wxWidgets_USE_FILE})

target_link_libraries(knitter ${wxWidgets_LIBRARIES})

