#ifndef __HOME_INTERFACE_HPP__
#define __HOME_INTERFACE_HPP__

// Qt Libraries
#include <QGridLayout>
#include <QPushButton>

// Custom Libraries
#include "Constants.hpp"
#include "QDatabaseWindow.hpp"

class QHomeInterface : public QMainWindow
{
	Q_OBJECT
	
	private:
	
		QWidget* const					mainWidget = new QWidget();
		QDatabaseWindow<PowerEnum>* const		powerDatabaseWindow = new QDatabaseWindow<PowerEnum>(mainWidget, "power");
		QDatabaseWindow<SpellEnum>* const		spellDatabaseWindow = new QDatabaseWindow<SpellEnum>(mainWidget, "spell");
	
	private slots:
	
		inline void					showPowerDatabase(void);
		inline void					showSpellDatabase(void);
	
	public:
	
		inline QHomeInterface(void);
};

QHomeInterface::QHomeInterface(void) : QMainWindow()
{
	QMainWindow::setWindowTitle("Dungeons & Dragons 3.5e Libraries");
	QMainWindow::setCentralWidget(QHomeInterface::mainWidget);
	QMainWindow::setMinimumWidth(500);
	
	const auto powerDatabaseButton = new QPushButton("Power Library");
	const auto spellDatabaseButton = new QPushButton("Spell Library");
	
	const auto layout = new QVBoxLayout();
	
	layout->addWidget(powerDatabaseButton);
	layout->addWidget(spellDatabaseButton);
	QHomeInterface::mainWidget->setLayout(layout);
	
	QObject::connect(powerDatabaseButton, SIGNAL(clicked(void)), this, SLOT(showPowerDatabase(void)));
	QObject::connect(spellDatabaseButton, SIGNAL(clicked(void)), this, SLOT(showSpellDatabase(void)));
}

void QHomeInterface::showPowerDatabase(void)
{
	QHomeInterface::powerDatabaseWindow->show();
	QMainWindow::hide();
}

void QHomeInterface::showSpellDatabase(void)
{
	QHomeInterface::spellDatabaseWindow->show();
	QMainWindow::hide();
}

#endif
