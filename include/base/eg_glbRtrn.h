#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

//Note: Standard function/file names are as follows:
//Filename: _egNAME_FILE_seg_
//Functionname: _egNAME_FUNCTION_seg_
#define eg_GlbRtrn_Result(glbrtrn, result) glbrtrn.addResult(result, __FILE__, true, __LINE__);
#define eg_GlbRtrn_egResult(glbrtrn, result) glbrtrn.addResult(result, _egNAME_FILE_seg_, false, __LINE__, _egNAME_FUNCTION_seg_, true);
//Use some macro overloading magic here (breaks da brian)

namespace eg {

	class GlbRtrn {
	public:
		struct Result {
			size_t result_hash;
			bool result_fail;
			std::string string_o;
			Result();
			Result(size_t nresult_hash, bool const nresult_fail = true, std::string const& nstring_o = "");
		};
		struct Step {
			Result const* step_result;
			std::string const* step_filename;
			bool delete_filename;
			std::string const* step_functionname;
			bool is_functionname;
			size_t step_linenumber;
			Step();
			Step(Result const*const nstep_result,
				std::string const*const nstep_filename = nullptr, bool const ndelete_filename = true,
				std::string const*const nstep_functionname = nullptr, bool const nis_functionname = false,
				size_t const nstep_linenumber = 0);
			virtual ~Step();
		};
		operator bool();
		operator size_t();

		static void set_default_ostream(std::ostream* const nostream);

		//Checks fail, and if true, prints the output to -output_steam-
		virtual void check(bool const verbose_output = false) const;
		//Resets fail to 0, validating operator bool()
		virtual void validate();
		//Adds a result/step to the glbrtrn. Preferably use macro.
		virtual void addResult(Result const& result,
			std::string const& fileName, bool const copy_fileName,
			size_t const lineNumber,
			std::string const& functionName = "", bool const is_functionname = false);
		virtual void print_output(bool const verbose_output = false) const;

		bool const default_parameter;
		std::ostream* output_stream;
		bool fail;
		std::vector<Step> step_v;

		GlbRtrn();
		GlbRtrn(bool const ndefault_parameter, std::ostream* const noutput_stream = eg::GlbRtrn::default_ostream, bool const nfail = false);
	protected:
		static std::ostream* default_ostream;
	};
	enum class Main_Result_e : size_t {
		Success = 0,
		Failure = 1
	};
	extern eg::GlbRtrn::Result const Main_Result_Success_r;
	extern eg::GlbRtrn::Result const Main_Result_Failure_r;
}