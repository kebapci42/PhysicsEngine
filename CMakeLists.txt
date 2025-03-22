cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

# SFML yapılandırma dosyalarının bulunduğu dizini belirtin
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(PhysicsEngine balls.cpp)

target_link_libraries(PhysicsEngine PRIVATE sfml-graphics sfml-window sfml-system)
