// PROJECT:         Indigo
// Author:          R. Javier
// File:            LogWriter.hpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Defines an interface for classes that wish to store
//                  log messages to the file system.
// Dependencies:
//                  n/a
// Notes:
//                  The goal for this interface is to allow multiple types
//                  of concrete child classes to define their own way of:
//
//                  1.) creating/opening a file at a specified path
//                  2.) writing/appending string data to the file
//                  3.) closing the file that was opened.
//
//                  It is intended for each instance of a LogWriter child
//                  class to have its own internally stored/managed file i/o
//                  stream and/or FILE.
#pragma once

// @includes
#include <cstdio>
#include <string>

namespace Indigo {

  // @abstract        LogWriter
  // @description     Abstract class for things that can be stored into
  //                  the file system.
  class LogWriter {
    public:
      // @constants
      // @enum            Mode
      // @description     Defines different data storage modes to control
      //                  the behavior of LogWriter::write().
      enum Mode {
        Append,
        Overwrite
      };

      // @functions
      virtual bool open(std::string path, LogWriter::Mode dsm) = 0;
      virtual int write(std::string data) = 0;
      virtual bool close() = 0;
  };
}