# Boson Native -V2

|GitHub CI|
|:-:|
|[![CI](https://github.com/trinity-tech-io/Boson.Native/actions/workflows/cmake.yml/badge.svg)](https://github.com/trinity-tech-io/Boson.Native/actions/workflows/cmake.yml)|

Boson is a decentralized and encrypted peer-to-peer (P2P)  communication framework that facilitates network traffic routing between virtual machines and decentralized Applications (dApps).  Boson Native is a C++ version of the distribution that runs efficiently on native machines such as **macOS**, **Linux**, and mobile devices like **iOS** and **Android** systems. And the version for **Windows** still under  development.

Boson is a new two-layered architecture that features a unified DHT network as the bottom layer and facilitates various application-oriented services on top of the DHT network, where a list of services includes, but is not limited to:

- An active proxy service forwards the service entries from third-parties originally located within a LAN network, making them accessible from the public;

**Notice**:  *the later two features have not been developed yet, but they are already included in the TODO List*.

## Guide to compiling and building to Boson Native

### 1. CMake Usage

The Boson project is built, tested, and packaged using CMake. A certain level of knowledge of CMake is required to effectively use this build system.

As of the time of writing, the source code can be compiled on **macOS** and **Linux** distributions such as Ubuntu and Debian. It also provides the options to cross-compile for the target platform of **iOS**. However, compiling for **Windows**, **Android**, and **Raspberry** devices is undergoing.

### 2. Pre-Installation of Dependencies

To generate Makefiles and manage project dependencies using the **configure** or **cmake** command, certain packages should be preinstalled on the host machine before compilation.

Consider the following commands to install the necessary packages on Linux system:

```shell
$ sudo apt-get update
$ sudo apt-get install -f build-essential autoconf automake autopoint libtool cmake libncurses-dev
```

Download this repository using Git:

```
git clone https://github.com/trinity-tech-io/Boson.Native
```

### 3. Build for Host systems: Ubuntu / Debian Linux / macOS

To compile the project from its source code and run it on `Ubuntu`, `Debian` and `macOS` host systems, please follow these steps listed below:

Open a new terminal window and navigate to the directory with the source code downloaded:

```shell
$ cd YOUR-PATH/Boson.Native
```

Next, create a directory within the **build** directory and name it according to your preference (we suggest to use the target platform name), then switch to use it as your working directory.:

```shell
$ cd build
$ mkdir macos-${uname -m}
$ cd macos-${uname -m}
```

Next, generate the project's `Makefile` files and compile them by running the commands below:

```shell
$ cmake ../..
$ make && make install
```

***Notice***: *To generate `Makefile` files according to your requirements, you may need to specify several CMake options listed below*:

- ***CMAKE_INSTALL_PREFIX*** - use this option to specify the directory where the generated libraries and header files will be installed.
- ***ENABLE_BOSON_DEVELOPEMENT*** -  enable this option to build the distribution for developement enviroment. Otherwise, it will build for production enviroment by default.
- **DCMAKE_BUILD_TYPE**  - use this option to build a distribution of either **Debug** or **Release **type.

*Here is an example of the command with all options included:*

```shell
$ cmake -DCMAKE_INSTALL_PREFIX=dist -DENABLE_BOSON_DEVELOPMENT=TRUE -DCMAKE_BUILD_TYPE=Debug ../..
```

### 4. Cross-Compiling for iOS: A Comprehensive Guide

Boson Native can be cross-compiled to run on iOS platform, and the compilation process is carried out on a MacOS host with XCode. Before proceeding, ensure that your MacOS version is 9.0 or higher.

The extra *CMake* options listed below would be required to build distribution for iOS platform:

- ***IOS_PLATFORM*** - use this option and specify the value of either **iphoneos** or **iphonesimulator** to indicate the target platform for distribution. Use the **iphoneos** option for iPhone mobile devices, and  the **iphonesimulator** option for the iPhone simulator.
- ***CMAKE_TOOLCHAIN_FILE*** - use this option to specifiy the toolchain to use for this building, and commend to use the value `../../cmake/iOSToolchain.cmake` here.

So, recommend you to use the following commands to build a distribution for iphone device under the directory of source code downloaded:

```shell
$ cd build
$ mkdir iphoneos
$ cd iphoneos
$ cmake -DCMAKE_INSTALL_PREFIX=dist -DIOS_PLATFORM=iphoneos -DCMAKE_TOOLCHAIN_FILE=../../cmake/iOSToolchain.cmake -DENABLE_BOSON_DEVELOPMENT=TRUE ../..
$ make && make install
```

After executing the whole series of commands, the libraries and headers will be installed under the directory  `build\iphoneos\dist` , and check the generated libraries by using the commands below:

```shell
$ cd dist
$ lipo -info lib/libboson.a
Non-fat file: lib/libboson.a is architecture: arm64
```

***Notice***: *Currently, only cross-compilation for the iOS platform is supported. However, cross-compilation for the Android platform is on the TODO list and will be added soon.*

### 5. Running Test Cases: Best Practices

As part of the compilation process, a series of test cases is built. Running these test cases is an effective way to gain a deeper understanding of both the internal modules and the public APIs.

Use the following command to run all of the testcases:

```shell
$ ./tests/apitests/apitests
```

***Notice**: The testcases need to be run with the compilation option -**DENABLE_BOSON_DEVELOPMENT**.*

### 6.  API document for Developers

The API documentation is currently lacking and it has been added to the TODO list, please stay tune for updates.


## Contribution

We welcome contributions from passionate developers from open-source community who aspire to create a secure, decentralized communication platform and help expand the capabilities of Boson to achieve wider adoption.

## Acknowledgments

A sincere thank you goes out to all the projects that we rely on directly or indirectly, for their contributions to the development of Boson Project. We value the collaborative nature of the open-source community and recognize the importance of working together to create innovative, reliable software solutions.

## License

This project is licensed under the terms of the [MIT License](https://github.com/trinity-tech-io/Boson.Native/blob/master/LICENSE). We believe that open-source licensing  promotes transparency, collaboration, and innovation, and we encourage others to contribute to the project in accordance with the terms of the license.
