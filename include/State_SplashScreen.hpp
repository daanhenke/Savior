#pragma once

#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "StateMachine.hpp"

class SplashScreenState : public State {
public:
    inline SplashScreenState() {
        this->Name = "SplashScreen";
    };

    inline void Start(StateMachine* machine) {
    	printf(CONSOLE_ESC(2J));
    	printf("Savior prerelease\nUse this application at your own risk, I'm not responsible if your cat\nspontaniously combusts or you lose your saves\n\nPress A to continue\nPress B to exit");
    };

    inline void Execute(StateMachine* machine) {
    	if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_A) {
    		machine->SetState("MainMenuScreen");
    		return;
    	}

    	if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B) {
    		static_cast<ApplicationState*>(machine->GetGlobalState())->IsRunning = false;
    		return;
    	}
    };

    inline void Stop(StateMachine* machine) {
    	printf("Bye...\n");
    }
};