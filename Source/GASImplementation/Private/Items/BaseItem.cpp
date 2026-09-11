// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseItem.h"

#include "Components/BoxComponent.h"


// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetBoxExtent(FVector(0.5f));
	// CollisionBox->SetCollisionProfileName("Item");
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

