#pragma once
#include <vector>
#include "ContactResolver.h"
using namespace std;

class ContactResolverIterator
{
public:
	ContactResolverIterator() {}
	ContactResolverIterator(unsigned _maxIterations) : max_iterations(_maxIterations) {}
	void resolveContacts(vector<ContactResolver*> contacts);

	unsigned max_iterations;
protected:
	unsigned current_iterations = 0;
};