#pragma once

#include "resource.hpp"
#include "embedded_resources/resource_12073696463075507820.hpp"
#include "embedded_resources/resource_12244619635858790702.hpp"

namespace {
class ResourceHolder {
private:
	std::array<Resource, 2> resources {
		Resource(resource_12073696463075507820,	resource_12073696463075507820_path),
		Resource(resource_12244619635858790702,	resource_12244619635858790702_path),
	};

public:
	auto Gather(const std::string& file) const {
		auto it = std::find_if(resources.begin(), resources.end(), [file](const auto& lhs) {
			return lhs.GetPath() == file;
		});
		if (it == resources.end())
			throw std::runtime_error("Unable to detect resource with name " + file);
		
		return it->GetArray();
	}

	auto Gather(fs::path file) const {
		return Gather(file.string());
	}

	auto Gather(const char* file) const {
		return Gather(std::string(file));
	}

	auto ListFiles() const {
		std::vector<std::string> dst{};
		dst.reserve(resources.size());
		for (auto&el : resources)
			dst.push_back(el.GetPath());

		return dst;
	}

	auto FindByFilename(const std::string& file) const {
		std::vector<Resource> dst{};
		dst.reserve(resources.size());
		auto sought_file = fs::path(file).filename();
		std::copy_if(resources.begin(), resources.end(), std::back_inserter(dst), [sought_file](const auto& item) {
			return sought_file == fs::path(item.GetPath()).filename();
		});
		
		return dst;
	}

	auto FindByFilename(fs::path file) const {
		return FindByFilename(file.string());
	}

	auto FindByFilename(const char* file) const {
		return FindByFilename(std::string(file));
	}

	auto operator()(const std::string& file) const {
		return Gather(file);
	}

	auto operator()(fs::path file) const {
		return Gather(file);
	}

	auto operator()(const char* file) const {
		return Gather(std::string(file));
	}
};
}
