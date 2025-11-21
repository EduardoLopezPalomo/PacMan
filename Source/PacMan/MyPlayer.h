// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "MyPlayer.generated.h"

UCLASS()
class PACMAN_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	int32 points;
	
	UInputMappingContext* InputMappingContext;
	
	UInputAction* move;
	UInputAction* sidemove;
	UInputAction* look;
	
	UFUNCTION()
	void AddPoints(int32 pointToAdd);
	
	void Move(const FInputActionValue& v);
	void SideMove(const FInputActionValue& v); 
	void Look(const FInputActionValue& v);
private:
	UStaticMeshComponent* mesh;
	UMaterialInterface* material;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
