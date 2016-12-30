#include "../include/eg/eg_descriptor.h"
#include "../include/eg/thirdparty/murmur3_32.h"

#include "../include/eg/macro/rm_w4307_0.h"


namespace Key {
	enum e {
		Fruit = murmur3_32_value("Fruit", 5, 0),
		Vegetable = murmur3_32_value("Vegetable", 9, 0),
		Meat = murmur3_32_value("Meat", 4, 0),
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
}

void example() {
	//Create a descriptor called david
	eg::Descriptor<> david;
	//Create a new key called "Fruit" and add the value "Apple" to it
	david[Key::Fruit] = Value::Fruit::Apple;
	//david now has 1 key, which can be accessed using the following syntax
	david[Key::Fruit];
	//david also has 1 value in the fruit key, which can be accessed using the following syntax
	david[Key::Fruit][Value::Fruit::Apple];
	//The apple value can be changed to something else using the following syntax
	david[Key::Fruit][Value::Fruit::Apple] = Value::Fruit::Orange;
	//To add a new value to the key, use the following syntax
	david[Key::Fruit] = Value::Fruit::Pear;
	//david now contains the key fruit with the values Orange and Pear
	//We can check whether david contains the value Pear in the key fruit using the following syntax
	if (david[Key::Fruit] & Value::Fruit::Pear) {
		//David contains the value pear
	}
	eg::Descriptor<> desc({ { Key::Fruit,
								{ Value::Fruit::Orange, Value::Fruit::Pear }
							} });
	//To check whether david contains the value Pear or the Value Orange in the Key Fruit, use the following syntax
	if (david[Key::Fruit] & eg::Descriptor<>::Descriptor({ { Key::Fruit, {Value::Fruit::Orange, Value::Fruit::Pear} } } )[Key::Fruit]) {
		//Sort of confusing looking?
		//The smarter way would probably be to use the if statement || instead of something like that
	}
}

#include "../include/eg/macro/rm_w4307_1.h"
