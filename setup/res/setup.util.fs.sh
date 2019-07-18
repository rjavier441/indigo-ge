#!/bin/bash
# @project      Indigo System Setup Utility
# @file         setup.util.fs.sh
# @author       R. Javier
# @version      v0.0.0
# @description  A collection of utility functions for file system related tasks
#               in Ubuntu/Debian

# @function			_checkAptInstalled()
# @description	This function checks if the specified apt package is installed.
# @parameters		(string) package    The full name of the package to look for.
# @returns			(string) result     1 on success, 0 otherwise.
function _checkAptInstalled() {

  local output="$(apt list --installed)"
  if [[ $output != *"$1"* ]]; then
    echo "0"
  else
    echo "1"
  fi
}

# @function     _checkDirExists()
# @description  This function check if the given directory exists.
# @parameters   (string) dir        The directory to check.
# @returns      (string) result     1 on success, 0 otherwise.
function _checkDirExists() {

  if [[ ! -d "$1" ]]; then
    echo "0"
  else
    echo "1"
  fi
}

# @function     _checkFileExists()
# @description  This function check if the given file exists.
# @parameters   (string) file       The file to check.
# @returns      (string) result     1 on success, 0 otherwise.
function _checkFileExists() {

  if [[ ! -f "$1" ]]; then
    echo "0"
  else
    echo "1"
  fi
}

# @function     _checkTarInstalled()
# @description  This function checks if GNU tar is installed in your machine.
# @parameters   n/a
# @returns      1 on success, 0 otherwise.
function _checkTarInstalled() {

  local output="$(tar --version)"
  if [[ $output != *"(GNU tar)"* ]]; then
    echo "0"
  else
    echo "1"
  fi
}

# @function			_log()
# @description	This prints a fancy log to the console
# @parameters		(string) log        The message to show
# @returns			(n/a)
function _log() {

  local msg="$1"
  printf "[ $msg ]\n"
}