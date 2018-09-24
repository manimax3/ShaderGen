#include "../src/log.h"
#include "../src/parsing/expression_parser.h"
#include "catch2/catch.hpp"

TEST_CASE("Expression parsing", "[parsing]")
{
    sg::parse::ExpressionGrammar<std::string::iterator> parser{};

    SECTION("FuncCallExpression")
    {
        std::string str   = "func(10,\"100\",hallo(10))";
        auto        begin = std::begin(str);
        auto        end   = std::end(str);

        sg::ast::Expression exp;

        REQUIRE(boost::spirit::qi::phrase_parse(
            begin, end, parser, boost::spirit::ascii::space, exp));
        REQUIRE(begin == end);
        REQUIRE(boost::get<sg::ast::FuncCallExpression>(exp).identifier
                == "func");
        REQUIRE(boost::get<sg::ast::FuncCallExpression>(exp).arguments.size()
                == 3);
    }

    SECTION("BinaryExpression")
    {
        std::string str   = "10 + 20";
        auto        begin = std::begin(str);
        auto        end   = std::end(str);

        sg::ast::Expression exp;

        REQUIRE(boost::spirit::qi::phrase_parse(
            begin, end, parser, boost::spirit::ascii::space, exp));
        REQUIRE(begin == end);
        REQUIRE(boost::get<sg::ast::BinaryExpression>(exp).op == '+');
    }
}
