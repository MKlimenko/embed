#include "gtest/gtest.h"
#include "resource_holder.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace rh {
	ResourceHolder embed;

	auto GetNmeaPath() {
		namespace fs = std::filesystem;
		static auto absolute_path = fs::path(NMEA_FULL_PATH).make_preferred().string();
		return absolute_path;
	}
}

namespace {
	auto ReadFile(const std::string& filename) {
		auto file = std::ifstream(filename, std::ios::binary | std::ios::ate);
		if (!file)
			throw std::runtime_error("Unable to open file");
		std::size_t bytes = file.tellg();
		file.seekg(0);

		auto vec = std::vector<std::uint8_t>(bytes);
		file.read(reinterpret_cast<char*>(vec.data()), vec.size());

		return vec;
	}
}

TEST(embed_test, test_full_path) {
	auto data = rh::embed(rh::GetNmeaPath());
	auto vec = ReadFile(rh::GetNmeaPath());
	ASSERT_EQ(data.size(), vec.size());
	for (std::size_t i = 0; i < data.size(); ++i)
		ASSERT_EQ(data[i], vec[i]);
}

TEST(embed_test, test_find) {
	auto data_vec = rh::embed.FindByFilename("nmea.txt");
	ASSERT_EQ(data_vec.size(), 1);
	auto data = data_vec[0].GetArray();
	auto vec = ReadFile(rh::GetNmeaPath());
	ASSERT_EQ(data.size(), vec.size());
	for (std::size_t i = 0; i < data.size(); ++i)
		ASSERT_EQ(data[i], vec[i]);
}

TEST(embed_test, test_subfolders) {
	ASSERT_EQ(rh::embed.ListFiles().size(), 3);
	auto data_vec = rh::embed.FindByFilename("subdir_file.txt");
	ASSERT_EQ(data_vec.size(), 1);
}

struct PerformanceTestFixture : testing::TestWithParam<std::size_t> {
	static auto GetInputFolder() {
		auto subfolder = "input_for_" + std::to_string(GetParam());
		auto test_data_path = std::filesystem::current_path() / subfolder;
		return test_data_path;
	}
	static auto GetOutputFolder() {
		auto subfolder = "output_for_" + std::to_string(GetParam());
		auto test_data_path = std::filesystem::current_path() / subfolder;
		return test_data_path;
	}

	static inline auto file_size = 1024;

	virtual void SetUp() override {
		std::filesystem::create_directory(GetInputFolder());
		for (std::size_t i = 0; i < GetParam(); ++i) {
			std::ofstream out(GetInputFolder() / std::to_string(i), std::ios::binary);
			out.seekp(file_size - 1);
			out.write("", 1);
		}
		std::filesystem::create_directory(GetOutputFolder());
	}
	virtual void TearDown() override {
		std::filesystem::remove_all(GetInputFolder());
		std::filesystem::remove_all(GetOutputFolder());
	}
};

TEST_P(PerformanceTestFixture, performance_test) {
	auto input = GetInputFolder();
	auto output = GetInputFolder();
	auto command = std::string(EMBED_EXE_PATH) + ' ' + input.string() + " -o " + output.string() + " > nul";
	auto result = system(command.c_str());
	ASSERT_EQ(result, 0);
}

INSTANTIATE_TEST_SUITE_P(
	PerformanceTest,
	PerformanceTestFixture,
	testing::Values(1, 8, 64, 512, 1024, 8192)
);
