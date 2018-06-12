#pragma once

#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "StateMachine.hpp"

class ApplicationState : public GlobalState {
public:
    ApplicationState() {
        this->Name = "ApplicationState";
    };

    bool IsRunning = true;
};