#include <cstring>
#include <cstdlib>
#include "string.h"
#include "ip.h"

using namespace std;

// Empty constructor
String::String() {
	this->length = 0;
	this->data = NULL;
}

// Copy constructor
String::String(const String &str) {
	this->length = str.length;
	if (!this->length) {
		this->data = NULL;
	} else {
		this->data = new char[length + 1];
		if (!this->data) {
			cout << "Error allocating the string" << endl;
		} else {
			strcpy(this->data, str.data);	
		}
	}
}

// constructor
String::String(const char *str) {
	// check for nullptr
	if (!str) {
		this->data = NULL;
		this->length = 0;
	}
	this->length = strlen(str);
	// if empty string return
	if (!this->length) {
		this->data = NULL;
	} else {
		this->data = new char[this->length + 1];
		// check if allocation failed
		if (!this->data) {
			cout << "Error allocating the string" << endl;
		} else {
			strcpy(this->data, str);	
		}	
	}
	
}

// destructor
String::~String() {
	this->length = 0;
	if (this->data)
		delete[] this->data;
}

String& String::operator=(const String &rhs) {
	this->length = rhs.length;
	// free previous string
	if (this->data) {
		delete[] this->data;
	}
	// check if rhs is empty
	if (!this->length) {
		this->data = NULL;
	} else {
		this->data = new char[this->length];
		// check if allocation failed
		if (!this->data) {
			cout << "Error allocating the string" << endl;
			this->length = 0;
		} else {
			strcpy(this->data, rhs.data);	
		}
	}
	return *this;
}

String& String::operator=(const char *str) {
	this->length = strlen(str);
	// free previous string
	if (this->data) {
		delete[] this->data;
	}
	// check if str in nullptr
	if (!str) {
		this->data = NULL;
		this->length = 0;
		return *this;
	}
	// check if rhs is empty
	if (!this->length) {
		this->data = NULL;
	} else {
		this->data = new char[this->length + 1];
		// check if allocation failed
		if (!this->data) {
			cout << "Error allocating the string" << endl;
			this->length = 0;
		} else {
			strcpy(this->data, str);	
		}
	}
	return *this;
}


bool String::equals(const String &rhs) const {
	return (this->length == rhs.length && strcmp(this->data, rhs.data) == 0);
}

bool String::equals(const char *rhs) const {
	if (!rhs)
		return false;
	return (this->length == strlen(rhs) && strcmp(this->data, rhs) == 0);
}

void String::split(const char *delimiters, String **output, size_t *size) const {
	if (!size)
		return;

	int sub_strings_size = 1, num_of_delimiters = strlen(delimiters);

	*size = 0;

	if (!delimiters || !output || !this->data)
		return;

	// Calculating the number of sub-strings of this->data, sub-strings are seperated by any character in delimiters
	for (int i = 0; i < (int) this->length; i++)
		for (int d = 0; d < num_of_delimiters; d++)
			if (this->data[i] == delimiters[d])
				sub_strings_size++;

	// Setting the size to the calculated value above
	*size = sub_strings_size;
	*output = new String[*size];
	int substr_idx = 0; // Index of the next substring to insert
	int start_str_idx = 0; // Index of the start of the next substring 

	for (int i = 0; i < (int) this->length; i++) {
		for (int d = 0; d < num_of_delimiters; d++) {
			if (this->data[i] == delimiters[d]) {
				// Calculating the substring borders and creating a copy of it and inserting it to *output
				if (i == start_str_idx) {
					(*output)[substr_idx] = String("");
				} else {
					char* new_str = new char[i - start_str_idx];
					strncpy(new_str, &this->data[start_str_idx], i - start_str_idx);
					new_str[i - start_str_idx] = (char) 0;
					(*output)[substr_idx] = String(new_str);
				}
				start_str_idx = i + 1;
				substr_idx++;
			}
		}
	}
	if (start_str_idx < (int) this->length) {
		(*output)[substr_idx] = String(&this->data[start_str_idx]);
	} else {
		(*output)[substr_idx] = String("");
	}
	
	// This piece of code, creates a new array of String, in which, all Strings are longer than 0
	// It also updates the *output and *size to the new values
	String* new_output = NULL;
	int new_size = 0;
	for (int i = 0; i < (int) *size; i++)
		if ((*output)[i].getData())
			new_size++;
	
	new_output = new String[new_size];
	int new_indx = 0;
	for (int i = 0; i < (int) *size; i++) {
		if ((*output)[i].getData()) {
			(new_output)[new_indx] = (*output)[i];
			new_indx++;
		}
	}
	delete[] (*output);
	*size = new_size;
	*output = new_output;

	return;
}

int String::to_integer() const {
	/* converting String to int, by spliting the String with "." delimiters
	*/
	int int_res = 0;
	String* sub_strings;
	size_t size = 0;
	this->split(".", &sub_strings, &size);
	// if this->data matches xxx.xxx.xxx.xxx parse as IP 
	if (size == SEGMENTS) {
		for (int i = 0; i < SEGMENTS; i++) {
			int xxx = sub_strings[i].trim().to_integer();
			if (xxx > 255 || xxx < 0) {
				delete[] sub_strings;
				return 0;
			}
			int_res |= xxx << (24 - (8 * i));
		}
	// parse as integer
	} else {
		int_res = atoi((this->trim()).data);
		if (int_res != 0) {
			if (sub_strings)
				delete[] sub_strings;
			return int_res;
		}
	}
	if (sub_strings)
		delete[] sub_strings;
	return int_res;
}

String String::trim() const {
	int first = 0, last = this->length - 1;
	while (this->data[first] == ' ' && first < last) {
		first++;
	}
	while (this->data[last] == ' ' && last > first) {
		last--;
	}
	// building new String that doesn't have leading or trailing white spaces
	char *new_str = new char[last - first + 1 + 1];
	strncpy(new_str, &this->data[first], last - first + 1);
	new_str[last - first + 1] = (char) 0;
	return String(new_str);
}