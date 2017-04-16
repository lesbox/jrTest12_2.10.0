#include "BattleDataManager.h"

MiniPveWarShipInformation::MiniPveWarShipInformation() {
	this->shipCid = 0;
	this->type = 0;
}

MiniPveWarShipInformation::~MiniPveWarShipInformation() {
	
}

bool MiniPveWarShipInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->shipCid = (int)getDoubleFromQJsonObject(data, "shipCid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("shipCid");
		return false;
	}

	this->type = (int)getDoubleFromQJsonObject(data, "type", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("type");
		return false;
	}

	return true;
}

MiniPveWarEnemyInformation::MiniPveWarEnemyInformation() {
	this->isFound = 0;

	this->canSkip = 0;
}

MiniPveWarEnemyInformation::~MiniPveWarEnemyInformation() {

}

bool MiniPveWarEnemyInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->isFound = (int)getDoubleFromQJsonObject(data, "isFound", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("isFound");
		return false;
	}

	this->enemyShips.clear();
	if (!data.contains("enemyShips") || !data["enemyShips"].isArray()) {
		errorManager.pushErrorInfo("enemyShips");
		return false;
	}
	else {
		QJsonArray enemyShipListTemp = data["enemyShips"].toArray();
		MiniPveWarShipInformation enemyShipTemp;

		for (int count = 0; count < enemyShipListTemp.size(); count++) {
			if (!enemyShipListTemp[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("enemyShips");
				return false;
			}

			if (false == enemyShipTemp.fromQJsonObject(enemyShipListTemp[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("enemyShips");
				return false;
			}

			this->enemyShips.append(enemyShipTemp);
		}
	}

	this->canSkip = (int)getDoubleFromQJsonObject(data, "canSkip", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("canSkip");
		return false;
	}

	return true;
}

MiniPveWarReport::MiniPveWarReport() {
	this->canDoNightWar = 0;
}

MiniPveWarReport::~MiniPveWarReport() {

}

bool MiniPveWarReport::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->canDoNightWar = (int)getDoubleFromQJsonObject(data, "canDoNightWar", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("canDoNightWar");
		return false;
	}

	return true;
}

MiniPveWarResult::MiniPveWarResult() {
	this->resultLevel = 0;
}

MiniPveWarResult::~MiniPveWarResult() {

}

bool MiniPveWarResult::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->resultLevel = (int)getDoubleFromQJsonObject(data, "resultLevel", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("resultLevel");
		return false;
	}

	return true;
}

MiniPveWarNodeInformation::MiniPveWarNodeInformation() {
	this->pveLevelEnd = 0;
	this->formation = 0;
	this->isNightWar = 0;
	this->isSkipSuccess = 0;
	this->nodeId = 0;


	this->spoils = 0;
	this->dropSpoils = 0;
	this->drop500 = 0;
	
}

MiniPveWarNodeInformation::~MiniPveWarNodeInformation() {

}

MiniPvpWarNodeInformation::MiniPvpWarNodeInformation() {
	this->formation = 0;
	this->isNightWar = 0;
}

MiniPvpWarNodeInformation::~MiniPvpWarNodeInformation() {

}

MiniPvpUserInformation::MiniPvpUserInformation() {
	this->uid = 0;
	this->resultLevel = 0;
}

MiniPvpUserInformation::~MiniPvpUserInformation() {

}

bool MiniPvpUserInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->uid = (int)getDoubleFromQJsonObject(data, "uid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("uid");
		return false;
	}

	this->resultLevel = (int)getDoubleFromQJsonObject(data, "resultLevel", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("resultLevel");
		return false;
	}

	return true;
}