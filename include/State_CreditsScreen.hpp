#pragma once

#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "StateMachine.hpp"
#include "State_ApplicationState.hpp"

class CreditsScreenState : public State {
public:
    inline CreditsScreenState() {
        this->Name = "CreditsScreen";
    };

    inline void Start(StateMachine* machine) {
        printf(CONSOLE_ESC(2J));
    	printf("Made by Dann_\n");
        printf("Press B to go back.\n");
    };

    inline void Execute(StateMachine* machine) {
        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B) {
            machine->SetState("MainMenuScreen");
        }
    };

    inline void Stop(StateMachine* machine) {
    	printf("Bye from credits...\n");
    }
};