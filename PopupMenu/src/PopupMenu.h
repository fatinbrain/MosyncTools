/**
 * \mainpage PopupMenu
 * \brief ###Shows menu with title, help message and some buttons###
 *
 *	\image html PopupMenu.png "PopupMenu in action"
 *	\image latex PopupMenu.png "PopupMenu in action"

 * 	This project was created to simplify common task -
 * 	create and show menu.
 *
 * 	There is possibility to change title, text of help,
 * 	remove and add menu items, to hide and show menu.
 */


/**
 * \file 	PopupMenu.h
 * \brief	Contains PopupMenu class.
 */

#ifndef POPUPMENU_H_
#define POPUPMENU_H_

#include <MAUtil/String.h>
#include <MAUtil/Vector.h>
#include <NativeUI/Widgets.h>


using namespace NativeUI;
using namespace MAUtil;

/**
 * \brief	Creates popup menu with title, help message and some buttons.
 * \note Callback edition.
 * \author fatINbraIN
 * \version 1.0
 *
 * ### Usage
 * #### in class definition:
 *
 *      PopupMenu* popupMenu;
 *
 * #### setup menu
 *
 *      popupMenu->clearMenuItems();
 *      popupMenu->addMenuItem(string_to_add);
 *
 *      popupMenu->setCallback(menuCallbacker);
 *      popupMenu->setCallback(menuCallbackerStr);
 *
 * #### to call menu:
 *
 *	    popupMenu->show();
 *
 *	### Callback functions    
 *		**void callbackInt(int index);**	-- for integer index of selected menu item (zero-based).    
 *
 *		**void callbackStr(String str);**	-- for string of selected menu item.
 */
class PopupMenu: public ButtonListener{
public:
	int result;/**<	\brief	Index of pressed menu item.
					\note	Zero-based.
				*/

	/**
	 * \brief	Default constructor.
	 * @param screen	Parent screen.
	 * @param helpMessage	Menu informational string.
	 * @param menuTitle	Tile of menu.
	 */
	PopupMenu(Screen* screen, String helpMessage = "select item", String menuTitle = "");

	/**
	 * \brief	Default destructor.
	 */
	~PopupMenu();

	/**
	 * \brief	Show current menu.
	 */
	void show();

	/**
	 * \brief	Hide current menu.
	 */
	void hide();

	/**
	 * \brief	Add one item to menu.
	 * @param menuItemName	String representing new menu item.
	 * \note If menuItemName is empty string, this menu item will be invisible.
	 */
	void addMenuItem(const String menuItemName);

	/**
	 * \brief	Clean all menu items.
	 */
	void clearMenuItems();

	/**
	 * \brief	Set help message of menu.
	 * @param helpMessage	String to set as help menu.
	 * @param justification	Help message justification -1left, 0center, 1right
	 */
	void setMenuHelpMessage(const String helpMessage, const int justification = -1);

	/**
	 * \brief	Set menu title.
	 * @param menuTitle	String to set as title.
	 */
	void setMenuTitle(const String menuTitle);

	/**
	 * \brief	Reset menu return code.
	 */
	void resetReturnCode();

	/**
	 * \brief	Callback function transmitting int parameter which represent 0-based index of selected menu item.
	 * @param callback Pointer to callback fucntion.
	 */
	void setCallback(void(*callback)(int));

	/**
	 * \brief	Callback function transmitting text of selected item.
	 * @param callback Pointer to callback fucntion.
	 */
	void setCallback(void(*callback)(String));

private:
	Dialog* dlg;/**<	\brief Main menu dialog to store all UI.*/
	VerticalLayout* vl;
	Label* lbHelpMessage;/**<	\brief Label widget to store menu help message.*/
	VerticalLayout* vlButt;
	Screen* parentScreen;/**<	\brief Pointer to parent screen.*/

	Vector<String> menuItemNames;/**<	\brief Vector of strings to store text representation of menu items.*/

	void(*intCallback)(int);/**<	\brief Pointer to callback function with integer parameter.*/
	void(*strCallback)(String);/**<	\brief Pointer to callback function with String parameter.*/

	void createUI();
	/**<	\brief Create menu layout.
	 *		\note Here you can customize menu look.
	 */

	void createMenuButtons();
	/**<	\brief Create menu items buttons.
	 * 		\note Here you can customize menu buttons look.
	 */

	int getButtonIndexByName(Button* button);
	/**<	\brief Extract menu button index by its name.*/

	virtual void buttonClicked(Widget* button);
	/**<	\brief React on menu button pressure.*/
};

#endif /* POPUPMENU_H_ */
