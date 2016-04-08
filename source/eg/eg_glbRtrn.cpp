#include "../../include/base/eg_glbRtrn.h"

eg::GlbRtrn::Result::Result() : result_hash(0), result_fail(true), string_o("") {
}

eg::GlbRtrn::Result::Result(size_t nresult_hash, bool const nresult_fail, std::string const& nstring_o) : result_hash(nresult_hash), result_fail(nresult_fail), string_o(nstring_o) {
}

eg::GlbRtrn::Step::Step() : step_result(nullptr), step_filename(nullptr), delete_filename(true), step_functionname(nullptr), is_functionname(false), step_linenumber(0) {
}

eg::GlbRtrn::Step::Step(eg::GlbRtrn::Result const*const nstep_result,
	std::string const*const nstep_filename, bool const ndelete_filename,
	std::string const*const nstep_functionname, bool const nis_functionname,
	size_t nstep_linenumber) :
	step_result(nstep_result),
	step_filename(nstep_filename), delete_filename(ndelete_filename),
	step_functionname(nstep_functionname), is_functionname(nis_functionname),
	step_linenumber(nstep_linenumber) {
}

eg::GlbRtrn::Step::~Step() {
	if (delete_filename) {
		delete step_filename;
	}
}

eg::GlbRtrn::operator bool() {
	return(fail);
}

eg::GlbRtrn::operator size_t() {
	return(step_v.back().step_result->result_hash);
}

void eg::GlbRtrn::set_default_ostream(std::ostream* const nostream) {
	default_ostream = nostream;
}

void eg::GlbRtrn::check(bool const verbose_output) const {
	if (fail) print_output(verbose_output);
}

void eg::GlbRtrn::validate() {
	fail = false;
}

void eg::GlbRtrn::addResult(eg::GlbRtrn::Result const& result,
	std::string const& fileName, bool const copy_fileName,
	size_t const lineNumber,
	std::string const& functionName, bool const is_functionname) {
	step_v.push_back(Step(&result,
		(copy_fileName ? new std::string(fileName) : &fileName), copy_fileName,
		(is_functionname ? &functionName : nullptr), is_functionname,
		lineNumber));
	if (result.result_fail)
		fail = true;
}

void eg::GlbRtrn::print_output(bool const verbose_output) const {
	//	Should produce an ouput like this
	//	eg::GlbRtrn-0xFFFFFFFFFFFFFFFF -> print_output:
	//	0x0		result_hash:	0x0
	//			result_string:	"a result"
	//			filename:		"error file"
	//			functionname:	"error function"
	//			linenumber:		123
	//	0x1...

	//Use some of that regex stuff or whatever here?
	std::stringstream max_length_ss;
	max_length_ss << std::hex << step_v.size() - 1;
	size_t max_length = max_length_ss.str().size();
	size_t max_length_add = max_length + 3;	//+3 for 0x...-

	std::ostream& output_stm = *output_stream;
	std::ios::fmtflags original_flags = output_stm.flags();

	auto pad_output = [&]()->void { for (size_t j = 0; j < max_length_add; j++) output_stm << " "; };

	output_stm << std::hex << std::setfill('0') << "eg::GlbRtrn-0x" << std::setw(sizeof(void*)*8) << this << " -> print_output:" << std::endl;
	for (size_t i = 0; i < step_v.size(); i++) {
		output_stm << std::hex << std::setfill(' ') << (step_v[i].step_result->result_fail ? "!0x" : " 0x") << std::setw(max_length) << i << " result_hash:\t0x" << std::setw(max_length) << step_v[i].step_result->result_hash << std::endl;
		if (step_v[i].step_result->result_fail || verbose_output) {
			pad_output(); output_stm << "result_string:\t\"" << step_v[i].step_result->string_o << "\"" << std::endl;
			pad_output(); output_stm << "filename:\t\t\"" << *step_v[i].step_filename << "\"" << std::endl;
			pad_output(); output_stm << "functionname:\t\"" << (step_v[i].is_functionname ? *step_v[i].step_functionname : "?") << "\"" << std::endl;
			pad_output(); output_stm << std::dec << "linenumber:\t\t" << step_v[i].step_linenumber << std::endl;
		}
	}
	output_stm.flags(original_flags);
}

eg::GlbRtrn::GlbRtrn() : default_parameter(false), output_stream(default_ostream), fail(false) {
}

eg::GlbRtrn::GlbRtrn(bool const ndefault_parameter, std::ostream* const noutput_stream, bool const nfail) : default_parameter(ndefault_parameter), output_stream(noutput_stream), fail(nfail) {
}

std::ostream* eg::GlbRtrn::default_ostream = &std::cout;

eg::GlbRtrn::Result const eg::Main_Result_Success_r(static_cast<size_t>(eg::Main_Result_e::Success), false, "Main_Success");
eg::GlbRtrn::Result const eg::Main_Result_Failure_r(static_cast<size_t>(eg::Main_Result_e::Failure), true, "Main_Failure");