#pragma once

#include "sqlite3pp/sql/expressions.hxx"
#include "sqlite3pp/sql/data_type.hxx"


namespace sqlite3pp {
    namespace sql {
        namespace operators {

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

            template <class ExpressionT>
            constexpr auto ABS(const expression<ExpressionT> &expr) {
                return function_expression<decltype(sql_strings::ABS), ExpressionT>{sql_strings::ABS, expr};
            }

            template <class ExpressionT, class DataTypeT>
            constexpr auto CAST(const expression<ExpressionT> &expr, const data_type<DataTypeT> &data_type) {
                return cast_expression<ExpressionT, DataTypeT>{expr, data_type};
            }

        }
    }
}
