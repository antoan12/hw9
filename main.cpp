#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"

using namespace std;

extern int check_args(int, char**);
extern void parse_input(Field&);

int main(int argc, char **argv) {
	// getting the input argument and parsing it into the String
	String filter(argv[1]);
	String *substrs;
	size_t size = 0;
	filter.split("=", &substrs, &size);

		// parsing Ip )
	if (substrs[0].trim().equals("src-ip") || substrs[0].trim().equals("dst-ip")) {
		Ip ip_filter(substrs[0].trim()); // initialize Ip with name substrs[0].trim()
		ip_filter.set_value(substrs[1].trim()); //set the value of the Ip filter to match the mask and IP received
		parse_input(ip_filter);
	}
	// parsing Port 
	if (substrs[0].trim().equals("src-port") || substrs[0].trim().equals("dst-port")) {
		Port port_filter(substrs[0].trim()); // initialize Port with name substrs[0].trim()
		port_filter.set_value(substrs[1].trim()); //set the value of the Ip filter to the port range
		parse_input(port_filter);
	}
	delete[] substrs;
	return 0;
}