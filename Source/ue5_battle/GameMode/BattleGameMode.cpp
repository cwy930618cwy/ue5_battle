// 战斗游戏模式cpp
#include "GameMode/BattleGameMode.h"
#include "BattleCharacter/BattleCharacter.h"  // 引入你的角色类

ABattleGameMode::ABattleGameMode()
{
    // 设置默认角色类为你的BattleCharacter
    DefaultPawnClass = ABattleCharacter::StaticClass();  // 告诉引擎：玩家出生时用ABattleCharacter
}