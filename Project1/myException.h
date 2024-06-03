#pragma once
#include<exception>

class ReadFailException : public std::exception {
public:
	explicit ReadFailException(char const* messeage) : exception(messeage) {};
};

class WriteFailException : public std::exception {
public:
	explicit WriteFailException(char const* messeage) : exception(messeage) {};
};