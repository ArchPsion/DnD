#ifndef __Q_SPELL_DATABASE_INTERFACE_HPP__
#define __Q_SPELL_DATABASE_INTERFACE_HPP__

// Qt Libraries
#include <QGroupBox>
#include <QShortcut>

// Custom Libraries
#include "HexBitsetPack.hpp"
#include "QAbstractDatabaseWindow.hpp"

class QSpellDatabaseWindow : public QAbstractDatabaseWindow
{
	private:
	
		static constexpr QColor				RevisedColor = QColor(255, 255, 255);
		static constexpr QColor				UnrevisedColor = QColor(203, 203, 203);

		static constexpr QColor				AbjurationColor = QColor(20, 205, 113);
		static constexpr QColor				ConjurationColor = QColor(255, 102, 102);
		static constexpr QColor				DivinationColor = QColor(255, 153, 51);
		static constexpr QColor				EnchantmentColor = QColor(255, 153, 255);
		static constexpr QColor				EvocationColor = QColor(102, 178, 255);
		static constexpr QColor				IllusionColor = QColor(217, 173, 0);
		static constexpr QColor				NecromancyColor = QColor(197, 135, 135);
		static constexpr QColor				TransmutationColor = QColor(204, 153, 255);
		static constexpr QColor				UniversalColor = QColor(128, 128, 128);
		
		static constexpr quint32			Number = static_cast<quint32>(SpellEnum::SIZE);
		static HexBitset<Number>			RevisedBitset;
		
		inline static QColor				Background(const HexBitset<Number>&);
		inline static QColor				Foreground(const HexBitset<Number>&);
		
		std::vector<HexFile<Number>>			allSpells;
		QFile						spellFile;
		QTextStream					spellFileStream;
		
		inline void					initialiseAreas(const QFont&, QGridLayout*);
		inline void					initialiseCastingTimes(const QFont&, QGridLayout*);
		inline void					initialiseClasses(const QFont&, QGridLayout*);
		inline void					initialiseControlButtons(const QFont&, QGridLayout*);
		inline void					initialiseData(void);
		inline void					initialiseDescriptors(const QFont&, QGridLayout*);
		inline void					initialiseDurations(const QFont&, QGridLayout*);
		inline void					initialiseEffects(const QFont&, QGridLayout*);
		inline void					initialiseEverythingElse(const QFont&, QGridLayout*);
		inline void					initialiseLevels(const QFont&, QGridLayout*);
		inline void					initialiseMaterials(const QFont&, QGridLayout*);
		inline void					initialiseRanges(const QFont&, QGridLayout*);
		inline void					initialiseSaves(const QFont&, QGridLayout*);
		inline void					initialiseSchools(const QFont&, QGridLayout*);
		inline void					initialiseSources(const QFont&, QGridLayout*);
		inline void					initialiseSpecial(const QFont&, QGridLayout*);
		inline void					initialiseSpellResistances(const QFont&, QGridLayout*);
		inline void					initialiseSubschools(const QFont&, QGridLayout*);
		inline void					initialiseTargets(const QFont&, QGridLayout*);
		inline void					initialiseTypes(const QFont&, QGridLayout*);
		inline void					initialiseWidgets(void);
		inline void					initialiseWindow(const HexFamily&, const QFont&, qint32);
		inline bool					spellIsValid(const HexFile<Number>&, const HexBitset<Number>&, const HexBitset<Number>&, const std::vector<HexBitset<Number>>&, const QString&, const QString&, bool, bool);
		
	protected slots:
	
		inline void					search(void) final;
	
	protected:
	
		inline void					closeEvent(QCloseEvent*);
		inline void					updateLore(quint32, QTextBrowser*) final;
	
	public:
	
		inline						QSpellDatabaseWindow(QWidget*);
};

QSpellDatabaseWindow::QSpellDatabaseWindow(QWidget* foo) :
	QAbstractDatabaseWindow(foo, "spell"),
	spellFile("files/spells.txt"),
	spellFileStream(&spellFile)
{
	QSpellDatabaseWindow::initialiseData();
	QSpellDatabaseWindow::initialiseWidgets();
	
	const auto s1 = new QShortcut(QAbstractDatabaseWindow::mainWidget);
	s1->setKeys({ QKeySequence(Qt::Key_Return), QKeySequence(Qt::Key_Enter) });
	
	QObject::connect(s1, SIGNAL(activated(void)), this, SLOT(search(void)));
}

QColor QSpellDatabaseWindow::Foreground(const HexBitset<Number>& b)
{
	if (b.testBit(SpellEnum::ABJURATION))
		return QSpellDatabaseWindow::AbjurationColor;
	
	if (b.testBit(SpellEnum::CONJURATION))
		return QSpellDatabaseWindow::ConjurationColor;
	
	if (b.testBit(SpellEnum::DIVINATION))
		return QSpellDatabaseWindow::DivinationColor;
	
	if (b.testBit(SpellEnum::ENCHANTMENT))
		return QSpellDatabaseWindow::EnchantmentColor;
	
	if (b.testBit(SpellEnum::EVOCATION))
		return QSpellDatabaseWindow::EvocationColor;
	
	if (b.testBit(SpellEnum::ILLUSION))
		return QSpellDatabaseWindow::IllusionColor;
	
	if (b.testBit(SpellEnum::NECROMANCY))
		return QSpellDatabaseWindow::NecromancyColor;
	
	if (b.testBit(SpellEnum::TRANSMUTATION))
		return QSpellDatabaseWindow::TransmutationColor;
	
	if (b.testBit(SpellEnum::UNIVERSAL))
		return QSpellDatabaseWindow::UniversalColor;
	
	return QColor(0, 0, 0);
}

void QSpellDatabaseWindow::initialiseAreas(const QFont& font, QGridLayout* layout)
{
	const auto areaBox = new QGroupBox("Areas", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(10u);
	
	newGroup.familyGroups.emplace_back("Circle", areaBox, SpellEnum::CIRCLE);
	newGroup.familyGroups.emplace_back("Cone", areaBox, SpellEnum::CONE);
	newGroup.familyGroups.emplace_back("Cylinder", areaBox, SpellEnum::CYLINDER);
	newGroup.familyGroups.emplace_back("Line", areaBox, SpellEnum::LINE);
	newGroup.familyGroups.emplace_back("Plane", areaBox, SpellEnum::PLANE);
	newGroup.familyGroups.emplace_back("Sphere", areaBox, SpellEnum::SPHERE);
	newGroup.familyGroups.emplace_back("Shapeable", areaBox, SpellEnum::SHAPEABLE);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", areaBox);
	otherGroup.familyGroups.emplace_back("Cube", areaBox, SpellEnum::CUBE);
	otherGroup.familyGroups.emplace_back("Square", areaBox, SpellEnum::SQUARE);
	otherGroup.familyGroups.emplace_back("Peculiar", areaBox, SpellEnum::PECULIAR_AREA);
	
	newGroup.familyGroups.emplace_back("Centered", areaBox, SpellEnum::CENTERED);
	
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
	layout->addWidget(areaBox, 8, 5, 2, 5);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 3);
}

void QSpellDatabaseWindow::initialiseCastingTimes(const QFont& font, QGridLayout* layout)
{
	const auto castingTimeBox = new QGroupBox("Casting Times", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Immediate", castingTimeBox, SpellEnum::IMMEDIATE);
	newGroup.familyGroups.emplace_back("Swift", castingTimeBox, SpellEnum::SWIFT);
	newGroup.familyGroups.emplace_back("Move", castingTimeBox, SpellEnum::MOVE);
	newGroup.familyGroups.emplace_back("Standard", castingTimeBox, SpellEnum::STANDARD);
	newGroup.familyGroups.emplace_back("1 round", castingTimeBox, SpellEnum::ONE_ROUND);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", castingTimeBox);
	otherGroup.familyGroups.emplace_back("2+ rounds", castingTimeBox, SpellEnum::TWO_ROUNDS);
	otherGroup.familyGroups.emplace_back("1+ minute", castingTimeBox, SpellEnum::ONE_MINUTE);
	otherGroup.familyGroups.emplace_back("10+ minutes", castingTimeBox, SpellEnum::TEN_MINUTES);
	otherGroup.familyGroups.emplace_back("1+ hour", castingTimeBox, SpellEnum::ONE_HOUR);
	otherGroup.familyGroups.emplace_back("1+ day", castingTimeBox, SpellEnum::ONE_DAY);
	otherGroup.familyGroups.emplace_back("See text", castingTimeBox, SpellEnum::TIME_SEE_TEXT);
	otherGroup.familyGroups.emplace_back("Peculiar", castingTimeBox, SpellEnum::PECULIAR_TIME);
	
	const auto castingTimeLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		castingTimeLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	castingTimeBox->setLayout(castingTimeLayout);
	layout->addWidget(castingTimeBox, 10, 0, 1, 6);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 4);
}

void QSpellDatabaseWindow::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Core Classes", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Bard", classBox, SpellEnum::BARD);
	newGroup.familyGroups.emplace_back("Cleric", classBox, SpellEnum::CLERIC);
	newGroup.familyGroups.emplace_back("Druid", classBox, SpellEnum::DRUID);
	newGroup.familyGroups.emplace_back("Paladin", classBox, SpellEnum::PALADIN);
	newGroup.familyGroups.emplace_back("Ranger", classBox, SpellEnum::RANGER);
	newGroup.familyGroups.emplace_back("Sorcerer", classBox, SpellEnum::SORCERER);
	newGroup.familyGroups.emplace_back("Wizard", classBox, SpellEnum::WIZARD);
	
	const auto classLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		classLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	classBox->setLayout(classLayout);
	layout->addWidget(classBox, 0, 0, 1, 7);
}

void QSpellDatabaseWindow::initialiseControlButtons(const QFont& font, QGridLayout* layout)
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
	layout->addWidget(filterControlBox, 11, 8, 2, 2);
}

void QSpellDatabaseWindow::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Acid", descriptorBox, SpellEnum::ACID);
	newGroup.familyGroups.emplace_back("Air", descriptorBox, SpellEnum::AIR);
	newGroup.familyGroups.emplace_back("Chaotic", descriptorBox, SpellEnum::CHAOTIC);
	newGroup.familyGroups.emplace_back("Cold", descriptorBox, SpellEnum::COLD);
	newGroup.familyGroups.emplace_back("Darkness", descriptorBox, SpellEnum::DARKNESS);
	newGroup.familyGroups.emplace_back("Death", descriptorBox, SpellEnum::DEATH);
	newGroup.familyGroups.emplace_back("Earth", descriptorBox, SpellEnum::EARTH);
	newGroup.familyGroups.emplace_back("Electricity", descriptorBox, SpellEnum::ELECTRICITY);
	newGroup.familyGroups.emplace_back("Evil", descriptorBox, SpellEnum::EVIL);
	newGroup.familyGroups.emplace_back("Fear", descriptorBox, SpellEnum::FEAR);
	newGroup.familyGroups.emplace_back("Fire", descriptorBox, SpellEnum::FIRE);
	newGroup.familyGroups.emplace_back("Force", descriptorBox, SpellEnum::FORCE);
	newGroup.familyGroups.emplace_back("Good", descriptorBox, SpellEnum::GOOD);
	newGroup.familyGroups.emplace_back("Incarnum", descriptorBox, SpellEnum::INCARNUM);
	newGroup.familyGroups.emplace_back("Language", descriptorBox, SpellEnum::LANGUAGE_DEPENDENT);
	newGroup.familyGroups.emplace_back("Lawful", descriptorBox, SpellEnum::LAWFUL);
	newGroup.familyGroups.emplace_back("Light", descriptorBox, SpellEnum::LIGHT);
	newGroup.familyGroups.emplace_back("Mind-Affecting", descriptorBox, SpellEnum::MIND_AFFECTING);
	newGroup.familyGroups.emplace_back("Sonic", descriptorBox, SpellEnum::SONIC);
	newGroup.familyGroups.emplace_back("Water", descriptorBox, SpellEnum::WATER);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", descriptorBox);
	otherGroup.familyGroups.emplace_back("Investiture", descriptorBox, SpellEnum::INVESTITURE);
	otherGroup.familyGroups.emplace_back("Mindset", descriptorBox, SpellEnum::MINDSET);
	
	const auto descriptorLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		descriptorLayout->addWidget(foo.masterButton, count/7, count % 7);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	descriptorBox->setLayout(descriptorLayout);
	layout->addWidget(descriptorBox, 4, 2, 3, 7);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 2);
}

void QSpellDatabaseWindow::initialiseDurations(const QFont& font, QGridLayout* layout)
{
	const auto durationBox = new QGroupBox("Durations", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(20u);
	
	newGroup.familyGroups.emplace_back("Instantaneous", durationBox, SpellEnum::INSTANTANEOUS);
	newGroup.familyGroups.emplace_back("1 round/2+ levels", durationBox, SpellEnum::ONE_ROUND_TWO_LEVELS);
	newGroup.familyGroups.emplace_back("1+ round/level", durationBox, SpellEnum::ONE_ROUND_LEVEL);
	newGroup.familyGroups.emplace_back("1+ minute/level", durationBox, SpellEnum::ONE_MINUTE_LEVEL);
	newGroup.familyGroups.emplace_back("10+ minutes/level", durationBox, SpellEnum::TEN_MINUTES_LEVEL);
	newGroup.familyGroups.emplace_back("1+ hour/level", durationBox, SpellEnum::ONE_HOUR_LEVEL);
	newGroup.familyGroups.emplace_back("1+ day/level", durationBox, SpellEnum::ONE_DAY_LEVEL);
	
	auto& fixedGroup = newGroup.familyGroups.emplace_back("Fixed", durationBox);
	fixedGroup.familyGroups.emplace_back("1+ round", durationBox, SpellEnum::FIXED_ONE_ROUND);
	fixedGroup.familyGroups.emplace_back("1+ minute", durationBox, SpellEnum::FIXED_ONE_MINUTE);
	fixedGroup.familyGroups.emplace_back("10+ minutes", durationBox, SpellEnum::FIXED_TEN_MINUTES);
	fixedGroup.familyGroups.emplace_back("1+ hour", durationBox, SpellEnum::FIXED_ONE_HOUR);
	fixedGroup.familyGroups.emplace_back("1+ day", durationBox, SpellEnum::FIXED_ONE_DAY);
	fixedGroup.familyGroups.emplace_back("1+ month", durationBox, SpellEnum::FIXED_ONE_MONTH);
	fixedGroup.familyGroups.emplace_back("1+ year", durationBox, SpellEnum::FIXED_ONE_YEAR);
	
	newGroup.familyGroups.emplace_back("Concentration", durationBox, SpellEnum::CONCENTRATION);
	newGroup.familyGroups.emplace_back("Permanent", durationBox, SpellEnum::PERMANENT);
	newGroup.familyGroups.emplace_back("See text", durationBox, SpellEnum::DURATION_SEE_TEXT);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", durationBox);
	otherGroup.familyGroups.emplace_back("Dice", durationBox, SpellEnum::DICE_DURATION);
	otherGroup.familyGroups.emplace_back("Peculiar", durationBox, SpellEnum::PECULIAR_DURATION);
	
	newGroup.familyGroups.emplace_back("Then", durationBox, SpellEnum::THEN_DURATION);
	newGroup.familyGroups.emplace_back("Dismiss", durationBox, SpellEnum::DISMISS);
	newGroup.familyGroups.emplace_back("Discharge", durationBox, SpellEnum::DISCHARGE);
	newGroup.familyGroups.emplace_back("Trigger", durationBox, SpellEnum::TRIGGER);
	
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
	layout->addWidget(durationBox, 11, 0, 2, 8);
	
	QAbstractDatabaseWindow::initialiseWindow(fixedGroup, font, 4);
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 2);
}

void QSpellDatabaseWindow::initialiseEffects(const QFont& font, QGridLayout* layout)
{
	const auto effectBox = new QGroupBox("Effects", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Burst", effectBox, SpellEnum::BURST);
	newGroup.familyGroups.emplace_back("Emanation", effectBox, SpellEnum::EMANATION);
	newGroup.familyGroups.emplace_back("Ray", effectBox, SpellEnum::RAY);
	newGroup.familyGroups.emplace_back("Spread", effectBox, SpellEnum::SPREAD);
	
	const auto effectLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		effectLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	effectBox->setLayout(effectLayout);
	layout->addWidget(effectBox, 10, 6, 1, 4);
}

void QSpellDatabaseWindow::initialiseEverythingElse(const QFont& font, QGridLayout* layout)
{
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back("3.5e", QAbstractDatabaseWindow::mainWidget);
	
	newGroup.masterButton->setObjectName("B");
	newGroup.masterButton->setFont(font);
	
	newGroup.familyGroups.emplace_back(SpellEnum::ANAUROCH_EMPIRE_OF_SHADE);
	newGroup.familyGroups.emplace_back(SpellEnum::CHAMPIONS_OF_RUIN);
	newGroup.familyGroups.emplace_back(SpellEnum::CHAMPIONS_OF_VALOR);
	newGroup.familyGroups.emplace_back(SpellEnum::CITY_OF_SPLENDORS_WATERDEEP);
	newGroup.familyGroups.emplace_back(SpellEnum::CITY_OF_STORMREACH);
	newGroup.familyGroups.emplace_back(SpellEnum::CITYSCAPE);
	newGroup.familyGroups.emplace_back(SpellEnum::COMPLETE_CHAMPION);
	newGroup.familyGroups.emplace_back(SpellEnum::COMPLETE_MAGE);
	newGroup.familyGroups.emplace_back(SpellEnum::COMPLETE_SCOUNDREL);
	newGroup.familyGroups.emplace_back(SpellEnum::DRAGON_MAGIC);
	newGroup.familyGroups.emplace_back(SpellEnum::DRAGONMARKED);
	newGroup.familyGroups.emplace_back(SpellEnum::DRAGONS_OF_EBERRON);
	newGroup.familyGroups.emplace_back(SpellEnum::DRAGONS_OF_FAERUN);
	newGroup.familyGroups.emplace_back(SpellEnum::DROW_OF_THE_UNDERDARK);
	newGroup.familyGroups.emplace_back(SpellEnum::EXPEDITION_TO_CASTLE_RAVENLOFT);
	newGroup.familyGroups.emplace_back(SpellEnum::EXPEDITION_TO_DEMONWEB_PITS);
	newGroup.familyGroups.emplace_back(SpellEnum::EXPEDITION_TO_UNDERMOUNTAIN);
	newGroup.familyGroups.emplace_back(SpellEnum::FAITHS_OF_EBERRON);
	newGroup.familyGroups.emplace_back(SpellEnum::FIENDISH_CODEX_I);
	newGroup.familyGroups.emplace_back(SpellEnum::FIENDISH_CODEX_II);
	newGroup.familyGroups.emplace_back(SpellEnum::FIVE_NATIONS);
	newGroup.familyGroups.emplace_back(SpellEnum::FORGE_OF_WAR);
	newGroup.familyGroups.emplace_back(SpellEnum::HEROES_OF_BATTLE);
	newGroup.familyGroups.emplace_back(SpellEnum::HEROES_OF_HORROR);
	newGroup.familyGroups.emplace_back(SpellEnum::LORDS_OF_MADNESS);
	newGroup.familyGroups.emplace_back(SpellEnum::MAGIC_OF_EBERRON);
	newGroup.familyGroups.emplace_back(SpellEnum::MONSTER_MANUAL_IV);
	newGroup.familyGroups.emplace_back(SpellEnum::MAGIC_OF_INCARNUM);
	newGroup.familyGroups.emplace_back(SpellEnum::PLAYERS_GUIDE_TO_EBERRON);
	newGroup.familyGroups.emplace_back(SpellEnum::PLAYERS_HANDBOOK);
	newGroup.familyGroups.emplace_back(SpellEnum::PLAYERS_HANDBOOK_II);
	newGroup.familyGroups.emplace_back(SpellEnum::POWER_OF_FAERUN);
	newGroup.familyGroups.emplace_back(SpellEnum::RACES_OF_EBERRON);
	newGroup.familyGroups.emplace_back(SpellEnum::RACES_OF_THE_DRAGON);
	newGroup.familyGroups.emplace_back(SpellEnum::SANDSTORM);
	newGroup.familyGroups.emplace_back(SpellEnum::SECRETS_OF_SARLONA);
	newGroup.familyGroups.emplace_back(SpellEnum::SECRETS_OF_XENDRIK);
	newGroup.familyGroups.emplace_back(SpellEnum::SPELL_COMPENDIUM);
	newGroup.familyGroups.emplace_back(SpellEnum::STORMWRACK);
	newGroup.familyGroups.emplace_back(SpellEnum::WEAPONS_OF_LEGACY);
	newGroup.familyGroups.emplace_back(SpellEnum::WEB35);
	
	layout->addWidget(QAbstractDatabaseWindow::nameLineEdit, 15, 0, 1, 4);
	layout->addWidget(QAbstractDatabaseWindow::loreLineEdit, 15, 4, 1, 5);
	layout->addWidget(newGroup.masterButton, 15, 9, 1, 1);
	
	layout->addWidget(QAbstractDatabaseWindow::resultList, 0, 10, 16, 7);
	layout->addWidget(QAbstractDatabaseWindow::loreBrowser, 0, 17, 15, 10);
	layout->addWidget(QAbstractDatabaseWindow::resultLabel, 15, 17, 1, 10);
	
	QObject::connect(newGroup.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	for (const auto& fml : newGroup.familyGroups)
		QSpellDatabaseWindow::RevisedBitset.setBit(fml.bit);
}

void QSpellDatabaseWindow::initialiseLevels(const QFont& font, QGridLayout* layout)
{
	const auto levelBox = new QGroupBox("Levels", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("0", levelBox, SpellEnum::LEVEL_0);
	newGroup.familyGroups.emplace_back("1", levelBox, SpellEnum::LEVEL_1);
	newGroup.familyGroups.emplace_back("2", levelBox, SpellEnum::LEVEL_2);
	newGroup.familyGroups.emplace_back("3", levelBox, SpellEnum::LEVEL_3);
	newGroup.familyGroups.emplace_back("4", levelBox, SpellEnum::LEVEL_4);
	newGroup.familyGroups.emplace_back("5", levelBox, SpellEnum::LEVEL_5);
	newGroup.familyGroups.emplace_back("6", levelBox, SpellEnum::LEVEL_6);
	newGroup.familyGroups.emplace_back("7", levelBox, SpellEnum::LEVEL_7);
	newGroup.familyGroups.emplace_back("8", levelBox, SpellEnum::LEVEL_8);
	newGroup.familyGroups.emplace_back("9", levelBox, SpellEnum::LEVEL_9);
	
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

void QSpellDatabaseWindow::initialiseMaterials(const QFont& font, QGridLayout* layout)
{
	const auto materialBox = new QGroupBox("Materials", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Focus", materialBox, SpellEnum::FOCUS);
	newGroup.familyGroups.emplace_back("Divine Focus", materialBox, SpellEnum::DIVINE_FOCUS);
	newGroup.familyGroups.emplace_back("Verbal", materialBox, SpellEnum::VERBAL);
	newGroup.familyGroups.emplace_back("Somatic", materialBox, SpellEnum::SOMATIC);
	newGroup.familyGroups.emplace_back("Material", materialBox, SpellEnum::MATERIAL);
	newGroup.familyGroups.emplace_back("Gold", materialBox, SpellEnum::GOLD);
	newGroup.familyGroups.emplace_back("Experience", materialBox, SpellEnum::EXPERIENCE);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", materialBox);
	otherGroup.familyGroups.emplace_back("Alignment", materialBox, SpellEnum::ALIGNMENT);
	otherGroup.familyGroups.emplace_back("Corruption", materialBox, SpellEnum::CORRUPT);
	otherGroup.familyGroups.emplace_back("Dragonmark", materialBox, SpellEnum::DRAGONMARK);
	otherGroup.familyGroups.emplace_back("Essentia", materialBox, SpellEnum::ESSENTIA);
	otherGroup.familyGroups.emplace_back("Racial", materialBox, SpellEnum::RACIAL);
	otherGroup.familyGroups.emplace_back("Sacrifice", materialBox, SpellEnum::SANCTIFIED);
	otherGroup.familyGroups.emplace_back("Verbal (Bard only)", materialBox, SpellEnum::VERBAL_BARD);
	
	const auto materialLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		materialLayout->addWidget(foo.masterButton, count/2, count % 2);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	materialBox->setLayout(materialLayout);
	layout->addWidget(materialBox, 3, 0, 4, 2);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 4);
}

void QSpellDatabaseWindow::initialiseRanges(const QFont& font, QGridLayout* layout)
{
	const auto rangeBox = new QGroupBox("Ranges", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(10u);
	
	newGroup.familyGroups.emplace_back("Personal", rangeBox, SpellEnum::PERSONAL);
	newGroup.familyGroups.emplace_back("Touch", rangeBox, SpellEnum::TOUCH);
	newGroup.familyGroups.emplace_back("Close", rangeBox, SpellEnum::CLOSE);
	newGroup.familyGroups.emplace_back("Medium", rangeBox, SpellEnum::MEDIUM);
	newGroup.familyGroups.emplace_back("Long", rangeBox, SpellEnum::LONG);
	
	auto& fixedGroup = newGroup.familyGroups.emplace_back("Fixed", rangeBox);
	fixedGroup.familyGroups.emplace_back("0 foot", rangeBox, SpellEnum::FIXED_0_FOOT);
	fixedGroup.familyGroups.emplace_back("15+ feet", rangeBox, SpellEnum::FIXED_15_FEET);
	fixedGroup.familyGroups.emplace_back("30+ feet", rangeBox, SpellEnum::FIXED_30_FEET);
	fixedGroup.familyGroups.emplace_back("60+ feet", rangeBox, SpellEnum::FIXED_60_FEET);
	fixedGroup.familyGroups.emplace_back("120+ feet", rangeBox, SpellEnum::FIXED_120_FEET);
	fixedGroup.familyGroups.emplace_back("1+ mile", rangeBox, SpellEnum::FIXED_1_MILE);
	
	newGroup.familyGroups.emplace_back("Unlimited", rangeBox, SpellEnum::UNLIMITED);
	newGroup.familyGroups.emplace_back("Boundless", rangeBox, SpellEnum::BOUNDLESS);
	newGroup.familyGroups.emplace_back("See text", rangeBox, SpellEnum::RANGE_SEE_TEXT);
	newGroup.familyGroups.emplace_back("Peculiar", rangeBox, SpellEnum::PECULIAR_RANGE);
	
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
	layout->addWidget(rangeBox, 8, 0, 2, 5);
	
	QAbstractDatabaseWindow::initialiseWindow(fixedGroup, font, 4);
}

void QSpellDatabaseWindow::initialiseSaves(const QFont& font, QGridLayout* layout)
{
	const auto saveBox = new QGroupBox("Saves", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Fortitude", saveBox, SpellEnum::FORTITUDE);
	newGroup.familyGroups.emplace_back("Reflex", saveBox, SpellEnum::REFLEX);
	newGroup.familyGroups.emplace_back("Will", saveBox, SpellEnum::WILL);
	newGroup.familyGroups.emplace_back("Object", saveBox, SpellEnum::SAVE_OBJECT);
	newGroup.familyGroups.emplace_back("Negate", saveBox, SpellEnum::NEGATE);
	newGroup.familyGroups.emplace_back("Partial", saveBox, SpellEnum::PARTIAL);
	newGroup.familyGroups.emplace_back("Half", saveBox, SpellEnum::HALF);
	newGroup.familyGroups.emplace_back("Disbelief", saveBox, SpellEnum::DISBELIEF);
	newGroup.familyGroups.emplace_back("Harmless", saveBox, SpellEnum::SAVE_HARMLESS);
	newGroup.familyGroups.emplace_back("See text", saveBox, SpellEnum::SAVE_SEE_TEXT);
	
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
	layout->addWidget(saveBox, 13, 3, 2, 5);
}

void QSpellDatabaseWindow::initialiseSchools(const QFont& font, QGridLayout* layout)
{
	const auto schoolBox = new QGroupBox("Schools", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Abjuration", schoolBox, SpellEnum::ABJURATION);
	newGroup.familyGroups.emplace_back("Conjuration", schoolBox, SpellEnum::CONJURATION);
	newGroup.familyGroups.emplace_back("Divination", schoolBox, SpellEnum::DIVINATION);
	newGroup.familyGroups.emplace_back("Enchantment", schoolBox, SpellEnum::ENCHANTMENT);
	newGroup.familyGroups.emplace_back("Evocation", schoolBox, SpellEnum::EVOCATION);
	newGroup.familyGroups.emplace_back("Illusion", schoolBox, SpellEnum::ILLUSION);
	newGroup.familyGroups.emplace_back("Necromancy", schoolBox, SpellEnum::NECROMANCY);
	newGroup.familyGroups.emplace_back("Transmutation", schoolBox, SpellEnum::TRANSMUTATION);
	newGroup.familyGroups.emplace_back("Universal", schoolBox, SpellEnum::UNIVERSAL);
	
	const auto schoolLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		schoolLayout->addWidget(foo.masterButton, count/3, count % 3);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	schoolBox->setLayout(schoolLayout);
	layout->addWidget(schoolBox, 1, 2, 3, 3);
}

void QSpellDatabaseWindow::initialiseSources(const QFont& font, QGridLayout* layout)
{
	const auto sourceBox = new QGroupBox("Sources", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("PHB", sourceBox, SpellEnum::PLAYERS_HANDBOOK);
	newGroup.familyGroups.emplace_back("SpC", sourceBox, SpellEnum::SPELL_COMPENDIUM);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", sourceBox);
	otherGroup.familyGroups.emplace_back("An", sourceBox, SpellEnum::ANAUROCH_EMPIRE_OF_SHADE);
	otherGroup.familyGroups.emplace_back("CCha", sourceBox, SpellEnum::COMPLETE_CHAMPION);
	otherGroup.familyGroups.emplace_back("Ci", sourceBox, SpellEnum::CITYSCAPE),
	otherGroup.familyGroups.emplace_back("CMge", sourceBox, SpellEnum::COMPLETE_MAGE);
	otherGroup.familyGroups.emplace_back("CoS", sourceBox, SpellEnum::CITY_OF_STORMREACH);
	otherGroup.familyGroups.emplace_back("CoV", sourceBox, SpellEnum::CHAMPIONS_OF_VALOR);
	otherGroup.familyGroups.emplace_back("CR", sourceBox, SpellEnum::CHAMPIONS_OF_RUIN);
	otherGroup.familyGroups.emplace_back("CSco", sourceBox, SpellEnum::COMPLETE_SCOUNDREL);
	otherGroup.familyGroups.emplace_back("CSW", sourceBox, SpellEnum::CITY_OF_SPLENDORS_WATERDEEP);
	otherGroup.familyGroups.emplace_back("DoE", sourceBox, SpellEnum::DRAGONS_OF_EBERRON);
	otherGroup.familyGroups.emplace_back("DoF", sourceBox, SpellEnum::DRAGONS_OF_FAERUN);
	otherGroup.familyGroups.emplace_back("Dmkd", sourceBox, SpellEnum::DRAGONMARKED);
	otherGroup.familyGroups.emplace_back("DrM", sourceBox, SpellEnum::DRAGON_MAGIC);
	otherGroup.familyGroups.emplace_back("DrU", sourceBox, SpellEnum::DROW_OF_THE_UNDERDARK);
	otherGroup.familyGroups.emplace_back("EDP", sourceBox, SpellEnum::EXPEDITION_TO_DEMONWEB_PITS);
	otherGroup.familyGroups.emplace_back("EU", sourceBox, SpellEnum::EXPEDITION_TO_UNDERMOUNTAIN);
	otherGroup.familyGroups.emplace_back("FoE", sourceBox, SpellEnum::FAITHS_OF_EBERRON);
	otherGroup.familyGroups.emplace_back("FC1", sourceBox, SpellEnum::FIENDISH_CODEX_I);
	otherGroup.familyGroups.emplace_back("FC2", sourceBox, SpellEnum::FIENDISH_CODEX_II);
	otherGroup.familyGroups.emplace_back("FN", sourceBox, SpellEnum::FIVE_NATIONS);
	otherGroup.familyGroups.emplace_back("FW", sourceBox, SpellEnum::FORGE_OF_WAR);
	otherGroup.familyGroups.emplace_back("HB", sourceBox, SpellEnum::HEROES_OF_BATTLE);
	otherGroup.familyGroups.emplace_back("HH", sourceBox, SpellEnum::HEROES_OF_HORROR);
	otherGroup.familyGroups.emplace_back("LoM", sourceBox, SpellEnum::LORDS_OF_MADNESS);
	otherGroup.familyGroups.emplace_back("MM4", sourceBox, SpellEnum::MONSTER_MANUAL_IV);
	otherGroup.familyGroups.emplace_back("MoE", sourceBox, SpellEnum::MAGIC_OF_EBERRON);
	otherGroup.familyGroups.emplace_back("MoI", sourceBox, SpellEnum::MAGIC_OF_INCARNUM);
	otherGroup.familyGroups.emplace_back("PGE", sourceBox, SpellEnum::PLAYERS_GUIDE_TO_EBERRON);
	otherGroup.familyGroups.emplace_back("PH2", sourceBox, SpellEnum::PLAYERS_HANDBOOK_II);
	otherGroup.familyGroups.emplace_back("PoF", sourceBox, SpellEnum::POWER_OF_FAERUN);
	otherGroup.familyGroups.emplace_back("Rav", sourceBox, SpellEnum::EXPEDITION_TO_CASTLE_RAVENLOFT);
	otherGroup.familyGroups.emplace_back("RDr", sourceBox, SpellEnum::RACES_OF_THE_DRAGON);
	otherGroup.familyGroups.emplace_back("RE", sourceBox, SpellEnum::RACES_OF_EBERRON);
	otherGroup.familyGroups.emplace_back("Sa", sourceBox, SpellEnum::SANDSTORM);
	otherGroup.familyGroups.emplace_back("SoS", sourceBox, SpellEnum::SECRETS_OF_SARLONA);
	otherGroup.familyGroups.emplace_back("SoX", sourceBox, SpellEnum::SECRETS_OF_XENDRIK);
	otherGroup.familyGroups.emplace_back("Sto", sourceBox, SpellEnum::STORMWRACK);
	otherGroup.familyGroups.emplace_back("WL", sourceBox, SpellEnum::WEAPONS_OF_LEGACY);
	
	const auto sourceLayout = new QVBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		sourceLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	sourceBox->setLayout(sourceLayout);
	layout->addWidget(sourceBox, 4, 9, 3, 1);
	
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 4);
}

void QSpellDatabaseWindow::initialiseSpecial(const QFont& font, QGridLayout* layout)
{
	const auto specialBox = new QGroupBox("Special", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(5u);
	
	auto& baseClassGroup = newGroup.familyGroups.emplace_back("Base Classes", specialBox);
	baseClassGroup.familyGroups.emplace_back("Adept", specialBox, SpellEnum::ADEPT);
	baseClassGroup.familyGroups.emplace_back("Artificer", specialBox, SpellEnum::ARTIFICER);
	baseClassGroup.familyGroups.emplace_back("Beguiler", specialBox, SpellEnum::BEGUILER);
	baseClassGroup.familyGroups.emplace_back("Death Delver", specialBox, SpellEnum::DEATH_DELVER);
	baseClassGroup.familyGroups.emplace_back("Dread Necromancer", specialBox, SpellEnum::DREAD_NECROMANCER);
	baseClassGroup.familyGroups.emplace_back("Duskblade", specialBox, SpellEnum::DUSKBLADE);
	baseClassGroup.familyGroups.emplace_back("Healer", specialBox, SpellEnum::HEALER);
	baseClassGroup.familyGroups.emplace_back("Hexblade", specialBox, SpellEnum::HEXBLADE);
	baseClassGroup.familyGroups.emplace_back("Shugenja", specialBox, SpellEnum::SHUGENJA);
	baseClassGroup.familyGroups.emplace_back("Wu Jen", specialBox, SpellEnum::WU_JEN);
	
	auto& prestigeClassGroup = newGroup.familyGroups.emplace_back("Prestige Classes", specialBox);
	prestigeClassGroup.familyGroups.emplace_back("Assassin", specialBox, SpellEnum::ASSASSIN);
	prestigeClassGroup.familyGroups.emplace_back("Blackguard", specialBox, SpellEnum::BLACKGUARD);
	
	auto& domainGroup = newGroup.familyGroups.emplace_back("Domains", specialBox);
	domainGroup.familyGroups.emplace_back("Air", specialBox, SpellEnum::AIR_DOMAIN);
	domainGroup.familyGroups.emplace_back("Abyss", specialBox, SpellEnum::ABYSS_DOMAIN);
	domainGroup.familyGroups.emplace_back("Animal", specialBox, SpellEnum::ANIMAL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Arborea", specialBox, SpellEnum::ARBOREA_DOMAIN);
	domainGroup.familyGroups.emplace_back("Baator", specialBox, SpellEnum::BAATOR_DOMAIN);
	domainGroup.familyGroups.emplace_back("Balance", specialBox, SpellEnum::BALANCE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Blackwater", specialBox, SpellEnum::BLACKWATER_DOMAIN);
	domainGroup.familyGroups.emplace_back("Cavern", specialBox, SpellEnum::CAVERN_DOMAIN);
	domainGroup.familyGroups.emplace_back("Celerity", specialBox, SpellEnum::CELERITY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Celestia", specialBox, SpellEnum::CELESTIA_DOMAIN);
	domainGroup.familyGroups.emplace_back("Chaos", specialBox, SpellEnum::CHAOS_DOMAIN);
	domainGroup.familyGroups.emplace_back("Charm", specialBox, SpellEnum::CHARM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Cold", specialBox, SpellEnum::COLD_DOMAIN);
	domainGroup.familyGroups.emplace_back("Community", specialBox, SpellEnum::COMMUNITY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Competition", specialBox, SpellEnum::COMPETITION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Corruption", specialBox, SpellEnum::CORRUPTION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Courage", specialBox, SpellEnum::COURAGE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Craft", specialBox, SpellEnum::CRAFT_DOMAIN);
	domainGroup.familyGroups.emplace_back("Creation", specialBox, SpellEnum::CREATION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Darkness", specialBox, SpellEnum::DARKNESS_DOMAIN);
	domainGroup.familyGroups.emplace_back("Death", specialBox, SpellEnum::DEATH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Deathbound", specialBox, SpellEnum::DEATHBOUND_DOMAIN);
	domainGroup.familyGroups.emplace_back("Demonic", specialBox, SpellEnum::DEMONIC_DOMAIN);
	domainGroup.familyGroups.emplace_back("Destruction", specialBox, SpellEnum::DESTRUCTION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Diabolic", specialBox, SpellEnum::DIABOLIC_DOMAIN);
	domainGroup.familyGroups.emplace_back("Domination", specialBox, SpellEnum::DOMINATION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Dragon", specialBox, SpellEnum::DRAGON_DOMAIN);
	domainGroup.familyGroups.emplace_back("Dream", specialBox, SpellEnum::DREAM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Drow", specialBox, SpellEnum::DROW_DOMAIN);
	domainGroup.familyGroups.emplace_back("Dwarf", specialBox, SpellEnum::DWARF_DOMAIN);
	domainGroup.familyGroups.emplace_back("Earth", specialBox, SpellEnum::EARTH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Elf", specialBox, SpellEnum::ELF_DOMAIN);
	domainGroup.familyGroups.emplace_back("Elysium", specialBox, SpellEnum::ELYSIUM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Entropy", specialBox, SpellEnum::ENTROPY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Envy", specialBox, SpellEnum::ENVY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Evil", specialBox, SpellEnum::EVIL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Family", specialBox, SpellEnum::FAMILY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Fate", specialBox, SpellEnum::FATE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Fire", specialBox, SpellEnum::FIRE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Force", specialBox, SpellEnum::FORCE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Fury", specialBox, SpellEnum::FURY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Glory", specialBox, SpellEnum::GLORY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Gluttony", specialBox, SpellEnum::GLUTTONY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Good", specialBox, SpellEnum::GOOD_DOMAIN);
	domainGroup.familyGroups.emplace_back("Gnome", specialBox, SpellEnum::GNOME_DOMAIN);
	domainGroup.familyGroups.emplace_back("Greed", specialBox, SpellEnum::GREED_DOMAIN);
	domainGroup.familyGroups.emplace_back("Hades", specialBox, SpellEnum::HADES_DOMAIN);
	domainGroup.familyGroups.emplace_back("Halfling", specialBox, SpellEnum::HALFLING_DOMAIN);
	domainGroup.familyGroups.emplace_back("Hatred", specialBox, SpellEnum::HATRED_DOMAIN);
	domainGroup.familyGroups.emplace_back("Healing", specialBox, SpellEnum::HEALING_DOMAIN);
	domainGroup.familyGroups.emplace_back("Hunger", specialBox, SpellEnum::HUNGER_DOMAIN);
	domainGroup.familyGroups.emplace_back("Illusion", specialBox, SpellEnum::ILLUSION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Incarnum", specialBox, SpellEnum::INCARNUM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Inquisition", specialBox, SpellEnum::INQUISITION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Knowledge", specialBox, SpellEnum::KNOWLEDGE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Law", specialBox, SpellEnum::LAW_DOMAIN);
	domainGroup.familyGroups.emplace_back("Liberation", specialBox, SpellEnum::LIBERATION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Limbo", specialBox, SpellEnum::LIMBO_DOMAIN);
	domainGroup.familyGroups.emplace_back("Luck", specialBox, SpellEnum::LUCK_DOMAIN);
	domainGroup.familyGroups.emplace_back("Lust", specialBox, SpellEnum::LUST_DOMAIN);
	domainGroup.familyGroups.emplace_back("Magic", specialBox, SpellEnum::MAGIC_DOMAIN);
	domainGroup.familyGroups.emplace_back("Madness", specialBox, SpellEnum::MADNESS_DOMAIN);
	domainGroup.familyGroups.emplace_back("Mechanus", specialBox, SpellEnum::MECHANUS_DOMAIN);
	domainGroup.familyGroups.emplace_back("Mentalism", specialBox, SpellEnum::MENTALISM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Metal", specialBox, SpellEnum::METAL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Mind", specialBox, SpellEnum::MIND_DOMAIN);
	domainGroup.familyGroups.emplace_back("Moon", specialBox, SpellEnum::MOON_DOMAIN);
	domainGroup.familyGroups.emplace_back("Mysticism", specialBox, SpellEnum::MYSTICISM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Nobility", specialBox, SpellEnum::NOBILITY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Ocean", specialBox, SpellEnum::OCEAN_DOMAIN);
	domainGroup.familyGroups.emplace_back("Ooze", specialBox, SpellEnum::OOZE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Oracle", specialBox, SpellEnum::ORACLE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Orc", specialBox, SpellEnum::ORC_DOMAIN);
	domainGroup.familyGroups.emplace_back("Pact", specialBox, SpellEnum::PACT_DOMAIN);
	domainGroup.familyGroups.emplace_back("Pestilence", specialBox, SpellEnum::PESTILENCE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Planning", specialBox, SpellEnum::PLANNING_DOMAIN);
	domainGroup.familyGroups.emplace_back("Plant", specialBox, SpellEnum::PLANT_DOMAIN);
	domainGroup.familyGroups.emplace_back("Portal", specialBox, SpellEnum::PORTAL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Pride", specialBox, SpellEnum::PRIDE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Protection", specialBox, SpellEnum::PROTECTION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Purification", specialBox, SpellEnum::PURIFICATION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Renewal", specialBox, SpellEnum::RENEWAL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Repose", specialBox, SpellEnum::REPOSE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Retribution", specialBox, SpellEnum::RETRIBUTION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Revered Ancestor", specialBox, SpellEnum::REVERED_ANCESTOR_DOMAIN);
	domainGroup.familyGroups.emplace_back("Rune", specialBox, SpellEnum::RUNE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Sand", specialBox, SpellEnum::SAND_DOMAIN);
	domainGroup.familyGroups.emplace_back("Scalykind", specialBox, SpellEnum::SCALYKIND_DOMAIN);
	domainGroup.familyGroups.emplace_back("Seafolk", specialBox, SpellEnum::SEAFOLK_DOMAIN);
	domainGroup.familyGroups.emplace_back("Slime", specialBox, SpellEnum::SLIME_DOMAIN);
	domainGroup.familyGroups.emplace_back("Sloth", specialBox, SpellEnum::SLOTH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Spell", specialBox, SpellEnum::SPELL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Spider", specialBox, SpellEnum::SPIDER_DOMAIN);
	domainGroup.familyGroups.emplace_back("Spite", specialBox, SpellEnum::SPITE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Storm", specialBox, SpellEnum::STORM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Strength", specialBox, SpellEnum::STRENGTH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Suffering", specialBox, SpellEnum::SUFFERING_DOMAIN);
	domainGroup.familyGroups.emplace_back("Summer", specialBox, SpellEnum::SUMMER_DOMAIN);
	domainGroup.familyGroups.emplace_back("Summoner", specialBox, SpellEnum::SUMMONER_DOMAIN);
	domainGroup.familyGroups.emplace_back("Sun", specialBox, SpellEnum::SUN_DOMAIN);
	domainGroup.familyGroups.emplace_back("Temptation", specialBox, SpellEnum::TEMPTATION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Thirst", specialBox, SpellEnum::THIRST_DOMAIN);
	domainGroup.familyGroups.emplace_back("Time", specialBox, SpellEnum::TIME_DOMAIN);
	domainGroup.familyGroups.emplace_back("Trade", specialBox, SpellEnum::TRADE_DOMAIN);
	domainGroup.familyGroups.emplace_back("Transformation", specialBox, SpellEnum::TRANSFORMATION_DOMAIN);
	domainGroup.familyGroups.emplace_back("Travel", specialBox, SpellEnum::TRAVEL_DOMAIN);
	domainGroup.familyGroups.emplace_back("Trickery", specialBox, SpellEnum::TRICKERY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Truth", specialBox, SpellEnum::TRUTH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Tyranny", specialBox, SpellEnum::TYRANNY_DOMAIN);
	domainGroup.familyGroups.emplace_back("Undeath", specialBox, SpellEnum::UNDEATH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Vile Darkness", specialBox, SpellEnum::VILE_DARKNESS_DOMAIN);
	domainGroup.familyGroups.emplace_back("War", specialBox, SpellEnum::WAR_DOMAIN);
	domainGroup.familyGroups.emplace_back("Warforged", specialBox, SpellEnum::WARFORGED_DOMAIN);
	domainGroup.familyGroups.emplace_back("Water", specialBox, SpellEnum::WATER_DOMAIN);
	domainGroup.familyGroups.emplace_back("Wealth", specialBox, SpellEnum::WEALTH_DOMAIN);
	domainGroup.familyGroups.emplace_back("Windstorm", specialBox, SpellEnum::WINDSTORM_DOMAIN);
	domainGroup.familyGroups.emplace_back("Wrath", specialBox, SpellEnum::WRATH_DOMAIN);
	
	auto& otherGroup = newGroup.familyGroups.emplace_back("Other", specialBox);
	otherGroup.familyGroups.emplace_back("Arcane Artifact", specialBox, SpellEnum::ARCANE_ARTIFACT);
	otherGroup.familyGroups.emplace_back("Corrupt", specialBox, SpellEnum::CORRUPT);
	otherGroup.familyGroups.emplace_back("Divine Artifact", specialBox, SpellEnum::DIVINE_ARTIFACT);
	otherGroup.familyGroups.emplace_back("Initiate", specialBox, SpellEnum::INITIATE);
	otherGroup.familyGroups.emplace_back("Oneiromancy", specialBox, SpellEnum::ONEIROMANCY);
	otherGroup.familyGroups.emplace_back("Sanctified", specialBox, SpellEnum::SANCTIFIED);
	
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
	layout->addWidget(specialBox, 1, 0, 2, 2);
	
	QAbstractDatabaseWindow::initialiseWindow(baseClassGroup, font, 5);
	QAbstractDatabaseWindow::initialiseWindow(prestigeClassGroup, font, 2);
	QAbstractDatabaseWindow::initialiseWindow(domainGroup, font, 10);
	QAbstractDatabaseWindow::initialiseWindow(otherGroup, font, 3);
}

void QSpellDatabaseWindow::initialiseSpellResistances(const QFont& font, QGridLayout* layout)
{
	const auto resistanceBox = new QGroupBox("Spell Resistance", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Yes", resistanceBox, SpellEnum::RESISTANCE),
	newGroup.familyGroups.emplace_back("Object", resistanceBox, SpellEnum::RESISTANCE_OBJECT),
	newGroup.familyGroups.emplace_back("Harmless", resistanceBox, SpellEnum::RESISTANCE_HARMLESS),
	newGroup.familyGroups.emplace_back("See text", resistanceBox, SpellEnum::RESISTANCE_SEE_TEXT);
	
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
	layout->addWidget(resistanceBox, 13, 8, 2, 2);
}

void QSpellDatabaseWindow::initialiseSubschools(const QFont& font, QGridLayout* layout)
{
	const auto subschoolBox = new QGroupBox("Subschools", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Calling", subschoolBox, SpellEnum::CALLING);
	newGroup.familyGroups.emplace_back("Charm", subschoolBox, SpellEnum::CHARM);
	newGroup.familyGroups.emplace_back("Compulsion", subschoolBox, SpellEnum::COMPULSION);
	newGroup.familyGroups.emplace_back("Creation", subschoolBox, SpellEnum::CREATION);
	newGroup.familyGroups.emplace_back("Figment", subschoolBox, SpellEnum::FIGMENT);
	newGroup.familyGroups.emplace_back("Glamer", subschoolBox, SpellEnum::GLAMER);
	newGroup.familyGroups.emplace_back("Healing", subschoolBox, SpellEnum::HEALING);
	newGroup.familyGroups.emplace_back("Pattern", subschoolBox, SpellEnum::PATTERN);
	newGroup.familyGroups.emplace_back("Phantasm", subschoolBox, SpellEnum::PHANTASM);
	newGroup.familyGroups.emplace_back("Polymorph", subschoolBox, SpellEnum::POLYMORPH);
	newGroup.familyGroups.emplace_back("Scrying", subschoolBox, SpellEnum::SCRYING);
	newGroup.familyGroups.emplace_back("Shadow", subschoolBox, SpellEnum::SHADOW);
	newGroup.familyGroups.emplace_back("Summoning", subschoolBox, SpellEnum::SUMMONING);
	newGroup.familyGroups.emplace_back("Teleportation", subschoolBox, SpellEnum::TELEPORTATION);
	
	const auto subschoolLayout = new QGridLayout();
	auto count = 0;
	
	for (const auto& foo : newGroup.familyGroups)
	{
		subschoolLayout->addWidget(foo.masterButton, count/5, count % 5);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		++count;
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	subschoolBox->setLayout(subschoolLayout);
	layout->addWidget(subschoolBox, 1, 5, 3, 5);
}

void QSpellDatabaseWindow::initialiseTargets(const QFont& font, QGridLayout* layout)
{
	const auto targetBox = new QGroupBox("Targets", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	
	newGroup.familyGroups.emplace_back("Areas", targetBox, SpellEnum::AREAS);
	newGroup.familyGroups.emplace_back("Creatures", targetBox, SpellEnum::CREATURES);
	newGroup.familyGroups.emplace_back("Objects", targetBox, SpellEnum::OBJECTS);
	newGroup.familyGroups.emplace_back("Corpses", targetBox, SpellEnum::CORPSES);
	newGroup.familyGroups.emplace_back("Multiple", targetBox, SpellEnum::MULTIPLE);
	newGroup.familyGroups.emplace_back("You", targetBox, SpellEnum::YOU);
	
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
	layout->addWidget(targetBox, 13, 0, 2, 3);
}

void QSpellDatabaseWindow::initialiseTypes(const QFont& font, QGridLayout* layout)
{
	const auto typeBox = new QGroupBox("Spell Types", QAbstractDatabaseWindow::mainWidget);
	auto& newGroup = QAbstractDatabaseWindow::buttonGroups.emplace_back();
	newGroup.familyGroups.reserve(5u);
	
	auto& arcaneGroup = newGroup.familyGroups.emplace_back("Arcane", typeBox);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::BARD);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::SORCERER);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::WIZARD);
	
	arcaneGroup.familyGroups.emplace_back(SpellEnum::ASSASSIN);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::ARCANE_ARTIFACT);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::BEGUILER);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::CORRUPT);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::DREAD_NECROMANCER);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::DUSKBLADE);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::HEXBLADE);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::ONEIROMANCY);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::SANCTIFIED);
	arcaneGroup.familyGroups.emplace_back(SpellEnum::WU_JEN);
	
	auto& divineGroup = newGroup.familyGroups.emplace_back("Divine", typeBox);
	divineGroup.familyGroups.emplace_back(SpellEnum::CLERIC);
	divineGroup.familyGroups.emplace_back(SpellEnum::DRUID);
	divineGroup.familyGroups.emplace_back(SpellEnum::PALADIN);
	divineGroup.familyGroups.emplace_back(SpellEnum::RANGER);
	
	divineGroup.familyGroups.emplace_back(SpellEnum::ADEPT);
	divineGroup.familyGroups.emplace_back(SpellEnum::BLACKGUARD);
	divineGroup.familyGroups.emplace_back(SpellEnum::CORRUPT);
	divineGroup.familyGroups.emplace_back(SpellEnum::DEATH_DELVER);
	divineGroup.familyGroups.emplace_back(SpellEnum::DIVINE_ARTIFACT);
	divineGroup.familyGroups.emplace_back(SpellEnum::HEALER);
	divineGroup.familyGroups.emplace_back(SpellEnum::INITIATE);
	divineGroup.familyGroups.emplace_back(SpellEnum::ONEIROMANCY);
	divineGroup.familyGroups.emplace_back(SpellEnum::SANCTIFIED);
	divineGroup.familyGroups.emplace_back(SpellEnum::SHUGENJA);
	
	auto& infusionGroup = newGroup.familyGroups.emplace_back("Infusion", typeBox);
	infusionGroup.familyGroups.emplace_back(SpellEnum::ARTIFICER);
	
	const auto typeLayout = new QHBoxLayout();
	
	for (const auto& foo : newGroup.familyGroups)
	{
		typeLayout->addWidget(foo.masterButton);
		foo.masterButton->setObjectName("A");
		foo.masterButton->setFont(font);
		
		QObject::connect(foo.masterButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	typeBox->setLayout(typeLayout);
	layout->addWidget(typeBox, 0, 7, 1, 3);
}

QColor QSpellDatabaseWindow::Background(const HexBitset<Number>& b)
{
	if (QSpellDatabaseWindow::RevisedBitset.any(b))
		return QSpellDatabaseWindow::RevisedColor;
	
	return QSpellDatabaseWindow::UnrevisedColor;
}

void QSpellDatabaseWindow::closeEvent(QCloseEvent* e)
{
	QWidget::parentWidget()->show();
	QMainWindow::closeEvent(e);
}

void QSpellDatabaseWindow::initialiseData(void)
{
	if (not QSpellDatabaseWindow::spellFile.open(QIODevice::ReadOnly | QIODevice::Text))
		std::exit(1);
	
	QSpellDatabaseWindow::spellFileStream.seek(0);
	auto line = 0u;
	
	while (not QSpellDatabaseWindow::spellFileStream.atEnd())
	{
		const auto name = QAbstractDatabaseWindow::ExtractString(QSpellDatabaseWindow::spellFile, '@');
		const auto bset = QAbstractDatabaseWindow::ExtractString(QSpellDatabaseWindow::spellFile, '@');
		
		const auto infoPos = QSpellDatabaseWindow::spellFile.pos();
		const auto info = QAbstractDatabaseWindow::ExtractString(QSpellDatabaseWindow::spellFile, '@');
		
		const auto lorePos = QSpellDatabaseWindow::spellFile.pos();
		const auto lore = QAbstractDatabaseWindow::ExtractString(QSpellDatabaseWindow::spellFile, '\n');
		
		QSpellDatabaseWindow::allSpells.emplace_back(name, bset, infoPos, lorePos);
		QSpellDatabaseWindow::nameToIndex[name] = line++;
	}
}

void QSpellDatabaseWindow::initialiseWidgets(void)
{
	QMainWindow::setWindowTitle("Dungeons & Dragons 3.5e Spell Library");
	QMainWindow::resize(1700, 600);
	
	const auto layout = new QGridLayout();
	QFont font;
	font.setPixelSize(10);
	
	QSpellDatabaseWindow::initialiseClasses(font, layout);
	QSpellDatabaseWindow::initialiseTypes(font, layout);
	QSpellDatabaseWindow::initialiseSpecial(font, layout);
	QSpellDatabaseWindow::initialiseSchools(font, layout);
	QSpellDatabaseWindow::initialiseSubschools(font, layout);
	QSpellDatabaseWindow::initialiseMaterials(font, layout);
	QSpellDatabaseWindow::initialiseDescriptors(font, layout);
	QSpellDatabaseWindow::initialiseSources(font, layout);
	
	QSpellDatabaseWindow::initialiseLevels(font, layout);
	QSpellDatabaseWindow::initialiseRanges(font, layout);
	QSpellDatabaseWindow::initialiseAreas(font, layout);
	QSpellDatabaseWindow::initialiseCastingTimes(font, layout);
	QSpellDatabaseWindow::initialiseEffects(font, layout);
	
	QSpellDatabaseWindow::initialiseDurations(font, layout);
	QSpellDatabaseWindow::initialiseControlButtons(font, layout);
	QSpellDatabaseWindow::initialiseTargets(font, layout);
	QSpellDatabaseWindow::initialiseSaves(font, layout);
	QSpellDatabaseWindow::initialiseSpellResistances(font, layout);
	QSpellDatabaseWindow::initialiseEverythingElse(font, layout);
	
	QAbstractDatabaseWindow::mainWidget->setLayout(layout);
}

void QSpellDatabaseWindow::search(void)
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
			const auto& file = QSpellDatabaseWindow::allSpells[u];
			const auto valid = QSpellDatabaseWindow::spellIsValid(file, greenBitset, redBitset, yellowBitsets, nameSearch, loreSearch, checkGreen, checkRed);
			
			if (valid)
				newSearchResults.push_back(index);
			
			++index;
		}
		
		QAbstractDatabaseWindow::searchResults.swap(newSearchResults);
	}
	else
	{
		QAbstractDatabaseWindow::searchResults.clear();
		
		for (const auto& file : QSpellDatabaseWindow::allSpells)
		{
			const auto valid = QSpellDatabaseWindow::spellIsValid(file, greenBitset, redBitset, yellowBitsets, nameSearch, loreSearch, checkGreen, checkRed);
			
			if (valid)
				QAbstractDatabaseWindow::searchResults.push_back(index);
			
			++index;
		}
	}
	
	QAbstractDatabaseWindow::resultList->clear();
	
	for (const auto& u : QSpellDatabaseWindow::searchResults)
	{
		const auto& file = QSpellDatabaseWindow::allSpells[u];
		const auto item = new QListWidgetItem(file.name);
		
		const auto backgroundColor = QSpellDatabaseWindow::Background(file.bits);
		const auto foregroundColor = QSpellDatabaseWindow::Foreground(file.bits);
		
		item->setBackground(backgroundColor);
		item->setForeground(foregroundColor);
		
		QAbstractDatabaseWindow::resultList->addItem(item);
	}
	
	const auto size = QSpellDatabaseWindow::searchResults.size();
	const auto resultString = QString::number(size) + " result" + QString(size > 1u ? "s" : "") + ".";
	
	QAbstractDatabaseWindow::resultLabel->setText(resultString);
}

bool QSpellDatabaseWindow::spellIsValid(const HexFile<Number>& file, const HexBitset<Number>& greenBitset, const HexBitset<Number>& redBitset, const std::vector<HexBitset<Number>>& yellowBitsets, const QString& nameSearch, const QString& loreSearch, bool checkGreen, bool checkRed)
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
		QSpellDatabaseWindow::spellFileStream.seek(file.textPositionInFile);
		const auto theLore = QSpellDatabaseWindow::spellFileStream.readLine().toLower();
		
		if (QAbstractDatabaseWindow::barTextsButton->isChecked() and theLore.indexOf(loreSearch, Qt::CaseInsensitive) >= 0)
			return false;
		
		if (not QAbstractDatabaseWindow::barTextsButton->isChecked() and theLore.indexOf(loreSearch, Qt::CaseInsensitive) < 0)
			return false;
	}
	
	return true;
}

void QSpellDatabaseWindow::updateLore(quint32 index, QTextBrowser* browser)
{
	const auto& file = QSpellDatabaseWindow::allSpells[index];
	QSpellDatabaseWindow::spellFileStream.seek(file.infoPositionInFile);
	
	const auto info = QAbstractDatabaseWindow::ExtractString(QSpellDatabaseWindow::spellFile, '@');
	const auto infoList = info.split(';');
	
	if (infoList.size() != 16u)
		return;
	
	const auto lore = QSpellDatabaseWindow::spellFileStream.readLine();
	auto qText = "<b>" + file.name + "</b><br>" + infoList.at(0) + "<br>";
	
	if (not infoList.at(1).isEmpty())
		qText += "<b>Core Classes:</b> " + infoList.at(1) + "<br>";

	if (not infoList.at(2).isEmpty())
		qText += "<b>Base Classes:</b> " + infoList.at(2) + "<br>";
	
	if (not infoList.at(3).isEmpty())
		qText += "<b>Prestige Classes:</b> " + infoList.at(3) + "<br>";
	
	if (not infoList.at(4).isEmpty())
		qText += "<b>Levels:</b> " + infoList.at(4) + "<br>";
	
	if (not infoList.at(5).isEmpty())
		qText += "<b>Domains:</b> " + infoList.at(5) + "<br>";
	
	qText += "<b>Components:</b> " + (infoList.at(6).isEmpty() ? "None" : infoList.at(6)) + "<br>";
	qText += "<b>Casting Time:</b> " + infoList.at(7) + "<br>";
	qText += "<b>Range:</b> " + infoList.at(8) + "<br>";
	
	if (not infoList.at(9).isEmpty())
		qText += "<b>Effect:</b> " + infoList.at(9) + "<br>";
	
	if (not infoList.at(10).isEmpty())
		qText += "<b>Target:</b> " + infoList.at(10) + "<br>";
	
	if (not infoList.at(11).isEmpty())
		qText += "<b>Area:</b> " + infoList.at(11) + "<br>";
	
	qText += "<b>Duration:</b> " + infoList.at(12) + "<br>";
	
	if (not infoList.at(13).isEmpty())
		qText += "<b>Saving Throw:</b> " + infoList.at(13) + "<br>";
	
	if (not infoList.at(14).isEmpty())
		qText += "<b>Spell Resistance:</b> " + infoList.at(14) + "<br>";
	
	qText += "<b>Source:</b> " + infoList.back();
	qText += QAbstractDatabaseWindow::Process(lore, QAbstractDatabaseWindow::loreLineEdit->text().toLower());
	
	browser->setHtml(qText);
}

#endif
