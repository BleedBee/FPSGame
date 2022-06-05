// Fill out your copyright notice in the Description page of Project Settings.


#include "SqliteDataBaseFunctionLib.h"
#include "Sqlite/Includes/sqlite3.h"

using namespace std;

sqlite3* pDataBase = nullptr;

bool USqliteDataBaseFunctionLib::CreateDataBase(FString strDataBaseName)
{
	FString strDataBasePath = FPaths::ProjectContentDir().Append(TEXT("DataBase/")).Append(strDataBaseName);
	int nRes = sqlite3_open_v2(TCHAR_TO_UTF8(*strDataBasePath), &pDataBase, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	UE_LOG(LogTemp, Warning, TEXT("nRes:%d"), nRes);
	if (nRes != SQLITE_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create DataBase Failed!!"));
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Create DataBase Success!!"));
		sqlite3_close(pDataBase);
		return true;
	}
}

FString USqliteDataBaseFunctionLib::GetDataBasePath(FString strDataBaseName)
{
	FString strDataBasePath = FPaths::ProjectContentDir().Append(TEXT("DataBase/")).Append(strDataBaseName);
	return strDataBasePath;
}

bool USqliteDataBaseFunctionLib::OpenDataBase(FString strDataBaseName)
{
	FString strDataBasePath = GetDataBasePath(strDataBaseName);
	int nRes = sqlite3_open_v2(TCHAR_TO_UTF8(*strDataBasePath), &pDataBase, SQLITE_OPEN_READWRITE, NULL);
	if (nRes != SQLITE_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("Open DataBase Failed!!"));
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Open DataBase Success!!"));
		return true;
	}
}

bool USqliteDataBaseFunctionLib::ExeSQL(FString strSQL)
{
	char* errmsg = NULL;
	sqlite3_exec(pDataBase, TCHAR_TO_UTF8(*strSQL), NULL, NULL, &errmsg);
	if (errmsg != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExeSQL Error, Error Code:%s"), UTF8_TO_TCHAR(errmsg));
		return false;
	}
	else
		return true;
}

void USqliteDataBaseFunctionLib::CloseDataBase(FString strDataBaseName)
{
	sqlite3_close(pDataBase);
}

bool USqliteDataBaseFunctionLib::InsertLoadInformation(FString LoadTime, FString LevelName, float PlayerLocationX, float PlayerLocationY, float PlayerLocationZ, float PlayerRotationX, float PlayerRotationY, float PlayerRotationZ, float PlayerHP, int PlayerCurrentBulletNum, int PlayerPrepareBulletNum)
{
	FString SQL=FString::Printf(TEXT("INSERT INTO LoadInformation (LoadTime,LevelName,PlayerLocationX,PlayerLocationY,PlayerLocationZ,PlayerRotationX,PlayerRotationY,PlayerRotationZ,PlayerHP,PlayerCurrentBulletNum,PlayerPrepareBulletNum) VALUES ('%s','%s',%f,%f,%f,%f,%f,%f,%f,%d,%d);"), *LoadTime, *LevelName, PlayerLocationX, PlayerLocationY, PlayerLocationZ, PlayerRotationX, PlayerRotationY, PlayerRotationZ, PlayerHP, PlayerCurrentBulletNum, PlayerPrepareBulletNum);
	bool Res = ExeSQL(SQL);
	return Res;
}

bool USqliteDataBaseFunctionLib::InsertFirstLevelInformation(int LoadID, int MonsterNum, int KilledMonsterNum, bool isBeenToAddress, bool isOpenSwitch)
{
	FString SQL = FString::Printf(TEXT("INSERT INTO FirstLevelInformation (LoadID,MonsterNum,KilledMonsterNum,isBeenToAddress,isOpenSwitch) VALUES (%d,%d,%d,%d,%d);"),LoadID,MonsterNum,KilledMonsterNum, isBeenToAddress?1:0,isOpenSwitch?1:0);
	bool Res = ExeSQL(SQL);
	return Res;
}

bool USqliteDataBaseFunctionLib::InsertMonsterInformation(int LoadID, int MonsterID, float MonsterLocationX, float MonsterLocationY, float MonsterLocationZ, float MonsterRotationX, float MonsterRotationY, float MonsterRotationZ, float MonsterHP)
{
	FString SQL = FString::Printf(TEXT("INSERT INTO MonsterInformation (LoadID,MonsterID,MonsterLocationX,MonsterLocationY,MonsterLocationZ,MonsterRotationX,MonsterRotationY,MonsterRotationZ,MonsterHP) VALUES (%d,%d,%f,%f,%f,%f,%f,%f,%f);"), LoadID, MonsterID, MonsterLocationX, MonsterLocationY, MonsterLocationZ, MonsterRotationX, MonsterRotationY, MonsterRotationZ, MonsterHP);
	bool Res = ExeSQL(SQL);
	return Res;
}

bool USqliteDataBaseFunctionLib::InsertBossLevelInformation(int LoadID, float BossLocationX, float BossLocationY, float BossLocationZ, float BossRotationX, float BossRotationY, float BossRotationZ, float BossHP, bool isBeginBossBattle)
{
	FString SQL = FString::Printf(TEXT("INSERT INTO BossLevelInformation (LoadID,BossLocationX,BossLocationY,BossLocationZ,BossRotationX,BossRotationY,BossRotationZ,BossHP,isBeginBossBattle) VALUES (%d,%f,%f,%f,%f,%f,%f,%f,%d);"), LoadID, BossLocationX, BossLocationY, BossLocationZ, BossRotationX, BossRotationY, BossRotationZ, BossHP, isBeginBossBattle?1:0);
	bool Res = ExeSQL(SQL);
	return Res;
}

bool USqliteDataBaseFunctionLib::QueryLoadInformation(int QueryLoadID,int& LoadID, FString& LoadTime, FString& LevelName, float& PlayerLocationX, float& PlayerLocationY, float& PlayerLocationZ, float& PlayerRotationX, float& PlayerRotationY, float& PlayerRotationZ, float& PlayerHP, int& PlayerCurrentBulletNum, int& PlayerPrepareBulletNum)
{
	sqlite3_stmt* stmt = nullptr;
	FString SQL = FString::Printf(TEXT("SELECT * FROM LoadInformation WHERE LoadID=%d;"), QueryLoadID);
	sqlite3_prepare_v2(pDataBase, TCHAR_TO_UTF8(*SQL), -1, &stmt, NULL);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		LoadID = sqlite3_column_int(stmt, 0);
		LoadTime = UTF8_TO_TCHAR(sqlite3_column_text(stmt, 1));
		LevelName = UTF8_TO_TCHAR(sqlite3_column_text(stmt, 2));
		PlayerLocationX = sqlite3_column_double(stmt, 3);
		PlayerLocationY = sqlite3_column_double(stmt, 4);
		PlayerLocationZ = sqlite3_column_double(stmt, 5);
		PlayerRotationX = sqlite3_column_double(stmt, 6);
		PlayerRotationY = sqlite3_column_double(stmt, 7);
		PlayerRotationZ = sqlite3_column_double(stmt, 8);
		PlayerHP = sqlite3_column_double(stmt, 9);
		PlayerCurrentBulletNum = sqlite3_column_int(stmt, 10);
		PlayerPrepareBulletNum = sqlite3_column_int(stmt, 11);
		sqlite3_finalize(stmt);
		return true;
	}
	sqlite3_finalize(stmt);
	return false;
}

bool USqliteDataBaseFunctionLib::QueryFirstLevelInformation(int QueryLoadID,int& LoadID, int& MonsterNum, int& KilledMonsterNum, bool& isBeenToAddress, bool& isOpenSwitch)
{
	sqlite3_stmt* stmt = nullptr;
	FString SQL = FString::Printf(TEXT("SELECT * FROM FirstLevelInformation WHERE LoadID=%d;"), QueryLoadID);
	sqlite3_prepare_v2(pDataBase, TCHAR_TO_UTF8(*SQL), -1, &stmt, NULL);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		LoadID = sqlite3_column_int(stmt, 0);
		MonsterNum = sqlite3_column_int(stmt, 1);
		KilledMonsterNum = sqlite3_column_int(stmt, 2);
		isBeenToAddress = sqlite3_column_int(stmt, 3) == 1 ? true : false;
		isOpenSwitch = sqlite3_column_int(stmt, 4) == 1 ? true : false;
		sqlite3_finalize(stmt);
		return true;
	}
	sqlite3_finalize(stmt);
	return false;
}

bool USqliteDataBaseFunctionLib::QueryMonsterInformation(int QueryLoadID, int QueryMonsterID, int& LoadID, int& MonsterID, float& MonsterLocationX, float& MonsterLocationY, float& MonsterLocationZ, float& MonsterRotationX, float& MonsterRotationY, float& MonsterRotationZ, float& MonsterHP)
{
	sqlite3_stmt* stmt = nullptr;
	FString SQL = FString::Printf(TEXT("SELECT * FROM MonsterInformation WHERE LoadID=%d AND MonsterID=%d;"), QueryLoadID, QueryMonsterID);
	sqlite3_prepare_v2(pDataBase, TCHAR_TO_UTF8(*SQL), -1, &stmt, NULL);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		LoadID = sqlite3_column_int(stmt, 0);
		MonsterID = sqlite3_column_int(stmt, 1);
		MonsterLocationX = sqlite3_column_double(stmt, 2);
		MonsterLocationY = sqlite3_column_double(stmt, 3);
		MonsterLocationZ = sqlite3_column_double(stmt, 4);
		MonsterRotationX = sqlite3_column_double(stmt, 5);
		MonsterRotationY = sqlite3_column_double(stmt, 6);
		MonsterRotationZ = sqlite3_column_double(stmt, 7);
		MonsterHP = sqlite3_column_double(stmt, 8);
		sqlite3_finalize(stmt);
		return true;
	}
	sqlite3_finalize(stmt);
	return false;
}

bool USqliteDataBaseFunctionLib::QueryBossLevelInformation(int QueryLoadID, int& LoadID, float& BossLocationX, float& BossLocationY, float& BossLocationZ, float& BossRotationX, float& BossRotationY, float& BossRotationZ, float& BossHP, bool& isBeginBossBattle)
{
	sqlite3_stmt* stmt = nullptr;
	FString SQL = FString::Printf(TEXT("SELECT * FROM BossLevelInformation WHERE LoadID=%d;"), QueryLoadID);
	sqlite3_prepare_v2(pDataBase, TCHAR_TO_UTF8(*SQL), -1, &stmt, NULL);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		LoadID = sqlite3_column_int(stmt, 0);
		BossLocationX = sqlite3_column_double(stmt, 1);
		BossLocationY = sqlite3_column_double(stmt, 2);
		BossLocationZ = sqlite3_column_double(stmt, 3);
		BossRotationX = sqlite3_column_double(stmt, 4);
		BossRotationY = sqlite3_column_double(stmt, 5);
		BossRotationZ = sqlite3_column_double(stmt, 6);
		BossHP = sqlite3_column_double(stmt, 7);
		isBeginBossBattle = sqlite3_column_int(stmt, 8) == 1 ? true : false;
		sqlite3_finalize(stmt);
		return true;
	}
	sqlite3_finalize(stmt);
	return false;
}

bool USqliteDataBaseFunctionLib::DeleteLoad(int LoadID)
{
	FString SQL = FString::Printf(TEXT("DELETE FROM LoadInformation WHERE LoadID=%d;DELETE FROM FirstLevelInformation WHERE LoadID=%d;DELETE FROM MonsterInformation WHERE LoadID=%d;DELETE FROM BossLevelInformation WHERE LoadID=%d;"), LoadID, LoadID, LoadID, LoadID);
	bool Res = ExeSQL(SQL);
	return Res;
}

int USqliteDataBaseFunctionLib::GetLatelyLoadID()
{
	sqlite3_stmt* stmt = nullptr;
	FString SQL = FString::Printf(TEXT("SELECT max(LoadID) FROM LoadInformation;"));
	sqlite3_prepare_v2(pDataBase, TCHAR_TO_UTF8(*SQL), -1, &stmt, NULL);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		int LatelyLoadID= sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		return LatelyLoadID;
	}
	sqlite3_finalize(stmt);
	return 0;
}

TArray<int> USqliteDataBaseFunctionLib::GetLoadIDs()
{
	TArray<int> LoadIDArray;
	sqlite3_stmt* stmt = nullptr;
	FString SQL = FString::Printf(TEXT("SELECT * FROM LoadInformation;"));
	sqlite3_prepare_v2(pDataBase, TCHAR_TO_UTF8(*SQL), -1, &stmt, NULL);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		LoadIDArray.Add(sqlite3_column_int(stmt, 0));
	}
	sqlite3_finalize(stmt);
	return LoadIDArray;
}
