#!/bin/bash
# ---
# setup.sh
# ---
# 
# A setup script that attempts to install and
# configure the dependencies for this project.
# ---
installMethod="package manager"
packageManager=""    # Assume unknown


# BEGIN OS-Specific Functions
# @function     setuplinuxUbuntuDebian()
# @description  This function performs setup of packages in the Ubuntu or Deb-
#               ian Linux environments
# @parameters   n/a
# @returns      n/a 
function setupLinuxUbuntuDebian {

    # Update the aptitude package lists
    printf "\n\n[ Ubuntu/Debian ]\n\n"
    printf "\n\n< Updating Package Lists >\n\n"
    sudo apt-get update

    # Attempt to acquire SFML from the aptitude pacakage manager
    printf "\n\n< Downloading SFML using Aptitude >\n\n"
    sudo apt-get install libsfml-dev

    # Install G++
    printf "\n\n< Installing G++ Cpp Compiler >\n\n"
    sudo apt-get update
    sudo apt-get install g++

    # Install Build Essentials Package
    printf "\n\n< Installing Build Essentials >\n\n"
    sudo apt-get update
    sudo apt-get install build-essential

    # Verify G++ Version
    printf "\n\n< Checking G++ Version >\n\n"
    g++ --version
}

# @function     setupLinuxCygwin()
# @description  This function performs setup of pacakages in the emulated Linux
#               environment for Windows (CYGWIN).
# @parameters   n/a
# @returns      n/a
function setupLinuxCygwin {

    # TODO: Figure out how to install on the Windows Linux emulator
    printf "\n\n[ Cygwin ]\n\n"
    echo "This install method is not yet supported!"
}

# @function     setupLinuxMsys()
# @description  This function performs setup of pacakages in the emulated Linux
#               shell for Windows (MSYS).
# @parameters   n/a
# @returns      n/a
function setupLinuxMsys {

    # TODO: Figure out how to install on the Windows Linux emulator
    printf "\n\n[ MSYS ]\n\n"
    echo "This install method is not yet supported!"
}

# @function     setupMac()
# @description  This function performs setup of pacakages in the emulated Linux
#               shell for Windows (MSYS).
# @parameters   n/a
# @returns      n/a
function setupMac {

    # TODO: Figure out how to install on the Windows Linux emulator
    printf "\n\n[ Mac ]\n\n"
    echo "This install method is not yet supported!"
}
# END OS-Specific Functions

# @function     main()
# @description  This is the main routine of this script
# @parameters   n/a
# @returns      n/a
function main {

    # ---
    # Step 0: Acquire sudo priviledges
    # ---
    # Check if the current user is root (i.e. sudo
    # privilege is already present)
    printf "\n\n[ INDIGO SETUP ]"

    # ---
    # Step 1: Determine the correct package manager/install method to use
    # ---
    if [ "$OSTYPE" == "linux-gnu" ]; then  # Linux

        # TODO: Determine which Linux distribution the system is running on
        # For now, assume ubuntu/debian
        setupLinuxUbuntuDebian
    elif [ "$OSTYPE" == "cygwin" ]; then   # Linux Emulation on Windows

        # TODO: Determine how to install the packages in Linux Emulator
        setupLinuxCygwin
    elif [ "$OSTYPE" == "msys" ]; then   # Windows Shell w/ GNU Utils (MinGW)

        # TODO: Determine how to install the packages in MinGW
        setupLinuxMsys
    elif [ "$OSTYPE" == "darwin" ]; then   # Mac

        # Run the mac setup
        setupMac
    fi

    printf "\n[ Package Installation Complete ]\n"
}

# Run main routine
main

exit 0
