# Indigo
A 2D RPG Engine for building simple RPG games

Current Version: v0.0.0

Created: 2019-03-20

Updated: 2020-11-20

---

## Table of Contents

- [Setup](#setup)
    - [Linux/Mac](#on-linuxmac)
    - [Windows](#on-windows)
- [Release Notes](#release-notes)

---

## Setup
This project was built in the Ubuntu Xenial 16.04 LTS Linux environment, and was built using

- SFML (v2.5.1+)
- C++ 11
- G++ 7.3.0 (ubuntu)

### On Linux/Mac
Setup on Linux or Mac systems can be done in either of the following ways.

- *Verify Environment Utilities*
    - Use the [setup script](./setup/setup.sh) to verify that your system has the appropriate tools and utilities to run the setup and configuration:
        ```bash
        ./setup.sh -V
        ```

- *Quick Setup*
    - You can automatically install and setup all dependencies by running the [setup script](./setup/setup.sh) provided in the project's root directory.
    - If installation fails, try manually installing the dependencies as described below.

- *Manual Setup*
    - You can acquire SFML by either visiting the [SFML website](https://www.sfml-dev.org/)

- *Test Installation*
    - Be sure to do a test run of your SFML installation by using the [setup script](./setup/setup.sh):
        ```bash
        ./setup.sh -t
        ```
    - This will attempt to compile and run a sample SFML GUI application on your system.
        - There are some caveats with this; see the [release notes](#release-notes)

---

## Release Notes

- 2020-11-20
    - If you are using WSL2 during a test run with "`./setup.sh -t`", you may need to update your WSL firewall settings to allow SFML to forward its video output to its display
        - See [X11 Forwarding on WSL2 - StackOverflow](https://stackoverflow.com/questions/61110603/how-to-set-up-working-x11-forwarding-on-wsl2) for more details