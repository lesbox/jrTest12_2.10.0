#include "BehaviourManager.h"

#ifdef ud_WLTNetwork
bool BehaviourManager::handleWLTData1() {
	sendWLTRequest2();
	return true;
}

bool BehaviourManager::handleWLTData2() {
	sendWLTRequest3();
	return true;
}

bool BehaviourManager::handleWLTData3() {
	(*getParentBehaviour()).childBehaviour[0].behaviourReturnValues.insert(ErrorCode::DataParseError, QVariant());
	emit(outputLog(0, "WLT reconnected"));
	emit(behaviourComplete());
	return true;
}
#endif