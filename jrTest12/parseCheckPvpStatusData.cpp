#include "BehaviourManager.h"

bool BehaviourManager::parseCheckPvpStatusData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCheckPvpStatusData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCheckPvpStatusData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}

	QJsonObject checkPvpStatusData1 = jsonContent.object();

	if (true == getErrorInfo(checkPvpStatusData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	dynamicParameters.pvpUserInfoList.clear();//attention
	if (!checkPvpStatusData1.contains("list") || !checkPvpStatusData1["list"].isArray()) {
		errorManager.pushErrorInfo("list");
		errorManager.pushErrorInfo("checkPvpStatusData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userlist = checkPvpStatusData1["list"].toArray();
		MiniPvpUserInformation userInfoTemp;

		for (int count = 0; count < userlist.size(); count++) {
			if (!userlist[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("list");
				errorManager.pushErrorInfo("checkPvpStatusData1");
				errorHandler(errorManager.getErrorInfo());
				return false;
			}

			if (false == userInfoTemp.fromQJsonObject(userlist[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("list");
				errorManager.pushErrorInfo("checkPvpStatusData1");
				errorHandler(errorManager.getErrorInfo());
				return false;
			}

			dynamicParameters.pvpUserInfoList.append(userInfoTemp);
		}

		dynamicParameters.canPvp = false;
		for (int count = 0; count < dynamicParameters.pvpUserInfoList.size(); count++) {
			if (dynamicParameters.pvpUserInfoList[count].resultLevel == 0) {
				dynamicParameters.canPvp = true;
			}
		}
	}

	handleCheckPvpStatusData1();
	emit(behaviourComplete());
	return true;
}