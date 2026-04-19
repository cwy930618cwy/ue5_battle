// 战斗角色移动组件
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BattleCharacterMovementComponent.generated.h"

UCLASS()
class UE5_BATTLE_API UBattleCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UBattleCharacterMovementComponent();

    // 开始冲刺
    void StartSprint();
    // 停止冲刺
    void StopSprint();

private:
    // 普通行走速度
    float WalkSpeed = 500.0f;
    // 冲刺速度
    float SprintSpeed = 900.0f;
};