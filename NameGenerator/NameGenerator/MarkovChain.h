#pragma once

#include "Matrix.h"

class MarkovChain
{
private:
	Matrix states;
	Matrix probabilities;
	int currentState;

private:
	void setCurrentState(int state);

public:
	MarkovChain(int numStates, int initialState, Matrix transitionProbabilities);
	~MarkovChain();

	int getCurrentState();
	void transitionStates(int numSteps = 1);
};

