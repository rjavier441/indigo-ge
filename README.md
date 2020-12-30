# **Indigo**

A 2D RPG Engine for building RPG games

Current Version: v0.0.1

Created: 2019-03-20

Updated: 2020-12-29

---

## **Table of Contents**

- [Dependencies](#dependencies)
- [Setup](#setup)
    - [Linux/Mac](#linuxmac)
- [Release Notes](#release-notes)

---

## **Dependencies**

This project was built under Ubuntu 20.04 (WSL2) and tested using the following tools and libraries:

- [SFML](https://www.sfml-dev.org/index.php) v2.5.1 using C++ 11
- [GNU G++](https://gcc.gnu.org/) v7.3.0 C++ Compiler
- [Catch2](https://github.com/catchorg/Catch2) v2.13.3 Unit Testing Framework
- [FakeIt](https://github.com/eranpeer/FakeIt) v2.0.5 C++ Mocking Framework
- *[VcXsrv](https://github.com/ArcticaProject/vcxsrv) v1.20.8.1 WSL2 X-Server

_*Only required if running Indigo in WSL2_

---

## **Setup**

Make sure you have the above dependencies installed and configured _**before**_ proceeding.

### Linux/Mac

Setup on Ubuntu Linux or Mac OS systems can be done through the following steps:

#### Verify Environment Utilities
    
- Use the [setup script](./setup/setup.sh) to verify that the required setup tools and utilities are installed:

    ```shell
    ~$ cd ./setup
    ~$ ./setup.sh -V
    ```

- Once required setup tools and utilities are installed, you can begin setup below.

#### Quick Setup

- Dependency setup and installation can be done automatically by running the [setup script](./setup/setup.sh):

    ```shell
    ~$ cd ./setup
    ~$ ./setup.sh -i
    ```

- If automatic installation fails, try manual installation described below.

#### Manual Setup

- Acquire SFML v2.0.5 via any of the following means:
    - Visit the [SFML website](https://www.sfml-dev.org/), download a compatible version and install it in your system.
    - Use your system's package manager (e.g. `apt`, `yum`, etc.) to acquire and install a compatible version.
- Ensure Catch2 v2.13.3 is included under `indigo/test/lib/catch2/`.
- If Catch2 is not found, acquire it via any of the following means:
    - Visit [Catch2 on Github](https://github.com/catchorg/Catch2), download the latest [single-header version](https://raw.githubusercontent.com/catchorg/Catch2/v2.x/single_include/catch2/catch.hpp), then save the resulting `catch.hpp` file under `indigo/test/lib/catch2/catch.hpp` (create the directory if it doesn't exist).
    - Use your system's package manager to acquire a compatible version.
- Ensure FakeIt v2.0.5 is installed under `indigo/test/lib/fakeit`

#### Test Installation

- Be sure to do a test run of your SFML installation by using the [setup script](./setup/setup.sh):
    
    ```shell
    ~$ cd ./setup
    ~$ ./setup.sh -t
    ```

- This will attempt to compile and run a sample SFML GUI application on your system.
    - There are some _**caveats**_ with this; see the [2020-11-20 release notes](#release-notes)

---

## **Release Notes**

- 2020-11-20
    - _(**For Ubuntu 20.04 WSL2 only**)_
        - Ubuntu 20.04 under WSL2 _**does not**_ come pre-packaged with a GUI environment to render graphics on.
        - However, you can _**forward**_ the rendering to your primary OS (i.e. Windows 10) via an X-Server, allowing you to run an Indigo game GUI by "proxy".
        - Install [VcXsrv](https://github.com/ArcticaProject/vcxsrv) and configure it to run in your WSL2 system before starting setup.
    - If you are using WSL2 during a test run with "`./setup.sh -t`":
        - You may need to update your WSL2 firewall settings to allow SFML to forward its video output to Windows
        - See [X11 Forwarding on WSL2 - StackOverflow](https://stackoverflow.com/questions/61110603/how-to-set-up-working-x11-forwarding-on-wsl2) for more details