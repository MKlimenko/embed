clear; clc; close all;

data_size_1_file = [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, ];
time_seconds_1_file = [4.2458712, 4.4737242, 4.4009209, 4.38499, 4.5056807, 4.5302156, 4.5185401, 4.4358826, 4.4410697, 4.5782725, 4.5071241, 4.5385873, 4.425545, 4.4826812, 4.4950508, 4.6179142, 4.664116, 4.8352709, 5.2451348, 5.4529658, 5.7756434, 6.4708188, 7.8748273, 10.6388606, 16.8013819, 43.9626009, 557.6133586, ];

figure
plot(log2(data_size_1_file), time_seconds_1_file)
grid
title('Benchmark results, one big file')
xlabel('Size of embedded data file, log2(bytes)')
ylabel('Time, seconds')

data_size_multiple_1kb_files = [0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024];
time_seconds_multiple_1kb_files = [4.3570112, 4.2996338, 4.3283141, 4.4510958, 4.595591, 4.6952979, 5.0675485, 5.4167353, 6.2087777, 8.1538394, 13.841897, 38.5579338];

figure
plot(log2(data_size_multiple_1kb_files), time_seconds_multiple_1kb_files)
grid
title('Benchmark results, multiple 1 KB files')
xlabel('Number of files, log2(N)')
ylabel('Time, seconds')