cmake_minimum_required(VERSION 3.16)
project(MainProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Include directories
include_directories(/opt/homebrew/Cellar/sfml/2.6.1/include
                    ./View
                    ./Model
                    ./Controller)

# Library directories
link_directories(/opt/homebrew/Cellar/sfml/2.6.1/lib)

# Manually list source files
set(SOURCES
    main.cpp
    Controller/controller.cpp
    Model/model.cpp
    View/view.cpp
    Controller/sortcontroller.cpp
    Model/sortmodel.cpp
    View/sortview.cpp
    Controller/searchcontroller.cpp
    Model/searchmodel.cpp
    View/searchview.cpp
)

# Add executable
add_executable(main ${SOURCES})

# Link libraries
target_link_libraries(main sfml-graphics sfml-window sfml-system)

