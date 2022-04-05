// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFactory.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseFactory::ABaseFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// рут сделали по умолчанию
	RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRoot");

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	BuildingMesh->SetupAttachment(RootComponent);

	HitCollider = CreateDefaultSubobject<UBoxComponent>("HitCollider");
	HitCollider->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void ABaseFactory::BeginPlay()
{
	Super::BeginPlay();

	// создаем таймер для спавна
	GetWorldTimerManager().SetTimer(Timer, this, &ABaseFactory::OnTankSpawnTick, SpawnInterval, true);
}

// Called every frame
void ABaseFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFactory::TakeDamage(FDamageData Damage)
{
	if (HealthComponent)
		HealthComponent->TakeDamageTank(Damage);
}

void ABaseFactory::OnTankSpawnTick()
{							// создает актор но не до конца, этим позволяя нам задать путь
	auto Tank = GetWorld()->SpawnActorDeferred<AEnemyTankPawn>(TankClass, SpawnPoint->GetComponentTransform());
																			// если фабрика имеет меньший размер то и акторы будут меньше
	// теперь можно задать ему параметры которые нужно задать - в констракт - передаем их в танк
	Tank->Waypoints = Waypoints;

	TanksSpawned++;
	Tank->Number = TanksSpawned;

	// заканчиваем создание танка, дальше он спавнится с заданными параметрами
	UGameplayStatics::FinishSpawningActor(Tank, SpawnPoint->GetComponentTransform());
}													