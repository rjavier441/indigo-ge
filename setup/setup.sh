#!/bin/bash
# @project      Indigo System Setup Utility
# @file         setup.sh
# @author       R. Javier
# @version      v0.0.0
# @description  This script is a tool intended to automate installation and
#               deployment of all dependencies for the Indigo project on
#               Ubuntu/Debian Linux systems. Note: Ensure your line endings are
#               appropriate for your system's interpreter, otherwise this script
#               may not run!

# @includes
source res/setup.util.fs.sh

# @global       SCRIPTDIR
# @description  The full directory of this script file, accessible no matter
#               where the script is called from.
SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

# @function     _help()
# @description  This function prints the help prompt.
# @parameters   n/a
# @returns      n/a
function _help() {

  echo ""
  echo "==========================="
  echo "Indigo System Setup Utility"
  echo "       ___________"
  echo "      /__/__|__\__\ "
  echo "      \ \   |   / / "
  echo "       \         / "
  echo "        \ \ | / / "
  echo "         \     / "
  echo "          \ | / "
  echo "           \ / "
  echo ""
  echo "for Ubuntu/Debian"
  echo "v0.0.0"
  echo "==========================="
  echo ""
  printf "DESCRIPTION\n"
  printf "\tThis utility is used to automatically install dependencies for\n"
  printf "\tIndigo RPG Engine\n"
  printf "\n\tAll aliases take the commands of their root commands.\n"
  printf "\n\t-i, --install\n"
  printf "\t\tInstalls dependencies and sets up file system structures and\n"
  printf "\t\tpermissions.\n"
  printf "\n\t-h, --help\n"
  printf "\t\tPrints this help prompt.\n"
  exit 0
}

# @function			_install()
# @description	This function installs dependencies, sets up the required file
#               system structure, and handles necessary permissions.
# @parameters		(n/a)
# @returns			(n/a)
function _install() {

  # Update package listings
  _log "Updating package listings"
  sudo apt-get update

  # Install SFML Development Libraries if necessary
  _log "Checking for SFML"
  if [[ "$(_checkAptInstalled libsfml-dev)" == "0" ]]; then
    _log "Installing SFML"
    sudo apt-get install libsfml-dev
  fi

  # Install G++ Compiler if necessary
  _log "Checking for G++"
  if [[ "$(_checkAptInstalled g++)" == "0" ]]; then
    _log "Installing G++"
    sudo apt-get install g++
  fi

  # Verify G++ version
  _log "Verifying G++ Version"
  if [[ "$(_verifyCompiler)" == "0" ]]; then
    echo "Error: Unable to detect G++!"
    exit 1
  fi

  # Install Ubuntu/Debian Build Essentials if necessary
  _log "Checking for Ubuntu/Debian Build-Essentials Package"
  if [[ "$(_checkAptInstalled build-essential)" == "0" ]];then
    _log "Installing Ubuntu/Debian Build-Essentials Package"
    sudo apt-get install build-essential
  fi
}

# @function			_verifyCompiler()
# @description	This function checks that the compiler installed successfully.
# @parameters		(n/a)
# @returns			(string) result     1 on success, 0 otherwise.
function _verifyCompiler() {

  local output="$(g++ --version)"
  if [[ $output != *"opyright"* ]]; then
    echo "0"
  else
    echo "1"
  fi
}

# @function     _main()
# @description  This is the script's entry point, which determines the correct
#               action to perform based on the user's input.
# @parameters   (string) cmd        The main command to run. See _help() for a
#                                   full list of supported commands.
#               (string) a1         The first argument
#               (string) a2         The second argument
# @return       n/a
function _main() {

  # Local variables
  local cmd="$1"
  local a1="$2"
  local a2="$3"

  # Determine the command to run
  case "$cmd" in

    # Help
    -h|--help)
      _help
      exit 0
      ;;

    # Install
    -i|--install)
    _install
      exit 0
      ;;
    
    # Test
    -t|--test)
      if [[ "$(_checkAptInstalled libsfml-dev)" == "0" ]]; then
        echo "false"
      else
        echo "true"
      fi
      exit 0
      ;;

    # Unknown Option
    *)
      _help
      exit 0
      ;;
  esac
}

# Run program
_main $1 $2 $3