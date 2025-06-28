//
//  functions.cpp
//  undergrad-research
//
//  Created by Illya Starikov on 01/02/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "functions.h"
#include "constants.h"

std::string getInput(std::string filename) {
    // gross, I know...
    std::ifstream in(filename);
    std::string content((std::istreambuf_iterator<char>(in)),
            (std::istreambuf_iterator<char>()));

    return content;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    return result;
}


std::string insertHeader(std::string program) {
    std::string regexString = "^";
    auto beginningOfProgramRegex = boost::regex(regexString);

    return boost::regex_replace(program, beginningOfProgramRegex, HEADER, boost::match_single_line);
}

std::string insertInjectionCallsInMain(std::string program) {
    auto mainRegex = boost::regex(R"((int|void)\s*?main\(.*?\)\s*?{([\s\S]*)})");
    auto flags = boost::format_first_only | boost::format_perl | boost::match_not_dot_newline;

    boost::smatch results;

    if (boost::regex_search(program, results, mainRegex, flags)) {
        boost::replace_first(program, results[2], insertInjectionCalls(results[2]));
    }

    return program;
}

bool shouldInsertInjectionCall(std::string line) {
    auto primitiveRegexString = std::stringstream();

    auto primitives = { "short", "int", "float", "long", "unsigned", "signed", "char" };
    auto lastPrimitive = "wchar_t";

    primitiveRegexString << R"(\s*?()";

    for (const auto& element : primitives) {
        primitiveRegexString << element << "|";
    }

    primitiveRegexString << lastPrimitive << R"()+([\w\d\[\]\s])+?(=.+?)?;)";

    return !boost::regex_match(line, boost::regex(primitiveRegexString.str()));
}

std::string insertInjectionCalls(std::string main) {
    auto regularExpressionString = std::string(R"(()") +
                                   R"(while\s*\(.*?\)\s*?{\n)" + "|" +
                                   R"(for\s*\(.*?\)\s*?{\n)" + "|" +
                                   R"(if\s*\(.*?\)\s*?{\n)" + "|" +
                                   R"(.*?;\n))";

    auto regex = boost::regex(regularExpressionString);
    auto iterator = boost::sregex_token_iterator(main.begin(), main.end(), regex, 0);

    boost::sregex_token_iterator end;
    auto counter = 0;

    auto mainCopy = main;

    for(; iterator != end; ++iterator) {
        if (shouldInsertInjectionCall(std::string(*iterator))) {
            auto ss = std::stringstream();
            ss << "__lineNum__("
               << counter
               << ");\n"
               << *iterator;

            boost::replace_first(mainCopy, std::string(*iterator), ss.str());
            counter++;
        }
    }
    return mainCopy;
}

std::string replaceWhileLoops(std::string program) {
    std::string regularExpressionString = R"(while\s*\((.*?)\)\s*({((?>[^{}]+|(?2))*)}))";
    auto forLoopRegex = boost::regex(regularExpressionString);
    boost::smatch results;

    auto loopCounter = 1;
    auto flags = boost::format_first_only | boost::format_perl | boost::match_not_dot_newline;

    while (boost::regex_search(program, results, forLoopRegex, flags)) {
        std::stringstream ss;

        auto condition  = results[1];
        auto body       = results[3];

        ss << "WHILELOOP" << loopCounter << ":\n\n"  <<
            body << "\n\n" <<
            "if (" << condition << ") {\n" <<
            "  goto WHILELOOP" << loopCounter << ";\n" <<
            "}\n";

        loopCounter += 1;
        program = boost::regex_replace(program, forLoopRegex, ss.str(), flags);
    }

    return program;
}

std::string replaceForLoops(std::string program) {
    std::string regularExpressionString =  R"(for\s*\((.*?);(.*?);(.*?)\)\s*({((?>[^{}]+|(?4))*)}))";

    auto forLoopRegex = boost::regex(regularExpressionString);
    boost::smatch results;

    auto loopCounter = 1;
    auto flags = boost::format_first_only | boost::format_perl | boost::match_not_dot_newline;

    while (boost::regex_search(program, results, forLoopRegex, flags)) {
        std::stringstream ss;

        auto init       = results[1];
        auto condition  = results[2];
        auto iteration  = results[3];
        auto body       = results[5];

        ss << init << ";\n" <<
            "FORLOOP" << loopCounter << ":\n\n"  <<
            body << "\n\n" <<
            iteration << ";\n"
            "if (" << condition << ") {\n" <<
            "  goto FORLOOP" << loopCounter << ";\n" <<
            "}\n";

        loopCounter += 1;
        program = boost::regex_replace(program, forLoopRegex, ss.str(), flags);
    }

    return program;
}

