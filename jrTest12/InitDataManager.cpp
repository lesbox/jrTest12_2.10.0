#include "InitDataManager.h"

MiniShipCard::MiniShipCard() {
	this->cid = 0;
	this->type = 0;

	this->evoCid = 0;
	this->evoToCid = 0;
	this->repairOilModulus = 0;
	this->repairSteelModulus = 0;
	this->repairTime = 0;
}

MiniShipCard::~MiniShipCard() {

}

bool MiniShipCard::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->cid = (int)getDoubleFromQJsonObject(data, "cid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("cid");
		return false;
	}

	this->type = (int)getDoubleFromQJsonObject(data, "type", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("type");
		return false;
	}

	this->dismantle.clear();
	if (data.contains("dismantle")) {
		QJsonObject dismantle = data["dismantle"].toObject();
		bool flagTemp1;
		int valueTemp1;

		for each(QString key in dismantle.keys()) {
			valueTemp1 = key.toInt(&flagTemp1);
			if (flagTemp1 == false) {
				errorManager.pushErrorInfo(key);
				errorManager.pushErrorInfo("dismantle");
				return false;
			}
			valueTemp = (int)getDoubleFromQJsonObject(dismantle, key, flagTemp);
			if (flagTemp != 0) {
				errorManager.pushErrorInfo(key);
				errorManager.pushErrorInfo("dismantle");
				return false;
			}
			this->dismantle.insert(valueTemp1, valueTemp);
		}
	}

	this->evoCid = (int)getDoubleFromQJsonObject(data, "evoCid", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("evoCid");
		return false;
	}

	this->evoToCid = (int)getDoubleFromQJsonObject(data, "evoToCid", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("evoToCid");
		return false;
	}

	this->repairOilModulus = getDoubleFromQJsonObject(data, "repairOilModulus", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("repairOilModulus");
		return false;
	}

	this->repairSteelModulus = getDoubleFromQJsonObject(data, "repairSteelModulus", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("repairSteelModulus");
		return false;
	}

	this->repairTime = getDoubleFromQJsonObject(data, "repairTime", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("repairTime");
		return false;
	}

	return true;
}

MiniGlobalConfig::MiniGlobalConfig() {

}

MiniGlobalConfig::~MiniGlobalConfig() {

}

bool MiniGlobalConfig::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->resourceRecoveryTime.clear();
	if (!data.contains("resourceRecoveryTime") || !data["resourceRecoveryTime"].isArray()) {
		errorManager.pushErrorInfo("resourceRecoveryTime");
		return false;
	}
	else {
		QJsonArray resourceRecoveryTime = data["resourceRecoveryTime"].toArray();

		for (int count = 0; count < resourceRecoveryTime.size(); count++) {
			valueTemp = (int)getDoubleFromQJsonValueRef(resourceRecoveryTime[count], flagTemp);
			if (flagTemp != 0) {
				return false;
			}
			this->resourceRecoveryTime.append(valueTemp);
		}
	}

	this->resourceRecoveryNum.clear();
	if (!data.contains("resourceRecoveryNum") || !data["resourceRecoveryNum"].isArray()) {
		errorManager.errorInfo = "resourceRecoveryNum";
		return false;
	}
	else {
		QJsonArray resourceRecoveryNum = data["resourceRecoveryNum"].toArray();

		for (int count = 0; count < resourceRecoveryNum.size(); count++) {
			valueTemp = (int)getDoubleFromQJsonValueRef(resourceRecoveryNum[count], flagTemp);
			if (flagTemp != 0) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("resourceRecoveryNum/");
				return false;
			}
			this->resourceRecoveryNum.append(valueTemp);
		}
	}

	return true;
}

MiniInitDataManager::MiniInitDataManager() {

}

MiniInitDataManager::~MiniInitDataManager() {

}

bool MiniInitDataManager::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->shipCard.clear();
	if (!data.contains("shipCard") || !data["shipCard"].isArray()) {
		errorManager.errorInfo = "shipCard";
		return false;
	}
	else {
		QJsonArray shipCard = data["shipCard"].toArray();
		MiniShipCard shipCardTemp;

		for (int count = 0; count < shipCard.size(); count++) {
			if (!shipCard[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipCard");
				return false;
			}
			if (false == shipCardTemp.fromQJsonObject(shipCard[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipCard");
				return false;
			}
			this->shipCard.insert(shipCardTemp.cid, shipCardTemp);
		}
	}

	if (!data.contains("globalConfig") || !data["globalConfig"].isObject()) {
		errorManager.pushErrorInfo("globalConfig");
		return false;
	}
	else {
		if (false == this->globalConfig.fromQJsonObject(data["globalConfig"].toObject(), errorManager)) {
			errorManager.pushErrorInfo("globalConfig");
			return false;
		}
	}

	this->errorCode.clear();
	if (!data.contains("errorCode") || !data["errorCode"].isObject()) {
		errorManager.errorInfo = "errorCode";
		return false;
	}
	else {
		QJsonObject errorCode = data["errorCode"].toObject();
		int keyValueTemp;
		QString stringValueTemp;
		bool flagTemp1;

		for each(QString key in errorCode.keys()) {
			keyValueTemp = key.toInt(&flagTemp1);
			if (flagTemp1 == false) {
				errorManager.pushErrorInfo(key);
				errorManager.pushErrorInfo("errorCode");
				return false;
			}
			stringValueTemp = getStringFromQJsonObject(errorCode, key, flagTemp);
			if (flagTemp != 0) {
				errorManager.pushErrorInfo(key);
				errorManager.pushErrorInfo("errorCode");
				return false;
			}
			this->errorCode.insert(keyValueTemp, stringValueTemp);
		}
	}

	return true;
}