// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MyPlayer.h"
#include "GameFramework/Pawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyPlayer::StaticClass();
}
