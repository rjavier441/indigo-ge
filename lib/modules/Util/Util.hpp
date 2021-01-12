// PROJECT:         Indigo
// Author:          R. Javier
// File:            Util.hpp
// Created:         2021-01-05
// Last Modified:   2021-01-05
// Details:
//                  A collection of utility methods for Indigo and tests.
// Dependencies:
//                  n/a
#pragma once

// @includes
// Compile-time OS check
#ifdef __linux__
# include <unistd.h>
# define INDIGO_USING_OS_LINUX
#else
# include <windows.h>
#endif
using namespace std;

namespace Indigo {
  namespace Util {
    void Sleep(unsigned int milliseconds) {
      #ifdef INDIGO_USING_OS_LINUX
        usleep(1000*milliseconds);
      #else
        ::Sleep(milliseconds);
      #endif
    }
  }
}