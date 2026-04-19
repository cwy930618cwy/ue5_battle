// 战斗角色基类
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/BattleInputConfig.h"
#include "Input/BattleInputActions.h" 
#include "Animation/AnimMontage.h" 
#include "Movement/BattleCharacterMovementComponent.h" 
#include "BattleCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBattleInputConfig;  // 前向声明输入配置类

UCLASS()
class UE5_BATTLE_API ABattleCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ABattleCharacter(const FObjectInitializer& ObjectInitializer); 

    virtual void BeginPlay() override;

    // 在 public 区域，BeginPlay 下面加：
    virtual void Tick(float DeltaTime) override; 
    
    // 重写输入组件设置函数
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 获取攻击蒙太奇（供动画实例使用）
    UAnimMontage* GetAttackMontage() const { return AttackMontage; } 

    // 在 public 区域加，放在 GetAttackMontage 下面
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    UBattleCharacterMovementComponent* BattleMovement; 

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

    // 动画实例
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> AttackMontage; 

    // 输入处理函数
    void Move(const struct FInputActionValue& Value);  // 移动输入处理
    void Look(const struct FInputActionValue& Value);  // 视角输入处理
    void StartJump();                                  // 开始跳跃
    void StopJump();                                   // 停止跳跃
    void Attack();                                     // 攻击
    void StartSprint();                                // 开始冲刺
    void StopSprint();                                 // 停止冲刺 
};