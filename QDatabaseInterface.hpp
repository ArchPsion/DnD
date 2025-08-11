#ifndef __DATABASE_INTERFACE_HPP__
#define __DATABASE_INTERFACE_HPP__

// Qt Libraries
#include <QGroupBox>
#include <QKeyEvent>

// Custom Libraries
#include "HexBitset.hpp"
#include "QDatabaseInterfaceIntermediary.hpp"

template<typename Type>
class QDatabaseInterface : public QDatabaseInterfaceIntermediary
{
	private:
		
		using CustomBitset = HexBitset<static_cast<quint32>(Type::SIZE)>;
		using NameBitsetPair = std::pair<QString, CustomBitset>;
		
		using ButtonBitsetPair = std::pair<QPushButton*, CustomBitset>;
		using ButtonBitPair = std::pair<QPushButton*, quint32>;
		
		static constexpr QColor				ClairsentienceDivinationColor = QColor(255, 153, 51);
		static constexpr QColor				MetacreativityConjurationColor = QColor(255, 102, 102);
		static constexpr QColor				PsychokinesisEvocationColor = QColor(102, 178, 255);
		static constexpr QColor				PsychometabolismTransmutationColor = QColor(204, 153, 255);
		static constexpr QColor				PsychoportationAbjurationColor = QColor(20, 205, 113);
		static constexpr QColor				TelepathyEnchantmentColor = QColor(255, 153, 255);
		
		static constexpr QColor				IllusionColor = QColor(217, 173, 0);
		static constexpr QColor				NecromancyColor = QColor(197, 135, 135);
		static constexpr QColor				UniversalColor = QColor(128, 128, 128);
		
		static const QString 				CastingOrManifestingString;
		static const QString 				ComponentOrDisplayString;
		static const QString 				DomainOrMantleString;
		static const QString 				ResistanceString;
		inline static CustomBitset			RevisedBitset;
		
		inline static QColor				Background(const CustomBitset&);
		static QColor					Foreground(const CustomBitset&);
		inline static ButtonBitPair 			MakePair(const QString&, Type);
		
		std::vector<NameBitsetPair>			spellOrPowerList;
		std::vector<quint32>				searchResults;
		
		std::vector<ButtonBitPair>			bits;
		std::vector<ButtonBitsetPair>			multibits;
		
		inline void					initialiseAreas(const QFont&, QGridLayout*, qint32);
		void						initialiseBars(const QFont&, QGridLayout*, qint32);
		inline void					initialiseCastingOrManifestingTimes(const QFont&, QGridLayout*, qint32);
		void						initialiseClasses(const QFont&, QGridLayout*);
		inline void					initialiseControlButtons(const QFont&, QGridLayout*, qint32);
		inline void					initialiseData(void);
		qint32						initialiseDescriptors(const QFont&, QGridLayout*);
		inline void					initialiseDurations(const QFont&, QGridLayout*, qint32);
		inline void					initialiseEffects(const QFont&, QGridLayout*, qint32);
		void						initialiseFeatures(const QFont&, QGridLayout*);
		inline void					initialiseLevels(const QFont&, QGridLayout*, qint32);
		void						initialiseMaterialsOrDisplays(const QFont&, QGridLayout*);
		inline void					initialiseRanges(const QFont&, QGridLayout*, qint32);
		inline void					initialiseResistances(const QFont&, QGridLayout*, qint32);
		inline void					initialiseSaves(const QFont&, QGridLayout*, qint32);
		void						initialiseSchoolsOrDisciplines(const QFont&, QGridLayout*);
		void						initialiseSources(const QFont&, QGridLayout*, qint32);
		void						initialiseSpecial(const QFont&, QGridLayout*);
		void						initialiseSubschoolsOrSubdisciplines(const QFont&, QGridLayout*);
		inline void					initialiseTargets(const QFont&, QGridLayout*, qint32);
		inline void					initialiseWidgets(void);
		inline void					initialiseWindow(const std::initializer_list<ButtonBitPair>&, const QString&, const QFont&, QPushButton*, CustomBitset&, qint32);
		inline void					resetButtons(void) override;
		inline void					search(void);
		inline void					searchBitsets(void);
		inline void					searchPattern(const std::string&, std::ifstream&, bool);
		inline void					searchStrings(void);
		inline void					updateLore(const QString&, QTextEdit*, quint32) const override;
		inline void					updateLoreFromList(QTextEdit*, qint32) const override;
	
	protected:
	
		inline void					closeEvent(QCloseEvent*);
		inline void					keyReleaseEvent(QKeyEvent*);
	
	public:
	
		inline						QDatabaseInterface(QWidget*, const QString&);
		inline bool					eventFilter(QObject*, QEvent*) override;
};

template<typename Type>
QDatabaseInterface<Type>::QDatabaseInterface(QWidget* foo, const QString& name) :
	QDatabaseInterfaceIntermediary(foo, name)
{
	QDatabaseInterface::initialiseData();
	QDatabaseInterface::initialiseWidgets();
}

template<typename Type>
QColor QDatabaseInterface<Type>::Background(const CustomBitset& b)
{
	if (QDatabaseInterface::RevisedBitset.any(b))
		return QColor(255, 255, 255);
	
	return QColor(203, 203, 203);
}

template<typename Type>
void QDatabaseInterface<Type>::closeEvent(QCloseEvent* e)
{
	QWidget::parentWidget()->show();
	QMainWindow::closeEvent(e);
}

template<typename Type>
bool QDatabaseInterface<Type>::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::KeyRelease)
		QDatabaseInterface::event(event);
	
	return QObject::eventFilter(obj, event);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseAreas(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto areaBox = new QGroupBox("Areas", this);
	const auto areaLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Circle", Type::CIRCLE),
				QDatabaseInterface::MakePair("Cone", Type::CONE),
				QDatabaseInterface::MakePair("Cylinder", Type::CYLINDER),
				QDatabaseInterface::MakePair("Line", Type::LINE),
				QDatabaseInterface::MakePair("Plane", Type::PLANE),
				QDatabaseInterface::MakePair("Sphere", Type::SPHERE),
				QDatabaseInterface::MakePair("Shapeable", Type::SHAPEABLE) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		areaLayout->addWidget(pr.first, count/5, count % 5);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = { QDatabaseInterface::MakePair("Cube", Type::CUBE),
				QDatabaseInterface::MakePair("Square", Type::SQUARE),
				QDatabaseInterface::MakePair("Peculiar", Type::PECULIAR_AREA) };
	
	const auto otherAreaButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherAreaButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other Areas", font, otherAreaButton, QDatabaseInterface::multibits.back().second, 4);
	
	areaLayout->addWidget(otherAreaButton, 1, count % 5);
	otherAreaButton->setObjectName("A");
	otherAreaButton->setFont(font);
	++count;
	
	QObject::connect(otherAreaButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	const auto pr = QDatabaseInterface::MakePair("Centered", Type::CENTERED);
	areaLayout->addWidget(pr.first, 1, count % 5);
	pr.first->setObjectName("A");
	pr.first->setFont(font);
	++count;
	
	QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	QDatabaseInterface::bits.push_back(pr);
	
	areaBox->setLayout(areaLayout);
	layout->addWidget(areaBox, delta + 1, 5, 2, 5);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseCastingOrManifestingTimes(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto castingOrManifestingTimeBox = new QGroupBox(QDatabaseInterface::CastingOrManifestingString + " Times", this);
	const auto castingOrManifestingTimeLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Immediate", Type::IMMEDIATE),
				QDatabaseInterface::MakePair("Swift", Type::SWIFT),
				QDatabaseInterface::MakePair("Move", Type::MOVE),
				QDatabaseInterface::MakePair("Standard", Type::STANDARD),
				QDatabaseInterface::MakePair("1 round", Type::ONE_ROUND) };
	
	for (const auto& pr : bitPairs)
	{
		castingOrManifestingTimeLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("2+ rounds", Type::TWO_ROUNDS),
				QDatabaseInterface::MakePair("1+ minute", Type::ONE_MINUTE),
				QDatabaseInterface::MakePair("10+ minutes", Type::TEN_MINUTES),
				QDatabaseInterface::MakePair("1+ hour", Type::ONE_HOUR),
				QDatabaseInterface::MakePair("1+ day", Type::ONE_DAY),
				QDatabaseInterface::MakePair("See text", Type::TIME_SEE_TEXT),
				QDatabaseInterface::MakePair("Peculiar", Type::PECULIAR_TIME) };
	
	const auto otherTimeButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherTimeButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other " + QDatabaseInterface::CastingOrManifestingString + " Times", font, otherTimeButton, QDatabaseInterface::multibits.back().second, 4);
	
	castingOrManifestingTimeLayout->addWidget(otherTimeButton);
	otherTimeButton->setObjectName("A");
	otherTimeButton->setFont(font);
	QObject::connect(otherTimeButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	castingOrManifestingTimeBox->setLayout(castingOrManifestingTimeLayout);
	layout->addWidget(castingOrManifestingTimeBox, delta + 3, 0, 1, 6);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseControlButtons(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto filterControlBox = new QGroupBox("Filter Controls", this);
	const auto filterControlLayout = new QGridLayout();
	
	const auto buttonList = { QDatabaseInterfaceIntermediary::barNamesButton, QDatabaseInterfaceIntermediary::keepListButton, QDatabaseInterfaceIntermediary::barTextsButton };
	auto count = 0;
	
	for (const auto& btn : buttonList)
	{
		filterControlLayout->addWidget(btn, count/2, count % 2);
		btn->setObjectName("KL");
		btn->setCheckable(true);
		btn->setFont(font);
		++count;
	}
	
	filterControlLayout->addWidget(QDatabaseInterfaceIntermediary::resetButton, 1, 1);
	QDatabaseInterfaceIntermediary::resetButton->setObjectName("KL");
	QDatabaseInterfaceIntermediary::resetButton->setFont(font);
	
	filterControlBox->setLayout(filterControlLayout);
	layout->addWidget(filterControlBox, delta + 4, 8, 2, 2);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseData(void)
{
	std::ifstream nameFile("files/" + QDatabaseInterfaceIntermediary::contentName.toStdString() + "Names");
	nameFile.clear();
	nameFile.seekg(std::ios::beg);
	
	std::ifstream bitFile("files/" + QDatabaseInterfaceIntermediary::contentName.toStdString() + "Bits");
	bitFile.clear();
	bitFile.seekg(std::ios::beg);
	
	std::string line;
	std::string name;
	auto count = 0u;
    
	while (nameFile.peek() != std::ifstream::traits_type::eof() and bitFile.peek() != std::ifstream::traits_type::eof())
	{
		getline(nameFile, name);
		getline(bitFile, line);
		
		QDatabaseInterface::spellOrPowerList.emplace_back(QString::fromStdString(name), line);
		QDatabaseInterfaceIntermediary::fullIndex[QString::fromStdString(name)] = count;
		++count;
	}
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseDurations(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto durationBox = new QGroupBox("Durations", this);
	const auto durationLayout = new QGridLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Instantaneous", Type::INSTANTANEOUS),
				QDatabaseInterface::MakePair("1 round/2+ levels", Type::ONE_ROUND_TWO_LEVELS),
				QDatabaseInterface::MakePair("1+ round/level", Type::ONE_ROUND_LEVEL),
				QDatabaseInterface::MakePair("1+ minute/level", Type::ONE_MINUTE_LEVEL),
				QDatabaseInterface::MakePair("10+ minutes/level", Type::TEN_MINUTES_LEVEL),
				QDatabaseInterface::MakePair("1+ hour/level", Type::ONE_HOUR_LEVEL),
				QDatabaseInterface::MakePair("1+ day/level", Type::ONE_DAY_LEVEL) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		durationLayout->addWidget(pr.first, 0, count);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("1+ round", Type::FIXED_ONE_ROUND),
				QDatabaseInterface::MakePair("1+ minute", Type::FIXED_ONE_MINUTE),
				QDatabaseInterface::MakePair("10+ minutes", Type::FIXED_TEN_MINUTES),
				QDatabaseInterface::MakePair("1+ hour", Type::FIXED_ONE_HOUR),
				QDatabaseInterface::MakePair("1+ day", Type::FIXED_ONE_DAY),
				QDatabaseInterface::MakePair("1+ month", Type::FIXED_ONE_MONTH),
				QDatabaseInterface::MakePair("1+ year", Type::FIXED_ONE_YEAR) };
	
	const auto fixedButton = new QPushButton("Fixed");
	QDatabaseInterface::multibits.emplace_back(fixedButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Fixed Durations", font, fixedButton, QDatabaseInterface::multibits.back().second, 4);
	
	durationLayout->addWidget(fixedButton, 0, count);
	fixedButton->setObjectName("A");
	fixedButton->setFont(font);
	QObject::connect(fixedButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	count = 0;
	
	const auto botPairs = { QDatabaseInterface::MakePair("Concentration", Type::CONCENTRATION),
				QDatabaseInterface::MakePair("Permanent", Type::PERMANENT),
				QDatabaseInterface::MakePair("See text", Type::DURATION_SEE_TEXT) };
	
	for (const auto& pr : botPairs)
	{
		durationLayout->addWidget(pr.first, 1, count);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto batPairs = { QDatabaseInterface::MakePair("Dice", Type::DICE_DURATION),
				QDatabaseInterface::MakePair("Peculiar", Type::PECULIAR_DURATION) };
	
	const auto otherButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(batPairs, "Other Durations", font, otherButton, QDatabaseInterface::multibits.back().second, 3);
	
	durationLayout->addWidget(otherButton, 1, count);
	otherButton->setObjectName("A");
	otherButton->setFont(font);
	QObject::connect(otherButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	++count;
	
	const auto betPairs = { QDatabaseInterface::MakePair("Then", Type::THEN_DURATION),
				QDatabaseInterface::MakePair("Dismiss", Type::DISMISS),
				QDatabaseInterface::MakePair("Discharge", Type::DISCHARGE),
				QDatabaseInterface::MakePair("Trigger", Type::TRIGGER) };
	
	for (const auto& pr : betPairs)
	{
		durationLayout->addWidget(pr.first, 1, count);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	durationBox->setLayout(durationLayout);
	layout->addWidget(durationBox, delta + 4, 0, 2, 8);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseEffects(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto effectBox = new QGroupBox("Effects", this);
	const auto effectLayout = new QHBoxLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Burst", Type::BURST),
				QDatabaseInterface::MakePair("Emanation", Type::EMANATION),
				QDatabaseInterface::MakePair("Ray", Type::RAY),
				QDatabaseInterface::MakePair("Spread", Type::SPREAD) };
	
	for (const auto& pr : bitPairs)
	{
		effectLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	effectBox->setLayout(effectLayout);
	layout->addWidget(effectBox, delta + 3, 6, 1, 4);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseLevels(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto levelBox = new QGroupBox("Levels", this);
	const auto levelLayout = new QHBoxLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("0", Type::LEVEL_0),
				QDatabaseInterface::MakePair("1", Type::LEVEL_1),
				QDatabaseInterface::MakePair("2", Type::LEVEL_2),
				QDatabaseInterface::MakePair("3", Type::LEVEL_3),
				QDatabaseInterface::MakePair("4", Type::LEVEL_4),
				QDatabaseInterface::MakePair("5", Type::LEVEL_5),
				QDatabaseInterface::MakePair("6", Type::LEVEL_6),
				QDatabaseInterface::MakePair("7", Type::LEVEL_7),
				QDatabaseInterface::MakePair("8", Type::LEVEL_8),
				QDatabaseInterface::MakePair("9", Type::LEVEL_9) };
	
	for (const auto& pr : bitPairs)
	{
		levelLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	levelBox->setLayout(levelLayout);
	layout->addWidget(levelBox, delta, 0, 1, 10);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseRanges(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto rangeBox = new QGroupBox("Ranges", this);
	const auto rangeLayout = new QGridLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Personal", Type::PERSONAL),
				QDatabaseInterface::MakePair("Touch", Type::TOUCH),
				QDatabaseInterface::MakePair("Close", Type::CLOSE),
				QDatabaseInterface::MakePair("Medium", Type::MEDIUM),
				QDatabaseInterface::MakePair("Long", Type::LONG) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		rangeLayout->addWidget(pr.first, 0, count);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("0 foot", Type::FIXED_0_FOOT),
				QDatabaseInterface::MakePair("5+ feet", Type::FIXED_5_FEET),
				QDatabaseInterface::MakePair("15+ feet", Type::FIXED_15_FEET),
				QDatabaseInterface::MakePair("30+ feet", Type::FIXED_30_FEET),
				QDatabaseInterface::MakePair("60+ feet", Type::FIXED_60_FEET),
				QDatabaseInterface::MakePair("120+ feet", Type::FIXED_120_FEET),
				QDatabaseInterface::MakePair("1+ mile", Type::FIXED_1_MILE) };
	
	const auto fixedButton = new QPushButton("Fixed");
	QDatabaseInterface::multibits.emplace_back(fixedButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other Ranges", font, fixedButton, QDatabaseInterface::multibits.back().second, 4);
	
	rangeLayout->addWidget(fixedButton, 1, 0);
	fixedButton->setObjectName("A");
	fixedButton->setFont(font);
	QObject::connect(fixedButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
				
				
	const auto botPairs = {	QDatabaseInterface::MakePair("Unlimited", Type::UNLIMITED),
				QDatabaseInterface::MakePair("Boundless", Type::BOUNDLESS),
				QDatabaseInterface::MakePair("See text", Type::RANGE_SEE_TEXT),
				QDatabaseInterface::MakePair("Peculiar", Type::PECULIAR_RANGE) };
	
	count = 1;
	
	for (const auto& pr : botPairs)
	{
		rangeLayout->addWidget(pr.first, 1, count);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	rangeBox->setLayout(rangeLayout);
	layout->addWidget(rangeBox, delta + 1, 0, 2, 5);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseResistances(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto resistanceBox = new QGroupBox(QDatabaseInterface::ResistanceString + " Resistance", this);
	const auto resistanceLayout = new QGridLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Yes", Type::RESISTANCE),
				QDatabaseInterface::MakePair("Object", Type::RESISTANCE_OBJECT),
				QDatabaseInterface::MakePair("Harmless", Type::RESISTANCE_HARMLESS),
				QDatabaseInterface::MakePair("See text", Type::RESISTANCE_SEE_TEXT) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		resistanceLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	resistanceBox->setLayout(resistanceLayout);
	layout->addWidget(resistanceBox, delta + 6, 8, 2, 2);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseSaves(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto saveBox = new QGroupBox("Saves", this);
	const auto saveLayout = new QGridLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Fortitude", Type::FORTITUDE),
				QDatabaseInterface::MakePair("Reflex", Type::REFLEX),
				QDatabaseInterface::MakePair("Will", Type::WILL),
				QDatabaseInterface::MakePair("Object", Type::SAVE_OBJECT),
				QDatabaseInterface::MakePair("Negate", Type::NEGATE),
				QDatabaseInterface::MakePair("Partial", Type::PARTIAL),
				QDatabaseInterface::MakePair("Half", Type::HALF),
				QDatabaseInterface::MakePair("Disbelief", Type::DISBELIEF),
				QDatabaseInterface::MakePair("Harmless", Type::SAVE_HARMLESS),
				QDatabaseInterface::MakePair("See text", Type::SAVE_SEE_TEXT) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		saveLayout->addWidget(pr.first, count/5, count % 5);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	saveBox->setLayout(saveLayout);
	layout->addWidget(saveBox, delta + 6, 3, 2, 5);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseTargets(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto targetBox = new QGroupBox("Targets", this);
	const auto targetLayout = new QGridLayout();
	std::map<QPushButton*, quint32> foo;
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Areas", Type::AREAS),
				QDatabaseInterface::MakePair("Creatures", Type::CREATURES),
				QDatabaseInterface::MakePair("Objects", Type::OBJECTS),
				QDatabaseInterface::MakePair("Corpses", Type::CORPSES),
				QDatabaseInterface::MakePair("Multiple", Type::MULTIPLE),
				QDatabaseInterface::MakePair("You", Type::YOU) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		targetLayout->addWidget(pr.first, count/3, count % 3);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	targetBox->setLayout(targetLayout);
	layout->addWidget(targetBox, delta + 6, 0, 2, 3);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseWidgets(void)
{
	QMainWindow::setWindowTitle("Dungeons & Dragons 3.5e " + QDatabaseInterface::ResistanceString + " Library");
	QMainWindow::resize(1700, 600);
	
	const auto layout = new QGridLayout(new QWidget());
	QMainWindow::setCentralWidget(layout->parentWidget());
	
	QFont font;
	font.setPointSize(8);
	
	QDatabaseInterface::initialiseClasses(font, layout);
	QDatabaseInterface::initialiseSpecial(font, layout);
	QDatabaseInterface::initialiseFeatures(font, layout);
	QDatabaseInterface::initialiseSchoolsOrDisciplines(font, layout);
	QDatabaseInterface::initialiseSubschoolsOrSubdisciplines(font, layout);
	QDatabaseInterface::initialiseMaterialsOrDisplays(font, layout);
	
	const auto delta = QDatabaseInterface::initialiseDescriptors(font, layout);
	QDatabaseInterface::initialiseSources(font, layout, delta);
	QDatabaseInterface::initialiseLevels(font, layout, delta);
	QDatabaseInterface::initialiseRanges(font, layout, delta);
	QDatabaseInterface::initialiseAreas(font, layout, delta);
	QDatabaseInterface::initialiseCastingOrManifestingTimes(font, layout, delta);
	QDatabaseInterface::initialiseEffects(font, layout, delta);
	QDatabaseInterface::initialiseDurations(font, layout, delta);
	QDatabaseInterface::initialiseControlButtons(font, layout, delta);
	QDatabaseInterface::initialiseTargets(font, layout, delta);
	QDatabaseInterface::initialiseSaves(font, layout, delta);
	QDatabaseInterface::initialiseResistances(font, layout, delta);
	QDatabaseInterface::initialiseBars(font, layout, delta);
	
	layout->addWidget(QDatabaseInterfaceIntermediary::resultList, 0, 10, delta + 9, 7);
	layout->addWidget(QDatabaseInterfaceIntermediary::lore, 0, 17, delta + 8, 10);
	layout->addWidget(QDatabaseInterfaceIntermediary::label, delta + 8, 17, 1, 10);
}

template<typename Type>
void QDatabaseInterface<Type>::initialiseWindow(const std::initializer_list<ButtonBitPair>& bitPairs, const QString& name, const QFont& font, QPushButton* button, CustomBitset& bset, qint32 columns)
{
	const auto layout = new QGridLayout(new QWidget());
	const auto window = new QMainWindow(button);
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		layout->addWidget(pr.first, count/columns, count % columns);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
		bset.set(pr.second);
	}
	
	window->installEventFilter(this);
	window->setCentralWidget(layout->parentWidget());
	
	window->setWindowTitle(name);
	window->hide();
}

template<typename Type>
void QDatabaseInterface<Type>::keyReleaseEvent(QKeyEvent* e)
{
	switch (e->key())
	{
		case Qt::Key_Return:
		case Qt::Key_Enter:
			QDatabaseInterface::search();
			break;

		default:
			break;
	}
	
	QMainWindow::keyReleaseEvent(e);
}

template<typename Type>
typename QDatabaseInterface<Type>::ButtonBitPair QDatabaseInterface<Type>::MakePair(const QString& name, Type bit)
{
	return std::pair(new QPushButton(name), static_cast<quint32>(bit));
}

template<typename Type>
void QDatabaseInterface<Type>::resetButtons(void)
{
	const auto style = QWidget::style();
	
	for (const auto& pr : QDatabaseInterface::bits)
	{
		if (pr.first->objectName() != "A")
		{
			pr.first->setObjectName("A");
			style->unpolish(pr.first);
		}
	}
	
	for (const auto& pr : QDatabaseInterface::multibits)
	{
		const auto name = pr.first->objectName();
		
		if (name.size() != 1u)
		{
			pr.first->setObjectName(name.at(0u));
			style->unpolish(pr.first);
		}
	}
}

template<typename Type>
void QDatabaseInterface<Type>::search(void)
{	
	if (!QDatabaseInterfaceIntermediary::keepListButton->isChecked())
	{
		const auto total = QDatabaseInterface::spellOrPowerList.size();
		QDatabaseInterface::searchResults.clear();
		QDatabaseInterface::searchResults.reserve(total);
		
		for (auto i = 0u; i < total; ++i)
			QDatabaseInterface::searchResults.push_back(i);
	}
	
	QDatabaseInterface::searchBitsets();
	QDatabaseInterface::searchStrings();
	QDatabaseInterfaceIntermediary::resultList->clear();
	
	if (!QDatabaseInterface::searchResults.empty())
	{
		for (const auto& u : QDatabaseInterface::searchResults)
		{
			const auto& [name, bset] = QDatabaseInterface::spellOrPowerList[u];
			const auto item = new QListWidgetItem(name);
			
			item->setBackground(QDatabaseInterface::Background(bset));
			item->setForeground(QDatabaseInterface::Foreground(bset));
			QDatabaseInterfaceIntermediary::resultList->addItem(item);
		}
	}
	
	const auto size = QDatabaseInterface::searchResults.size();
	QDatabaseInterfaceIntermediary::label->setText(QString::number(size) + " result" + (size > 1u ? "s" : "") + ".");
}

template<typename Type>
void QDatabaseInterface<Type>::searchBitsets(void)
{
	CustomBitset noneBitset;
	CustomBitset anyBitset;
	CustomBitset allBitset;
	
	for (const auto& [button, bit] : QDatabaseInterface::bits)
	{
		switch (button->objectName().size())
		{
			case 2:
				allBitset.set(bit);
				break;
			
			case 3:
				noneBitset.set(bit);
				break;
			
			case 4:
				anyBitset.set(bit);
				break;
			
			default:
				break;
		}
	}
	
	std::vector<CustomBitset> anyBitsets;
	
	for (const auto& [button, bset] : QDatabaseInterface::multibits)
	{
		switch (button->objectName().size())
		{
			case 2:
				anyBitsets.push_back(bset);
				break;
			
			case 3:
				noneBitset.set(bset);
				break;
			
			case 4:
				anyBitset.set(bset);
				break;
			
			default:
				break;
		}
	}
	
	if (anyBitset.any())
		anyBitsets.push_back(anyBitset);
	
	const auto noAllSearch = !allBitset.any();
	const auto noNoneSearch = !noneBitset.any();
	
	if (anyBitsets.empty() and noAllSearch and noNoneSearch)
		return;
	
	std::vector<quint32> newResults;
	
	for (const auto& u : QDatabaseInterface::searchResults)
	{
		const auto& bset = QDatabaseInterface::spellOrPowerList[u].second;
		
		if (noAllSearch or bset.all(allBitset))
		{
			if (noNoneSearch or bset.none(noneBitset))
			{
				bool match = true;
				
				for (const auto& b : anyBitsets)
					match = (match and bset.any(b));
				
				if (match)
					newResults.push_back(u);
			}
		}
	}
	
	newResults.swap(QDatabaseInterface::searchResults);
}

template<typename Type>
void QDatabaseInterface<Type>::searchPattern(const std::string& pattern, std::ifstream& file, bool exclude)
{
	std::vector<quint32> newResults;
	std::string line;
	auto count = 0u;
	
	file.clear();
	file.seekg(std::ios::beg);
	
	for (const auto& u : QDatabaseInterface::searchResults)
	{
		while (count < u)
		{
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			++count;
		}
		
		QDatabaseInterfaceIntermediary::GetLine(file, line);
		std::transform(line.cbegin(), line.cend(), line.begin(), ::tolower);
		const bool match = (line.find(pattern) != std::string::npos);
		
		if (match != exclude)
			newResults.push_back(count);
		
		++count;
	}
	
	newResults.swap(QDatabaseInterface::searchResults);
}

template<typename Type>
void QDatabaseInterface<Type>::searchStrings(void)
{
	auto namePattern = QDatabaseInterfaceIntermediary::nameLineEdit->text().toStdString();
	std::transform(namePattern.cbegin(), namePattern.cend(), namePattern.begin(), ::tolower);
	
	if (!namePattern.empty())
	{
		std::ifstream nameFile("files/" + QDatabaseInterfaceIntermediary::contentName.toStdString() + "Names");
		QDatabaseInterface::searchPattern(namePattern, nameFile, QDatabaseInterface::barNamesButton->isChecked());
	}
	
	auto lorePattern = QDatabaseInterfaceIntermediary::loreLineEdit->text().toStdString();
	std::transform(lorePattern.cbegin(), lorePattern.cend(), lorePattern.begin(), ::tolower);
	
	if (!lorePattern.empty())
	{
		std::ifstream loreFile("files/" + QDatabaseInterfaceIntermediary::contentName.toStdString() + "Texts");
		QDatabaseInterface::searchPattern(lorePattern, loreFile, QDatabaseInterface::barTextsButton->isChecked());
	}
}

template <typename Type>
void QDatabaseInterface<Type>::updateLoreFromList(QTextEdit* loreToChange, qint32 row) const
{
	if (row >= 0 and row < static_cast<qint32>(QDatabaseInterface::searchResults.size()))
	{
		const auto line = QDatabaseInterface::searchResults[row];
		QDatabaseInterface::updateLore(QDatabaseInterface::spellOrPowerList[line].first, loreToChange, line);
	}
}

template <typename Type>
void QDatabaseInterface<Type>::updateLore(const QString& name, QTextEdit* loreToChange, quint32 line) const
{
	std::ifstream infoFile("files/" + QDatabaseInterfaceIntermediary::contentName.toStdString() + "Infos");
	std::ifstream loreFile("files/" + QDatabaseInterfaceIntermediary::contentName.toStdString() + "Texts");
	
	infoFile.clear();
	infoFile.seekg(std::ios::beg);
	
	loreFile.clear();
	loreFile.seekg(std::ios::beg);
	
	for (auto i = 0u; i < line; ++i)
	{
		infoFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		loreFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	std::string str;
	getline(infoFile, str);
	
	const auto infoList = QString::fromStdString(str).split(';');
	auto qText = "<b>" + name + "</b><br>" + infoList.at(0) + "<br>";
	
	if (!infoList.at(1).isEmpty())
		qText += "<b>Core Classes:</b> " + infoList.at(1) + "<br>";

	if (!infoList.at(2).isEmpty())
		qText += "<b>Base Classes:</b> " + infoList.at(2) + "<br>";
	
	if (!infoList.at(3).isEmpty())
		qText += "<b>Prestige Classes:</b> " + infoList.at(3) + "<br>";
	
	if (!infoList.at(4).isEmpty())
		qText += "<b>Levels:</b> " + infoList.at(4) + "<br>";
	
	if (!infoList.at(5).isEmpty())
		qText += "<b>" + QDatabaseInterface::DomainOrMantleString + ":</b> " + infoList.at(5) + "<br>";
	
	qText += "<b>" + QDatabaseInterface::ComponentOrDisplayString + ":</b> ";
	qText += (infoList.at(6).isEmpty() ? "None" : infoList.at(6)) + "<br>";
	qText += "<b>" + QDatabaseInterface::CastingOrManifestingString + " Time:</b> " + infoList.at(7) + "<br>";
	qText += "<b>Range:</b> " + infoList.at(8) + "<br>";
	
	if (!infoList.at(9).isEmpty())
		qText += "<b>Effect:</b> " + infoList.at(9) + "<br>";
	
	if (!infoList.at(10).isEmpty())
		qText += "<b>Target:</b> " + infoList.at(10) + "<br>";
	
	if (!infoList.at(11).isEmpty())
		qText += "<b>Area:</b> " + infoList.at(11) + "<br>";
	
	qText += "<b>Duration:</b> " + infoList.at(12) + "<br>";
	
	if (!infoList.at(13).isEmpty())
		qText += "<b>Saving Throw:</b> " + infoList.at(13) + "<br>";
	
	if (!infoList.at(14).isEmpty())
		qText += "<b>" + QDatabaseInterface::ResistanceString + " Resistance:</b> " + infoList.at(14) + "<br>";
	
	qText += "<b>Source:</b> " + infoList.back();
	
	getline(loreFile, str);
	qText += QDatabaseInterfaceIntermediary::Process(str, QDatabaseInterfaceIntermediary::loreLineEdit->text());
	
	loreToChange->clear();
	loreToChange->setText(qText);
}

#endif
