# Install script for directory: /home/hakim/Desktop/projects/GP_cpp/libgp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gp" TYPE FILE FILES
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_factory.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_linear_ard.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_linear_one.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_matern3_iso.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_matern5_iso.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_noise.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_rq_iso.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_periodic_matern3_iso.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_periodic.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_se_ard.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_se_ard_noisy_inp.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_se_iso.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_sum.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cov_prod.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/gp.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/gp_sparse.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/gp_utils.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/sampleset.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/rprop.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/input_dim_filter.h"
    "/home/hakim/Desktop/projects/GP_cpp/libgp/include/cg.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/libgp.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/libgp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/examples/cmake_install.cmake")
  include("/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/hakim/Desktop/projects/GP_cpp/libgp/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
