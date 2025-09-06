#ifndef __HEX_BITSET_PACK_HPP__
#define __HEX_BITSET_PACK_HPP__

// Standard Libraries
#include <vector>

// Custom Libraries
#include "HexBitset.hpp"
#include "OtherClasses.hpp"

template<quint32 Number>
class HexBitsetPack
{
	private:
	
		HexBitset<Number>					greenBitset;
		HexBitset<Number>					redBitset;
		std::vector<HexBitset<Number>>				yellowBitsets;
		
		inline void						readBits(const HexFamily&, HexBitset<Number>&);
		inline void						readSecondaryBits(const HexFamily&, HexBitset<Number>&, bool);
	
	public:
	
		inline							HexBitsetPack(void);
		inline							HexBitsetPack(const std::vector<HexFamily>&);
		
		inline const HexBitset<Number>&				getGreenBitset(void) const;
		inline const HexBitset<Number>&				getRedBitset(void) const;
		inline const std::vector<HexBitset<Number>>&		getYellowBitsets(void) const;
};

template<quint32 Number>
HexBitsetPack<Number>::HexBitsetPack(void)
{
}

template<quint32 Number>
HexBitsetPack<Number>::HexBitsetPack(const std::vector<HexFamily>& vect)
{
	for (const auto& fml : vect)
	{
		auto yellowBitset = HexBitset<Number>();
		HexBitsetPack::readBits(fml, yellowBitset);
		
		if (not yellowBitset.null())
			HexBitsetPack::yellowBitsets.push_back(yellowBitset);
	}
}

template<quint32 Number>
const HexBitset<Number>& HexBitsetPack<Number>::getGreenBitset(void) const
{
	return HexBitsetPack::greenBitset;
}

template<quint32 Number>
const HexBitset<Number>& HexBitsetPack<Number>::getRedBitset(void) const
{
	return HexBitsetPack::redBitset;
}

template<quint32 Number>
const std::vector<HexBitset<Number>>& HexBitsetPack<Number>::getYellowBitsets(void) const
{
	return HexBitsetPack::yellowBitsets;
}

template<quint32 Number>
void HexBitsetPack<Number>::readBits(const HexFamily& fml, HexBitset<Number>& yellowBitset)
{
	if (fml.masterButton == nullptr)
	{
		for (const auto& foo : fml.familyGroups)
			HexBitsetPack::readBits(foo, yellowBitset);
	}
	else
	{
		const auto name = fml.masterButton->objectName();
		const auto size = name.size();
		
		switch (size)
		{
			case 1u:
			{
				for (const auto& foo : fml.familyGroups)
					HexBitsetPack::readSecondaryBits(foo, yellowBitset, false);
				
				break;
			}
			
			case 2u:
			{
				if (fml.familyGroups.empty())
					HexBitsetPack::greenBitset.setBit(fml.bit);
				else
				{
					auto anotherYellowBitset = HexBitset<Number>();
					HexBitsetPack::readSecondaryBits(fml, anotherYellowBitset, true);
					
					if (not anotherYellowBitset.null())
						HexBitsetPack::yellowBitsets.push_back(anotherYellowBitset);
				}
					
				break;
			}
			
			case 3u:
			{
				if (fml.familyGroups.empty())
					HexBitsetPack::redBitset.setBit(fml.bit);
				else
					HexBitsetPack::readSecondaryBits(fml, HexBitsetPack::redBitset, true);
					
				break;
			}
			
			case 4u:
			{
				if (fml.familyGroups.empty())
					yellowBitset.setBit(fml.bit);
				else
					HexBitsetPack::readSecondaryBits(fml, yellowBitset, true);
					
				break;
			}
			
			default:
				break;
		}
	}
}

template<quint32 Number>
void HexBitsetPack<Number>::readSecondaryBits(const HexFamily& fml, HexBitset<Number>& theBitset, bool forced)
{
	for (const auto& child : fml.familyGroups)
	{
		if (forced)
			theBitset.setBit(child.bit);
		else
		{
			const auto name = child.masterButton->objectName();
			const auto size = name.size();
			
			switch (size)
			{
				case 2u:
					HexBitsetPack::greenBitset.setBit(child.bit);
					break;
				
				case 3u:
					HexBitsetPack::redBitset.setBit(child.bit);
					break;
				
				case 4u:
					theBitset.setBit(child.bit);
					break;
				
				default:
					break;
			}
		}
	}
}

#endif
