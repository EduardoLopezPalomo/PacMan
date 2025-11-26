// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto shape = CreateDefaultSubobject<USphereComponent>(TEXT("Shape"));
	RootComponent = shape;
	shape->SetSphereRadius(45.f);
	shape->SetCollisionProfileName(TEXT("Pawn"));
	
	auto collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	collisionSphere->SetupAttachment(RootComponent);
	collisionSphere->SetSphereRadius(50.f);
	collisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/M_MaterialPlayer.M_MaterialPlayer"));
	
	
	InputMappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("InputMappingContext"));
	
	move = CreateDefaultSubobject<UInputAction>(TEXT("MoveAction"));
	sidemove= CreateDefaultSubobject<UInputAction>(TEXT("SideMoveAction"));
	look= CreateDefaultSubobject<UInputAction>(TEXT("LookAction"));
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = true;
	
	auto moveMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	moveMovement->MaxSpeed = 500.0f;
	
	auto arm =CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	arm->SetupAttachment(RootComponent);

	auto camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraPlayer"));
	camera->SetupAttachment(arm);
	camera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereAsset.Succeeded())
	{
		mesh->SetStaticMesh(SphereAsset.Object);
	}
	points = 0;
	
}

void AMyPlayer::Move(const FInputActionValue& v) {	
	FVector forward = GetWorld()->GetFirstPlayerController()->GetControlRotation().Vector();
	AddMovementInput(forward, v.GetMagnitude());
}

void AMyPlayer::SideMove(const FInputActionValue& v) {	
	FVector lateral = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().RotateVector(FVector::RightVector);
	AddMovementInput(lateral, v.GetMagnitude());
}

void AMyPlayer::Look(const FInputActionValue& v) {
	FVector2D lookAxis = v.Get<FVector2D>();
	AddControllerYawInput(lookAxis.X);
	AddControllerPitchInput(lookAxis.Y);
}

void AMyPlayer::AddPoints(int32 pointToAdd)
{
	points += pointToAdd;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	mesh->SetMaterial(0, material);
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto controller = Cast<APlayerController>(GetController());
	if (auto system = controller->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
		if (InputMappingContext) {
			system->AddMappingContext(InputMappingContext, 1);

			move->bConsumeInput = true;
			move->ValueType = EInputActionValueType::Axis1D;
			sidemove->bConsumeInput = true;
			sidemove->ValueType = EInputActionValueType::Axis1D;
			look->ValueType = EInputActionValueType::Axis2D;
			
			InputMappingContext->MapKey(look, EKeys::MouseX);
			InputMappingContext->MapKey(look, EKeys::MouseY);
			InputMappingContext->MapKey(move, EKeys::W);
			InputMappingContext->MapKey(sidemove, EKeys::D);

			auto & mapping = InputMappingContext->MapKey(move, EKeys::S);
			mapping.Modifiers.Add(NewObject<UInputModifierNegate>(this));
			auto & mappingSide = InputMappingContext->MapKey(sidemove, EKeys::A);
			mappingSide.Modifiers.Add(NewObject<UInputModifierNegate>(this));
		}
	}

	auto eic = Cast<UEnhancedInputComponent>(InputComponent);
	eic->BindAction(move, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
	eic->BindAction(sidemove, ETriggerEvent::Triggered, this, &AMyPlayer::SideMove);
	eic->BindAction(look, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
}

