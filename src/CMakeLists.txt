add_executable(knitter 
knitter.cpp
settings.cpp)

find_package(wxWidgets COMPONENTS base core gl REQUIRED)

include(${wxWidgets_USE_FILE})

target_link_libraries(knitter ${wxWidgets_LIBRARIES})

