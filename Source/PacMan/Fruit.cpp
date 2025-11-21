// Fill out your copyright notice in the Description page of Project Settings.


#include "Fruit.h"
#include "Components/SphereComponent.h"
#include "MyPlayer.h"

// Sets default values
AFruit::AFruit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto shape = CreateDefaultSubobject<USphereComponent>(TEXT("Shape"));
	RootComponent = shape;
	shape->SetSphereRadius(50.f);
	shape->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	shape->OnComponentBeginOverlap.AddDynamic(this, &AFruit::OnActorBeginOverlap);
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	
	material = CreateDefaultSubobject<UMaterialInterface>(TEXT("Material"));

}
void AFruit::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)return;
	
	if(OtherActor->IsA(AMyPlayer::StaticClass()))
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Has ganado"));
	}	
}

// Called when the game starts or when spawned
void AFruit::BeginPlay()
{
	Super::BeginPlay();
	mesh->SetStaticMesh(outsideMesh.LoadSynchronous());
	material = ousideMaterial.LoadSynchronous();
	mesh->SetMaterial(0, material);
	
}

// Called every frame
void AFruit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

