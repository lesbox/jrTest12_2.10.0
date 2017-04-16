#include "Commen.h"
#include "JRManager.h"

#define ud_WLTNetwork

enum CollectStrategy {
	StealResourceStrategy,
	StealPantsStrategy,
	CollectShipStrategy,
};

enum ErrorCode {
	GetTaskAward,
	GetLoginAward,
	RepairDockIdle,
	ActiveFleetIdle,
	CampaignFinished,
	CollectShipFinished,
	NonactiveFleetIdle,
	SaveAndLoad,
	NoError,
	DataParseError,
	InsufficientResourceError,
	RouteError,
	OperationError,
	/*
	FatalError,
	RouteError,
	OperationError,
	UpdateTaskAward,
	UpdateLoginAward,
	DataOutOfDateError,
	RepairDockTimerTimeout,
	PveExploreTimerTimeout
	*/
};

enum RequestId {
	NoRequest,
	BuildLogRequest1,
	CreateFleetRequest1,
	SupplyMultiBoatRequest1,
	LoginRequest1,
	LoginRequest2,
	LoginRequest3,
	LoginRequest4,
	LoginRequest5,
	LoginRequest6,
	LoginRequest7,
	LoginRequest8,
	LoginRequest9,
	PveExploreCompleteRequest1,
	PveExploreStartRequest1,
	PveWarRequest1,
	PveWarRequest2,
	PveWarRequest3,
	PveWarRequest4,
	PveWarRequest5,
	PveWarRequest6,
	PveWarRequest7,
	PveWarRequest8,
	PveWarRequest9,
	CheckPvpStatusRequest1,
	PvpWarRequest1,
	PvpWarRequest2,
	PvpWarRequest3,
	PvpWarRequest4,
	PvpWarRequest5,
	PvpWarRequest6,
	PvpWarRequest7,
	RepairShipStartRequest1,
	GetCampaignFleetRequest1,
	CampaignRequest1,
	CampaignRequest2,
	CampaignRequest3,
	CampaignRequest4,
	CampaignRequest5,
	CampaignRequest6,
	GetTaskAwardRequest1,
	GetLoginAwardRequest1,
	SupplyBoatRequest1,
	GetInitializationDataRequest1,
	InstantRepairMultiShipRequest1,
	RepairShipCompleteRequest1,
	CheckSpoilsShopRequest1,
	DismantleRequest1,
	RemoveEquipmentRequest1,
	ChangeEquipmentRequest1,

#ifdef ud_WLTNetwork
	WLTRequest1,
	WLTRequest2,
	WLTRequest3,
#endif

};

enum BehaviourType
{
	RootBehavior,

	IdleBehaviour,

	InitStaticParametersBehaviour,

	InitBattleParametersBehaviour,

	LoginBehaviour,

	InitDynamicParametersBehaviour,

	StealOilBehaviour,

	StealAmmoBehaviour,

	StealAluminiumBehaviour,

	StealPantsBehaviour,

	CollectDogFoodBehaviour,

	CollectShipBehaviour,

	TrainShipBehaviour,

	RepairShipBehaviour,

	RepairShipStartBehaviour,

	RepairShipCompleteBehaviour,

	InstantRepairMultiShipBehaviour,

	CreateFleetBehaviour,

	RemoveEquipmentBehaviour,

	ChangeEquipmentBehaviour,

	SupplyMultiBoatBehaviour,

	SupplyBoatBehaviour,

	PveWarBehaviour,

	PveExploreBehaviour,

	ActiveFleetPveExploreBehaviour,

	PveExploreStartBehaviour,

	PveExploreCompleteBehaviour,

	CheckPvpStatusBehaviour,

	UpdatePvpStatusBehaviour,

	PvpWarBehaviour,

	GetCampaignFleetBehaviour,

	UpdateCampaignStatusBehaviour,

	CampaignBehaviour,

	CompleteTaskBehaviour,

	GetTaskAwardBehaviour,

	GetLoginAwardBehaviour,

	GetInitializationDataBehaviour,

	CheckSpoilsShopBehaviour,

	DismantleBehaviour,

	SaveAndLoadBehaviour
};
class GetTaskAwardBehaviourParameter {
public:
	int taskId;
};
Q_DECLARE_METATYPE(GetTaskAwardBehaviourParameter);

class LoginBehaviourParameter {
public:
	QString username;
	QString password;
	int serverId;
};
Q_DECLARE_METATYPE(LoginBehaviourParameter);

class CreateFleetBehaviourParameter {
public:
	int fleetId;
	QVector<int> shipIdList;
};
Q_DECLARE_METATYPE(CreateFleetBehaviourParameter);

class RepairShipStartBehaviourParameter {
public:
	int repairDockId;
	int shipId;
};
Q_DECLARE_METATYPE(RepairShipStartBehaviourParameter);

class RepairShipCompleteBehaviourParameter {
public:
	int repairDockId;
	int shipId;
};
Q_DECLARE_METATYPE(RepairShipCompleteBehaviourParameter);

class InstantRepairMultiShipBehaviourParameter {
public:
	QVector<int> shipIdList;
};
Q_DECLARE_METATYPE(InstantRepairMultiShipBehaviourParameter);

class RemoveEquipmentBehaviourParameter {
public:
	int shipId;
	int equipmentPos;
};
Q_DECLARE_METATYPE(RemoveEquipmentBehaviourParameter);

class ChangeEquipmentBehaviourParameter {
public:
	int shipId;
	int equipmentPos;
	int equipmentCid;
};
Q_DECLARE_METATYPE(ChangeEquipmentBehaviourParameter);

class SupplyMultiBoatBehaviourParameter {
public:
	QVector<int> shipIdList;
};
Q_DECLARE_METATYPE(SupplyMultiBoatBehaviourParameter);

class SupplyBoatBehaviourParameter {
public:
	int shipId;
};
Q_DECLARE_METATYPE(SupplyBoatBehaviourParameter);

class PveWarRouteInformation_OneNode {
public:
	bool canSkip;
	bool mustSkip;
	int defaultFormation;
	bool canDoNightWar;

	QMap<int, PveWarRouteInformation_OneNode> childNodes;
};

class PveWarBehaviourParameter {
public:
	int fleetId;
	int pveChapter;
	int pveId;
	QMap<int, PveWarRouteInformation_OneNode>::iterator pveNodeIter;

	QMap<int, PveWarRouteInformation_OneNode> routeInfo;
};
Q_DECLARE_METATYPE(PveWarBehaviourParameter);

class PvpWarBehaviourParameter {
public:
	int fleetId;
	int fuid;
};
Q_DECLARE_METATYPE(PvpWarBehaviourParameter);

class CampaignBehaviourParameter {
public:
	int campaignId;
	QVector<int> campaignFleet; 
};
Q_DECLARE_METATYPE(CampaignBehaviourParameter);

class PveExploreStartBehaviourParameter {
public:
	int fleetId;
	int pveExploreId;
};
Q_DECLARE_METATYPE(PveExploreStartBehaviourParameter);

class PveExploreCompleteBehaviourParameter {
public:
	int pveExploreId;
};
Q_DECLARE_METATYPE(PveExploreCompleteBehaviourParameter);

class DismantleBehaviourParameter {
public:
	bool isDismantleEquipment;
	QVector<int> dismantleShipIdList;
};
Q_DECLARE_METATYPE(DismantleBehaviourParameter);

class BehaviourNode{
public:
	BehaviourType behaviourType;
	QVariant behaviourParameters;
	QMap<ErrorCode, QVariant> behaviourReturnValues;
	QQueue<BehaviourNode> childBehaviour;

public:
	BehaviourNode();
	~BehaviourNode();

	BehaviourNode(BehaviourType behaviourType, QVariant behaviourParameters);
};

class PveWarInformation {
public:
	PveWarBehaviourParameter pveWarInfo;

	QVector<MiniPveWarNodeInformation> pveWarNodeList;
};

class PvpWarInformation {
public:
	PvpWarBehaviourParameter pvpWarInfo;

	MiniPvpWarNodeInformation pvpWarNode;
};

class CampaignInformation {
public:
	CampaignBehaviourParameter campaignInfo;

	MiniPveWarNodeInformation campaignNode;
};

class ShipConfigInformation {
public:
	int shipId;
	QMap<int, int> equipmentInfo;
};

class CompleteTaskInformation {
public:
	QVector<int> fleetInfo;

	BehaviourNode pveWarInfo;
};

class UpdateFlag {
public:
	bool unlockedShipsFlag;
	bool pvpUserInfoListFlag;
	bool currentCampaignInfoFlag;
	bool spoilNumFlag;
};

class TrainingShipConfigInformation {
public:
	int shipId;
	int Level;
	QMap<int, int> equipmentInfo;
};

class DynamicParametersInformation {
public:
	UpdateFlag dataUpdateFlag;

	QList<int> stealOilAndAmmoDogFoodShipIdList;

	int defaultStealAluminiumShipId;
	QList<int> stealAluminiumDogFoodShipIdList;

	PveWarInformation currentPveWarInfo;

	QVector<int> dismantleShipIdList;
	QVector<int> dogFoodShipIdList;
	QVector<int> reservedShipIdList;

	QVector<MiniPvpUserInformation> pvpUserInfoList;

	PvpWarInformation currentPvpWarInfo;

	CampaignInformation currentCampaignInfo;

	int drop500;

	bool canPvp;
	bool canCampaign;
	bool canCompleteTask;

	int spoilNum;
	int maxSpoilNum;

	int stealAmmoBrokenCount;
	int stealOilBrokenCount;

	int completeTaskShipType;

	int trainingOil;
	int trainingAmmo;

	bool loginFinished;

	bool collectShipSuccessFlag;

	int collectShip_205SkipFailedCount;

public:
	DynamicParametersInformation();
	~DynamicParametersInformation();

	bool resetAll();
};

class StaticParametersInformation {
public:
	QString initInfoFilePath;

	int maxResponseDelay;
	int maxRequestRepeatNum;
	int activeFleetId;
	BehaviourNode behaviourNode_Login;
	BehaviourNode behaviourNode_PveWar_StealOil;
	BehaviourNode behaviourNode_PveWar_StealAmmo;
	BehaviourNode behaviourNode_PveWar_StealAluminium;
	BehaviourNode behaviourNode_PveWar_TrainShip;
	BehaviourNode behaviourNode_PveWar_CollectDogFood_101;
	BehaviourNode behaviourNode_PveWar_CollectDogFood_505;
	QVector<int> collectDogFood_505FleetInfo;
	BehaviourNode behaviourNode_PveWar_StealPants;
	QVector<int> stealPantsFleetConfig;
	BehaviourNode behaviourNode_PveWar_CollectShip_604;
	QVector<int> collectShip_604FleetInfo;
	BehaviourNode behaviourNode_PveWar_CollectShip_701;
	QVector<int> collectShip_701FleetInfo;
	BehaviourNode behaviourNode_PveWar_CollectShip_702_1;
	QVector<int> collectShip_702_1FleetInfo;
	BehaviourNode behaviourNode_PveWar_CollectShip_702_2;
	QVector<int> collectShip_702_2FleetInfo;
	BehaviourNode behaviourNode_PveWar_CollectShip_205;
	QVector<int> collectShip_205FleetInfo;
	BehaviourNode behaviourNode_PveWar_CompleteTask_104;
	QVector<int> completeTask_104FleetInfo;
	BehaviourNode behaviourNode_PveWar_CompleteTask_201;
	QVector<int> completeTask_201FleetInfo;
	BehaviourNode behaviourNode_PveWar_CompleteTask_302;
	QVector<int> completeTask_302FleetInfo;
	BehaviourNode behaviourNode_PveWar_CompleteTask_601;
	QVector<int> completeTask_601FleetInfo;

	QVector<ShipConfigInformation> stealAluminiumShipList;

	QVector<int> reservedShipCidList;
	QVector<int> repairShipIdList;
	QVector<TrainingShipConfigInformation> trainingShipList;

	CollectStrategy defaultCollectStrategy;
	QMap<int, int> pveExploreConfig;
	QVector<int> activeFleetPveExploreFleetConfig;

	QVector<int> canCompleteTaskCidList;
	//2300333 击破母港周边哨戒(第1章)敌军势力
	//2300433 击破扶桑海域攻略(第2章)敌军势力
	//2300533 击破星洲海峡突破(第3章)敌军势力
	//2200232 击破敌军主力
	//2200732 [出征]作战：战列舰
	//2201532 [出征]作战：战列舰
	//2200932 [出征]作战：航空母舰
	//2201732 [出征]作战：航空母舰
	//2200632 [出征]作战：重巡洋舰
	//2201432 [出征]作战：重巡洋舰
	//2201832 [出征]作战：战列巡洋舰
	//2201132 [出征]作战：战列巡洋舰
	//2200832 [出征]作战：轻型航空母舰
	//2201632 [出征]作战：轻型航空母舰

	CompleteTaskInformation completeTaskInfo_2300333;
	CompleteTaskInformation completeTaskInfo_2300433;
	CompleteTaskInformation completeTaskInfo_2300533;
	CompleteTaskInformation completeTaskInfo_2200232;
	CompleteTaskInformation completeTaskInfo_2200732;
	CompleteTaskInformation completeTaskInfo_2201532;
	CompleteTaskInformation completeTaskInfo_2200932;
	CompleteTaskInformation completeTaskInfo_2201732;
	CompleteTaskInformation completeTaskInfo_2200632;
	CompleteTaskInformation completeTaskInfo_2201432;
	CompleteTaskInformation completeTaskInfo_2201832;
	CompleteTaskInformation completeTaskInfo_2201132;
	CompleteTaskInformation completeTaskInfo_2200832;
	CompleteTaskInformation completeTaskInfo_2201632;

	QVector<int> pvpFleetConfig;

	int defaultCampaignId;

	QDateTime spoilEventStartTime;
	QVector<int> maxSpoilNumList;

	QVector<BehaviourType> mutexBehaviourList;

	QVector<int> collectShipShipCidList;

	QVector<int> commenShipIdList;

	QVector<QString> resultLevelDescriptorList;
};

class BehaviourManager : public QThread{
	Q_OBJECT

public:
	JRManager jrData;
	StaticParametersInformation staticParameters;
	DynamicParametersInformation dynamicParameters;

	QQueue<BehaviourNode> rootBehaviour;
	int currentBehaviourDepth;

	//network
	QMap<QString, QString> cookie;
	ud_NetworkCookie * networkCookie;
	QNetworkAccessManager* networkManager;
	QNetworkRequest * request;
	QNetworkReply * networkReply;
	QNetworkSession * networkSession;

	QTimer networkDelayTimer;
	QTimer resendRequestTimer;

	RequestId currentRequestId;
	int currentRequestRepeatNum;

	//errorInfo
	QByteArray lastResponseContent;

	//timer
	QTimer repairDockTimer[4];
	QTimer pveExploreTimer[4];
	QTimer updatePvpStatusTimer;
	QTimer updateDrop500Timer;
	QTimer serverMaintenanceTimer;

#ifdef ud_WLTNetwork
	//WLT information
	QByteArray ipAddress;
	QByteArray rn;
#endif

public:
	BehaviourManager();
	~BehaviourManager();

	bool startCollectProcess();
	bool initStaticParameters();
	bool initDynamicParameters();
	bool initBehaviourparameters();
	bool initBattleParameters();
	bool generateNextBattleParameters();
	bool executeNextExecutableBehaviour();

public:
	bool idle();

	bool login();
	bool sendLoginRequest1();
	bool sendLoginRequest2();
	bool sendLoginRequest3();
	bool sendLoginRequest4();
	bool sendLoginRequest5();
	bool sendLoginRequest6();
	bool sendLoginRequest7();
	bool sendLoginRequest8();
	bool sendLoginRequest9();
	bool handleLoginData1();
	bool handleLoginData2();
	bool handleLoginData3();
	bool handleLoginData4();
	bool handleLoginData5();
	bool handleLoginData6();
	bool handleLoginData7();
	bool handleLoginData8();
	bool handleLoginData9();

	bool stealOil();

	bool stealAmmo();

	bool stealAluminium();

	bool collectDogFood();

	bool collectShip();

	bool trainShip();

	bool createFleet();
	bool sendCreateFleetRequest1(); 
	bool handleCreateFleetData1();

	bool repairShip();

	bool repairShipStart();
	bool sendRepairShipStartRequest1();
	bool handleRepairShipStartData1();

	bool repairShipComplete();
	bool sendRepairShipCompleteRequest1();
	bool handleRepairShipCompleteData1();

	bool instantRepairMultiShip();
	bool sendInstantRepairMultiShipRequest1();
	bool handleInstantRepairMultiShipData1();

	bool removeEquipment();
	bool sendRemoveEquipmentRequest1();
	bool handleRemoveEquipmentData1();

	bool changeEquipment();
	bool sendChangeEquipmentRequest1();
	bool handleChangeEquipmentData1();

	bool supplyMultiBoat();
	bool sendSupplyMultiBoatRequest1();
	bool handleSupplyMultiBoatData1();

	bool supplyBoat();
	bool sendSupplyBoatRequest1();
	bool handleSupplyBoatData1();

	bool pveWar();
	bool sendPveWarRequest1();
	bool sendPveWarRequest2();
	bool sendPveWarRequest3();
	bool sendPveWarRequest4();
	bool sendPveWarRequest5();
	bool sendPveWarRequest6();
	bool sendPveWarRequest7();
	bool sendPveWarRequest8();
	bool sendPveWarRequest9();
	bool handlePveWarData1();
	bool handlePveWarData2();
	bool handlePveWarData3();
	bool handlePveWarData4();
	bool handlePveWarData5();
	bool handlePveWarData6();
	bool handlePveWarData7();
	bool handlePveWarData8();
	bool handlePveWarData9();

	bool pveExplore();
	bool activeFleetPveExplore();
	bool pveExploreStart();
	bool sendPveExploreStartRequest1();
	bool handlePveExploreStartData1();

	bool pveExploreComplete();
	bool sendPveExploreCompleteRequest1();
	bool handlePveExploreCompleteData1();

	bool checkPvpStatus();
	bool sendCheckPvpStatusRequest1();
	bool handleCheckPvpStatusData1();

	bool updatePvpStatus();
	bool pvpWar();
	bool sendPvpWarRequest1();
	bool sendPvpWarRequest2();
	bool sendPvpWarRequest3();
	bool sendPvpWarRequest4();
	bool sendPvpWarRequest5();
	bool sendPvpWarRequest6();
	bool sendPvpWarRequest7();
	bool handlePvpWarData1();
	bool handlePvpWarData2();
	bool handlePvpWarData3();
	bool handlePvpWarData4();
	bool handlePvpWarData5();
	bool handlePvpWarData6();
	bool handlePvpWarData7();

	bool getCampaignFleet();
	bool sendGetCampaignFleetRequest1();
	bool handleGetCampaignFleetData1();

	bool updateCampaignStatus();
	bool campaign();
	bool sendCampaignRequest1();
	bool sendCampaignRequest2();
	bool sendCampaignRequest3();
	bool sendCampaignRequest4();
	bool sendCampaignRequest5();
	bool sendCampaignRequest6();
	bool handleCampaignData1();
	bool handleCampaignData2();
	bool handleCampaignData3();
	bool handleCampaignData4();
	bool handleCampaignData5();
	bool handleCampaignData6();

	bool dismantle();
	bool sendDismantleRequest1();
	bool handleDismantleData1();

	bool checkSpoilShop();
	bool sendCheckSpoilsShopRequest1();
	bool handleCheckSpoilsShopData1();

	bool getInitializationData();
	bool sendGetInitializationDataRequest1();
	bool handleGetInitializationDataData1();

	bool updateTaskAwardStatus();
	bool getTaskAward();
	bool sendGetTaskAwardRequest1();
	bool handleGetTaskAwardData1();

	bool updateLoginAwardStatus();
	bool getLoginAward();
	bool sendGetLoginAwardRequest1();
	bool handleGetLoginAwardData1();

	bool stealPants();
	
	bool completeTask();

	bool startCompleteTask_2300333();

	bool startCompleteTask_2300433();

	bool startCompleteTask_2300533();

	bool startCompleteTask_2200232();

	bool startCompleteTask_2200732();

	bool startCompleteTask_2201532();

	bool startCompleteTask_2200932();

	bool startCompleteTask_2201732();

	bool startCompleteTask_2200632();

	bool startCompleteTask_2201432();

	bool startCompleteTask_2201832();

	bool startCompleteTask_2201132();

	bool startCompleteTask_2200832();

	bool startCompleteTask_2201632();

	bool saveAndLoad();

#ifdef ud_WLTNetwork
	bool sendWLTRequest1();
	bool sendWLTRequest2();
	bool sendWLTRequest3();

	bool handleWLTData1();
	bool handleWLTData2();
	bool handleWLTData3();
#endif

public:
	//auxiliary functions
	BehaviourNode * getParentBehaviour();

	bool updateResource();

	bool dispatchShip(int shipId);

	int checkFleetBrokenStatus(int fleetId);

	int checkFleetSupplyStatus(int fleetId);

	int generatePid();

	bool getErrorInfo(QJsonObject content);

	void errorHandler(QString errorInfo);

	bool handleResponse(QJsonDocument & jsonContent, ErrorManager & errorManager);

	int isTheSameClass(int shipId1, int shipId2);

	int getBrokenStatus(int shipId);

	bool buildRequest(QString url, bool appendSuffix = true, bool appendCookies = true, QMap<QByteArray, QByteArray> extraRawHeaders = QMap<QByteArray, QByteArray>(), QString host = QString("s12.jr.moefantasy.com"));

	QString generateEncryptCode();

public slots:
	bool networkErrorSlot(QNetworkReply::NetworkError msg);
	bool abortRequest();
	bool resendRequest();

	bool handleBehaviourResult();

	bool parseLoginData1();
	bool parseLoginData2();
	bool parseLoginData3();
	bool parseLoginData4();
	bool parseLoginData5();
	bool parseLoginData6();
	bool parseLoginData7();
	bool parseLoginData8();
	bool parseLoginData9();

	bool parseCreateFleetData1();

	bool parseRepairShipStartData1();

	bool parseRepairShipCompleteData1();

	bool parseInstantRepairMultiShipData1();

	bool parseRemoveEquipmentData1();

	bool parseChangeEquipmentData1();

	bool parseSupplyMultiBoatData1();

	bool parseSupplyBoatData1();

	bool parsePveWarData1();
	bool parsePveWarData2();
	bool parsePveWarData3();
	bool parsePveWarData4();
	bool parsePveWarData5();
	bool parsePveWarData6();
	bool parsePveWarData7();
	bool parsePveWarData8();
	bool parsePveWarData9();

	bool parsePveExploreStartData1();

	bool parsePveExploreCompleteData1();

	bool parseCheckPvpStatusData1();

	bool parsePvpWarData1();
	bool parsePvpWarData2();
	bool parsePvpWarData3();
	bool parsePvpWarData4();
	bool parsePvpWarData5();
	bool parsePvpWarData6();
	bool parsePvpWarData7();

	bool parseGetCampaignFleetData1();

	bool parseCampaignData1();
	bool parseCampaignData2();
	bool parseCampaignData3();
	bool parseCampaignData4();
	bool parseCampaignData5();
	bool parseCampaignData6();

	bool parseDismantleData1();

	bool parseCheckSpoilsShopData1();

	bool parseGetInitializationDataData1();

	bool parseGetTaskAwardData1();

	bool parseGetLoginAwardData1();

	bool repairDockTimerTimeout();

	bool pveExploreTimerTimeout();

	bool updatePvpStatusTimerTimeout();

	bool updateDrop500TimerTimeout();
	
	bool serverMaintenanceTimerTimeout();

#ifdef ud_WLTNetwork
	void reconnectWLAN();
	void reconnectWLANError(QNetworkSession::SessionError err);
	void reconnectWLANErrorHandler();

	bool parseWLTData1();
	bool parseWLTData2();
	bool parseWLTData3();
#endif

signals:
	int behaviourComplete();
	int outputLog(int outputId, QString logInfo);
};

