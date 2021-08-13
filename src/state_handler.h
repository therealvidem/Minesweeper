#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

#include "utils/time_utils.h"
#include "game_struct.h"

void ChangeGameState(GameStruct *gameStruct, GameState newState);
void OnGameStateChange(GameStruct *gameStruct, GameState oldState, GameState newState);

#endif
