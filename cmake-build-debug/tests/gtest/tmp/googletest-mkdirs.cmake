# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src/googletest"
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src/googletest-build"
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest"
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/tmp"
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src/googletest-stamp"
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src"
  "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src/googletest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src/googletest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/gtest/src/googletest-stamp${cfgdir}") # cfgdir has leading slash
endif()
