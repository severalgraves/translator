#include "gtest.h"

#include "translator.h"

TEST(TNumber, can_create_number)
{
	ASSERT_NO_THROW(Number num(5.5));
}

TEST(TNumber, can_get_number_value)
{
	Number num(2);

	EXPECT_EQ(num.getValue(), 2);
}

TEST(TOperator, can_create_operation)
{
	ASSERT_NO_THROW(Operator op(2.5));
}

TEST(TOperator, can_get_operation)
{
	Operator op('+');

	EXPECT_EQ(op.getOp(), '+');
}

TEST(TOpeningBracket, can_create_open_bracket)
{
	ASSERT_NO_THROW(Bracket ob('('));
}

TEST(TOpeningBracket, can_get_open_bracket)
{
	Bracket ob('(');

	EXPECT_EQ(ob.get_op(), '(');
}

TEST(TClosingBracket, can_create_close_bracket)
{
	ASSERT_NO_THROW(Bracket cb(')'));
}

TEST(TClosingBracket, can_get_close_bracket)
{
	Bracket cb(')');
	EXPECT_EQ(cb.get_op(), ')');
}

TEST(tTranslator, can_create_expression)
{
	ASSERT_NO_THROW(Translator expr("3*2-4"));
}

TEST(tTranslator, impossible_division_by_zero)
{
	Translator expr("5/0");

	ASSERT_ANY_THROW(expr.solve());
}

TEST(tTranslator, can_add)
{

	Translator expr("3+4.5");

	double s = 3 + 4.5;

	EXPECT_EQ(s, expr.Calculation());
}

TEST(tTranslator, can_subtract)
{

	Translator expr("3-4.5");

	double a = 3 - 4.5;


	EXPECT_EQ(a, expr.Calculation());
}

TEST(tTranslator, can_multiply)
{

	Translator expr("3*4.5");

	double a = 3 * 4.5;


	EXPECT_EQ(a, expr.Calculation());
}

TEST(tTranslator, can_divide)
{

	Translator expr("3/4.5");

	double a = 3.8;


	EXPECT_NE(a, expr.Calculation());
}

TEST(tTranslator, invalid_brackets)
{
	Translator expr1("((33/29)");

	Translator expr2("((33/2)+19))");

	Translator expr3("(33/2+1)(2+29))");

	ASSERT_ANY_THROW(expr1.solve());

	ASSERT_ANY_THROW(expr2.solve());

	ASSERT_ANY_THROW(expr3.solve());
}

TEST(tTranslator, combination_of_operations_without_errors)
{
	Translator expr("(5.2-3)*(8+2.5)/(4+1)");

	ASSERT_NO_THROW(expr.Calculation());
}

TEST(tTranslator, combination_of_operations_and_priority_with_correct_answer)
{
	Translator expr("(5.2-3)*(8+2.5)/(4+1)");

	double d = (5.2 - 3) * (8 + 2.5) / (4 + 1);

	EXPECT_EQ(d, expr.Calculation());
}

TEST(tTranslator, two_operators_in_a_row)
{
	Translator expr("3++2*5");
	ASSERT_ANY_THROW(expr.solve());
}
