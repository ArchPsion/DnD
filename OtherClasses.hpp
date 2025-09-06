#ifndef __OTHER_CLASSES_HPP__
#define __OTHER_CLASSES_HPP__

// Standard Libraries
#include <vector>

// Qt Libraries
#include <QPushButton>

// Custom Libraries
#include "Enum.hpp"
#include "HexBitset.hpp"

struct HexFamily
{
	QPushButton*			masterButton = nullptr;
	quint32				bit = compl(0u);
	std::vector<HexFamily>		familyGroups;
	
	HexFamily(void)
	{
	}
	
	template<typename Type>
	HexFamily(Type foo) : bit(static_cast<quint32>(foo))
	{
	}
	
	HexFamily(const QString& text, QWidget* parent) : masterButton(new QPushButton(text, parent))
	{
	}
	
	template<typename Type>
	HexFamily(const QString& text, QWidget* parent, Type foo) : masterButton(new QPushButton(text, parent)), bit(static_cast<quint32>(foo))
	{
	}
};

template<quint32 Number>
struct HexFile
{
	QString			name = "";
	HexBitset<Number>	bits;
	
	qint32			infoPositionInFile = -1;
	qint32			textPositionInFile = -1;
	
	HexFile(const QString& n, const QString& b, qint32 ip, qint32 tp) : name(n), bits(b), infoPositionInFile(ip), textPositionInFile(tp)
	{
	}
};

#endif
