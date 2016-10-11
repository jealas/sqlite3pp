#pragma once

#include "sqlite3pp/sql/column.hxx"
#include "sqlite3pp/sql/serializable.hxx"
#include "sqlite3pp/sql/sql_strings.hxx"


namespace {
    using namespace sqlite3pp::sql;

    constexpr auto IS_JOIN_STR = sql_strings::IS.join(sql_strings::SPACE, sql_strings::SPACE);
    constexpr auto IS_NOT_JOIN_STR = sql_strings::IS_NOT.join(sql_strings::SPACE, sql_strings::SPACE);
    constexpr auto LIKE_JOIN_STR = sql_strings::LIKE.join(sql_strings::SPACE, sql_strings::SPACE);

}


namespace sqlite3pp {
    namespace sql {

        template <class LeftSerializableT, class JoinStringT, class RightSerializableT>
        class binary_expression_serializable : public serializable<binary_expression_serializable<LeftSerializableT, JoinStringT, RightSerializableT>> {
        public:
            constexpr binary_expression_serializable(const serializable<LeftSerializableT> &left_serializable,
                    const JoinStringT &join_string,
                    const serializable<RightSerializableT> &right_serializable)

                : left_serializable{left_serializable},
                  join_string{join_string},
                  right_serializable{right_serializable} {}

            constexpr auto to_str() const { return join_string.join(left_serializable.to_str(), right_serializable.to_str()); }

        private:
            LeftSerializableT left_serializable;
            JoinStringT join_string;
            RightSerializableT right_serializable;
        };

        template <class SerializableT>
        class parenthesis_serializable : public serializable<parenthesis_serializable<SerializableT>> {
        public:
            constexpr parenthesis_serializable(const serializable<SerializableT> &serializable_value)
                    : serializable_value{serializable_value} {}

            constexpr auto to_str() const { return serializable_value.to_str().join(sql_strings::OPEN_PARENTHESIS, sql_strings::CLOSE_PARENTHESIS); }

        private:
            SerializableT serializable_value;
        };

        template <class UnaryOperatorT, class SerializableT>
        class unary_expression_serializable : public serializable<SerializableT> {
        public:
            constexpr unary_expression_serializable(const UnaryOperatorT &operator_string, const serializable<SerializableT> &value)
                : operator_string{operator_string}, serializable_value{value} {}

            constexpr auto to_str() const { return serializable_value.to_str().join(operator_string); }

        private:
                UnaryOperatorT operator_string;
                SerializableT serializable_value;
        };

        template <class FunctionNameT, class LeftArgT, class RightArgT>
        class function_serializable {
        public:
            constexpr function_serializable(const FunctionNameT &function_name, const serializable<LeftArgT> &left_arg, const serializable<RightArgT> &right_arg)
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

        //! Surrounds a serializable object with parenthesis.
        //! \param serializable A serializable object.
        //! \return A constexpr_string that corresponds to the serializable surrounded with parenthesis.
        template <class SerializableT>
        constexpr auto P(const serializable<SerializableT> &serializable_value) {
            return parenthesis_serializable<SerializableT>{serializable_value};
        }

        template <class LeftT, class RightT>
        constexpr auto operator || (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::PIPE_PIPE), RightT>{left, sql_strings::PIPE_PIPE, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator * (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::ASTERISK), RightT>{left, sql_strings::ASTERISK, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator / (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::FORWARD_SLASH), RightT>{left, sql_strings::FORWARD_SLASH, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator % (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::PERCENT), RightT>{left, sql_strings::PERCENT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator + (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::PLUS), RightT>{left, sql_strings::PLUS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator - (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::MINUS), RightT>{left, sql_strings::MINUS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator << (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::LEFT_SHIFT), RightT>{left, sql_strings::LEFT_SHIFT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator >> (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::RIGHT_SHIFT), RightT>{left, sql_strings::RIGHT_SHIFT, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator & (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::AMPERSAND), RightT>{left, sql_strings::AMPERSAND, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator | (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::PIPE), RightT>{left, sql_strings::PIPE, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator < (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::LESS_THAN), RightT>{left, sql_strings::LESS_THAN, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator > (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::GREATER_THAN), RightT>{left, sql_strings::GREATER_THAN, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator <= (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::LESS_EQUALS), RightT>{left, sql_strings::LESS_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator >= (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::GREATER_EQUALS), RightT>{left, sql_strings::GREATER_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator == (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::EQUALS_EQUALS), RightT>{left, sql_strings::EQUALS_EQUALS, right};
        }

        template <class LeftT, class RightT>
        constexpr auto operator != (const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(sql_strings::NOT_EQUALS), RightT>{left, sql_strings::NOT_EQUALS, right};
        }

        template <class T>
        constexpr auto operator ~ (const serializable<T> &value) {
            return unary_expression_serializable<decltype(sql_strings::TILDE), T>{sql_strings::TILDE, value};
        }

        template <class T>
        constexpr auto operator + (const serializable<T> &value) {
            return unary_expression_serializable<decltype(sql_strings::PLUS), T>{sql_strings::PLUS, value};
        }

        template <class T>
        constexpr auto operator - (const serializable<T> &value) {
            return unary_expression_serializable<decltype(sql_strings::MINUS), T>{sql_strings::MINUS, value};
        }

        template <class LeftT, class RightT>
        constexpr auto IS(const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(IS_JOIN_STR), RightT>{left, IS_JOIN_STR, right};
        }

        template <class LeftT, class RightT>
        constexpr auto IS_NOT(const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(IS_NOT_JOIN_STR), RightT>{left, IS_NOT_JOIN_STR, right};
        }

        template <class LeftT, class RightT>
        constexpr auto LIKE(const serializable<LeftT> &left, const serializable<RightT> &right) {
            return binary_expression_serializable<LeftT, decltype(LIKE_JOIN_STR), RightT>{left, LIKE_JOIN_STR, right};
        }

        // Prefix + and negation operators.
    }
}
