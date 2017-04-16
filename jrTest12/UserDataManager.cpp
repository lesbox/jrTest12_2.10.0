#include "UserDataManager.h"

MiniBattleProperty::MiniBattleProperty() {
	this->hp = 0;
	this->oil = 0;
	this->ammo = 0;
	this->aluminium = 0;
}

MiniBattleProperty::~MiniBattleProperty() {

}

bool MiniBattleProperty::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->hp = (int)getDoubleFromQJsonObject(data, "hp", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("hp");
		return false;
	}

	this->oil = (int)getDoubleFromQJsonObject(data, "oil", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("oil");
		return false;
	}

	this->ammo = (int)getDoubleFromQJsonObject(data, "ammo", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("ammo");
		return false;
	}

	this->aluminium = (int)getDoubleFromQJsonObject(data, "aluminium", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("aluminium");
		return false;
	}

	this->speed = (int)getDoubleFromQJsonObject(data, "speed", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("speed");
		return false;
	}

	return true;
}

MiniNormalShipInformation::MiniNormalShipInformation() {
	this->id = 0;
	this->level = 0;

	this->status = 0;
	this->shipCid = 0;
	this->fleetId = 0;
	this->isLocked = 0;


}

MiniNormalShipInformation::~MiniNormalShipInformation() {

}

bool MiniNormalShipInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->id = (int)getDoubleFromQJsonObject(data, "id", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("id");
		return false;
	}

	this->level = (int)getDoubleFromQJsonObject(data, "level", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("level");
		return false;
	}

	this->equipment.clear();
	if (!data.contains("equipment")) {
		errorManager.pushErrorInfo("equipment");
		return false;
	}
	else {
		if (data["equipment"].isArray()) {
			QJsonArray equipmentListTemp = data["equipment"].toArray();
			for (int count = 0; count < equipmentListTemp.size(); count++) {
				valueTemp = (int)getDoubleFromQJsonValueRef(equipmentListTemp[count], flagTemp);
				if (flagTemp != 0) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("equipment");
					return false;
				}
				this->equipment.insert(count, valueTemp);
			}
		}
		else if (data["equipment"].isObject()) {
			QJsonObject equipmentTemp = data["equipment"].toObject();
			bool flagTemp1;
			int equipmentPos;
			for each(QString key in equipmentTemp.keys()) {
				int equipmentPos = key.toInt(&flagTemp1);
				if (flagTemp1 == false) {
					errorManager.pushErrorInfo(key);
					errorManager.pushErrorInfo("equipment");
					return false;
				}
				valueTemp = (int)getDoubleFromQJsonValueRef(equipmentTemp[key], flagTemp);
				if (flagTemp != 0) {
					errorManager.pushErrorInfo(key);
					errorManager.pushErrorInfo("equipment");
					return false;
				}
				this->equipment.insert(equipmentPos, valueTemp);
			}
		}
		else {
			errorManager.pushErrorInfo("equipment");
			return false;
		}
	}

	this->status = (int)getDoubleFromQJsonObject(data, "status", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("status");
		return false;
	}

	this->shipCid = (int)getDoubleFromQJsonObject(data, "shipCid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("shipCid");
		return false;
	}

	this->fleetId = (int)getDoubleFromQJsonObject(data, "fleetId", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("fleetId");
		return false;
	}

	this->isLocked = (int)getDoubleFromQJsonObject(data, "isLocked", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("isLocked");
		return false;
	}

	if (!data.contains("battleProps") || !data["battleProps"].isObject()) {
		errorManager.pushErrorInfo("battleProps");
		return false;
	}
	else {
		if (false == this->battleProps.fromQJsonObject(data["battleProps"].toObject(), errorManager)) {
			errorManager.pushErrorInfo("battleProps");
			return false;
		}
	}

	if (!data.contains("battlePropsMax") || !data["battlePropsMax"].isObject()) {
		errorManager.pushErrorInfo("battlePropsMax");
		return false;
	}
	else {
		if (false == this->battlePropsMax.fromQJsonObject(data["battlePropsMax"].toObject(), errorManager)) {
			errorManager.pushErrorInfo("battlePropsMax");
			return false;
		}

		this->battlePropsMax.speed = this->battleProps.speed;
	}

	return true;
}

MiniEquipmentInformation::MiniEquipmentInformation() {
	this->equipmentCid = 0;
	this->num = 0;
}

MiniEquipmentInformation::~MiniEquipmentInformation() {

}

bool MiniEquipmentInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->equipmentCid = (int)getDoubleFromQJsonObject(data, "equipmentCid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("equipmentCid");
		return false;
	}

	this->num = (int)getDoubleFromQJsonObject(data, "num", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("num");
		return false;
	}

	return true;
}

MiniRepairDockInformation::MiniRepairDockInformation() {
	this->id = 0;
	this->locked = 0;
	this->endTime = 0;
	this->shipId = 0;
}

MiniRepairDockInformation::~MiniRepairDockInformation(){

}

bool MiniRepairDockInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->id = (int)getDoubleFromQJsonObject(data, "id", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("id");
		return false;
	}

	this->locked = (int)getDoubleFromQJsonObject(data, "locked", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("locked");
		return false;
	}

	this->endTime = (uint)getDoubleFromQJsonObject(data, "endTime", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("endTime");
		return false;
	}

	this->shipId = (int)getDoubleFromQJsonObject(data, "shipId", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("shipId");
		return false;
	}

	return true;
}

MiniNormalFleetInformation::MiniNormalFleetInformation() {
	this->id = 0;
	this->status = 0;

}

MiniNormalFleetInformation::~MiniNormalFleetInformation() {

}

bool MiniNormalFleetInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->id = (int)getDoubleFromQJsonObject(data, "id", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("id");
		return false;
	}

	this->status = (int)getDoubleFromQJsonObject(data, "status", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("status");
		return false;
	}

	this->ships.clear();
	if (!data.contains("ships") || !data["ships"].isArray()) {
		errorManager.pushErrorInfo("ships");
		return false;
	}
	else {
		QJsonArray shipListTemp = data["ships"].toArray();
		for (int count = 0; count < shipListTemp.size(); count++) {
			valueTemp = (int)getDoubleFromQJsonValueRef(shipListTemp[count], flagTemp);
			if (flagTemp != 0) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("ships");
				return false;
			}
			this->ships.append(valueTemp);
		}
	}

	return true;
}

MiniPackageInformation::MiniPackageInformation() {
	this->itemCid = 0;
	this->num = 0;
}

MiniPackageInformation::~MiniPackageInformation() {

}

bool MiniPackageInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->itemCid = (int)getDoubleFromQJsonObject(data, "itemCid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("itemCid");
		return false;
	}

	this->num = (int)getDoubleFromQJsonObject(data, "num", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("num");
		return false;
	}

	return true;
}

MiniTaskConditionInformation::MiniTaskConditionInformation() {
	this->totalAmount = 0;
	this->finishedAmount = 0;
}

MiniTaskConditionInformation::~MiniTaskConditionInformation() {

}

bool MiniTaskConditionInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	auto test = data.keys();

	this->totalAmount = (int)getDoubleFromQJsonObject(data, "totalAmount", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("totalAmount");
		return false;
	}

	this->finishedAmount = (int)getDoubleFromQJsonObject(data, "finishedAmount", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("finishedAmount");
		return false;
	}

	return true;
}

MiniTaskInformation::MiniTaskInformation() {
	this->taskCid = 0;
	
}

MiniTaskInformation::~MiniTaskInformation() {

}

bool MiniTaskInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->taskCid = (int)getDoubleFromQJsonObject(data, "taskCid", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("taskCid");
		return false;
	}

	this->condition.clear();
	if (!data.contains("condition") || !data["condition"].isArray()) {
		errorManager.pushErrorInfo("condition");
		return false;
	}
	else {
		QJsonArray conditionListTemp = data["condition"].toArray();
		MiniTaskConditionInformation conditionTemp;

		for (int count = 0; count < conditionListTemp.size(); count++) {
			if (!conditionListTemp[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("condition");
				return false;
			}

			if (false == conditionTemp.fromQJsonObject(conditionListTemp[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("condition");
				return false;
			}

			this->condition.append(conditionTemp);
		}
	}

	return true;
}

MiniPveExploreLevelInformation::MiniPveExploreLevelInformation() {
	this->exploreId = 0;
	this->fleetId = 0;
	this->endTime = 0;
}

MiniPveExploreLevelInformation::~MiniPveExploreLevelInformation() {

}

bool MiniPveExploreLevelInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->exploreId = (int)getDoubleFromQJsonObject(data, "exploreId", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("exploreId");
		return false;
	}

	this->fleetId = (int)getDoubleFromQJsonObject(data, "fleetId", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("fleetId");
		return false;
	}

	this->endTime = (uint)getDoubleFromQJsonObject(data, "endTime", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("endTime");
		return false;
	}

	return true;
}

MiniPveExploreInformation::MiniPveExploreInformation() {

}

MiniPveExploreInformation::~MiniPveExploreInformation() {

}

bool MiniPveExploreInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->levels.clear();
	if (!data.contains("levels") || !data["levels"].isArray()) {
		errorManager.pushErrorInfo("levels");
		return false;
	}
	else {
		QJsonArray levelListTemp = data["levels"].toArray();
		MiniPveExploreLevelInformation pveExploreLevelInformationTemp;

		for (int count = 0; count < levelListTemp.size(); count++) {
			if (!levelListTemp[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("levels");
				return false;
			}

			if (false == pveExploreLevelInformationTemp.fromQJsonObject(levelListTemp[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("levels");
				return false;
			}

			this->levels.insert(pveExploreLevelInformationTemp.exploreId, pveExploreLevelInformationTemp);
		}
	}

	return true;
}

MiniContinueLoginAwardInformation::MiniContinueLoginAwardInformation() {
	this->canGetDay = 0;
}

MiniContinueLoginAwardInformation::~MiniContinueLoginAwardInformation() {
	
}

bool MiniContinueLoginAwardInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->canGetDay = (int)getDoubleFromQJsonObject(data, "canGetDay", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("canGetDay");
		return false;
	}

	return true;
}

MiniMarketingInformation::MiniMarketingInformation() {

}

MiniMarketingInformation::~MiniMarketingInformation() {

}

bool MiniMarketingInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	if (!data.contains("continueLoginAward") || !data["continueLoginAward"].isObject()) {
		errorManager.pushErrorInfo("continueLoginAward");
		return false;
	}
	else {
		if (false == this->continueLoginAward.fromQJsonObject(data["continueLoginAward"].toObject(), errorManager)) {
			errorManager.pushErrorInfo("continueLoginAward");
			return false;
		}
	}

	return true;
}

UserResourceInformation::UserResourceInformation() {
	this->gold = 0;
	this->oil = 0;
	this->ammo = 0;
	this->steel = 0;
	this->aluminium = 0;

	this->lastUpdateTime = 0;
}

UserResourceInformation::~UserResourceInformation() {
	
}

bool UserResourceInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->gold = (int)getDoubleFromQJsonObject(data, "gold", flagTemp);
	if (flagTemp == 1) {
		errorManager.pushErrorInfo("gold");
		return false;
	}

	this->oil = (int)getDoubleFromQJsonObject(data, "oil", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("oil");
		return false;
	}

	this->ammo = (int)getDoubleFromQJsonObject(data, "ammo", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("ammo");
		return false;
	}

	this->steel = (int)getDoubleFromQJsonObject(data, "steel", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("steel");
		return false;
	}

	this->aluminium = (int)getDoubleFromQJsonObject(data, "aluminium", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("aluminium");
		return false;
	}

	this->lastUpdateTime = QDateTime::currentDateTime().toTime_t();

	return true;
}

MiniPveNodeInformation::MiniPveNodeInformation() {

}

MiniPveNodeInformation::~MiniPveNodeInformation() {

}

bool MiniPveNodeInformation::fromQJsonArray(QJsonArray data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->nodeInfo.clear();
	for (int count = 0; count < data.size(); count++) {
		if (!data[count].isObject()) {
			errorManager.pushErrorInfo(QString::number(count));
			return false;
		}

		int valueTemp1;

		valueTemp = (int)getDoubleFromQJsonObject(data[count].toObject(), "id", flagTemp);
		if(flagTemp != 0){
			errorManager.pushErrorInfo("id");
			errorManager.pushErrorInfo(QString::number(count));
			return false;
		}

		valueTemp1 = (int)getDoubleFromQJsonObject(data[count].toObject(), "nodeType", flagTemp);
		if (flagTemp != 0) {
			errorManager.pushErrorInfo("nodeType");
			errorManager.pushErrorInfo(QString::number(count));
			return false;
		}

		this->nodeInfo.insert(valueTemp, valueTemp1);
	}

	return true;
}

MiniCampaignPassInformation::MiniCampaignPassInformation() {
	this->remainNum = 0;
}

MiniCampaignPassInformation::~MiniCampaignPassInformation() {

}

bool MiniCampaignPassInformation::fromQJsonObject(QJsonObject data, ErrorManager & errorManager) {
	int flagTemp;
	int valueTemp;

	this->remainNum = (int)getDoubleFromQJsonObject(data, "remainNum", flagTemp);
	if (flagTemp != 0) {
		errorManager.pushErrorInfo("remainNum");
		return false;
	}

	return true;
}

MiniUserDataManager::MiniUserDataManager() {


	this->currentServer = 0;

	this->shipNumTop = 0;
	this->userId = 0;







}

MiniUserDataManager::~MiniUserDataManager() {

}