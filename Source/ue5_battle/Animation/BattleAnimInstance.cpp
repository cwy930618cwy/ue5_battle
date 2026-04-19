// 角色动画cpp
#include "Animation/BattleAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BattleCharacter/BattleCharacter.h"
#include "Movement/BattleCharacterMovementComponent.h"

void UBattleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // 获取拥有这个动画实例的角色
    ACharacter* Character = Cast<ACharacter>(GetOwningActor());
    if (!Character) return;

    // 获取角色的移动组件
    UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
    if (!MoveComp) return;

    // 每帧更新角色状态变量
    Speed = Character->GetVelocity().Size();           // 当前速度大小
    bIsInAir = MoveComp->IsFalling();                  // 是否在空中
    bIsMoving = Speed > 3.0f;                          // 速度大于3才算在移动（避免抖动）

    // 判断是否正在播放攻击蒙太奇
    UAnimMontage* AttackMontage = nullptr;
    ABattleCharacter* BattleChar = Cast<ABattleCharacter>(Character);
    if (BattleChar)
    {
        AttackMontage = BattleChar->GetAttackMontage();
    }
    bIsAttacking = AttackMontage && Montage_IsPlaying(AttackMontage);

    if (BattleChar && BattleChar->BattleMovement)
    {
        bIsSprintingAnim = BattleChar->BattleMovement->IsSprinting();
    }
}