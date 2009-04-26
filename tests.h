#ifndef __TESTS_H__
#define __TESTS_H__

#include <string>
#include <iostream>
#include "library1.h"

#define SPACES "                                        "

using namespace std;

string stat2str(StatusType stat) {
	switch ( stat ) {
		case ALLOCATION_ERROR	:	return "ALLOCATION_ERROR";
		case INVALID_INPUT		:	return "INVALID_INPUT";
		case SUCCESS			:	return "SUCCESS";
		case FAILURE			:	return "FAILURE";
		default					:	return "\033[31mUNDEFINED\033[0m";
	}
}

void expect(string message, StatusType exp, StatusType result) {
	const unsigned int len = 40;
	message += ":";
	while(message.length() < len) {
		message += " ";
	}
	if (result == exp) cout << "\t" << message << "\033[32mOK\033[0m\t\t" + stat2str(result) << endl;
	else cout << "\t" << message << "\033[31mFAIL\033[0m\t\t" + stat2str(result) << endl;
}



#endif /* __TESTS_H__ */

