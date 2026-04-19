#include "Movement/BattleCharacterMovementComponent.h"

UBattleCharacterMovementComponent::UBattleCharacterMovementComponent()
{
    // 设置基础移动参数
    MaxWalkSpeed = WalkSpeed;
    MaxAcceleration = 2048.0f;            // 加速度（越大起步越快）
    GroundFriction = 8.0f;                // 地面摩擦力（越大停步越快）
    BrakingDecelerationWalking = 2048.0f; // 刹车减速度
}

void UBattleCharacterMovementComponent::SetWantsToSprint(bool bSprint)
{
    bWantsToSprint = bSprint;
}

void UBattleCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 每帧根据 bWantsToSprint 决定速度，不受跳跃状态影响
    if (bWantsToSprint)
    {
        bIsSprinting = true;
        MaxWalkSpeed = SprintSpeed;
    }
    else
    {
        bIsSprinting = false;
        MaxWalkSpeed = WalkSpeed;
    }
}

void UBattleCharacterMovementComponent::StartSprinting()
{
    SetWantsToSprint(true);
}

void UBattleCharacterMovementComponent::StopSprinting()
{
    SetWantsToSprint(false);
}