///include WaitMessage header to access class
#include "WaitMessage/WaitMessage.h"

#include <ma.h>
#include <mavsprintf.h>
#include <MAUtil/Moblet.h>
#include <NativeUI/Widgets.h>
#include <NativeUI/WidgetUtil.h>

using namespace MAUtil;
using namespace NativeUI;


class NativeUIMoblet : public Moblet, public ButtonListener
{
public:
	NativeUIMoblet()
	{
		///create WaitMessage in constructor
		 wm = new WaitMessage("Title", "Simple message");

		createUI();
	}

	virtual ~NativeUIMoblet()
	{
		btnShow->removeButtonListener(this);
		delete mScreen;

		///delete WaitMessage in destructor
		delete wm;
	}

	void createUI()
	{
		mScreen = new Screen();
		mLayout = new VerticalLayout();
		mLayout->fillSpaceHorizontally();
		mLayout->fillSpaceVertically();
		mLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

		Label *lb = new Label("\nWaitMessage\ndemo\n");
		lb->fillSpaceHorizontally();
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		lb->setFontSize(20);
		mLayout->addChild(lb);

		btnShow = new Button();
		btnShow->fillSpaceHorizontally();
		btnShow->addButtonListener(this);
		btnShow->setText("Press to wait");
		mLayout->addChild(btnShow);

		btnChange = new Button();
		btnChange->fillSpaceHorizontally();
		btnChange->addButtonListener(this);
		btnChange->setText("Change title and text");
		mLayout->addChild(btnChange);

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
		if(button == btnShow){
			///show WaitMessage
			wm->hide();
			wm->show();
		}else if(button == btnChange){
			///change WaitMessage and show
			wm->hide();
			wm->setTitle("New title");
			wm->setMessage("New message\n in two lines");
			wm->show();
		}
	}

private:
    Screen* mScreen;
    VerticalLayout* mLayout;
    Button* btnShow;
    Button* btnChange;

    ///Pointer to WaitMessage
    WaitMessage *wm;
};

extern "C" int MAMain()
{
	Moblet::run(new NativeUIMoblet());
	return 0;
}
