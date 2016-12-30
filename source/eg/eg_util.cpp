#include "../../include/eg/eg_util.h"

eg::Param<eg::util::Remove_p0_from_p1_Param_e> const eg::util::Remove_p0_from_p1_Param_d(1, true,
	Remove_p0_from_p1_Param_e::Condition_All, false);

eg::Param<eg::util::Add_p0_to_p1_Param_e> const eg::util::Add_p0_to_p1_Param_d(1, true,
	Add_p0_to_p1_Param_e::Condition_New, true);

void eg::util::edianSwap(void *buffer, size_t buffer_len, size_t type_len) {
	if (!type_len) type_len = buffer_len;
	buffer_len /= type_len;
	uint8_t *pres_buffer = new uint8_t[type_len];
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

std::string eg::util::truncateFilename(std::string filename, size_t const level) {
	size_t position = std::string::npos;
	for (size_t i = 0; i < level; i++) {
		position = filename.find_last_of("/\\", position);
		if (position == std::string::npos) break;
		position--;
	}
	return(filename.substr(position));
}