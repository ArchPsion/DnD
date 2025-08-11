#ifndef __DATABASE_INTERFACE_INTERMEDIARY_HPP__
#define __DATABASE_INTERFACE_INTERMEDIARY_HPP__

// C++ Libraries
#include <fstream>

// Qt Libraries
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>

class QDatabaseInterfaceIntermediary : public QMainWindow
{
	Q_OBJECT
	
	protected:
	
		inline static const QString						FixStart = QString("<font color=#7B68EE>");
		inline static const QString						FixEnd = QString("</font>");
		inline static const QString						HighlightStart = QString("<span style=\"background-color: #FFEFD5\">");
		inline static const QString						HighlightEnd = QString("</span>");
		
		inline static std::map<QString, QDatabaseInterfaceIntermediary*>	Databases;
		
		inline static void							GetLine(std::ifstream&, std::string&);
		inline static char							LowerCase(char);
		inline static std::string						MakeList(const std::vector<std::string>&);
		inline static std::string						MakeTable(const std::vector<std::string>&, qint32);
		
		inline static bool							Correlate(const QString&, const QString&);
		inline static QString							Process(const std::string&, const QString&);
		inline static QString							Table(const std::string&);
		
		QMainWindow* const							informationWindow;
		QTextBrowser* const							informationContent;
		
		QPushButton* const							barNamesButton;
		QPushButton* const							barTextsButton;
		QPushButton* const							keepListButton;
		QPushButton* const							resetButton;
		
		QLineEdit* const							nameLineEdit;
		QLineEdit* const							loreLineEdit;
		QListWidget* const							resultList;
		QTextBrowser* const							lore;
		QLabel* const								label;
		
		const QString								contentName;
		std::map<QString, quint32>						fullIndex;
			
		virtual void								resetButtons(void) = 0;
		virtual void								updateLore(const QString&, QTextEdit*, quint32) const = 0;
		virtual void								updateLoreFromList(QTextEdit*, qint32) const = 0;
	
	protected slots:
	
		inline void 								resetEverything(void);
		inline void 								showDescription(const QUrl&) const;
		inline void 								showDescriptionFromList(int) const;
		inline void 								switchButtonState(void) const;
	
	public:
	
		inline									QDatabaseInterfaceIntermediary(QWidget*, const QString&);
};

QDatabaseInterfaceIntermediary::QDatabaseInterfaceIntermediary(QWidget* foo, const QString& name) : 
	QMainWindow(foo),
	informationWindow(new QMainWindow(this)),
	informationContent(new QTextBrowser(informationWindow)),
	barNamesButton(new QPushButton("Bar Names", this)),
	barTextsButton(new QPushButton("Bar Texts", this)),
	keepListButton(new QPushButton("Keep List", this)),
	resetButton(new QPushButton("Reset Buttons", this)),
	nameLineEdit(new QLineEdit(this)),
	loreLineEdit(new QLineEdit(this)),
	resultList(new QListWidget(this)),
	lore(new QTextBrowser(this)),
	label(new QLabel(this)),
	contentName(name)
{
	QDatabaseInterfaceIntermediary::Databases[name] = this;
	QObject::connect(QDatabaseInterfaceIntermediary::resetButton, SIGNAL(released(void)), this, SLOT(resetEverything(void)));
	QObject::connect(QDatabaseInterfaceIntermediary::resultList, SIGNAL(currentRowChanged(int)), this, SLOT(showDescriptionFromList(int)));
	QObject::connect(QDatabaseInterfaceIntermediary::lore, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(showDescription(const QUrl&)));
	
	QDatabaseInterfaceIntermediary::nameLineEdit->setPlaceholderText("Search names...");
	QDatabaseInterfaceIntermediary::nameLineEdit->installEventFilter(this);
	
	QDatabaseInterfaceIntermediary::loreLineEdit->setPlaceholderText("Search descriptions...");
	QDatabaseInterfaceIntermediary::loreLineEdit->installEventFilter(this);
	
	QDatabaseInterfaceIntermediary::lore->setReadOnly(true);
	QDatabaseInterfaceIntermediary::lore->setOpenLinks(false);
	QDatabaseInterfaceIntermediary::lore->installEventFilter(this);
	
	const auto layout = new QVBoxLayout(new QWidget());
	QDatabaseInterfaceIntermediary::informationWindow->setCentralWidget(layout->parentWidget());
	layout->addWidget(QDatabaseInterfaceIntermediary::informationContent);
	
	QDatabaseInterfaceIntermediary::informationWindow->setWindowTitle("Information Window");
	QDatabaseInterfaceIntermediary::informationWindow->resize(600, 800);
	
	const auto flags = QDatabaseInterfaceIntermediary::informationWindow->windowFlags();
	QDatabaseInterfaceIntermediary::informationWindow->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
	
	QDatabaseInterfaceIntermediary::informationContent->setReadOnly(true);
	QDatabaseInterfaceIntermediary::informationContent->setOpenLinks(false);
	QObject::connect(QDatabaseInterfaceIntermediary::informationContent, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(showDescription(const QUrl&)));
	
	QString stylesheet = "table, td { border: 1px solid #333; }"
				"thead, tfoot { background-color: #333; color: #fff; }";
	
	//QDatabaseInterfaceIntermediary::lore->document()->setDefaultStyleSheet(stylesheet);
}

bool QDatabaseInterfaceIntermediary::Correlate(const QString& str1, const QString& str2)
{
	const auto size1 = str1.size();
	const auto size2 = str2.size();
	
	if (size2 > size1 and size2 - size1 >= 3)
		return false;
	
	if (size1 > size2 and size1 - size2 >= 3)
		return false;
	
	auto count = 0;
	auto it1 = str1.cbegin();
	auto it2 = str2.cbegin();
	
	while (count < size1 and count < size2 and *it1 == *it2)
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
	
	while (count < size1 and count < size2 and *itt1 == *itt2)
	{
		++count;
		++itt1;
		++itt2;
	}
	
	return (size1 == count or size2 == count);
}

void QDatabaseInterfaceIntermediary::GetLine(std::ifstream& stream, std::string& line)
{
	char c;
	line.clear();

	while (stream.get(c) and c != '\n')
	{
		switch (c)
		{
			case '[':
			case ']':
			case '|':
			case '{':
			case '}':
				break;
			
			default:
				line.push_back(c);
				break;
		}
	}
}

char QDatabaseInterfaceIntermediary::LowerCase(char c)
{
	return (c < 'A' or c > 'Z' ? c : c - 'A' + 'a');
}

std::string QDatabaseInterfaceIntermediary::MakeList(const std::vector<std::string>& listCells)
{
	if (listCells.empty())
		return "";
	
	std::string result("<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\">");
	bool newItem = true;
	
	for (const auto& str : listCells)
	{
		if (str[0u] != '^')
		{
			if (!newItem)
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
			
			result += "<li align=\"justify\">" + str.substr(1u) + "</li>";
		}
	}
	
	return result + "</ul>";
}

std::string QDatabaseInterfaceIntermediary::MakeTable(const std::vector<std::string>& tableCells, qint32 rows)
{
	if (tableCells.empty())
		return "";
	
	std::string result("<p align=\"center\"><table border=\"1\" cellspacing=\"2\">");
	const auto columns = tableCells.size()/rows;
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

QString QDatabaseInterfaceIntermediary::Process(const std::string& lore, const QString& pattern)
{
	const auto lorend = lore.cend();
	
	std::string text("<p align=\"justify\">");
	text.reserve(lore.capacity()*2u);
	bool listOrTable = false;
	
	for (auto lorit = lore.cbegin(); lorit != lorend; ++lorit)
	{
		switch (*lorit)
		{
			case '#':
			{
				if (!listOrTable)
				{
					text += "</p>";
					listOrTable = true;
				}
				
				++lorit;
				
				std::vector<std::string> table;
				auto beg = lorit;
				auto rows = 1;
				
				while (*lorit != '#')
				{
					switch (*lorit)
					{
						case ':':
							++rows;
							[[fallthrough]];
						
						case ';':
							table.emplace_back(beg, lorit);
							beg = lorit + 1u;
						
						default:
							break;
					}
					
					++lorit;
				}
				
				table.emplace_back(beg, lorit);
				text += QDatabaseInterfaceIntermediary::MakeTable(table, rows);
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
				
				++lorit;
				
				std::vector<std::string> lst;
				auto beg = lorit;
				
				while (lorit != lorend and *lorit != '$' and *lorit != '#')
				{
					switch (*lorit)
					{
						case '*':
						{
							lst.emplace_back(beg, lorit);
							beg = lorit + 1u;
							break;
						}
						
						case '^':
						{
							lst.emplace_back(beg, lorit);
							beg = lorit;
							break;
						}
						
						default:
							break;
					}
					
					++lorit;
				}
				
				lst.emplace_back(beg, lorit);
				text += QDatabaseInterfaceIntermediary::MakeList(lst);
				--lorit;
				break;
			}
			
			case '$':
			{
				if (!listOrTable)
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
				
				text += *lorit;
				break;
			}
		}
	}
	
	const auto size = static_cast<qint32>(pattern.size());
	auto braces = 0u;
	auto fixes = 0u;
	auto pos = 0u;
	
	const auto beg = pattern.cbegin();
	const auto end = pattern.cend();
	const auto textend = text.cend();
	auto it = beg;
	
	std::string utf8;
	utf8.reserve(4u);
	
	QString result;
	result.reserve(text.capacity());
	
	for (auto textit = text.cbegin(); textit != textend; ++textit)
	{
		if (*textit & 128u)
		{
			utf8.push_back(*textit);
			continue;
		}
		
		if (!utf8.empty())
		{
			result += QString::fromUtf8(utf8.c_str());
			utf8.clear();
		}
		
		switch (*textit)
		{
			case '[':
			{
				++textit;
				
				switch (*textit)
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
						--textit;
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
				result += (fixes % 2u != 0u ? QDatabaseInterfaceIntermediary::FixEnd : QDatabaseInterfaceIntermediary::FixStart);
				++fixes;
				break;
			}
				
			case '{':
			{
				while (*textit == '{')
				{
					++textit;
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
				
				--textit;
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
						++textit;
						break;
					
					default:
						break;
				}
				
				braces = 0u;
				break;
			}
		
			default:
			{
				if (size > 0 and QDatabaseInterfaceIntermediary::LowerCase(*textit) == *it)
				{
					if (it == beg)
						pos = result.size();
					
					++it;
					
					if (it == end)
					{
						result.insert(pos, QDatabaseInterfaceIntermediary::HighlightStart);
						result += *textit;
						result += QDatabaseInterfaceIntermediary::HighlightEnd;
					}
					else
						result += *textit;
				}
				else
				{
					it = beg;
					result += *textit;
				}
				
				break;
			}
		}
	}
	
	return result + "</p>";
}

void QDatabaseInterfaceIntermediary::switchButtonState(void) const
{
	const auto sender = static_cast<QWidget*>(QObject::sender());
	const auto name = sender->objectName().toStdString();
	
	switch (name.size())
	{
		case 1u:
			sender->setObjectName(name[0u] == 'A' ? "AA" : "BB");
			break;
		
		case 2u:
			sender->setObjectName(name[0u] == 'A' ? "AAA" : "BBB");
			break;
		
		case 3u:
			sender->setObjectName(name[0u] == 'A' ? "AAAA" : "B");
			break;
		
		default:
		{
			const auto& childList = sender->children();
			
			if (childList.size() > 0)
				static_cast<QWidget*>(childList.front())->show();
				
			sender->setObjectName("A");
			break;
		}
	}

	sender->style()->unpolish(sender);
	sender->style()->polish(sender);
}

void QDatabaseInterfaceIntermediary::showDescription(const QUrl& url) const
{
	const auto lore = (QObject::sender() == QDatabaseInterfaceIntermediary::lore ? QDatabaseInterfaceIntermediary::lore : QDatabaseInterfaceIntermediary::informationContent);
	const auto otherLore = (QObject::sender() == QDatabaseInterfaceIntermediary::lore ? QDatabaseInterfaceIntermediary::informationContent : QDatabaseInterfaceIntermediary::lore);
	
	const auto& name = lore->textCursor().selectedText();
	const auto& descriptor = url.url();
	
	if (const auto dbit = QDatabaseInterfaceIntermediary::Databases.find(descriptor); dbit != QDatabaseInterfaceIntermediary::Databases.cend())
	{
		if (const auto it = dbit->second->fullIndex.find(name); it != dbit->second->fullIndex.cend())
		{
			dbit->second->updateLore(it->first, otherLore, it->second);
			QDatabaseInterfaceIntermediary::informationWindow->show();
		}
		else
		{
			const auto start = name.left(3);
			const auto stop = name.left(2) + static_cast<char>(static_cast<quint32>(name[2].toLatin1()) + 1u);
			const auto end = dbit->second->fullIndex.upper_bound(stop);
			
			for (auto it = dbit->second->fullIndex.lower_bound(start); it != end; ++it)
			{
				if (QDatabaseInterfaceIntermediary::Correlate(name, it->first))
				{
					dbit->second->updateLore(it->first, otherLore, it->second);
					QDatabaseInterfaceIntermediary::informationWindow->show();
					break;
				}
			}
		}
	}
	else
	{
		for (const auto& pr : QDatabaseInterfaceIntermediary::Databases)
		{
			if (const auto it = pr.second->fullIndex.find(name); it != pr.second->fullIndex.cend())
			{
				pr.second->updateLore(it->first, otherLore, it->second);
				QDatabaseInterfaceIntermediary::informationWindow->show();
				break;
			}
		}
	}
}

void QDatabaseInterfaceIntermediary::showDescriptionFromList(int row) const
{
	this->updateLoreFromList(QDatabaseInterfaceIntermediary::lore, row);
}

void QDatabaseInterfaceIntermediary::resetEverything(void)
{
	this->resetButtons();
}

#endif
