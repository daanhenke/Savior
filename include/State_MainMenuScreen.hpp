#pragma once

#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "StateMachine.hpp"
#include "ConsoleMenu.hpp"

class MainMenuScreenState : public State {
public:
    ConsoleMenu* Menu;
    inline MainMenuScreenState() {
        this->Name = "MainMenuScreen";
        this->Menu = new ConsoleMenu();
        this->Menu->AddEntry("Export");
        this->Menu->AddEntry("Import (TODO)");
        this->Menu->AddEntry("Credits");
        this->Menu->AddEntry("Exit to hbmenu");
    };

    inline void Start(StateMachine* machine) {
    	printf(CONSOLE_ESC(2J));
        this->Menu->PrintMenu();
    };

    inline void Execute(StateMachine* machine) {
    	if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_A) {
            std::string CurrentEntry = this->Menu->GetCurrentEntry();
            if (CurrentEntry == "Export") {
                machine->SetState("SelectGameScreen");
                return;
            }

            if (CurrentEntry == "Credits") {
                machine->SetState("CreditsScreen");
                return;
            }

            if (CurrentEntry == "Exit to hbmenu") {
                static_cast<ApplicationState*>(machine->GetGlobalState())->IsRunning = false;
                return;
            }
    	}

    	if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B) {
    		machine->SetState("SplashScreen");
    		return;
    	}

        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_UP) {
            this->Menu->MoveUp();
            this->Start(machine);
            return;
        }

        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_DOWN) {
            this->Menu->MoveDown();
            this->Start(machine);
            return;
        }
    };

    inline void Stop(StateMachine* machine) {}
};