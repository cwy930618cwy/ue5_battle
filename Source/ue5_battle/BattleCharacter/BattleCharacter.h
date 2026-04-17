// 战斗角色基类
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BattleCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UE5_BATTLE_API ABattleCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ABattleCharacter();

protected:
    // 相机臂
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* CameraBoom;

    // 摄像机
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* FollowCamera;
};