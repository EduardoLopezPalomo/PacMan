// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fruit.generated.h"

UCLASS()
class PACMAN_API AFruit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFruit();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	TSoftObjectPtr<UStaticMesh> outsideMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
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
