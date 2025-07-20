#ifndef __KEY_BSP_H
#define __KEY_BSP_H

#include "key_mod.h"

void KeyHandler( eKeyState xKeyValue);

void BspKeyInstantiation(void);

extern tUniversalButton vf07_key1;
extern tUniversalButton vf07_key2;
extern tUniversalButton vf07_key3;

void Key1Handler( eKeyState xKeyValue);
void Key2Handler( eKeyState xKeyValue);
void Key3Handler( eKeyState xKeyValue);

#endif

