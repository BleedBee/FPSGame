// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SqliteDataBaseFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class AFPS_PROJECT_API USqliteDataBaseFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static FString GetDataBasePath(FString strDataBaseName);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool CreateDataBase(FString strDataBaseName);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool OpenDataBase(FString strDataBaseName);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool ExeSQL(FString strSQL);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static void CloseDataBase(FString strDataBaseName);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool InsertLoadInformation(FString LoadTime, FString LevelName, float PlayerLocationX, float PlayerLocationY, float PlayerLocationZ, float PlayerRotationX, float PlayerRotationY, float PlayerRotationZ, float PlayerHP, int PlayerCurrentBulletNum, int PlayerPrepareBulletNum);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool InsertFirstLevelInformation(int LoadID,int MonsterNum,int KilledMonsterNum,bool isBeenToAddress,bool isOpenSwitch);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool InsertMonsterInformation(int LoadID, int MonsterID, float MonsterLocationX, float MonsterLocationY, float MonsterLocationZ, float MonsterRotationX, float MonsterRotationY, float MonsterRotationZ, float MonsterHP);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool InsertBossLevelInformation(int LoadID,float BossLocationX, float BossLocationY, float BossLocationZ, float BossRotationX, float BossRotationY, float BossRotationZ, float BossHP,bool isBeginBossBattle);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool QueryLoadInformation(int QueryLoadID,int& LoadID,FString& LoadTime, FString& LevelName, float& PlayerLocationX, float& PlayerLocationY, float& PlayerLocationZ, float& PlayerRotationX, float& PlayerRotationY, float& PlayerRotationZ, float& PlayerHP, int& PlayerCurrentBulletNum, int& PlayerPrepareBulletNum);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool QueryFirstLevelInformation(int QueryLoadID, int& LoadID, int& MonsterNum, int& KilledMonsterNum, bool& isBeenToAddress, bool& isOpenSwitch);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool QueryMonsterInformation(int QueryLoadID, int QueryMonsterID, int& LoadID, int& MonsterID, float& MonsterLocationX, float& MonsterLocationY, float& MonsterLocationZ, float& MonsterRotationX, float& MonsterRotationY, float& MonsterRotationZ, float& MonsterHP);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool QueryBossLevelInformation(int QueryLoadID, int& LoadID, float& BossLocationX, float& BossLocationY, float& BossLocationZ, float& BossRotationX, float& BossRotationY, float& BossRotationZ, float& BossHP, bool& isBeginBossBattle);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static bool DeleteLoad(int LoadID);

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static int GetLatelyLoadID();

	UFUNCTION(BlueprintCallable, Category = "SqliteDateBase")
	static TArray<int> GetLoadIDs();
};
