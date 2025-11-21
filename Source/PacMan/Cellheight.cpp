// Fill out your copyright notice in the Description page of Project Settings.


#include "Cellheight.h"

// Sets default values for this component's properties
UCellheight::UCellheight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCellheight::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	MyPlayer = Cast<AMyPlayer>(pawn);
}


// Called every frame
void UCellheight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (MyPlayer->points >= MaxPoint && GetOwner()->GetActorLocation().Z < CellHeight)
	{
		FVector newLocation = GetOwner()->GetActorLocation();
		newLocation.Z += CellHeight*DeltaTime;
		GetOwner()->SetActorLocation(newLocation);
	}
	// ...
}

