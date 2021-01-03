// PROJECT:         Indigo
// Author:          R. Javier
// File:            Logger.hpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Defines an interface for message logging.
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <string>

namespace Indigo {

  // @constants
  const std::string EMPTY_STRING = "";

  // @abstract        Logger
  // @description     Abstract class for loggers of any kind
  class Logger {
    public:
      // @functions
      virtual int log(std::string msg, std::string prefix) = 0;
  };
}