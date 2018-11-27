#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <functional>
#include "span.hpp"
#include <tuple>

class Resource {
private:
	const tcb::span<const std::uint8_t> arr_view;
	const std::string_view path;

public:
	using EmbeddedData = tcb::span<const std::uint8_t>;

	template <std::size_t sz>
	constexpr Resource(const std::array<std::uint8_t, sz>& arr_, const char* path_) : arr_view(arr_), path(path_) {}
	Resource(const std::vector<std::uint8_t>& vec_, std::string_view path_) : arr_view(vec_), path(path_) {}

	constexpr auto GetArray() const {
		return arr_view;
	}

	constexpr auto GetPath() const {
		return path;
	}
};
