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

# @function:        _checkCmdExists()
# @description:     Checks if the given terminal command/utility exists
#                   (i.e. "which [cmd]").
# @parameters:      (string) cmd        The command/utility to check for.
# @returns:         (string) result     1 on success, 0 otherwise.
function _checkCmdExists() {
  if [[ -n "$(which $1)" ]]; then
    echo "1"
  else
    echo "0"
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