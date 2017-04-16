#include "BehaviourManager.h"

bool BehaviourManager::parseInstantRepairMultiShipData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseInstantRepairMultiShipData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseInstantRepairMultiShipData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject instantRepairMultiShipData1 = jsonContent.object();

	if (true == getErrorInfo(instantRepairMultiShipData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!instantRepairMultiShipData1.contains("packageVo") || !instantRepairMultiShipData1["packageVo"].isArray()) {
		errorManager.pushErrorInfo("packageVo");
		errorManager.pushErrorInfo("instantRepairMultiShipData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray packageList = instantRepairMultiShipData1["packageVo"].toArray();
		MiniPackageInformation packageTemp;

		for (int count = 0; count < packageList.size(); count++) {
			if (!packageList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("packageVo");
				errorManager.pushErrorInfo("instantRepairMultiShipData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == packageTemp.fromQJsonObject(packageList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("packageVo");
				errorManager.pushErrorInfo("instantRepairMultiShipData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.packageVo.insert(packageTemp.itemCid, packageTemp);
		}
	}

	if (!instantRepairMultiShipData1.contains("userVo") || !instantRepairMultiShipData1["userVo"].isObject()) {
		errorManager.pushErrorInfo("userVo");
		errorManager.pushErrorInfo("instantRepairMultiShipData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject userVo = instantRepairMultiShipData1["userVo"].toObject();

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userVo, errorManager)) {
			errorManager.pushErrorInfo("userVo");
			errorManager.pushErrorInfo("instantRepairMultiShipData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!instantRepairMultiShipData1.contains("shipVOs") || !instantRepairMultiShipData1["shipVOs"].isArray()) {
		errorManager.pushErrorInfo("shipVOs");
		errorManager.pushErrorInfo("instantRepairMultiShipData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userShipList = instantRepairMultiShipData1["shipVOs"].toArray();
		MiniNormalShipInformation shipTemp;

		for (int count = 0; count < userShipList.size(); count++) {
			if (!userShipList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("instantRepairMultiShipData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == shipTemp.fromQJsonObject(userShipList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("instantRepairMultiShipData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
		}
	}

	if (instantRepairMultiShipData1.contains("updateTaskVo")) {
		if (!instantRepairMultiShipData1["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("instantRepairMultiShipData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = instantRepairMultiShipData1["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("instantRepairMultiShipData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("instantRepairMultiShipData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.taskVo.insert(taskTemp.taskCid, taskTemp);
			}

			updateTaskAwardStatus();
		}
	}

	if (instantRepairMultiShipData1.contains("repairDockVo")) {
		if (!instantRepairMultiShipData1["repairDockVo"].isArray()) {
			errorManager.pushErrorInfo("repairDockVo");
			errorManager.pushErrorInfo("instantRepairMultiShipData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray dockList = instantRepairMultiShipData1["repairDockVo"].toArray();
			MiniRepairDockInformation dockTemp;

			for (int count = 0; count < dockList.size(); count++) {
				if (!dockList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("repairDockVo");
					errorManager.pushErrorInfo("instantRepairMultiShipData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == dockTemp.fromQJsonObject(dockList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("repairDockVo");
					errorManager.pushErrorInfo("instantRepairMultiShipData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.repairDockVo.insert(dockTemp.id, dockTemp);
			}

			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::RepairDockIdle, QVariant());
		}
	}

	handleInstantRepairMultiShipData1();
	emit(behaviourComplete());
	return true;
}