#include "Movement/BattleCharacterMovementComponent.h"

UBattleCharacterMovementComponent::UBattleCharacterMovementComponent()
{
    // 设置基础移动参数
    MaxWalkSpeed = WalkSpeed;
    MaxAcceleration = 2048.0f;       // 加速度（越大起步越快）
    GroundFriction = 8.0f;           // 地面摩擦力（越大停步越快）
    BrakingDecelerationWalking = 2048.0f;  // 刹车减速度
}

void UBattleCharacterMovementComponent::StartSprint()
{
    MaxWalkSpeed = SprintSpeed;
}

void UBattleCharacterMovementComponent::StopSprint()
{
    MaxWalkSpeed = WalkSpeed;
}