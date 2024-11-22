#include "Translate.h"

#include <regex>
#include <unordered_map>

namespace Translate {

    StringType toInternational(const StringType& ukranianPhonetic) {
        static const std::unordered_map<StringType, StringType> UKRANIAN_DIGRAPHS = {
            {L"\\{дз\\}", L"d̪͡z̪"},
            {L"\\{дж\\}", L"d͡ʒ"},
            {L"\\{дз\\}[`\\'’]", L"d͡ʒʲ"},
            {L"\\(дз\\)", L"d̪͡z̪"},
            {L"\\(дж\\)", L"d͡ʒ"},
            {L"\\(дз\\)[`\\'’]", L"d̪͡z̪ʲ"},
        };

        static const std::unordered_map<StringType, StringType> UKRANIAN_MIXED_VOWELS = {
            {L"еи", L"e"},
            {L"ие", L"ɪ"},
            {L"оу", L"o"}
        };

        static const std::unordered_map<StringType, StringType> UKRANIAN_SOFT_CONSONANTS = {
            {L"д[`\\'’]", L"dʲ"},
            {L"л[`\\'’]", L"lʲ"},
            {L"н[`\\'’]", L"nʲ"},
            {L"р[`\\'’]", L"rʲ"},
            {L"с[`\\'’]", L"sʲ"},
            {L"с[`\\'’]", L"sʲ"},
            {L"т[`\\'’]", L"tʲ"},
            {L"ц[`\\'’]", L"tsʲ"},
            {L"з[`\\'’]", L"zʲ"},

            // haven't seen this stuff in english wiki, I suppose this works like that with soft consonants
            {L"м[`\\'’]", L"mʲ"},
            {L"к[`\\'’]", L"kʲ"}

            // They probably think, that in word джміль[джм'іл'] sound [м'] is hard
            // Or in кішка[к'ішка] [к'] is hard
            // As far as I know as native Ukranian speaker pretty much every consonant
            // is being softened before i (with some exceptions)
        };

        static const std::unordered_map<StringType, StringType> UKRANIAN_STRESSED_VOWELS = {
            {L"а́", L"ɑ"},
            {L"е́", L"ɛ"},
            {L"і́", L"i"},
            {L"и́", L"ɪ"},
            {L"о́", L"ɔ"},
            {L"у́", L"u"},
            {L"а[`\\'’]", L"ɑ"},
            {L"е[`\\'’]", L"ɛ"},
            {L"і[`\\'’]", L"i"},
            {L"и[`\\'’]", L"ɪ"},
            {L"о[`\\'’]", L"ɔ"},
            {L"у[`\\'’]", L"u"}
        };

        static const std::unordered_map<StringType, StringType> UKRANIAN_SEMIVOWELS = {
            {L"й", L"j"},
            {L"ў", L"w"},
        };

        static const std::unordered_map<StringType, StringType> UKRANIAN_STRESSED_CONSONANTS = {
            {L"б", L"b"},
            {L"д", L"d̪"},
            {L"ф", L"f"},
            {L"ґ", L"g"},
            {L"г", L"ɣ"},
            {L"к", L"k"},
            {L"л", L"ɫ"},
            {L"м", L"m"},
            {L"н", L"n̪"},
            {L"п", L"p"},
            {L"р", L"r"},
            {L"с", L"s̪"},
            {L"ш", L"ʃ"},
            {L"т", L"t̪"},
            {L"ц", L"t̪͡s̪"},
            {L"ч", L"t͡ʃ"},
            {L"в", L"w"},
            {L"х", L"x"},
            {L"з", L"z̪"},
            {L"ж", L"ʒ"},
        };

        static const std::unordered_map<StringType, StringType> UKRANIAN_UNSTRESSED_VOWELS = {
            {L"а", L"ɐ"},
            {L"о", L"o"},
            {L"у", L"ʊ"},
            {L"е", L"e"},
            {L"і", L"i"},
            {L"и", L"ɪ"},
        };

        StringType result = ukranianPhonetic;

        for (auto&[ukr, international] : UKRANIAN_DIGRAPHS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }

        for (auto&[ukr, international] : UKRANIAN_MIXED_VOWELS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }

        for (auto&[ukr, international] : UKRANIAN_SOFT_CONSONANTS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }

        for (auto&[ukr, international] : UKRANIAN_STRESSED_VOWELS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }

        for (auto&[ukr, international] : UKRANIAN_SEMIVOWELS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }
        for (auto&[ukr, international] : UKRANIAN_STRESSED_CONSONANTS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }
        for (auto&[ukr, international] : UKRANIAN_UNSTRESSED_VOWELS) {
            result = std::move(std::regex_replace(result, std::wregex(ukr), international));
        }

        return result;
    }

    StringType toUkranian(const StringType& ifa) {
        static const std::unordered_map<StringType, StringType> MULTICHARACTER_SYMBOLS = {
            {L"⟨d͡z⟩", L"{дз}"},
            {L"⟨d͜z⟩", L"{дз}"},
            {L"⟨ʣ⟩", L"{дз}"},



            {L"/d͡ʒ/", L"{дж}"},
            {L"⟨d͡ʒ⟩", L"{дж}"},
            {L"⟨ʤ⟩", L"{дж}"},
            {L"⟨ɟ⟩", L"{дж}"},
            {L"⟨ǰ⟩", L"{дж}"},
            {L"⟨ǧ⟩", L"{дж}"},
        };

        static const std::unordered_map<StringType, StringType> IFA_DIGRAPHS = {
            // дж, дз and дз'(softened дз)

            {L"d͡z", L"{дз}"},
            {L"d͜z", L"{дз}"},
            {L"dz", L"{дз}"},
            {L"d̪͡z̪", L"{дз}"},
            {L"ʣ", L"{дз}"},

            {L"d͡ʒ", L"{дж}"},
            {L"d͡ʒ", L"{дж}"},
            {L"d͜ʒ", L"{дж}"},
            {L"dʒ", L"{дж}"},
            {L"d̠ʲʒ", L"{дж}"},

            {L"d͡zʲ", L"{дз}'"},
            {L"d͜zʲ", L"{дз}'"},
            {L"dzʲ", L"{дз}'"},
            {L"d̪͡z̪ʲ", L"{дз}'"},

            // soft consonants

            {L"dʲ", L"д'"},
            {L"lʲ", L"л'"},
            {L"nʲ", L"н'"},
            {L"rʲ", L"р'"},
            {L"sʲ", L"с'"},
            {L"sʲ", L"с'"},
            {L"tʲ", L"т'"},
            {L"tsʲ", L"ц'"},
            {L"zʲ", L"з'"},
            {L"mʲ", L"м'"},
            {L"kʲ", L"к'"},

            // hard consonants

            {L"t̪͡s̪", L"ц"},
            {L"t͡ʃ", L"ч"},
        };

        static const std::unordered_map<StringType, StringType> IFA_SYMBOLS = {
            {L"ɑ", L"а́"},
            {L"ɛ", L"е́"},
            {L"i", L"і́"},
            {L"ɪ", L"и́"},
            {L"ɔ", L"о́"},
            {L"u", L"у́"},
            {L"e", L"еи"},
            {L"ɪ", L"ие"},
            {L"o", L"оу"},

            {L"d", L"д"},
            {L"l", L"л"},
            {L"ɫ", L"л"},
            {L"n", L"н"},
            {L"r", L"р"},
            {L"s", L"с"},
            {L"s", L"с"},
            {L"t", L"т"},
            {L"ts", L"ц"},
            {L"z", L"з"},
            {L"m", L"м"},
            {L"k", L"к"},

            {L"j", L"й"},
            {L"w", L"ў"},

            {L"b", L"б"},
            {L"d̪", L"д"},
            {L"f", L"ф"},
            {L"g", L"ґ"},
            {L"ɣ", L"г"},
            {L"n̪", L"н"},
            {L"p", L"п"},
            {L"r", L"р"},
            {L"s̪", L"с"},
            {L"ʃ", L"ш"},
            {L"t̪", L"т"},
            {L"w", L"в"},
            {L"x", L"х"},
            {L"z̪", L"з"},
            {L"ʒ", L"ж"},
            {L"ɐ", L"а"},
            {L"o", L"о"},
            {L"ʊ", L"у"},
            {L"e", L"е"},
            {L"i", L"і"},
            {L"ɪ", L"и"},

            // Not sure if this is softening shit, but let it be
            // To be sure, this Ukranian counterpart is mostly included before
            {L"ʲ", L"'"},
        };

        StringType result = ifa;

        for (auto&[international, ukr] : MULTICHARACTER_SYMBOLS) {
            result = std::move(std::regex_replace(result, std::wregex(international), ukr));
        }

        for (auto&[international, ukr] : IFA_DIGRAPHS) {
            result = std::move(std::regex_replace(result, std::wregex(international), ukr));
        }

        for (auto&[international, ukr] : IFA_SYMBOLS) {
            result = std::move(std::regex_replace(result, std::wregex(international), ukr));
        }

        return result;
    }
}
