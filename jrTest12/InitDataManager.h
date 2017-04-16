#ifndef _INITDATAMANAGER_
#define _INITDATAMANAGER_

#include "Commen.h"
#include "ErrorManager.h"

class MiniShipCard {
public:
	int cid;
	int type;
	QMap<int, int> dismantle;
	int evoCid;
	int evoToCid;
	double repairOilModulus;
	double repairSteelModulus;
	double repairTime;

public:
	MiniShipCard();
	~MiniShipCard();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniGlobalConfig {
public:
	QVector<int> resourceRecoveryTime;
	QVector<int> resourceRecoveryNum;

public:
	MiniGlobalConfig();
	~MiniGlobalConfig();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniInitDataManager {
public:
	QMap<int, MiniShipCard> shipCard;
	MiniGlobalConfig globalConfig;
	QMap<int, QString> errorCode;

public:
	MiniInitDataManager();
	~MiniInitDataManager();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};
#endif
