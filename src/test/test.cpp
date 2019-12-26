#include "resource_holder.hpp"

namespace rh {
	ResourceHolder embed;
}

int main() {
	auto data = rh::embed(R"(..\..\..\example\nmea.txt)");
	auto find = rh::embed.FindByFilename("nmea.txt");

	return 0;
}
