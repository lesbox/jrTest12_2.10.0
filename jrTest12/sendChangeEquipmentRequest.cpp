#include "BehaviourManager.h"

bool BehaviourManager::sendChangeEquipmentRequest1() {
	currentRequestId = RequestId::ChangeEquipmentRequest1;

	ChangeEquipmentBehaviourParameter changeEquipmentBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<ChangeEquipmentBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/changeEquipment/") + QString::number(changeEquipmentBehaviourParameterTemp.shipId) + QString("/") + QString::number(changeEquipmentBehaviourParameterTemp.equipmentCid) + QString("/") + QString::number(changeEquipmentBehaviourParameterTemp.equipmentPos));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseChangeEquipmentData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}