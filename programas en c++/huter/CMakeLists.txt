cmake_minimum_required(VERSION 3.2)

include("~/cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.10.9.tar.gz"
    SHA1 "53b198e364dc7bc8360fc545f798563229bd7e20"
)

project(Foo)

hunter_add_package(Boost COMPONENTS regex system filesystem)
find_package(Boost CONFIG REQUIRED regex system filesystem)

add_executable(foo foo.cpp)
target_link_libraries(foo PUBLIC Boost::regex Boost::system Boost::filesystem)
