#include "../include/eg/eg_engine.h"
#include "../include/eg/macro/rm_w4307_0.h"

#include <map>
#include <string>

namespace Key {
	enum e {
		Fruit = murmur3_32_value("Fruit", 5, 0),
		Vegetable = murmur3_32_value("Vegetable", 9, 0),
		Meat = murmur3_32_value("Meat", 4, 0),
	};
	std::map<int, std::string> str_map{
		{Fruit, "Fruit"},
		{Vegetable, "Vegetable"},
		{Meat, "Meat"}
	};
}

namespace Value {
	namespace Fruit {
		enum e {
			Apple = murmur3_32_value("Apple", 5, 0),
			Pear = murmur3_32_value("Pear", 4, 0),
			Orange = murmur3_32_value("Orange", 6, 0)
		};
	}
	namespace Vegetable {
		enum e {
			Pea = murmur3_32_value("Pea", 3, 0),
			Carrot = murmur3_32_value("Carrot", 6, 0),
			Corn = murmur3_32_value("Corn", 4, 0)
		};
	}
	namespace Meat {
		enum e {
			Beef = murmur3_32_value("Beef", 4, 0),
			Chicken = murmur3_32_value("Chicken", 7, 0),
			Pork = murmur3_32_value("Pork", 4, 0)
		};
	}
	std::map<int, std::string> str_map{
		{ Fruit::Apple, "Apple" },
		{ Fruit::Pear, "Pear" },
		{ Fruit::Orange, "Orange" },
		{ Vegetable::Pea, "Pea"},
		{ Vegetable::Carrot, "Carrot" },
		{ Vegetable::Corn, "Corn" },
		{ Meat::Beef, "Beef" },
		{ Meat::Chicken, "Chicket" },
		{ Meat::Pork, "Pork" }
	};
}

void print_contents(eg::Descriptor<> &p0) {
	std::cout << "Contains:" << std::endl;
	for (auto &&element : p0.description) {
		std::cout << Key::str_map[element.first] << ": ";
		for (auto &&value : element.second) {
			std::cout << Value::str_map[value] << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(int argc, char** argv) {
	eg::Descriptor<> david;
	//Create key fruit
	david[Key::Fruit];
	print_contents(david);
	//Add value apple to key fruit
	david[Key::Fruit][Value::Fruit::Apple];
	print_contents(david);
	//Add value pear to key fruit
	david[Key::Fruit] = david[Key::Fruit] + Value::Fruit::Pear;
	print_contents(david);
	//Add value orange to key fruit
	david[Key::Fruit] += Value::Fruit::Orange;
	print_contents(david);
	//Remove value orange from key fruit
	david[Key::Fruit] -= Value::Fruit::Orange;
	print_contents(david);
	//Remove value pear from key fruit
	david[Key::Fruit] = david[Key::Fruit] - Value::Fruit::Pear;
	print_contents(david);
	//Add value orange and value pear back to key fruit
	david[Key::Fruit] += std::vector<int>::vector({ Value::Fruit::Orange, Value::Fruit::Pear });
	print_contents(david);
	//Remove apple and pear from key fruit
	david[Key::Fruit] -= std::vector<int>::vector({ Value::Fruit::Apple, Value::Fruit::Pear });
	print_contents(david);
	//Make a michael.
	eg::Descriptor<> michael;
	michael[Key::Fruit] += Value::Fruit::Pear;
	michael[Key::Fruit] += Value::Fruit::Apple;
	//Add michaels values to david
	david[Key::Fruit] += michael[Key::Fruit];
	print_contents(david);
	//Make michael only contain pear
	michael[Key::Fruit] = Value::Fruit::Pear;
	//Print comparison
	print_contents(david[Key::Fruit] & michael[Key::Fruit]);
	//Check more comparison
	if ((david & michael) == michael) {
		std::cout << "Yes!" << std::endl;
	}
	else
		std::cout << "No!" << std::endl;
	//Remove pear from david
	david[Key::Fruit] -= Value::Fruit::Pear;
	if ((david & michael) == michael) {
		std::cout << "Yes!" << std::endl;
	}
	else
		std::cout << "No!" << std::endl;
	
	system("pause");
}

#include "../include/eg/macro/rm_w4307_1.h"
