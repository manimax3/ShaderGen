#pragma once
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/variant.hpp>
#include <vector>

namespace sg {
namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;
using space_type  = qi::ascii::space_type;
}
