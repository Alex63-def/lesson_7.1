// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "Engine/TargetPoint.h"
#include "EnemyTankPawn.generated.h"

/**
 * 
 */
UCLASS()
class LESSON_3_API AEnemyTankPawn : public ATankPawn
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DeathEffectt;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioDeathEffectt;

	//����� ���������� ����� �� ���������� ������ �� ��� possess �� �� �������� �� ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move")
		TArray<ATargetPoint*> Waypoints;

	AEnemyTankPawn();

	// ���� ����� ������������ ��������� ��� ������ ����� �� ������ BaseFactory
	virtual void OnConstrution(const FTransform& Transform) override;

	// ��� ��� �������, �� �� ��� �� ������
	int Number = -1;

private:

	//UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void OnHealthChanged(float CurrentHealth) override;
	virtual void OnDeath() override;
	virtual void SelfDestruction() override;
};
