/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008-2013 Armin Burgmeier <armin@arbur.net>
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
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _GOBBY_PREFERENCESDIALOG_HPP_
#define _GOBBY_PREFERENCESDIALOG_HPP_

#include "core/preferences.hpp"
#include "core/certificatemanager.hpp"
#include "core/huebutton.hpp"
#include "util/groupframe.hpp"

#include <gtkmm/dialog.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/combobox.h>
#include <gtkmm/notebook.h>
#include <gtkmm/alignment.h>
#include <gtkmm/scale.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/fontbutton.h>
#include <gtkmm/sizegroup.h>
#include <gtkmm/liststore.h>

namespace Gobby
{

template<typename OptionType>
class PreferencesComboBox: public Gtk::ComboBox
{
public:
	PreferencesComboBox(Preferences::Option<OptionType>& option):
		m_option(option), m_store(Gtk::ListStore::create(m_columns))
	{
		set_model(m_store);

		Gtk::CellRendererText* renderer =
			Gtk::manage(new Gtk::CellRendererText);
		pack_start(*renderer, true);
		add_attribute(renderer->property_text(), m_columns.text);
	}

	void add(const Glib::ustring& text, const OptionType& value)
	{
		Gtk::TreeIter iter = m_store->append();
		(*iter)[m_columns.text] = text;
		(*iter)[m_columns.value] = value;

		if(m_option == value)
			set_active(iter);
	}

private:
	class Columns: public Gtk::TreeModelColumnRecord
	{
	public:
		Gtk::TreeModelColumn<Glib::ustring> text;
		Gtk::TreeModelColumn<OptionType> value;

		Columns() { add(text); add(value); }
	};

	virtual void on_changed()
	{
		Gtk::ComboBox::on_changed();
		OptionType value = (*get_active())[m_columns.value];

		if(m_option != value)
			m_option = value;
	}

	Preferences::Option<OptionType>& m_option;

	Columns m_columns;
	Glib::RefPtr<Gtk::ListStore> m_store;
};

class PreferencesDialog : public Gtk::Dialog
{
public:
	template<typename OptionType>
	class ComboColumns: public Gtk::TreeModelColumnRecord
	{
	};

	class Page: public Gtk::Frame
	{
	public:
		Page();
		void add(Gtk::Widget& widget, bool expand);

	protected:
		Gtk::VBox m_box;
	};

	class User: public Page
	{
	public:
		User(Gtk::Window& parent, Preferences& preferences);

	protected:
		void on_local_allow_connections_toggled();
		void on_local_require_password_toggled();
		void on_local_keep_documents_toggled();

		GroupFrame m_group_settings;
		GroupFrame m_group_remote;
		GroupFrame m_group_local;

		Gtk::HBox m_box_user_name;
		Gtk::Label m_lbl_user_name;
		Gtk::Entry m_ent_user_name;

		Gtk::HBox m_box_user_color;
		Gtk::Label m_lbl_user_color;
		HueButton m_btn_user_color;

		Gtk::HBox m_box_user_alpha;
		Gtk::Label m_lbl_user_alpha;
		Gtk::HScale m_scl_user_alpha;

		Gtk::CheckButton m_btn_remote_show_cursors;
		Gtk::CheckButton m_btn_remote_show_selections;
		Gtk::CheckButton m_btn_remote_show_current_lines;
		Gtk::CheckButton m_btn_remote_show_cursor_positions;

		Gtk::CheckButton m_btn_local_allow_connections;
		Gtk::CheckButton m_btn_local_require_password;
		Gtk::Label m_lbl_local_password;
		Gtk::Entry m_ent_local_password;
		Gtk::HBox m_box_local_password;
		Gtk::Label m_lbl_local_port;
		Gtk::SpinButton m_ent_local_port;
		Gtk::HBox m_box_local_port;
		Gtk::VBox m_box_local_connections;
		Gtk::CheckButton m_btn_local_keep_documents;
		Gtk::Label m_lbl_local_documents_directory;
		Gtk::FileChooserButton m_btn_local_documents_directory;
		Gtk::HBox m_box_local_documents_directory;

		Glib::RefPtr<Gtk::SizeGroup> m_size_group;
	};

	class Editor: public Page
	{
	public:
		Editor(Preferences& preferences);

	protected:
		void on_autosave_enabled_toggled();

		GroupFrame m_group_tab;
		GroupFrame m_group_indentation;
		GroupFrame m_group_homeend;
		GroupFrame m_group_saving;

		Gtk::HBox m_box_tab_width;
		Gtk::Label m_lbl_tab_width;
		Gtk::SpinButton m_ent_tab_width;
		Gtk::CheckButton m_btn_tab_spaces;

		Gtk::CheckButton m_btn_indentation_auto;

		Gtk::CheckButton m_btn_homeend_smart;

		Gtk::CheckButton m_btn_autosave_enabled;
		Gtk::HBox m_box_autosave_interval;
		Gtk::Label m_lbl_autosave_interval;
		Gtk::Label m_lbl_autosave_interval_suffix;
		Gtk::SpinButton m_ent_autosave_interval;
	};

	class View: public Page
	{
	public:
		View(Preferences& preferences);
		void set(Preferences::View& view) const;

	protected:
		void on_wrap_text_toggled();
		void on_margin_display_toggled();

		GroupFrame m_group_wrap;
		GroupFrame m_group_linenum;
		GroupFrame m_group_curline;
		GroupFrame m_group_margin;
		GroupFrame m_group_bracket;
		GroupFrame m_group_spaces;

		Gtk::CheckButton m_btn_wrap_text;
		Gtk::CheckButton m_btn_wrap_words;

		Gtk::CheckButton m_btn_linenum_display;

		Gtk::CheckButton m_btn_curline_highlight;

		Gtk::CheckButton m_btn_margin_display;
		Gtk::HBox m_box_margin_pos;
		Gtk::Label m_lbl_margin_pos;
		Gtk::SpinButton m_ent_margin_pos;

		Gtk::CheckButton m_btn_bracket_highlight;
		PreferencesComboBox<GtkSourceDrawSpacesFlags>
			m_cmb_spaces_display;
	};

	class Appearance: public Page
	{
	public:
		Appearance(Preferences& preferences);

	protected:
		class Columns: public Gtk::TreeModelColumnRecord
		{
		public:
			Gtk::TreeModelColumn<GtkSourceStyleScheme*> scheme;
			Gtk::TreeModelColumn<Glib::ustring> name;
			Gtk::TreeModelColumn<Glib::ustring> description;
			Columns()
			{
				add(scheme);
				add(name);
				add(description);
			}
		};

		void on_scheme_changed(Preferences& preferences);

		GroupFrame m_group_toolbar;
		GroupFrame m_group_font;
		GroupFrame m_group_scheme;

		PreferencesComboBox<Gtk::ToolbarStyle> m_cmb_toolbar_style;
		Gtk::FontButton m_btn_font;

		Columns m_columns;
		Glib::RefPtr<Gtk::ListStore> m_list;
		Gtk::TreeView m_tree;
	};

	class Security: public Page
	{
	public:
		Security(Preferences& preferences,
		         const CertificateManager& m_cert_manager);
	
	protected:
		void set_file_error(Gtk::Label& label, const GError* error);

		void on_credentials_changed();
		void on_auth_cert_toggled();

		const CertificateManager& m_cert_manager;

		GroupFrame m_group_trust_file;
		GroupFrame m_group_connection_policy;
		GroupFrame m_group_authentication;

		Gtk::FileChooserButton m_btn_path_trust_file;
		Gtk::Label m_error_trust_file;
		PreferencesComboBox<InfXmppConnectionSecurityPolicy>
			m_cmb_connection_policy;

		Gtk::RadioButton m_btn_auth_none;
		Gtk::RadioButton m_btn_auth_cert;
		Gtk::Label m_lbl_key_file;
		Gtk::FileChooserButton m_btn_key_file;
		Gtk::HBox m_box_key_file;
		Gtk::Label m_error_key_file;
		Gtk::Label m_lbl_cert_file;
		Gtk::FileChooserButton m_btn_cert_file;
		Gtk::HBox m_box_cert_file;
		Gtk::Label m_error_cert_file;

		Glib::RefPtr<Gtk::SizeGroup> m_size_group;
	};

	PreferencesDialog(Gtk::Window& parent,
	                  Preferences& preferences,
	                  const CertificateManager& cert_manager);

protected:
	virtual void on_response(int id);

	Preferences& m_preferences;

	Gtk::Notebook m_notebook;

	User m_page_user;
	Editor m_page_editor;
	View m_page_view;
	Appearance m_page_appearance;
	Security m_page_security;
};

}

#endif // _GOBBY_PREFERENCESDIALOG_HPP_
