// PROJECT:         Indigo
// Author:          R. Javier
// File:            ConsoleLogger.hpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Defines a special logger solely for console-only
//                  debug messages
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <string>
#include "../../interface/Logger/Logger.hpp"

namespace Indigo {

  // @class           ConsoleLogger
  // @description     Console message logging class
  class ConsoleLogger : public Indigo::Logger {
    public:
      int log(
        std::string msg, std::string prefix = Indigo::EMPTY_STRING
      ) override;
      static ConsoleLogger& getInstance();
    private:
      ConsoleLogger();
      ~ConsoleLogger();
  };
}