// 战斗输入动作定义
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "BattleInputActions.generated.h"

UCLASS()
class UE5_BATTLE_API UBattleInputActions : public UDataAsset {
  GENERATED_BODY()
public:
    // 移动输入动作
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
  UInputAction* MoveAction;

  // 视角输入
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
  UInputAction* LookAction;

  // 跳跃输入
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Actions")
  UInputAction* JumpAction;
};
