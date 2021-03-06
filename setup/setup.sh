#!/bin/bash
# @project      Indigo System Setup Utility
# @file         setup.sh
# @author       R. Javier
# @version      v0.0.1
# @description  This script is a tool intended to automate installation and
#               deployment of all dependencies for the Indigo project on
#               Ubuntu/Debian Linux systems. Note: Ensure your line endings
#               are appropriate for your system's interpreter, otherwise
#               this script may not run!
# @notes        *If you are using WSL2, the -t/--test option will NOT be
#               able to launch a GUI app unless a link is made between
#               WSL2's X11 and Windows. See the VcXsrv Project:
#               https://github.com/ArcticaProject/vcxsrv
#               *Installing VcXsrv might break WSL2's DNS server config, but
#               a reconfiguration of your /etc/resolv.conf file and a slight
#               deviation from the VcXsrv DISPLAY modification can fix it.
#               Here are some helpful links to resolve the issues:
#               https://gist.github.com/coltenkrauter/608cfe02319ce60facd76373249b8ca6
#               https://kenny.yeoyou.net/it/2020/09/10/windows-development-environment.html
#               https://stackoverflow.com/a/63092879/9028285

# @includes
source res/setup.util.fs.sh
source res/setup.util.log.sh

# @global       SCRIPTDIR
# @description  The full directory of this script file, accessible no matter
#               where the script is called from.
SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

# @global:          VERSION
# @description:     The setup script's current version
VERSION="v0.0.1"

# @function     _help()
# @description  This function prints the help prompt.
# @parameters   n/a
# @returns      n/a
function _help() {

  _log
  _log "===========================" lightblue
  _log "Indigo System Setup Utility" primary
  _log "$VERSION"
  _log "       ___________" lightblue
  _log "      /__/__|__\__\ " lightblue
  _log "      \ \   |   / / " lightblue
  _log "       \         / " lightblue
  _log "        \ \ | / / " lightblue
  _log "         \     / " lightblue
  _log "          \ | / " lightblue
  _log "           \ / " lightblue
  _log ""
  _log "Ubuntu/Debian" red "for "
  _log "===========================" lightblue
  _log ""
  printf "DESCRIPTION\n"
  printf "\tThis utility is used to automatically install dependencies for\n"
  printf "\tIndigo RPG Engine\n"
  printf "\n\tAll aliases take the commands of their root commands.\n"
  printf "\n\t-i, --install\n"
  printf "\t\tInstalls dependencies and sets up file system structures and\n"
  printf "\t\tpermissions.\n"
  printf "\n\t-h, --help\n"
  printf "\t\tPrints this help prompt.\n"
  printf "\n\t-V, --verify\n"
  printf "\t\tChecks if you have all the required utilities installed.\n"
  printf "\n\t-t, --test\n"
  printf "\t\tTests your SFML installation by compiling and running a test\n"
  printf "\t\tapp"
  printf "\n"
  exit 0
}

# @function			_install()
# @description	This function installs dependencies, sets up the required file
#               system structure, and handles necessary permissions.
# @parameters		(n/a)
# @returns			(n/a)
function _install() {

  # Update package listings
  _hlog "Updating package listings"
  sudo apt-get update

  # Install SFML Development Libraries if necessary
  _hlog "Checking for SFML"
  if [[ "$(_checkAptInstalled libsfml-dev)" == "0" ]]; then
    _hlog "Installing SFML"
    sudo apt-get install libsfml-dev
  fi

  # Install G++ Compiler if necessary
  _hlog "Checking for G++"
  if [[ "$(_checkAptInstalled g++)" == "0" ]]; then
    _hlog "Installing G++"
    sudo apt-get install g++
  fi

  # Verify G++ version
  _hlog "Verifying G++ Version"
  if [[ "$(_verifyCompiler)" == "0" ]]; then
    echo "Error: Unable to detect G++!"
    exit 1
  fi

  # Install Ubuntu/Debian Build Essentials if necessary
  _hlog "Checking for Ubuntu/Debian Build-Essentials Package"
  if [[ "$(_checkAptInstalled build-essential)" == "0" ]];then
    _hlog "Installing Ubuntu/Debian Build-Essentials Package"
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
  local totalVerifySteps=""
  local currentProgress=""

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
    
    # Test SFML configuration
    -t|--test)
      # TEST
      _hlog "Testing SFML Installation..." lightblue

      # Switch this subshell to the sfml-dev test directory
      _log "Entering 'test/sfml-dev'..."
      cd test/sfml-dev

      # Compile main and generate
      _nlog "Compiling test application..."
      if g++ -c main.cpp; then
        _log "OK" success
      else
        _log "FAILED" danger
        _log "Compilation error, aborting!" red
        exit 1
      fi

      # Link main and SFML utilities to generate test executable "sfml-app"
      _nlog "Generating 'sfml-test.app' executable..."
      if g++ main.o -o sfml-test.app -lsfml-graphics -lsfml-window -lsfml-system; then
        _log "OK" success
      else
        _log "FAILED" danger
        _log "Linking error, aborting!" red
        exit 1
      fi

      # Test app
      _nlog "Starting 'sfml-test.app'..."
      if ./sfml-test.app; then
        _log "OK" success
      else
        _log "FAILED" danger
        _log "SFML app failed for some reason!" red
        exit 1
      fi

      _hlog "Test Complete" success
      exit 0
      ;;
    
    # Verify (checks dependencies and util availability)
    -V|--verify)

      totalVerifySteps="6"
      currentProgress="0"
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      _clearCurrentLine
      _hlog "Verifying CLI utilities..." lightblue
      # # DEBUG
      # _testColors
      # exit 0

      # Checks if apt is installed
      _nlog "Checking for apt/apt-get..."
      if [[ "$(which apt)" == "0" && "$(which apt-get)" == "0" ]]; then
        _log "FAILED" danger
        _log "Your system does not have apt or apt-get!" red
        exit 1
      else
        _log "OK" success
      fi
      currentProgress=$((currentProgress + 1))
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      sleep 1

      # Check if make is installed
      _clearCurrentLine
      _nlog "Checking for make..."
      if [[ "$(_checkCmdExists make)" == "0" ]]; then
        _log "FAILED" danger
        _log "Your system does not have GNU Make!" red
        exit 1
      else
        _log "OK" success
      fi
      currentProgress=$((currentProgress + 1))
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      sleep 1

      # Checks if scons is installed
      _clearCurrentLine
      _nlog "Checking for scons..."
      if [[ "$(_checkAptInstalled scons)" == "0" ]]; then
        _log "FAILED" danger
        _log "Your system does not have scons installed!" red
        exit 1
      else
        _log "OK" success
      fi
      currentProgress=$((currentProgress + 1))
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      sleep 1

      # Check if TAR is installed
      _clearCurrentLine
      _nlog "Checking for tar..."
      if [[ "$(_checkCmdExists tar)" == "0" ]]; then
        _log "FAILED" danger
        _log "Your system does not have Tar!" red
        exit 1
      else
        _log "OK" success
      fi
      currentProgress=$((currentProgress + 1))
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      sleep 1

      # Check if G++ is installed
      _clearCurrentLine
      _nlog "Checking for g++..."
      if [[ "$(_checkCmdExists g++)" == "0" ]]; then
        _log "FAILED" danger
        _log "Your system does not have g++!" red
        exit 1
      else
        _log "OK" success
      fi
      currentProgress=$((currentProgress + 1))
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      sleep 1

      # Checks if apt has SFML Dev Library installed
      _clearCurrentLine
      _hlog "Verifying SFML installation..." lightblue
      _nlog "Checking for libsfml-dev..."
      if [[ "$(_checkAptInstalled libsfml-dev)" == "0" ]]; then
        _log "FAILED" danger
        _log "Your system does not have SFML Dev Library installed!" red
        exit 1
      else
        _log "OK" success
      fi
      currentProgress=$((currentProgress + 1))
      _printProgress $((currentProgress * 100 / totalVerifySteps))
      sleep 1

      # End progress bar
      _clearCurrentLine
      _hlog "Verification Complete" success

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