#include "ContactResolverIterator.h"

void ContactResolverIterator::resolveContacts(vector<ContactResolver*> contacts) {
	current_iterations = 0;
	while (current_iterations < max_iterations) {
		if (contacts.empty()) return;

		for (int i = 0; i < contacts.size(); i++) {
			if (contacts[i]->getSeparatingSpeed() >= 0 && contacts[i]->overlapDepth <= 0) {
				return;
			}
		}

		unsigned int current_index = 0;

		float current_min = contacts[0]->getSeparatingSpeed();
		for (unsigned int i = 1; i < contacts.size(); i++) {
			if (contacts[i]->getSeparatingSpeed() < current_min) {
				current_index = i;
				current_min = contacts[i]->getSeparatingSpeed();
			}
		}

		if (current_min >= 0) {
			return;
		}

		contacts[current_index]->resolve();
		current_iterations++;
	}
}