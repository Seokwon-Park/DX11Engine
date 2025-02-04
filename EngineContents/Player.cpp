#include "EnginePCH.h"
#include "Player.h"
#include <EnginePlatform/EngineInputSystem.h>

APlayer::APlayer()
	:AEntity()
{
	//BoxCollider2D->SetRelativeScale3D(FVector4(28.0f, 56.0f, 1.0f));
	CapsuleCollider2D->SetRelativeScale3D(FVector4(26.0f, 56.0f, 1.0f));
	CapsuleCollider2D->SetCollisionLayer(ECollisionLayer::Player);
}

APlayer::~APlayer()
{
}


void APlayer::Tick(float _DeltaTime)
{
	AEntity::Tick(_DeltaTime);

	StateMachine->CurrentState->Update();
}

void APlayer::BeginPlay()
{
	AEntity::BeginPlay();

	StateMachine = std::make_shared<PlayerStateMachine>();
	IdleState = std::make_shared<PlayerIdleState>(this, StateMachine.get(), "TeviIdle");
	RunState = std::make_shared<PlayerRunState>(this, StateMachine.get(), "TeviRun");
	JumpState = std::make_shared<PlayerJumpState>(this, StateMachine.get(), "TeviJump");
	AirState = std::make_shared<PlayerAirState>(this, StateMachine.get(), "TeviAir");
	AttackState = std::make_shared<PlayerGroundAttackState>(this, StateMachine.get(), "TeviAttack");
	Animator->SetAnimationEndEvent("TeviAttack0",  std::bind(&PlayerGroundAttackState::AnimationEndTrigger, AttackState));
	Animator->SetAnimationEndEvent("TeviAttack1", std::bind(&PlayerGroundAttackState::AnimationEndTrigger, AttackState));
	Animator->SetAnimationEndEvent("TeviAttack2", std::bind(&PlayerGroundAttackState::AnimationEndTrigger, AttackState));
	Animator->SetAnimationEndEvent("TeviAttack3", std::bind(&PlayerGroundAttackState::AnimationEndTrigger, AttackState));

	StateMachine->InitState(AirState);
}

void APlayer::AttackTrigger()
{
    /*Physics2D.OverlapCircleAll(player.attackCheck.position, player.attackCheckRadius);

    foreach(var hit in colliders)
    {
        if (hit.GetComponent<Enemy>() != null)
        {
            EnemyStats _target = hit.GetComponent<EnemyStats>();

            if (_target != null)
                player.stats.DoDamage(_target);

            ItemData_Equipment weaponData = Inventory.Instance.GetEquipment(EquipmentType.Weapon);

            if (weaponData != null)
            {
                weaponData.Effect(_target.transform);
            }
        }
    }*/
}
