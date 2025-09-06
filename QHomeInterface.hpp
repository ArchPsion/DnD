#ifndef __Q_HOME_INTERFACE_HPP__
#define __Q_HOME_INTERFACE_HPP__

// Qt Libraries
#include <QGridLayout>
#include <QPushButton>

// Custom Libraries
#include "QPowerDatabaseWindow.hpp"
#include "QSpellDatabaseWindow.hpp"

class QHomeInterface : public QMainWindow
{
	Q_OBJECT
	
	private:
	
		QPowerDatabaseWindow* const			powerDatabaseWindow = new QPowerDatabaseWindow(this);
		QSpellDatabaseWindow* const			spellDatabaseWindow = new QSpellDatabaseWindow(this);
	
	private slots:
	
		inline void					showPowerDatabase(void);
		inline void					showSpellDatabase(void);
	
	public:
	
		inline QHomeInterface(void);
};

QHomeInterface::QHomeInterface(void) : QMainWindow()
{
	const auto mainWidget = new QWidget();
	const auto layout = new QVBoxLayout();
	
	QMainWindow::setWindowTitle("Dungeons & Dragons 3.5e Libraries");
	QMainWindow::setCentralWidget(mainWidget);
	QMainWindow::setMinimumWidth(500);
	
	const auto powerDatabaseButton = new QPushButton("Power Library");
	const auto spellDatabaseButton = new QPushButton("Spell Library");
	
	layout->addWidget(powerDatabaseButton);
	layout->addWidget(spellDatabaseButton);
	mainWidget->setLayout(layout);
	
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
