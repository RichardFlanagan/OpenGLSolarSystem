#include <string>
#include <assert.h>

static void ASSERTION(bool conditionResult, std::string errorMessage){
	assert((0, errorMessage.c_str()));
}