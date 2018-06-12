
#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "StateMachine.hpp"
#include "State_ApplicationState.hpp"
#include "State_SplashScreen.hpp"
#include "State_MainMenuScreen.hpp"
#include "State_SelectGameScreen.hpp"
#include "State_CreditsScreen.hpp"

int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(NULL);

    StateMachine* machine = new StateMachine(new ApplicationState());
    machine->AddState(new SplashScreenState());
    machine->AddState(new MainMenuScreenState());
    machine->AddState(new SelectGameScreenState());
    machine->AddState(new CreditsScreenState());
    machine->SetState("SplashScreen");

    while(appletMainLoop() && static_cast<ApplicationState*>(machine->GetGlobalState())->IsRunning)
    {
        hidScanInput();

        machine->Execute();

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

    gfxExit();
    return 0;
}