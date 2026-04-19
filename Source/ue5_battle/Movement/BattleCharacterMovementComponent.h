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

    // 设置是否想要冲刺
    void SetWantsToSprint(bool bSprint);

    // 是否正在冲刺
    bool IsSprinting() const { return bIsSprinting; }

    // 开始冲刺（供输入绑定调用）
    void StartSprinting();
    // 停止冲刺（供输入绑定调用）
    void StopSprinting(); 

    // 重写 Tick
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // 普通行走速度
    float WalkSpeed = 500.0f;
    // 冲刺速度
    float SprintSpeed = 900.0f;
    // 是否想要冲刺的标志
    bool bWantsToSprint = false;
    // 是否正在冲刺
    bool bIsSprinting = false;
};