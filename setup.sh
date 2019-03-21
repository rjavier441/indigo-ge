#!/bin/bash
# -----------------------------------------------------------------------------
# setup.sh
# -----------------------------------------------------------------------------
# 
# A setup script that attempts to install and
# configure the dependencies for this project.
# -----------------------------------------------------------------------------
installMethod="package manager"
packageManager=""    # Assume unknown

# -----------------------------------------------------------------------------
# Step 0: Acquire sudo priviledges
# -----------------------------------------------------------------------------
# Check if the current user is root (i.e. sudo
# privilege is already present)
if [ "$UID" -eq 0 ]; then
    echo "Sudo privilege acquired."
else
    echo "Acquiring sudo privileges..."
    exec sudo "$0" "$@"
fi

# -----------------------------------------------------------------------------
# Step 1: Determine the correct package manager/install method to use
# -----------------------------------------------------------------------------
if [ "$OSTYPE" == "linux-gnu" ]; then  # Linux

    # TODO: Determine which Linux distribution the system is running on
    packageManager="apt-get"
elif [ "$OSTYPE" == "cygwin" ]; then   # Linux Emulation on Windows

    # TODO: Determine how to install the packages in Linux Emulator
    packageManager="yum"
elif [ "$OSTYPE" == "msys" ]; then   # Windows Shell w/ GNU Utils (MinGW)

    # TODO: Determine how to install the packages in MinGW
    packageManager="?"
elif [ "$OSTYPE" == "darwin" ]; then   # Mac

    # According to the SFML documentation, Mac requires an intallation from the
    # intenet, so we'll have to download it instead of using a package manager
    installMethod="download"
    packageManager=""
fi

# -----------------------------------------------------------------------------
# Step 2: Acquire SFML
# -----------------------------------------------------------------------------
# Determine the method to acquire SFML
echo "Installing SFML by $installMethod..."
if [ "$installMethod" == "package manager" ]; then
    echo "Using package manager \"$packageManager\""
elif [ "$installMethod" == "download" ]; then
    echo "Downloading packages from the internet"
fi
exit 0
