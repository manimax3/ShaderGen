#pragma once
#include "expression.h"
#include "parsing.h"

namespace sg::parse {

template<typename I>
struct ConstantGrammar : public qi::grammar<I, ast::Constant(), space_type> {
    ConstantGrammar()
        : ConstantGrammar::base_type(mStart, "Constant")
    {
        mLit %= qi::lexeme[(qi::lit("\"") >> *(qi::char_ - '"')) > '"'];
        mReal %= qi::double_ | qi::float_;
        mInt %= qi::int_;
        mStart %= mInt | mReal | mLit;

        mLit.name("LiteralConstant");
        mReal.name("RealNumConstant");
        mInt.name("IntNumConstant");
        mStart.name("Constant");
    }

private:
    qi::rule<I, ast::Constant(), space_type>        mStart;
    qi::rule<I, ast::LiteralConstant(), space_type> mLit;
    qi::rule<I, ast::RealNumConstant(), space_type> mReal;
    qi::rule<I, ast::IntNumConstant(), space_type>  mInt;
};

struct BinOperationSymbol : qi::symbols<char, ast::BinOperation> {
    BinOperationSymbol()
    {
        add("+", ast::BinOperation::Plus)("-", ast::BinOperation::Minus)(
            "*", ast::BinOperation::Mult)("/", ast::BinOperation::Div);
    }
} binOperationSymbol;

template<typename I>
struct ExpressionGrammar
    : public qi::grammar<I, ast::Expression(), space_type> {

    ExpressionGrammar()
        : ExpressionGrammar::base_type(mStart, "Expression")
    {

        using phoenix::assign;
        using phoenix::at_c;
        using phoenix::push_back;
        using qi::_val;

        mFuncCall %= mIdentifier >> '(' >> -(mStart >> *(',' >> mStart)) >> ')';
        mBinary %= mStart >> binOperationSymbol >> mStart;
        mIndex %= mStart >> '[' >> mStart >> ']';
        mIdentifier %= (qi::alpha | '_') >> *(qi::alnum | '_');
        mStart %= mConstantGrammar | mFuncCall | mIndex | mBinary;

        mFuncCall.name("FuncCallExpression");
        mBinary.name("BinaryExpression");
        mIndex.name("IndexExpression");
        mIdentifier.name("IndexExpression");
        mStart.name("Expression");

        qi::on_error<qi::fail>
        (
            mStart
          , std::cout
                << val("Error! Expecting ")
                << _4                               // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2)   // iterators to error-pos, end
                << val("\"")
                << std::endl
        );
    }

private:
    qi::rule<I, ast::Expression(), space_type>         mStart;
    qi::rule<I, ast::FuncCallExpression(), space_type> mFuncCall;
    qi::rule<I, ast::BinaryExpression(), space_type>   mBinary;
    qi::rule<I, ast::IndexExpression(), space_type>    mIndex;
    qi::rule<I, std::string()>                         mIdentifier;
    ConstantGrammar<I>                                 mConstantGrammar;
};
}
