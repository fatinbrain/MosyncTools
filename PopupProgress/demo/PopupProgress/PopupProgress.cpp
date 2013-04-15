#include "PopupProgress.h"

char* dots[] = {" ", ".", "..", "...", "....", ".....", "....", "...", "..", "."};


PopupProgress::PopupProgress(String title, String message):
	sTitle(title), sMessage(message) {
	upCount = 0;
	createUI();
	dlg->hide();
}

PopupProgress::~PopupProgress() {
}

void PopupProgress::setMaxVal(int maxVal) {
	if(maxVal > 0){
		pb->setProgress(0);
		pb->setMaximumValue(maxVal);
		updatePercentage();
	}
}

void PopupProgress::setProgress(int val) {
	if(val > 0 && val <= pb->getMaximumValue() ){
		pb->setProgress(val);
		updatePercentage();
	}
}

void PopupProgress::show(){
	dlg->show();
}

void PopupProgress::hide() {
	dlg->hide();
}

PopupProgress::PopupProgress() {
}

void PopupProgress::createUI() {
	dlg = new Dialog();
	dlg->setTitle(sTitle);

	vlMain = new VerticalLayout();
	vlMain->fillSpaceHorizontally();
	vlMain->fillSpaceVertically();
	vlMain->setScrollable(true);
	vlMain->wrapContentHorizontally();
	vlMain->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	vlMain->setPaddingBottom(10);
	vlMain->setPaddingRight(10);
	vlMain->setPaddingLeft(10);
	vlMain->setPaddingTop(10);

	lbMessage = new Label();
	lbMessage->fillSpaceHorizontally();
	lbMessage->wrapContentHorizontally();
	lbMessage->setText(sMessage);
	vlMain->addChild(lbMessage);

	hlProgress = new VerticalLayout();
	hlProgress->fillSpaceHorizontally();
	hlProgress->setScrollable(true);
	hlProgress->wrapContentHorizontally();
	hlProgress->setPaddingBottom(10);
	hlProgress->setPaddingRight(10);
	hlProgress->setPaddingLeft(10);
	hlProgress->setPaddingTop(10);

	lbPercent = new Label();
	lbPercent->fillSpaceHorizontally();
	lbPercent->setTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
	lbPercent->setText("--%");
	hlProgress->addChild(lbPercent);

	pb = new ProgressBar();
	pb->fillSpaceHorizontally();
	pb->setMaximumValue(100);
	hlProgress->addChild(pb);

	vlMain->addChild(hlProgress);

	lbMessage->setFontSize(18);
	lbPercent->setFontSize(18);
	dlg->addChild(vlMain);
}

String genDots(int& value){
	String buff = "";
	value = value > 9 ? 0 : value;

	buff += dots[value];

	return buff;
}

void PopupProgress::setTitle(String title) {
	sTitle = title;
	dlg->setTitle(sTitle);
}

void PopupProgress::setMessage(String message) {
	sMessage = message;
	lbMessage->setText(sMessage);
}

void PopupProgress::updatePercentage() {
	int z = pb->getProgress() * 100 / pb->getMaximumValue();
	dlg->setTitle(sTitle + genDots(upCount));
	upCount++;

	char buff[30];
	sprintf(&buff[0], "%2d", z);
	String sPercent = (buff);
	sPercent += "%";
	lbPercent->setText(sPercent);
}
