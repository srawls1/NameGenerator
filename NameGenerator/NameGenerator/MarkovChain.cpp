#include "stdafx.h"
#include "MarkovChain.h"
#include <cstdlib>


MarkovChain::MarkovChain(int numStates, int initialState, Matrix transitionProbabilities)
	: states(numStates, 1), probabilities(transitionProbabilities)
{
	states.setAt(initialState, 0, 1.f);
}


MarkovChain::~MarkovChain()
{
}

int MarkovChain::getCurrentState()
{
	float random = (float)rand() / RAND_MAX;
	float cumulativeProbability = 0.f;

	for (int i = 0; i < states.numRows(); ++i)
	{
		cumulativeProbability += states.getAt(i, 0);
		if (random < cumulativeProbability)
		{
			setCurrentState(i);
			return i;
		}
	}

	return -1;
}

void MarkovChain::setCurrentState(int state)
{
	for (int i = 0; i < states.numRows(); ++i)
	{
		states.setAt(i, 0, 0.f);
	}

	states.setAt(state, 0, 1.f);
}

void MarkovChain::transitionStates(int numSteps)
{
	Matrix transitionProbabilities(identity(states.numRows()));
	for (int i = 0; i < numSteps; ++i)
	{
		transitionProbabilities = transitionProbabilities * probabilities;
	}

	states = transitionProbabilities * states;
}