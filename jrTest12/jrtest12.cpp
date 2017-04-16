#include "jrtest12.h"

jrTest12::jrTest12(QWidget *parent) : QMainWindow(parent){
	for (int count = 0; count < 3; count++) {
		describe_pveExplore_logPrinter.append(new QLabel(this));
		describe_pveExplore_logPrinter.last()->setText("E#" + QString::number(count + 1) + " Log :");
		pveExplore_logPrinter.append(new QPlainTextEdit(this));
		pveExplore_logPrinter.last()->setMaximumBlockCount(500);
		pveExplore_logPrinter.last()->setPlainText("process start");

		describe_pveExplore_timePrinter.append(new QLabel(this));
		describe_pveExplore_timePrinter.last()->setText("Time :");
		pveExplore_timePrinter.append(new QLabel(this));
		pveExplore_timePrinter.last()->setText("00:00:00");

		pveExplore_behaviourTime.append(new QTime(0, 0, 0, 0));
	}

	for (int count = 0; count < 2; count++) {
		describe_repairShip_logPrinter.append(new QLabel(this));
		describe_repairShip_logPrinter.last()->setText("R#" + QString::number(count + 1) + " Log :");
		repairShip_logPrinter.append(new QPlainTextEdit(this));
		repairShip_logPrinter.last()->setMaximumBlockCount(500);
		repairShip_logPrinter.last()->setPlainText("process start");

		describe_repairShip_timePrinter.append(new QLabel(this));
		describe_repairShip_timePrinter.last()->setText("Time :");
		repairShip_timePrinter.append(new QLabel(this));
		repairShip_timePrinter.last()->setText("00:00:00");

		repairShip_behaviourTime.append(new QTime(0, 0, 0, 0));
	}

	describe_updatePvpStatus_logPrinter = new QLabel(this);
	describe_updatePvpStatus_logPrinter->setText("PLog :");
	updatePvpStatus_logPrinter = new QPlainTextEdit(this);
	updatePvpStatus_logPrinter->setMaximumBlockCount(500);
	updatePvpStatus_logPrinter->setPlainText("process start");

	describe_updatePvpStatus_timePrinter = new QLabel(this);
	describe_updatePvpStatus_timePrinter->setText("Time :");
	updatePvpStatus_timePrinter = new QLabel(this);
	updatePvpStatus_timePrinter->setText("00:00:00");
	updatePvpStatus_behaviourTime = new QTime(0, 0, 0, 0);

	describe_updateDrop500Status_logPrinter = new QLabel(this);
	describe_updateDrop500Status_logPrinter->setText("DLog :");
	updateDrop500Status_logPrinter = new QPlainTextEdit(this);
	updateDrop500Status_logPrinter->setMaximumBlockCount(500);
	updateDrop500Status_logPrinter->setPlainText("process start");

	describe_updateDrop500Status_timePrinter = new QLabel(this);
	describe_updateDrop500Status_timePrinter->setText("Time :");
	updateDrop500Status_timePrinter = new QLabel(this);
	updateDrop500Status_timePrinter->setText("00:00:00");
	updateDrop500Status_behaviourTime = new QTime(0, 0, 0, 0);

	describe_logPrinter = new QLabel(this);
	describe_logPrinter->setText("Log :");
	logPrinter = new QPlainTextEdit(this);
	logPrinter->setMaximumBlockCount(500);
	logPrinter->setPlainText("process start");

	describe_timePrinter = new QLabel(this);
	describe_timePrinter->setText("Time :");
	timePrinter = new QLabel(this);
	timePrinter->setText("00:00:00");
	behaviourTime = new QTime(0, 0, 0, 0);

	collect505Count = 0;
	describe_collect505Num = new QLabel(this);
	describe_collect505Num->setText("505 count :");
	collect505Num = new QLabel(this);
	collect505Num->setText(QString::number(collect505Count));

	stealOilCount = 0;
	describe_stealOilNum = new QLabel(this);
	describe_stealOilNum->setText("Oi count :");
	stealOilNum = new QLabel(this);
	stealOilNum->setText(QString::number(stealOilCount));

	stealAmmoCount = 0;
	describe_stealAmmoNum = new QLabel(this);
	describe_stealAmmoNum->setText("Am count :");
	stealAmmoNum = new QLabel(this);
	stealAmmoNum->setText(QString::number(stealAmmoCount));

	stealAluminiumCount = 0;
	describe_stealAluminiumNum = new QLabel(this);
	describe_stealAluminiumNum->setText("Al count :");
	stealAluminiumNum = new QLabel(this);
	stealAluminiumNum->setText(QString::number(stealAluminiumCount));

	describe_spoilNum = new QLabel(this);
	describe_spoilNum->setText("Sp count :");
	spoilNum = new QLabel(this);
	spoilNum->setText(QString::number(0));

	centralWidget = new QWidget(this);
	mainLayout = new QGridLayout(centralWidget);
	mainLayout->setSpacing(10);
	mainLayout->setMargin(10);
	mainLayout->addWidget(describe_timePrinter, 0, 0);
	mainLayout->addWidget(timePrinter, 0, 1);
	mainLayout->addWidget(describe_logPrinter, 1, 0, Qt::AlignTop);
	mainLayout->addWidget(logPrinter, 1, 1, 7, 1);
	for (int count = 0; count < describe_pveExplore_timePrinter.size(); count++) {
		mainLayout->addWidget(describe_pveExplore_timePrinter[count], count * 2, 2, 1, 1);
		mainLayout->addWidget(pveExplore_timePrinter[count], count * 2, 3, 1, 1);
		mainLayout->addWidget(describe_pveExplore_logPrinter[count], count * 2 + 1, 2, 1, 1, Qt::AlignTop);
		mainLayout->addWidget(pveExplore_logPrinter[count], count * 2 + 1, 3, 1, 1);
	}
	extraInformationWidget = new QWidget(centralWidget);
	extraInformationLayout = new QGridLayout(extraInformationWidget);
	extraInformationLayout->setSpacing(10);
	extraInformationLayout->setMargin(10);
	extraInformationLayout->addWidget(describe_collect505Num, 0, 0, 1, 1);
	extraInformationLayout->addWidget(collect505Num, 0, 1, 1, 1);
	extraInformationLayout->addWidget(describe_stealOilNum, 1, 0, 1, 1);
	extraInformationLayout->addWidget(stealOilNum, 1, 1, 1, 1);
	extraInformationLayout->addWidget(describe_stealAmmoNum, 2, 0, 1, 1);
	extraInformationLayout->addWidget(stealAmmoNum, 2, 1, 1, 1);
	extraInformationLayout->addWidget(describe_stealAluminiumNum, 3, 0, 1, 1);
	extraInformationLayout->addWidget(stealAluminiumNum, 3, 1, 1, 1);
	extraInformationLayout->addWidget(describe_spoilNum, 4, 0, 1, 1);
	extraInformationLayout->addWidget(spoilNum, 4, 1, 1, 1);
	extraInformationWidget->setLayout(extraInformationLayout);
	mainLayout->addWidget(extraInformationWidget, 6, 2, 2, 2);
	for (int count = 0; count < describe_repairShip_timePrinter.size(); count++) {
		mainLayout->addWidget(describe_repairShip_timePrinter[count], count * 2, 4, 1, 1);
		mainLayout->addWidget(repairShip_timePrinter[count], count * 2, 5, 1, 1);
		mainLayout->addWidget(describe_repairShip_logPrinter[count], count * 2 + 1, 4, 1, 1, Qt::AlignTop);
		mainLayout->addWidget(repairShip_logPrinter[count], count * 2 + 1, 5, 1, 1);
	}
	mainLayout->addWidget(describe_updatePvpStatus_timePrinter, 4, 4, 1, 1);
	mainLayout->addWidget(updatePvpStatus_timePrinter, 4, 5, 1, 1);
	mainLayout->addWidget(describe_updatePvpStatus_logPrinter, 5, 4, 1, 1, Qt::AlignTop);
	mainLayout->addWidget(updatePvpStatus_logPrinter, 5, 5, 1, 1);
	mainLayout->addWidget(describe_updateDrop500Status_timePrinter, 6, 4, 1, 1);
	mainLayout->addWidget(updateDrop500Status_timePrinter, 6, 5, 1, 1);
	mainLayout->addWidget(describe_updateDrop500Status_logPrinter, 7, 4, 1, 1, Qt::AlignTop);
	mainLayout->addWidget(updateDrop500Status_logPrinter, 7, 5, 1, 1);

	mainLayout->setColumnStretch(1, 1);
	mainLayout->setColumnStretch(3, 1);
	mainLayout->setColumnStretch(5, 1);

	centralWidget->setLayout(mainLayout);
	this->setCentralWidget(centralWidget);
	resize(700, 100);

	behaviourTimer = new QTimer(this);
	connect(behaviourTimer, SIGNAL(timeout()), this, SLOT(behaviourTimerTimeout()));

	behaviourTimer->setSingleShot(false);
	behaviourTimer->start(1000);

	connect(&mainBehaviour, SIGNAL(outputLog(int, QString)), this, SLOT(appendNextLog(int, QString)));
}

jrTest12::~jrTest12(){
	for (int count = 0; count < pveExplore_behaviourTime.size(); count++) {
		delete pveExplore_behaviourTime[count];
	}

	for (int count = 0; count < repairShip_behaviourTime.size(); count++) {
		delete repairShip_behaviourTime[count];
	}

	delete updatePvpStatus_behaviourTime;

	delete updateDrop500Status_behaviourTime;

	delete behaviourTime;
}

bool jrTest12::behaviourTimerTimeout() {
	*behaviourTime = behaviourTime->addSecs(1);
	timePrinter->setText(behaviourTime->toString("hh:mm:ss"));

	for (int count = 0; count < describe_pveExplore_timePrinter.size(); count++) {
		*(pveExplore_behaviourTime[count]) = (pveExplore_behaviourTime[count])->addSecs(1);
		pveExplore_timePrinter[count]->setText(pveExplore_behaviourTime[count]->toString("hh:mm:ss"));
	}

	for (int count = 0; count < describe_repairShip_timePrinter.size(); count++) {
		*(repairShip_behaviourTime[count]) = (repairShip_behaviourTime[count])->addSecs(1);
		repairShip_timePrinter[count]->setText(repairShip_behaviourTime[count]->toString("hh:mm:ss"));
	}

	*(updatePvpStatus_behaviourTime) = (updatePvpStatus_behaviourTime)->addSecs(1);
	updatePvpStatus_timePrinter->setText(updatePvpStatus_behaviourTime->toString("hh:mm:ss"));

	*(updateDrop500Status_behaviourTime) = (updateDrop500Status_behaviourTime)->addSecs(1);
	updateDrop500Status_timePrinter->setText(updateDrop500Status_behaviourTime->toString("hh:mm:ss"));

	return true;
}

bool jrTest12::appendNextLog(int outputId, QString logInfo) {
	if (outputId <= 0) {
		logPrinter->appendPlainText(behaviourTime->toString("hh:mm:ss"));
		logPrinter->appendPlainText(logInfo);
		behaviourTime->setHMS(0, 0, 0, 0);
		timePrinter->setText(behaviourTime->toString("hh:mm:ss"));
	}
	else if (outputId <= 3) {
		pveExplore_logPrinter[outputId - 1]->appendPlainText(pveExplore_behaviourTime[outputId -1]->toString("hh:mm:ss"));
		pveExplore_logPrinter[outputId - 1]->appendPlainText(logInfo);
		pveExplore_behaviourTime[outputId - 1]->setHMS(0, 0, 0, 0);
		pveExplore_timePrinter[outputId - 1]->setText(pveExplore_behaviourTime[outputId - 1]->toString("hh:mm:ss"));
	}
	else if (outputId <= 5) {
		repairShip_logPrinter[outputId - 4]->appendPlainText(repairShip_behaviourTime[outputId - 4]->toString("hh:mm:ss"));
		repairShip_logPrinter[outputId - 4]->appendPlainText(logInfo);
		repairShip_behaviourTime[outputId - 4]->setHMS(0, 0, 0, 0);
		repairShip_timePrinter[outputId - 4]->setText(pveExplore_behaviourTime[outputId - 4]->toString("hh:mm:ss"));
	}
	else if (outputId == 6) {
		updatePvpStatus_logPrinter->appendPlainText(updatePvpStatus_behaviourTime->toString("hh:mm:ss"));
		updatePvpStatus_logPrinter->appendPlainText(logInfo);
		updatePvpStatus_behaviourTime->setHMS(0, 0, 0, 0);
		updatePvpStatus_timePrinter->setText(updatePvpStatus_behaviourTime->toString("hh:mm:ss"));
	}
	else if (outputId == 7) {
		updateDrop500Status_logPrinter->appendPlainText(updateDrop500Status_behaviourTime->toString("hh:mm:ss"));
		updateDrop500Status_logPrinter->appendPlainText(logInfo);
		updateDrop500Status_behaviourTime->setHMS(0, 0, 0, 0);
		updateDrop500Status_timePrinter->setText(updateDrop500Status_behaviourTime->toString("hh:mm:ss"));
	}
	else if (outputId == 8) {
		collect505Count++;
		collect505Num->setText(QString::number(collect505Count));
	}
	else if (outputId == 9) {
		stealOilCount++;
		stealOilNum->setText(QString::number(stealOilCount));
	}
	else if (outputId == 10) {
		stealAmmoCount++;
		stealAmmoNum->setText(QString::number(stealAmmoCount));
	}
	else if (outputId == 11) {
		stealAluminiumCount++;
		stealAluminiumNum->setText(QString::number(stealAluminiumCount));
	}
	else if (outputId == 12) {
		spoilNum->setText(logInfo);
	}

	return true;
}
