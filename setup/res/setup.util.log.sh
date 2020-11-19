#!/bin/bash
# @PROJECT:         Indigo System Setup Utility
# @Author:          R. Javier
# @File:            setup.util.log.sh
# @Date Created:    2020-11-19
# @Last Modified:   2020-11-19
# @Details:
#                   A collection of utility functions for console
#                   logging in Ubuntu/Debian.
# @Dependencies:
#                   n/a

# @global:          FGCOLOR
# @description:     A set of ANSI 4-bit forground text color escape codes*.
#                   Valid style names are keys to the dictionary below**.
#                   Look up the ANSI Select Graphic Rendition subset for a
#                   full list of valid codes in the ANSI standard.
# @notes            *Some colors don't look good in certain terminals
#                   (e.g. Yellow does not look bright in some WSL2 setups).
#                   **Color codes only show in printf with double quotes or
#                   using echo with the "-e" option.
#                   See https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
declare -A FGCOLOR
FGCOLOR[none]="\033[0m"   # i.e. reset all formatting = 0
FGCOLOR[black]="\033[0;30m" # not visible unless background is highlighted
FGCOLOR[darkgray]="\033[1;30m"
FGCOLOR[red]="\033[0;31m"
FGCOLOR[lightred]="\033[1;31m"
FGCOLOR[green]="\033[0;32m"
FGCOLOR[lightgreen]="\033[1;32m"
FGCOLOR[darkyellow]="\033[0;33m"
FGCOLOR[yellow]="\033[1;93m"
FGCOLOR[blue]="\033[0;34m"
FGCOLOR[lightblue]="\033[1;34m" # i.e. bold = 1, light blue foreground = 33
FGCOLOR[purple]="\033[0;35m"
FGCOLOR[lightpurple]="\033[1;35m"
FGCOLOR[cyan]="\033[0;36m"
FGCOLOR[lightcyan]="\033[1;36m"
FGCOLOR[lightgray]="\033[0;37m"
FGCOLOR[white]="\033[1;37m"

# @global:          LOGPRESET
# @description:     A set of log style presets. Unlike @global FGCOLOR, this
#                   set of styles also modify additional styling parameters
#                   like bold, underline, italic, and alternate fonts. Valid
#                   style names are keys to the dictionary below.
declare -A LOGPRESET
LOGPRESET[warning]="\033[0;30;43m"  # i.e. reset; black fg; yello bg
LOGPRESET[primary]="\033[1;37;44m"
LOGPRESET[info]="\033[1;37;104m"
LOGPRESET[success]="\033[1;37;102m"
LOGPRESET[danger]="\033[1;37;41m"
LOGPRESET[light]="\033[0;30;107m"
LOGPRESET[dark]="\033[1;37;40m"
LOGPRESET[invertedprimary]="\033[1;34;107m"
LOGPRESET[underline]="\033[0;37;4m"

# @function:        _testColors()
# @description:     Prints a test set of lines for available color codes.
# @parameters:      n/a
# @returns:         n/a
function _testColors() {
  # Print sample color styles
  echo -e "\033[0;4mSupported Foreground Color Styles:\033[0m"
  for key in "${!FGCOLOR[@]}"; do
    printf "${FGCOLOR[$key]}$key${FGCOLOR[none]}\n"
  done

  # Print sample log preset styles
  echo -e "\n\033[0;4mSupported Log Preset Styles:\033[0m"
  for key in "${!LOGPRESET[@]}"; do
    printf "${LOGPRESET[$key]}$key${FGCOLOR[none]}\n"
  done
}

# @function:        _clearCurrentLine()
# @description:     Removes the latest line. Useful for removing a progress
#                   bar after you're done with it.
# @parameters:      n/a
# @returns:         n/a
function _clearCurrentLine() {
  local screenWidth=$(tput cols)
  local replacementText=""
  for ((i = 0; i < ${screenWidth}; i++)); do
    replacementText+=" "
  done
  echo -ne "$replacementText\r"
}

# @function:        _printProgress()
# @description:     Prints a progress bar with the given percentage.
# @parameters:      (number) progress   The percentage to print out (i.e. a
#                                       number between and including 0 and
#                                       100).
# @returns:         n/a
function _printProgress() {
	local screenWidth=$(tput cols)
  local maxWidth=$((screenWidth - 8)) # -4 for xxx% and -4 for spacing
	local tickCnt=$((maxWidth*$1/100))
  local spaceCnt=$((maxWidth - tickCnt))
	local line=" "
  
  # Add leading spaces for percentage text
  if [[ "$1" < "10" ]]; then
    line+="  "
  elif [[ "$1" < "100" ]]; then
    line+=" "
  fi
  line+="$1% ["

  # Add progress ticks
  for ((i = 0; i < ${tickCnt}; i++)); do
		line+="|"
	done

  # Add spacer ticks
  for ((i = 0; i < ${spaceCnt}; i++)); do
    line+="."
  done
  line+="]"

  # Print progress bar to screen
  echo -ne "$line\r"
}

# @function			    _log()
# @description	    This prints a log to the console.
# @parameters		    (string) msg        The log message to show.
#                   (~string) style     The style to use for the message*
#                                       (see @global FGCOLOR and @global
#                                       LOGPRESET for a list of valid style
#                                       names).
#                   (~string) prefix    Text to prepend to the message.
#                   (~string) suffix    Text to append to the message.
# @returns			    (n/a)
# @notes            *Prefix and suffix are unaffected by the given style.
function _log() {
  local msgHeadStyle=${FGCOLOR[none]}
  local msgTailStyle=${FGCOLOR[none]}
  local msg="$1"
  local prefix=""
  local suffix=""
  local style=""
  local newline="\n"

  # Acquire prefix and suffix if given
  if [[ -n $3 ]]; then
    prefix=$3
  fi
  if [[ -n $4 ]]; then
    suffix=$4
  fi

  # Acquire style if given
  if [[ -n $2 ]]; then
    style=$2
  fi

  # Acquire newline setting if given
  if [[ -n $5 ]] && [[ $5 == "1" ]]; then
    newline=""
  fi

  # If style is specified
  if [[ -n $style ]]; then
    
    # If a valid color code, use it as a custom color code for the message
    if [[ -n ${FGCOLOR[$style]+Y} ]]; then
      msgHeadStyle=${FGCOLOR[$style]}

    # If a valid log preset, use it as a custom style for this message
    elif [[ -n ${LOGPRESET[$style]+Y} ]]; then
      msgHeadStyle=${LOGPRESET[$style]}
    fi
  fi

  printf "$prefix$msgHeadStyle$msg$msgTailStyle$suffix$newline"
}

# @function			    _hlog()
# @description	    This prints a fancy log heading to the console.
# @parameters		    (string) msg        The heading message to show.
#                   (~string) style     The style to use for the message
#                                       (see @global FGCOLOR and @global
#                                       LOGPRESET for a list of valid style
#                                       names).
# @returns			    (n/a)
function _hlog() {
  local msg="$1"
  local style=""

  # Acquire style if given
  if [[ -n $2 ]]; then
    style=$2
  fi

  _log "$msg" "$style" "[ " " ]"
}

# @function:        _nlog()
# @description:     Likg _log() but forces no newline
# @parameters:      (string) msg        The log message to show.
#                   (~string) style     The style to use for the message*
#                                       (see @global FGCOLOR and @global
#                                       LOGPRESET for a list of valid style
#                                       names).
#                   (~string) prefix    Text to prepend to the message.
#                   (~string) suffix    Text to append to the message.
# @returns:         n/a
function _nlog() {
  local msg="$1"
  local style=""
  local prefix=""
  local suffix=""

  # Acquire style if given
  if [[ -n $2 ]]; then
    style=$2
  fi

  # Acquire pre/suffix if given
  if [[ -n $3 ]]; then
    prefix=$3
  fi
  if [[ -n $4 ]]; then
    suffix=$4
  fi

  _log "$msg" "$style" "$prefix" "$suffix" "1"
}