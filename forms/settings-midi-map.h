/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#pragma once

#include <QtWidgets/QDialog>
#include <qcombobox.h>
#include "ui_settings-midi-map.h"

class SettingsMidiMap : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsMidiMap(QWidget *parent = 0);
	~SettingsMidiMap();
	void ToggleShowHide();
	void MakeTypeCombo(int row);
	void MakeTypeCombo(int row, int existing);
	void MakeFaderActionsCombo(int row);
	void MakeFaderActionsCombo(int row, int existing);

	void MakeButtonActionsCombo(int row);
	void MakeButtonActionsCombo(int row, int existing);


private Q_SLOTS:
	void FormAccepted();

private:
	Ui::SettingsMidiMap *ui;
};
