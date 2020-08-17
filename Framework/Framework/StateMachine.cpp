#include "StateMachine.h"

void StateMachine::AddState(StateRef newState, bool isReplacing) // function to add a state to the stack and replace current state
{
	this->_isAdding = true; 
	this->_isReplacing = isReplacing; 

	this->_newState = std::move(newState);
}

void StateMachine::ProcessStateChanges()
{
	if (this->_isAdding)
	{
		if (!this->_states.empty())
		{
			if (this->_isReplacing) // removes the current state if there is something in the stack
			{
				this->_states.pop();
			}
		}

		this->_states.push(std::move(this->_newState)); // move the new state onto the stack
		this->_states.top()->Init(); // calls the initialiser of the state class
		this->_isAdding = false; 
	}
}

StateRef &StateMachine::GetActiveState()
{
	return this->_states.top(); // we are returning a reference to the top state so we can process chanegs
}
