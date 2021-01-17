# **Indigo**

A 2D RPG Engine for building RPG games

Current Version: v0.0.1

Created: 2019-03-20

Updated: 2020-12-29

---

## **Table of Contents**

- [Dependencies](#dependencies)
- [Prerequesites](#prerequesites)
- [Setup](#setup)
    - [Linux](#linux)
- [Release Notes](#release-notes)

---

## **Dependencies**

This project was built under Ubuntu 20.04 (WSL2) and tested using the following tools and libraries:

- [SFML](https://www.sfml-dev.org/index.php) v2.5.1 using C++ 11
- [GNU G++](https://gcc.gnu.org/) v7.3.0 C++ Compiler
- [Catch2](https://github.com/catchorg/Catch2) v2.13.3 Unit Testing Framework
- [FakeIt](https://github.com/eranpeer/FakeIt) v2.0.5 C++ Mocking Framework
- *[VcXsrv](https://github.com/ArcticaProject/vcxsrv) v1.20.8.1 WSL2 X-Server

_*Only required if running Indigo games in WSL2_

---

## **Prerequesites**

This section will go over initial configuration steps required for the setup section. Make sure to complete this section _**before**_ proceeding to [Setup](#setup).

### Catch2 Setup

1. A single-file header for Catch2 v2.13.3 is _**already**_ included under `test/lib/catch2/catch.hpp`.

1. However, you may use any other _**compatible**_ version by replacing the file in that directory.
    - Make sure to name the file `"catch.hpp"`.

### FakeIt Setup

1. A single-file header for FakeIt v2.0.5 is _**already**_ included under `test/lib/fakeit/single_header/catch/fakeit.hpp`. However, you will need to create the file `test/lib/fakeit/config.txt` and place the following content inside it:
    ```
    ./test/lib/fakeit
    ```

1. However, you may use any other _**compatible**_ version by replacing the file in that directory.
    - Make sure to name the file `"fakeit.hpp"`.

---

## **Setup**

Make sure you have completed the [Prerequesites](#prerequesites) section _**before**_ proceeding.

### Linux

Setup on Ubuntu Linux systems can be done through the following steps:

#### Verify Environment Utilities
    
- Use the [setup script](./setup/setup.sh) to verify that the required setup tools and utilities are installed:

    ```shell
    ~$ cd ./setup
    ~$ ./setup.sh -V
    ```

- Once required setup tools and utilities are installed, you can begin setup below.
    - If verification fails or your system is not Ubuntu Linux, you will have to perform [Manual Setup](#manual-setup).

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
- If you would like to use a different Catch2 version:

    - Visit [Catch2 on Github](https://github.com/catchorg/Catch2), download the desired [single-header version](https://raw.githubusercontent.com/catchorg/Catch2/v2.x/single_include/catch2/catch.hpp), then save the resulting `catch.hpp` file under `indigo/test/lib/catch2/catch.hpp` (create the directory if it doesn't exist).

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

- 2020-11-20 _**(For Ubuntu WSL2 only)**_
    - Ubuntu 20.04 under WSL2 _**does not**_ come pre-packaged with an environment to render any GUIs.
        - However, you can _**forward**_ the rendering to your primary OS (i.e. Windows 10) via an X-Server, allowing you to run an Indigo game GUI by "proxy".
        - Install [VcXsrv](https://github.com/ArcticaProject/vcxsrv) and configure it to run in your WSL2 system before starting setup.
    - If you are using WSL2 during a test run with "`./setup.sh -t`":
        - You may need to update your WSL2 firewall settings to allow SFML to forward its video output to Windows
        - See [X11 Forwarding on WSL2 - StackOverflow](https://stackoverflow.com/questions/61110603/how-to-set-up-working-x11-forwarding-on-wsl2) for more details