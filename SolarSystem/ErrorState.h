#ifndef ERROR_STATE_H
#define ERROR_STATE_H

class ErrorState {
public:
	ErrorState() : errorStatus(0), errorString("") {}
	const unsigned int getErrorStatus();
	const std::string getErrorString();
private:
	unsigned int errorStatus;
	std::string errorString;
};

#endif // ERROR_STATE_H