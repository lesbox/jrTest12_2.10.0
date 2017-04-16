#include "BehaviourManager.h"

bool BehaviourManager::handlePveExploreStartData1() {
	PveExploreStartBehaviourParameter pveExploreStartBehaviourParameterTemp = (*getParentBehaviour()).childBehaviour[0].behaviourParameters.value<PveExploreStartBehaviourParameter>();
	
	uint currentTime = QDateTime::currentDateTime().toTime_t();
	if (!pveExploreTimer[pveExploreStartBehaviourParameterTemp.fleetId - 1].isActive()) {
		pveExploreTimer[pveExploreStartBehaviourParameterTemp.fleetId - 1].setSingleShot(true);
		pveExploreTimer[pveExploreStartBehaviourParameterTemp.fleetId - 1].start((jrData.userInfo.pveExploreVo.levels[pveExploreStartBehaviourParameterTemp.pveExploreId].endTime - currentTime + 5) * 1000); QTime timeTemp(0, 0, 0, 0);

		int waitTime = jrData.userInfo.pveExploreVo.levels[pveExploreStartBehaviourParameterTemp.pveExploreId].endTime - currentTime;
		timeTemp = timeTemp.addSecs(waitTime > 0 ? waitTime : 0);
		if (pveExploreStartBehaviourParameterTemp.fleetId == staticParameters.activeFleetId) {
			emit(outputLog(0, "wait : " + timeTemp.toString("hh:mm:ss")));
		}
		else {
			emit(outputLog(pveExploreStartBehaviourParameterTemp.fleetId, "wait : " + timeTemp.toString("hh:mm:ss")));
		}
	}

	return true;
}