import os
import shutil
import time

cwd = os.getcwd()
def NumerousFiles(benchmark_data_folder, embed_data_folder, test_file_wildcard):
    size_kb = 1
    number_of_files = 1
    while number_of_files <= 1024:
        shutil.rmtree(benchmark_data_folder, ignore_errors=True)
        shutil.rmtree(embed_data_folder, ignore_errors=True)
        os.makedirs(benchmark_data_folder, exist_ok=True)
        os.system('cmake --build . --target embed --config Release --clean-first')
        for i in range (1, number_of_files + 1):
            cur_fule = f"{test_file_wildcard}{i}.bin"
            with open(cur_fule, "wb") as out:    
                out.truncate(size_kb * 1024)
        start = time.time()
        os.system('cmake --build . --target embed_benchmark --config Release')
        stop = time.time()
        current_time = 1000 * (stop - start)
        print(f"{number_of_files} files: {current_time}")
        number_of_files *= 2

def SingleFile(benchmark_data_folder, embed_data_folder, test_file_wildcard):
    size_b = 1
    while size_b <= 16 * 1024 * 1024:
        shutil.rmtree(benchmark_data_folder, ignore_errors=True)
        shutil.rmtree(embed_data_folder, ignore_errors=True)
        os.makedirs(benchmark_data_folder, exist_ok=True)
        os.system('cmake --build . --target embed --config Release --clean-first')
        cur_fule = f"{test_file_wildcard}.bin"
        with open(cur_fule, "wb") as out:    
            out.truncate(size_b)
        start = time.time()
        os.system('cmake --build . --target embed_benchmark --config Release')
        stop = time.time()
        current_time = 1000 * (stop - start)
        print(f"{size_b} bytes: {current_time}")
        size_b *= 8

try:
    script_location = os.path.realpath(__file__ + '/../')
    build_folder = script_location + '/build'
    shutil.rmtree(build_folder, ignore_errors=True)
    os.makedirs(build_folder, exist_ok=True)
    os.chdir(build_folder)
    benchmark_data_folder = script_location + '/benchmark_data/'
    embed_data_folder = script_location + '/benchmark/embedded_resources'
    shutil.rmtree(benchmark_data_folder, ignore_errors=True)
    shutil.rmtree(embed_data_folder, ignore_errors=True)
    os.system('cmake -DBYPASS_TESTS=1 -DENABLE_BENCHMARK=1 ..')
    os.system('cmake --build . --target embed --config Release')
    start = time.time()
    os.system('cmake --build . --target embed_benchmark --config Release')
    stop = time.time()
    pure_time_seconds = 1000 * (stop - start)
    print(f"No data: {pure_time_seconds}")

    test_file_wildcard = benchmark_data_folder + 'test_'
    NumerousFiles(benchmark_data_folder, embed_data_folder, test_file_wildcard)
    SingleFile(benchmark_data_folder, embed_data_folder, test_file_wildcard)

    shutil.rmtree(benchmark_data_folder, ignore_errors=True)
    shutil.rmtree(embed_data_folder, ignore_errors=True)

except (RuntimeError, TypeError, NameError) as e:
    print(f"Unexpected {e=}, {type(e)=}")

os.chdir(cwd)