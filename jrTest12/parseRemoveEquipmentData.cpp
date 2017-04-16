#include "BehaviourManager.h"

bool BehaviourManager::parseRemoveEquipmentData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseRemoveEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseRemoveEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QJsonObject removeEquipmentData1 = jsonContent.object();

	if (true == getErrorInfo(removeEquipmentData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!removeEquipmentData1.contains("shipVO") || !removeEquipmentData1["shipVO"].isObject()) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("removeEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject shipVo = removeEquipmentData1["shipVO"].toObject();
		MiniNormalShipInformation shipTemp;

		if (false == shipTemp.fromQJsonObject(shipVo, errorManager)) {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("removeEquipmentData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
			return false;
		}

		jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
	}

	if (!removeEquipmentData1.contains("equipmentVo") || !removeEquipmentData1["equipmentVo"].isArray()) {
		errorManager.pushErrorInfo("equipmentVo");
		errorManager.pushErrorInfo("removeEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray equipmentList = removeEquipmentData1["equipmentVo"].toArray();
		MiniEquipmentInformation equipmentTemp;

		for (int count = 0; count < equipmentList.size(); count++) {
			if (!equipmentList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("removeEquipmentData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			if (false == equipmentTemp.fromQJsonObject(equipmentList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("removeEquipmentData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.equipmentVo.insert(equipmentTemp.equipmentCid, equipmentTemp);
		}
	}

	handleRemoveEquipmentData1();
	emit(behaviourComplete());
	return true;
}