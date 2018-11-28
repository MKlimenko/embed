# `std::embed` implementation for the poor (C++17)

This repository contains an example implementation of the `std::embed` from the [P1040](https://wg21.link/p1040) proposal. There is an overview in the [blog post](https://mklimenko.github.io/english/2018/11/26/stdembed-for-the-poor/), feedback is highly appreciated.

## Usage

To distribute arbitrary resources with your application two steps are required:

1. Preprocess resources to create the corresponding header files.
2. Gather resources from the source code. 

## Building

There are two PowerShell scripts used to build and install the application and to remove it.

## Benchmark

One of the key concerns is the performance. I've benchmarked two corner cases:

1. One big file
2. Multiple small files

As a starting point I've measured the complete rebuild process on my PC (MSVC 15.9.2, i5-750, 12GB of RAM) and it took 3992 ms.

### Total rebuild times

Table for the one big file:

| File size 	| Build time, ms 	|
|:---------:	|:--------------:	|
|   1 byte  	|      4033      	|
|  8 bytes  	|      4423      	|
|  64 bytes 	|      3984      	|
| 512 bytes 	|      4197      	|
|    4 KB   	|      4393      	|
|   32 KB   	|      4843      	|
|   256 KB  	|      6431      	|
|    2 MB   	|      11436     	|
|   16 MB   	|      12912     	|

For the multiple small files:

| Number of 1 KB files 	| Build time, ms 	|
|:--------------------:	|:--------------:	|
|           1          	|      4400      	|
|           8          	|      5200      	|
|          64          	|      6236      	|
|          512         	|      23034     	|
|         1024         	|      61523     	|

The vast majority of the time is occupied by the link time, not the `rh::embed` itself.

### `rh::embed` times

To illustrate this, I've measured both the `rh::embed` performance and the total part of the whole process:

| File size 	| Embed time, ms 	| Percent of the whole rebuild time 	|
|:---------:	|:--------------:	|:---------------------------------:	|
|   1 byte  	|       59       	|                1.46               	|
|  8 bytes  	|       50       	|                1.13               	|
|  64 bytes 	|       56       	|                1.4                	|
| 512 bytes 	|       49       	|                1.11               	|
|    4 KB   	|       49       	|                1.01               	|
|   32 KB   	|       85       	|                1.32               	|
|   256 KB  	|       75       	|                1.16               	|
|    2 MB   	|       312      	|                2.7                	|
|   16 MB   	|      1796      	|                13.9               	|

| Number of 1 KB files 	| Embed time, ms 	| Percent of the whole rebuild time 	|
|:--------------------:	|:--------------:	|:---------------------------------:	|
|           1          	|       52       	|                1.18               	|
|           8          	|       62       	|                1.19               	|
|          64          	|       139      	|                2.22               	|
|          512         	|       844      	|                3.66               	|
|         1024         	|      1584      	|                2.5                	|


## Roadmap

- [ ] Compressing the resources
- [ ] Make the tool cross-platform (CMake?)
- [ ] Use the clang AST (scan the source files for the resources)