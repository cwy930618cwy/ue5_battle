// 战斗角色基类cpp
#include "BattleCharacter/BattleCharacter.h"
#include "GameFramework/SpringArmComponent.h"  // 弹簧臂组件头文件
#include "Camera/CameraComponent.h"             // 摄像机组件头文件
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/BattleInputConfig.h"
#include "Input/BattleInputActions.h" 
#include "GameFramework/CharacterMovementComponent.h" 

ABattleCharacter::ABattleCharacter()
{
    // ========== 1. 加载骨骼网格体（角色模型） ========== //
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
        TEXT("/Game/MyResources/Meshes/SKM_Manny")  // 模型资产路径
    );
    if (MeshAsset.Succeeded())  // 检查资产是否加载成功
    {
        GetMesh()->SetSkeletalMesh(MeshAsset.Object);                          // 把模型设置到角色的Mesh组件上
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));          // 模型下移90，让脚踩在胶囊体底部
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));         // 模型旋转-90度，让角色面朝前方
    }

    // ========== 1.1 加载动画蓝图 ========== //
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPAsset(
        TEXT("/Game/MyResources/Animation/ABP_Battle")
    );
    if (AnimBPAsset.Succeeded())
    {
        GetMesh()->SetAnimInstanceClass(AnimBPAsset.Class);  // 设置动画蓝图
    }

    // ========== 2. 创建弹簧臂（摄像机支架） ========== //
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));  // 创建弹簧臂子对象，命名为CameraBoom
    CameraBoom->SetupAttachment(RootComponent);                                    // 挂载到根组件（胶囊体）上
    CameraBoom->TargetArmLength = 300.0f;                                          // 弹簧臂长度300，即摄像机离角色300单位
    CameraBoom->bUsePawnControlRotation = true;                                    // 弹簧臂跟随控制器旋转（鼠标控制视角）

    // ========== 3. 创建跟随摄像机 ========== //
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // 创建摄像机子对象，命名为FollowCamera
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);   // 挂载到弹簧臂末端的插槽上

    // ========== 4. 角色旋转设置 ========== //
    bUseControllerRotationPitch = false;  // 不让控制器的Pitch（上下看）直接旋转角色
    bUseControllerRotationYaw = false;    // 不让控制器的Yaw（左右看）直接旋转角色
    bUseControllerRotationRoll = false;   // 不让控制器的Roll（翻滚）直接旋转角色
    // 以上三个都设false，意味着角色朝向由移动方向决定，而不是鼠标方向

    // ========== 5. 角色移动组件设置 ========== //
    GetCharacterMovement()->bOrientRotationToMovement = true;              // 角色朝向移动方向
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);  // 转身速度
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;                         // 最大行走速度
    GetCharacterMovement()->JumpZVelocity = 700.0f;                        // 跳跃高度
    GetCharacterMovement()->AirControl = 0.35f;                            // 空中控制力 

    // ========== 5. 加载输入配置资产 ========== //
    static ConstructorHelpers::FObjectFinder<UBattleInputConfig> InputConfigAsset(
        TEXT("/Game/MyResources/Input/DA_BattleInputConfig")
    );
    if (InputConfigAsset.Succeeded())
    {
        InputConfig = InputConfigAsset.Object;
    }

    // ========== 6. 加载 InputActions 数据资产 ========== //
    static ConstructorHelpers::FObjectFinder<UBattleInputActions> InputActionsAsset(
        TEXT("/Game/MyResources/Input/DA_BattleInputActions")
    );

    // ========== 7. 加载三个 InputAction 资产，并赋值进去 ========== //
    static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveAsset(
        TEXT("/Game/MyResources/Input/IA_Move")
    );
    static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookAsset(
        TEXT("/Game/MyResources/Input/IA_Look")
    );
    static ConstructorHelpers::FObjectFinder<UInputAction> IA_JumpAsset(
        TEXT("/Game/MyResources/Input/IA_Jump")
    );

    if (InputConfig && InputActionsAsset.Succeeded())
    {
        InputConfig->InputActions = InputActionsAsset.Object;

        if (IA_MoveAsset.Succeeded()) InputConfig->InputActions->MoveAction = IA_MoveAsset.Object;
        if (IA_LookAsset.Succeeded()) InputConfig->InputActions->LookAction = IA_LookAsset.Object;
        if (IA_JumpAsset.Succeeded()) InputConfig->InputActions->JumpAction = IA_JumpAsset.Object;
    } 

}

// ========== 4. 开始播放 ========== //
void ABattleCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 获取 PlayerController
    APlayerController* PC = Cast<APlayerController>(Controller);
    if (PC)
    {
        if (InputConfig)
        {
            // 将输入配置绑定到玩家控制器
            UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
            if (Subsystem)
            {
                Subsystem->AddMappingContext(InputConfig->InputMappingContext, 0);
            }
        }
    }
}

// ========== 5. 输入组件设置 ========== //
void ABattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 检查输入配置是否有效
    if (!InputConfig)
    {
        UE_LOG(LogTemp, Warning, TEXT("InputConfig is null! Please assign an InputConfig asset in the editor."));
        return;
    }

    // 获取增强输入组件
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (!EnhancedInputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get EnhancedInputComponent"));
        return;
    }

    // 绑定输入动作
    if (InputConfig->InputActions)
    {
        // 绑定移动输入
        EnhancedInputComponent->BindAction(
            InputConfig->InputActions->MoveAction, 
            ETriggerEvent::Triggered, 
            this, 
            &ABattleCharacter::Move
        );

        // 绑定视角输入
        EnhancedInputComponent->BindAction(
            InputConfig->InputActions->LookAction, 
            ETriggerEvent::Triggered, 
            this, 
            &ABattleCharacter::Look
        );

        // 绑定跳跃输入（开始和结束）
        EnhancedInputComponent->BindAction(
            InputConfig->InputActions->JumpAction, 
            ETriggerEvent::Started, 
            this, 
            &ABattleCharacter::StartJump
        );
        EnhancedInputComponent->BindAction(
            InputConfig->InputActions->JumpAction, 
            ETriggerEvent::Completed, 
            this, 
            &ABattleCharacter::StopJump
        );
    }
}

// ========== 6. 移动输入处理 ========== //
void ABattleCharacter::Move(const FInputActionValue& Value)
{
    // 获取输入值
    FVector2D MovementVector = Value.Get<FVector2D>();

    if(Controller != nullptr && MovementVector.SizeSquared() > 0.0f)
    {
        // 获取控制器的前向和右向变量
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);  // 只使用Yaw旋转，忽略Pitch和Roll

        // 计算移动方向
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // 应用移动
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

// ========== 7. 视角输入处理 ========== //
void ABattleCharacter::Look(const FInputActionValue& Value)
{
    // 获取输入值
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if(Controller != nullptr)
    {
        // 添加视角输入
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

// ========== 8. 跳跃输入处理 ========== //
void ABattleCharacter::StartJump()
{
    Jump();
}

void ABattleCharacter::StopJump()
{
    StopJumping();
}
