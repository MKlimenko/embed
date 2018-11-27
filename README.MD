# `std::embed` implementation for the poor (C++17)

This repository contains an example implementation of the `std::embed` from the [P1040](https://wg21.link/p1040) proposal. There is an overview in the [blog post](https://mklimenko.github.io/english/2018/11/26/stdembed-for-the-poor/), feedback is highly appreciated.

## Usage

To distribute arbitrary resources with your application two steps are required:

1. Preprocess resources to create the corresponding header files.
2. Gather resources from the source code. 

## Building

There are two PowerShell scripts used to build and install the application and to remove it.

## Roadmap

- [ ] Compressing the resources
- [ ] Make the tool cross-platform (CMake?)
- [ ] Use the clang AST (scan the source files for the resources)