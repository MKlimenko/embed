#pragma once

#include "saver.hpp"

#include <algorithm>
#include <execution>
#include <fstream>

namespace fs = std::filesystem;

class Embed {
private:
	Saver saver;

	void Save(fs::path entry, bool root_is_directory = false) {
		if (fs::is_directory(entry)) {
			if (root_is_directory)
				return;
			std::vector<fs::path> files;
			for (auto& el : fs::recursive_directory_iterator(entry))
				if (!el.is_directory())
					files.push_back(el.path());
			std::for_each(std::execution::par_unseq, files.begin(), files.end(),
				[this](auto& el) {Save(el, true); });
		}
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
		std::for_each(std::execution::par_unseq, entries.begin(), entries.end(),
			[this](auto& entry) { Save(entry); }
		);
	}
};
