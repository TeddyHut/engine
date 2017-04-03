#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace eg {
	namespace util {
		//Type tokenenum_t must have members "Quotation", "StrPlaceholder", and "Invalid". TODO: I'm sure that there's some fancy standard library type functions to assert that condition.
		template <typename tokenenum_t, std::map<tokenenum_t, std::string> const &tokenmap>
		class TextParse {
		public:
			static tokenenum_t str_to_token(std::string const &str);
			void generate_tokens(std::string const &text);
			std::vector<tokenenum_t> vec_token;
			std::vector<std::string> vec_str;
		};
		
		template<typename tokenenum_t, std::map<tokenenum_t, std::string> const & tokenmap>
		tokenenum_t TextParse<tokenenum_t, tokenmap>::str_to_token(std::string const & str)
		{
			auto itr = std::find_if(tokenmap.begin(), tokenmap.end(), [&](std::pair<tokenenum_t const, std::string const> const &p0) {return(p0.second == str); });
			if (itr == tokenmap.end())
				return(tokenenum_t::Invalid);
			return((*itr).first);
		}

		template<typename tokenenum_t, std::map<tokenenum_t, std::string> const & tokenmap>
		void TextParse<tokenenum_t, tokenmap>::generate_tokens(std::string const & text)
		{
			vec_token.clear();
			vec_str.clear();
			std::stringstream content(text);
			while (!content.eof()) {
				std::string segment;
				content >> segment;
				size_t quoteBegin_pos = segment.find(tokenmap.at(tokenenum_t::Quotation));
				if (quoteBegin_pos != std::string::npos) {
					std::string quote_str = segment;
					size_t quoteEnd_pos = quote_str.rfind(tokenmap.at(tokenenum_t::Quotation));
					if (quoteEnd_pos != quoteBegin_pos) {
						quote_str = quote_str.substr(quoteBegin_pos + 1, quoteEnd_pos - quoteBegin_pos - 1);
					}
					else {
						quote_str = quote_str.substr(quoteBegin_pos + 1);
						std::getline(content, segment, tokenmap.at(tokenenum_t::Quotation).at(0));
						quote_str += segment;
					}
					vec_token.push_back(tokenenum_t::Quotation);
					vec_token.push_back(tokenenum_t::StrPlaceholder);
					vec_token.push_back(tokenenum_t::Quotation);
					vec_str.push_back(quote_str);
				}
				else {
					auto token = str_to_token(segment);
					if (token == tokenenum_t::Invalid) {
						vec_str.push_back(segment);
						token = tokenenum_t::StrPlaceholder;
					}
					vec_token.push_back(token);
				}
			}
		}
	}
}
