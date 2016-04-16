#pragma once

#include <cstdint>
#include <cstddef>

namespace eg {
	namespace util {
		namespace Container {
			//Will be returned by Iterator, and is used as the 'element' of what the iterater is pointing to
			//-Master_t- = The type of the object that created/stored this element
			//-Element_t- = The type of the object that this element 'points to'
			//-Index_t- = The type of entity used to address the index of the master object. Used in -Master_t-.Container_get(-Index_t-)
			template<typename Master_t, typename Element_t = Master_t, typename Index_t = size_t> class Element {
			public:
				//Returns -iteration-
				Index_t const get_iteration();

				//Sets master element at position -iteration-
				void operator=(Element_t const &p0);
				void operator=(Element<Master_t, Element_t, Index_t> const &p0);
				//Returns -master-.Container_get(iteration)
				operator Element_t &();
				operator Element_t const &() const;	//TODO: Check whether we need const and non-const versions when brain starts working

				//TODO: Switch to _iteration over iteration
				//TODO: Maybe overload this contructor with a Master_t *const version? If things don't work out...
				Element(Master_t const *const nmaster, Index_t const niteration);
			private:
				Master_t *master;
				Index_t iteration;
			};

			//Will be returned by -Master_t-.begin(), end(), etc. Used as an iterator, and will create an element upon the dereference '*' operator
			//-Master_t- = The type of the object that created/stored this iterator
			//-Element_t- = The type of the object that this iterator 'points to'
			//-Index_t- = The type of entity used to address the index of the master object. Used in -Master_t-.Container_get(-Index_t-)
			template<typename Master_t, typename Element_t = Master_t, typename Index_t = size_t> class Iterator {
			public:
				//Returns -iteration-
				Index_t const get_iteration();

				//Sets master element at position -iteration-
				void operator=(Element_t const &p0);
				void operator=(Iterator<Master_t, Element_t, Index_t> const &p0);
				//Increments iteration by 1
				void operator++();
				//Compares for equality
				bool const operator==(Iterator<Master_t, Element_t, Index_t> const &p0) const;
				//Compares for difference
				bool const operator!=(Iterator<Master_t, Element_t, Index_t> const &p0) const;
				//Returns an Element_t that can be used to obtain the -master- values
				Element<Master_t, Element_t, Index_t> operator *();
				Element<Master_t, Element_t, Index_t> const operator *() const;

				Iterator(Master_t const *const nmaster, Index_t const niteration);
			private:
				Master_t *master;
				Index_t iteration;
			};
		}
	}
}

template<typename Master_t, typename Element_t, typename Index_t> Index_t const eg::util::Container::Element<Master_t, Element_t, Index_t>::get_iteration() {
	return(iteration);
}

template<typename Master_t, typename Element_t, typename Index_t> void eg::util::Container::Element<Master_t, Element_t, Index_t>::operator=(Element_t const &p0) {
	master->Container_set(iteration, p0);
}

template<typename Master_t, typename Element_t, typename Index_t> void eg::util::Container::Element<Master_t, Element_t, Index_t>::operator=(Element<Master_t, Element_t, Index_t> const &p0) {
	master->Container_set(p0.iteration, p0);	//Should automatically convert to needed type becuase of operator T0();
}

template<typename Master_t, typename Element_t, typename Index_t> eg::util::Container::Element<Master_t, Element_t, Index_t>::operator Element_t &() {
	return(master->Container_get(iteration));
}

template<typename Master_t, typename Element_t, typename Index_t> eg::util::Container::Element<Master_t, Element_t, Index_t>::operator Element_t const &() const {
	return(master->Container_get(iteration));
}

//Why const * const and const_cast are needed: Needed because cannot convert 'const this' to 'this' when passing master param from const function
template<typename Master_t, typename Element_t, typename Index_t> eg::util::Container::Element<Master_t, Element_t, Index_t>::Element(Master_t const *const nmaster, Index_t const niteration) : master(const_cast<Master_t *>(nmaster)), iteration(niteration) {
}

template<typename Master_t, typename Element_t, typename Index_t> Index_t const eg::util::Container::Iterator<Master_t, Element_t, Index_t>::get_iteration() {
	return(iteration);
}

template<typename Master_t, typename Element_t, typename Index_t> void eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator=(Element_t const &p0) {
	master->Container_set(iteration, p0);
}

template<typename Master_t, typename Element_t, typename Index_t> void eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator=(Iterator<Master_t, Element_t, Index_t> const &p0) {
	master->Container_set(p0.iteration, p0);
}

template<typename Master_t, typename Element_t, typename Index_t> void eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator++() {
	iteration++;
	//TODO: Some error checking here would be a good idea.
}

template<typename Master_t, typename Element_t, typename Index_t> bool const eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator==(Iterator<Master_t, Element_t, Index_t> const &p0) const {
	return((iteration == p0.iteration) && (master == p0.master));
}

template<typename Master_t, typename Element_t, typename Index_t> bool const eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator!=(Iterator<Master_t, Element_t, Index_t> const &p0) const {
	return((iteration != p0.iteration) || (master != p0.master));
}

template<typename Master_t, typename Element_t, typename Index_t> eg::util::Container::Element<Master_t, Element_t, Index_t> eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator *() {
	return(typename eg::util::Container::Element<Master_t, Element_t, Index_t>::Element(master, iteration));
}

template<typename Master_t, typename Element_t, typename Index_t> eg::util::Container::Element<Master_t, Element_t, Index_t> const eg::util::Container::Iterator<Master_t, Element_t, Index_t>::operator *() const {
	return(const_cast<eg::util::Container::Element<Master_t, Element_t, Index_t> const>(typename eg::util::Container::Element<Master_t, Element_t, Index_t>::Element(master, iteration)));//Maybe get rid of that const_cast... Not really needed
}

//Maybe cast to <T0* const>?
template<typename Master_t, typename Element_t, typename Index_t> eg::util::Container::Iterator<Master_t, Element_t, Index_t>::Iterator(Master_t const *const nmaster, Index_t const niteration) : master(const_cast<Master_t *>(nmaster)), iteration(niteration) {
}