// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPoints.h"
#include "Components/SphereComponent.h"
#include "MyPlayer.h"

// Sets default values
ABallPoints::ABallPoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto shape = CreateDefaultSubobject<USphereComponent>(TEXT("Shape"));
	RootComponent = shape;
	shape->SetSphereRadius(50.f);
	shape->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	shape->OnComponentBeginOverlap.AddDynamic(this, &ABallPoints::OnActorBeginOverlap);
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	
	material = CreateDefaultSubobject<UMaterialInterface>(TEXT("Material"));
	
	pointsValue = 1;

}

void ABallPoints::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)return;
	
	if(OtherActor->IsA(AMyPlayer::StaticClass()))
	{
		AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
		player->AddPoints(pointsValue);
		Destroy();
	}	
}


// Called when the game starts or when spawned
void ABallPoints::BeginPlay()
{
	Super::BeginPlay();
	mesh->SetStaticMesh(outsideMesh.LoadSynchronous());
	material = ousideMaterial.LoadSynchronous();
	mesh->SetMaterial(0, material);
	
}

// Called every frame
void ABallPoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

