#include "BehaviourManager.h"

bool BehaviourManager::sendRemoveEquipmentRequest1() {
	currentRequestId = RequestId::RemoveEquipmentRequest1;

	RemoveEquipmentBehaviourParameter removeEquipmentBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<RemoveEquipmentBehaviourParameter>();

	buildRequest(QString("http://s") + QString::number(jrData.userInfo.currentServer) + QString(".jr.moefantasy.com/boat/removeEquipment/") + QString::number(removeEquipmentBehaviourParameterTemp.shipId) + QString("/") + QString::number(removeEquipmentBehaviourParameterTemp.equipmentPos));

	networkReply = networkManager->get(*request);
	connect(networkReply, SIGNAL(finished()), this, SLOT(parseRemoveEquipmentData1()));
	connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
	networkDelayTimer.setSingleShot(true);
	networkDelayTimer.start(staticParameters.maxResponseDelay);

	return true;
}