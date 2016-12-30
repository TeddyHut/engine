#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_glbRtrn.h"
#include "eg_descriptor.h"

namespace eg {

	class DataReference {
	public:
		static DataReference const PRESET_DEFAULT;
		static constexpr size_t DATASIZE_UNDEFINED = 0;		//An undefined data size

		Descriptor<> description;
		size_t dataSize;	//Size of the data pointed to
		void *dataPointer;	//Pointer to data
		bool arrayType;		//If allocated by new[] should be true (just in case type isn't known... Doesn't make much difference though)
		size_t alteration;	//Alteration of dataType; Allows for "sub types" in types, eg, to differentiate between different string names

		DataReference();
		DataReference(Descriptor<> const description, size_t const ndataSize = DATASIZE_UNDEFINED, void *const ndataPointer = nullptr, bool const narrayType = 0);
		//Would like to make this protected if possible
		DataManipulator *load_dataManipulator;
	};
	//It will lov
	//I have NO IDEA why you would use this one... But you never know.
	class DataReferenceSet {
	public:
		//Work out something like this: typedef std::remove_pointer<decltype(this)> this_t;

		//TODO (for v2): Use typed enums here to possible reference the ones in eg::util. Writing the same thing twice (param gets passed straight to util...)
		size_t const size() const;

		void add_DataReference(DataReference const &ndataRefernce);						//Add dataReference to set
		void add_DataReference(std::vector<DataReference> const &ndataReference);		//Add dataReference to set

		void remove_DataReference(DataReference const &ndataReference, Param<util::Remove_p0_from_p1_Param_e> const param = util::Remove_p0_from_p1_Param_d);				//Remove dataReference from set
		void remove_DataReference(std::vector<DataReference> const &ndataReference, Param<util::Remove_p0_from_p1_Param_e> const param = util::Remove_p0_from_p1_Param_d);	//Remove dataReference from set

		auto begin()							->util::Container::Iterator<DataReferenceSet, DataReference>;
		auto begin() const						->util::Container::Iterator<DataReferenceSet, DataReference> const;
		auto end()								->util::Container::Iterator<DataReferenceSet, DataReference>;
		auto end() const						->util::Container::Iterator<DataReferenceSet, DataReference> const;
		auto operator[](size_t const p0)		->util::Container::Element<DataReferenceSet, DataReference>;
		auto operator[](size_t const p0) const	->util::Container::Element<DataReferenceSet, DataReference> const;
	protected:
		void Container_set(size_t const iteration, DataReference const &element);
		DataReference &Container_get(size_t const iteration);
		DataReference const &Container_get(size_t const iteration) const;

		std::vector<DataReference> dataReferenceVector;

		friend util::Container::Element<DataReferenceSet, DataReference>;		//TODO: See if there is a way around using <DataReferenceSet>, like above.
		friend util::Container::Iterator<DataReferenceSet, DataReference>;
	};

} //end namespace eg

bool operator== (eg::DataReference const &lhs, eg::DataReference const &rhs);	//dataType