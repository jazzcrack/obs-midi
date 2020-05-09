#include <iostream>

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-data.h>

#include "RtMidi.h"

#include "forms/settings-dialog.h"
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-midi", "en-US")


void midiin_callback(double deltatime, std::vector<unsigned char> *message, void *userData)
{
	unsigned int nBytes = message->size();
	for (unsigned int i = 0; i < nBytes; i++) {
		blog(LOG_INFO, "Byte %d = %d", i, (int)message->at(i));
	}
	if (nBytes > 0)
		std::cout << "stamp = " << deltatime << std::endl;
}



bool obs_module_load(void)
{
	blog(LOG_INFO, "MIDI LOADED ");
	RtMidiIn *midiin = 0;
	// RtMidiIn constructor
	try {
		midiin = new RtMidiIn();
	} catch (RtMidiError &error) {
		// Handle the exception here
		error.printMessage();
	}

	unsigned int nPorts = midiin->getPortCount();
	blog(LOG_INFO, "Number of MIDI ports found: %d", nPorts);
	for (unsigned int i = 0; i < nPorts; i++) {
		try {
			std::string portName = midiin->getPortName(i);
			blog(LOG_INFO, "MIDI DEVICE FOUND: %s", &portName);
		} catch (RtMidiError &error) {
			error.printMessage();
		}
	}

	midiin->openPort(0);
	midiin->setCallback(&midiin_callback);


	// UI SETUP
	QMainWindow *mainWindow = (QMainWindow *)obs_frontend_get_main_window();
	SettingsDialog *settingsDialog = new SettingsDialog(mainWindow);

	const char* menuActionText = obs_module_text("OBSMIDI.Settings.DialogTitle");
	QAction* menuAction = (QAction*)obs_frontend_add_tools_menu_qaction(menuActionText);
	QObject::connect(menuAction, &QAction::triggered, [settingsDialog] {
		// The settings dialog belongs to the main window. Should be ok
		// to pass the pointer to this QAction belonging to the main window
		settingsDialog->ToggleShowHide();
	});
	
	return true;
}
