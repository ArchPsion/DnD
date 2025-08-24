// Qt Libraries
#include <QTextTable>

// Custom Libraries
#include "Constants.hpp"
#include "QDatabaseInterface.hpp"

template<>
QColor QDatabaseInterface<PowerEnum>::Foreground(const CustomBitset& b)
{
	if (b.test(PowerEnum::CLAIRSENTIENCE))
		return QDatabaseInterface::ClairsentienceDivinationColor;
	else if (b.test(PowerEnum::METACREATIVITY))
		return QDatabaseInterface::MetacreativityConjurationColor;
	else if (b.test(PowerEnum::PSYCHOKINESIS))
		return QDatabaseInterface::PsychokinesisEvocationColor;
	else if (b.test(PowerEnum::PSYCHOMETABOLISM))
		return QDatabaseInterface::PsychometabolismTransmutationColor;
	else if (b.test(PowerEnum::PSYCHOPORTATION))
		return QDatabaseInterface::PsychoportationAbjurationColor;
	else if (b.test(PowerEnum::TELEPATHY))
		return QDatabaseInterface::TelepathyEnchantmentColor;
	
	return QColor(0, 0, 0);
}

template<>
QColor QDatabaseInterface<SpellEnum>::Foreground(const CustomBitset& b)
{
	if (b.test(SpellEnum::ABJURATION))
		return QDatabaseInterface::PsychoportationAbjurationColor;
	else if (b.test(SpellEnum::CONJURATION))
		return QDatabaseInterface::MetacreativityConjurationColor;
	else if (b.test(SpellEnum::DIVINATION))
		return QDatabaseInterface::ClairsentienceDivinationColor;
	else if (b.test(SpellEnum::ENCHANTMENT))
		return QDatabaseInterface::TelepathyEnchantmentColor;
	else if (b.test(SpellEnum::EVOCATION))
		return QDatabaseInterface::PsychokinesisEvocationColor;
	else if (b.test(SpellEnum::ILLUSION))
		return QDatabaseInterface::IllusionColor;
	else if (b.test(SpellEnum::NECROMANCY))
		return QDatabaseInterface::NecromancyColor;
	else if (b.test(SpellEnum::TRANSMUTATION))
		return QDatabaseInterface::PsychometabolismTransmutationColor;
	else if (b.test(SpellEnum::UNIVERSAL))
		return QDatabaseInterface::UniversalColor;
	
	return QColor(0, 0, 0);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Core Classes", this);
	const auto classLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Bard", SpellEnum::BARD),
					QDatabaseInterface::MakePair("Cleric", SpellEnum::CLERIC),
					QDatabaseInterface::MakePair("Druid", SpellEnum::DRUID),
					QDatabaseInterface::MakePair("Paladin", SpellEnum::PALADIN),
					QDatabaseInterface::MakePair("Ranger", SpellEnum::RANGER),
					QDatabaseInterface::MakePair("Sorcerer", SpellEnum::SORCERER),
					QDatabaseInterface::MakePair("Wizard", SpellEnum::WIZARD) };
	
	for (const auto& pr : bitPairs)
	{
		classLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	classBox->setLayout(classLayout);
	layout->addWidget(classBox, 0, 0, 1, 7);
}

template<>
void QDatabaseInterface<PowerEnum>::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Classes", this);
	const auto classLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Lurk", PowerEnum::LURK),
					QDatabaseInterface::MakePair("Psion", PowerEnum::PSION),
					QDatabaseInterface::MakePair("Psychic Rogue", PowerEnum::PSYCHIC_ROGUE),
					QDatabaseInterface::MakePair("Psychic Warrior", PowerEnum::PSYCHIC_WARRIOR) };
	
	for (const auto& pr : bitPairs)
	{
		classLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	classBox->setLayout(classLayout);
	layout->addWidget(classBox, 0, 0, 1, 4);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseSpecial(const QFont& font, QGridLayout* layout)
{	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Adept", SpellEnum::ADEPT),
				QDatabaseInterface::MakePair("Artificer", SpellEnum::ARTIFICER),
				QDatabaseInterface::MakePair("Beguiler", SpellEnum::BEGUILER),
				QDatabaseInterface::MakePair("Death Delver", SpellEnum::DEATH_DELVER),
				QDatabaseInterface::MakePair("Dread Necromancer", SpellEnum::DREAD_NECROMANCER),
				QDatabaseInterface::MakePair("Duskblade", SpellEnum::DUSKBLADE),
				QDatabaseInterface::MakePair("Healer", SpellEnum::HEALER),
				QDatabaseInterface::MakePair("Hexblade", SpellEnum::HEXBLADE),
				QDatabaseInterface::MakePair("Shugenja", SpellEnum::SHUGENJA),
				QDatabaseInterface::MakePair("Wu Jen", SpellEnum::WU_JEN) };
	
	const auto botPairs = {	QDatabaseInterface::MakePair("Assassin", SpellEnum::ASSASSIN),
					QDatabaseInterface::MakePair("Blackguard", SpellEnum::BLACKGUARD) };
	
	const auto betPairs = {	QDatabaseInterface::MakePair("Arcane Artifact", SpellEnum::ARCANE_ARTIFACT),
				QDatabaseInterface::MakePair("Corrupt", SpellEnum::CORRUPT),
				QDatabaseInterface::MakePair("Divine Artifact", SpellEnum::DIVINE_ARTIFACT),
				QDatabaseInterface::MakePair("Initiate", SpellEnum::INITIATE),
				QDatabaseInterface::MakePair("Oneiromancy", SpellEnum::ONEIROMANCY),
				QDatabaseInterface::MakePair("Sanctified", SpellEnum::SANCTIFIED) };
	
	const auto butPairs = {	QDatabaseInterface::MakePair("Air", SpellEnum::AIR_DOMAIN),
				QDatabaseInterface::MakePair("Abyss", SpellEnum::ABYSS_DOMAIN),
				QDatabaseInterface::MakePair("Animal", SpellEnum::ANIMAL_DOMAIN),
				QDatabaseInterface::MakePair("Arborea", SpellEnum::ARBOREA_DOMAIN),
				QDatabaseInterface::MakePair("Baator", SpellEnum::BAATOR_DOMAIN),
				QDatabaseInterface::MakePair("Balance", SpellEnum::BALANCE_DOMAIN),
				QDatabaseInterface::MakePair("Blackwater", SpellEnum::BLACKWATER_DOMAIN),
				QDatabaseInterface::MakePair("Cavern", SpellEnum::CAVERN_DOMAIN),
				QDatabaseInterface::MakePair("Celerity", SpellEnum::CELERITY_DOMAIN),
				QDatabaseInterface::MakePair("Celestia", SpellEnum::CELESTIA_DOMAIN),
				QDatabaseInterface::MakePair("Chaos", SpellEnum::CHAOS_DOMAIN),
				QDatabaseInterface::MakePair("Charm", SpellEnum::CHARM_DOMAIN),
				QDatabaseInterface::MakePair("Cold", SpellEnum::COLD_DOMAIN),
				QDatabaseInterface::MakePair("Community", SpellEnum::COMMUNITY_DOMAIN),
				QDatabaseInterface::MakePair("Competition", SpellEnum::COMPETITION_DOMAIN),
				QDatabaseInterface::MakePair("Corruption", SpellEnum::CORRUPTION_DOMAIN),
				QDatabaseInterface::MakePair("Courage", SpellEnum::COURAGE_DOMAIN),
				QDatabaseInterface::MakePair("Craft", SpellEnum::CRAFT_DOMAIN),
				QDatabaseInterface::MakePair("Creation", SpellEnum::CREATION_DOMAIN),
				QDatabaseInterface::MakePair("Darkness", SpellEnum::DARKNESS_DOMAIN),
				QDatabaseInterface::MakePair("Death", SpellEnum::DEATH_DOMAIN),
				QDatabaseInterface::MakePair("Deathbound", SpellEnum::DEATHBOUND_DOMAIN),
				QDatabaseInterface::MakePair("Demonic", SpellEnum::DEMONIC_DOMAIN),
				QDatabaseInterface::MakePair("Destruction", SpellEnum::DESTRUCTION_DOMAIN),
				QDatabaseInterface::MakePair("Diabolic", SpellEnum::DIABOLIC_DOMAIN),
				QDatabaseInterface::MakePair("Domination", SpellEnum::DOMINATION_DOMAIN),
				QDatabaseInterface::MakePair("Dragon", SpellEnum::DRAGON_DOMAIN),
				QDatabaseInterface::MakePair("Dream", SpellEnum::DREAM_DOMAIN),
				QDatabaseInterface::MakePair("Drow", SpellEnum::DROW_DOMAIN),
				QDatabaseInterface::MakePair("Dwarf", SpellEnum::DWARF_DOMAIN),
				QDatabaseInterface::MakePair("Earth", SpellEnum::EARTH_DOMAIN),
				QDatabaseInterface::MakePair("Elf", SpellEnum::ELF_DOMAIN),
				QDatabaseInterface::MakePair("Elysium", SpellEnum::ELYSIUM_DOMAIN),
				QDatabaseInterface::MakePair("Entropy", SpellEnum::ENTROPY_DOMAIN),
				QDatabaseInterface::MakePair("Envy", SpellEnum::ENVY_DOMAIN),
				QDatabaseInterface::MakePair("Evil", SpellEnum::EVIL_DOMAIN),
				QDatabaseInterface::MakePair("Family", SpellEnum::FAMILY_DOMAIN),
				QDatabaseInterface::MakePair("Fate", SpellEnum::FATE_DOMAIN),
				QDatabaseInterface::MakePair("Fire", SpellEnum::FIRE_DOMAIN),
				QDatabaseInterface::MakePair("Force", SpellEnum::FORCE_DOMAIN),
				QDatabaseInterface::MakePair("Fury", SpellEnum::FURY_DOMAIN),
				QDatabaseInterface::MakePair("Glory", SpellEnum::GLORY_DOMAIN),
				QDatabaseInterface::MakePair("Gluttony", SpellEnum::GLUTTONY_DOMAIN),
				QDatabaseInterface::MakePair("Good", SpellEnum::GOOD_DOMAIN),
				QDatabaseInterface::MakePair("Gnome", SpellEnum::GNOME_DOMAIN),
				QDatabaseInterface::MakePair("Greed", SpellEnum::GREED_DOMAIN),
				QDatabaseInterface::MakePair("Hades", SpellEnum::HADES_DOMAIN),
				QDatabaseInterface::MakePair("Halfling", SpellEnum::HALFLING_DOMAIN),
				QDatabaseInterface::MakePair("Hatred", SpellEnum::HATRED_DOMAIN),
				QDatabaseInterface::MakePair("Healing", SpellEnum::HEALING_DOMAIN),
				QDatabaseInterface::MakePair("Hunger", SpellEnum::HUNGER_DOMAIN),
				QDatabaseInterface::MakePair("Illusion", SpellEnum::ILLUSION_DOMAIN),
				QDatabaseInterface::MakePair("Incarnum", SpellEnum::INCARNUM_DOMAIN),
				QDatabaseInterface::MakePair("Inquisition", SpellEnum::INQUISITION_DOMAIN),
				QDatabaseInterface::MakePair("Knowledge", SpellEnum::KNOWLEDGE_DOMAIN),
				QDatabaseInterface::MakePair("Law", SpellEnum::LAW_DOMAIN),
				QDatabaseInterface::MakePair("Liberation", SpellEnum::LIBERATION_DOMAIN),
				QDatabaseInterface::MakePair("Limbo", SpellEnum::LIMBO_DOMAIN),
				QDatabaseInterface::MakePair("Luck", SpellEnum::LUCK_DOMAIN),
				QDatabaseInterface::MakePair("Lust", SpellEnum::LUST_DOMAIN),
				QDatabaseInterface::MakePair("Magic", SpellEnum::MAGIC_DOMAIN),
				QDatabaseInterface::MakePair("Madness", SpellEnum::MADNESS_DOMAIN),
				QDatabaseInterface::MakePair("Mechanus", SpellEnum::MECHANUS_DOMAIN),
				QDatabaseInterface::MakePair("Mentalism", SpellEnum::MENTALISM_DOMAIN),
				QDatabaseInterface::MakePair("Metal", SpellEnum::METAL_DOMAIN),
				QDatabaseInterface::MakePair("Mind", SpellEnum::MIND_DOMAIN),
				QDatabaseInterface::MakePair("Moon", SpellEnum::MOON_DOMAIN),
				QDatabaseInterface::MakePair("Mysticism", SpellEnum::MYSTICISM_DOMAIN),
				QDatabaseInterface::MakePair("Nobility", SpellEnum::NOBILITY_DOMAIN),
				QDatabaseInterface::MakePair("Ocean", SpellEnum::OCEAN_DOMAIN),
				QDatabaseInterface::MakePair("Ooze", SpellEnum::OOZE_DOMAIN),
				QDatabaseInterface::MakePair("Oracle", SpellEnum::ORACLE_DOMAIN),
				QDatabaseInterface::MakePair("Orc", SpellEnum::ORC_DOMAIN),
				QDatabaseInterface::MakePair("Pact", SpellEnum::PACT_DOMAIN),
				QDatabaseInterface::MakePair("Pestilence", SpellEnum::PESTILENCE_DOMAIN),
				QDatabaseInterface::MakePair("Planning", SpellEnum::PLANNING_DOMAIN),
				QDatabaseInterface::MakePair("Plant", SpellEnum::PLANT_DOMAIN),
				QDatabaseInterface::MakePair("Portal", SpellEnum::PORTAL_DOMAIN),
				QDatabaseInterface::MakePair("Pride", SpellEnum::PRIDE_DOMAIN),
				QDatabaseInterface::MakePair("Protection", SpellEnum::PROTECTION_DOMAIN),
				QDatabaseInterface::MakePair("Purification", SpellEnum::PURIFICATION_DOMAIN),
				QDatabaseInterface::MakePair("Renewal", SpellEnum::RENEWAL_DOMAIN),
				QDatabaseInterface::MakePair("Repose", SpellEnum::REPOSE_DOMAIN),
				QDatabaseInterface::MakePair("Retribution", SpellEnum::RETRIBUTION_DOMAIN),
				QDatabaseInterface::MakePair("Revered Ancestor", SpellEnum::REVERED_ANCESTOR_DOMAIN),
				QDatabaseInterface::MakePair("Rune", SpellEnum::RUNE_DOMAIN),
				QDatabaseInterface::MakePair("Sand", SpellEnum::SAND_DOMAIN),
				QDatabaseInterface::MakePair("Scalykind", SpellEnum::SCALYKIND_DOMAIN),
				QDatabaseInterface::MakePair("Seafolk", SpellEnum::SEAFOLK_DOMAIN),
				QDatabaseInterface::MakePair("Slime", SpellEnum::SLIME_DOMAIN),
				QDatabaseInterface::MakePair("Sloth", SpellEnum::SLOTH_DOMAIN),
				QDatabaseInterface::MakePair("Spell", SpellEnum::SPELL_DOMAIN),
				QDatabaseInterface::MakePair("Spider", SpellEnum::SPIDER_DOMAIN),
				QDatabaseInterface::MakePair("Spite", SpellEnum::SPITE_DOMAIN),
				QDatabaseInterface::MakePair("Storm", SpellEnum::STORM_DOMAIN),
				QDatabaseInterface::MakePair("Strength", SpellEnum::STRENGTH_DOMAIN),
				QDatabaseInterface::MakePair("Suffering", SpellEnum::SUFFERING_DOMAIN),
				QDatabaseInterface::MakePair("Summer", SpellEnum::SUMMER_DOMAIN),
				QDatabaseInterface::MakePair("Summoner", SpellEnum::SUMMONER_DOMAIN),
				QDatabaseInterface::MakePair("Sun", SpellEnum::SUN_DOMAIN),
				QDatabaseInterface::MakePair("Temptation", SpellEnum::TEMPTATION_DOMAIN),
				QDatabaseInterface::MakePair("Thirst", SpellEnum::THIRST_DOMAIN),
				QDatabaseInterface::MakePair("Time", SpellEnum::TIME_DOMAIN),
				QDatabaseInterface::MakePair("Trade", SpellEnum::TRADE_DOMAIN),
				QDatabaseInterface::MakePair("Transformation", SpellEnum::TRANSFORMATION_DOMAIN),
				QDatabaseInterface::MakePair("Travel", SpellEnum::TRAVEL_DOMAIN),
				QDatabaseInterface::MakePair("Trickery", SpellEnum::TRICKERY_DOMAIN),
				QDatabaseInterface::MakePair("Truth", SpellEnum::TRUTH_DOMAIN),
				QDatabaseInterface::MakePair("Tyranny", SpellEnum::TYRANNY_DOMAIN),
				QDatabaseInterface::MakePair("Undeath", SpellEnum::UNDEATH_DOMAIN),
				QDatabaseInterface::MakePair("Vile Darkness", SpellEnum::VILE_DARKNESS_DOMAIN),
				QDatabaseInterface::MakePair("War", SpellEnum::WAR_DOMAIN),
				QDatabaseInterface::MakePair("Warforged", SpellEnum::WARFORGED_DOMAIN),
				QDatabaseInterface::MakePair("Water", SpellEnum::WATER_DOMAIN),
				QDatabaseInterface::MakePair("Wealth", SpellEnum::WEALTH_DOMAIN),
				QDatabaseInterface::MakePair("Windstorm", SpellEnum::WINDSTORM_DOMAIN),
				QDatabaseInterface::MakePair("Wrath", SpellEnum::WRATH_DOMAIN) };
	
	const auto baseClassButton = new QPushButton("Base Classes");
	QDatabaseInterface::multibits.emplace_back(baseClassButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(bitPairs, "Base Classes", font, baseClassButton, QDatabaseInterface::multibits.back().second, 5);
	
	const auto prestigeClassButton = new QPushButton("Prestige Classes");
	QDatabaseInterface::multibits.emplace_back(prestigeClassButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(botPairs, "Prestige Classes", font, prestigeClassButton, QDatabaseInterface::multibits.back().second, 4);
	
	const auto domainButton = new QPushButton("Domains");
	QDatabaseInterface::multibits.emplace_back(domainButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Domains", font, domainButton, QDatabaseInterface::multibits.back().second, 10);
	
	const auto otherButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(betPairs, "Special", font, otherButton, QDatabaseInterface::multibits.back().second, 3);
	
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
void QDatabaseInterface<PowerEnum>::initialiseSpecial(const QFont& font, QGridLayout* layout)
{
	const auto specialBox = new QGroupBox("Special", this);
	const auto specialLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Body Leech", PowerEnum::BODY_LEECH),
				QDatabaseInterface::MakePair("Egoist", PowerEnum::EGOIST),
				QDatabaseInterface::MakePair("Kineticist", PowerEnum::KINETICIST),
				QDatabaseInterface::MakePair("Nomad", PowerEnum::NOMAD),
				QDatabaseInterface::MakePair("Seer", PowerEnum::SEER),
				QDatabaseInterface::MakePair("Shaper", PowerEnum::SHAPER),
				QDatabaseInterface::MakePair("Telepath", PowerEnum::TELEPATH) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		specialLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("Air", PowerEnum::AIR_MANTLE),
				QDatabaseInterface::MakePair("Chaos", PowerEnum::CHAOS_MANTLE),
				QDatabaseInterface::MakePair("Communication", PowerEnum::COMMUNICATION_MANTLE),
				QDatabaseInterface::MakePair("Conflict", PowerEnum::CONFLICT_MANTLE),
				QDatabaseInterface::MakePair("Consumption", PowerEnum::CONSUMPTION_MANTLE),
				QDatabaseInterface::MakePair("Corruption and Madness", PowerEnum::CORRUPTION_AND_MADNESS_MANTLE),
				QDatabaseInterface::MakePair("Creation", PowerEnum::CREATION_MANTLE),
				QDatabaseInterface::MakePair("Death", PowerEnum::DEATH_MANTLE),
				QDatabaseInterface::MakePair("Deception", PowerEnum::DECEPTION_MANTLE),
				QDatabaseInterface::MakePair("Destruction", PowerEnum::DESTRUCTION_MANTLE),
				QDatabaseInterface::MakePair("Earth", PowerEnum::EARTH_MANTLE),
				QDatabaseInterface::MakePair("Elements", PowerEnum::ELEMENTS_MANTLE),
				QDatabaseInterface::MakePair("Energy", PowerEnum::ENERGY_MANTLE),
				QDatabaseInterface::MakePair("Evil", PowerEnum::EVIL_MANTLE),
				QDatabaseInterface::MakePair("Fate", PowerEnum::FATE_MANTLE),
				QDatabaseInterface::MakePair("Fire", PowerEnum::FIRE_MANTLE),
				QDatabaseInterface::MakePair("Force", PowerEnum::FORCE_MANTLE),
				QDatabaseInterface::MakePair("Freedom", PowerEnum::FREEDOM_MANTLE),
				QDatabaseInterface::MakePair("Good", PowerEnum::GOOD_MANTLE),
				QDatabaseInterface::MakePair("Guardian", PowerEnum::GUARDIAN_MANTLE),
				QDatabaseInterface::MakePair("Justice", PowerEnum::JUSTICE_MANTLE),
				QDatabaseInterface::MakePair("Knowledge", PowerEnum::KNOWLEDGE_MANTLE),
				QDatabaseInterface::MakePair("Law", PowerEnum::LAW_MANTLE),
				QDatabaseInterface::MakePair("Life", PowerEnum::LIFE_MANTLE),
				QDatabaseInterface::MakePair("Light and Darkness", PowerEnum::LIGHT_AND_DARKNESS_MANTLE),
				QDatabaseInterface::MakePair("Magic", PowerEnum::MAGIC_MANTLE),
				QDatabaseInterface::MakePair("Mental Power", PowerEnum::MENTAL_POWER_MANTLE),
				QDatabaseInterface::MakePair("Natural World", PowerEnum::NATURAL_WORLD_MANTLE),
				QDatabaseInterface::MakePair("Pain and Suffering", PowerEnum::PAIN_AND_SUFFERING_MANTLE),
				QDatabaseInterface::MakePair("Physical Power", PowerEnum::PHYSICAL_POWER_MANTLE),
				QDatabaseInterface::MakePair("Plane", PowerEnum::PLANE_MANTLE),
				QDatabaseInterface::MakePair("Repose", PowerEnum::REPOSE_MANTLE),
				QDatabaseInterface::MakePair("Time", PowerEnum::TIME_MANTLE),
				QDatabaseInterface::MakePair("Water", PowerEnum::WATER_MANTLE) };
	
	const auto mantleButton = new QPushButton("Mantles");
	QDatabaseInterface::multibits.emplace_back(mantleButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Mantles", font, mantleButton, QDatabaseInterface::multibits.back().second, 5);
	
	specialLayout->addWidget(mantleButton);
	mantleButton->setObjectName("A");
	mantleButton->setFont(font);
	QObject::connect(mantleButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	specialBox->setLayout(specialLayout);
	layout->addWidget(specialBox, 1, 0, 4, 2);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto arcaneButton = new QPushButton("Arcane");
	QDatabaseInterface::multibits.emplace_back(arcaneButton, CustomBitset());
	
	auto& arcaneBitset = QDatabaseInterface::multibits.back().second;
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
	QDatabaseInterface::multibits.emplace_back(divineButton, CustomBitset());
	
	auto& divineBitset = QDatabaseInterface::multibits.back().second;
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
	
	for (const auto& [btn, bset] : QDatabaseInterface::multibits)
	{
		if (btn->text() == "Domains")
		{
			divineBitset.set(bset);
			break;
		}
	}
	
	const auto infusionButton = new QPushButton("Infusion");
	QDatabaseInterface::multibits.emplace_back(infusionButton, CustomBitset());
	
	auto& infusionBitset = QDatabaseInterface::multibits.back().second;
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
void QDatabaseInterface<PowerEnum>::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto featureBox = new QGroupBox("Features", this);
	const auto featureLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Augment", PowerEnum::AUGMENT),
					QDatabaseInterface::MakePair("Experience", PowerEnum::EXPERIENCE) };
	
	for (const auto& pr : bitPairs)
	{
		featureLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	featureBox->setLayout(featureLayout);
	layout->addWidget(featureBox, 1, 2, 1, 2);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseSchoolsOrDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto schoolBox = new QGroupBox("Schools", this);
	const auto schoolLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Abjuration", SpellEnum::ABJURATION),
				QDatabaseInterface::MakePair("Conjuration", SpellEnum::CONJURATION),
				QDatabaseInterface::MakePair("Divination", SpellEnum::DIVINATION),
				QDatabaseInterface::MakePair("Enchantment", SpellEnum::ENCHANTMENT),
				QDatabaseInterface::MakePair("Evocation", SpellEnum::EVOCATION),
				QDatabaseInterface::MakePair("Illusion", SpellEnum::ILLUSION),
				QDatabaseInterface::MakePair("Necromancy", SpellEnum::NECROMANCY),
				QDatabaseInterface::MakePair("Transmutation", SpellEnum::TRANSMUTATION),
				QDatabaseInterface::MakePair("Universal", SpellEnum::UNIVERSAL) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		schoolLayout->addWidget(pr.first, count/3, count % 3);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	schoolBox->setLayout(schoolLayout);
	layout->addWidget(schoolBox, 1, 2, 3, 3);
}

template<>
void QDatabaseInterface<PowerEnum>::initialiseSchoolsOrDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto disciplineBox = new QGroupBox("Disciplines", this);
	const auto disciplineLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Clairsentience", PowerEnum::CLAIRSENTIENCE),
				QDatabaseInterface::MakePair("Metacreativity", PowerEnum::METACREATIVITY),
				QDatabaseInterface::MakePair("Psychokinesis", PowerEnum::PSYCHOKINESIS),
				QDatabaseInterface::MakePair("Psychometabolism", PowerEnum::PSYCHOMETABOLISM),
				QDatabaseInterface::MakePair("Psychoportation", PowerEnum::PSYCHOPORTATION),
				QDatabaseInterface::MakePair("Telepathy", PowerEnum::TELEPATHY) };
	
	for (const auto& pr : bitPairs)
	{
		disciplineLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	disciplineBox->setLayout(disciplineLayout);
	layout->addWidget(disciplineBox, 0, 4, 1, 6);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseSubschoolsOrSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subschoolBox = new QGroupBox("Subschools", this);
	const auto subschoolLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Calling", SpellEnum::CALLING),
				QDatabaseInterface::MakePair("Charm", SpellEnum::CHARM),
				QDatabaseInterface::MakePair("Compulsion", SpellEnum::COMPULSION),
				QDatabaseInterface::MakePair("Creation", SpellEnum::CREATION),
				QDatabaseInterface::MakePair("Figment", SpellEnum::FIGMENT),
				QDatabaseInterface::MakePair("Glamer", SpellEnum::GLAMER),
				QDatabaseInterface::MakePair("Healing", SpellEnum::HEALING),
				QDatabaseInterface::MakePair("Pattern", SpellEnum::PATTERN),
				QDatabaseInterface::MakePair("Phantasm", SpellEnum::PHANTASM),
				QDatabaseInterface::MakePair("Polymorph", SpellEnum::POLYMORPH),
				QDatabaseInterface::MakePair("Scrying", SpellEnum::SCRYING),
				QDatabaseInterface::MakePair("Shadow", SpellEnum::SHADOW),
				QDatabaseInterface::MakePair("Summoning", SpellEnum::SUMMONING),
				QDatabaseInterface::MakePair("Teleportation", SpellEnum::TELEPORTATION) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		subschoolLayout->addWidget(pr.first, count/5, count % 5);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	subschoolBox->setLayout(subschoolLayout);
	layout->addWidget(subschoolBox, 1, 5, 3, 5);
}

template<>
void QDatabaseInterface<PowerEnum>::initialiseSubschoolsOrSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subdisciplineBox = new QGroupBox("Subdisciplines", this);
	const auto subdisciplineLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Charm", PowerEnum::CHARM),
				QDatabaseInterface::MakePair("Compulsion", PowerEnum::COMPULSION),
				QDatabaseInterface::MakePair("Creation", PowerEnum::CREATION),
				QDatabaseInterface::MakePair("Healing", PowerEnum::HEALING),
				QDatabaseInterface::MakePair("Scrying", PowerEnum::SCRYING),
				QDatabaseInterface::MakePair("Teleportation", PowerEnum::TELEPORTATION) };
	
	for (const auto& pr : bitPairs)
	{
		subdisciplineLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	subdisciplineBox->setLayout(subdisciplineLayout);
	layout->addWidget(subdisciplineBox, 1, 4, 1, 6);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseMaterialsOrDisplays(const QFont& font, QGridLayout* layout)
{
	const auto materialBox = new QGroupBox("Materials", this);
	const auto materialLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Focus", SpellEnum::FOCUS),
				QDatabaseInterface::MakePair("Divine Focus", SpellEnum::DIVINE_FOCUS),
				QDatabaseInterface::MakePair("Verbal", SpellEnum::VERBAL),
				QDatabaseInterface::MakePair("Somatic", SpellEnum::SOMATIC),
				QDatabaseInterface::MakePair("Material", SpellEnum::MATERIAL),
				QDatabaseInterface::MakePair("Gold", SpellEnum::GOLD),
				QDatabaseInterface::MakePair("Experience", SpellEnum::EXPERIENCE) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		materialLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("Alignment", SpellEnum::ALIGNMENT),
				QDatabaseInterface::MakePair("Corruption", SpellEnum::CORRUPT),
				QDatabaseInterface::MakePair("Dragonmark", SpellEnum::DRAGONMARK),
				QDatabaseInterface::MakePair("Essentia", SpellEnum::ESSENTIA),
				QDatabaseInterface::MakePair("Racial", SpellEnum::RACIAL),
				QDatabaseInterface::MakePair("Sacrifice", SpellEnum::SANCTIFIED),
				QDatabaseInterface::MakePair("Verbal (Bard only)", SpellEnum::VERBAL_BARD) };
	
	const auto otherComponentButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherComponentButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other Components", font, otherComponentButton, QDatabaseInterface::multibits.back().second, 10);
	
	materialLayout->addWidget(otherComponentButton, 3, 1);
	otherComponentButton->setObjectName("A");
	otherComponentButton->setFont(font);
	QObject::connect(otherComponentButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	materialBox->setLayout(materialLayout);
	layout->addWidget(materialBox, 3, 0, 4, 2);
}

template<>
void QDatabaseInterface<PowerEnum>::initialiseMaterialsOrDisplays(const QFont& font, QGridLayout* layout)
{
	const auto displayBox = new QGroupBox("Displays", this);
	const auto displayLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Auditory", PowerEnum::AUDITORY),
				QDatabaseInterface::MakePair("Material", PowerEnum::MATERIAL),
				QDatabaseInterface::MakePair("Mental", PowerEnum::MENTAL),
				QDatabaseInterface::MakePair("Olfactory", PowerEnum::OLFACTORY),
				QDatabaseInterface::MakePair("Visual", PowerEnum::VISUAL) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		displayLayout->addWidget(pr.first, count/2, count % 2);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	displayBox->setLayout(displayLayout);
	layout->addWidget(displayBox, 2, 2, 3, 2);
}

template<>
qint32 QDatabaseInterface<SpellEnum>::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", this);
	const auto descriptorLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Acid", SpellEnum::ACID),
				QDatabaseInterface::MakePair("Air", SpellEnum::AIR),
				QDatabaseInterface::MakePair("Chaotic", SpellEnum::CHAOTIC),
				QDatabaseInterface::MakePair("Cold", SpellEnum::COLD),
				QDatabaseInterface::MakePair("Darkness", SpellEnum::DARKNESS),
				QDatabaseInterface::MakePair("Death", SpellEnum::DEATH),
				QDatabaseInterface::MakePair("Earth", SpellEnum::EARTH),
				QDatabaseInterface::MakePair("Electricity", SpellEnum::ELECTRICITY),
				QDatabaseInterface::MakePair("Evil", SpellEnum::EVIL),
				QDatabaseInterface::MakePair("Fear", SpellEnum::FEAR),
				QDatabaseInterface::MakePair("Fire", SpellEnum::FIRE),
				QDatabaseInterface::MakePair("Force", SpellEnum::FORCE),
				QDatabaseInterface::MakePair("Good", SpellEnum::GOOD),
				QDatabaseInterface::MakePair("Incarnum", SpellEnum::INCARNUM),
				QDatabaseInterface::MakePair("Language", SpellEnum::LANGUAGE_DEPENDENT),
				QDatabaseInterface::MakePair("Lawful", SpellEnum::LAWFUL),
				QDatabaseInterface::MakePair("Light", SpellEnum::LIGHT),
				QDatabaseInterface::MakePair("Mind-Affecting", SpellEnum::MIND_AFFECTING),
				QDatabaseInterface::MakePair("Sonic", SpellEnum::SONIC),
				QDatabaseInterface::MakePair("Water", SpellEnum::WATER) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		descriptorLayout->addWidget(pr.first, count/7, count % 7);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = { QDatabaseInterface::MakePair("Investiture", SpellEnum::INVESTITURE),
				QDatabaseInterface::MakePair("Mindset", SpellEnum::MINDSET) };
	
	const auto otherDescriptorButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherDescriptorButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other Descriptors", font, otherDescriptorButton, QDatabaseInterface::multibits.back().second, 2);
	
	descriptorLayout->addWidget(otherDescriptorButton, 2, 5);
	otherDescriptorButton->setObjectName("A");
	otherDescriptorButton->setFont(font);
	QObject::connect(otherDescriptorButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	descriptorBox->setLayout(descriptorLayout);
	layout->addWidget(descriptorBox, 4, 2, 3, 7);
	return 7;
}

template<>
qint32 QDatabaseInterface<PowerEnum>::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", this);
	const auto descriptorLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Acid", PowerEnum::ACID),
				QDatabaseInterface::MakePair("Cold", PowerEnum::COLD),
				QDatabaseInterface::MakePair("Darkness", PowerEnum::DARKNESS),
				QDatabaseInterface::MakePair("Death", PowerEnum::DEATH),
				QDatabaseInterface::MakePair("Electricity", PowerEnum::ELECTRICITY),
				QDatabaseInterface::MakePair("Evil", PowerEnum::EVIL),
				QDatabaseInterface::MakePair("Fear", PowerEnum::FEAR),
				QDatabaseInterface::MakePair("Fire", PowerEnum::FIRE),
				QDatabaseInterface::MakePair("Force", PowerEnum::FORCE),
				QDatabaseInterface::MakePair("Good", PowerEnum::GOOD),
				QDatabaseInterface::MakePair("Language", PowerEnum::LANGUAGE_DEPENDENT),
				QDatabaseInterface::MakePair("Light", PowerEnum::LIGHT),
				QDatabaseInterface::MakePair("Mind-Affecting", PowerEnum::MIND_AFFECTING),
				QDatabaseInterface::MakePair("Shadow", PowerEnum::SHADOW),
				QDatabaseInterface::MakePair("Sonic", PowerEnum::SONIC) };
	
	auto count = 0;
	
	for (const auto& pr : bitPairs)
	{
		descriptorLayout->addWidget(pr.first, count/5, count % 5);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		++count;
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	descriptorBox->setLayout(descriptorLayout);
	layout->addWidget(descriptorBox, 2, 4, 3, 5);
	return 5;
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseSources(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto sourceBox = new QGroupBox("Sources", this);
	const auto sourceLayout = new QVBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("PHB", SpellEnum::PLAYERS_HANDBOOK),
				QDatabaseInterface::MakePair("SpC", SpellEnum::SPELL_COMPENDIUM) };
	
	for (const auto& pr : bitPairs)
	{
		sourceLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("An", SpellEnum::ANAUROCH_EMPIRE_OF_SHADE),
				QDatabaseInterface::MakePair("CCha", SpellEnum::COMPLETE_CHAMPION),
				QDatabaseInterface::MakePair("Ci", SpellEnum::CITYSCAPE),
				QDatabaseInterface::MakePair("CMge", SpellEnum::COMPLETE_MAGE),
				QDatabaseInterface::MakePair("CoS", SpellEnum::CITY_OF_STORMREACH),
				QDatabaseInterface::MakePair("CoV", SpellEnum::CHAMPIONS_OF_VALOR),
				QDatabaseInterface::MakePair("CR", SpellEnum::CHAMPIONS_OF_RUIN),
				QDatabaseInterface::MakePair("CSco", SpellEnum::COMPLETE_SCOUNDREL),
				QDatabaseInterface::MakePair("CSW", SpellEnum::CITY_OF_SPLENDORS_WATERDEEP),
				QDatabaseInterface::MakePair("DoE", SpellEnum::DRAGONS_OF_EBERRON),
				QDatabaseInterface::MakePair("DoF", SpellEnum::DRAGONS_OF_FAERUN),
				QDatabaseInterface::MakePair("Dmkd", SpellEnum::DRAGONMARKED),
				QDatabaseInterface::MakePair("DrM", SpellEnum::DRAGON_MAGIC),
				QDatabaseInterface::MakePair("DrU", SpellEnum::DROW_OF_THE_UNDERDARK),
				QDatabaseInterface::MakePair("EDP", SpellEnum::EXPEDITION_TO_DEMONWEB_PITS),
				QDatabaseInterface::MakePair("EU", SpellEnum::EXPEDITION_TO_UNDERMOUNTAIN),
				QDatabaseInterface::MakePair("FoE", SpellEnum::FAITHS_OF_EBERRON),
				QDatabaseInterface::MakePair("FC1", SpellEnum::FIENDISH_CODEX_I),
				QDatabaseInterface::MakePair("FC2", SpellEnum::FIENDISH_CODEX_II),
				QDatabaseInterface::MakePair("FN", SpellEnum::FIVE_NATIONS),
				QDatabaseInterface::MakePair("FW", SpellEnum::FORGE_OF_WAR),
				QDatabaseInterface::MakePair("HB", SpellEnum::HEROES_OF_BATTLE),
				QDatabaseInterface::MakePair("HH", SpellEnum::HEROES_OF_HORROR),
				QDatabaseInterface::MakePair("LoM", SpellEnum::LORDS_OF_MADNESS),
				QDatabaseInterface::MakePair("MM4", SpellEnum::MONSTER_MANUAL_IV),
				QDatabaseInterface::MakePair("MoE", SpellEnum::MAGIC_OF_EBERRON),
				QDatabaseInterface::MakePair("MoI", SpellEnum::MAGIC_OF_INCARNUM),
				QDatabaseInterface::MakePair("PGE", SpellEnum::PLAYERS_GUIDE_TO_EBERRON),
				QDatabaseInterface::MakePair("PH2", SpellEnum::PLAYERS_HANDBOOK_II),
				QDatabaseInterface::MakePair("PoF", SpellEnum::POWER_OF_FAERUN),
				QDatabaseInterface::MakePair("Rav", SpellEnum::EXPEDITION_TO_CASTLE_RAVENLOFT),
				QDatabaseInterface::MakePair("RDr", SpellEnum::RACES_OF_THE_DRAGON),
				QDatabaseInterface::MakePair("RE", SpellEnum::RACES_OF_EBERRON),
				QDatabaseInterface::MakePair("Sa", SpellEnum::SANDSTORM),
				QDatabaseInterface::MakePair("SoS", SpellEnum::SECRETS_OF_SARLONA),
				QDatabaseInterface::MakePair("SoX", SpellEnum::SECRETS_OF_XENDRIK),
				QDatabaseInterface::MakePair("Sto", SpellEnum::STORMWRACK),
				QDatabaseInterface::MakePair("WL", SpellEnum::WEAPONS_OF_LEGACY) };
	
	const auto otherSourceButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherSourceButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other Sources", font, otherSourceButton, QDatabaseInterface::multibits.back().second, 4);
	
	sourceLayout->addWidget(otherSourceButton);
	otherSourceButton->setObjectName("A");
	otherSourceButton->setFont(font);
	QObject::connect(otherSourceButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	sourceBox->setLayout(sourceLayout);
	layout->addWidget(sourceBox, delta - 3, 9, 3, 1);
}

template<>
void QDatabaseInterface<PowerEnum>::initialiseSources(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto sourceBox = new QGroupBox("Sources", this);
	const auto sourceLayout = new QVBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("XPH", PowerEnum::EXPANDED_PSIONICS_HANDBOOK),
				QDatabaseInterface::MakePair("CPsi", PowerEnum::COMPLETE_PSIONIC) };
	
	for (const auto& pr : bitPairs)
	{
		sourceLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("DrM", PowerEnum::DRAGON_MAGIC),
				QDatabaseInterface::MakePair("FoE", PowerEnum::FAITHS_OF_EBERRON),
				QDatabaseInterface::MakePair("Hyp", PowerEnum::HYPERCONSCIOUS),
				QDatabaseInterface::MakePair("MoE", PowerEnum::MAGIC_OF_EBERRON),
				QDatabaseInterface::MakePair("MoI", PowerEnum::MAGIC_OF_INCARNUM),
				QDatabaseInterface::MakePair("PGE", PowerEnum::PLAYERS_GUIDE_TO_EBERRON),
				QDatabaseInterface::MakePair("RDr", PowerEnum::RACES_OF_THE_DRAGON),
				QDatabaseInterface::MakePair("RW", PowerEnum::RACES_OF_THE_WILD),
				QDatabaseInterface::MakePair("SoS", PowerEnum::SECRETS_OF_SARLONA),
				QDatabaseInterface::MakePair("Sto", PowerEnum::STORMWRACK),
				QDatabaseInterface::MakePair("WL", PowerEnum::WEAPONS_OF_LEGACY),
				QDatabaseInterface::MakePair("Web", PowerEnum::WEB) };
	
	const auto otherSourceButton = new QPushButton("Other");
	QDatabaseInterface::multibits.emplace_back(otherSourceButton, CustomBitset());
	QDatabaseInterface::initialiseWindow(butPairs, "Other Sources", font, otherSourceButton, QDatabaseInterface::multibits.back().second, 4);
	
	sourceLayout->addWidget(otherSourceButton);
	otherSourceButton->setObjectName("A");
	otherSourceButton->setFont(font);
	QObject::connect(otherSourceButton, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
	
	sourceBox->setLayout(sourceLayout);
	layout->addWidget(sourceBox, delta - 3, 9, 3, 1);
}

template<>
void QDatabaseInterface<SpellEnum>::initialiseBars(const QFont& font, QGridLayout* layout, qint32 delta)
{
	layout->addWidget(QDatabaseInterfaceIntermediary::nameLineEdit, delta + 8, 0, 1, 4);
	layout->addWidget(QDatabaseInterfaceIntermediary::loreLineEdit, delta + 8, 4, 1, 5);
	
	QDatabaseInterface::RevisedBitset.set(SpellEnum::ANAUROCH_EMPIRE_OF_SHADE);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::CHAMPIONS_OF_RUIN);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::CHAMPIONS_OF_VALOR);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::CITY_OF_SPLENDORS_WATERDEEP);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::CITY_OF_STORMREACH);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::CITYSCAPE);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::COMPLETE_CHAMPION);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::COMPLETE_MAGE);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::COMPLETE_SCOUNDREL);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::DRAGON_MAGIC);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::DRAGONMARKED);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::DRAGONS_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::DRAGONS_OF_FAERUN);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::DROW_OF_THE_UNDERDARK);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::EXPEDITION_TO_CASTLE_RAVENLOFT);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::EXPEDITION_TO_DEMONWEB_PITS);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::EXPEDITION_TO_UNDERMOUNTAIN);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::FAITHS_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::FIENDISH_CODEX_I);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::FIENDISH_CODEX_II);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::FIVE_NATIONS);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::FORGE_OF_WAR);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::HEROES_OF_BATTLE);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::HEROES_OF_HORROR);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::LORDS_OF_MADNESS);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::MAGIC_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::MONSTER_MANUAL_IV);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::MAGIC_OF_INCARNUM);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::PLAYERS_GUIDE_TO_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::PLAYERS_HANDBOOK);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::PLAYERS_HANDBOOK_II);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::POWER_OF_FAERUN);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::RACES_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::RACES_OF_THE_DRAGON);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::SANDSTORM);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::SECRETS_OF_SARLONA);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::SECRETS_OF_XENDRIK);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::SPELL_COMPENDIUM);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::STORMWRACK);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::WEAPONS_OF_LEGACY);
	QDatabaseInterface::RevisedBitset.set(SpellEnum::WEB35);
	
	const auto button35e = new QPushButton("3.5e");
	QDatabaseInterface::multibits.emplace_back(button35e, QDatabaseInterface::RevisedBitset);
	
	layout->addWidget(button35e, delta + 8, 9, 1, 1);
	button35e->setObjectName("B");
	button35e->setFont(font);
	
	QObject::connect(button35e, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
}

template<>
void QDatabaseInterface<PowerEnum>::initialiseBars(const QFont&, QGridLayout* layout, qint32 delta)
{
	QDatabaseInterface::RevisedBitset.set(PowerEnum::COMPLETE_PSIONIC);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::DRAGON_MAGIC);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::EXPANDED_PSIONICS_HANDBOOK);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::FAITHS_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::HYPERCONSCIOUS);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::MAGIC_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::MAGIC_OF_INCARNUM);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::PLAYERS_GUIDE_TO_EBERRON);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::RACES_OF_THE_DRAGON);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::RACES_OF_THE_WILD);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::SECRETS_OF_SARLONA);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::STORMWRACK);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::WEAPONS_OF_LEGACY);
	QDatabaseInterface::RevisedBitset.set(PowerEnum::WEB);
	
	layout->addWidget(QDatabaseInterfaceIntermediary::nameLineEdit, delta + 8, 0, 1, 5);
	layout->addWidget(QDatabaseInterfaceIntermediary::loreLineEdit, delta + 8, 5, 1, 5);
}
