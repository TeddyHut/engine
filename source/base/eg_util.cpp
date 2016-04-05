#include "../../include/base/eg_util.h"

bool eg::Param::get_param(size_t const param) const {
	refreshExtern();
	return(get_param_p(param));
}

void eg::Param::set_param(size_t const param, bool nbit) {
	set_param_p(param, nbit);
	refreshExtern();
}

void eg::Param::add_param(size_t const amount) {
	size_t amountc = amount;
	while (true) {
		if (static_cast<size_t>(param_free) < amountc) {
			amountc -= static_cast<size_t>(param_free);
			param_amount += static_cast<size_t>(param_free);

			param_data.push_back(0);
			param_free = 8;
		}
		else {
			param_free -= static_cast<uint8_t>(amountc);
			param_amount += amountc;
			break;
		}
	}
}

void eg::Param::remove_param(size_t const amount) {
	size_t amountc = amount;
	while (true) {
		size_t f = static_cast<size_t>(8 - param_free);
		if (f < amountc) {
			amountc -= f;
			param_amount -= f;

			param_data.erase(param_data.end() - 1);
			param_free = 0;
		}
		else {
			param_free += static_cast<uint8_t>(amountc);
			param_amount -= amountc;
			break;
		}
	}
}

auto eg::Param::begin()->eg::util::Container::Iterator<eg::Param, bool> {
	return(eg::util::Container::Iterator<eg::Param, bool>::Iterator(this, 0));
}

auto eg::Param::begin() const->eg::util::Container::Iterator<eg::Param, bool> const {
	return(eg::util::Container::Iterator<eg::Param, bool>::Iterator(this, 0));
}

auto eg::Param::end()->eg::util::Container::Iterator<eg::Param, bool> {
	return(eg::util::Container::Iterator<eg::Param, bool>::Iterator(this, param_amount));
}

auto eg::Param::end() const->eg::util::Container::Iterator<eg::Param, bool> const {
	return(eg::util::Container::Iterator<eg::Param, bool>::Iterator(this, param_amount));
}

auto eg::Param::operator[](size_t const p0)->eg::util::Container::Element<eg::Param, bool> {
	return(eg::util::Container::Element<eg::Param, bool>::Element(this, p0));
}

auto eg::Param::operator[](size_t const p0) const->eg::util::Container::Element<eg::Param, bool> const {
	return(eg::util::Container::Element<eg::Param, bool>::Element(this, p0));
}

eg::Param::Param(size_t amount) : param_amount(0), param_free(0) {
	add_param(amount);
}

eg::Param::Param(size_t amount, size_t param, bool nbit, ...) : param_amount(0), param_free(0) {
	add_param(amount);
	set_param(param, nbit);
	amount -= 1;

	va_list ellipse;
	va_start(ellipse, nbit);

	for (size_t i = 0; i < amount; i++) {
		uint32_t const tparam = va_arg(ellipse, uint32_t);
		bool const tbit = va_arg(ellipse, bool);
		set_param(tparam, tbit);
	}
	va_end(ellipse);
}

eg::Param::Param() : param_amount(0), param_free(0) {
}

eg::Param::~Param() {
}

bool eg::Param::get_param_p(size_t const param) const {
	return(((param_data[param / 8]) >> param % 8) & 0x01);
}

void eg::Param::set_param_p(size_t const param, bool const nbit) {
	param_data[param / 8] &= ~(1 << (param % 8));
	param_data[param / 8] |= (nbit << (param % 8));
}

void eg::Param::refreshExtern() {
	for (auto&& element : externReference) {						//Iterate through externReferences
		bool intern = get_param_p(element.iteration);
		if (intern != element.element) {							//If the extern and the intern are no longer in sync
			if (element.element != element.element_prev) {			//If it was the extern that changed
				set_param_p(element.iteration, element.element);	//Update the internal param with that information
			}
			else {													//If it was the intern that changed
				element.element = intern;							//Update the extern with that information
			}
		}
		element.element_prev = element.element;						//Has been checked
	}
}

void eg::Param::refreshExtern() const {
	//const_cast<std::remove_const<decltype(this)>::type>(this)->refreshExtern();
	const_cast<eg::Param*>(this)->refreshExtern();	//<- THAT IS THE PIVOT OF C++ DISRESPECT RIGHT THERE
}

void eg::Param::Container_set(size_t const iteration, bool const element) {
	set_param(iteration, element);
}

bool& eg::Param::Container_get(size_t const iteration) {
	refreshExtern();
	for (auto&& element : externReference) {
		if (element.iteration == iteration) {
			return(element.element);
		}
	}
	ExternReference exref;
	exref.iteration = iteration;
	exref.element = get_param_p(exref.iteration);
	exref.element_prev = exref.element;
	externReference.push_back(exref);
	return(externReference[externReference.size()-1].element);
}

bool const& eg::Param::Containter_get(size_t const iteration) const {
	return(const_cast<eg::Param*>(this)->Container_get(iteration));		//AND I DID IT AGAIN! *clap clap clap*
}

size_t const eg::util::remove_p0_from_p1::PARAM_ALL = 0;
eg::Param const Param_DEFAULT(1,
	eg::util::remove_p0_from_p1::PARAM_ALL, false);

void eg::util::edianSwap(void* buffer, size_t buffer_len, size_t type_len) {
	if (!type_len) type_len = buffer_len;
	buffer_len /= type_len;
	uint8_t* pres_buffer = new uint8_t[type_len];
	for (size_t i = 0; i < buffer_len; i++) {
		uint8_t* offset = reinterpret_cast<uint8_t*>(buffer) + (i*type_len);
		memcpy(pres_buffer, offset, type_len);
		for (size_t a = type_len; a > 0; a--) {
			*offset = pres_buffer[a - 1];
			offset++;
		}
	}
	delete[] pres_buffer;
}