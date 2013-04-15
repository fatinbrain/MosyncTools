/**
 * \mainpage PopupProgress
 * \brief ###Shows message with title, text and progress bar with percentage###
 *
 *	\image html PopupProgress.png "PopupProgress in action"
 *	\image latex PopupProgress.png "PopupProgress in action"
 
 * 	This project was created to simplify common task -
 * 	showing message with progress bar.
 *
 * 	There is possibility to change title, text of message,
 * 	percentage, to hide and show message.
 */


/**
 * \file 	PopupProgress.h
 * \brief	Contains PopupProgress class.
 */
#ifndef POPUPPROGRESS_H_
#define POPUPPROGRESS_H_

#include <NativeUI/Widgets.h>
#include <MAUtil/String.h>


using namespace NativeUI;
using namespace MAUtil;

/**
 * \brief Popup progress bar with title, text.
 *	\version 1.0
 *	\author fatINbraIN
 *
 *	Provide ability to show popup window with caption, text and progress
 *	bar with percentage.
 */
class PopupProgress{
public:
	/**
	 * \brief Default constructor.
	 * @param title Title of popup progress.
	 * @param message Help message of window.
	 */
	PopupProgress(/*Screen* parent, */String title = "", String message = "");

	/**
	 * \brief Default destructor.
	 */
	~PopupProgress();

	/**
	 * \brief Set maximal value of progress bar.
	 * @param maxVal  New maximal value.
	 */
	void setMaxVal(int maxVal);

	/**
	 * \brief Set current progress value.
	 * @param val New progress value.
	 */
	void setProgress(int val);

	/**
	 * \brief Set title of popup progress.
	 * @param title New title.
	 */
	void setTitle(String title);

	/**
	 * \brief Set help message.
	 * @param message New help message.
	 */
	void setMessage(String message);

	/**
	 * \brief Show window.
	 */
	void show();

	/**
	 * \brief Hide window.
	 */
	void hide();


private:
	/**
	 * \brief Hidden default constructor.
	 */
	PopupProgress();

	/**
	 * \name Visual widgets.
	 * \brief List of all widgets used to create user interface.
	 */
	/**@{*/
	Dialog* dlg;			/**<\brief Main dialog widget to store all UI.*/
	VerticalLayout* vlMain;
	Label* lbMessage;		/**<\brief Label for message text.*/
	VerticalLayout* hlProgress;
	ProgressBar* pb;		/**<\brief Progress bar widget.*/
	Label* lbPercent;		/**<\brief Label for percentage text.*/
	/**@}*/

	String sTitle;			/**<\brief String for window title.*/
	String sMessage;		/**<\brief String for text message.*/

	int upCount;			/**<\brief Number for 'dots' effect.*/

	/**
	 * \brief Creates user interface.
	 */
	void createUI();

	/**
	 * \brief Update percentage text.
	 */
	void updatePercentage();
};

#endif /* POPUPPROGRESS_H_ */
