#include "catch.hpp"

#include "hash_dictionary.hpp"

#include <iostream> // for debugging
#include <sstream>  // for std::ostringstream
#include <string>   // for std::string

typedef unsigned int KeyType;
typedef std::string ValueType;
typedef std::size_t (*FunctionType)(const KeyType &key);
typedef HashDictionary<KeyType, ValueType, FunctionType> DictionaryType;

std::size_t testHash(const KeyType& key)
{
	return key % 10;
}

std::size_t testLargeHash(const KeyType& key)
{
	return key % 100;
}

TEST_CASE("Basic Tests", "[Dictionary]") {
	//To DO
	DictionaryType test_dictionary(testHash);

	// require dictionary initially empty and has no size
	REQUIRE(test_dictionary.isEmpty());
	REQUIRE(test_dictionary.size() == 0);

	// test adding some key-value pairs
	test_dictionary.add(1, "Hello");
	test_dictionary.add(2, "Beautiful");
	test_dictionary.add(3, "World");

	REQUIRE(test_dictionary.size() == 3);
	REQUIRE(test_dictionary.get(1) == "Hello");
	REQUIRE(test_dictionary.get(2) == "Beautiful");
	REQUIRE(test_dictionary.get(3) == "World");

	// test overwriting a key should update value, not create new element
	test_dictionary.add(2, "Wonderful");
	REQUIRE(test_dictionary.size() == 3);
	REQUIRE(test_dictionary.get(2) == "Wonderful");

	// test removing a value
	test_dictionary.remove(2);
	REQUIRE(test_dictionary.size() == 2);
	REQUIRE_FALSE(test_dictionary.contains(2));

	// ensures throw error occurs when remove index is out of bounds
	REQUIRE_THROWS(test_dictionary.remove(10));
	REQUIRE_THROWS(test_dictionary.remove(100));

	// test clearing capabilities 
	test_dictionary.clear();
	REQUIRE(test_dictionary.isEmpty());
	REQUIRE(test_dictionary.size() == 0);
}

TEST_CASE("Test large Dictionary", "[Dictionary]") {
	//To Do
	DictionaryType test_dictionary(testLargeHash);

	// ensure dictionary is empty
	REQUIRE(test_dictionary.size() == 0);
	REQUIRE(test_dictionary.isEmpty());

	for (int i = 0; i < 1000; i++)
	{
		std::string entry = std::to_string(i);
		test_dictionary.add(i, entry);
	}

	REQUIRE(test_dictionary.size() == 1000);

	// ensure each value was added appropriately
	for (int i = 0; i < 1000; i++)
	{
		std::string expected = std::to_string(i);
		REQUIRE(test_dictionary.get(i) == expected);
	}

	// ensures throw error occurs when remove index is out of bounds
	REQUIRE_THROWS(test_dictionary.remove(3000));

	// tests clear 
	test_dictionary.clear();
	REQUIRE(test_dictionary.size() == 0);
}

