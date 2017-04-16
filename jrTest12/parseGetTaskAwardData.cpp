#include "BehaviourManager.h"

bool BehaviourManager::parseGetTaskAwardData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseGetTaskAwardData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseGetTaskAwardData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject getTaskAwardData1 = jsonContent.object();

	if (true == getErrorInfo(getTaskAwardData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (getTaskAwardData1.contains("userResVo")) {
		if (!getTaskAwardData1["userResVo"].isObject()) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("getTaskAwardData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject userResVo = getTaskAwardData1["userResVo"].toObject();

			if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
				errorManager.pushErrorInfo("userResVo");
				errorManager.pushErrorInfo("getTaskAwardData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	if (getTaskAwardData1.contains("taskVo")) {
		if (!getTaskAwardData1["taskVo"].isArray()) {
			errorManager.pushErrorInfo("taskVo");
			errorManager.pushErrorInfo("getTaskAwardData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = getTaskAwardData1["taskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("taskVo");
					errorManager.pushErrorInfo("getTaskAwardData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("taskVo");
					errorManager.pushErrorInfo("getTaskAwardData1");
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

	if (getTaskAwardData1.contains("packageVo")) {
		if (!getTaskAwardData1["packageVo"].isArray()) {
			errorManager.pushErrorInfo("packageVo");
			errorManager.pushErrorInfo("getTaskAwardData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray packageList = getTaskAwardData1["packageVo"].toArray();
			MiniPackageInformation packageTemp;

			for (int count = 0; count < packageList.size(); count++) {
				if (!packageList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("getTaskAwardData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == packageTemp.fromQJsonObject(packageList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("getTaskAwardData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.packageVo.insert(packageTemp.itemCid, packageTemp);
			}
		}
	}

	GetTaskAwardBehaviourParameter getTaskAwardBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<GetTaskAwardBehaviourParameter>();

	jrData.userInfo.taskVo.remove(getTaskAwardBehaviourParameterTemp.taskId);

	handleGetTaskAwardData1();
	emit(behaviourComplete());
	return true;
}