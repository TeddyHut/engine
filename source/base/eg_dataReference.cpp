#include "../../include/base/eg_dataReference.h"

eg::DataReference const eg::DataReference::PRESET_DEFAULT;
size_t const eg::DataReference::DATATYPE_UNDEFINED = 0xFFFFFFFF;
size_t const eg::DataReference::DATASIZE_UNDEFINED = 0xFFFFFFFF;

eg::DataReference::DataReference() : dataType(eg::DataReference::DATATYPE_UNDEFINED), dataSize(eg::DataReference::DATASIZE_UNDEFINED), dataPointer(nullptr), arrayType(false), alteration(0) {
}

eg::DataReference::DataReference(size_t const ndataType,size_t const ndataSize, void* const ndataPointer, bool const narrayType) : dataType(ndataType), dataSize(ndataSize), dataPointer(ndataPointer), arrayType(narrayType), alteration(0) {
}

size_t const eg::DataReferenceSet::size() const {
	return(dataReferenceVector.size());
}

void eg::DataReferenceSet::add_DataReference(eg::DataReference const& ndataReference) {
	dataReferenceVector.push_back(ndataReference);	//Add a data referece to vector
}

void eg::DataReferenceSet::add_DataReference(std::vector<eg::DataReference> const& ndataReference) {
	dataReferenceVector.insert(dataReferenceVector.end(),ndataReference.begin(),ndataReference.end());	//Add vector of dataReferences to vector (at end)
}

void eg::DataReferenceSet::remove_DataReference(eg::DataReference const& ndataReference, eg::Param<eg::util::Remove_p0_from_p1_Param_e> const param) {
	std::vector<eg::DataReference> nvdataReference;
	nvdataReference.push_back(ndataReference);
	eg::util::remove_p0_from_p1(nvdataReference, dataReferenceVector, param);
}

void eg::DataReferenceSet::remove_DataReference(std::vector<eg::DataReference> const& ndataReference, eg::Param<eg::util::Remove_p0_from_p1_Param_e> const param) {
	eg::util::remove_p0_from_p1(ndataReference, dataReferenceVector, param);
}

auto eg::DataReferenceSet::begin()->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> {
	return(eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>(this, 0));
}

auto eg::DataReferenceSet::begin() const->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> const {
	return(eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>(this, 0));
}

auto eg::DataReferenceSet::end()->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> {
	return(eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>(this, dataReferenceVector.size()));
}

auto eg::DataReferenceSet::end() const->eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference> const {
	return(eg::util::Container::Iterator<eg::DataReferenceSet, eg::DataReference>(this, dataReferenceVector.size()));
}

auto eg::DataReferenceSet::operator[](size_t const iteration)->eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference> {
	return(eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference>(this, iteration));
}

auto eg::DataReferenceSet::operator[](size_t const iteration) const->eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference> const {
	return(eg::util::Container::Element<eg::DataReferenceSet, eg::DataReference>(this, iteration));
}

void eg::DataReferenceSet::Container_set(size_t const iteration, eg::DataReference const& element) {
	dataReferenceVector[iteration] = element;
}

eg::DataReference& eg::DataReferenceSet::Container_get(size_t const iteration) {
	return(dataReferenceVector[iteration]);
}

eg::DataReference const& eg::DataReferenceSet::Container_get(size_t const iteration) const {
	return(dataReferenceVector[iteration]);
}

bool operator== (eg::DataReference const& lhs,eg::DataReference const& rhs) {
	return(lhs.dataType == rhs.dataType);
}