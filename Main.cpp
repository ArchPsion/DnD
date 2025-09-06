// Qt Libraries
#include <QApplication>

// Custom Libraries
#include "QHomeInterface.hpp"

int main(int argc, char *argv[])
{	
	auto app = QApplication(argc, argv);
	
	const QString stylesheet = "QGroupBox { border: 1px solid gray; border-radius: 9px; font-size: 10px; font-weight: bold; margin-top: 1.5ex; }"
				"QPushButton#A    { background-color: rgb(204, 255, 255) }"
				"QPushButton#B    { background-color: rgb(204, 255, 255) }"
				"QPushButton#AA   { background-color: rgb(153, 255, 153) }"
				"QPushButton#BB   { background-color: rgb(153, 255, 153) }"
				"QPushButton#AAA  { background-color: rgb(255, 153, 153) }"
				"QPushButton#BBB  { background-color: rgb(255, 153, 153) }"
				"QPushButton#AAAA { background-color: rgb(255, 255, 153) }"
				"QPushButton { min-width: 1px }"
				"QPushButton#KL { max-height: 100px }"
				"QTextEdit { font-size: 13px; }";
	
	app.setStyleSheet(stylesheet);
	
	auto p = app.palette();
	p.setColor(QPalette::Window, QColor(255, 255, 255));
	p.setColor(QPalette::WindowText, QColor(51, 51, 51));
	
	p.setColor(QPalette::Base, QColor(255, 255, 255));
	p.setColor(QPalette::AlternateBase, QColor(255, 255, 255));
	
	p.setColor(QPalette::PlaceholderText, QColor(51, 51, 51));
	p.setColor(QPalette::Text, QColor(51, 51, 51));
	
	p.setColor(QPalette::Disabled, QPalette::Button, QColor(170, 170, 170));
	p.setColor(QPalette::Active, QPalette::Button, QColor(204, 204, 204));
	p.setColor(QPalette::Inactive, QPalette::Button, QColor(204, 204, 204));
	p.setColor(QPalette::ButtonText, QColor(51, 51, 51));
	
	p.setColor(QPalette::Highlight, QColor(142, 45, 197));
	p.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
	app.setPalette(p);
	
	auto window = QHomeInterface();
	window.show();
	return app.exec();
}
