#pragma once

#include "Matrix.h"

class MarkovChain
{
private:
	Matrix states;
	Matrix probabilities;

public:
	MarkovChain(int numStates, int initialState, Matrix transitionProbabilities);
	~MarkovChain();

	int getCurrentState();
	void setCurrentState(int state);
	void transitionStates(int numSteps = 1);
};

