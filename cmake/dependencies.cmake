# Copyright Louis Dionne 2016
# Copyright Zach Laine 2016-2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

###############################################################################
# Boost
###############################################################################
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.64.0 COMPONENTS ${boost_components})
if (Boost_INCLUDE_DIR)
  add_library(boost INTERFACE)
  target_include_directories(boost INTERFACE ${Boost_INCLUDE_DIR})
else ()
  message("-- Boost was not found; it will be cloned locally.")
  if (NOT BOOST_BRANCH)
    set(BOOST_BRANCH master)
  endif()
  add_custom_target(
    boost_root_clone
    git clone --depth 100 -b ${BOOST_BRANCH}
      https://github.com/boostorg/boost.git boost_root
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  add_custom_target(
    boost_clone
    COMMAND git submodule init libs/test
    COMMAND git submodule init libs/algorithm
    COMMAND git submodule init libs/bind
    COMMAND git submodule init libs/container_hash
    COMMAND git submodule init libs/exception
    COMMAND git submodule init libs/function
    COMMAND git submodule init libs/integer
    COMMAND git submodule init libs/io
    COMMAND git submodule init libs/iterator
    COMMAND git submodule init libs/move
    COMMAND git submodule init libs/mpl
    COMMAND git submodule init libs/numeric
    COMMAND git submodule init libs/preprocessor
    COMMAND git submodule init libs/range
    COMMAND git submodule init libs/smart_ptr
    COMMAND git submodule init libs/static_assert
    COMMAND git submodule init libs/type_index
    COMMAND git submodule init libs/type_traits
    COMMAND git submodule init libs/throw_exception
    COMMAND git submodule init libs/utility
    COMMAND git submodule init libs/assert
    COMMAND git submodule init libs/config
    COMMAND git submodule init libs/core
    COMMAND git submodule init libs/predef
    COMMAND git submodule init libs/detail
    COMMAND git submodule init tools/build
    COMMAND git submodule init libs/headers
    COMMAND git submodule init tools/boost_install
    COMMAND git submodule update --jobs 3
    COMMAND ./bootstrap.sh
    COMMAND ./b2 headers
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/boost_root
    DEPENDS boost_root_clone)
  add_library(boost INTERFACE)
  add_dependencies(boost boost_clone)
  target_include_directories(boost INTERFACE ${CMAKE_BINARY_DIR}/boost_root)
endif ()
