#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_glbRtrn.h"
#include "eg_type.h"

namespace eg {

	class DataReference {
	public:
		static DataReference const PRESET_DEFAULT;
		static size_t const DATATYPE_UNDEFINED;   //An undefined data type
		static size_t const DATASIZE_UNDEFINED;	//An undefined data size

		size_t dataType;  //Type of data pointed to
		size_t dataSize;  //Size of the data pointed to
		void* dataPointer;  //Pointer to data
		bool arrayType; //If allocated by new[] should be true (just in case type isn't known... Doesn't make much difference though)
		size_t alteration; //Alteration of dataType; Allows for "sub types" in types, eg, to differentiate between different string names

		DataReference();
		DataReference(size_t const ndataType, size_t const ndataSize = DATASIZE_UNDEFINED, void* const ndataPointer = nullptr, bool const narrayType = 0);
		//Would like to make this protected if possible
		eg::DataManipulator* load_dataManipulator;
	};

	//I have NO IDEA why you would use this one... But you never know.
	class DataReferenceSet {
	public:
		//Work out something like this: typedef std::remove_pointer<decltype(this)> this_t;

		//TODO (for v2): Use typed enums here to possible reference the ones in eg::util. Writing the same thing twice (param gets passed straight to util...)
		size_t const size() const;

		void add_DataReference(eg::DataReference const& ndataRefernce);						//Add dataReference to set
		void add_DataReference(std::vector<eg::DataReference> const& ndataReference);		//Add dataReference to set

		void remove_DataReference(eg::DataReference const& ndataReference, eg::Param<eg::util::Remove_p0_from_p1_Param_e> const param = eg::util::Remove_p0_from_p1_Param_d);				//Remove dataReference from set
		void remove_DataReference(std::vector<eg::DataReference> const& ndataReference, eg::Param<eg::util::Remove_p0_from_p1_Param_e> const param = eg::util::Remove_p0_from_p1_Param_d);	//Remove dataReference from set

		//eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> begin(); //Old style
		auto begin()							->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>;
		auto begin() const						->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> const;
		auto end()								->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>;
		auto end() const						->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> const;
		auto operator[](size_t const p0)		->eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference>;
		auto operator[](size_t const p0) const	->eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference> const;
	protected:
		void Container_set(size_t const iteration, eg::DataReference const& element);
		eg::DataReference& Container_get(size_t const iteration);
		eg::DataReference const& Container_get(size_t const iteration) const;

		std::vector<eg::DataReference> dataReferenceVector;

		friend eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference>;		//TODO: See if there is a way around using <DataReferenceSet>, like above.
		friend eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>;
	};

} //end namespace eg

bool operator== (eg::DataReference const& lhs,eg::DataReference const& rhs);	//dataType