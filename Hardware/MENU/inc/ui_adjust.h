#ifndef _UI_ADJUST_H
#define _UI_ADJUST_H

#include "decoy.h"

void OnPDFunctionLoad(void);
void OnPDFunctionExit(void);
void OnPDFunction(void);

void OnQCFunctionLoad(void);
void OnQCFunctionExit(void);
void OnQCFunction(void);

void OnPDOFunctionLoad(void);
void OnPDOFunctionExit(void);
void OnPDOFunction(void);


void UI_Adjust_Load(void);
void UI_Adjust_Exit(void);
void UI_Adjust_Task(void);

void PD_Ok(void);
void Key_Register_PD(void);
void Set_PD_Protocol(void);
extern void Key_Start_Task(void);




#endif
