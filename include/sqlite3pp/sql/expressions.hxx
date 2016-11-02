#pragma once

#include <tuple>
#include <utility>

#include "sqlite3pp/sql/serializable.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"
#include "sqlite3pp/sql/data_type.hxx"


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
    static constexpr auto AS_STR = sql_strings::AS.join(sql_strings::SPACE, sql_strings::SPACE);

    static constexpr auto NOT_LIKE_STR = sql_strings::NOT_LIKE.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_GLOB_STR = sql_strings::NOT_GLOB.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_MATCH_STR = sql_strings::NOT_MATCH.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_REGEXP_STR = sql_strings::NOT_REGEXP.join(sql_strings::SPACE, sql_strings::SPACE);
    static constexpr auto NOT_BETWEEN_STR = sql_strings::NOT_BETWEEN.join(sql_strings::SPACE, sql_strings::SPACE);
}


namespace sqlite3pp {
    namespace sql {

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

            constexpr auto to_str() const { return join_constexpr_strings(operator_string, expression_value.to_str()); }

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

        template <class ExpressionT, class DataTypeT>
        class cast_expression : public expression<cast_expression<ExpressionT, DataTypeT>> {
        public:
            constexpr cast_expression(const expression<ExpressionT> &value_expression, const data_type<DataTypeT> &data_type)
                : value_expression{static_cast<const ExpressionT &>(value_expression)}, data_type{data_type} {}

            constexpr auto to_str() const {
                const auto as_expression_str = sql_strings::SPACE.join(value_expression.to_str(), sql_strings::AS, data_type.to_str());
                return join_constexpr_strings(sql_strings::CAST, sql_strings::OPEN_PARENTHESIS, as_expression_str, sql_strings::CLOSE_PARENTHESIS);
            }

        private:
            const ExpressionT &value_expression;
            DataTypeT data_type;
        };

        template <class ExpressionT>
        class count_expression : public expression<count_expression<ExpressionT>> {
        public:
            constexpr count_expression(const expression<ExpressionT> &value_expression)
                    : expression{static_cast<const ExpressionT &>(value_expression)} {}

            constexpr auto to_str() const {
                return join_constexpr_strings(sql_strings::COUNT, sql_strings::OPEN_PARENTHESIS, expression.to_str(), sql_strings::CLOSE_PARENTHESIS);
            }

        private:
            const ExpressionT &expression;
        };

    }
}
