#include "resource_holder.hpp"

int main() {
	auto data = rh::embed(R"(..\..\..\example\nmea.txt)");
	
	return 0;
}
