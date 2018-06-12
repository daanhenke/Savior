#pragma once

#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "StateMachine.hpp"
#include "ConsoleMenu.hpp"
#include "SaveDataManager.hpp"

class SelectGameScreenState : public State {
public:
    ConsoleMenu* Menu;
    SaveDataManager* SaveManager;

    inline SelectGameScreenState() {
        this->Name = "SelectGameScreen";
        this->Menu = new ConsoleMenu();
        this->Menu->AddEntry("Retardation");

        this->SaveManager = new SaveDataManager();
    };

    inline void Start(StateMachine* machine) {
    	printf(CONSOLE_ESC(2J));
        this->Menu->PrintMenu();

        this->SaveManager->ReadSaveDataInfoList();

        for(unsigned int i = 0; i < this->SaveManager->GetSaveDataInfoList().size(); i++) {
        	FsSaveDataInfo SaveDataInfo = this->SaveManager->GetSaveDataInfoList()[i];

        	printf("TitleID: %lx\n", SaveDataInfo.titleID);
        }
    };

    inline void Execute(StateMachine* machine) {
    	if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B) {
    		machine->SetState("MainMenuScreen");
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