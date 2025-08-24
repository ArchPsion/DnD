// Qt Libraries
#include <QTextTable>

// Custom Libraries
#include "Constants.hpp"
#include "QDatabaseWindow.hpp"

template<>
QColor QDatabaseWindow<PowerEnum>::Foreground(const CustomBitset& b)
{
	if (b.test(PowerEnum::CLAIRSENTIENCE))
		return QDatabaseWindow::ClairsentienceDivinationColor;
	else if (b.test(PowerEnum::METACREATIVITY))
		return QDatabaseWindow::MetacreativityConjurationColor;
	else if (b.test(PowerEnum::PSYCHOKINESIS))
		return QDatabaseWindow::PsychokinesisEvocationColor;
	else if (b.test(PowerEnum::PSYCHOMETABOLISM))
		return QDatabaseWindow::PsychometabolismTransmutationColor;
	else if (b.test(PowerEnum::PSYCHOPORTATION))
		return QDatabaseWindow::PsychoportationAbjurationColor;
	else if (b.test(PowerEnum::TELEPATHY))
		return QDatabaseWindow::TelepathyEnchantmentColor;
	
	return QColor(0, 0, 0);
}

template<>
QColor QDatabaseWindow<SpellEnum>::Foreground(const CustomBitset& b)
{
	if (b.test(SpellEnum::ABJURATION))
		return QDatabaseWindow::PsychoportationAbjurationColor;
	else if (b.test(SpellEnum::CONJURATION))
		return QDatabaseWindow::MetacreativityConjurationColor;
	else if (b.test(SpellEnum::DIVINATION))
		return QDatabaseWindow::ClairsentienceDivinationColor;
	else if (b.test(SpellEnum::ENCHANTMENT))
		return QDatabaseWindow::TelepathyEnchantmentColor;
	else if (b.test(SpellEnum::EVOCATION))
		return QDatabaseWindow::PsychokinesisEvocationColor;
	else if (b.test(SpellEnum::ILLUSION))
		return QDatabaseWindow::IllusionColor;
	else if (b.test(SpellEnum::NECROMANCY))
		return QDatabaseWindow::NecromancyColor;
	else if (b.test(SpellEnum::TRANSMUTATION))
		return QDatabaseWindow::PsychometabolismTransmutationColor;
	else if (b.test(SpellEnum::UNIVERSAL))
		return QDatabaseWindow::UniversalColor;
	
	return QColor(0, 0, 0);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Core Classes", this);
	const auto classLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Bard", SpellEnum::BARD),
					QDatabaseWindow::MakePair("Cleric", SpellEnum::CLERIC),
					QDatabaseWindow::MakePair("Druid", SpellEnum::DRUID),
					QDatabaseWindow::MakePair("Paladin", SpellEnum::PALADIN),
					QDatabaseWindow::MakePair("Ranger", SpellEnum::RANGER),
					QDatabaseWindow::MakePair("Sorcerer", SpellEnum::SORCERER),
					QDatabaseWindow::MakePair("Wizard", SpellEnum::WIZARD) };
	
	for (const auto& pr : bitPairs)
	{
		classLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	classBox->setLayout(classLayout);
	layout->addWidget(classBox, 0, 0, 1, 7);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Classes", this);
	const auto classLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Lurk", PowerEnum::LURK),
					QDatabaseWindow::MakePair("Psion", PowerEnum::PSION),
					QDatabaseWindow::MakePair("Psychic Rogue", PowerEnum::PSYCHIC_ROGUE),
					QDatabaseWindow::MakePair("Psychic Warrior", PowerEnum::PSYCHIC_WARRIOR) };
	
	for (const auto& pr : bitPairs)
	{
		classLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	classBox->setLayout(classLayout);
	layout->addWidget(classBox, 0, 0, 1, 4);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseSpecial(const QFont& font, QGridLayout* layout)
{	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Adept", SpellEnum::ADEPT),
				QDatabaseWindow::MakePair("Artificer", SpellEnum::ARTIFICER),
				QDatabaseWindow::MakePair("Beguiler", SpellEnum::BEGUILER),
				QDatabaseWindow::MakePair("Death Delver", SpellEnum::DEATH_DELVER),
				QDatabaseWindow::MakePair("Dread Necromancer", SpellEnum::DREAD_NECROMANCER),
				QDatabaseWindow::MakePair("Duskblade", SpellEnum::DUSKBLADE),
				QDatabaseWindow::MakePair("Healer", SpellEnum::HEALER),
				QDatabaseWindow::MakePair("Hexblade", SpellEnum::HEXBLADE),
				QDatabaseWindow::MakePair("Shugenja", SpellEnum::SHUGENJA),
				QDatabaseWindow::MakePair("Wu Jen", SpellEnum::WU_JEN) };
	
	const auto botPairs = {	QDatabaseWindow::MakePair("Assassin", SpellEnum::ASSASSIN),
					QDatabaseWindow::MakePair("Blackguard", SpellEnum::BLACKGUARD) };
	
	const auto betPairs = {	QDatabaseWindow::MakePair("Arcane Artifact", SpellEnum::ARCANE_ARTIFACT),
				QDatabaseWindow::MakePair("Corrupt", SpellEnum::CORRUPT),
				QDatabaseWindow::MakePair("Divine Artifact", SpellEnum::DIVINE_ARTIFACT),
				QDatabaseWindow::MakePair("Initiate", SpellEnum::INITIATE),
				QDatabaseWindow::MakePair("Oneiromancy", SpellEnum::ONEIROMANCY),
				QDatabaseWindow::MakePair("Sanctified", SpellEnum::SANCTIFIED) };
	
	const auto butPairs = {	QDatabaseWindow::MakePair("Air", SpellEnum::AIR_DOMAIN),
				QDatabaseWindow::MakePair("Abyss", SpellEnum::ABYSS_DOMAIN),
				QDatabaseWindow::MakePair("Animal", SpellEnum::ANIMAL_DOMAIN),
				QDatabaseWindow::MakePair("Arborea", SpellEnum::ARBOREA_DOMAIN),
				QDatabaseWindow::MakePair("Baator", SpellEnum::BAATOR_DOMAIN),
				QDatabaseWindow::MakePair("Balance", SpellEnum::BALANCE_DOMAIN),
				QDatabaseWindow::MakePair("Blackwater", SpellEnum::BLACKWATER_DOMAIN),
				QDatabaseWindow::MakePair("Cavern", SpellEnum::CAVERN_DOMAIN),
				QDatabaseWindow::MakePair("Celerity", SpellEnum::CELERITY_DOMAIN),
				QDatabaseWindow::MakePair("Celestia", SpellEnum::CELESTIA_DOMAIN),
				QDatabaseWindow::MakePair("Chaos", SpellEnum::CHAOS_DOMAIN),
				QDatabaseWindow::MakePair("Charm", SpellEnum::CHARM_DOMAIN),
				QDatabaseWindow::MakePair("Cold", SpellEnum::COLD_DOMAIN),
				QDatabaseWindow::MakePair("Community", SpellEnum::COMMUNITY_DOMAIN),
				QDatabaseWindow::MakePair("Competition", SpellEnum::COMPETITION_DOMAIN),
				QDatabaseWindow::MakePair("Corruption", SpellEnum::CORRUPTION_DOMAIN),
				QDatabaseWindow::MakePair("Courage", SpellEnum::COURAGE_DOMAIN),
				QDatabaseWindow::MakePair("Craft", SpellEnum::CRAFT_DOMAIN),
				QDatabaseWindow::MakePair("Creation", SpellEnum::CREATION_DOMAIN),
				QDatabaseWindow::MakePair("Darkness", SpellEnum::DARKNESS_DOMAIN),
				QDatabaseWindow::MakePair("Death", SpellEnum::DEATH_DOMAIN),
				QDatabaseWindow::MakePair("Deathbound", SpellEnum::DEATHBOUND_DOMAIN),
				QDatabaseWindow::MakePair("Demonic", SpellEnum::DEMONIC_DOMAIN),
				QDatabaseWindow::MakePair("Destruction", SpellEnum::DESTRUCTION_DOMAIN),
				QDatabaseWindow::MakePair("Diabolic", SpellEnum::DIABOLIC_DOMAIN),
				QDatabaseWindow::MakePair("Domination", SpellEnum::DOMINATION_DOMAIN),
				QDatabaseWindow::MakePair("Dragon", SpellEnum::DRAGON_DOMAIN),
				QDatabaseWindow::MakePair("Dream", SpellEnum::DREAM_DOMAIN),
				QDatabaseWindow::MakePair("Drow", SpellEnum::DROW_DOMAIN),
				QDatabaseWindow::MakePair("Dwarf", SpellEnum::DWARF_DOMAIN),
				QDatabaseWindow::MakePair("Earth", SpellEnum::EARTH_DOMAIN),
				QDatabaseWindow::MakePair("Elf", SpellEnum::ELF_DOMAIN),
				QDatabaseWindow::MakePair("Elysium", SpellEnum::ELYSIUM_DOMAIN),
				QDatabaseWindow::MakePair("Entropy", SpellEnum::ENTROPY_DOMAIN),
				QDatabaseWindow::MakePair("Envy", SpellEnum::ENVY_DOMAIN),
				QDatabaseWindow::MakePair("Evil", SpellEnum::EVIL_DOMAIN),
				QDatabaseWindow::MakePair("Family", SpellEnum::FAMILY_DOMAIN),
				QDatabaseWindow::MakePair("Fate", SpellEnum::FATE_DOMAIN),
				QDatabaseWindow::MakePair("Fire", SpellEnum::FIRE_DOMAIN),
				QDatabaseWindow::MakePair("Force", SpellEnum::FORCE_DOMAIN),
				QDatabaseWindow::MakePair("Fury", SpellEnum::FURY_DOMAIN),
				QDatabaseWindow::MakePair("Glory", SpellEnum::GLORY_DOMAIN),
				QDatabaseWindow::MakePair("Gluttony", SpellEnum::GLUTTONY_DOMAIN),
				QDatabaseWindow::MakePair("Good", SpellEnum::GOOD_DOMAIN),
				QDatabaseWindow::MakePair("Gnome", SpellEnum::GNOME_DOMAIN),
				QDatabaseWindow::MakePair("Greed", SpellEnum::GREED_DOMAIN),
				QDatabaseWindow::MakePair("Hades", SpellEnum::HADES_DOMAIN),
				QDatabaseWindow::MakePair("Halfling", SpellEnum::HALFLING_DOMAIN),
				QDatabaseWindow::MakePair("Hatred", SpellEnum::HATRED_DOMAIN),
				QDatabaseWindow::MakePair("Healing", SpellEnum::HEALING_DOMAIN),
				QDatabaseWindow::MakePair("Hunger", SpellEnum::HUNGER_DOMAIN),
				QDatabaseWindow::MakePair("Illusion", SpellEnum::ILLUSION_DOMAIN),
				QDatabaseWindow::MakePair("Incarnum", SpellEnum::INCARNUM_DOMAIN),
				QDatabaseWindow::MakePair("Inquisition", SpellEnum::INQUISITION_DOMAIN),
				QDatabaseWindow::MakePair("Knowledge", SpellEnum::KNOWLEDGE_DOMAIN),
				QDatabaseWindow::MakePair("Law", SpellEnum::LAW_DOMAIN),
				QDatabaseWindow::MakePair("Liberation", SpellEnum::LIBERATION_DOMAIN),
				QDatabaseWindow::MakePair("Limbo", SpellEnum::LIMBO_DOMAIN),
				QDatabaseWindow::MakePair("Luck", SpellEnum::LUCK_DOMAIN),
				QDatabaseWindow::MakePair("Lust", SpellEnum::LUST_DOMAIN),
				QDatabaseWindow::MakePair("Magic", SpellEnum::MAGIC_DOMAIN),
				QDatabaseWindow::MakePair("Madness", SpellEnum::MADNESS_DOMAIN),
				QDatabaseWindow::MakePair("Mechanus", SpellEnum::MECHANUS_DOMAIN),
				QDatabaseWindow::MakePair("Mentalism", SpellEnum::MENTALISM_DOMAIN),
				QDatabaseWindow::MakePair("Metal", SpellEnum::METAL_DOMAIN),
				QDatabaseWindow::MakePair("Mind", SpellEnum::MIND_DOMAIN),
				QDatabaseWindow::MakePair("Moon", SpellEnum::MOON_DOMAIN),
				QDatabaseWindow::MakePair("Mysticism", SpellEnum::MYSTICISM_DOMAIN),
				QDatabaseWindow::MakePair("Nobility", SpellEnum::NOBILITY_DOMAIN),
				QDatabaseWindow::MakePair("Ocean", SpellEnum::OCEAN_DOMAIN),
				QDatabaseWindow::MakePair("Ooze", SpellEnum::OOZE_DOMAIN),
				QDatabaseWindow::MakePair("Oracle", SpellEnum::ORACLE_DOMAIN),
				QDatabaseWindow::MakePair("Orc", SpellEnum::ORC_DOMAIN),
				QDatabaseWindow::MakePair("Pact", SpellEnum::PACT_DOMAIN),
				QDatabaseWindow::MakePair("Pestilence", SpellEnum::PESTILENCE_DOMAIN),
				QDatabaseWindow::MakePair("Planning", SpellEnum::PLANNING_DOMAIN),
				QDatabaseWindow::MakePair("Plant", SpellEnum::PLANT_DOMAIN),
				QDatabaseWindow::MakePair("Portal", SpellEnum::PORTAL_DOMAIN),
				QDatabaseWindow::MakePair("Pride", SpellEnum::PRIDE_DOMAIN),
				QDatabaseWindow::MakePair("Protection", SpellEnum::PROTECTION_DOMAIN),
				QDatabaseWindow::MakePair("Purification", SpellEnum::PURIFICATION_DOMAIN),
				QDatabaseWindow::MakePair("Renewal", SpellEnum::RENEWAL_DOMAIN),
				QDatabaseWindow::MakePair("Repose", SpellEnum::REPOSE_DOMAIN),
				QDatabaseWindow::MakePair("Retribution", SpellEnum::RETRIBUTION_DOMAIN),
				QDatabaseWindow::MakePair("Revered Ancestor", SpellEnum::REVERED_ANCESTOR_DOMAIN),
				QDatabaseWindow::MakePair("Rune", SpellEnum::RUNE_DOMAIN),
				QDatabaseWindow::MakePair("Sand", SpellEnum::SAND_DOMAIN),
				QDatabaseWindow::MakePair("Scalykind", SpellEnum::SCALYKIND_DOMAIN),
				QDatabaseWindow::MakePair("Seafolk", SpellEnum::SEAFOLK_DOMAIN),
				QDatabaseWindow::MakePair("Slime", SpellEnum::SLIME_DOMAIN),
				QDatabaseWindow::MakePair("Sloth", SpellEnum::SLOTH_DOMAIN),
				QDatabaseWindow::MakePair("Spell", SpellEnum::SPELL_DOMAIN),
				QDatabaseWindow::MakePair("Spider", SpellEnum::SPIDER_DOMAIN),
				QDatabaseWindow::MakePair("Spite", SpellEnum::SPITE_DOMAIN),
				QDatabaseWindow::MakePair("Storm", SpellEnum::STORM_DOMAIN),
				QDatabaseWindow::MakePair("Strength", SpellEnum::STRENGTH_DOMAIN),
				QDatabaseWindow::MakePair("Suffering", SpellEnum::SUFFERING_DOMAIN),
				QDatabaseWindow::MakePair("Summer", SpellEnum::SUMMER_DOMAIN),
				QDatabaseWindow::MakePair("Summoner", SpellEnum::SUMMONER_DOMAIN),
				QDatabaseWindow::MakePair("Sun", SpellEnum::SUN_DOMAIN),
				QDatabaseWindow::MakePair("Temptation", SpellEnum::TEMPTATION_DOMAIN),
				QDatabaseWindow::MakePair("Thirst", SpellEnum::THIRST_DOMAIN),
				QDatabaseWindow::MakePair("Time", SpellEnum::TIME_DOMAIN),
				QDatabaseWindow::MakePair("Trade", SpellEnum::TRADE_DOMAIN),
				QDatabaseWindow::MakePair("Transformation", SpellEnum::TRANSFORMATION_DOMAIN),
				QDatabaseWindow::MakePair("Travel", SpellEnum::TRAVEL_DOMAIN),
				QDatabaseWindow::MakePair("Trickery", SpellEnum::TRICKERY_DOMAIN),
				QDatabaseWindow::MakePair("Truth", SpellEnum::TRUTH_DOMAIN),
				QDatabaseWindow::MakePair("Tyranny", SpellEnum::TYRANNY_DOMAIN),
				QDatabaseWindow::MakePair("Undeath", SpellEnum::UNDEATH_DOMAIN),
				QDatabaseWindow::MakePair("Vile Darkness", SpellEnum::VILE_DARKNESS_DOMAIN),
				QDatabaseWindow::MakePair("War", SpellEnum::WAR_DOMAIN),
				QDatabaseWindow::MakePair("Warforged", SpellEnum::WARFORGED_DOMAIN),
				QDatabaseWindow::MakePair("Water", SpellEnum::WATER_DOMAIN),
				QDatabaseWindow::MakePair("Wealth", SpellEnum::WEALTH_DOMAIN),
				QDatabaseWindow::MakePair("Windstorm", SpellEnum::WINDSTORM_DOMAIN),
				QDatabaseWindow::MakePair("Wrath", SpellEnum::WRATH_DOMAIN) };
	
	const auto baseClassButton = new QPushButton("Base Classes");
	QDatabaseWindow::multibits.emplace_back(baseClassButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(bitPairs, "Base Classes", font, baseClassButton, QDatabaseWindow::multibits.back().second, 5);
	
	const auto prestigeClassButton = new QPushButton("Prestige Classes");
	QDatabaseWindow::multibits.emplace_back(prestigeClassButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(botPairs, "Prestige Classes", font, prestigeClassButton, QDatabaseWindow::multibits.back().second, 4);
	
	const auto domainButton = new QPushButton("Domains");
	QDatabaseWindow::multibits.emplace_back(domainButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(butPairs, "Domains", font, domainButton, QDatabaseWindow::multibits.back().second, 10);
	
	const auto otherButton = new QPushButton("Other");
	QDatabaseWindow::multibits.emplace_back(otherButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(betPairs, "Special", font, otherButton, QDatabaseWindow::multibits.back().second, 3);
	
	const auto specialBox = new QGroupBox("Special", this);
	const auto specialLayout = new QGridLayout();
	
	const auto specialButtons = { baseClassButton, prestigeClassButton, domainButton, otherButton };
	auto count = 0;
	
	for (const auto& button : specialButtons)
	{
		specialLayout->addWidget(button, count/2, count % 2);
		button->setObjectName("A");
		button->setFont(font);
		++count;
		
		QObject::connect(button, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	specialBox->setLayout(specialLayout);
	layout->addWidget(specialBox, 1, 0, 2, 2);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseSpecial(const QFont& font, QGridLayout* layout)
{
	const auto specialBox = new QGroupBox("Special", this);
	const auto specialLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Body Leech", PowerEnum::BODY_LEECH),
				QDatabaseWindow::MakePair("Egoist", PowerEnum::EGOIST),
				QDatabaseWindow::MakePair("Kineticist", PowerEnum::KINETICIST),
				QDatabaseWindow::MakePair("Nomad", PowerEnum::NOMAD),
				QDatabaseWindow::MakePair("Seer", PowerEnum::SEER),
				QDatabaseWindow::MakePair("Shaper", PowerEnum::SHAPER),
				QDatabaseWindow::MakePair("Telepath", PowerEnum::TELEPATH) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		specialLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseWindow::MakePair("Air", PowerEnum::AIR_MANTLE),
				QDatabaseWindow::MakePair("Chaos", PowerEnum::CHAOS_MANTLE),
				QDatabaseWindow::MakePair("Communication", PowerEnum::COMMUNICATION_MANTLE),
				QDatabaseWindow::MakePair("Conflict", PowerEnum::CONFLICT_MANTLE),
				QDatabaseWindow::MakePair("Consumption", PowerEnum::CONSUMPTION_MANTLE),
				QDatabaseWindow::MakePair("Corruption and Madness", PowerEnum::CORRUPTION_AND_MADNESS_MANTLE),
				QDatabaseWindow::MakePair("Creation", PowerEnum::CREATION_MANTLE),
				QDatabaseWindow::MakePair("Death", PowerEnum::DEATH_MANTLE),
				QDatabaseWindow::MakePair("Deception", PowerEnum::DECEPTION_MANTLE),
				QDatabaseWindow::MakePair("Destruction", PowerEnum::DESTRUCTION_MANTLE),
				QDatabaseWindow::MakePair("Earth", PowerEnum::EARTH_MANTLE),
				QDatabaseWindow::MakePair("Elements", PowerEnum::ELEMENTS_MANTLE),
				QDatabaseWindow::MakePair("Energy", PowerEnum::ENERGY_MANTLE),
				QDatabaseWindow::MakePair("Evil", PowerEnum::EVIL_MANTLE),
				QDatabaseWindow::MakePair("Fate", PowerEnum::FATE_MANTLE),
				QDatabaseWindow::MakePair("Fire", PowerEnum::FIRE_MANTLE),
				QDatabaseWindow::MakePair("Force", PowerEnum::FORCE_MANTLE),
				QDatabaseWindow::MakePair("Freedom", PowerEnum::FREEDOM_MANTLE),
				QDatabaseWindow::MakePair("Good", PowerEnum::GOOD_MANTLE),
				QDatabaseWindow::MakePair("Guardian", PowerEnum::GUARDIAN_MANTLE),
				QDatabaseWindow::MakePair("Justice", PowerEnum::JUSTICE_MANTLE),
				QDatabaseWindow::MakePair("Knowledge", PowerEnum::KNOWLEDGE_MANTLE),
				QDatabaseWindow::MakePair("Law", PowerEnum::LAW_MANTLE),
				QDatabaseWindow::MakePair("Life", PowerEnum::LIFE_MANTLE),
				QDatabaseWindow::MakePair("Light and Darkness", PowerEnum::LIGHT_AND_DARKNESS_MANTLE),
				QDatabaseWindow::MakePair("Magic", PowerEnum::MAGIC_MANTLE),
				QDatabaseWindow::MakePair("Mental Power", PowerEnum::MENTAL_POWER_MANTLE),
				QDatabaseWindow::MakePair("Natural World", PowerEnum::NATURAL_WORLD_MANTLE),
				QDatabaseWindow::MakePair("Pain and Suffering", PowerEnum::PAIN_AND_SUFFERING_MANTLE),
				QDatabaseWindow::MakePair("Physical Power", PowerEnum::PHYSICAL_POWER_MANTLE),
				QDatabaseWindow::MakePair("Plane", PowerEnum::PLANE_MANTLE),
				QDatabaseWindow::MakePair("Repose", PowerEnum::REPOSE_MANTLE),
				QDatabaseWindow::MakePair("Time", PowerEnum::TIME_MANTLE),
				QDatabaseWindow::MakePair("Water", PowerEnum::WATER_MANTLE) };
	
	const auto mantleButton = new QPushButton("Mantles");
	QDatabaseWindow::multibits.emplace_back(mantleButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(butPairs, "Mantles", font, mantleButton, QDatabaseWindow::multibits.back().second, 5);
	
	specialLayout->addWidget(mantleButton);
	mantleButton->setObjectName("A");
	mantleButton->setFont(font);
	QObject::connect(mantleButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	specialBox->setLayout(specialLayout);
	layout->addWidget(specialBox, 1, 0, 4, 2);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto arcaneButton = new QPushButton("Arcane");
	QDatabaseWindow::multibits.emplace_back(arcaneButton, CustomBitset());
	
	auto& arcaneBitset = QDatabaseWindow::multibits.back().second;
	arcaneBitset.set(SpellEnum::BARD);
	arcaneBitset.set(SpellEnum::SORCERER);
	arcaneBitset.set(SpellEnum::WIZARD);
	
	arcaneBitset.set(SpellEnum::ASSASSIN);
	arcaneBitset.set(SpellEnum::ARCANE_ARTIFACT);
	arcaneBitset.set(SpellEnum::BEGUILER);
	arcaneBitset.set(SpellEnum::CORRUPT);
	arcaneBitset.set(SpellEnum::DREAD_NECROMANCER);
	arcaneBitset.set(SpellEnum::DUSKBLADE);
	arcaneBitset.set(SpellEnum::HEXBLADE);
	arcaneBitset.set(SpellEnum::ONEIROMANCY);
	arcaneBitset.set(SpellEnum::SANCTIFIED);
	arcaneBitset.set(SpellEnum::WU_JEN);
	
	const auto divineButton = new QPushButton("Divine");
	QDatabaseWindow::multibits.emplace_back(divineButton, CustomBitset());
	
	auto& divineBitset = QDatabaseWindow::multibits.back().second;
	divineBitset.set(SpellEnum::CLERIC);
	divineBitset.set(SpellEnum::DRUID);
	divineBitset.set(SpellEnum::PALADIN);
	divineBitset.set(SpellEnum::RANGER);
	
	divineBitset.set(SpellEnum::ADEPT);
	divineBitset.set(SpellEnum::BLACKGUARD);
	divineBitset.set(SpellEnum::CORRUPT);
	divineBitset.set(SpellEnum::DEATH_DELVER);
	divineBitset.set(SpellEnum::DIVINE_ARTIFACT);
	divineBitset.set(SpellEnum::HEALER);
	divineBitset.set(SpellEnum::INITIATE);
	divineBitset.set(SpellEnum::ONEIROMANCY);
	divineBitset.set(SpellEnum::SANCTIFIED);
	divineBitset.set(SpellEnum::SHUGENJA);
	
	for (const auto& [btn, bset] : QDatabaseWindow::multibits)
	{
		if (btn->text() == "Domains")
		{
			divineBitset.set(bset);
			break;
		}
	}
	
	const auto infusionButton = new QPushButton("Infusion");
	QDatabaseWindow::multibits.emplace_back(infusionButton, CustomBitset());
	
	auto& infusionBitset = QDatabaseWindow::multibits.back().second;
	infusionBitset.set(SpellEnum::ARTIFICER);
	
	const auto featureBox = new QGroupBox("Types", this);
	const auto featureLayout = new QHBoxLayout();
	const auto featureButtons = { arcaneButton, divineButton, infusionButton };
	
	for (const auto& button : featureButtons)
	{
		featureLayout->addWidget(button);
		button->setObjectName("A");
		button->setFont(font);
		
		QObject::connect(button, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	}
	
	featureBox->setLayout(featureLayout);
	layout->addWidget(featureBox, 0, 7, 1, 3);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto featureBox = new QGroupBox("Features", this);
	const auto featureLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Augment", PowerEnum::AUGMENT),
					QDatabaseWindow::MakePair("Experience", PowerEnum::EXPERIENCE) };
	
	for (const auto& pr : bitPairs)
	{
		featureLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	featureBox->setLayout(featureLayout);
	layout->addWidget(featureBox, 1, 2, 1, 2);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseSchoolsOrDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto schoolBox = new QGroupBox("Schools", this);
	const auto schoolLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Abjuration", SpellEnum::ABJURATION),
				QDatabaseWindow::MakePair("Conjuration", SpellEnum::CONJURATION),
				QDatabaseWindow::MakePair("Divination", SpellEnum::DIVINATION),
				QDatabaseWindow::MakePair("Enchantment", SpellEnum::ENCHANTMENT),
				QDatabaseWindow::MakePair("Evocation", SpellEnum::EVOCATION),
				QDatabaseWindow::MakePair("Illusion", SpellEnum::ILLUSION),
				QDatabaseWindow::MakePair("Necromancy", SpellEnum::NECROMANCY),
				QDatabaseWindow::MakePair("Transmutation", SpellEnum::TRANSMUTATION),
				QDatabaseWindow::MakePair("Universal", SpellEnum::UNIVERSAL) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		schoolLayout->addWidget(pr.first, count/3, count % 3);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	schoolBox->setLayout(schoolLayout);
	layout->addWidget(schoolBox, 1, 2, 3, 3);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseSchoolsOrDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto disciplineBox = new QGroupBox("Disciplines", this);
	const auto disciplineLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Clairsentience", PowerEnum::CLAIRSENTIENCE),
				QDatabaseWindow::MakePair("Metacreativity", PowerEnum::METACREATIVITY),
				QDatabaseWindow::MakePair("Psychokinesis", PowerEnum::PSYCHOKINESIS),
				QDatabaseWindow::MakePair("Psychometabolism", PowerEnum::PSYCHOMETABOLISM),
				QDatabaseWindow::MakePair("Psychoportation", PowerEnum::PSYCHOPORTATION),
				QDatabaseWindow::MakePair("Telepathy", PowerEnum::TELEPATHY) };
	
	for (const auto& pr : bitPairs)
	{
		disciplineLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	disciplineBox->setLayout(disciplineLayout);
	layout->addWidget(disciplineBox, 0, 4, 1, 6);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseSubschoolsOrSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subschoolBox = new QGroupBox("Subschools", this);
	const auto subschoolLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Calling", SpellEnum::CALLING),
				QDatabaseWindow::MakePair("Charm", SpellEnum::CHARM),
				QDatabaseWindow::MakePair("Compulsion", SpellEnum::COMPULSION),
				QDatabaseWindow::MakePair("Creation", SpellEnum::CREATION),
				QDatabaseWindow::MakePair("Figment", SpellEnum::FIGMENT),
				QDatabaseWindow::MakePair("Glamer", SpellEnum::GLAMER),
				QDatabaseWindow::MakePair("Healing", SpellEnum::HEALING),
				QDatabaseWindow::MakePair("Pattern", SpellEnum::PATTERN),
				QDatabaseWindow::MakePair("Phantasm", SpellEnum::PHANTASM),
				QDatabaseWindow::MakePair("Polymorph", SpellEnum::POLYMORPH),
				QDatabaseWindow::MakePair("Scrying", SpellEnum::SCRYING),
				QDatabaseWindow::MakePair("Shadow", SpellEnum::SHADOW),
				QDatabaseWindow::MakePair("Summoning", SpellEnum::SUMMONING),
				QDatabaseWindow::MakePair("Teleportation", SpellEnum::TELEPORTATION) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		subschoolLayout->addWidget(pr.first, count/5, count % 5);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	subschoolBox->setLayout(subschoolLayout);
	layout->addWidget(subschoolBox, 1, 5, 3, 5);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseSubschoolsOrSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subdisciplineBox = new QGroupBox("Subdisciplines", this);
	const auto subdisciplineLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Charm", PowerEnum::CHARM),
				QDatabaseWindow::MakePair("Compulsion", PowerEnum::COMPULSION),
				QDatabaseWindow::MakePair("Creation", PowerEnum::CREATION),
				QDatabaseWindow::MakePair("Healing", PowerEnum::HEALING),
				QDatabaseWindow::MakePair("Scrying", PowerEnum::SCRYING),
				QDatabaseWindow::MakePair("Teleportation", PowerEnum::TELEPORTATION) };
	
	for (const auto& pr : bitPairs)
	{
		subdisciplineLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	subdisciplineBox->setLayout(subdisciplineLayout);
	layout->addWidget(subdisciplineBox, 1, 4, 1, 6);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseMaterialsOrDisplays(const QFont& font, QGridLayout* layout)
{
	const auto materialBox = new QGroupBox("Materials", this);
	const auto materialLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Focus", SpellEnum::FOCUS),
				QDatabaseWindow::MakePair("Divine Focus", SpellEnum::DIVINE_FOCUS),
				QDatabaseWindow::MakePair("Verbal", SpellEnum::VERBAL),
				QDatabaseWindow::MakePair("Somatic", SpellEnum::SOMATIC),
				QDatabaseWindow::MakePair("Material", SpellEnum::MATERIAL),
				QDatabaseWindow::MakePair("Gold", SpellEnum::GOLD),
				QDatabaseWindow::MakePair("Experience", SpellEnum::EXPERIENCE) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		materialLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseWindow::MakePair("Alignment", SpellEnum::ALIGNMENT),
				QDatabaseWindow::MakePair("Corruption", SpellEnum::CORRUPT),
				QDatabaseWindow::MakePair("Dragonmark", SpellEnum::DRAGONMARK),
				QDatabaseWindow::MakePair("Essentia", SpellEnum::ESSENTIA),
				QDatabaseWindow::MakePair("Racial", SpellEnum::RACIAL),
				QDatabaseWindow::MakePair("Sacrifice", SpellEnum::SANCTIFIED),
				QDatabaseWindow::MakePair("Verbal (Bard only)", SpellEnum::VERBAL_BARD) };
	
	const auto otherComponentButton = new QPushButton("Other");
	QDatabaseWindow::multibits.emplace_back(otherComponentButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(butPairs, "Other Components", font, otherComponentButton, QDatabaseWindow::multibits.back().second, 10);
	
	materialLayout->addWidget(otherComponentButton, 3, 1);
	otherComponentButton->setObjectName("A");
	otherComponentButton->setFont(font);
	QObject::connect(otherComponentButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	materialBox->setLayout(materialLayout);
	layout->addWidget(materialBox, 3, 0, 4, 2);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseMaterialsOrDisplays(const QFont& font, QGridLayout* layout)
{
	const auto displayBox = new QGroupBox("Displays", this);
	const auto displayLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Auditory", PowerEnum::AUDITORY),
				QDatabaseWindow::MakePair("Material", PowerEnum::MATERIAL),
				QDatabaseWindow::MakePair("Mental", PowerEnum::MENTAL),
				QDatabaseWindow::MakePair("Olfactory", PowerEnum::OLFACTORY),
				QDatabaseWindow::MakePair("Visual", PowerEnum::VISUAL) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		displayLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	displayBox->setLayout(displayLayout);
	layout->addWidget(displayBox, 2, 2, 3, 2);
}

template<>
qint32 QDatabaseWindow<SpellEnum>::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", this);
	const auto descriptorLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Acid", SpellEnum::ACID),
				QDatabaseWindow::MakePair("Air", SpellEnum::AIR),
				QDatabaseWindow::MakePair("Chaotic", SpellEnum::CHAOTIC),
				QDatabaseWindow::MakePair("Cold", SpellEnum::COLD),
				QDatabaseWindow::MakePair("Darkness", SpellEnum::DARKNESS),
				QDatabaseWindow::MakePair("Death", SpellEnum::DEATH),
				QDatabaseWindow::MakePair("Earth", SpellEnum::EARTH),
				QDatabaseWindow::MakePair("Electricity", SpellEnum::ELECTRICITY),
				QDatabaseWindow::MakePair("Evil", SpellEnum::EVIL),
				QDatabaseWindow::MakePair("Fear", SpellEnum::FEAR),
				QDatabaseWindow::MakePair("Fire", SpellEnum::FIRE),
				QDatabaseWindow::MakePair("Force", SpellEnum::FORCE),
				QDatabaseWindow::MakePair("Good", SpellEnum::GOOD),
				QDatabaseWindow::MakePair("Incarnum", SpellEnum::INCARNUM),
				QDatabaseWindow::MakePair("Language", SpellEnum::LANGUAGE_DEPENDENT),
				QDatabaseWindow::MakePair("Lawful", SpellEnum::LAWFUL),
				QDatabaseWindow::MakePair("Light", SpellEnum::LIGHT),
				QDatabaseWindow::MakePair("Mind-Affecting", SpellEnum::MIND_AFFECTING),
				QDatabaseWindow::MakePair("Sonic", SpellEnum::SONIC),
				QDatabaseWindow::MakePair("Water", SpellEnum::WATER) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		descriptorLayout->addWidget(pr.first, count/7, count % 7);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	const auto butPairs = { QDatabaseWindow::MakePair("Investiture", SpellEnum::INVESTITURE),
				QDatabaseWindow::MakePair("Mindset", SpellEnum::MINDSET) };
	
	const auto otherDescriptorButton = new QPushButton("Other");
	QDatabaseWindow::multibits.emplace_back(otherDescriptorButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(butPairs, "Other Descriptors", font, otherDescriptorButton, QDatabaseWindow::multibits.back().second, 2);
	
	descriptorLayout->addWidget(otherDescriptorButton, 2, 5);
	otherDescriptorButton->setObjectName("A");
	otherDescriptorButton->setFont(font);
	QObject::connect(otherDescriptorButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	descriptorBox->setLayout(descriptorLayout);
	layout->addWidget(descriptorBox, 4, 2, 3, 7);
	return 7;
}

template<>
qint32 QDatabaseWindow<PowerEnum>::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", this);
	const auto descriptorLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("Acid", PowerEnum::ACID),
				QDatabaseWindow::MakePair("Cold", PowerEnum::COLD),
				QDatabaseWindow::MakePair("Darkness", PowerEnum::DARKNESS),
				QDatabaseWindow::MakePair("Death", PowerEnum::DEATH),
				QDatabaseWindow::MakePair("Electricity", PowerEnum::ELECTRICITY),
				QDatabaseWindow::MakePair("Evil", PowerEnum::EVIL),
				QDatabaseWindow::MakePair("Fear", PowerEnum::FEAR),
				QDatabaseWindow::MakePair("Fire", PowerEnum::FIRE),
				QDatabaseWindow::MakePair("Force", PowerEnum::FORCE),
				QDatabaseWindow::MakePair("Good", PowerEnum::GOOD),
				QDatabaseWindow::MakePair("Language", PowerEnum::LANGUAGE_DEPENDENT),
				QDatabaseWindow::MakePair("Light", PowerEnum::LIGHT),
				QDatabaseWindow::MakePair("Mind-Affecting", PowerEnum::MIND_AFFECTING),
				QDatabaseWindow::MakePair("Shadow", PowerEnum::SHADOW),
				QDatabaseWindow::MakePair("Sonic", PowerEnum::SONIC) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		descriptorLayout->addWidget(pr.first, count/5, count % 5);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	descriptorBox->setLayout(descriptorLayout);
	layout->addWidget(descriptorBox, 2, 4, 3, 5);
	return 5;
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseSources(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto sourceBox = new QGroupBox("Sources", this);
	const auto sourceLayout = new QVBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("PHB", SpellEnum::PLAYERS_HANDBOOK),
				QDatabaseWindow::MakePair("SpC", SpellEnum::SPELL_COMPENDIUM) };
	
	for (const auto& pr : bitPairs)
	{
		sourceLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseWindow::MakePair("An", SpellEnum::ANAUROCH_EMPIRE_OF_SHADE),
				QDatabaseWindow::MakePair("CCha", SpellEnum::COMPLETE_CHAMPION),
				QDatabaseWindow::MakePair("Ci", SpellEnum::CITYSCAPE),
				QDatabaseWindow::MakePair("CMge", SpellEnum::COMPLETE_MAGE),
				QDatabaseWindow::MakePair("CoS", SpellEnum::CITY_OF_STORMREACH),
				QDatabaseWindow::MakePair("CoV", SpellEnum::CHAMPIONS_OF_VALOR),
				QDatabaseWindow::MakePair("CR", SpellEnum::CHAMPIONS_OF_RUIN),
				QDatabaseWindow::MakePair("CSco", SpellEnum::COMPLETE_SCOUNDREL),
				QDatabaseWindow::MakePair("CSW", SpellEnum::CITY_OF_SPLENDORS_WATERDEEP),
				QDatabaseWindow::MakePair("DoE", SpellEnum::DRAGONS_OF_EBERRON),
				QDatabaseWindow::MakePair("DoF", SpellEnum::DRAGONS_OF_FAERUN),
				QDatabaseWindow::MakePair("Dmkd", SpellEnum::DRAGONMARKED),
				QDatabaseWindow::MakePair("DrM", SpellEnum::DRAGON_MAGIC),
				QDatabaseWindow::MakePair("DrU", SpellEnum::DROW_OF_THE_UNDERDARK),
				QDatabaseWindow::MakePair("EDP", SpellEnum::EXPEDITION_TO_DEMONWEB_PITS),
				QDatabaseWindow::MakePair("EU", SpellEnum::EXPEDITION_TO_UNDERMOUNTAIN),
				QDatabaseWindow::MakePair("FoE", SpellEnum::FAITHS_OF_EBERRON),
				QDatabaseWindow::MakePair("FC1", SpellEnum::FIENDISH_CODEX_I),
				QDatabaseWindow::MakePair("FC2", SpellEnum::FIENDISH_CODEX_II),
				QDatabaseWindow::MakePair("FN", SpellEnum::FIVE_NATIONS),
				QDatabaseWindow::MakePair("FW", SpellEnum::FORGE_OF_WAR),
				QDatabaseWindow::MakePair("HB", SpellEnum::HEROES_OF_BATTLE),
				QDatabaseWindow::MakePair("HH", SpellEnum::HEROES_OF_HORROR),
				QDatabaseWindow::MakePair("LoM", SpellEnum::LORDS_OF_MADNESS),
				QDatabaseWindow::MakePair("MM4", SpellEnum::MONSTER_MANUAL_IV),
				QDatabaseWindow::MakePair("MoE", SpellEnum::MAGIC_OF_EBERRON),
				QDatabaseWindow::MakePair("MoI", SpellEnum::MAGIC_OF_INCARNUM),
				QDatabaseWindow::MakePair("PGE", SpellEnum::PLAYERS_GUIDE_TO_EBERRON),
				QDatabaseWindow::MakePair("PH2", SpellEnum::PLAYERS_HANDBOOK_II),
				QDatabaseWindow::MakePair("PoF", SpellEnum::POWER_OF_FAERUN),
				QDatabaseWindow::MakePair("Rav", SpellEnum::EXPEDITION_TO_CASTLE_RAVENLOFT),
				QDatabaseWindow::MakePair("RDr", SpellEnum::RACES_OF_THE_DRAGON),
				QDatabaseWindow::MakePair("RE", SpellEnum::RACES_OF_EBERRON),
				QDatabaseWindow::MakePair("Sa", SpellEnum::SANDSTORM),
				QDatabaseWindow::MakePair("SoS", SpellEnum::SECRETS_OF_SARLONA),
				QDatabaseWindow::MakePair("SoX", SpellEnum::SECRETS_OF_XENDRIK),
				QDatabaseWindow::MakePair("Sto", SpellEnum::STORMWRACK),
				QDatabaseWindow::MakePair("WL", SpellEnum::WEAPONS_OF_LEGACY) };
	
	const auto otherSourceButton = new QPushButton("Other");
	QDatabaseWindow::multibits.emplace_back(otherSourceButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(butPairs, "Other Sources", font, otherSourceButton, QDatabaseWindow::multibits.back().second, 4);
	
	sourceLayout->addWidget(otherSourceButton);
	otherSourceButton->setObjectName("A");
	otherSourceButton->setFont(font);
	QObject::connect(otherSourceButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	sourceBox->setLayout(sourceLayout);
	layout->addWidget(sourceBox, delta - 3, 9, 3, 1);
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseSources(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto sourceBox = new QGroupBox("Sources", this);
	const auto sourceLayout = new QVBoxLayout();
	
	const auto bitPairs = {	QDatabaseWindow::MakePair("XPH", PowerEnum::EXPANDED_PSIONICS_HANDBOOK),
				QDatabaseWindow::MakePair("CPsi", PowerEnum::COMPLETE_PSIONIC) };
	
	for (const auto& pr : bitPairs)
	{
		sourceLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseWindow::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseWindow::MakePair("DrM", PowerEnum::DRAGON_MAGIC),
				QDatabaseWindow::MakePair("FoE", PowerEnum::FAITHS_OF_EBERRON),
				QDatabaseWindow::MakePair("Hyp", PowerEnum::HYPERCONSCIOUS),
				QDatabaseWindow::MakePair("MoE", PowerEnum::MAGIC_OF_EBERRON),
				QDatabaseWindow::MakePair("MoI", PowerEnum::MAGIC_OF_INCARNUM),
				QDatabaseWindow::MakePair("PGE", PowerEnum::PLAYERS_GUIDE_TO_EBERRON),
				QDatabaseWindow::MakePair("RDr", PowerEnum::RACES_OF_THE_DRAGON),
				QDatabaseWindow::MakePair("RW", PowerEnum::RACES_OF_THE_WILD),
				QDatabaseWindow::MakePair("SoS", PowerEnum::SECRETS_OF_SARLONA),
				QDatabaseWindow::MakePair("Sto", PowerEnum::STORMWRACK),
				QDatabaseWindow::MakePair("WL", PowerEnum::WEAPONS_OF_LEGACY),
				QDatabaseWindow::MakePair("Web", PowerEnum::WEB) };
	
	const auto otherSourceButton = new QPushButton("Other");
	QDatabaseWindow::multibits.emplace_back(otherSourceButton, CustomBitset());
	QDatabaseWindow::initialiseWindow(butPairs, "Other Sources", font, otherSourceButton, QDatabaseWindow::multibits.back().second, 4);
	
	sourceLayout->addWidget(otherSourceButton);
	otherSourceButton->setObjectName("A");
	otherSourceButton->setFont(font);
	QObject::connect(otherSourceButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	sourceBox->setLayout(sourceLayout);
	layout->addWidget(sourceBox, delta - 3, 9, 3, 1);
}

template<>
void QDatabaseWindow<SpellEnum>::initialiseBars(const QFont& font, QGridLayout* layout, qint32 delta)
{
	layout->addWidget(QAbstractDatabaseWindow::nameLineEdit, delta + 8, 0, 1, 4);
	layout->addWidget(QAbstractDatabaseWindow::loreLineEdit, delta + 8, 4, 1, 5);
	
	QDatabaseWindow::RevisedBitset.set(SpellEnum::ANAUROCH_EMPIRE_OF_SHADE);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::CHAMPIONS_OF_RUIN);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::CHAMPIONS_OF_VALOR);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::CITY_OF_SPLENDORS_WATERDEEP);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::CITY_OF_STORMREACH);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::CITYSCAPE);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::COMPLETE_CHAMPION);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::COMPLETE_MAGE);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::COMPLETE_SCOUNDREL);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::DRAGON_MAGIC);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::DRAGONMARKED);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::DRAGONS_OF_EBERRON);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::DRAGONS_OF_FAERUN);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::DROW_OF_THE_UNDERDARK);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::EXPEDITION_TO_CASTLE_RAVENLOFT);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::EXPEDITION_TO_DEMONWEB_PITS);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::EXPEDITION_TO_UNDERMOUNTAIN);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::FAITHS_OF_EBERRON);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::FIENDISH_CODEX_I);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::FIENDISH_CODEX_II);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::FIVE_NATIONS);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::FORGE_OF_WAR);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::HEROES_OF_BATTLE);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::HEROES_OF_HORROR);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::LORDS_OF_MADNESS);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::MAGIC_OF_EBERRON);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::MONSTER_MANUAL_IV);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::MAGIC_OF_INCARNUM);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::PLAYERS_GUIDE_TO_EBERRON);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::PLAYERS_HANDBOOK);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::PLAYERS_HANDBOOK_II);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::POWER_OF_FAERUN);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::RACES_OF_EBERRON);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::RACES_OF_THE_DRAGON);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::SANDSTORM);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::SECRETS_OF_SARLONA);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::SECRETS_OF_XENDRIK);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::SPELL_COMPENDIUM);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::STORMWRACK);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::WEAPONS_OF_LEGACY);
	QDatabaseWindow::RevisedBitset.set(SpellEnum::WEB35);
	
	const auto button35e = new QPushButton("3.5e");
	QDatabaseWindow::multibits.emplace_back(button35e, QDatabaseWindow::RevisedBitset);
	
	layout->addWidget(button35e, delta + 8, 9, 1, 1);
	button35e->setObjectName("B");
	button35e->setFont(font);
	
	QObject::connect(button35e, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
}

template<>
void QDatabaseWindow<PowerEnum>::initialiseBars(const QFont&, QGridLayout* layout, qint32 delta)
{
	QDatabaseWindow::RevisedBitset.set(PowerEnum::COMPLETE_PSIONIC);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::DRAGON_MAGIC);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::EXPANDED_PSIONICS_HANDBOOK);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::FAITHS_OF_EBERRON);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::HYPERCONSCIOUS);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::MAGIC_OF_EBERRON);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::MAGIC_OF_INCARNUM);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::PLAYERS_GUIDE_TO_EBERRON);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::RACES_OF_THE_DRAGON);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::RACES_OF_THE_WILD);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::SECRETS_OF_SARLONA);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::STORMWRACK);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::WEAPONS_OF_LEGACY);
	QDatabaseWindow::RevisedBitset.set(PowerEnum::WEB);
	
	layout->addWidget(QAbstractDatabaseWindow::nameLineEdit, delta + 8, 0, 1, 5);
	layout->addWidget(QAbstractDatabaseWindow::loreLineEdit, delta + 8, 5, 1, 5);
}
