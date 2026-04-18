// 战斗角色基类cpp
#include "BattleCharacter/BattleCharacter.h"
#include "GameFramework/SpringArmComponent.h"  // 弹簧臂组件头文件
#include "Camera/CameraComponent.h"             // 摄像机组件头文件

ABattleCharacter::ABattleCharacter()
{
    // ========== 1. 加载骨骼网格体（角色模型） ========== //
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
        TEXT("/Game/ThreeCharacters/Characters/Mannequins/Meshes/SKM_Manny")  // 模型资产路径
    );
    if (MeshAsset.Succeeded())  // 检查资产是否加载成功
    {
        GetMesh()->SetSkeletalMesh(MeshAsset.Object);                          // 把模型设置到角色的Mesh组件上
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));          // 模型下移90，让脚踩在胶囊体底部
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));         // 模型旋转-90度，让角色面朝前方
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
}