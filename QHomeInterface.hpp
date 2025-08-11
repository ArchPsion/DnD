#ifndef __HOME_INTERFACE_HPP__
#define __HOME_INTERFACE_HPP__

// Qt Libraries
#include <QGridLayout>
#include <QPushButton>

// Custom Libraries
#include "Constants.hpp"
#include "QDatabaseInterface.hpp"

class QHomeInterface : public QMainWindow
{
	Q_OBJECT
	
	private:
		
		QDatabaseInterface<PowerConstantsEnum>* const powerDatabaseWindow;
		QDatabaseInterface<SpellConstantsEnum>* const spellDatabaseWindow;
	
	private slots:
	
		inline void openPowerDatabase(void);
		inline void openSpellDatabase(void);
	
	public:
	
		inline QHomeInterface(void);
};

QHomeInterface::QHomeInterface(void) :
	QMainWindow(),
	powerDatabaseWindow(new QDatabaseInterface<PowerConstantsEnum>(this, "power")),
	spellDatabaseWindow(new QDatabaseInterface<SpellConstantsEnum>(this, "spell"))
{
	QMainWindow::setWindowTitle("Dungeons & Dragons 3.5e Libraries");
	QMainWindow::setMinimumWidth(500);
	
	const auto layout = new QVBoxLayout(new QWidget());
	QMainWindow::setCentralWidget(layout->parentWidget());
	
	const auto powerDatabaseButton = new QPushButton("Power Library");
	const auto spellDatabaseButton = new QPushButton("Spell Library");
	
	layout->addWidget(powerDatabaseButton);
	layout->addWidget(spellDatabaseButton);
	
	QObject::connect(powerDatabaseButton, SIGNAL(clicked(void)), this, SLOT(openPowerDatabase(void)));
	QObject::connect(spellDatabaseButton, SIGNAL(clicked(void)), this, SLOT(openSpellDatabase(void)));
}

void QHomeInterface::openPowerDatabase(void)
{
	QHomeInterface::powerDatabaseWindow->show();
	QMainWindow::hide();
}

void QHomeInterface::openSpellDatabase(void)
{
	QHomeInterface::spellDatabaseWindow->show();
	QMainWindow::hide();
}

#endif
