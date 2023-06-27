# build with something like
#cmake -DCMAKE_TOOLCHAIN_FILE="C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake" .
#Compilar con cmake --build .
set(PACKAGES_DIR "C:\\Program Files\\vcpkg\\packages")
set(BOOST_INC "C:\\\\Program Files\\\\boost_1_82_0")
set(IMPORTED_IMPLIB "")
set(CPPRESTSDK_INC "${PACKAGES_DIR}\\cpprestsdk_x86-windows\\include")
set(cpprestsdk_DIR "${PACKAGES_DIR}\\cpprestsdk_x64-windows\\share\\cpprestsdk")
set(unofficial-brotli_DIR "${PACKAGES_DIR}\\brotli_x64-windows\\share\\unofficial-brotli")
cmake_minimum_required(VERSION 3.10)
project(azdebug VERSION 1.0)

find_package(cpprestsdk CONFIG REQUIRED)
#find_package(unofficial-brotli CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h
#configure_file(TutorialConfig.h.in TutorialConfig.h)
# TODO 3: Add an executable called Tutorial to the project
add_executable(azdebug debug.cpp json_utils.cpp jira.cpp azdev.cpp utils.cpp)
#target_link_libraries(azdebug PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal unofficial::brotli::brotlidec unofficial::brotli::brotlienc)
include_directories(${BOOST_INC} ${CPPRESTSDK_INC} ${CPPRESTSDK_INC}\\cpprest  ${CPPRESTSDK_INC}\\pplx)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED OFF)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.82.0 COMPONENTS ${BOOST_INC}\\\\lib64-msvc-14.2) 