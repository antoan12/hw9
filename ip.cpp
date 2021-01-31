#include "ip.h"

using namespace std;

// constructor
Ip::Ip(String pattern) : Field(pattern, IP) { }

bool Ip::set_value(String val) {
	String *sub_strings;
	size_t size = 0;
	val.split("/", &sub_strings, &size); // check if val matches XXX.XXX.XXX.XXX/mask
	if (size != MASK_SEGMENT) {
		//size is 0 then sub_strings was not allocated
		if (size != 0) {
			delete[] sub_strings;
		}
		return false;
	} else {
		//val matches XXX.XXX.XXX.XXX/mask
		int ip = sub_strings[0].trim().to_integer(); // extracting the ip from val
		int bits_to_ignore = 32 - sub_strings[1].trim().to_integer(); //extracting the number of lower bits to ignore from val
		delete[] sub_strings;
		if (bits_to_ignore > 32 || bits_to_ignore < 0)
			return false;
		unsigned int bitmask = (bits_to_ignore == 32) ? 0xFFFFFFFF : ((unsigned int) 1 << bits_to_ignore) - 1; // n lower bits are set to 1
		this->low = ip & (~bitmask); // minimum ip
		this->high = ip | bitmask; //maximum ip
		return true;
	}
}

bool Ip::match_value(String val) const {
	
	unsigned int int_val = (unsigned int) val.trim().to_integer();
	return ((low <= int_val) && (high >= int_val));
}