#pragma once

#include <tuple>
#include <utility>

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/serializable.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"


namespace {
    using namespace sqlite3pp::sql;

    static constexpr auto IS_NOT_STR = sql_strings::IS_NOT.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto IS_STR = sql_strings::IS.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto LIKE_STR = sql_strings::LIKE.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto GLOB_STR = sql_strings::GLOB.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto MATCH_STR = sql_strings::MATCH.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto REGEXP_STR = sql_strings::REGEXP.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto AND_STR = sql_strings::AND.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto OR_STR = sql_strings::OR.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_STR = sql_strings::SPACE.join(sql_strings::NOT);

    static constexpr auto NOT_LIKE_STR = sql_strings::NOT_LIKE.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_GLOB_STR = sql_strings::NOT_GLOB.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_MATCH_STR = sql_strings::NOT_MATCH.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_REGEXP_STR = sql_strings::NOT_REGEXP.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_BETWEEN_STR = sql_strings::NOT_BETWEEN.join(sql_strings::SPACE, sql_strings::SPACE);
}


namespace sqlite3pp {
    namespace sql {

        // Forward declare the two exprsesion types.
        template <class>
        class is_expression_member;

        template <class>
        class not_expression_member;

        template <class, class, class>
        class binary_operator_expression;

        template <class, class, class>
        class between_expression;

        template <class, class, class>
        class not_between_expression;

        template <class ExpressionT>
        class expression : public serializable<ExpressionT> {
        public:
            constexpr expression() : IS{*this}, NOT{*this} {}

            template <class OtherExpressionT>
            constexpr auto AND(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(AND_STR), OtherExpressionT>{*this, AND_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto OR(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(OR_STR), OtherExpressionT>{*this, OR_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto LIKE(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(LIKE_STR), OtherExpressionT>{*this, LIKE_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto GLOB(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(GLOB_STR), OtherExpressionT>{*this, GLOB_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto REGEXP(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(REGEXP_STR), OtherExpressionT>{*this, REGEXP_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto MATCH(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(MATCH_STR), OtherExpressionT>{*this, MATCH_STR, other_expression};
            }

            template <class StartExpressionT, class EndExpressionT>
            constexpr auto BETWEEN(const expression<StartExpressionT> &start, const expression<EndExpressionT> &end) const {
                return between_expression<ExpressionT, StartExpressionT, EndExpressionT>{*this, start, end};
            }

        public:
            is_expression_member<ExpressionT> IS;
            not_expression_member<ExpressionT> NOT;
        };

        // Full expression types.
        template <class LeftExpressionT, class JoinStringT, class RightExpressionT>
        class binary_operator_expression : public expression<binary_operator_expression<LeftExpressionT, JoinStringT, RightExpressionT>> {
        public:
            constexpr binary_operator_expression(const expression<LeftExpressionT> &left_expression,
                    const JoinStringT &join_string,
                    const expression<RightExpressionT> &right_expression)

                : left_expression{static_cast<const LeftExpressionT &>(left_expression)},
                  join_string{join_string},
                  right_expression{static_cast<const RightExpressionT &>(right_expression)} {}

            constexpr auto to_str() const { return join_string.join(left_expression.to_str(), right_expression.to_str()); }

        private:
            const LeftExpressionT &left_expression;
            JoinStringT join_string;
            const RightExpressionT &right_expression;
        };

        // Helper member expression types.
        template <class ExpressionT>
        class is_expression_member {
        public:
            constexpr is_expression_member(const expression<ExpressionT> &parent_expression)
                : parent_expression{static_cast<const ExpressionT &>(parent_expression)} {}

            template <class OtherExpressionT>
            constexpr auto NOT(const expression<OtherExpressionT> &other_expression) const { return binary_operator_expression<ExpressionT, decltype(IS_NOT_STR), OtherExpressionT>{parent_expression, IS_NOT_STR, other_expression}; } 

            template <class OtherExpressionT>
            constexpr auto operator()(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(IS_STR), OtherExpressionT>{parent_expression, IS_STR, other_expression};
            }

        private:
            const ExpressionT &parent_expression;
        };

        template <class ExpressionT>
        class not_expression_member {
        public:
            constexpr not_expression_member(expression<ExpressionT> &parent_expression)
                : parent_expression{static_cast<const ExpressionT &>(parent_expression)} {}

            template <class OtherExpressionT>
            constexpr auto LIKE(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(NOT_LIKE_STR), OtherExpressionT>{parent_expression, NOT_LIKE_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto GLOB(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(NOT_GLOB_STR), OtherExpressionT>{parent_expression, NOT_GLOB_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto REGEXP(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(NOT_REGEXP_STR), OtherExpressionT>{parent_expression, NOT_REGEXP_STR, other_expression};
            }

            template <class OtherExpressionT>
            constexpr auto MATCH(const expression<OtherExpressionT> &other_expression) const {
                return binary_operator_expression<ExpressionT, decltype(NOT_MATCH_STR), OtherExpressionT>{parent_expression, NOT_MATCH_STR, other_expression};
            }

            template <class StartExpressionT, class EndExpressionT>
            constexpr auto BETWEEN(const expression<StartExpressionT> &start, const expression<EndExpressionT> &end) const {
                return not_between_expression<ExpressionT, StartExpressionT, EndExpressionT>{parent_expression, start, end};
            }

        private:
            const ExpressionT &parent_expression;
        }; 

        template <class ValueExpressionT, class StartExpressionT, class EndExpressionT>
        class between_expression : public expression<between_expression<ValueExpressionT, StartExpressionT, EndExpressionT>> {
        public:
            constexpr between_expression(const expression<ValueExpressionT> &value, const expression<StartExpressionT> &start, const expression<EndExpressionT> &end)
                : value{static_cast<const ValueExpressionT &>(value)}, start{static_cast<const StartExpressionT &>(start)}, end{static_cast<const EndExpressionT &>(end)}  {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(value.to_str(), sql_strings::BETWEEN, start.to_str(), sql_strings::AND, end.to_str()); }

        private:
            const ValueExpressionT &value;
            const StartExpressionT &start;
            const EndExpressionT &end;
        };

        template <class ValueExpressionT, class StartExpressionT, class EndExpressionT>
        class not_between_expression : public expression<not_between_expression<ValueExpressionT, StartExpressionT, EndExpressionT>> {
        public:
            constexpr not_between_expression(const expression<ValueExpressionT> &value, const expression<StartExpressionT> &start, const expression<EndExpressionT> &end)
                : value{static_cast<const ValueExpressionT &>(value)}, start{static_cast<const StartExpressionT &>(start)}, end{static_cast<const EndExpressionT &>(end)}  {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(value.to_str(), sql_strings::NOT_BETWEEN, start.to_str(), sql_strings::AND, end.to_str()); }

        private:
            const ValueExpressionT &value;
            const StartExpressionT &start;
            const EndExpressionT &end;
        };

        template <class ExpressionT>
        class parenthesis_expression : public expression<parenthesis_expression<ExpressionT>> {
        public:
            constexpr parenthesis_expression(const expression<ExpressionT> &expression_value)
                    : expression_value{static_cast<const ExpressionT &>(expression_value)} {}

            constexpr auto to_str() const { return expression_value.to_str().join(sql_strings::OPEN_PARENTHESIS, sql_strings::CLOSE_PARENTHESIS); }

        private:
            const ExpressionT &expression_value;
        };

        template <class UnaryOperatorT, class ExpressionT>
        class unary_operator_expression : public expression<unary_operator_expression<UnaryOperatorT, ExpressionT>> {
        public:
            constexpr unary_operator_expression(const UnaryOperatorT &operator_string, const expression<ExpressionT> &value)
                : operator_string{operator_string}, expression_value{static_cast<const ExpressionT &>(value)} {}

            constexpr auto to_str() const { return expression_value.to_str().join(operator_string); }

        private:
                UnaryOperatorT operator_string;
                const ExpressionT &expression_value;
        };

        template <class FunctionNameT, class ... ArgsT>
        class function_expression : public expression<function_expression<FunctionNameT, ArgsT...>> {
        public:
            constexpr function_expression(const FunctionNameT &function_name, const expression<ArgsT> & ... args)
                : function_name{function_name}, args{static_cast<const ArgsT &>(args)...} {}

            constexpr auto to_str() const {
                return join_constexpr_strings(function_name, sql_strings::OPEN_PARENTHESIS, make_args_str(), sql_strings::CLOSE_PARENTHESIS);
            }

        private:
            template <std::size_t ... Indexes>
            constexpr auto make_args_str_helper(std::index_sequence<Indexes...>) const {
                return sql_strings::COMMA.join(std::get<Indexes>(args).to_str()...);
            }

            constexpr auto make_args_str() const {
                return make_args_str_helper(std::make_index_sequence<sizeof...(ArgsT)>());
            }

        private:
            FunctionNameT function_name;
            std::tuple<const ArgsT & ...> args;
        };

        //! Surrounds expression with parenthesis.
        //! \param expression An expression object.
        //! \return A constexpr_string that corresponds to the expression surrounded with parenthesis.
        template <class ExpressionT>
        constexpr auto P(const expression<ExpressionT> &expression_value) {
            return parenthesis_expression<ExpressionT>{expression_value};
        }

        template <class LeftT, class RightT>
        constexpr auto operator || (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::PIPE_PIPE), RightT>{left, sql_strings::PIPE_PIPE, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator * (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::ASTERISK), RightT>{left, sql_strings::ASTERISK, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator / (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::FORWARD_SLASH), RightT>{left, sql_strings::FORWARD_SLASH, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator % (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::PERCENT), RightT>{left, sql_strings::PERCENT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator + (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::PLUS), RightT>{left, sql_strings::PLUS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator - (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::MINUS), RightT>{left, sql_strings::MINUS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator << (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::LEFT_SHIFT), RightT>{left, sql_strings::LEFT_SHIFT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator >> (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::RIGHT_SHIFT), RightT>{left, sql_strings::RIGHT_SHIFT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator & (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::AMPERSAND), RightT>{left, sql_strings::AMPERSAND, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator | (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::PIPE), RightT>{left, sql_strings::PIPE, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator < (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::LESS_THAN), RightT>{left, sql_strings::LESS_THAN, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator > (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::GREATER_THAN), RightT>{left, sql_strings::GREATER_THAN, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator <= (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::LESS_EQUALS), RightT>{left, sql_strings::LESS_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator >= (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::GREATER_EQUALS), RightT>{left, sql_strings::GREATER_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator == (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::EQUALS_EQUALS), RightT>{left, sql_strings::EQUALS_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator != (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_operator_expression<LeftT, decltype(sql_strings::NOT_EQUALS), RightT>{left, sql_strings::NOT_EQUALS, right};
        }

        template <class ExpressionT>
        constexpr auto operator ~ (const expression<ExpressionT> &expr) {
            return unary_operator_expression<decltype(sql_strings::TILDE), ExpressionT>{sql_strings::TILDE, expr};
        }

        template <class ExpressionT>
        constexpr auto operator + (const expression<ExpressionT> &expr) {
            return unary_operator_expression<decltype(sql_strings::PLUS), ExpressionT>{sql_strings::PLUS, expr};
        }

        template <class ExpressionT>
        constexpr auto operator - (const expression<ExpressionT> &expr) {
            return unary_operator_expression<decltype(sql_strings::MINUS), ExpressionT>{sql_strings::MINUS, expr};
        }

        template <class ExpressionT>
        constexpr auto NOT(const expression<ExpressionT> &expr) {
            return function_expression<decltype(sql_strings::NOT), ExpressionT>{sql_strings::NOT, expr};
        }

    }
}
