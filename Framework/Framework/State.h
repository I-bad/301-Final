#pragma once

// The State class is an abstract class that each state inherits.
class State
{
public:
	// declared the function to zero he is simply stating that the 
	//function is a pure virtual function, which has no implementation in the parent class and needs to be implemented in an inherited class
	virtual void Init() = 0; 
	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;
};