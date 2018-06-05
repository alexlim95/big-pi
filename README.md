# big-pi

This project steps through computing and printing the first thousand decimal places of pi as well as the first million decimal places of pi.

## Background - The Borwein Algorithm ##

This program will derive the necessary correct digits of pi using the Borwein algorithm which calculates the value of 1/pi. There are several iterative algorithms which have difference convergence rates. This repository consists of two examples: quartic convergence and nonic convergence.

**Quartic Convergence** converges quartically against 1/pi (i.e. each iteration approximately quadruples the number of correct digits).

**Nonic Convergence** converges nonically to 1/pi (i.e. each iteration approximately multiplies the number of correct digits by nine).

More information about the Borwein algorithm can be found [here](https://en.wikipedia.org/wiki/Borwein%27s_algorithm)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

We will be using Linux (Ubuntu 16.04.3 LTS) which can be downloaded [here](https://www.ubuntu.com/download/desktop). Other operating systems may possibly be used but will not be covered in this tutorial. Ubuntu was ran on VirtualBox which can be download [here](https://www.virtualbox.org/wiki/Downloads).

We will also be working with the Multiple Precision Integers and Rationals (MPIR) library which is a portable library written in C for arbitrary precision arithmetic on integers, rational numbers, and floating-point numbers. It aims to provide the fastest possible arithmetic for all applications that need higher precision than is directly supported by the basic C types.

We will be using the MPIR 3.0.0 version which can be downloaded [here](http://mpir.org/downloads.html) along with its [documentation](http://mpir.org/mpir-3.0.0.pdf).

### Build And Install The Library

The mpir-3.0.0 folder extracted from the mpir-3.0.0.zip file contains the necessary C source files and several shell scripts to get started. You can run the scripts on a Linux system in a bash terminal window.

First open a terminal window and change directories to the mpir-3.0.0 folder. For example, my mpir-3.0.0 folder was on my Desktop.

```
cd Desktop/mpir-3.0.0
```

Next, run the **configure** script which checks your system for necessary utility programs and generates the makefiles. Then, run **make** which uses the generated makefiles to compile the C source files and build the library.

```
./configure
make
```

**(Optional)** On some systems, you may get a error message saying that a system-wide yasm is not found or no usable m4 found $PATH for /usr/5bin. Some additional packages may need to be installed such as the **yasm** assembler/disassembler for Intel x86 architecture and the **m4** macro processor.

```
sudo apt-get update && sudo apt-get dist-upgrade -y
sudo apt-get install yasm
sudo apt-get install m4
```

Some self-tests can be run with **make check** which compiles and runs test programs to verify that you properly built the library.

```
make check
```

Finally, run **make install** to install the MPIR library **libmpir*** (several files) and its header file **mpir.h** in the standard locations **/usr/local/lib** and **/usr/local/include**, respectively.

```
make install
```

## Compiling Your Program ##

In order to compile and run your program **BigPi.cpp** on the command line:

```
g++ -std=c++11 BigPiThousandNonic.cpp -lmpir -o BigPiThousandNonic
./BigPiThousandNonic
```

The **-lmpir** specifies using the MPIR library.

## Acknowledgments

* MPIR documentation
