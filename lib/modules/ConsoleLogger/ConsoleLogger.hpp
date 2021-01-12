// PROJECT:         Indigo
// Author:          R. Javier
// File:            ConsoleLogger.hpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Defines a singleton class solely for console-only
//                  debug message logging
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <string>
#include <cstring>
#include <exception>
#include <fstream>
#include "../../interface/Logger/Logger.hpp"
#include "../../interface/LogWriter/LogWriter.hpp"

namespace Indigo {

  // @exceptions
  namespace ConsoleLoggerException {
    class LogDirNotFound : public std::exception {
      protected:
        std::string msg;
      public:
        explicit LogDirNotFound(const char* expectedPath)
          : msg("Missing log dir: " + std::string(expectedPath)) {}
        explicit LogDirNotFound(const std::string& expectedPath)
          : msg("Missing log dir: " + expectedPath) {}
        virtual ~LogDirNotFound() noexcept {}
        
        virtual const char* what() const noexcept {
          return msg.c_str();
        }
    };
  }

  // @class           ConsoleLogger
  // @description     Console message logging singleton.
  class ConsoleLogger : public Indigo::Logger, public Indigo::LogWriter {
    public:
      // @class methods
      static ConsoleLogger& getInstance();
      void startRecording();
      void stopRecording();
      bool isRecording();
      void setLogDir(std::string path);
      std::string getCurrentLogDir();
      std::string getCurrentLogFilePath();
      std::string generateFileName();
      
      // @interface methods
      int log(
        std::string msg,
        std::string prefix = Indigo::kEmptyString
      ) override;

    private:
      // @member variables
      bool recording;
      std::ofstream currentFile;
      std::string currentFilePath;
      std::string logDir;
      std::string currentLogDir;

      // @class methods
      ConsoleLogger();
      ~ConsoleLogger();
      void setRecording(bool active);

      // @interface methods
      bool open(
        std::string path,
        LogWriter::Mode dsm = LogWriter::Mode::Append
      ) override;
      int write(std::string data) override;
      bool close() override;

  };
}