#ifndef __Q_ABSTRACT_DATABASE_WINDOW_HPP__
#define __Q_ABSTRACT_DATABASE_WINDOW_HPP__

// C++ Libraries
#include <iostream>
#include <vector>

// Qt Libraries
#include <QFile>
#include <QGridLayout>
#include <QHash>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QTextBrowser>
#include <QTextStream>

// Custom Libraries
#include "OtherClasses.hpp"

class QAbstractDatabaseWindow : public QMainWindow
{
	Q_OBJECT
	
	protected:
	
		static const QString							FixStart;
		static const QString							FixEnd;
		static const QString							HighlightStart;
		static const QString							HighlightEnd;
		
		static QHash<QString, QAbstractDatabaseWindow*>				Databases;
		
		template<typename Type> inline static QString				ConstructFromIterators(Type, Type);
		inline static bool							Correlate(const QString&, const QString&);
		inline static QString							ExtractString(QFile&, char);
		inline static QString							MakeList(const std::vector<QString>&);
		inline static QString							MakeTable(const std::vector<QString>&, quint32);
		inline static QString							Process(const QString&, const QString&);
		inline static void							RemakeWidget(QWidget*, const QString&);
		
		QWidget* const								mainWidget = new QWidget();
		
		QMainWindow* const							informationWindow = new QMainWindow(mainWidget);
		QTextBrowser* const							informationContent = new QTextBrowser(informationWindow);
		
		QPushButton* const							barNamesButton = new QPushButton("Bar Names", mainWidget);
		QPushButton* const							barTextsButton = new QPushButton("Bar Texts", mainWidget);
		QPushButton* const							keepListButton = new QPushButton("Keep List", mainWidget);
		QPushButton* const							resetButton = new QPushButton("Reset Buttons", mainWidget);
		
		QLineEdit* const							nameLineEdit = new QLineEdit(mainWidget);
		QLineEdit* const							loreLineEdit = new QLineEdit(mainWidget);
		QListWidget* const							resultList = new QListWidget(mainWidget);
		
		QTextBrowser* const							loreBrowser = new QTextBrowser(mainWidget);
		QLabel* const								resultLabel = new QLabel(mainWidget);
		
		QMap<QString, quint32>							nameToIndex;
		std::vector<HexFamily>							buttonGroups;
		std::vector<quint32>							searchResults;
		
		inline void								initialiseWindow(const HexFamily&, const QFont&, qint32);
		inline void								resetGroup(const HexFamily&) const;
		virtual void								updateLore(quint32, QTextBrowser*) = 0;
	
	protected slots:
	
		inline void								resetButtons(void) const;
		virtual void								search(void) = 0;
		inline void 								showDescriptionFromClick(const QUrl&);
		inline void 								showDescriptionFromList(QListWidgetItem*);
		inline void 								switchButtonState(void) const;
	
	public:
	
		inline									QAbstractDatabaseWindow(QWidget*, const QString&);
};

QAbstractDatabaseWindow::QAbstractDatabaseWindow(QWidget* foo, const QString& name) : QMainWindow(foo)
{
	QAbstractDatabaseWindow::Databases[name] = this;
	QMainWindow::setCentralWidget(QAbstractDatabaseWindow::mainWidget);
	
	QAbstractDatabaseWindow::buttonGroups.reserve(20u);
	
	QAbstractDatabaseWindow::nameLineEdit->setPlaceholderText("Search names...");
	QAbstractDatabaseWindow::loreLineEdit->setPlaceholderText("Search descriptions...");
	
	QAbstractDatabaseWindow::loreBrowser->setReadOnly(true);
	QAbstractDatabaseWindow::loreBrowser->setOpenLinks(false);
	
	const auto someWidget = new QWidget();
	const auto layout = new QVBoxLayout();
	
	QAbstractDatabaseWindow::informationWindow->setCentralWidget(someWidget);
	layout->addWidget(QAbstractDatabaseWindow::informationContent);
	someWidget->setLayout(layout);
	
	QAbstractDatabaseWindow::informationWindow->setWindowTitle("Information Window");
	QAbstractDatabaseWindow::informationWindow->resize(600, 800);
	
	const auto flags = QAbstractDatabaseWindow::informationWindow->windowFlags();
	QAbstractDatabaseWindow::informationWindow->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
	
	QAbstractDatabaseWindow::informationContent->setReadOnly(true);
	QAbstractDatabaseWindow::informationContent->setOpenLinks(false);
	
	QObject::connect(QAbstractDatabaseWindow::resetButton, SIGNAL(released(void)), this, SLOT(resetButtons(void)));
	QObject::connect(QAbstractDatabaseWindow::resultList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(showDescriptionFromList(QListWidgetItem*)));
	QObject::connect(QAbstractDatabaseWindow::loreBrowser, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(showDescriptionFromClick(const QUrl&)));
	QObject::connect(QAbstractDatabaseWindow::informationContent, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(showDescriptionFromClick(const QUrl&)));
	
	//QString stylesheet = "table, td { border: 1px solid #333; }"
	//			"thead, tfoot { background-color: #333; color: #fff; }";
	//
	//QAbstractDatabaseWindow::loreBrowser->document()->setDefaultStyleSheet(stylesheet);
}

template<typename Type>
QString QAbstractDatabaseWindow::ConstructFromIterators(Type it, Type end)
{
	auto foo = QString();
	
	while (it != end)
	{
		foo += (*it);
		++it;
	}
	
	return foo;
}

bool QAbstractDatabaseWindow::Correlate(const QString& str1, const QString& str2)
{
	const auto size1 = str1.size();
	const auto size2 = str2.size();
	
	if (size2 > size1 and size2 - size1 >= 3u)
		return false;
	
	if (size1 > size2 and size1 - size2 >= 3u)
		return false;
	
	auto it1 = str1.cbegin();
	auto it2 = str2.cbegin();
	auto count = 0;
	
	while (count < size1 and count < size2 and it1->toLower() == it2->toLower())
	{
		++count;
		++it1;
		++it2;
	}
	
	if (count == size1 and count == size2)
		return true;
	
	if (count <= 1 or size1 == size2)
		return false;
	
	auto itt1 = str1.crbegin();
	auto itt2 = str2.crbegin();
	
	while (count < size1 and count < size2 and itt1->toLower() == itt2->toLower())
	{
		++count;
		++itt1;
		++itt2;
	}
	
	return (size1 == count or size2 == count);
}

QString QAbstractDatabaseWindow::ExtractString(QFile& file, char stopChar)
{
	auto result = QString();
	auto newChar = '0';
	
	while (file.getChar(&newChar))
	{
		if (newChar == stopChar)
			break;
		
		result += newChar;
	}
	
	return result;
}

void QAbstractDatabaseWindow::initialiseWindow(const HexFamily& fml, const QFont& font, qint32 columns)
{
	const auto window = new QMainWindow(fml.masterButton);
	const auto someWidget = new QWidget();
	const auto layout = new QGridLayout();
	
	auto count = 0;
	
	for (const auto& foo : fml.familyGroups)
	{
		layout->addWidget(foo.masterButton, count/columns, count % columns);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	someWidget->setLayout(layout);
	window->setCentralWidget(someWidget);
	
	window->installEventFilter(QAbstractDatabaseWindow::mainWidget);
	window->setWindowTitle(fml.masterButton->text());
	window->hide();
}

QString QAbstractDatabaseWindow::MakeList(const std::vector<QString>& listCells)
{
	if (listCells.empty())
		return "";
	
	auto result = QString("<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">");
	bool newItem = true;
	
	for (const auto& str : listCells)
	{
		if (str.isEmpty())
			continue;
		
		if (str.front() != '^')
		{
			if (not newItem)
			{
				result += "</ul><ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">";
				newItem = true;
			}
			
			result += "<li align=\"justify\">" + str + "</li>";
		}
		else
		{
			if (newItem)
			{
				result += "</ul><ul type=\"circle\" style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">";
				newItem = false;
			}
			
			result += "<li align=\"justify\">" + str.sliced(1u) + "</li>";
		}
	}
	
	return result + "</ul>";
}

QString QAbstractDatabaseWindow::MakeTable(const std::vector<QString>& tableCells, quint32 numberOfRows)
{
	if (tableCells.empty())
		return "";
	
	const auto columns = tableCells.size()/numberOfRows;
	auto result = QString("<p align=\"center\"><table border=\"1\" cellspacing=\"2\">");
	auto count = 0u;
	
	for (const auto& str : tableCells)
	{
		if (count < 1u)
			result += "<tr>";
		
		result += "<td style=\"text-align:center;\"><span style=\"font-size:9pt;\">" + str + "</span></td>";
		++count;
		
		if (count == columns)
		{
			result += "</tr>";
			count = 0u;
		}
	}
	
	return result + "</table></p>";
}

QString QAbstractDatabaseWindow::Process(const QString& lore, const QString& pattern)
{
	auto text = QString("<p align=\"justify\">");
	text.reserve(lore.capacity()*2u);
	
	bool listOrTable = false;
	
	for (auto cit = lore.cbegin(); cit != lore.cend(); ++cit)
	{
		switch (cit->unicode())
		{
			case '#':
			{
				if (not listOrTable)
				{
					text += "</p>";
					listOrTable = true;
				}
				
				++cit;
				
				auto table = std::vector<QString>();
				auto beg = cit;
				auto rows = 1u;
				
				while (cit->unicode() != '#')
				{
					switch (cit->unicode())
					{
						case ':':
							++rows;
							[[fallthrough]];
						
						case ';':
							table.emplace_back(QAbstractDatabaseWindow::ConstructFromIterators(beg, cit));
							beg = cit + 1u;
						
						default:
							break;
					}
					
					++cit;
				}
				
				table.emplace_back(QAbstractDatabaseWindow::ConstructFromIterators(beg, cit));
				text += QAbstractDatabaseWindow::MakeTable(table, rows);
				break;
			}
				
			case '*':
			{
				if (listOrTable)
					text += "<br>";
				else
				{
					text += "</p>";
					listOrTable = true;
				}
				
				++cit;
				
				auto theList = std::vector<QString>();
				auto beg = cit;
				
				while (cit != lore.cend() and cit->unicode() != '$' and cit->unicode() != '#')
				{
					switch (cit->unicode())
					{
						case '*':
						{
							theList.emplace_back(QAbstractDatabaseWindow::ConstructFromIterators(beg, cit));
							beg = cit + 1u;
							break;
						}
						
						case '^':
						{
							theList.emplace_back(QAbstractDatabaseWindow::ConstructFromIterators(beg, cit));
							beg = cit;
							break;
						}
						
						default:
							break;
					}
					
					++cit;
				}
				
				theList.emplace_back(QAbstractDatabaseWindow::ConstructFromIterators(beg, cit));
				text += QAbstractDatabaseWindow::MakeList(theList);
				
				--cit;
				break;
			}
			
			case '$':
			{
				if (not listOrTable)
					text += "<br>";
				
				break;
			}
			
			default:
			{
				if (listOrTable)
				{
					text += "<p align=\"justify\">";
					listOrTable = false;
				}
				
				text += *cit;
				break;
			}
		}
	}
	
	const auto size = pattern.size();
	auto it = pattern.cbegin();
	
	auto result = QString();
	result.reserve(text.capacity());
	
	auto braces = 0u;
	auto fixes = 0u;
	auto pos = 0u;
	
	for (auto cit = text.cbegin(); cit != text.cend(); ++cit)
	{
		switch (cit->unicode())
		{
			case '[':
			{
				++cit;
				
				switch (cit->unicode())
				{
					case '1':
						result += "<a href=\"spell\">";
						break;
					
					case '2':
						result += "<a href=\"power\">";
						break;
						
					case '3':
						result += "<a href=\"ability\">";
						break;
					
					case '4':
						result += "<a href=\"feat\">";
						break;
					
					case '5':
						result += "<a href=\"skill\">";
						break;
					
					default:
						result += "<a href=\"0\">";
						--cit;
						break;
				}
				
				break;
			}
			
			case ']':
			{
				result += "</a>";
				break;
			}
			
			case '|':
			{
				result += (fixes % 2u != 0u ? QAbstractDatabaseWindow::FixEnd : QAbstractDatabaseWindow::FixStart);
				++fixes;
				break;
			}
				
			case '{':
			{
				while (cit->unicode() == '{')
				{
					++cit;
					++braces;
				}
				
				switch (braces)
				{
					case 1u:
						result += "<em>";
						break;
					
					case 2u:
						result += "<b>";
						break;
					
					default:
						break;
				}
				
				--cit;
				break;
			}
			
			case '}':
			{
				switch (braces)
				{
					case 1u:
						result += "</em>";
						break;
					
					case 2u:
						result += "</b>";
						++cit;
						break;
					
					default:
						break;
				}
				
				braces = 0u;
				break;
			}
		
			default:
			{
				if (size > 0u and cit->toLower() == *it)
				{
					if (pattern.cbegin() == it)
						pos = result.size();
					
					++it;
					
					if (pattern.cend() == it)
					{
						result.insert(pos, QAbstractDatabaseWindow::HighlightStart);
						result += *cit;
						result += QAbstractDatabaseWindow::HighlightEnd;
					}
					else
						result += *cit;
				}
				else
				{
					it = pattern.cbegin();
					result += *cit;
				}
				
				break;
			}
		}
	}
	
	return result + "</p>";
}

void QAbstractDatabaseWindow::RemakeWidget(QWidget* foo, const QString& name)
{
	foo->setObjectName(name);
	foo->style()->unpolish(foo);
	foo->style()->polish(foo);
}

void QAbstractDatabaseWindow::resetButtons(void) const
{
	for (const auto& fml : QAbstractDatabaseWindow::buttonGroups)
		QAbstractDatabaseWindow::resetGroup(fml);
}

void QAbstractDatabaseWindow::resetGroup(const HexFamily& fml) const
{
	if (fml.masterButton != nullptr)
	{
		const auto name = fml.masterButton->objectName();
		
		if (name.size() > 1u)
			QAbstractDatabaseWindow::RemakeWidget(fml.masterButton, name.front());
	}
	
	for (const auto& foo : fml.familyGroups)
		QAbstractDatabaseWindow::resetGroup(foo);
}
#include <iostream>
void QAbstractDatabaseWindow::showDescriptionFromClick(const QUrl& url)
{
	const auto sender = static_cast<QTextBrowser*>(QObject::sender());
	const auto recipient = (sender == QAbstractDatabaseWindow::loreBrowser ? QAbstractDatabaseWindow::informationContent : QAbstractDatabaseWindow::loreBrowser);
	
	const auto& name = sender->textCursor().selectedText();
	const auto& descriptor = url.url();
	
	const auto dit = QAbstractDatabaseWindow::Databases.find(descriptor);
	
	if (QAbstractDatabaseWindow::Databases.cend() != dit)
	{
		const auto db = dit.value();
		const auto cit = db->nameToIndex.find(name);
		
		if (db->nameToIndex.cend() != cit)
		{
			db->updateLore(cit.value(), recipient);
			QAbstractDatabaseWindow::informationWindow->show(); // Either it has to be shown, or it is visible already.
		}
		else
		{
			const auto start = name.left(3);
			const auto stop = name.left(2) + static_cast<char>(name[2].unicode() + 1u); // name is somewhere between start and stop
			const auto end = QAbstractDatabaseWindow::nameToIndex.upperBound(stop);
			
			for (auto it = QAbstractDatabaseWindow::nameToIndex.lowerBound(start); it != end; ++it)
			{
				const auto found = QAbstractDatabaseWindow::Correlate(it.key(), name);
				
				if (found)
				{
					this->updateLore(it.value(), recipient);
					QAbstractDatabaseWindow::informationWindow->show(); // Same.
					break;
				}
			}
		}
	}
	else
	{
		for (const auto& db : QAbstractDatabaseWindow::Databases)
		{
			const auto cit = db->nameToIndex.find(name);
			
			if (db->nameToIndex.cend() != cit)
			{
				db->updateLore(cit.value(), recipient);
				QAbstractDatabaseWindow::informationWindow->show(); // Same.
				break;
			}
		}
	}
}

void QAbstractDatabaseWindow::showDescriptionFromList(QListWidgetItem* newItem)
{
	if (newItem == nullptr)
		return;
	
	const auto name = newItem->text();
	const auto it = QAbstractDatabaseWindow::nameToIndex.find(name);
	
	if (QAbstractDatabaseWindow::nameToIndex.cend() != it)
		this->updateLore(it.value(), QAbstractDatabaseWindow::loreBrowser);
}

void QAbstractDatabaseWindow::switchButtonState(void) const
{
	const auto sender = static_cast<QWidget*>(QObject::sender());
	const auto name = sender->objectName();
	auto nextName = QString("A");
	
	switch (name.size())
	{
		case 1u:
			nextName = (name.front() == 'A' ? "AA" : "BB");
			break;
		
		case 2u:
			nextName = (name.front() == 'A' ? "AAA" : "BBB");
			break;
		
		case 3u:
			nextName = (name.front() == 'A' ? "AAAA" : "B");
			break;
		
		default:
		{
			const auto& childList = sender->children();
			
			if (childList.size() != 0u)
				static_cast<QWidget*>(childList.front())->show();
				
			break;
		}
	}
	
	QAbstractDatabaseWindow::RemakeWidget(sender, nextName);
}

#endif
