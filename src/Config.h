#include <string>

class Config {
	public:
		float phi;
		float version;
		std::string versionType;
	
		Config() {
			phi = 1.618033988749895f;
			version = 0.1f;
			versionType = "Alpha";
		}
};