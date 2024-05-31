#include <string>
#include <iostream>
#include <vector>
//IP address form: XXX.XXX.XXX.XXX 
//where the first segment is a number between 1 and 126
//and the remaining segments 
//are represented by number sbetween 0 and 255     
//eg. the IP range is
// 1.0.0.0
// 126.255.255.255

//write a program that takes a string as an input and prints whether the string is a vaild IP address

//OPTIONAL 1: Modify the program so that is takes an input from the command line
//OPTIONAL 2: Create a IP address class that takes a string and its constructor and produces a valid IP address object
//OPTIONAL 3: Using enums, modify the program to print a error message that corresponds to what is invalid about the address (e.g. insufficient periods, insufficient fiellds, wrong field format etc.)

/// <summary>
/// This function returns true if an address contains exactly 3 periods
/// </summary>
/// <param name="address">IP address as a string</param>
/// <returns></returns>
bool containsThreePeriods(const std::string& address)
{
	int32_t count{ 0 };
	static constexpr int32_t periodCount{ 3 };
	for (const auto& element : address)
	{
		if (element == '.')
		{
			++count;
		}
		if (count > periodCount)
		{
			return false;
		}
	}
	return (count == periodCount);
}

void testTP(const std::string& addr)
{
	bool res = containsThreePeriods(addr);
	std::cout << "Address " << addr << " is" << (res ? "" : " not") << " valid\n";
}


/// <summary>
/// This function splits an IP address into substrings that are delimited by periods
/// </summary>
/// <param name="address"></param>
/// <returns>A vector of strings</returns>
std::vector<std::string> splitAddress(const std::string& address)
{
	std::vector<std::string> result{};
	std::string tempString{};
	for (const auto& element : address)
	{
		if (element != '.')
		{
			tempString += element;
		}
		else
		{
			if (!tempString.empty())
			{
				result.push_back(tempString);
			}
			tempString.clear();
		}
	}
	if (!tempString.empty())
	{
		result.push_back(tempString);
	}
	return result;
}

void testSplit(const std::string& address)
{
	std::vector<std::string> result = splitAddress(address);
	std::cout << "The substring of address " << address << " are ";
	for (const auto& element : result)
	{
		std::cout <<"\"" << element << "\" ";
	}
	std::cout << '\n';
}

/// <summary>
/// Converts a vector of strings into a vector of integers (when possible)
/// </summary>
/// <param name="fields"></param>
/// <returns></returns>
std::vector<int32_t> convertToInt(const std::vector<std::string>& fields)
{
	std::vector<int32_t> result{};
	for (const auto& field : fields)
	{
		try
		{
			int32_t number{ std::stoi(field) };
			result.push_back(number);
			
		}
		catch (...)
		{

		}
	}
	return result;
}


void testConvert(const std::string& addr) 
{
	std::cout << "The integer fields of address " << addr << " are ";
	for (const auto& num : convertToInt(splitAddress(addr)))
	{
		std::cout << num << " ";
	}
	std::cout << "\n";
}

/// <summary>
/// Checks if an IP address is valid
/// </summary>
/// <param name="address"></param>
/// <returns></returns>
bool validateAddress(const std::string& address)
{
	if (!containsThreePeriods(address))
	{
		return false;
	}
	auto stringFields{ splitAddress(address) };
	if (stringFields.size() != 4)
	{
		return false;
	}
	auto intFields{ convertToInt(stringFields) };
	if (intFields.size() != 4)
	{
		return false;
	}

	if (intFields[0] < 1 || intFields[0] > 126)
	{
		return false;
	}

	for (const auto& field : intFields)
	{
		if (field < 0 || field > 255)
		{
			return false;
		}

	}

	return true;

}

void testValidate(const std::string& addr)
{
	bool res = validateAddress(addr);
	std::cout << "IP address " << addr << " is"<< (res ? "" : " not") << " a valid IP address\n";
}

int main()
{
	std::vector<std::string> addrs = { 
	"1.0.3.4",
	"1.0.5.6.7",
	 "1.0.3",
	 "...",
	 "123.",
	 ".123",
	 "123.abc.123",
	 "0.0.0.0"
	};
	for (const auto& addr : addrs) {
		testTP(addr);
		testSplit(addr);
		testConvert(addr);
		testValidate(addr);
	}

	return 0;
}