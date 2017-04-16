#include "BehaviourManager.h"

bool BehaviourManager::handleRepairShipStartData1() {
	RepairShipStartBehaviourParameter repairShipStartBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<RepairShipStartBehaviourParameter>();

	uint currentTime = QDateTime::currentDateTime().toTime_t();
	QTime timeTemp(0, 0, 0, 0);

	if (!repairDockTimer[repairShipStartBehaviourParameterTemp.repairDockId - 1].isActive()) {
		repairDockTimer[repairShipStartBehaviourParameterTemp.repairDockId - 1].setSingleShot(true);
		repairDockTimer[repairShipStartBehaviourParameterTemp.repairDockId - 1].start((jrData.userInfo.repairDockVo[repairShipStartBehaviourParameterTemp.repairDockId].endTime - currentTime + 5) * 1000);

		if (repairShipStartBehaviourParameterTemp.repairDockId < 3) {
			int waitTime = jrData.userInfo.repairDockVo[repairShipStartBehaviourParameterTemp.repairDockId].endTime - currentTime;
			timeTemp = timeTemp.addSecs(waitTime > 0 ? waitTime : 0);
			emit(outputLog(repairShipStartBehaviourParameterTemp.repairDockId + 3, "wait : " + timeTemp.toString("hh:mm:ss")));
		}
	}
	return true;
}