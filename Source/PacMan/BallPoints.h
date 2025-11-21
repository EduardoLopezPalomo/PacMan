// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallPoints.generated.h"

UCLASS()
class PACMAN_API ABallPoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallPoints();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Points")
	int32 pointsValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Points")
	TSoftObjectPtr<UStaticMesh> outsideMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Points")
	TSoftObjectPtr<UMaterialInterface> ousideMaterial;
	
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
private:
	UStaticMeshComponent* mesh;
	UMaterialInterface* material;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
