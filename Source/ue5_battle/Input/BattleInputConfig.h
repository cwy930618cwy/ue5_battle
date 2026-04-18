// 战斗输入配置
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMappingContext.h"
#include "BattleInputActions.h"
#include "BattleInputConfig.generated.h"

UCLASS()
class UE5_BATTLE_API UBattleInputConfig : public UDataAsset {
  GENERATED_BODY()
public:
  // 输入映射上下文
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Config")
  UInputMappingContext* InputMappingContext;

  // 在类中添加输入动作引用
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Config")
  UBattleInputActions* InputActions;
};
