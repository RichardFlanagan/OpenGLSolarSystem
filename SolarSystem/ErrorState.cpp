#include <string>
#include "ErrorState.h"

const unsigned int ErrorState::getErrorStatus() {
	return errorStatus;
}
const std::string ErrorState::getErrorString() {
	return errorString;
}