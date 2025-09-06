#ifndef __Q_POWER_DATABASE_INTERFACE_HPP__
#define __Q_POWER_DATABASE_INTERFACE_HPP__

// Qt Libraries
#include <QGroupBox>
#include <QShortcut>

// Custom Libraries
#include "HexBitsetPack.hpp"
#include "QAbstractDatabaseWindow.hpp"

class QPowerDatabaseWindow : public QAbstractDatabaseWindow
{
	private:
	
		static constexpr QColor				ClairsentienceColor = QColor(255, 153, 51);
		static constexpr QColor				MetacreativityColor = QColor(255, 102, 102);
		static constexpr QColor				PsychokinesisColor = QColor(102, 178, 255);
		static constexpr QColor				PsychometabolismColor = QColor(204, 153, 255);
		static constexpr QColor				PsychoportationColor = QColor(20, 205, 113);
		static constexpr QColor				TelepathyColor = QColor(255, 153, 255);
		
		static constexpr quint32			Number = static_cast<quint32>(PowerEnum::SIZE);
		
		inline static QColor				Foreground(const HexBitset<Number>&);
		
		std::vector<HexFile<Number>>			allPowers;
		QFile						powerFile;
		QTextStream					powerFileStream;
		
		inline void					initialiseAreas(const QFont&, QGridLayout*);
		inline void					initialiseClasses(const QFont&, QGridLayout*);
		inline void					initialiseControlButtons(const QFont&, QGridLayout*);
		inline void					initialiseData(void);
		inline void					initialiseDescriptors(const QFont&, QGridLayout*);
		inline void					initialiseDisciplines(const QFont&, QGridLayout*);
		inline void					initialiseDisplays(const QFont&, QGridLayout*);
		inline void					initialiseDurations(const QFont&, QGridLayout*);
		inline void					initialiseEffects(const QFont&, QGridLayout*);
		inline void					initialiseEverythingElse(QGridLayout*);
		inline void					initialiseFeatures(const QFont&, QGridLayout*);
		inline void					initialiseLevels(const QFont&, QGridLayout*);
		inline void					initialiseManifestingTimes(const QFont&, QGridLayout*);
		inline void					initialisePowerResistances(const QFont&, QGridLayout*);
		inline void					initialiseRanges(const QFont&, QGridLayout*);
		inline void					initialiseSaves(const QFont&, QGridLayout*);
		inline void					initialiseSources(const QFont&, QGridLayout*);
		inline void					initialiseSpecial(const QFont&, QGridLayout*);
		inline void					initialiseSubdisciplines(const QFont&, QGridLayout*);
		inline void					initialiseTargets(const QFont&, QGridLayout*);
		inline void					initialiseWidgets(void);
		inline void					initialiseWindow(const HexFamily&, const QFont&, qint32);
		inline bool					powerIsValid(const HexFile<Number>&, const HexBitset<Number>&, const HexBitset<Number>&, const std::vector<HexBitset<Number>>&, const QString&, const QString&, bool, bool);
		
	protected slots:
	
		inline void					search(void) final;
	
	protected:
	
		inline void					closeEvent(QCloseEvent*);
		inline void					updateLore(quint32, QTextBrowser*) final;
	
	public:
	
		inline						QPowerDatabaseWindow(QWidget*);
};

QPowerDatabaseWindow::QPowerDatabaseWindow(QWidget* foo) :
	QAbstractDatabaseWindow(foo, "power"),
	powerFile("files/powers.txt"),
	powerFileStream(&powerFile)
{
	QPowerDatabaseWindow::initialiseData();
	QPowerDatabaseWindow::initialiseWidgets();
	
	const auto s1 = new QShortcut(QAbstractDatabaseWindow::mainWidget);
	s1->setKeys({ QKeySequence(Qt::Key_Return), QKeySequence(Qt::Key_Enter) });
	
	QObject::connect(s1, SIGNAL(activated(void)), this, SLOT(search(void)));
}

QColor QPowerDatabaseWindow::Foreground(const HexBitset<Number>& b)
{
	if (b.testBit(PowerEnum::PSYCHOPORTATION))
		return QPowerDatabaseWindow::PsychoportationColor;
	
	if (b.testBit(PowerEnum::METACREATIVITY))
		return QPowerDatabaseWindow::MetacreativityColor;
	
	if (b.testBit(PowerEnum::CLAIRSENTIENCE))
		return QPowerDatabaseWindow::ClairsentienceColor;
	
	if (b.testBit(PowerEnum::TELEPATHY))
		return QPowerDatabaseWindow::TelepathyColor;
	
	if (b.testBit(PowerEnum::PSYCHOKINESIS))
		return QPowerDatabaseWindow::PsychokinesisColor;
	
	if (b.testBit(PowerEnum::PSYCHOMETABOLISM))
		return QPowerDatabaseWindow::PsychometabolismColor;
	
	return QColor(0, 0, 0);
}

void QPowerDatabaseWindow::initialiseAreas(const QFont& font, QGridLayout* layout)
{
	const auto areaBox = new QGroupBox("Areas", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(10u);
	
	newGroup.familyGroups.emplace_back("Circle", areaBox, PowerEnum::CIRCLE);
	newGroup.familyGroups.emplace_back("Cone", areaBox, PowerEnum::CONE);
	newGroup.familyGroups.emplace_back("Cylinder", areaBox, PowerEnum::CYLINDER);
	newGroup.familyGroups.emplace_back("Line", areaBox, PowerEnum::LINE);
	newGroup.familyGroups.emplace_back("Plane", areaBox, PowerEnum::PLANE);
	newGroup.familyGroups.emplace_back("Sphere", areaBox, PowerEnum::SPHERE);
	newGroup.familyGroups.emplace_back("Shapeable", areaBox, PowerEnum::SHAPEABLE);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", areaBox);
	otherGroup.familyGroups.emplace_back("Cube", areaBox, PowerEnum::CUBE);
	otherGroup.familyGroups.emplace_back("Square", areaBox, PowerEnum::SQUARE);
	otherGroup.familyGroups.emplace_back("Peculiar", areaBox, PowerEnum::PECULIAR_AREA);
	
	newGroup.familyGroups.emplace_back("Centered", areaBox, PowerEnum::CENTERED);
	
	const auto areaLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		areaLayout->addWidget(foo.masterButton, count/5, count % 5);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	areaBox->setLayout(areaLayout);
	layout->addWidget(areaBox, 5, 5, 2, 5);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 3);
}

void QPowerDatabaseWindow::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Classes", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Lurk", classBox, PowerEnum::LURK);
	newGroup.familyGroups.emplace_back("Psion", classBox, PowerEnum::PSION);
	newGroup.familyGroups.emplace_back("Psychic Rogue", classBox, PowerEnum::PSYCHIC_ROGUE);
	newGroup.familyGroups.emplace_back("Psychic Warrior", classBox, PowerEnum::PSYCHIC_WARRIOR);
	
	const auto classLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		classLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	classBox->setLayout(classLayout);
	layout->addWidget(classBox, 0, 0, 1, 4);
}

void QPowerDatabaseWindow::initialiseControlButtons(const QFont& font, QGridLayout* layout)
{
	const auto filterControlBox = new QGroupBox("Filter Controls", QAbstractDatabaseWindow::mainWidget);
	const auto filterControlLayout = new QGridLayout();
	
	const auto buttonList = { QAbstractDatabaseWindow::barNamesButton, QAbstractDatabaseWindow::keepListButton, QAbstractDatabaseWindow::barTextsButton };
	auto count = 0;
	
	for (const auto& btn : buttonList)
	{
		filterControlLayout->addWidget(btn, count/2, count % 2);
		btn->setObjectName("KL");
		btn->setCheckable(true);
		btn->setFont(font);
		++count;
	}
	
	filterControlLayout->addWidget(QAbstractDatabaseWindow::resetButton, 1, 1);
	QAbstractDatabaseWindow::resetButton->setObjectName("KL");
	QAbstractDatabaseWindow::resetButton->setFont(font);
	
	filterControlBox->setLayout(filterControlLayout);
	layout->addWidget(filterControlBox, 9, 8, 2, 2);
}

void QPowerDatabaseWindow::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Acid", descriptorBox, PowerEnum::ACID);
	newGroup.familyGroups.emplace_back("Cold", descriptorBox, PowerEnum::COLD);
	newGroup.familyGroups.emplace_back("Darkness", descriptorBox, PowerEnum::DARKNESS);
	newGroup.familyGroups.emplace_back("Death", descriptorBox, PowerEnum::DEATH);
	newGroup.familyGroups.emplace_back("Electricity", descriptorBox, PowerEnum::ELECTRICITY);
	newGroup.familyGroups.emplace_back("Evil", descriptorBox, PowerEnum::EVIL);
	newGroup.familyGroups.emplace_back("Fear", descriptorBox, PowerEnum::FEAR);
	newGroup.familyGroups.emplace_back("Fire", descriptorBox, PowerEnum::FIRE);
	newGroup.familyGroups.emplace_back("Force", descriptorBox, PowerEnum::FORCE);
	newGroup.familyGroups.emplace_back("Good", descriptorBox, PowerEnum::GOOD);
	newGroup.familyGroups.emplace_back("Language", descriptorBox, PowerEnum::LANGUAGE_DEPENDENT);
	newGroup.familyGroups.emplace_back("Light", descriptorBox, PowerEnum::LIGHT);
	newGroup.familyGroups.emplace_back("Mind-Affecting", descriptorBox, PowerEnum::MIND_AFFECTING);
	newGroup.familyGroups.emplace_back("Shadow", descriptorBox, PowerEnum::SHADOW);
	newGroup.familyGroups.emplace_back("Sonic", descriptorBox, PowerEnum::SONIC);
	
	const auto descriptorLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		descriptorLayout->addWidget(foo.masterButton, count/5, count % 5);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	descriptorBox->setLayout(descriptorLayout);
	layout->addWidget(descriptorBox, 2, 4, 3, 5);
}

void QPowerDatabaseWindow::initialiseDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto disciplineBox = new QGroupBox("Disciplines", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Clairsentience", disciplineBox, PowerEnum::CLAIRSENTIENCE);
	newGroup.familyGroups.emplace_back("Metacreativity", disciplineBox, PowerEnum::METACREATIVITY);
	newGroup.familyGroups.emplace_back("Psychokinesis", disciplineBox, PowerEnum::PSYCHOKINESIS);
	newGroup.familyGroups.emplace_back("Psychometabolism", disciplineBox, PowerEnum::PSYCHOMETABOLISM);
	newGroup.familyGroups.emplace_back("Psychoportation", disciplineBox, PowerEnum::PSYCHOPORTATION);
	newGroup.familyGroups.emplace_back("Telepathy", disciplineBox, PowerEnum::TELEPATHY);
	
	const auto disciplineLayout = new QHBoxLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		disciplineLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	disciplineBox->setLayout(disciplineLayout);
	layout->addWidget(disciplineBox, 0, 4, 1, 6);
}

void QPowerDatabaseWindow::initialiseDisplays(const QFont& font, QGridLayout* layout)
{
	const auto displayBox = new QGroupBox("Displays", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Auditory", displayBox, PowerEnum::AUDITORY);
	newGroup.familyGroups.emplace_back("Material", displayBox, PowerEnum::MATERIAL);
	newGroup.familyGroups.emplace_back("Mental", displayBox, PowerEnum::MENTAL);
	newGroup.familyGroups.emplace_back("Olfactory", displayBox, PowerEnum::OLFACTORY);
	newGroup.familyGroups.emplace_back("Visual", displayBox, PowerEnum::VISUAL);
	
	const auto displayLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		displayLayout->addWidget(foo.masterButton, count/2, count % 2);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	displayBox->setLayout(displayLayout);
	layout->addWidget(displayBox, 2, 2, 3, 2);
}

void QPowerDatabaseWindow::initialiseDurations(const QFont& font, QGridLayout* layout)
{
	const auto durationBox = new QGroupBox("Durations", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(20u);
	
	newGroup.familyGroups.emplace_back("Instantaneous", durationBox, PowerEnum::INSTANTANEOUS);
	newGroup.familyGroups.emplace_back("1 round/2+ levels", durationBox, PowerEnum::ONE_ROUND_TWO_LEVELS);
	newGroup.familyGroups.emplace_back("1+ round/level", durationBox, PowerEnum::ONE_ROUND_LEVEL);
	newGroup.familyGroups.emplace_back("1+ minute/level", durationBox, PowerEnum::ONE_MINUTE_LEVEL);
	newGroup.familyGroups.emplace_back("10+ minutes/level", durationBox, PowerEnum::TEN_MINUTES_LEVEL);
	newGroup.familyGroups.emplace_back("1+ hour/level", durationBox, PowerEnum::ONE_HOUR_LEVEL);
	newGroup.familyGroups.emplace_back("1+ day/level", durationBox, PowerEnum::ONE_DAY_LEVEL);
	
	auto& fixedGroup = newGroup.familyGroups.emplace_back("Fixed", durationBox);
	fixedGroup.familyGroups.emplace_back("1+ round", durationBox, PowerEnum::FIXED_ONE_ROUND);
	fixedGroup.familyGroups.emplace_back("1+ minute", durationBox, PowerEnum::FIXED_ONE_MINUTE);
	fixedGroup.familyGroups.emplace_back("10+ minutes", durationBox, PowerEnum::FIXED_TEN_MINUTES);
	fixedGroup.familyGroups.emplace_back("1+ hour", durationBox, PowerEnum::FIXED_ONE_HOUR);
	fixedGroup.familyGroups.emplace_back("1+ day", durationBox, PowerEnum::FIXED_ONE_DAY);
	fixedGroup.familyGroups.emplace_back("1+ month", durationBox, PowerEnum::FIXED_ONE_MONTH);
	fixedGroup.familyGroups.emplace_back("1+ year", durationBox, PowerEnum::FIXED_ONE_YEAR);
	
	newGroup.familyGroups.emplace_back("Concentration", durationBox, PowerEnum::CONCENTRATION);
	newGroup.familyGroups.emplace_back("Permanent", durationBox, PowerEnum::PERMANENT);
	newGroup.familyGroups.emplace_back("See text", durationBox, PowerEnum::DURATION_SEE_TEXT);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", durationBox);
	otherGroup.familyGroups.emplace_back("Dice", durationBox, PowerEnum::DICE_DURATION);
	otherGroup.familyGroups.emplace_back("Peculiar", durationBox, PowerEnum::PECULIAR_DURATION);
	
	newGroup.familyGroups.emplace_back("Then", durationBox, PowerEnum::THEN_DURATION);
	newGroup.familyGroups.emplace_back("Dismiss", durationBox, PowerEnum::DISMISS);
	newGroup.familyGroups.emplace_back("Discharge", durationBox, PowerEnum::DISCHARGE);
	newGroup.familyGroups.emplace_back("Trigger", durationBox, PowerEnum::TRIGGER);
	
	const auto durationLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		durationLayout->addWidget(foo.masterButton, count/8, count % 8);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	durationBox->setLayout(durationLayout);
	layout->addWidget(durationBox, 9, 0, 2, 8);
	
	QAbstractDatabaseWindow::initialiseWindow(fixedGroup, font, 4);
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 2);
}

void QPowerDatabaseWindow::initialiseEffects(const QFont& font, QGridLayout* layout)
{
	const auto effectBox = new QGroupBox("Effects", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Burst", effectBox, PowerEnum::BURST);
	newGroup.familyGroups.emplace_back("Emanation", effectBox, PowerEnum::EMANATION);
	newGroup.familyGroups.emplace_back("Ray", effectBox, PowerEnum::RAY);
	newGroup.familyGroups.emplace_back("Spread", effectBox, PowerEnum::SPREAD);
	
	const auto effectLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		effectLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	effectBox->setLayout(effectLayout);
	layout->addWidget(effectBox, 8, 6, 1, 4);
}

void QPowerDatabaseWindow::initialiseEverythingElse(QGridLayout* layout)
{
	layout->addWidget(QAbstractDatabaseWindow::nameLineEdit, 13, 0, 1, 5);
	layout->addWidget(QAbstractDatabaseWindow::loreLineEdit, 13, 5, 1, 5);
	
	layout->addWidget(QAbstractDatabaseWindow::resultList, 0, 10, 14, 7);
	layout->addWidget(QAbstractDatabaseWindow::loreBrowser, 0, 17, 13, 10);
	layout->addWidget(QAbstractDatabaseWindow::resultLabel, 13, 17, 1, 10);
}

void QPowerDatabaseWindow::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto featureBox = new QGroupBox("Features", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Augment", featureBox, PowerEnum::AUGMENT);
	newGroup.familyGroups.emplace_back("Experience", featureBox, PowerEnum::EXPERIENCE);
	
	const auto featureLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		featureLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	featureBox->setLayout(featureLayout);
	layout->addWidget(featureBox, 1, 2, 1, 2);
}

void QPowerDatabaseWindow::initialiseLevels(const QFont& font, QGridLayout* layout)
{
	const auto levelBox = new QGroupBox("Levels", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("0", levelBox, PowerEnum::LEVEL_0);
	newGroup.familyGroups.emplace_back("1", levelBox, PowerEnum::LEVEL_1);
	newGroup.familyGroups.emplace_back("2", levelBox, PowerEnum::LEVEL_2);
	newGroup.familyGroups.emplace_back("3", levelBox, PowerEnum::LEVEL_3);
	newGroup.familyGroups.emplace_back("4", levelBox, PowerEnum::LEVEL_4);
	newGroup.familyGroups.emplace_back("5", levelBox, PowerEnum::LEVEL_5);
	newGroup.familyGroups.emplace_back("6", levelBox, PowerEnum::LEVEL_6);
	newGroup.familyGroups.emplace_back("7", levelBox, PowerEnum::LEVEL_7);
	newGroup.familyGroups.emplace_back("8", levelBox, PowerEnum::LEVEL_8);
	newGroup.familyGroups.emplace_back("9", levelBox, PowerEnum::LEVEL_9);
	
	const auto levelLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		levelLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	levelBox->setLayout(levelLayout);
	layout->addWidget(levelBox, 7, 0, 1, 10);
}

void QPowerDatabaseWindow::initialiseManifestingTimes(const QFont& font, QGridLayout* layout)
{
	const auto manifestingTimeBox = new QGroupBox("Manifesting Times", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Immediate", manifestingTimeBox, PowerEnum::IMMEDIATE);
	newGroup.familyGroups.emplace_back("Swift", manifestingTimeBox, PowerEnum::SWIFT);
	newGroup.familyGroups.emplace_back("Move", manifestingTimeBox, PowerEnum::MOVE);
	newGroup.familyGroups.emplace_back("Standard", manifestingTimeBox, PowerEnum::STANDARD);
	newGroup.familyGroups.emplace_back("1 round", manifestingTimeBox, PowerEnum::ONE_ROUND);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", manifestingTimeBox);
	otherGroup.familyGroups.emplace_back("2+ rounds", manifestingTimeBox, PowerEnum::TWO_ROUNDS);
	otherGroup.familyGroups.emplace_back("1+ minute", manifestingTimeBox, PowerEnum::ONE_MINUTE);
	otherGroup.familyGroups.emplace_back("10+ minutes", manifestingTimeBox, PowerEnum::TEN_MINUTES);
	otherGroup.familyGroups.emplace_back("1+ hour", manifestingTimeBox, PowerEnum::ONE_HOUR);
	otherGroup.familyGroups.emplace_back("1+ day", manifestingTimeBox, PowerEnum::ONE_DAY);
	otherGroup.familyGroups.emplace_back("See text", manifestingTimeBox, PowerEnum::TIME_SEE_TEXT);
	otherGroup.familyGroups.emplace_back("Peculiar", manifestingTimeBox, PowerEnum::PECULIAR_TIME);
	
	const auto manifestingTimeLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		manifestingTimeLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	manifestingTimeBox->setLayout(manifestingTimeLayout);
	layout->addWidget(manifestingTimeBox, 8, 0, 1, 6);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 4);
}

void QPowerDatabaseWindow::initialiseRanges(const QFont& font, QGridLayout* layout)
{
	const auto rangeBox = new QGroupBox("Ranges", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(10u);
	
	newGroup.familyGroups.emplace_back("Personal", rangeBox, PowerEnum::PERSONAL);
	newGroup.familyGroups.emplace_back("Touch", rangeBox, PowerEnum::TOUCH);
	newGroup.familyGroups.emplace_back("Close", rangeBox, PowerEnum::CLOSE);
	newGroup.familyGroups.emplace_back("Medium", rangeBox, PowerEnum::MEDIUM);
	newGroup.familyGroups.emplace_back("Long", rangeBox, PowerEnum::LONG);
	
	auto& fixedGroup = newGroup.familyGroups.emplace_back("Fixed", rangeBox);
	fixedGroup.familyGroups.emplace_back("0 foot", rangeBox, PowerEnum::FIXED_0_FOOT);
	fixedGroup.familyGroups.emplace_back("15+ feet", rangeBox, PowerEnum::FIXED_15_FEET);
	fixedGroup.familyGroups.emplace_back("30+ feet", rangeBox, PowerEnum::FIXED_30_FEET);
	fixedGroup.familyGroups.emplace_back("60+ feet", rangeBox, PowerEnum::FIXED_60_FEET);
	fixedGroup.familyGroups.emplace_back("120+ feet", rangeBox, PowerEnum::FIXED_120_FEET);
	fixedGroup.familyGroups.emplace_back("1+ mile", rangeBox, PowerEnum::FIXED_1_MILE);
	
	newGroup.familyGroups.emplace_back("Unlimited", rangeBox, PowerEnum::UNLIMITED);
	newGroup.familyGroups.emplace_back("Boundless", rangeBox, PowerEnum::BOUNDLESS);
	newGroup.familyGroups.emplace_back("See text", rangeBox, PowerEnum::RANGE_SEE_TEXT);
	newGroup.familyGroups.emplace_back("Peculiar", rangeBox, PowerEnum::PECULIAR_RANGE);
	
	const auto rangeLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		rangeLayout->addWidget(foo.masterButton, count/5, count % 5);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	rangeBox->setLayout(rangeLayout);
	layout->addWidget(rangeBox, 5, 0, 2, 5);
	
	QAbstractDatabaseWindow::initialiseWindow(fixedGroup, font, 4);
}

void QPowerDatabaseWindow::initialiseSaves(const QFont& font, QGridLayout* layout)
{
	const auto saveBox = new QGroupBox("Saves", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Fortitude", saveBox, PowerEnum::FORTITUDE);
	newGroup.familyGroups.emplace_back("Reflex", saveBox, PowerEnum::REFLEX);
	newGroup.familyGroups.emplace_back("Will", saveBox, PowerEnum::WILL);
	newGroup.familyGroups.emplace_back("Object", saveBox, PowerEnum::SAVE_OBJECT);
	newGroup.familyGroups.emplace_back("Negate", saveBox, PowerEnum::NEGATE);
	newGroup.familyGroups.emplace_back("Partial", saveBox, PowerEnum::PARTIAL);
	newGroup.familyGroups.emplace_back("Half", saveBox, PowerEnum::HALF);
	newGroup.familyGroups.emplace_back("Disbelief", saveBox, PowerEnum::DISBELIEF);
	newGroup.familyGroups.emplace_back("Harmless", saveBox, PowerEnum::SAVE_HARMLESS);
	newGroup.familyGroups.emplace_back("See text", saveBox, PowerEnum::SAVE_SEE_TEXT);
	
	const auto saveLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		saveLayout->addWidget(foo.masterButton, count/5, count % 5);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	saveBox->setLayout(saveLayout);
	layout->addWidget(saveBox, 11, 3, 2, 5);
}

void QPowerDatabaseWindow::initialiseSources(const QFont& font, QGridLayout* layout)
{
	const auto sourceBox = new QGroupBox("Sources", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("XPH", sourceBox, PowerEnum::EXPANDED_PSIONICS_HANDBOOK);
	newGroup.familyGroups.emplace_back("CPsi", sourceBox, PowerEnum::COMPLETE_PSIONIC);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", sourceBox);
	otherGroup.familyGroups.emplace_back("DrM", sourceBox, PowerEnum::DRAGON_MAGIC);
	otherGroup.familyGroups.emplace_back("FoE", sourceBox, PowerEnum::FAITHS_OF_EBERRON);
	otherGroup.familyGroups.emplace_back("Hyp", sourceBox, PowerEnum::HYPERCONSCIOUS);
	otherGroup.familyGroups.emplace_back("MoE", sourceBox, PowerEnum::MAGIC_OF_EBERRON);
	otherGroup.familyGroups.emplace_back("MoI", sourceBox, PowerEnum::MAGIC_OF_INCARNUM);
	otherGroup.familyGroups.emplace_back("PGE", sourceBox, PowerEnum::PLAYERS_GUIDE_TO_EBERRON);
	otherGroup.familyGroups.emplace_back("RDr", sourceBox, PowerEnum::RACES_OF_THE_DRAGON);
	otherGroup.familyGroups.emplace_back("RW", sourceBox, PowerEnum::RACES_OF_THE_WILD);
	otherGroup.familyGroups.emplace_back("SoS", sourceBox, PowerEnum::SECRETS_OF_SARLONA);
	otherGroup.familyGroups.emplace_back("Sto", sourceBox, PowerEnum::STORMWRACK);
	otherGroup.familyGroups.emplace_back("WL", sourceBox, PowerEnum::WEAPONS_OF_LEGACY);
	otherGroup.familyGroups.emplace_back("Web", sourceBox, PowerEnum::WEB);
	
	const auto sourceLayout = new QVBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		sourceLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	sourceBox->setLayout(sourceLayout);
	layout->addWidget(sourceBox, 2, 9, 3, 1);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 4);
}

void QPowerDatabaseWindow::initialiseSpecial(const QFont& font, QGridLayout* layout)
{
	const auto specialBox = new QGroupBox("Special", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Body Leech", specialBox, PowerEnum::BODY_LEECH);
	newGroup.familyGroups.emplace_back("Egoist", specialBox, PowerEnum::EGOIST);
	newGroup.familyGroups.emplace_back("Kineticist", specialBox, PowerEnum::KINETICIST);
	newGroup.familyGroups.emplace_back("Nomad", specialBox, PowerEnum::NOMAD);
	newGroup.familyGroups.emplace_back("Seer", specialBox, PowerEnum::SEER);
	newGroup.familyGroups.emplace_back("Shaper", specialBox, PowerEnum::SHAPER);
	newGroup.familyGroups.emplace_back("Telepath", specialBox, PowerEnum::TELEPATH);
	
	auto& mantleGroup = newGroup.familyGroups.emplace_back("Mantles", specialBox);
	mantleGroup.familyGroups.emplace_back("Air", specialBox, PowerEnum::AIR_MANTLE);
	mantleGroup.familyGroups.emplace_back("Chaos", specialBox, PowerEnum::CHAOS_MANTLE);
	mantleGroup.familyGroups.emplace_back("Communication", specialBox, PowerEnum::COMMUNICATION_MANTLE);
	mantleGroup.familyGroups.emplace_back("Conflict", specialBox, PowerEnum::CONFLICT_MANTLE);
	mantleGroup.familyGroups.emplace_back("Consumption", specialBox, PowerEnum::CONSUMPTION_MANTLE);
	mantleGroup.familyGroups.emplace_back("Corruption and Madness", specialBox, PowerEnum::CORRUPTION_AND_MADNESS_MANTLE);
	mantleGroup.familyGroups.emplace_back("Creation", specialBox, PowerEnum::CREATION_MANTLE);
	mantleGroup.familyGroups.emplace_back("Death", specialBox, PowerEnum::DEATH_MANTLE);
	mantleGroup.familyGroups.emplace_back("Deception", specialBox, PowerEnum::DECEPTION_MANTLE);
	mantleGroup.familyGroups.emplace_back("Destruction", specialBox, PowerEnum::DESTRUCTION_MANTLE);
	mantleGroup.familyGroups.emplace_back("Earth", specialBox, PowerEnum::EARTH_MANTLE);
	mantleGroup.familyGroups.emplace_back("Elements", specialBox, PowerEnum::ELEMENTS_MANTLE);
	mantleGroup.familyGroups.emplace_back("Energy", specialBox, PowerEnum::ENERGY_MANTLE);
	mantleGroup.familyGroups.emplace_back("Evil", specialBox, PowerEnum::EVIL_MANTLE);
	mantleGroup.familyGroups.emplace_back("Fate", specialBox, PowerEnum::FATE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Fire", specialBox, PowerEnum::FIRE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Force", specialBox, PowerEnum::FORCE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Freedom", specialBox, PowerEnum::FREEDOM_MANTLE);
	mantleGroup.familyGroups.emplace_back("Good", specialBox, PowerEnum::GOOD_MANTLE);
	mantleGroup.familyGroups.emplace_back("Guardian", specialBox, PowerEnum::GUARDIAN_MANTLE);
	mantleGroup.familyGroups.emplace_back("Justice", specialBox, PowerEnum::JUSTICE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Knowledge", specialBox, PowerEnum::KNOWLEDGE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Law", specialBox, PowerEnum::LAW_MANTLE);
	mantleGroup.familyGroups.emplace_back("Life", specialBox, PowerEnum::LIFE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Light and Darkness", specialBox, PowerEnum::LIGHT_AND_DARKNESS_MANTLE);
	mantleGroup.familyGroups.emplace_back("Magic", specialBox, PowerEnum::MAGIC_MANTLE);
	mantleGroup.familyGroups.emplace_back("Mental Power", specialBox, PowerEnum::MENTAL_POWER_MANTLE);
	mantleGroup.familyGroups.emplace_back("Natural World", specialBox, PowerEnum::NATURAL_WORLD_MANTLE);
	mantleGroup.familyGroups.emplace_back("Pain and Suffering", specialBox, PowerEnum::PAIN_AND_SUFFERING_MANTLE);
	mantleGroup.familyGroups.emplace_back("Physical Power", specialBox, PowerEnum::PHYSICAL_POWER_MANTLE);
	mantleGroup.familyGroups.emplace_back("Plane", specialBox, PowerEnum::PLANE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Repose", specialBox, PowerEnum::REPOSE_MANTLE);
	mantleGroup.familyGroups.emplace_back("Time", specialBox, PowerEnum::TIME_MANTLE);
	mantleGroup.familyGroups.emplace_back("Water", specialBox, PowerEnum::WATER_MANTLE);
	
	const auto specialLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		specialLayout->addWidget(foo.masterButton, count/2, count % 2);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	specialBox->setLayout(specialLayout);
	layout->addWidget(specialBox, 1, 0, 4, 2);
	
	QAbstractDatabaseWindow::initialiseWindow(mantleGroup, font, 5);
}

void QPowerDatabaseWindow::initialisePowerResistances(const QFont& font, QGridLayout* layout)
{
	const auto resistanceBox = new QGroupBox("Power Resistance", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Yes", resistanceBox, PowerEnum::RESISTANCE),
	newGroup.familyGroups.emplace_back("Object", resistanceBox, PowerEnum::RESISTANCE_OBJECT),
	newGroup.familyGroups.emplace_back("Harmless", resistanceBox, PowerEnum::RESISTANCE_HARMLESS),
	newGroup.familyGroups.emplace_back("See text", resistanceBox, PowerEnum::RESISTANCE_SEE_TEXT);
	
	const auto resistanceLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		resistanceLayout->addWidget(foo.masterButton, count/2, count % 2);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	resistanceBox->setLayout(resistanceLayout);
	layout->addWidget(resistanceBox, 11, 8, 2, 2);
}

void QPowerDatabaseWindow::initialiseSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subdisciplineBox = new QGroupBox("Subdisciplines", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Charm", subdisciplineBox, PowerEnum::CHARM);
	newGroup.familyGroups.emplace_back("Compulsion", subdisciplineBox, PowerEnum::COMPULSION);
	newGroup.familyGroups.emplace_back("Creation", subdisciplineBox, PowerEnum::CREATION);
	newGroup.familyGroups.emplace_back("Healing", subdisciplineBox, PowerEnum::HEALING);
	newGroup.familyGroups.emplace_back("Scrying", subdisciplineBox, PowerEnum::SCRYING);
	newGroup.familyGroups.emplace_back("Teleportation", subdisciplineBox, PowerEnum::TELEPORTATION);
	
	const auto subdisciplineLayout = new QHBoxLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		subdisciplineLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	subdisciplineBox->setLayout(subdisciplineLayout);
	layout->addWidget(subdisciplineBox, 1, 4, 1, 6);
}

void QPowerDatabaseWindow::initialiseTargets(const QFont& font, QGridLayout* layout)
{
	const auto targetBox = new QGroupBox("Targets", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Areas", targetBox, PowerEnum::AREAS);
	newGroup.familyGroups.emplace_back("Creatures", targetBox, PowerEnum::CREATURES);
	newGroup.familyGroups.emplace_back("Objects", targetBox, PowerEnum::OBJECTS);
	newGroup.familyGroups.emplace_back("Corpses", targetBox, PowerEnum::CORPSES);
	newGroup.familyGroups.emplace_back("Multiple", targetBox, PowerEnum::MULTIPLE);
	newGroup.familyGroups.emplace_back("You", targetBox, PowerEnum::YOU);
	
	const auto targetLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		targetLayout->addWidget(foo.masterButton, count/3, count % 3);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	targetBox->setLayout(targetLayout);
	layout->addWidget(targetBox, 11, 0, 2, 3);
}

void QPowerDatabaseWindow::closeEvent(QCloseEvent* e)
{
	QWidget::parentWidget()->show();
	QMainWindow::closeEvent(e);
}

void QPowerDatabaseWindow::initialiseData(void)
{
	if (not QPowerDatabaseWindow::powerFile.open(QIODevice::ReadOnly | QIODevice::Text))
		std::exit(1);
	
	QPowerDatabaseWindow::powerFileStream.seek(0);
	auto line = 0u;
	
	while (not QPowerDatabaseWindow::powerFileStream.atEnd())
	{
		const auto name = QAbstractDatabaseWindow::ExtractString(QPowerDatabaseWindow::powerFile, '@');
		const auto bset = QAbstractDatabaseWindow::ExtractString(QPowerDatabaseWindow::powerFile, '@');
		
		const auto infoPos = QPowerDatabaseWindow::powerFile.pos();
		const auto info = QAbstractDatabaseWindow::ExtractString(QPowerDatabaseWindow::powerFile, '@');
		
		const auto lorePos = QPowerDatabaseWindow::powerFile.pos();
		const auto lore = QAbstractDatabaseWindow::ExtractString(QPowerDatabaseWindow::powerFile, '\n');
		
		QPowerDatabaseWindow::allPowers.emplace_back(name, bset, infoPos, lorePos);
		QPowerDatabaseWindow::nameToIndex[name] = line++;
	}
}

void QPowerDatabaseWindow::initialiseWidgets(void)
{
	QMainWindow::setWindowTitle("Dungeons & Dragons 3.5e Power Library");
	QMainWindow::resize(1700, 600);
	
	const auto layout = new QGridLayout();
	QFont font;
	font.setPixelSize(10);
	
	QPowerDatabaseWindow::initialiseClasses(font, layout);
	QPowerDatabaseWindow::initialiseDisciplines(font, layout);
	QPowerDatabaseWindow::initialiseSpecial(font, layout);
	QPowerDatabaseWindow::initialiseFeatures(font, layout);
	QPowerDatabaseWindow::initialiseSubdisciplines(font, layout);
	QPowerDatabaseWindow::initialiseDisplays(font, layout);
	QPowerDatabaseWindow::initialiseDescriptors(font, layout);
	QPowerDatabaseWindow::initialiseSources(font, layout);
	
	QPowerDatabaseWindow::initialiseLevels(font, layout);
	QPowerDatabaseWindow::initialiseRanges(font, layout);
	QPowerDatabaseWindow::initialiseAreas(font, layout);
	QPowerDatabaseWindow::initialiseManifestingTimes(font, layout);
	QPowerDatabaseWindow::initialiseEffects(font, layout);
	
	QPowerDatabaseWindow::initialiseDurations(font, layout);
	QPowerDatabaseWindow::initialiseControlButtons(font, layout);
	QPowerDatabaseWindow::initialiseTargets(font, layout);
	QPowerDatabaseWindow::initialiseSaves(font, layout);
	QPowerDatabaseWindow::initialisePowerResistances(font, layout);
	QPowerDatabaseWindow::initialiseEverythingElse(layout);
	
	QAbstractDatabaseWindow::mainWidget->setLayout(layout);
}

void QPowerDatabaseWindow::search(void)
{
	const auto fullPack = HexBitsetPack<Number>(QAbstractDatabaseWindow::buttonGroups);
	const auto nameSearch = QAbstractDatabaseWindow::nameLineEdit->text().toLower();
	const auto loreSearch = QAbstractDatabaseWindow::loreLineEdit->text().toLower();
	
	const auto& greenBitset = fullPack.getGreenBitset();
	const auto& redBitset = fullPack.getRedBitset();
	const auto& yellowBitsets = fullPack.getYellowBitsets();
	
	const auto checkGreen = not greenBitset.null();
	const auto checkRed = not redBitset.null();
	
	auto index = 0u;
	
	if (QAbstractDatabaseWindow::keepListButton->isChecked())
	{
		auto newSearchResults = std::vector<quint32>();
		
		for (const auto& u : QAbstractDatabaseWindow::searchResults)
		{
			const auto& file = QPowerDatabaseWindow::allPowers[u];
			const auto valid = QPowerDatabaseWindow::powerIsValid(file, greenBitset, redBitset, yellowBitsets, nameSearch, loreSearch, checkGreen, checkRed);
			
			if (valid)
				newSearchResults.push_back(index);
			
			++index;
		}
		
		QAbstractDatabaseWindow::searchResults.swap(newSearchResults);
	}
	else
	{
		QAbstractDatabaseWindow::searchResults.clear();
		
		for (const auto& file : QPowerDatabaseWindow::allPowers)
		{
			const auto valid = QPowerDatabaseWindow::powerIsValid(file, greenBitset, redBitset, yellowBitsets, nameSearch, loreSearch, checkGreen, checkRed);
			
			if (valid)
				QAbstractDatabaseWindow::searchResults.push_back(index);
			
			++index;
		}
	}
	
	QAbstractDatabaseWindow::resultList->clear();
	
	for (const auto& u : QPowerDatabaseWindow::searchResults)
	{
		const auto& file = QPowerDatabaseWindow::allPowers[u];
		const auto item = new QListWidgetItem(file.name);
		
		const auto foregroundColor = QPowerDatabaseWindow::Foreground(file.bits);
		item->setForeground(foregroundColor);
		
		QAbstractDatabaseWindow::resultList->addItem(item);
	}
	
	const auto size = QPowerDatabaseWindow::searchResults.size();
	const auto resultString = QString::number(size) + " result" + QString(size > 1u ? "s" : "") + ".";
	
	QAbstractDatabaseWindow::resultLabel->setText(resultString);
}

bool QPowerDatabaseWindow::powerIsValid(const HexFile<Number>& file, const HexBitset<Number>& greenBitset, const HexBitset<Number>& redBitset, const std::vector<HexBitset<Number>>& yellowBitsets, const QString& nameSearch, const QString& loreSearch, bool checkGreen, bool checkRed)
{
	if (checkGreen and not file.bits.all(greenBitset))
		return false;
	
	if (checkRed and not file.bits.none(redBitset))
		return false;
	
	for (const auto& yellowBitset : yellowBitsets)
	{
		if (not file.bits.any(yellowBitset))
			return false;
	}
	
	if (not nameSearch.isEmpty())
	{
		const auto theName = file.name.toLower();
		
		if (QAbstractDatabaseWindow::barNamesButton->isChecked() and theName.indexOf(nameSearch) >= 0)
			return false;
		
		if (not QAbstractDatabaseWindow::barNamesButton->isChecked() and theName.indexOf(nameSearch) < 0)
			return false;
	}
	
	if (not loreSearch.isEmpty())
	{
		QPowerDatabaseWindow::powerFileStream.seek(file.textPositionInFile);
		const auto theLore = QPowerDatabaseWindow::powerFileStream.readLine().toLower();
		
		if (QAbstractDatabaseWindow::barTextsButton->isChecked() and theLore.indexOf(loreSearch, Qt::CaseInsensitive) >= 0)
			return false;
		
		if (not QAbstractDatabaseWindow::barTextsButton->isChecked() and theLore.indexOf(loreSearch, Qt::CaseInsensitive) < 0)
			return false;
	}
	
	return true;
}

void QPowerDatabaseWindow::updateLore(quint32 index, QTextBrowser* browser)
{
	const auto& file = QPowerDatabaseWindow::allPowers[index];
	QPowerDatabaseWindow::powerFileStream.seek(file.infoPositionInFile);
	
	const auto info = QAbstractDatabaseWindow::ExtractString(QPowerDatabaseWindow::powerFile, '@');
	const auto infoList = info.split(';');
	
	if (infoList.size() != 15u)
		return;
	
	const auto lore = QPowerDatabaseWindow::powerFileStream.readLine();
	auto qText = "<b>" + file.name + "</b><br>" + infoList.at(0) + "<br>";
	
	if (not infoList.at(1).isEmpty())
		qText += "<b>Base Classes:</b> " + infoList.at(1) + "<br>";
	
	if (not infoList.at(2).isEmpty())
		qText += "<b>Prestige Classes:</b> " + infoList.at(2) + "<br>";
	
	if (not infoList.at(3).isEmpty())
		qText += "<b>Levels:</b> " + infoList.at(3) + "<br>";
	
	if (not infoList.at(4).isEmpty())
		qText += "<b>Mantles:</b> " + infoList.at(4) + "<br>";
	
	qText += "<b>Displays:</b> " + (infoList.at(5).isEmpty() ? "None" : infoList.at(5)) + "<br>";
	qText += "<b>Manifesting Time:</b> " + infoList.at(6) + "<br>";
	qText += "<b>Range:</b> " + infoList.at(7) + "<br>";
	
	if (not infoList.at(8).isEmpty())
		qText += "<b>Effect:</b> " + infoList.at(8) + "<br>";
	
	if (not infoList.at(9).isEmpty())
		qText += "<b>Target:</b> " + infoList.at(9) + "<br>";
	
	if (not infoList.at(10).isEmpty())
		qText += "<b>Area:</b> " + infoList.at(10) + "<br>";
	
	qText += "<b>Duration:</b> " + infoList.at(11) + "<br>";
	
	if (not infoList.at(12).isEmpty())
		qText += "<b>Saving Throw:</b> " + infoList.at(12) + "<br>";
	
	if (not infoList.at(13).isEmpty())
		qText += "<b>Power Resistance:</b> " + infoList.at(13) + "<br>";
	
	qText += "<b>Source:</b> " + infoList.back();
	qText += QAbstractDatabaseWindow::Process(lore, QAbstractDatabaseWindow::loreLineEdit->text().toLower());
	
	browser->setHtml(qText);
}

#endif
