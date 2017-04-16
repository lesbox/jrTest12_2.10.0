#include "BehaviourManager.h"

bool BehaviourManager::parseCampaignData1() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCampaignData1");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCampaignData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject campaignData1 = jsonContent.object();

	if (true == getErrorInfo(campaignData1)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (!campaignData1.contains("enemyVO") || !campaignData1["enemyVO"].isObject()) {
		errorManager.pushErrorInfo("enemyVO");
		errorManager.pushErrorInfo("campaignData1");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject enemyVo = campaignData1["enemyVO"].toObject();

		if (false == dynamicParameters.currentCampaignInfo.campaignNode.enemyVo.fromQJsonObject(enemyVo, errorManager)) {
			errorManager.pushErrorInfo("enemyVO");
			errorManager.pushErrorInfo("campaignData1");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	handleCampaignData1();
	return true;
}

bool BehaviourManager::parseCampaignData2() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCampaignData2");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCampaignData2");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject campaignData2 = jsonContent.object();

	if (true == getErrorInfo(campaignData2)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (campaignData2.contains("userResVo")) {
		if (!campaignData2["userResVo"].isObject()) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("campaignData2");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject userResVo = campaignData2["userResVo"].toObject();

			if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
				errorManager.pushErrorInfo("userResVo");
				errorManager.pushErrorInfo("campaignData2");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	if (campaignData2.contains("warReport")) {
		if (!campaignData2["warReport"].isObject()) {
			errorManager.pushErrorInfo("warReport");
			errorManager.pushErrorInfo("campaignData2");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject warReport = campaignData2["warReport"].toObject();

			if (false == dynamicParameters.currentCampaignInfo.campaignNode.warReport.fromQJsonObject(warReport, errorManager)) {
				errorManager.pushErrorInfo("warReport");
				errorManager.pushErrorInfo("campaignData2");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	handleCampaignData2();
	return true;
}

bool BehaviourManager::parseCampaignData3() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCampaignData3");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCampaignData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject campaignData3 = jsonContent.object();

	if (true == getErrorInfo(campaignData3)) {
		return false;
	}

	int flagTemp;
	int valueTemp;

	if (campaignData3.contains("updateTaskVo")) {
		if (!campaignData3["updateTaskVo"].isArray()) {
			errorManager.pushErrorInfo("updateTaskVo");
			errorManager.pushErrorInfo("campaignData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray taskList = campaignData3["updateTaskVo"].toArray();
			MiniTaskInformation taskTemp;

			for (int count = 0; count < taskList.size(); count++) {
				if (!taskList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("campaignData3");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == taskTemp.fromQJsonObject(taskList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("updateTaskVo");
					errorManager.pushErrorInfo("campaignData3");
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

	if (!campaignData3.contains("campaignVo") || !campaignData3["campaignVo"].isObject()) {
		errorHandler(QString("parseCampaignData3 error : campaignVo\n"));
		return false;
	}
	else {
		QJsonObject campaignVo = campaignData3["campaignVo"].toObject();

		if (!campaignVo.contains("passInfo") || !campaignVo["passInfo"].isObject()) {
			errorManager.pushErrorInfo("passInfo");
			errorManager.pushErrorInfo("campaignVo");
			errorManager.pushErrorInfo("campaignData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject passInfo = campaignVo["passInfo"].toObject();

			if (false == jrData.userInfo.passInfo.fromQJsonObject(passInfo, errorManager)) {
				errorManager.pushErrorInfo("passInfo");
				errorManager.pushErrorInfo("campaignVo");
				errorManager.pushErrorInfo("campaignData3");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			dynamicParameters.canCampaign = false;
			if (jrData.userInfo.passInfo.remainNum > 0) {
				dynamicParameters.canCampaign = true;
			}
		}
	}

	if (campaignData3.contains("packageVo")) {
		if (!campaignData3["packageVo"].isArray()) {
			errorManager.pushErrorInfo("packageVo");
			errorManager.pushErrorInfo("campaignData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonArray packageList = campaignData3["packageVo"].toArray();
			MiniPackageInformation packageTemp;

			for (int count = 0; count < packageList.size(); count++) {
				if (!packageList[count].isObject()) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("campaignData3");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				if (false == packageTemp.fromQJsonObject(packageList[count].toObject(), errorManager)) {
					errorManager.pushErrorInfo(QString::number(count));
					errorManager.pushErrorInfo("packageVo");
					errorManager.pushErrorInfo("campaignData3");
					errorHandler(errorManager.getErrorInfo());
					(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
					emit(behaviourComplete());
					return false;
				}

				jrData.userInfo.packageVo.insert(packageTemp.itemCid, packageTemp);
			}
		}
	}

	if (campaignData3.contains("userResVo")) {
		if (!campaignData3["userResVo"].isObject()) {
			errorManager.pushErrorInfo("userResVo");
			errorManager.pushErrorInfo("campaignData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
		else {
			QJsonObject userResVo = campaignData3["userResVo"].toObject();

			if (false == jrData.userInfo.userResourceVo.fromQJsonObject(userResVo, errorManager)) {
				errorManager.pushErrorInfo("userResVo");
				errorManager.pushErrorInfo("campaignData3");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}
		}
	}

	if (!campaignData3.contains("warResult") || !campaignData3["warResult"].isObject()) {
		errorManager.pushErrorInfo("warResult");
		errorManager.pushErrorInfo("campaignData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject warResult = campaignData3["warResult"].toObject();

		if (false == dynamicParameters.currentCampaignInfo.campaignNode.warResult.fromQJsonObject(warResult, errorManager)) {
			errorManager.pushErrorInfo("warResult");
			errorManager.pushErrorInfo("campaignData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}
	}

	if (!campaignData3.contains("shipVO")) {
		errorManager.pushErrorInfo("shipVO");
		errorManager.pushErrorInfo("campaignData3");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonArray userShipList;
		MiniNormalShipInformation shipTemp;

		if (campaignData3["shipVO"].isObject()) {
			userShipList.append(campaignData3["shipVO"].toObject());
		}
		else if (campaignData3["shipVO"].isArray()) {
			userShipList = campaignData3["shipVO"].toArray();
		}
		else {
			errorManager.pushErrorInfo("shipVO");
			errorManager.pushErrorInfo("campaignData3");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		for (int count = 0; count < userShipList.size(); count++) {
			if (!userShipList[count].isObject()) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("campaignData3");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			if (false == shipTemp.fromQJsonObject(userShipList[count].toObject(), errorManager)) {
				errorManager.pushErrorInfo(QString::number(count));
				errorManager.pushErrorInfo("shipVOs");
				errorManager.pushErrorInfo("campaignData3");
				errorHandler(errorManager.getErrorInfo());
				(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
				emit(behaviourComplete());
				return false;
			}

			jrData.userInfo.userShipVo.insert(shipTemp.id, shipTemp);
		}
	}

	handleCampaignData3();
	return true;
}

bool BehaviourManager::parseCampaignData4() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCampaignData4");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCampaignData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject campaignData4 = jsonContent.object();

	if (true == getErrorInfo(campaignData4)) {
		return false;
	}

	if (!campaignData4.contains("marketingData") || !campaignData4["marketingData"].isObject()) {
		errorManager.pushErrorInfo("marketingData");
		errorManager.pushErrorInfo("campaignData4");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject marketingData = campaignData4["marketingData"].toObject();

		if (false == jrData.userInfo.marketingData.fromQJsonObject(marketingData, errorManager)) {
			errorManager.pushErrorInfo("marketingData");
			errorManager.pushErrorInfo("campaignData4");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		updateLoginAwardStatus();
	}

	handleCampaignData4();
	return true;
}

bool BehaviourManager::parseCampaignData5() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCampaignData5");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCampaignData5");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject campaignData5 = jsonContent.object();

	if (true == getErrorInfo(campaignData5)) {
		return false;
	}

	handleCampaignData5();
	return true;
}

bool BehaviourManager::parseCampaignData6() {
	QJsonDocument jsonContent;
	ErrorManager errorManager;

	if (false == handleResponse(jsonContent, errorManager)) {
		errorManager.pushErrorInfo("parseCampaignData6");
		errorHandler(errorManager.getErrorInfo());
		return false;
	}

	if (!jsonContent.isObject()) {
		errorManager.pushErrorInfo("jsonContent type error");
		errorManager.pushErrorInfo("parseCampaignData6");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}

	QJsonObject campaignData6 = jsonContent.object();

	if (true == getErrorInfo(campaignData6)) {
		return false;
	}

	if (!campaignData6.contains("passInfo") || !campaignData6["passInfo"].isObject()) {
		errorManager.pushErrorInfo("passInfo");
		errorManager.pushErrorInfo("campaignData6");
		errorHandler(errorManager.getErrorInfo());
		(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
		emit(behaviourComplete());
		return false;
	}
	else {
		QJsonObject passInfo = campaignData6["passInfo"].toObject();

		if (false == jrData.userInfo.passInfo.fromQJsonObject(passInfo, errorManager)) {
			errorManager.pushErrorInfo("passInfo");
			errorManager.pushErrorInfo("campaignData6");
			errorHandler(errorManager.getErrorInfo());
			(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
			emit(behaviourComplete());
			return false;
		}

		dynamicParameters.canCampaign = false;
		if (jrData.userInfo.passInfo.remainNum > 0) {
			dynamicParameters.canCampaign = true;
		}
	}

	handleCampaignData6();
	emit(behaviourComplete());
	return true;
}
