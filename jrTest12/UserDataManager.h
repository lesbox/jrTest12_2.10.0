#ifndef _UD_USERDATAMANAGER_
#define _UD_USERDATAMANAGER_

#include "Commen.h"
#include "ErrorManager.h"

class MiniBattleProperty {
public:
	int hp;
	int oil;
	int ammo;
	int aluminium;
	double speed;

public:
	MiniBattleProperty();
	~MiniBattleProperty();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniNormalShipInformation {
public:
	int id;
	int level;
	QMap<int, int> equipment;
	int status;
	int shipCid;
	int fleetId;
	int isLocked;
	MiniBattleProperty battleProps;
	MiniBattleProperty battlePropsMax;

public:
	MiniNormalShipInformation();
	~MiniNormalShipInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniEquipmentInformation {
public:
	int equipmentCid;
	int num;

public:
	MiniEquipmentInformation();
	~MiniEquipmentInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniRepairDockInformation {
public:
	int id;
	int locked;
	uint endTime;
	int shipId;

public:
	MiniRepairDockInformation();
	~MiniRepairDockInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniNormalFleetInformation {
public:
	int id;
	int status;
	QVector<int> ships;

public:
	MiniNormalFleetInformation();
	~MiniNormalFleetInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPackageInformation {
public:
	int itemCid;
	int num;

public:
	MiniPackageInformation();
	~MiniPackageInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniTaskConditionInformation {
public:
	int totalAmount;
	int finishedAmount;

public:
	MiniTaskConditionInformation();
	~MiniTaskConditionInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniTaskInformation {
public:
	int taskCid;
	QVector<MiniTaskConditionInformation> condition;

public:
	MiniTaskInformation();
	~MiniTaskInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPveExploreLevelInformation {
public:
	int exploreId;
	int fleetId;
	uint endTime;

public:
	MiniPveExploreLevelInformation();
	~MiniPveExploreLevelInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniPveExploreInformation {
public:
	QMap<int, MiniPveExploreLevelInformation> levels;

public:
	MiniPveExploreInformation();
	~MiniPveExploreInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniContinueLoginAwardInformation {
public:
	int canGetDay;

public:
	MiniContinueLoginAwardInformation();
	~MiniContinueLoginAwardInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniMarketingInformation {
public:
	MiniContinueLoginAwardInformation continueLoginAward;

public:
	MiniMarketingInformation();
	~MiniMarketingInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class MiniCampaignPassInformation {
public:
	int remainNum;

public:
	MiniCampaignPassInformation();
	~MiniCampaignPassInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
};

class UserResourceInformation {
public:
	int gold;
	double oil;
	double ammo;
	double steel;
	double aluminium;

	uint lastUpdateTime;

public:
	UserResourceInformation();
	~UserResourceInformation();

	bool fromQJsonObject(QJsonObject data, ErrorManager & errorManager);
}; 

class MiniPveNodeInformation {
public:
	QMap<int, int> nodeInfo;

public:
	MiniPveNodeInformation();
	~MiniPveNodeInformation();

	bool fromQJsonArray(QJsonArray data, ErrorManager & errorManager);
};

class MiniUserDataManager {
public:
	QString username;
	QString pwd;
	int currentServer;

	//game data
	int userId;
	UserResourceInformation userResourceVo;
	int shipNumTop;
	QMap<int, MiniNormalShipInformation> userShipVo;
	QMap<int, MiniEquipmentInformation> equipmentVo;
	QMap<int, MiniRepairDockInformation> repairDockVo;
	QMap<int, MiniNormalFleetInformation> fleetVo;
	QMap<int, MiniPackageInformation> packageVo;
	QMap<int, MiniTaskInformation> taskVo;
	MiniPveExploreInformation pveExploreVo;
	MiniMarketingInformation marketingData;
	MiniCampaignPassInformation passInfo;
	MiniPveNodeInformation pveNodeInfo;

public:
	MiniUserDataManager();
	~MiniUserDataManager();
};

#endif