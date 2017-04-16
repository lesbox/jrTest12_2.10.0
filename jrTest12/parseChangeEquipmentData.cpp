#include "BehaviourManager.h"

bool BehaviourManager::parseChangeEquipmentData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseChangeEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseChangeEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QJsonObject changeEquipmentData1 = jsonContent.object();

	if (true == getErrorInfo(changeEquipmentData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!changeEquipmentData1.contains("shipVO") || !changeEquipmentData1["shipVO"].isObject()) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("changeEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject shipVo = changeEquipmentData1["shipVO"].toObject();
		MiniNormalShipInformation shipTemp;

		if (false == shipTemp.fromQJsonObject(shipVo, errorManager)) {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("changeEquipmentData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
			return false;
		}

		jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
	}

	if (!changeEquipmentData1.contains("equipmentVo") || !changeEquipmentData1["equipmentVo"].isArray()) {
		errorManager.pushErrorInfo("equipmentVo");
		errorManager.pushErrorInfo("changeEquipmentData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray equipmentList = changeEquipmentData1["equipmentVo"].toArray();
		MiniEquipmentInformation equipmentTemp;

		for (int count = 0; count < equipmentList.size(); count++) {
			if (!equipmentList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("changeEquipmentData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			if (false == equipmentTemp.fromQJsonObject(equipmentList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("changeEquipmentData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.equipmentVo.insert(equipmentTemp.equipmentCid, equipmentTemp);
		}
	}

	handleChangeEquipmentData1();
	emit(behaviourComplete());
	return true;
}