///include header
#include "PopupProgress/PopupProgress.h"

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
		ppProgress = new PopupProgress("Long process", "Please wait until end.\nIt will not take too long.");

		createUI();
	}

	virtual ~NativeUIMoblet()
	{
		mButton->removeButtonListener(this);
		delete mScreen;
	}

	void createUI()
	{
		mScreen = new Screen();

		mLayout = new VerticalLayout();
		mLayout->fillSpaceHorizontally();
		mLayout->fillSpaceVertically();
		mLayout->setChildHorizontalAlignment(MAW_ALIGNMENT_CENTER);

		Label* lb = new Label("\n[[PopupProgress]]\n[demo]\n");
		lb->setFontSize(20);
		lb->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		lb->fillSpaceHorizontally();
		lb->setBackgroundColor(0x444444);
		mLayout->addChild(lb);

		Label* lb2 = new Label("Shows how to treat PopupProgress class\n\n");
		lb2->setFontSize(18);
		lb2->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
		mLayout->addChild(lb2);

		mButton = new Button();
		mButton->fillSpaceHorizontally();
		mButton->addButtonListener(this);
		mButton->setFontSize(18);
		mButton->setText("Press to run demo");

		mLayout->addChild(mButton);
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
		ppProgress->setMaxVal(100);
		ppProgress->show();

		for(int i = 0; i < 100; i++){
			if(i%1==0){
				ppProgress->setProgress(i);
			}
		}
		ppProgress->setProgress(100);
		ppProgress->hide();
	}

private:
    Screen* mScreen;
    VerticalLayout* mLayout;
    Button* mButton;

    ///Pointer to PopupProgress object
    PopupProgress* ppProgress;
};

extern "C" int MAMain()
{
	Moblet::run(new NativeUIMoblet());
	return 0;
}
