#include "BehaviourManager.h"

bool BehaviourManager::parseGetLoginAwardData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseGetLoginAwardData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseGetLoginAwardData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject getLoginAwardData1 = jsonContent.object();

	if (true == getErrorInfo(getLoginAwardData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (getLoginAwardData1.contains("userResVo")) {
		if (!getLoginAwardData1["userResVo"].isObject()) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("getLoginAwardData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject userResVo = getLoginAwardData1["userResVo"].toObject();

			if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
				errorManager.pushErrorInfo("userResVo");
				errorManager.pushErrorInfo("getLoginAwardData1");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	if (getLoginAwardData1.contains("packageVo")) {
		if (!getLoginAwardData1["packageVo"].isArray()) {
			errorManager.pushErrorInfo("packageVo");
			errorManager.pushErrorInfo("getLoginAwardData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray packageList = getLoginAwardData1["packageVo"].toArray();
			MiniPackageInformation packageTemp;

			for (int count = 0; count < packageList.size(); count++) {
				if (!packageList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("getLoginAwardData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == packageTemp.fromQJsonObject(packageList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("getLoginAwardData1");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.packageVo.insert(packageTemp.itemCid, packageTemp);
			}
		}
	}

	if (!getLoginAwardData1.contains("marketingData") || !getLoginAwardData1["marketingData"].isObject()) {
		errorManager.pushErrorInfo("marketingData");
		errorManager.pushErrorInfo("getLoginAwardData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject marketingData = getLoginAwardData1["marketingData"].toObject();

		if (false == jrData.userInfo.marketingData.fromQJsonObject(marketingData, errorManager)) {
			errorManager.pushErrorInfo("marketingData");
			errorManager.pushErrorInfo("getLoginAwardData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		updateLoginAwardStatus();
	}

	handleGetLoginAwardData1();
	emit(behaviourComplete());
	return true;
}