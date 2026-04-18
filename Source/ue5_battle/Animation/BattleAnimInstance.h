// 战斗动画实例基类
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BattleAnimInstance.generated.h"

UCLASS()
class UE5_BATTLE_API UBattleAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    // 角色速度（动画蓝图里用这个判断走/跑）
    UPROPERTY(BlueprintReadOnly, Category = "Character State")
    float Speed = 0.0f;

    // 是否在空中（动画蓝图里用这个判断跳跃）
    UPROPERTY(BlueprintReadOnly, Category = "Character State")
    bool bIsInAir = false;

    // 是否在移动（速度 > 0）
    UPROPERTY(BlueprintReadOnly, Category = "Character State")
    bool bIsMoving = false;
};