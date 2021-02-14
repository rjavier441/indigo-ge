// PROJECT:         Indigo
// Author:          R. Javier
// File:            ConsoleLogger.cpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Defines implementation of class ConsoleLogger.
// Dependencies:
//                  n/a

// @includes
#include <cstdio>
#include <ctime>
#include <locale>
#include <string>
#include <iostream>
#include <exception>
#include <fstream>
#include <filesystem>
#include "ConsoleLogger.hpp"
using namespace std;

// @ctor
Indigo::ConsoleLogger::ConsoleLogger() {
  recording = false;
  currentFilePath = "";
  logDir = "";
  currentLogDir = "";
}

// @dtor
Indigo::ConsoleLogger::~ConsoleLogger() {
  // Do nothing
}

// @function        getInstance()
// @description     Returns a reference to the ConsoleLogger singleton,
//                  initializing one if it doesn't yet exist.
// @parameters      n/a
// @returns         (ConsoleLogger&) ref
//                                      Refernce to the singleton.
Indigo::ConsoleLogger& Indigo::ConsoleLogger::getInstance() {
  
  // Initialize a single instance
  static ConsoleLogger instance;
  return instance;
}

// @function        log()
// @description     Prints a message
// @parameters      (string) msg        The message to print.
//                  (~string) prefix    (Optional) A message prefix,
//                                      useful for identifying the
//                                      message sender.
// @returns         (int) length        Length of the printed message.
//                                      Returns -1 on failure
int Indigo::ConsoleLogger::log(string msg, string prefix) {
  int writeResult = 0;
  int printResult = 0;
  if( recording ) {
    writeResult = write(prefix + msg + "\n");
  }
  printResult = printf("%s%s\n", prefix.c_str(), msg.c_str());
  return recording ? ( writeResult > -1 ? writeResult : -1 ) : printResult;
}

// @function        setRecording()
// @description     Controls whether the ConsoleLogger instance should save
//                  its messages to a log file.
// @parameters      (bool) active       If true, all subsequent calls to
//                                      ConsoleLogger::log() will be saved
//                                      into a log file until this function
//                                      is called with active as false.
// @returns         n/a
void Indigo::ConsoleLogger::setRecording(bool active) {

  try {

    // On recording activation
    if( !recording && active ) {

      // Update to latest recording path
      currentLogDir = logDir;

      // Ensure the log directory is found
      filesystem::path p = filesystem::absolute(currentLogDir);
      if( !filesystem::exists(p) ) {
        throw ConsoleLoggerException::LogDirNotFound( p.c_str() );
      }

      // Determine a unique file name
      if( currentLogDir.find_last_of('/') != currentLogDir.length() - 1 ) {
        currentLogDir += '/';
      }
      
      // Open a file for writing
      open( currentLogDir + generateFileName() );
    } else if( recording && !active ) { // On recording deactivation

      // Conclude recording by closing file
      close();
    }
    recording = active;
  } catch( const exception& e ) {
    printf("[ERR] %s\n", e.what());
    throw;  // rethrows current error
  }
}

// @function        getCurrentLogFilePath()
// @description     Gives the client a copy of the current log file path.
// @parameters      n/a
// @returns         (string) path       The path of the log file currently
//                                      being used*.
// @notes           * The current log file path only updates on a transition
//                    of recording from "inactive" to "active". Do not rely
//                    on this function to indicate if recording is currently
//                    active; use isRecording() instead.
string Indigo::ConsoleLogger::getCurrentLogFilePath() {
  return currentFilePath;
}

// @function        generateFileName()
// @description     Produces a unique filename using timestamps.
// @parameters      n/a
// @returns         (string) name       The name of a new log file.
string Indigo::ConsoleLogger::generateFileName() {
  
  // Use the current local system time to generate a unique file name
  time_t cur = time(nullptr);
  char temp[20];
  string output = Indigo::kEmptyString;
  if( strftime( temp, sizeof(temp), "%Y-%m-%d_%H:%M:%S",
    localtime(&cur) ) ) {
    output = static_cast<string>(temp);
  }
  
  return output + ".log";
}

// @function        startRecording()
// @description     Begins saving log messages if not already recording.
// @parameters      n/a
// @returns         n/a
void Indigo::ConsoleLogger::startRecording() {
  setRecording(true);
}

// @function        stopRecording()
// @description     Ends saving of log messages if not already ended.
// @parameters      n/a
// @returns         n/a
void Indigo::ConsoleLogger::stopRecording() {
  setRecording(false);
}

// @function        isRecording()
// @description     Returns the current recording active state.
// @parameters      n/a
// @returns         (bool) active       Returns true if the ConsoleLogger
//                                      singleton is currently recording.
bool Indigo::ConsoleLogger::isRecording() {
  return recording;
}

// @function        setLogDir()
// @description     Allows you to control where ConsoleLogger saves its log
//                  recordings following the next recording activation*.
// @parameters      (string) path       Specifies the directory to store
//                                      logs in.
// @returns         n/a
// @notes           * If the ConsoleLogger singleton is currently recording
//                    at the time of this function call, the new path will
//                    not be used until the next time recording is
//                    activated.
void Indigo::ConsoleLogger::setLogDir(string path) {
  logDir = path;
}

// @function        getCurrentLogDir()
// @description     Returns the currently used log directory*.
// @parameters      n/a
// @returns         (string) path       The currently used log directory.
// @notes           * If ConsoleLogger::setLogDir() was called while the
//                    ConsoleLogger singleton was currently recording, this
//                    function will not return the new log dir value until
//                    the next time recording is activated.
string Indigo::ConsoleLogger::getCurrentLogDir() {
  return currentLogDir;
}

// @function        open()
// @description     Opens a file to store log messages when recording is
//                  active. Creates a log file if it doesn't yet exist.
// @parameters      (string) path       The path of the file to create and
//                                      open.
//                  (~LogWriter::Mode) dsm
//                                      Determines whether to overwrite or
//                                      append data to the specified file.
//                                      Defaults to LogWriter::Mode::Append.
// @returns         (bool) success      Returns true only if file opened
//                                      successfully. Otherwise, returns
//                                      false.
bool Indigo::ConsoleLogger::open(string path, Indigo::LogWriter::Mode dsm) {

  try {
    // Update current filepath and open the file for the designated mode
    currentFilePath = path;
    if( !currentFile.is_open() ) {
      currentFile.open(
        currentFilePath,
        ios::out | (
          dsm == Indigo::LogWriter::Mode::Append ? ios::app : ios::trunc
        )
      );
      return currentFile.is_open();
    }
  } catch( const exception& e ) {
    printf("[ERR] %s\n", e.what());
  }
  return false;
}

// @function        write()
// @description     Writes data to the currently open log file.
// @parameters      (string) data       The message to write.
// @returns         (int) total         Total characters written. Returns
//                                      -1 on failure.
int Indigo::ConsoleLogger::write(string data) {

  try {
    // Do not write if no file is present
    if( currentFile.is_open() ) {
      int total = data.length();
      currentFile.write(data.c_str(), total);
      return total;
    }
  } catch( const exception& e ) {
    printf("[ERR] %s\n", e.what() );
  }
  return -1;
}

// @function        close()
// @description     Closes the file associated with this singleton.
// @parameters      n/a
// @returns         (bool) success      Returns true only if the file closed
//                                      successfully. Otherwise, returns
//                                      false.
bool Indigo::ConsoleLogger::close() {
  try {
    if( currentFile.is_open() ) {
      currentFile.close();
    }
    return !currentFile.is_open();
  } catch( const exception& e ) {
    printf("[ERR] %s\n", e.what());
    return false;
  }
}