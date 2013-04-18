#include "PopupMenu.h"

PopupMenu::PopupMenu(Screen* screen, String helpMessage, String menuTitle) :
		parentScreen(screen), result(-1) {
	createUI();
	dlg->setTitle(menuTitle);
	lbHelpMessage->setText(helpMessage);
	intCallback = NULL;
	strCallback = NULL;
}

PopupMenu::~PopupMenu() {
	if(dlg != NULL){
		delete dlg;
		dlg = NULL;
	}
}

void PopupMenu::show() {
	createMenuButtons();
	result = -1;
	ASSERT_MSG(dlg != NULL, "PopupMenu dlg empty");
	dlg->show();
}

void PopupMenu::hide() {
	dlg->hide();
}

void PopupMenu::addMenuItem(const String menuItemName) {
	menuItemNames.add(menuItemName);
}

void PopupMenu::createUI() {
	dlg = new Dialog();
	dlg->setTitle("popup menu");
	vl = new VerticalLayout();
	vl->fillSpaceHorizontally();
	vl->fillSpaceVertically();
	vl->setPaddingBottom(10);
	vl->setPaddingTop(10);
	vl->setPaddingRight(10);
	vl->setPaddingLeft(10);
	vl->setScrollable(true);

	lbHelpMessage = new Label("lb");
	lbHelpMessage->setFontSize(20);
	lbHelpMessage->fillSpaceHorizontally();
	lbHelpMessage->wrapContentHorizontally();
	vl->addChild(lbHelpMessage);

	vlButt = new VerticalLayout();
	vlButt->setPaddingBottom(10);
	vlButt->setPaddingTop(10);
	vlButt->setPaddingRight(10);
	vlButt->setPaddingLeft(10);
	vl->addChild(vlButt);
	dlg->setMainWidget(vl);
}

void PopupMenu::setMenuHelpMessage(const String helpMessage, const int justification) {
	lbHelpMessage->setText(helpMessage);
	switch (justification) {
	case 1:
		lbHelpMessage->setTextHorizontalAlignment(MAW_ALIGNMENT_RIGHT);
		break;
	case 0:
		lbHelpMessage->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		break;
	default:
		lbHelpMessage->setTextHorizontalAlignment(MAW_ALIGNMENT_LEFT);
		break;
	}
}

void PopupMenu::setMenuTitle(const String menuTitle) {
	dlg->setTitle(menuTitle);
}

void PopupMenu::clearMenuItems() {
	menuItemNames.clear();
}

void PopupMenu::resetReturnCode() {
	result = -1;
}

void PopupMenu::setCallback(void (*callback)(String)) {
	strCallback = callback;
}

void PopupMenu::buttonClicked(Widget *button) {
	Button* b = static_cast<Button*>(button);
	result = getButtonIndexByName(b);

	if(intCallback != NULL){
		intCallback(result);
	}
	if(strCallback != NULL){
		strCallback( ((Button*)(button))->getText() );
	}

	ASSERT_MSG(parentScreen != NULL, "menu's parent screen is NULL");
	this->hide();
	parentScreen->show();
}

void PopupMenu::createMenuButtons() {
	Button* b;
	ASSERT_MSG(vlButt != NULL, "PopupMenu[vlButt]empty");

	//remove old menu buttons
	while (vlButt->countChildWidgets() != 0) {
		b = static_cast<Button*>(vlButt->getChild(0));
		vlButt->removeChild(vlButt->getChild(0));
		if(b != NULL){
			delete b;
			b = NULL;
		}
	}

	//create new menu buttons
	for (int i = 0; i < menuItemNames.size(); i++) {
		Button* bNew = new Button();
		bNew->setText(menuItemNames[i]);
		bNew->fillSpaceHorizontally();
		bNew->setFontSize(18);
		bNew->addButtonListener(this);
		if(menuItemNames[i].length() == 0){
			bNew->setVisible(false);
		}
		vlButt->addChild(bNew);
	}
}

int PopupMenu::getButtonIndexByName(Button *button) {
	int ret = -1;
	String buttonText = button->getText();

	for (int i = 0; i < menuItemNames.size(); i++) {
		if (buttonText == menuItemNames[i]) {
			return i;
		}
	}

	return ret;
}

void PopupMenu::setCallback(void(*callback)(int)){
	intCallback = callback;
}
