// Qt Libraries
#include <QTextTable>

// Custom Libraries
#include "Constants.hpp"
#include "QDatabaseInterface.hpp"

template<>
QColor QDatabaseInterface<PowerConstantsEnum>::Foreground(const CustomBitset& b)
{
	if (b.test(PowerConstantsEnum::CLAIRSENTIENCE))
		return QDatabaseInterface::ClairsentienceDivinationColor;
	else if (b.test(PowerConstantsEnum::METACREATIVITY))
		return QDatabaseInterface::MetacreativityConjurationColor;
	else if (b.test(PowerConstantsEnum::PSYCHOKINESIS))
		return QDatabaseInterface::PsychokinesisEvocationColor;
	else if (b.test(PowerConstantsEnum::PSYCHOMETABOLISM))
		return QDatabaseInterface::PsychometabolismTransmutationColor;
	else if (b.test(PowerConstantsEnum::PSYCHOPORTATION))
		return QDatabaseInterface::PsychoportationAbjurationColor;
	else if (b.test(PowerConstantsEnum::TELEPATHY))
		return QDatabaseInterface::TelepathyEnchantmentColor;
	
	return QColor(0, 0, 0);
}

template<>
QColor QDatabaseInterface<SpellConstantsEnum>::Foreground(const CustomBitset& b)
{
	if (b.test(SpellConstantsEnum::ABJURATION))
		return QDatabaseInterface::PsychoportationAbjurationColor;
	else if (b.test(SpellConstantsEnum::CONJURATION))
		return QDatabaseInterface::MetacreativityConjurationColor;
	else if (b.test(SpellConstantsEnum::DIVINATION))
		return QDatabaseInterface::ClairsentienceDivinationColor;
	else if (b.test(SpellConstantsEnum::ENCHANTMENT))
		return QDatabaseInterface::TelepathyEnchantmentColor;
	else if (b.test(SpellConstantsEnum::EVOCATION))
		return QDatabaseInterface::PsychokinesisEvocationColor;
	else if (b.test(SpellConstantsEnum::ILLUSION))
		return QDatabaseInterface::IllusionColor;
	else if (b.test(SpellConstantsEnum::NECROMANCY))
		return QDatabaseInterface::NecromancyColor;
	else if (b.test(SpellConstantsEnum::TRANSMUTATION))
		return QDatabaseInterface::PsychometabolismTransmutationColor;
	else if (b.test(SpellConstantsEnum::UNIVERSAL))
		return QDatabaseInterface::UniversalColor;
	
	return QColor(0, 0, 0);
}

template<>
void QDatabaseInterface<SpellConstantsEnum>::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Core Classes", this);
	const auto classLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Bard", SpellConstantsEnum::BARD),
					QDatabaseInterface::MakePair("Cleric", SpellConstantsEnum::CLERIC),
					QDatabaseInterface::MakePair("Druid", SpellConstantsEnum::DRUID),
					QDatabaseInterface::MakePair("Paladin", SpellConstantsEnum::PALADIN),
					QDatabaseInterface::MakePair("Ranger", SpellConstantsEnum::RANGER),
					QDatabaseInterface::MakePair("Sorcerer", SpellConstantsEnum::SORCERER),
					QDatabaseInterface::MakePair("Wizard", SpellConstantsEnum::WIZARD) };
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseClasses(const QFont& font, QGridLayout* layout)
{
	const auto classBox = new QGroupBox("Classes", this);
	const auto classLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Lurk", PowerConstantsEnum::LURK),
					QDatabaseInterface::MakePair("Psion", PowerConstantsEnum::PSION),
					QDatabaseInterface::MakePair("Psychic Rogue", PowerConstantsEnum::PSYCHIC_ROGUE),
					QDatabaseInterface::MakePair("Psychic Warrior", PowerConstantsEnum::PSYCHIC_WARRIOR) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseSpecial(const QFont& font, QGridLayout* layout)
{	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Adept", SpellConstantsEnum::ADEPT),
				QDatabaseInterface::MakePair("Artificer", SpellConstantsEnum::ARTIFICER),
				QDatabaseInterface::MakePair("Beguiler", SpellConstantsEnum::BEGUILER),
				QDatabaseInterface::MakePair("Death Delver", SpellConstantsEnum::DEATH_DELVER),
				QDatabaseInterface::MakePair("Dread Necromancer", SpellConstantsEnum::DREAD_NECROMANCER),
				QDatabaseInterface::MakePair("Duskblade", SpellConstantsEnum::DUSKBLADE),
				QDatabaseInterface::MakePair("Healer", SpellConstantsEnum::HEALER),
				QDatabaseInterface::MakePair("Hexblade", SpellConstantsEnum::HEXBLADE),
				QDatabaseInterface::MakePair("Shugenja", SpellConstantsEnum::SHUGENJA),
				QDatabaseInterface::MakePair("Wu Jen", SpellConstantsEnum::WU_JEN) };
	
	const auto botPairs = {	QDatabaseInterface::MakePair("Assassin", SpellConstantsEnum::ASSASSIN),
					QDatabaseInterface::MakePair("Blackguard", SpellConstantsEnum::BLACKGUARD) };
	
	const auto betPairs = {	QDatabaseInterface::MakePair("Arcane Artifact", SpellConstantsEnum::ARCANE_ARTIFACT),
				QDatabaseInterface::MakePair("Corrupt", SpellConstantsEnum::CORRUPT),
				QDatabaseInterface::MakePair("Divine Artifact", SpellConstantsEnum::DIVINE_ARTIFACT),
				QDatabaseInterface::MakePair("Initiate", SpellConstantsEnum::INITIATE),
				QDatabaseInterface::MakePair("Oneiromancy", SpellConstantsEnum::ONEIROMANCY),
				QDatabaseInterface::MakePair("Sanctified", SpellConstantsEnum::SANCTIFIED) };
	
	const auto butPairs = {	QDatabaseInterface::MakePair("Air", SpellConstantsEnum::AIR_DOMAIN),
				QDatabaseInterface::MakePair("Abyss", SpellConstantsEnum::ABYSS_DOMAIN),
				QDatabaseInterface::MakePair("Animal", SpellConstantsEnum::ANIMAL_DOMAIN),
				QDatabaseInterface::MakePair("Arborea", SpellConstantsEnum::ARBOREA_DOMAIN),
				QDatabaseInterface::MakePair("Baator", SpellConstantsEnum::BAATOR_DOMAIN),
				QDatabaseInterface::MakePair("Balance", SpellConstantsEnum::BALANCE_DOMAIN),
				QDatabaseInterface::MakePair("Blackwater", SpellConstantsEnum::BLACKWATER_DOMAIN),
				QDatabaseInterface::MakePair("Cavern", SpellConstantsEnum::CAVERN_DOMAIN),
				QDatabaseInterface::MakePair("Celerity", SpellConstantsEnum::CELERITY_DOMAIN),
				QDatabaseInterface::MakePair("Celestia", SpellConstantsEnum::CELESTIA_DOMAIN),
				QDatabaseInterface::MakePair("Chaos", SpellConstantsEnum::CHAOS_DOMAIN),
				QDatabaseInterface::MakePair("Charm", SpellConstantsEnum::CHARM_DOMAIN),
				QDatabaseInterface::MakePair("Cold", SpellConstantsEnum::COLD_DOMAIN),
				QDatabaseInterface::MakePair("Community", SpellConstantsEnum::COMMUNITY_DOMAIN),
				QDatabaseInterface::MakePair("Competition", SpellConstantsEnum::COMPETITION_DOMAIN),
				QDatabaseInterface::MakePair("Corruption", SpellConstantsEnum::CORRUPTION_DOMAIN),
				QDatabaseInterface::MakePair("Courage", SpellConstantsEnum::COURAGE_DOMAIN),
				QDatabaseInterface::MakePair("Craft", SpellConstantsEnum::CRAFT_DOMAIN),
				QDatabaseInterface::MakePair("Creation", SpellConstantsEnum::CREATION_DOMAIN),
				QDatabaseInterface::MakePair("Darkness", SpellConstantsEnum::DARKNESS_DOMAIN),
				QDatabaseInterface::MakePair("Death", SpellConstantsEnum::DEATH_DOMAIN),
				QDatabaseInterface::MakePair("Deathbound", SpellConstantsEnum::DEATHBOUND_DOMAIN),
				QDatabaseInterface::MakePair("Demonic", SpellConstantsEnum::DEMONIC_DOMAIN),
				QDatabaseInterface::MakePair("Destruction", SpellConstantsEnum::DESTRUCTION_DOMAIN),
				QDatabaseInterface::MakePair("Diabolic", SpellConstantsEnum::DIABOLIC_DOMAIN),
				QDatabaseInterface::MakePair("Domination", SpellConstantsEnum::DOMINATION_DOMAIN),
				QDatabaseInterface::MakePair("Dragon", SpellConstantsEnum::DRAGON_DOMAIN),
				QDatabaseInterface::MakePair("Dream", SpellConstantsEnum::DREAM_DOMAIN),
				QDatabaseInterface::MakePair("Drow", SpellConstantsEnum::DROW_DOMAIN),
				QDatabaseInterface::MakePair("Dwarf", SpellConstantsEnum::DWARF_DOMAIN),
				QDatabaseInterface::MakePair("Earth", SpellConstantsEnum::EARTH_DOMAIN),
				QDatabaseInterface::MakePair("Elf", SpellConstantsEnum::ELF_DOMAIN),
				QDatabaseInterface::MakePair("Elysium", SpellConstantsEnum::ELYSIUM_DOMAIN),
				QDatabaseInterface::MakePair("Entropy", SpellConstantsEnum::ENTROPY_DOMAIN),
				QDatabaseInterface::MakePair("Envy", SpellConstantsEnum::ENVY_DOMAIN),
				QDatabaseInterface::MakePair("Evil", SpellConstantsEnum::EVIL_DOMAIN),
				QDatabaseInterface::MakePair("Family", SpellConstantsEnum::FAMILY_DOMAIN),
				QDatabaseInterface::MakePair("Fate", SpellConstantsEnum::FATE_DOMAIN),
				QDatabaseInterface::MakePair("Fire", SpellConstantsEnum::FIRE_DOMAIN),
				QDatabaseInterface::MakePair("Force", SpellConstantsEnum::FORCE_DOMAIN),
				QDatabaseInterface::MakePair("Fury", SpellConstantsEnum::FURY_DOMAIN),
				QDatabaseInterface::MakePair("Glory", SpellConstantsEnum::GLORY_DOMAIN),
				QDatabaseInterface::MakePair("Gluttony", SpellConstantsEnum::GLUTTONY_DOMAIN),
				QDatabaseInterface::MakePair("Good", SpellConstantsEnum::GOOD_DOMAIN),
				QDatabaseInterface::MakePair("Gnome", SpellConstantsEnum::GNOME_DOMAIN),
				QDatabaseInterface::MakePair("Greed", SpellConstantsEnum::GREED_DOMAIN),
				QDatabaseInterface::MakePair("Hades", SpellConstantsEnum::HADES_DOMAIN),
				QDatabaseInterface::MakePair("Halfling", SpellConstantsEnum::HALFLING_DOMAIN),
				QDatabaseInterface::MakePair("Hatred", SpellConstantsEnum::HATRED_DOMAIN),
				QDatabaseInterface::MakePair("Healing", SpellConstantsEnum::HEALING_DOMAIN),
				QDatabaseInterface::MakePair("Hunger", SpellConstantsEnum::HUNGER_DOMAIN),
				QDatabaseInterface::MakePair("Illusion", SpellConstantsEnum::ILLUSION_DOMAIN),
				QDatabaseInterface::MakePair("Incarnum", SpellConstantsEnum::INCARNUM_DOMAIN),
				QDatabaseInterface::MakePair("Inquisition", SpellConstantsEnum::INQUISITION_DOMAIN),
				QDatabaseInterface::MakePair("Knowledge", SpellConstantsEnum::KNOWLEDGE_DOMAIN),
				QDatabaseInterface::MakePair("Law", SpellConstantsEnum::LAW_DOMAIN),
				QDatabaseInterface::MakePair("Liberation", SpellConstantsEnum::LIBERATION_DOMAIN),
				QDatabaseInterface::MakePair("Limbo", SpellConstantsEnum::LIMBO_DOMAIN),
				QDatabaseInterface::MakePair("Luck", SpellConstantsEnum::LUCK_DOMAIN),
				QDatabaseInterface::MakePair("Lust", SpellConstantsEnum::LUST_DOMAIN),
				QDatabaseInterface::MakePair("Magic", SpellConstantsEnum::MAGIC_DOMAIN),
				QDatabaseInterface::MakePair("Madness", SpellConstantsEnum::MADNESS_DOMAIN),
				QDatabaseInterface::MakePair("Mechanus", SpellConstantsEnum::MECHANUS_DOMAIN),
				QDatabaseInterface::MakePair("Mentalism", SpellConstantsEnum::MENTALISM_DOMAIN),
				QDatabaseInterface::MakePair("Metal", SpellConstantsEnum::METAL_DOMAIN),
				QDatabaseInterface::MakePair("Mind", SpellConstantsEnum::MIND_DOMAIN),
				QDatabaseInterface::MakePair("Moon", SpellConstantsEnum::MOON_DOMAIN),
				QDatabaseInterface::MakePair("Mysticism", SpellConstantsEnum::MYSTICISM_DOMAIN),
				QDatabaseInterface::MakePair("Nobility", SpellConstantsEnum::NOBILITY_DOMAIN),
				QDatabaseInterface::MakePair("Ocean", SpellConstantsEnum::OCEAN_DOMAIN),
				QDatabaseInterface::MakePair("Ooze", SpellConstantsEnum::OOZE_DOMAIN),
				QDatabaseInterface::MakePair("Oracle", SpellConstantsEnum::ORACLE_DOMAIN),
				QDatabaseInterface::MakePair("Orc", SpellConstantsEnum::ORC_DOMAIN),
				QDatabaseInterface::MakePair("Pact", SpellConstantsEnum::PACT_DOMAIN),
				QDatabaseInterface::MakePair("Pestilence", SpellConstantsEnum::PESTILENCE_DOMAIN),
				QDatabaseInterface::MakePair("Planning", SpellConstantsEnum::PLANNING_DOMAIN),
				QDatabaseInterface::MakePair("Plant", SpellConstantsEnum::PLANT_DOMAIN),
				QDatabaseInterface::MakePair("Portal", SpellConstantsEnum::PORTAL_DOMAIN),
				QDatabaseInterface::MakePair("Pride", SpellConstantsEnum::PRIDE_DOMAIN),
				QDatabaseInterface::MakePair("Protection", SpellConstantsEnum::PROTECTION_DOMAIN),
				QDatabaseInterface::MakePair("Purification", SpellConstantsEnum::PURIFICATION_DOMAIN),
				QDatabaseInterface::MakePair("Renewal", SpellConstantsEnum::RENEWAL_DOMAIN),
				QDatabaseInterface::MakePair("Repose", SpellConstantsEnum::REPOSE_DOMAIN),
				QDatabaseInterface::MakePair("Retribution", SpellConstantsEnum::RETRIBUTION_DOMAIN),
				QDatabaseInterface::MakePair("Revered Ancestor", SpellConstantsEnum::REVERED_ANCESTOR_DOMAIN),
				QDatabaseInterface::MakePair("Rune", SpellConstantsEnum::RUNE_DOMAIN),
				QDatabaseInterface::MakePair("Sand", SpellConstantsEnum::SAND_DOMAIN),
				QDatabaseInterface::MakePair("Scalykind", SpellConstantsEnum::SCALYKIND_DOMAIN),
				QDatabaseInterface::MakePair("Seafolk", SpellConstantsEnum::SEAFOLK_DOMAIN),
				QDatabaseInterface::MakePair("Slime", SpellConstantsEnum::SLIME_DOMAIN),
				QDatabaseInterface::MakePair("Sloth", SpellConstantsEnum::SLOTH_DOMAIN),
				QDatabaseInterface::MakePair("Spell", SpellConstantsEnum::SPELL_DOMAIN),
				QDatabaseInterface::MakePair("Spider", SpellConstantsEnum::SPIDER_DOMAIN),
				QDatabaseInterface::MakePair("Spite", SpellConstantsEnum::SPITE_DOMAIN),
				QDatabaseInterface::MakePair("Storm", SpellConstantsEnum::STORM_DOMAIN),
				QDatabaseInterface::MakePair("Strength", SpellConstantsEnum::STRENGTH_DOMAIN),
				QDatabaseInterface::MakePair("Suffering", SpellConstantsEnum::SUFFERING_DOMAIN),
				QDatabaseInterface::MakePair("Summer", SpellConstantsEnum::SUMMER_DOMAIN),
				QDatabaseInterface::MakePair("Summoner", SpellConstantsEnum::SUMMONER_DOMAIN),
				QDatabaseInterface::MakePair("Sun", SpellConstantsEnum::SUN_DOMAIN),
				QDatabaseInterface::MakePair("Temptation", SpellConstantsEnum::TEMPTATION_DOMAIN),
				QDatabaseInterface::MakePair("Thirst", SpellConstantsEnum::THIRST_DOMAIN),
				QDatabaseInterface::MakePair("Time", SpellConstantsEnum::TIME_DOMAIN),
				QDatabaseInterface::MakePair("Trade", SpellConstantsEnum::TRADE_DOMAIN),
				QDatabaseInterface::MakePair("Transformation", SpellConstantsEnum::TRANSFORMATION_DOMAIN),
				QDatabaseInterface::MakePair("Travel", SpellConstantsEnum::TRAVEL_DOMAIN),
				QDatabaseInterface::MakePair("Trickery", SpellConstantsEnum::TRICKERY_DOMAIN),
				QDatabaseInterface::MakePair("Truth", SpellConstantsEnum::TRUTH_DOMAIN),
				QDatabaseInterface::MakePair("Tyranny", SpellConstantsEnum::TYRANNY_DOMAIN),
				QDatabaseInterface::MakePair("Undeath", SpellConstantsEnum::UNDEATH_DOMAIN),
				QDatabaseInterface::MakePair("Vile Darkness", SpellConstantsEnum::VILE_DARKNESS_DOMAIN),
				QDatabaseInterface::MakePair("War", SpellConstantsEnum::WAR_DOMAIN),
				QDatabaseInterface::MakePair("Warforged", SpellConstantsEnum::WARFORGED_DOMAIN),
				QDatabaseInterface::MakePair("Water", SpellConstantsEnum::WATER_DOMAIN),
				QDatabaseInterface::MakePair("Wealth", SpellConstantsEnum::WEALTH_DOMAIN),
				QDatabaseInterface::MakePair("Windstorm", SpellConstantsEnum::WINDSTORM_DOMAIN),
				QDatabaseInterface::MakePair("Wrath", SpellConstantsEnum::WRATH_DOMAIN) };
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseSpecial(const QFont& font, QGridLayout* layout)
{
	const auto specialBox = new QGroupBox("Special", this);
	const auto specialLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Body Leech", PowerConstantsEnum::BODY_LEECH),
				QDatabaseInterface::MakePair("Egoist", PowerConstantsEnum::EGOIST),
				QDatabaseInterface::MakePair("Kineticist", PowerConstantsEnum::KINETICIST),
				QDatabaseInterface::MakePair("Nomad", PowerConstantsEnum::NOMAD),
				QDatabaseInterface::MakePair("Seer", PowerConstantsEnum::SEER),
				QDatabaseInterface::MakePair("Shaper", PowerConstantsEnum::SHAPER),
				QDatabaseInterface::MakePair("Telepath", PowerConstantsEnum::TELEPATH) };
	
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
	
	const auto butPairs = {	QDatabaseInterface::MakePair("Air", PowerConstantsEnum::AIR_MANTLE),
				QDatabaseInterface::MakePair("Chaos", PowerConstantsEnum::CHAOS_MANTLE),
				QDatabaseInterface::MakePair("Communication", PowerConstantsEnum::COMMUNICATION_MANTLE),
				QDatabaseInterface::MakePair("Conflict", PowerConstantsEnum::CONFLICT_MANTLE),
				QDatabaseInterface::MakePair("Consumption", PowerConstantsEnum::CONSUMPTION_MANTLE),
				QDatabaseInterface::MakePair("Corruption and Madness", PowerConstantsEnum::CORRUPTION_AND_MADNESS_MANTLE),
				QDatabaseInterface::MakePair("Creation", PowerConstantsEnum::CREATION_MANTLE),
				QDatabaseInterface::MakePair("Death", PowerConstantsEnum::DEATH_MANTLE),
				QDatabaseInterface::MakePair("Deception", PowerConstantsEnum::DECEPTION_MANTLE),
				QDatabaseInterface::MakePair("Destruction", PowerConstantsEnum::DESTRUCTION_MANTLE),
				QDatabaseInterface::MakePair("Earth", PowerConstantsEnum::EARTH_MANTLE),
				QDatabaseInterface::MakePair("Elements", PowerConstantsEnum::ELEMENTS_MANTLE),
				QDatabaseInterface::MakePair("Energy", PowerConstantsEnum::ENERGY_MANTLE),
				QDatabaseInterface::MakePair("Evil", PowerConstantsEnum::EVIL_MANTLE),
				QDatabaseInterface::MakePair("Fate", PowerConstantsEnum::FATE_MANTLE),
				QDatabaseInterface::MakePair("Fire", PowerConstantsEnum::FIRE_MANTLE),
				QDatabaseInterface::MakePair("Force", PowerConstantsEnum::FORCE_MANTLE),
				QDatabaseInterface::MakePair("Freedom", PowerConstantsEnum::FREEDOM_MANTLE),
				QDatabaseInterface::MakePair("Good", PowerConstantsEnum::GOOD_MANTLE),
				QDatabaseInterface::MakePair("Guardian", PowerConstantsEnum::GUARDIAN_MANTLE),
				QDatabaseInterface::MakePair("Justice", PowerConstantsEnum::JUSTICE_MANTLE),
				QDatabaseInterface::MakePair("Knowledge", PowerConstantsEnum::KNOWLEDGE_MANTLE),
				QDatabaseInterface::MakePair("Law", PowerConstantsEnum::LAW_MANTLE),
				QDatabaseInterface::MakePair("Life", PowerConstantsEnum::LIFE_MANTLE),
				QDatabaseInterface::MakePair("Light and Darkness", PowerConstantsEnum::LIGHT_AND_DARKNESS_MANTLE),
				QDatabaseInterface::MakePair("Magic", PowerConstantsEnum::MAGIC_MANTLE),
				QDatabaseInterface::MakePair("Mental Power", PowerConstantsEnum::MENTAL_POWER_MANTLE),
				QDatabaseInterface::MakePair("Natural World", PowerConstantsEnum::NATURAL_WORLD_MANTLE),
				QDatabaseInterface::MakePair("Pain and Suffering", PowerConstantsEnum::PAIN_AND_SUFFERING_MANTLE),
				QDatabaseInterface::MakePair("Physical Power", PowerConstantsEnum::PHYSICAL_POWER_MANTLE),
				QDatabaseInterface::MakePair("Plane", PowerConstantsEnum::PLANE_MANTLE),
				QDatabaseInterface::MakePair("Repose", PowerConstantsEnum::REPOSE_MANTLE),
				QDatabaseInterface::MakePair("Time", PowerConstantsEnum::TIME_MANTLE),
				QDatabaseInterface::MakePair("Water", PowerConstantsEnum::WATER_MANTLE) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto arcaneButton = new QPushButton("Arcane");
	QDatabaseInterface::multibits.emplace_back(arcaneButton, CustomBitset());
	
	auto& arcaneBitset = QDatabaseInterface::multibits.back().second;
	arcaneBitset.set(SpellConstantsEnum::BARD);
	arcaneBitset.set(SpellConstantsEnum::SORCERER);
	arcaneBitset.set(SpellConstantsEnum::WIZARD);
	
	arcaneBitset.set(SpellConstantsEnum::ASSASSIN);
	arcaneBitset.set(SpellConstantsEnum::ARCANE_ARTIFACT);
	arcaneBitset.set(SpellConstantsEnum::BEGUILER);
	arcaneBitset.set(SpellConstantsEnum::CORRUPT);
	arcaneBitset.set(SpellConstantsEnum::DREAD_NECROMANCER);
	arcaneBitset.set(SpellConstantsEnum::DUSKBLADE);
	arcaneBitset.set(SpellConstantsEnum::HEXBLADE);
	arcaneBitset.set(SpellConstantsEnum::ONEIROMANCY);
	arcaneBitset.set(SpellConstantsEnum::SANCTIFIED);
	arcaneBitset.set(SpellConstantsEnum::WU_JEN);
	
	const auto divineButton = new QPushButton("Divine");
	QDatabaseInterface::multibits.emplace_back(divineButton, CustomBitset());
	
	auto& divineBitset = QDatabaseInterface::multibits.back().second;
	divineBitset.set(SpellConstantsEnum::CLERIC);
	divineBitset.set(SpellConstantsEnum::DRUID);
	divineBitset.set(SpellConstantsEnum::PALADIN);
	divineBitset.set(SpellConstantsEnum::RANGER);
	
	divineBitset.set(SpellConstantsEnum::ADEPT);
	divineBitset.set(SpellConstantsEnum::BLACKGUARD);
	divineBitset.set(SpellConstantsEnum::CORRUPT);
	divineBitset.set(SpellConstantsEnum::DEATH_DELVER);
	divineBitset.set(SpellConstantsEnum::DIVINE_ARTIFACT);
	divineBitset.set(SpellConstantsEnum::HEALER);
	divineBitset.set(SpellConstantsEnum::INITIATE);
	divineBitset.set(SpellConstantsEnum::ONEIROMANCY);
	divineBitset.set(SpellConstantsEnum::SANCTIFIED);
	divineBitset.set(SpellConstantsEnum::SHUGENJA);
	
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
	infusionBitset.set(SpellConstantsEnum::ARTIFICER);
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseFeatures(const QFont& font, QGridLayout* layout)
{
	const auto featureBox = new QGroupBox("Features", this);
	const auto featureLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Augment", PowerConstantsEnum::AUGMENT),
					QDatabaseInterface::MakePair("Experience", PowerConstantsEnum::EXPERIENCE) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseSchoolsOrDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto schoolBox = new QGroupBox("Schools", this);
	const auto schoolLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Abjuration", SpellConstantsEnum::ABJURATION),
				QDatabaseInterface::MakePair("Conjuration", SpellConstantsEnum::CONJURATION),
				QDatabaseInterface::MakePair("Divination", SpellConstantsEnum::DIVINATION),
				QDatabaseInterface::MakePair("Enchantment", SpellConstantsEnum::ENCHANTMENT),
				QDatabaseInterface::MakePair("Evocation", SpellConstantsEnum::EVOCATION),
				QDatabaseInterface::MakePair("Illusion", SpellConstantsEnum::ILLUSION),
				QDatabaseInterface::MakePair("Necromancy", SpellConstantsEnum::NECROMANCY),
				QDatabaseInterface::MakePair("Transmutation", SpellConstantsEnum::TRANSMUTATION),
				QDatabaseInterface::MakePair("Universal", SpellConstantsEnum::UNIVERSAL) };
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseSchoolsOrDisciplines(const QFont& font, QGridLayout* layout)
{
	const auto disciplineBox = new QGroupBox("Disciplines", this);
	const auto disciplineLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Clairsentience", PowerConstantsEnum::CLAIRSENTIENCE),
				QDatabaseInterface::MakePair("Metacreativity", PowerConstantsEnum::METACREATIVITY),
				QDatabaseInterface::MakePair("Psychokinesis", PowerConstantsEnum::PSYCHOKINESIS),
				QDatabaseInterface::MakePair("Psychometabolism", PowerConstantsEnum::PSYCHOMETABOLISM),
				QDatabaseInterface::MakePair("Psychoportation", PowerConstantsEnum::PSYCHOPORTATION),
				QDatabaseInterface::MakePair("Telepathy", PowerConstantsEnum::TELEPATHY) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseSubschoolsOrSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subschoolBox = new QGroupBox("Subschools", this);
	const auto subschoolLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Calling", SpellConstantsEnum::CALLING),
				QDatabaseInterface::MakePair("Charm", SpellConstantsEnum::CHARM),
				QDatabaseInterface::MakePair("Compulsion", SpellConstantsEnum::COMPULSION),
				QDatabaseInterface::MakePair("Creation", SpellConstantsEnum::CREATION),
				QDatabaseInterface::MakePair("Figment", SpellConstantsEnum::FIGMENT),
				QDatabaseInterface::MakePair("Glamer", SpellConstantsEnum::GLAMER),
				QDatabaseInterface::MakePair("Healing", SpellConstantsEnum::HEALING),
				QDatabaseInterface::MakePair("Pattern", SpellConstantsEnum::PATTERN),
				QDatabaseInterface::MakePair("Phantasm", SpellConstantsEnum::PHANTASM),
				QDatabaseInterface::MakePair("Polymorph", SpellConstantsEnum::POLYMORPH),
				QDatabaseInterface::MakePair("Scrying", SpellConstantsEnum::SCRYING),
				QDatabaseInterface::MakePair("Shadow", SpellConstantsEnum::SHADOW),
				QDatabaseInterface::MakePair("Summoning", SpellConstantsEnum::SUMMONING),
				QDatabaseInterface::MakePair("Teleportation", SpellConstantsEnum::TELEPORTATION) };
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseSubschoolsOrSubdisciplines(const QFont& font, QGridLayout* layout)
{
	const auto subdisciplineBox = new QGroupBox("Subdisciplines", this);
	const auto subdisciplineLayout = new QHBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Charm", PowerConstantsEnum::CHARM),
				QDatabaseInterface::MakePair("Compulsion", PowerConstantsEnum::COMPULSION),
				QDatabaseInterface::MakePair("Creation", PowerConstantsEnum::CREATION),
				QDatabaseInterface::MakePair("Healing", PowerConstantsEnum::HEALING),
				QDatabaseInterface::MakePair("Scrying", PowerConstantsEnum::SCRYING),
				QDatabaseInterface::MakePair("Teleportation", PowerConstantsEnum::TELEPORTATION) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseMaterialsOrDisplays(const QFont& font, QGridLayout* layout)
{
	const auto materialBox = new QGroupBox("Materials", this);
	const auto materialLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Focus", SpellConstantsEnum::FOCUS),
				QDatabaseInterface::MakePair("Divine Focus", SpellConstantsEnum::DIVINE_FOCUS),
				QDatabaseInterface::MakePair("Verbal", SpellConstantsEnum::VERBAL),
				QDatabaseInterface::MakePair("Somatic", SpellConstantsEnum::SOMATIC),
				QDatabaseInterface::MakePair("Material", SpellConstantsEnum::MATERIAL),
				QDatabaseInterface::MakePair("Gold", SpellConstantsEnum::GOLD),
				QDatabaseInterface::MakePair("Experience", SpellConstantsEnum::EXPERIENCE) };
	
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
	
	const auto butPairs = {	QDatabaseInterface::MakePair("Alignment", SpellConstantsEnum::ALIGNMENT),
				QDatabaseInterface::MakePair("Corruption", SpellConstantsEnum::CORRUPT),
				QDatabaseInterface::MakePair("Dragonmark", SpellConstantsEnum::DRAGONMARK),
				QDatabaseInterface::MakePair("Essentia", SpellConstantsEnum::ESSENTIA),
				QDatabaseInterface::MakePair("Racial", SpellConstantsEnum::RACIAL),
				QDatabaseInterface::MakePair("Sacrifice", SpellConstantsEnum::SANCTIFIED),
				QDatabaseInterface::MakePair("Verbal (Bard only)", SpellConstantsEnum::VERBAL_BARD) };
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseMaterialsOrDisplays(const QFont& font, QGridLayout* layout)
{
	const auto displayBox = new QGroupBox("Displays", this);
	const auto displayLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Auditory", PowerConstantsEnum::AUDITORY),
				QDatabaseInterface::MakePair("Material", PowerConstantsEnum::MATERIAL),
				QDatabaseInterface::MakePair("Mental", PowerConstantsEnum::MENTAL),
				QDatabaseInterface::MakePair("Olfactory", PowerConstantsEnum::OLFACTORY),
				QDatabaseInterface::MakePair("Visual", PowerConstantsEnum::VISUAL) };
	
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
qint32 QDatabaseInterface<SpellConstantsEnum>::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", this);
	const auto descriptorLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Acid", SpellConstantsEnum::ACID),
				QDatabaseInterface::MakePair("Air", SpellConstantsEnum::AIR),
				QDatabaseInterface::MakePair("Chaotic", SpellConstantsEnum::CHAOTIC),
				QDatabaseInterface::MakePair("Cold", SpellConstantsEnum::COLD),
				QDatabaseInterface::MakePair("Darkness", SpellConstantsEnum::DARKNESS),
				QDatabaseInterface::MakePair("Death", SpellConstantsEnum::DEATH),
				QDatabaseInterface::MakePair("Earth", SpellConstantsEnum::EARTH),
				QDatabaseInterface::MakePair("Electricity", SpellConstantsEnum::ELECTRICITY),
				QDatabaseInterface::MakePair("Evil", SpellConstantsEnum::EVIL),
				QDatabaseInterface::MakePair("Fear", SpellConstantsEnum::FEAR),
				QDatabaseInterface::MakePair("Fire", SpellConstantsEnum::FIRE),
				QDatabaseInterface::MakePair("Force", SpellConstantsEnum::FORCE),
				QDatabaseInterface::MakePair("Good", SpellConstantsEnum::GOOD),
				QDatabaseInterface::MakePair("Incarnum", SpellConstantsEnum::INCARNUM),
				QDatabaseInterface::MakePair("Language", SpellConstantsEnum::LANGUAGE_DEPENDENT),
				QDatabaseInterface::MakePair("Lawful", SpellConstantsEnum::LAWFUL),
				QDatabaseInterface::MakePair("Light", SpellConstantsEnum::LIGHT),
				QDatabaseInterface::MakePair("Mind-Affecting", SpellConstantsEnum::MIND_AFFECTING),
				QDatabaseInterface::MakePair("Sonic", SpellConstantsEnum::SONIC),
				QDatabaseInterface::MakePair("Water", SpellConstantsEnum::WATER) };
	
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
	
	const auto butPairs = { QDatabaseInterface::MakePair("Investiture", SpellConstantsEnum::INVESTITURE),
				QDatabaseInterface::MakePair("Mindset", SpellConstantsEnum::MINDSET) };
	
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
qint32 QDatabaseInterface<PowerConstantsEnum>::initialiseDescriptors(const QFont& font, QGridLayout* layout)
{
	const auto descriptorBox = new QGroupBox("Descriptors", this);
	const auto descriptorLayout = new QGridLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("Acid", PowerConstantsEnum::ACID),
				QDatabaseInterface::MakePair("Cold", PowerConstantsEnum::COLD),
				QDatabaseInterface::MakePair("Darkness", PowerConstantsEnum::DARKNESS),
				QDatabaseInterface::MakePair("Death", PowerConstantsEnum::DEATH),
				QDatabaseInterface::MakePair("Electricity", PowerConstantsEnum::ELECTRICITY),
				QDatabaseInterface::MakePair("Evil", PowerConstantsEnum::EVIL),
				QDatabaseInterface::MakePair("Fear", PowerConstantsEnum::FEAR),
				QDatabaseInterface::MakePair("Fire", PowerConstantsEnum::FIRE),
				QDatabaseInterface::MakePair("Force", PowerConstantsEnum::FORCE),
				QDatabaseInterface::MakePair("Good", PowerConstantsEnum::GOOD),
				QDatabaseInterface::MakePair("Language", PowerConstantsEnum::LANGUAGE_DEPENDENT),
				QDatabaseInterface::MakePair("Light", PowerConstantsEnum::LIGHT),
				QDatabaseInterface::MakePair("Mind-Affecting", PowerConstantsEnum::MIND_AFFECTING),
				QDatabaseInterface::MakePair("Shadow", PowerConstantsEnum::SHADOW),
				QDatabaseInterface::MakePair("Sonic", PowerConstantsEnum::SONIC) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseSources(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto sourceBox = new QGroupBox("Sources", this);
	const auto sourceLayout = new QVBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("PHB", SpellConstantsEnum::PLAYERS_HANDBOOK),
				QDatabaseInterface::MakePair("SpC", SpellConstantsEnum::SPELL_COMPENDIUM) };
	
	for (const auto& pr : bitPairs)
	{
		sourceLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("An", SpellConstantsEnum::ANAUROCH_EMPIRE_OF_SHADE),
				QDatabaseInterface::MakePair("CCha", SpellConstantsEnum::COMPLETE_CHAMPION),
				QDatabaseInterface::MakePair("Ci", SpellConstantsEnum::CITYSCAPE),
				QDatabaseInterface::MakePair("CMge", SpellConstantsEnum::COMPLETE_MAGE),
				QDatabaseInterface::MakePair("CoS", SpellConstantsEnum::CITY_OF_STORMREACH),
				QDatabaseInterface::MakePair("CoV", SpellConstantsEnum::CHAMPIONS_OF_VALOR),
				QDatabaseInterface::MakePair("CR", SpellConstantsEnum::CHAMPIONS_OF_RUIN),
				QDatabaseInterface::MakePair("CSco", SpellConstantsEnum::COMPLETE_SCOUNDREL),
				QDatabaseInterface::MakePair("CSW", SpellConstantsEnum::CITY_OF_SPLENDORS_WATERDEEP),
				QDatabaseInterface::MakePair("DoE", SpellConstantsEnum::DRAGONS_OF_EBERRON),
				QDatabaseInterface::MakePair("DoF", SpellConstantsEnum::DRAGONS_OF_FAERUN),
				QDatabaseInterface::MakePair("Dmkd", SpellConstantsEnum::DRAGONMARKED),
				QDatabaseInterface::MakePair("DrM", SpellConstantsEnum::DRAGON_MAGIC),
				QDatabaseInterface::MakePair("DrU", SpellConstantsEnum::DROW_OF_THE_UNDERDARK),
				QDatabaseInterface::MakePair("EDP", SpellConstantsEnum::EXPEDITION_TO_DEMONWEB_PITS),
				QDatabaseInterface::MakePair("EU", SpellConstantsEnum::EXPEDITION_TO_UNDERMOUNTAIN),
				QDatabaseInterface::MakePair("FoE", SpellConstantsEnum::FAITHS_OF_EBERRON),
				QDatabaseInterface::MakePair("FC1", SpellConstantsEnum::FIENDISH_CODEX_I),
				QDatabaseInterface::MakePair("FC2", SpellConstantsEnum::FIENDISH_CODEX_II),
				QDatabaseInterface::MakePair("FN", SpellConstantsEnum::FIVE_NATIONS),
				QDatabaseInterface::MakePair("FW", SpellConstantsEnum::FORGE_OF_WAR),
				QDatabaseInterface::MakePair("HB", SpellConstantsEnum::HEROES_OF_BATTLE),
				QDatabaseInterface::MakePair("HH", SpellConstantsEnum::HEROES_OF_HORROR),
				QDatabaseInterface::MakePair("LoM", SpellConstantsEnum::LORDS_OF_MADNESS),
				QDatabaseInterface::MakePair("MM4", SpellConstantsEnum::MONSTER_MANUAL_IV),
				QDatabaseInterface::MakePair("MoE", SpellConstantsEnum::MAGIC_OF_EBERRON),
				QDatabaseInterface::MakePair("MoI", SpellConstantsEnum::MAGIC_OF_INCARNUM),
				QDatabaseInterface::MakePair("PGE", SpellConstantsEnum::PLAYERS_GUIDE_TO_EBERRON),
				QDatabaseInterface::MakePair("PH2", SpellConstantsEnum::PLAYERS_HANDBOOK_II),
				QDatabaseInterface::MakePair("PoF", SpellConstantsEnum::POWER_OF_FAERUN),
				QDatabaseInterface::MakePair("Rav", SpellConstantsEnum::EXPEDITION_TO_CASTLE_RAVENLOFT),
				QDatabaseInterface::MakePair("RDr", SpellConstantsEnum::RACES_OF_THE_DRAGON),
				QDatabaseInterface::MakePair("RE", SpellConstantsEnum::RACES_OF_EBERRON),
				QDatabaseInterface::MakePair("Sa", SpellConstantsEnum::SANDSTORM),
				QDatabaseInterface::MakePair("SoS", SpellConstantsEnum::SECRETS_OF_SARLONA),
				QDatabaseInterface::MakePair("SoX", SpellConstantsEnum::SECRETS_OF_XENDRIK),
				QDatabaseInterface::MakePair("Sto", SpellConstantsEnum::STORMWRACK),
				QDatabaseInterface::MakePair("WL", SpellConstantsEnum::WEAPONS_OF_LEGACY) };
	
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
void QDatabaseInterface<PowerConstantsEnum>::initialiseSources(const QFont& font, QGridLayout* layout, qint32 delta)
{
	const auto sourceBox = new QGroupBox("Sources", this);
	const auto sourceLayout = new QVBoxLayout();
	
	const auto bitPairs = {	QDatabaseInterface::MakePair("XPH", PowerConstantsEnum::EXPANDED_PSIONICS_HANDBOOK),
				QDatabaseInterface::MakePair("CPsi", PowerConstantsEnum::COMPLETE_PSIONIC) };
	
	for (const auto& pr : bitPairs)
	{
		sourceLayout->addWidget(pr.first);
		pr.first->setObjectName("A");
		pr.first->setFont(font);
		
		QObject::connect(pr.first, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
		QDatabaseInterface::bits.push_back(pr);
	}
	
	const auto butPairs = {	QDatabaseInterface::MakePair("DrM", PowerConstantsEnum::DRAGON_MAGIC),
				QDatabaseInterface::MakePair("FoE", PowerConstantsEnum::FAITHS_OF_EBERRON),
				QDatabaseInterface::MakePair("Hyp", PowerConstantsEnum::HYPERCONSCIOUS),
				QDatabaseInterface::MakePair("MoE", PowerConstantsEnum::MAGIC_OF_EBERRON),
				QDatabaseInterface::MakePair("MoI", PowerConstantsEnum::MAGIC_OF_INCARNUM),
				QDatabaseInterface::MakePair("PGE", PowerConstantsEnum::PLAYERS_GUIDE_TO_EBERRON),
				QDatabaseInterface::MakePair("RDr", PowerConstantsEnum::RACES_OF_THE_DRAGON),
				QDatabaseInterface::MakePair("RW", PowerConstantsEnum::RACES_OF_THE_WILD),
				QDatabaseInterface::MakePair("SoS", PowerConstantsEnum::SECRETS_OF_SARLONA),
				QDatabaseInterface::MakePair("Sto", PowerConstantsEnum::STORMWRACK),
				QDatabaseInterface::MakePair("WL", PowerConstantsEnum::WEAPONS_OF_LEGACY),
				QDatabaseInterface::MakePair("Web", PowerConstantsEnum::WEB) };
	
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
void QDatabaseInterface<SpellConstantsEnum>::initialiseBars(const QFont& font, QGridLayout* layout, qint32 delta)
{
	layout->addWidget(QDatabaseInterfaceIntermediary::nameLineEdit, delta + 8, 0, 1, 4);
	layout->addWidget(QDatabaseInterfaceIntermediary::loreLineEdit, delta + 8, 4, 1, 5);
	
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::ANAUROCH_EMPIRE_OF_SHADE);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::CHAMPIONS_OF_RUIN);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::CHAMPIONS_OF_VALOR);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::CITY_OF_SPLENDORS_WATERDEEP);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::CITY_OF_STORMREACH);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::CITYSCAPE);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::COMPLETE_CHAMPION);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::COMPLETE_MAGE);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::COMPLETE_SCOUNDREL);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::DRAGON_MAGIC);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::DRAGONMARKED);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::DRAGONS_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::DRAGONS_OF_FAERUN);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::DROW_OF_THE_UNDERDARK);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::EXPEDITION_TO_CASTLE_RAVENLOFT);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::EXPEDITION_TO_DEMONWEB_PITS);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::EXPEDITION_TO_UNDERMOUNTAIN);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::FAITHS_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::FIENDISH_CODEX_I);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::FIENDISH_CODEX_II);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::FIVE_NATIONS);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::FORGE_OF_WAR);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::HEROES_OF_BATTLE);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::HEROES_OF_HORROR);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::LORDS_OF_MADNESS);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::MAGIC_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::MONSTER_MANUAL_IV);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::MAGIC_OF_INCARNUM);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::PLAYERS_GUIDE_TO_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::PLAYERS_HANDBOOK);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::PLAYERS_HANDBOOK_II);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::POWER_OF_FAERUN);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::RACES_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::RACES_OF_THE_DRAGON);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::SANDSTORM);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::SECRETS_OF_SARLONA);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::SECRETS_OF_XENDRIK);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::SPELL_COMPENDIUM);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::STORMWRACK);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::WEAPONS_OF_LEGACY);
	QDatabaseInterface::RevisedBitset.set(SpellConstantsEnum::WEB35);
	
	const auto button35e = new QPushButton("3.5e");
	QDatabaseInterface::multibits.emplace_back(button35e, QDatabaseInterface::RevisedBitset);
	
	layout->addWidget(button35e, delta + 8, 9, 1, 1);
	button35e->setObjectName("B");
	button35e->setFont(font);
	
	QObject::connect(button35e, SIGNAL(released(void)), this, SLOT(switchButtonState(void)));
}

template<>
void QDatabaseInterface<PowerConstantsEnum>::initialiseBars(const QFont&, QGridLayout* layout, qint32 delta)
{
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::COMPLETE_PSIONIC);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::DRAGON_MAGIC);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::EXPANDED_PSIONICS_HANDBOOK);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::FAITHS_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::HYPERCONSCIOUS);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::MAGIC_OF_EBERRON);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::MAGIC_OF_INCARNUM);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::PLAYERS_GUIDE_TO_EBERRON);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::RACES_OF_THE_DRAGON);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::RACES_OF_THE_WILD);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::SECRETS_OF_SARLONA);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::STORMWRACK);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::WEAPONS_OF_LEGACY);
	QDatabaseInterface::RevisedBitset.set(PowerConstantsEnum::WEB);
	
	layout->addWidget(QDatabaseInterfaceIntermediary::nameLineEdit, delta + 8, 0, 1, 5);
	layout->addWidget(QDatabaseInterfaceIntermediary::loreLineEdit, delta + 8, 5, 1, 5);
}
