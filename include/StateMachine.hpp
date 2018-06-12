#pragma once

#include <string.h>
#include <map>
#include <stdio.h>

class StateMachine;

class State {
public:
	std::string Name;
	virtual void Execute(StateMachine* machine);
	virtual void Start(StateMachine* machine);
	virtual void Stop(StateMachine* machine);
};

class GlobalState : public State {
public:
	inline void Execute(StateMachine* machine) {
		printf("The global state shouldn't be executed!\n");
	}

	inline void Start(StateMachine* machine) {
		this->Execute(machine);
	}

	inline void Stop(StateMachine* machine) {
		this->Execute(machine);
	}
};

class StateMachineStorage {
public:
	std::string ActiveState = "None";
	std::map<std::string, State*> StateMap;
	GlobalState* Global;
};

class StateMachine {
public:
	StateMachineStorage* Storage;

	inline StateMachine(GlobalState* GlobalState) {
		this->Storage = new StateMachineStorage();
		this->Storage->Global = GlobalState;
	}

	inline GlobalState* GetGlobalState() {
		return this->Storage->Global;
	}

	inline State* GetState(std::string name) {
		if (this->Storage->StateMap.count(name) > 0) {
			return this->Storage->StateMap[this->Storage->ActiveState];
		}

		return NULL;
	}

	inline State* GetCurrentState() {
		return this->GetState(this->Storage->ActiveState);
	}

	inline void AddState(State* state) {
		this->Storage->StateMap[state->Name] = state;
		#ifdef _STATEMACHINE_DEBUG
		printf("Added state: %s\n", state->Name.c_str());
		#endif
	}

	inline void SetState(std::string name) {
		if (this->Storage->StateMap.count(name) > 0) {
			#ifdef _STATEMACHINE_DEBUG
			printf("Setting state: %s\n", name.c_str());
			#endif

			if (this->Storage->ActiveState != "None") {
				this->GetCurrentState()->Stop(this);
			}

			this->Storage->ActiveState = name;
			this->GetCurrentState()->Start(this);
		} else {
			#ifdef _STATEMACHINE_DEBUG
			printf("Unknown state: %s\n", name.c_str());
			#endif
		}
	}

	inline void Execute() {
		if (this->Storage->ActiveState != "None") {
			this->GetCurrentState()->Execute(this);
		}
	}
};