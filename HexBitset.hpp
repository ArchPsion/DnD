#ifndef __BITSET_HPP__
#define __BITSET_HPP__

// Standard Libraries
#include <array>

template <quint64 Number>
class HexBitset
{
	private:
	
		static constexpr auto				ARRAY_SIZE = (Number - 1llu)/64llu + 1llu;
		std::array<quint64, ARRAY_SIZE>			bytes;
	
	public:
	
		inline						HexBitset(void);
		inline 						HexBitset(const std::string&);
		
		inline bool					all(const HexBitset<Number>&) const;
		inline bool					any(void) const;
		inline bool					any(const HexBitset<Number>&) const;
		inline bool					none(const HexBitset<Number>&) const;
		template <typename Type> inline void		set(Type);
		inline void					set(const HexBitset<Number>&);
		template <typename Type> inline bool		test(Type) const;
};

template <quint64 Number>
HexBitset<Number>::HexBitset(void)
{
	HexBitset::bytes.fill(0llu);
}

template <quint64 Number>
HexBitset<Number>::HexBitset(const std::string& str) : bytes({ 0llu })
{
	const auto strend = (str.size() <= Number ? str.crend() : str.crbegin() + Number);
	auto arrit = HexBitset::bytes.begin();
	auto byte = 1llu;
	
	for (auto strit = str.crbegin(); strit != strend; ++strit)
	{
		if (*strit != '0')
			*arrit |= byte;
		
		byte <<= 1llu;
		
		if (byte == 0llu)
		{
			byte = 1llu;
			++arrit;
		}
	}
}
template <quint64 Number>
bool HexBitset<Number>::all(const HexBitset<Number>& b) const
{
	auto it = HexBitset::bytes.cbegin();
	
	for (const auto& u : b.bytes)
	{
		if ((*it & u) != u)
			return false;
		
		++it;
	}
	
	return true;
}

template <quint64 Number>
bool HexBitset<Number>::any(void) const
{
	for (const auto& u : HexBitset::bytes)
	{
		if (u != 0llu)
			return true;
	}
	
	return false;
}

template <quint64 Number>
bool HexBitset<Number>::any(const HexBitset<Number>& b) const
{
	auto it = HexBitset::bytes.cbegin();
	
	for (const auto& u : b.bytes)
	{
		if ((*it & u) != 0llu)
			return true;
		
		++it;
	}
	
	return false;
}

template <quint64 Number>
bool HexBitset<Number>::none(const HexBitset<Number>& b) const
{
	auto it = HexBitset::bytes.cbegin();
	
	for (const auto& u : b.bytes)
	{
		if ((*it & u) != 0llu)
			return false;
		
		++it;
	}
	
	return true;
}

template <quint64 Number>
template <typename Type>
void HexBitset<Number>::set(Type k)
{
	HexBitset::bytes[static_cast<quint64>(k)/64llu] |= (1llu << (static_cast<quint64>(k) % 64llu));
}

template <quint64 Number>
void HexBitset<Number>::set(const HexBitset<Number>& b)
{
	auto it = b.bytes.cbegin();
	
	for (auto& u : HexBitset::bytes)
	{
		u |= *it;
		++it;
	}
}

template <quint64 Number>
template <typename Type>
bool HexBitset<Number>::test(Type k) const
{
	return static_cast<bool>((HexBitset::bytes[static_cast<quint64>(k)/64llu] >> (static_cast<quint64>(k) % 64llu)) & 1llu);
}

#endif
