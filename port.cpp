#include "port.h"

// constructor
Port::Port(String pattern) : Field(pattern, PORT) { }

bool Port::set_value(String val) {
	String *sub_strings;
	size_t size = 0;
	val.split("-", &sub_strings, &size); // check if val matches min-high
	if (size != RANGE_SEGMENT) {
		//size is 0 then sub_strings was not allocated
		if (size != 0) {
			delete[] sub_strings;
		}
		return false;
	}
	// getting the range of the ports
	this->range[0] = sub_strings[0].trim().to_integer();
	this->range[1] = sub_strings[1].trim().to_integer();
	delete[] sub_strings;
	if (range[0] > range[1])
		return false;
	return true;
}

bool Port::match_value(String val) const {
	int int_val = val.trim().to_integer();
	return ((int_val >= range[0]) && (int_val <= range[1]));
}