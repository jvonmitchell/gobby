/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008, 2009 Armin Burgmeier <armin@arbur.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _GOBBY_VIEW_COMMANDS_HPP_
#define _GOBBY_VIEW_COMMANDS_HPP_

#include "core/header.hpp"
#include "core/folder.hpp"

#include <sigc++/trackable.h>

namespace Gobby
{

class ViewCommands: public sigc::trackable
{
public:
	ViewCommands(Header& header, Folder& folder,
	             Preferences& preferences);
	~ViewCommands();

protected:
	void on_document_changed(SessionView* view);
	
	void on_menu_toolbar_toggled();
	void on_menu_statusbar_toggled();
	void on_menu_browser_toggled();
	void on_menu_userlist_toggled();
	void on_pref_toolbar_changed();
	void on_pref_statusbar_changed();
	void on_pref_browser_changed();
	void on_pref_userlist_changed();

	void on_menu_language_changed(
		const Glib::RefPtr<Gtk::RadioAction>& action);
	void on_doc_language_changed(GtkSourceLanguage* language);

	Header& m_header;
	Folder& m_folder;
	Preferences& m_preferences;

	TextSessionView* m_current_view;

	sigc::connection m_menu_language_changed_connection;
	sigc::connection m_document_language_changed_connection;

	sigc::connection m_menu_view_toolbar_connection;
	sigc::connection m_menu_view_statusbar_connection;
	sigc::connection m_menu_view_browser_connection;
	sigc::connection m_menu_view_userlist_connection;

	sigc::connection m_pref_view_statusbar_connection;
	sigc::connection m_pref_view_toolbar_connection;
	sigc::connection m_pref_view_browser_connection;
	sigc::connection m_pref_view_userlist_connection;

private:
	void ensure_find_dialog();
};

}

#endif // _GOBBY_VIEW_COMMANDS_HPP_
