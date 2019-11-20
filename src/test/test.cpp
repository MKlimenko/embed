#include "resource_holder.hpp"

namespace rh {
	ResourceHolder embed;
}

int main() {
	auto data = rh::embed(fs::path(R"(..\..\..\example\nmea.txt)"));
	auto data_path = rh::embed(fs::path(R"(../../../example/nmea.txt)"));
	
	return 0;
}
