#ifndef _UD_BATTLEDATAMANAGER_
#define _UD_BATTLEDATAMANAGER_

#include "Commen.h"
#include "ErrorManager.h"

class MiniPveWarShipInformation {
public:
	int shipCid;
	int type;

public:
	MiniPveWarShipInformation();
	~MiniPveWarShipInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPveWarEnemyInformation {
public:
	int isFound;
	QVector<MiniPveWarShipInformation> enemyShips;
	int canSkip;

public:
	MiniPveWarEnemyInformation();
	~MiniPveWarEnemyInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPveWarReport {
public:
	int canDoNightWar;

public:
	MiniPveWarReport();
	~MiniPveWarReport();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPveWarResult {
public:
	int resultLevel;

public:
	MiniPveWarResult();
	~MiniPveWarResult();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPveWarNodeInformation {
public:
	int pveLevelEnd;
	int formation;
	int isNightWar;
	int isSkipSuccess;
	int nodeId;
	MiniPveWarEnemyInformation enemyVo;
	MiniPveWarReport warReport;
	int spoils;
	int dropSpoils;
	int drop500;
	MiniPveWarResult warResult;

public:
	MiniPveWarNodeInformation();
	~MiniPveWarNodeInformation();
};

class MiniPvpWarNodeInformation {
public:
	int formation;
	int isNightWar;

	MiniPveWarEnemyInformation enemyVo;
	MiniPveWarReport warReport;
	MiniPveWarResult warResult;

public:
	MiniPvpWarNodeInformation();
	~MiniPvpWarNodeInformation();
};

class MiniPvpUserInformation {
public:
	int uid;
	int resultLevel;

public:
	MiniPvpUserInformation();
	~MiniPvpUserInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};
#endif // !_UD_BATTLEINFORMATION_

