#include "BehaviourManager.h"

bool BehaviourManager::parseDismantleData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseDismantleData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseDismantleData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject dismantleData1 = jsonContent.object();

	if (true == getErrorInfo(dismantleData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!dismantleData1.contains("userVo") || !dismantleData1["userVo"].isObject()) {
		errorManager.pushErrorInfo("userVo");
		errorManager.pushErrorInfo("dismantleData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject userVo = dismantleData1["userVo"].toObject();

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userVo, errorManager)) {
			errorManager.pushErrorInfo("userVo");
			errorManager.pushErrorInfo("dismantleData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!dismantleData1.contains("equipmentVo") || !dismantleData1["equipmentVo"].isArray()) {
		errorManager.pushErrorInfo("equipmentVo");
		errorManager.pushErrorInfo("dismantleData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray equipmentList = dismantleData1["equipmentVo"].toArray();
		MiniEquipmentInformation equipmentTemp;

		for (int count = 0; count < equipmentList.size(); count++) {
			if (!equipmentList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("dismantleData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == equipmentTemp.fromQJsonObject(equipmentList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("equipmentVo");
				errorManager.pushErrorInfo("dismantleData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.equipmentVo.insert(equipmentTemp.equipmentCid, equipmentTemp);
		}
	}

	if (!dismantleData1.contains("delShips") || !dismantleData1["delShips"].isArray()) {
		errorManager.pushErrorInfo("delShips");
		errorManager.pushErrorInfo("dismantleData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
		return false;
	}
	else {
		QJsonArray delShips = dismantleData1["delShips"].toArray();

		for (int count = 0; count < delShips.size(); count++) {
			valueTemp = (int)getDoubleFromQJsonValueRef(delShips[count], flagTemp);
			if (flagTemp != 0) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("delShips");
				errorManager.pushErrorInfo("dismantleData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.remove(valueTemp);
		}
	}

	handleDismantleData1();
	emit(behaviourComplete());
	return true;
}