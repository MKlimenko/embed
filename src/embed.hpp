#pragma once

#include "saver.hpp"

#include <fstream>

namespace fs = std::filesystem;

class Embed {
private:
	Saver saver;

	void Save(fs::path entry) {
		if (fs::is_directory(entry))
			for (auto&el : fs::recursive_directory_iterator(entry))
				Save(el);
		else {
			if (!fs::exists(entry))
				throw std::runtime_error("No such file:" + entry.string());
			std::ifstream inf(entry.string(), std::ios::binary);
			std::vector<std::uint8_t> data(fs::file_size(entry));

			inf.read(reinterpret_cast<char*>(data.data()), data.size());
			saver.Save(data, entry);
		}
	}

public:
	Embed() noexcept : Embed(".") {}
	Embed(fs::path call_folder) noexcept :
		saver(fs::is_regular_file(call_folder) ? call_folder.parent_path() : call_folder) 
	{}

	void SaveAll(tcb::span<std::string> entries) {
		for (auto&entry : entries)
			Save(entry);
	}
};
