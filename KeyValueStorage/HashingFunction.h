#pragma once

// NOTE: should make it abstract
class HashingFunction
{
private:
	int modulus;

public:
	HashingFunction(int);
	~HashingFunction();

public:
	size_t compute(char*, const int);
};

