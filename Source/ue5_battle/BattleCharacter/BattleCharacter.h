// 战斗角色基类
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/BattleInputConfig.h"
#include "Input/BattleInputActions.h" 
#include "BattleCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBattleInputConfig;  // 前向声明输入配置类

UCLASS()
class UE5_BATTLE_API ABattleCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ABattleCharacter();

    virtual void BeginPlay() override;
    
    // 重写输入组件设置函数
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // 相机臂
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* CameraBoom;

    // 摄像机
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* FollowCamera;

    // 输入配置 - 引用输入映射和动作定义
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UBattleInputConfig* InputConfig;

    // 输入处理函数
    void Move(const struct FInputActionValue& Value);  // 移动输入处理
    void Look(const struct FInputActionValue& Value);  // 视角输入处理
    void StartJump();                                  // 开始跳跃
    void StopJump();                                   // 停止跳跃
};