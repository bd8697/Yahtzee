#pragma once

#include <memory>
#include <stack>

#include "GameState.h"

typedef std::unique_ptr<GameState> StateRef;

class StateMachine
{
public:
	StateMachine(){}
	~StateMachine(){}

	void AddState(GameState* newState, bool isReplacing = true);
	void RemoveState();

	void ProcessStateChanges();

	GameState* GetActiveState();

private:
	std::stack<GameState*> _states;
	GameState* _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;

};

