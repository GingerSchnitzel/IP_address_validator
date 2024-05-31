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
	std::cout << "address " << addr << " is" << (res ? "" : " not") << " valid\n";
}



int main()
{
	std::vector<std::string> addrs = {
	"1.0.3.4",
	"1.0.5.6.7",
	 "1.0.3"
	};
	for (const auto& addr : addrs) {
		testTP(addr);
	}
	return 0;
}