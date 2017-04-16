#include "BehaviourManager.h"

bool BehaviourManager::parsePveExploreCompleteData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parsePveExploreCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parsePveExploreCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject pveExploreCompleteData1 = jsonContent.object();

	if (true == getErrorInfo(pveExploreCompleteData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (pveExploreCompleteData1.contains("updateTaskVo")) {
		if (!pveExploreCompleteData1["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("pveExploreCompleteData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = pveExploreCompleteData1["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("pveExploreCompleteData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("pveExploreCompleteData1");
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

	if (pveExploreCompleteData1.contains("packageVo")) {
		if (!pveExploreCompleteData1["packageVo"].isArray()) {
			errorManager.pushErrorInfo("packageVo");
			errorManager.pushErrorInfo("pveExploreCompleteData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray packageList = pveExploreCompleteData1["packageVo"].toArray();
			MiniPackageInformation packageTemp;

			for (int count = 0; count < packageList.size(); count++) {
				if (!packageList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("pveExploreCompleteData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == packageTemp.fromQJsonObject(packageList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("pveExploreCompleteData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.packageVo.insert(packageTemp.itemCid, packageTemp);
			}
		}
	}

	if (!pveExploreCompleteData1.contains("userResVo") || !pveExploreCompleteData1["userResVo"].isObject()) {
		errorManager.pushErrorInfo("userResVo");
		errorManager.pushErrorInfo("pveExploreCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject userResVo = pveExploreCompleteData1["userResVo"].toObject();

		if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("pveExploreCompleteData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!pveExploreCompleteData1.contains("pveExploreVo") || !pveExploreCompleteData1["pveExploreVo"].isObject()) {
		errorManager.pushErrorInfo("pveExploreVo");
		errorManager.pushErrorInfo("pveExploreCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject pveExplore = pveExploreCompleteData1["pveExploreVo"].toObject();

		if (false == jrData.userInfo.pveExploreVo.fromQJsonObject(pveExplore, errorManager)) {
			errorManager.pushErrorInfo("pveExploreVo");
			errorManager.pushErrorInfo("pveExploreCompleteData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!pveExploreCompleteData1.contains("fleetVo") || !pveExploreCompleteData1["fleetVo"].isArray()) {
		errorManager.pushErrorInfo("fleetVo");
		errorManager.pushErrorInfo("pveExploreCompleteData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray fleetList = pveExploreCompleteData1["fleetVo"].toArray();
		MiniNormalFleetInformation fleetTemp;

		for (int count = 0; count < fleetList.size(); count++) {
			if (!fleetList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("pveExploreCompleteData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == fleetTemp.fromQJsonObject(fleetList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("fleetVo");
				errorManager.pushErrorInfo("pveExploreCompleteData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.fleetVo.insert(fleetTemp.id, fleetTemp);
		}

		PveExploreCompleteBehaviourParameter pveExploreCompleteBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PveExploreCompleteBehaviourParameter>();

		if (pveExploreCompleteBehaviourParameterTemp.pveExploreId == staticParameters.pveExploreConfig[staticParameters.activeFleetId]) {
			if (!(*getParentBehaviour()).behaviourReturnValues.contains(ErrorCode::ActiveFleetIdle)) {
				(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::ActiveFleetIdle, QVariant());
			}
		}
		else {
			if (!(*getParentBehaviour()).behaviourReturnValues.contains(ErrorCode::NonactiveFleetIdle)) {
				(*getParentBehaviour()).behaviourReturnValues.insert(ErrorCode::NonactiveFleetIdle, QVariant());
			}
		}
	}

	handlePveExploreCompleteData1();
	emit(behaviourComplete());
	return true;
}