// Fill out your copyright notice in the Description page of Project Settings.

#include "BombermanPawn.h"
#include "BombermanMovementComponent.h"
#include "BombermanInventoryMngrComponent.h"
#include "Engine.h"

// Sets default values
ABombermanPawn::ABombermanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere collision"));
	Collision->SetSphereRadius(49.5f);

	// Set collision and constraints for movement
	this->SetRootComponent(Collision);
	Collision->SetSimulatePhysics(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (Collision->GetBodyInstance()) {
		// Lock rotation
		Collision->GetBodyInstance()->bLockXRotation = true;
		Collision->GetBodyInstance()->bLockYRotation = true;
		Collision->GetBodyInstance()->bLockZRotation = true;
		Collision->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
		// Set response channels (for bomb explosion trace)
		Collision->GetBodyInstance()->SetResponseToAllChannels(ECollisionResponse::ECR_Block);
		Collision->GetBodyInstance()->SetResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	}
	
	Collision->SetLinearDamping(5.5f);
	Collision->SetAngularDamping(2.5f);

	// Set mesh
	BombermanMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomberman mesh"));
	BombermanMesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);
	BombermanMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set movement component
	MovementComponent = CreateDefaultSubobject<UBombermanMovementComponent>(TEXT("Movement component"));
	
	// Set inventory manager
	InventoryManager = CreateDefaultSubobject<UBombermanInventoryMngrComponent>(TEXT("Inventory manager component"));
}

// Called when the game starts or when spawned
void ABombermanPawn::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent->Initialize(Collision, BombermanMesh, this);
	InventoryManager->Initialize(this);
}

// Called every frame
void ABombermanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABombermanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

