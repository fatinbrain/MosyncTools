///STEP 01:	include PopupMenu header
#include "PopupMenu/PopupMenu.h"

#include <ma.h>
#include <mavsprintf.h>
#include <MAUtil/Moblet.h>
#include <NativeUI/Widgets.h>
#include <NativeUI/WidgetUtil.h>

#include <MAUtil/Vector.h>

using namespace MAUtil;
using namespace NativeUI;



const int menuItemsCount = 3;
const String menuItemsStrs[menuItemsCount] = {
		"First item",
		"Second item",
		"Last item"};


///STEP 04: introduce prototypes to main screen class
void menuCallbackerInt(int index);
void menuCallbackerStr(String name);


class MainScreenClass : public Moblet, public ButtonListener
{
public:
	///function to update label as indication of menu action
	void updateLabel(String labelText){
		lbSelected->setText(labelText);
	}

	MainScreenClass()
	{
		createUI();

		///STEP 05a:	create and setup menu
		pMenu = new PopupMenu(mScreen, "Tap menu item", "PopupMenu demo");

		///STEP 05b:	fill menu with items
		pMenu->clearMenuItems();
		for(int i = 0; i < menuItemsCount; i++){
			pMenu->addMenuItem(menuItemsStrs[i]);
		}

		///STEP 05c:	connect callbacks
		pMenu->setCallback(menuCallbackerStr);
		pMenu->setCallback(menuCallbackerInt);
	}


	virtual ~MainScreenClass()
	{
		btnInvokeMenu->removeButtonListener(this);

		delete mScreen;

		if(pMenu != NULL){
			delete pMenu;
			pMenu = NULL;
		}
	}

	void createUI()
	{
		mScreen = new Screen();
		mLayout = new VerticalLayout();
		mLayout->fillSpaceHorizontally();
		mLayout->fillSpaceVertically();
		mLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

		Label* lb = new Label("[[PopupMenu]]\ndemo");
		lb->fillSpaceHorizontally();
		lb->setFontSize(20);
		lb->setBackgroundColor(0x555555);
		mLayout->addChild(lb);

		Label* lbHelp = new Label("Show how to treat\n[PopupMenu] class\n");
		lbHelp->fillSpaceHorizontally();
		lbHelp->setFontSize(16);
		mLayout->addChild(lbHelp);

		Label* lbSelectedHelp = new Label("Menu item selected\n<index>-<text>");
		lbSelectedHelp->fillSpaceHorizontally();
		lbSelectedHelp->setBackgroundColor(0x4444aa);
		lbSelectedHelp->setFontSize(18);
		mLayout->addChild(lbSelectedHelp);

		lbSelected = new Label("menu not ivnoked");
		lbSelected->fillSpaceHorizontally();
		lbSelected->setBackgroundColor(0x4444ff);
		lbSelected->setFontColor(0xffffff);
		lbSelected->setFontSize(18);
		mLayout->addChild(lbSelected);

		VerticalLayout* lButtons = new VerticalLayout();
		lButtons->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		lButtons->setPaddingTop(10);
		lButtons->setPaddingLeft(10);
		lButtons->setPaddingRight(10);

		btnInvokeMenu = new Button();
		btnInvokeMenu->fillSpaceHorizontally();
		btnInvokeMenu->addButtonListener(this);
		btnInvokeMenu->setFontSize(18);
		btnInvokeMenu->setText("Invoke menu");
		lButtons->addChild(btnInvokeMenu);

		mLayout->addChild(lButtons);
		mScreen->setMainWidget(mLayout);
		mScreen->show();
	}

	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			close();
		}
	}

	virtual void buttonClicked(Widget* button)
	{
		if(button == btnInvokeMenu){
			///STEP 06:	Invoke menu
			ASSERT_MSG(pMenu != NULL, "pmenu null");
//			maMessageBox("shit!", "will show menu");
			pMenu->show();
		}
	}

private:
    Screen* mScreen;
    VerticalLayout* mLayout;
    Button* btnInvokeMenu;
    Label* lbSelected;

    ///STEP 02:	popup menu pointer
    PopupMenu* pMenu;
};

///need pointer of main screen class if you plan to make menu interact with.
MainScreenClass* m;

///STEP 03a: create callback functions
///this function will interact with MainScreenClass
void menuCallbackerInt(int index){
	char cBuff[20];
	sprintf(&cBuff[0], "%d", index);
	String sBuff = "";
	sBuff += cBuff;
	sBuff += "-";
	sBuff += menuItemsStrs[index];

	m->updateLabel(sBuff);
}

///STEP 03b: create callback functions
void menuCallbackerStr(String name){
	maMessageBox("Menu item tapped:", name.c_str());
}

extern "C" int MAMain()
{
	m = new MainScreenClass();
	Moblet::run(m);
	return 0;
}
