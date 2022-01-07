# `std::embed` implementation for the poor (C++17)

This repository contains an example implementation of the `std::embed` from the [P1040](https://wg21.link/p1040) proposal. There is an overview in the [blog post](https://mklimenko.github.io/english/2018/11/26/stdembed-for-the-poor/), feedback is highly appreciated.

## Usage

To distribute arbitrary resources with your application two steps are required:

1. Preprocess resources to create the corresponding header files.
2. Gather resources from the source code. 

## Building

Use CMake to build `rh::embed` itself, tests and benchmark. Tests are enabled by default, use `-DBYPASS_TESTS=1` to disable them, benchmark, on the other hand, is disabled. To enable benchmark build use `-DENABLE_BENCHMARK=1`.

## Benchmark

One of the key concerns is performance. I've benchmarked two corner cases:

1. One big file
2. Multiple small files

As a starting point, I've measured the complete rebuild process on my PC (MSVC 17.0.4, Ryzen 3700X, 32GB of RAM) with the bare time of 1390 ms. For the sake of history and comparison, there's also data for my older PC (MSVC 15.9.2, i5-750, 12GB of RAM) with a baseline of 3992 ms.

### Total rebuild times

Table for the one big file:

| File size     | Build time, ms, WSL   | Build time, ms, Windows   | Build time, ms, Old PC    |
|:---------:    |:-------------------:  |:-----------------------:  |:----------------------:   |
|   1 byte      |         479           |           1413            |          4033             |
|  8 bytes      |         471           |           1412            |          4423             |
|  64 bytes     |         482           |           1390            |          3984             |
| 512 bytes     |         491           |           1402            |          4197             |
|    4 KB       |         485           |           1413            |          4393             |
|   32 KB       |         503           |           1421            |          4843             |
|   256 KB      |         708           |           1548            |          6431             |
|    2 MB       |         2645          |           2688            |          11436            |
|   16 MB       |        19234          |          11748            |          12912            |

For the multiple small files:

| Number of 1 KB files  | Build time, ms, WSL   | Build time, ms, Windows   | Build time, ms, Old PC    |
|:--------------------: |:-------------------:  |:-----------------------:  |:----------------------:   |
|           1           |         473           |           1386            |          4400             |
|           8           |         485           |           1422            |          5200             |
|          64           |         587           |           1587            |          6236             |
|          512          |         1268          |           3309            |          23034            |
|         1024          |         2049          |           8601            |          61523            |

The vast majority of the time is occupied by the link time, not the `rh::embed` itself.

### `rh::embed` times

> N.B. These times were measured on my old PC, they're roughly the same on my new one, so I decided to leave this part as is.

To illustrate this, I've measured both the `rh::embed` performance and the total part of the whole process:

| File size     | Embed time, ms    | Percent of the whole rebuild time     |
|:---------:    |:--------------:   |:---------------------------------:    |
|   1 byte      |       59          |                1.46                   |
|  8 bytes      |       50          |                1.13                   |
|  64 bytes     |       56          |                1.4                    |
| 512 bytes     |       49          |                1.11                   |
|    4 KB       |       49          |                1.01                   |
|   32 KB       |       85          |                1.32                   |
|   256 KB      |       75          |                1.16                   |
|    2 MB       |       312         |                2.7                    |
|   16 MB       |      1796         |                13.9                   |

| Number of 1 KB files  | Embed time, ms    | Percent of the whole rebuild time     |
|:--------------------: |:--------------:   |:---------------------------------:    |
|           1           |       52          |                1.18                   |
|           8           |       62          |                1.19                   |
|          64           |       139         |                2.22                   |
|          512          |       844         |                3.66                   |
|         1024          |      1584         |                2.5                    |


## Roadmap

- [x] Make the tool cross-platform (CMake)
- [ ] Add CPack scripts for the proper installation
- [ ] Compressing the resources
- [ ] Use the clang AST (scan the source files for the resources)