#pragma once
#include "../enum.h"
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace sg::ast {

BETTER_ENUM(BinOperation, int, Plus, Minus, Mult, Div);

struct LiteralConstant {
    std::string value;
};

struct RealNumConstant {
    double value;
};

struct IntNumConstant {
    int value;
};

using Constant
    = boost::variant<LiteralConstant, RealNumConstant, IntNumConstant>;

struct FuncCallExpression;

struct IndexExpression;

struct BinaryExpression;

using Expression = boost::variant<Constant,
                                  boost::recursive_wrapper<FuncCallExpression>,
                                  boost::recursive_wrapper<IndexExpression>,
                                  boost::recursive_wrapper<BinaryExpression>>;

struct FuncCallExpression {
    std::string             identifier;
    std::vector<Expression> arguments;
};

struct IndexExpression {
    Expression inner;
    Expression outer;
};

struct BinaryExpression {
    Expression   lhs;
    BinOperation op = BinOperation::Plus;
    Expression   rhs;
};
}

BOOST_FUSION_ADAPT_STRUCT(sg::ast::LiteralConstant, value);
BOOST_FUSION_ADAPT_STRUCT(sg::ast::RealNumConstant, value);
BOOST_FUSION_ADAPT_STRUCT(sg::ast::IntNumConstant, value);
BOOST_FUSION_ADAPT_STRUCT(sg::ast::FuncCallExpression, identifier, arguments);
BOOST_FUSION_ADAPT_STRUCT(sg::ast::IndexExpression, inner, outer);
BOOST_FUSION_ADAPT_STRUCT(sg::ast::BinaryExpression, lhs, op, rhs);
