cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

# SFML'yi arar (Windows için ek ayarlar gerekebilir)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(PhysicsEngine balls.cpp)

# Statik kütüphane kullanacaksanız ekleyin:
# add_definitions(-DSFML_STATIC)

target_link_libraries(PhysicsEngine PRIVATE sfml-graphics sfml-window sfml-system)

