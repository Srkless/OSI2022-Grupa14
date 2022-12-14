#pragma once

//#include "database.hpp"
#include "UserAccount.h"
#include "utility.h"
#include <ftxui/dom/table.hpp>
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/box.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/terminal.hpp"
#include "ftxui/util/ref.hpp"

using namespace ftxui;

namespace gui {

	void login_interface();
	void register_interface();
	/*void change_password(Database& db, User& user, bool quitable,
		std::function<void(Database&)> caller);

	void employee_interface(Database& db);
	void selling_items_interface(Database& db);
	void supervisor_interface(Database& db);
	void employee_overview(Database& db);
	void create_employee_interface(Database& db);
	void items_overview(Database& db);
	void report_interface(Database& db);
	void daily_report(Database& db, const std::vector<Item>& items);
	void weekly_report(Database& db, const std::vector<Item>& items);
	void monthly_report(Database& db, const std::vector<Item>& items);
	void yearly_report(Database& db, const std::vector<Item>& items);
	void arbitrary_report(Database& db, const std::vector<Item>& items);
	void create_item_interface(Database& db);*/
};