#pragma once

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/serializable.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"


namespace sqlite3pp {
    namespace sql {

        // Forward declare the two exprsesion types.
        template <class>
        class is_expression_member;

        template <class>
        class not_expression_member;

        template <class>
        class notnull_expression;

        template <class T>
        class expression : public serializable<T> {
        public:
            constexpr expression() : IS{this}, NOT{this} {}

            constexpr operator T&() { return *static_cast<T *>(this); }
            constexpr operator const T&() const { return *static_cast<const T *>(this); }

            constexpr auto NOTNULL() const { return notnull_expression<T>{*this}; }

        public:
            is_expression_member<T> IS;
            not_expression_member<T> NOT;
        };

        // Full expression types.
        template <class LeftExpressionT, class RightExpressionT>
        class is_not_expression : public expression<is_not_expression<LeftExpressionT, RightExpressionT>> {
        public:
            constexpr is_not_expression(const expression<LeftExpressionT> &left_expression, const expression<RightExpressionT> &right_expression)
                : left_expression{left_expression}, right_expression{right_expression} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(left_expression.to_str(), sql_strings::IS_NOT, right_expression.to_str()); }

        private:
            LeftExpressionT left_expression;
            RightExpressionT right_expression;
        };

        template <class ExpressionT>
        class notnull_expression : public expression<notnull_expression<ExpressionT>> {
        public:
            constexpr notnull_expression(const expression<ExpressionT> &parent_expression)
                : parent_expression{parent_expression} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(parent_expression.to_str(), sql_strings::NOTNULL); }

        private:
            ExpressionT parent_expression;
        };

        template <class LeftExpressionT, class RightExpressionT>
        class not_expression : public expression<not_expression<LeftExpressionT, RightExpressionT>> {
        public:
            constexpr not_expression(const expression<LeftExpressionT> &left_expression, const expression<RightExpressionT> &right_expression)
                : left_expression{left_expression}, right_expression{right_expression} {}

            constexpr auto to_str() const { return sql_strings::SPACE.join(left_expression.to_str(), right_expression.to_str()); }

        private:
            LeftExpressionT left_expression;
            RightExpressionT right_expression;
        };

        // Helper member expression types.

        template <class ExpressionT>
        class is_expression_member {
        public:
            constexpr is_expression_member(const expression<ExpressionT> *parent_expression)
                : parent_expression{static_cast<const ExpressionT *>(parent_expression)} {}

            template <class OtherExpressionT>
            constexpr auto NOT(const expression<OtherExpressionT> &other_expression) const { return is_not_expression<ExpressionT, OtherExpressionT>{*parent_expression, other_expression}; } 

        private:
            const ExpressionT *parent_expression;
        };

        template <class ExpressionT>
        class not_expression_member {
        public:
            constexpr not_expression_member(expression<ExpressionT> *parent_expression)
                : parent_expression{static_cast<const ExpressionT *>(parent_expression)} {}

            template <class OtherExpressionT>
            constexpr auto operator()(const expression<OtherExpressionT> &other_expression) {
                return not_expression<ExpressionT, OtherExpressionT>{*parent_expression, other_expression};
            }

        private:
            const ExpressionT *parent_expression;
        }; 

        template <class LeftExpressionT, class JoinStringT, class RightExpressionT>
        class binary_expression : public expression<binary_expression<LeftExpressionT, JoinStringT, RightExpressionT>> {
        public:
            constexpr binary_expression(const expression<LeftExpressionT> &left_expression,
                    const JoinStringT &join_string,
                    const expression<RightExpressionT> &right_expression)

                : left_expression{left_expression},
                  join_string{join_string},
                  right_expression{right_expression} {}

            constexpr auto to_str() const { return join_string.join(left_expression.to_str(), right_expression.to_str()); }

        private:
            LeftExpressionT left_expression;
            JoinStringT join_string;
            RightExpressionT right_expression;
        };

        template <class ExpressionT>
        class parenthesis_expression : public expression<parenthesis_expression<ExpressionT>> {
        public:
            constexpr parenthesis_expression(const expression<ExpressionT> &expression_value)
                    : expression_value{expression_value} {}

            constexpr auto to_str() const { return expression_value.to_str().join(sql_strings::OPEN_PARENTHESIS, sql_strings::CLOSE_PARENTHESIS); }

        private:
            ExpressionT expression_value;
        };

        template <class UnaryOperatorT, class ExpressionT>
        class unary_expression : public expression<unary_expression<UnaryOperatorT, ExpressionT>> {
        public:
            constexpr unary_expression(const UnaryOperatorT &operator_string, const expression<ExpressionT> &value)
                : operator_string{operator_string}, expression_value{value} {}

            constexpr auto to_str() const { return expression_value.to_str().join(operator_string); }

        private:
                UnaryOperatorT operator_string;
                ExpressionT expression_value;
        };

        template <class FunctionNameT, class LeftArgT, class RightArgT>
        class function_expression : public expression<function_expression<FunctionNameT, LeftArgT, RightArgT>> {
        public:
            constexpr function_expression(const FunctionNameT &function_name, const expression<LeftArgT> &left_arg, const expression<RightArgT> &right_arg)
                : function_name{function_name}, left_arg{left_arg}, right_arg{right_arg} {}

            constexpr auto to_str() const {
                const auto args_str = sql_strings::COMMA.join(left_arg.to_str(), right_arg.to_str());
                return join_constexpr_strings(function_name, sql_strings::OPEN_PARENTHESIS, args_str, sql_strings::CLOSE_PARENTHESIS);
            }

        private:
            FunctionNameT function_name;
            LeftArgT left_arg;
            RightArgT right_arg;
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
            return binary_expression<LeftT, decltype(sql_strings::PIPE_PIPE), RightT>{left, sql_strings::PIPE_PIPE, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator * (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::ASTERISK), RightT>{left, sql_strings::ASTERISK, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator / (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::FORWARD_SLASH), RightT>{left, sql_strings::FORWARD_SLASH, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator % (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::PERCENT), RightT>{left, sql_strings::PERCENT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator + (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::PLUS), RightT>{left, sql_strings::PLUS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator - (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::MINUS), RightT>{left, sql_strings::MINUS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator << (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::LEFT_SHIFT), RightT>{left, sql_strings::LEFT_SHIFT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator >> (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::RIGHT_SHIFT), RightT>{left, sql_strings::RIGHT_SHIFT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator & (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::AMPERSAND), RightT>{left, sql_strings::AMPERSAND, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator | (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::PIPE), RightT>{left, sql_strings::PIPE, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator < (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::LESS_THAN), RightT>{left, sql_strings::LESS_THAN, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator > (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::GREATER_THAN), RightT>{left, sql_strings::GREATER_THAN, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator <= (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::LESS_EQUALS), RightT>{left, sql_strings::LESS_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator >= (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::GREATER_EQUALS), RightT>{left, sql_strings::GREATER_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator == (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::EQUALS_EQUALS), RightT>{left, sql_strings::EQUALS_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator != (const expression<LeftT> &left, const expression<RightT> &right) {
            return binary_expression<LeftT, decltype(sql_strings::NOT_EQUALS), RightT>{left, sql_strings::NOT_EQUALS, right};
        }

        template <class T>
        constexpr auto operator ~ (const expression<T> &value) {
            return unary_expression<decltype(sql_strings::TILDE), T>{sql_strings::TILDE, value};
        }

        template <class T>
        constexpr auto operator + (const expression<T> &value) {
            return unary_expression<decltype(sql_strings::PLUS), T>{sql_strings::PLUS, value};
        }

        template <class T>
        constexpr auto operator - (const expression<T> &value) {
            return unary_expression<decltype(sql_strings::MINUS), T>{sql_strings::MINUS, value};
        }
    }
}
