#include "field.h"
#include "ip.h"
#include "port.h"

using namespace std;
// constructor
Field::Field(String pattern, field_type type) {
	this->pattern = pattern;
	this->type = type;
}

// constructor
Field::Field(String pattern) {
	this->pattern = pattern;
	this->type = GENERIC;
}

// constructor
Field::~Field() {
}

field_type Field::get_type() const {
	return this->type;
}

// override by Ip and Port
bool Field::set_value(String val) {
	switch(this->type) {
		case IP:
			return ((Ip*)this)->set_value(val);
		case PORT:
			return ((Port*)this)->set_value(val);
		default:
			break;
	}
	return false;
}

// override by Ip and Port
bool Field::match_value(String val) const {
	switch(this->type) {
		case IP:
			return ((Ip*)this)->match_value(val);
		case PORT:
			return ((Port*)this)->match_value(val);
		default:
			break;
	}
	return false;
}


bool Field::match(String packet) {
	bool res = false;
	String *sub_packet;
	size_t size = 0;
	packet.split(",", &sub_packet, &size); //spliting by "," hence, we can check if we received a packet
	if (!size)
		return false;
	for (int i = 0; i < (int) size; i++) {
		size_t expected_size = 0;
		String *substrs;
		sub_packet[i].split("=", &substrs, &expected_size);
		if (expected_size == 0)
			continue;
		if (expected_size == 2) {
			if (this->pattern.trim().equals(substrs[0].trim())) {
				// depends on the implementation in the sub-classes, Ip and Port
				res = this->match_value(substrs[1].trim());
			}
		}
		// free substrs
		delete[] substrs;
	}
	// free sub_Strings to prevent memory leak
	delete[] sub_packet;
	return res;
}