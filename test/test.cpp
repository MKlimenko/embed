#include "gtest/gtest.h"
#include "resource_holder.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

namespace rh {
	ResourceHolder embed;
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
	auto data = rh::embed(NMEA_FULL_PATH);
	auto vec = ReadFile(NMEA_FULL_PATH);
	ASSERT_EQ(data.size(), vec.size());
	for (std::size_t i = 0; i < data.size(); ++i)
		ASSERT_EQ(data[i], vec[i]);
}

TEST(embed_test, test_find) {
	auto data_vec = rh::embed.FindByFilename("nmea.txt");
	ASSERT_EQ(data_vec.size(), 1);
	auto data = data_vec[0].GetArray();
	auto vec = ReadFile(NMEA_FULL_PATH);
	ASSERT_EQ(data.size(), vec.size());
	for (std::size_t i = 0; i < data.size(); ++i)
		ASSERT_EQ(data[i], vec[i]);
}
