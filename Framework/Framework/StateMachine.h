#pragma once

#include <memory>
#include <stack>
#include "State.h"

// The StateMachine class is just a simple wrapper around a std::stack which handles transitioning between states.

typedef std::unique_ptr<State> StateRef; // a pointer of type state, called stateref

class StateMachine //handles all of our states
{
public:
	StateMachine() { }
	~StateMachine() { }

	void AddState(StateRef newState, bool isReplacing = true); //method for adding a state to the stack and a bool for removing the current state
		
	void ProcessStateChanges(); // Run at start of each loop in Game.cpp

	StateRef &GetActiveState(); //return a reference to the top level state which will run in terms of drawing update etc

private:
	std::stack<StateRef> _states; // stack of stateref created above which is a unique pointer to a state - the states on the stack
	StateRef _newState; // latest state which we add

	bool _isRemoving; // varibles for controlling the statemahine
	bool _isAdding, _isReplacing;
};
