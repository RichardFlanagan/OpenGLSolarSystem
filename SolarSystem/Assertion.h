/*
File: Assertion.h
Author: Richard Flanagan
Description:
*/
#ifndef ASSERTION_H
#define ASSERTION_H

#include <string>
#include <assert.h>

/*
	Static method used for making assertions, and passing an error message if they fail.
*/
static void ASSERTION(bool conditionResult, std::string errorMessage){
	assert((0, errorMessage.c_str()));
}

#endif // ASSERTION_H