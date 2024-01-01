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
