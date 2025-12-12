#include "Four.h"
#include <gtest/gtest.h>
#include <string>

// ==================== ТЕСТЫ КОНСТРУКТОРОВ ====================
TEST(FourTest, DefaultConstructor) {
    Four f;
    EXPECT_EQ(f.to_string(), "0");
    EXPECT_EQ(f.size(), 1);
}

TEST(FourTest, ConstructorWithSizeAndFillValid) {
    Four f1(5, 2);
    EXPECT_EQ(f1.to_string(), "22222");
    EXPECT_EQ(f1.size(), 5);
    
    Four f2(3, 0);
    EXPECT_EQ(f2.to_string(), "0");
    EXPECT_EQ(f2.size(), 3);
    
    Four f3(1, 3);
    EXPECT_EQ(f3.to_string(), "3");
    EXPECT_EQ(f3.size(), 1);
}

TEST(FourTest, ConstructorWithSizeAndFillInvalid) {
    EXPECT_THROW(Four(3, 4), std::invalid_argument);
    EXPECT_THROW(Four(2, 5), std::invalid_argument);
    EXPECT_THROW(Four(0, 0), std::invalid_argument);
}

TEST(FourTest, ConstructorWithInitializerListValid) {
    Four f1 = {1, 2, 3, 0};
    EXPECT_EQ(f1.to_string(), "321");
    EXPECT_EQ(f1.size(), 4);
    
    Four f2 = {0};
    EXPECT_EQ(f2.to_string(), "0");
    EXPECT_EQ(f2.size(), 1);
    
    Four f3 = {3, 2, 1};
    EXPECT_EQ(f3.to_string(), "123");
    EXPECT_EQ(f3.size(), 3);
}

TEST(FourTest, ConstructorWithInitializerListEmpty) {
    Four f = {};
    EXPECT_EQ(f.to_string(), "0");
    EXPECT_EQ(f.size(), 1);
}

TEST(FourTest, ConstructorWithInitializerListInvalid) {
    EXPECT_THROW(Four({1, 2, 4}), std::invalid_argument);
    EXPECT_THROW(Four({3, 5}), std::invalid_argument);
}

TEST(FourTest, ConstructorFromStringValid) {
    Four f1("1230");
    EXPECT_EQ(f1.to_string(), "1230");
    EXPECT_EQ(f1.size(), 4);
    
    Four f2("0");
    EXPECT_EQ(f2.to_string(), "0");
    EXPECT_EQ(f2.size(), 1);
    
    Four f3("333");
    EXPECT_EQ(f3.to_string(), "333");
    EXPECT_EQ(f3.size(), 3);
    
    Four f4("00123");
    EXPECT_EQ(f4.to_string(), "123");
}

TEST(FourTest, ConstructorFromStringEmpty) {
    Four f("");
    EXPECT_EQ(f.to_string(), "0");
    EXPECT_EQ(f.size(), 1);
}

TEST(FourTest, ConstructorFromStringInvalid) {
    EXPECT_THROW(Four("1234"), std::invalid_argument);
    EXPECT_THROW(Four("567"), std::invalid_argument);
    EXPECT_THROW(Four("12a3"), std::invalid_argument);
}

TEST(FourTest, CopyConstructor) {
    Four original("1230");
    Four copy(original);
    
    EXPECT_EQ(copy.to_string(), "1230");
    EXPECT_EQ(copy.size(), 4);
    EXPECT_TRUE(copy.equals(original));
}

TEST(FourTest, MoveConstructor) {
    Four original("1230");
    size_t originalSize = original.size();
    
    Four moved(std::move(original));
    
    EXPECT_EQ(moved.to_string(), "1230");
    EXPECT_EQ(moved.size(), originalSize);
    EXPECT_EQ(original.size(), 0);
}

// ==================== ТЕСТЫ МЕТОДА COPY() ====================
TEST(FourTest, CopyMethod) {
    Four original("1230");
    Four copied = original.copy();
    
    EXPECT_EQ(copied.to_string(), "1230");
    EXPECT_EQ(copied.size(), original.size());
    EXPECT_TRUE(copied.equals(original));
}

// ==================== ТЕСТЫ СЛОЖЕНИЯ ====================
TEST(FourTest, AdditionBasic) {
    Four a("0");
    Four b("0");
    EXPECT_EQ(a.add(b).to_string(), "0");
    
    Four c("1");
    Four d("0");
    EXPECT_EQ(c.add(d).to_string(), "1");
}

TEST(FourTest, AdditionWithoutCarry) {
    Four a("12");
    Four b("21");
    EXPECT_EQ(a.add(b).to_string(), "33");
}

TEST(FourTest, AdditionWithCarry) {
    Four a("3");
    Four b("1");
    EXPECT_EQ(a.add(b).to_string(), "10");
    
    Four c("13");
    Four d("12");
    EXPECT_EQ(c.add(d).to_string(), "31");
}

TEST(FourTest, AdditionWithDifferentLengths) {
    Four a("1230");
    Four b("21");
    EXPECT_EQ(a.add(b).to_string(), "1311");
}

TEST(FourTest, AdditionWithCarryToNewDigit) {
    Four a("333");
    Four b("1");
    EXPECT_EQ(a.add(b).to_string(), "1000");
}

// ==================== ТЕСТЫ ВЫЧИТАНИЯ ====================
TEST(FourTest, SubtractionBasic) {
    Four a("1");
    Four b("0");
    EXPECT_EQ(a.subtract(b).to_string(), "1");
    
    Four c("10");
    Four d("1");
    EXPECT_EQ(c.subtract(d).to_string(), "3");
}

TEST(FourTest, SubtractionWithoutBorrow) {
    Four a("32");
    Four b("12");
    EXPECT_EQ(a.subtract(b).to_string(), "20");
}

TEST(FourTest, SubtractionWithBorrow) {
    Four a("100");
    Four b("1");
    EXPECT_EQ(a.subtract(b).to_string(), "33");
    
    Four c("1230");
    Four d("321");
    EXPECT_EQ(c.subtract(d).to_string(), "303");
}

TEST(FourTest, SubtractionEqualNumbers) {
    Four a("123");
    Four b("123");
    EXPECT_EQ(a.subtract(b).to_string(), "0");
}

TEST(FourTest, SubtractionThrowsOnNegativeResult) {
    Four a("10");
    Four b("20");
    EXPECT_THROW(a.subtract(b), std::underflow_error);
    
    Four c("1");
    Four d("100");
    EXPECT_THROW(c.subtract(d), std::underflow_error);
}

// ==================== ТЕСТЫ СРАВНЕНИЯ ====================
TEST(FourTest, EqualsSimple) {
    Four a("123");
    Four b("123");
    EXPECT_TRUE(a.equals(b));
}

// ИСПРАВЛЕНО: заменили "124" (недопустимо) на "122"
TEST(FourTest, NotEqualsSimple) {
    Four a("123");
    Four b("122");  // Было "124" - НЕДОПУСТИМАЯ ЦИФРА 4!
    EXPECT_FALSE(a.equals(b));
}

TEST(FourTest, EqualsWithDifferentLengths) {
    Four a("123");
    Four b("0123");
    EXPECT_TRUE(a.equals(b));
}

TEST(FourTest, NotEqualsWithDifferentLengths) {
    Four a("123");
    Four b("12");
    EXPECT_FALSE(a.equals(b));
}

TEST(FourTest, LessThanSimple) {
    Four a("12");
    Four b("123");
    EXPECT_TRUE(a.less_than(b));
}

TEST(FourTest, LessThanEqualLength) {
    Four a("122");
    Four b("123");
    EXPECT_TRUE(a.less_than(b));
}

TEST(FourTest, NotLessThan) {
    Four a("123");
    Four b("12");
    EXPECT_FALSE(a.less_than(b));
}

TEST(FourTest, NotLessThanEqual) {
    Four a("123");
    Four b("123");
    EXPECT_FALSE(a.less_than(b));
}

TEST(FourTest, GreaterThanSimple) {
    Four a("123");
    Four b("12");
    EXPECT_TRUE(a.greater_than(b));
}

TEST(FourTest, GreaterThanEqualLength) {
    Four a("123");
    Four b("122");
    EXPECT_TRUE(a.greater_than(b));
}

TEST(FourTest, NotGreaterThan) {
    Four a("12");
    Four b("123");
    EXPECT_FALSE(a.greater_than(b));
}

TEST(FourTest, NotGreaterThanEqual) {
    Four a("123");
    Four b("123");
    EXPECT_FALSE(a.greater_than(b));
}

TEST(FourTest, CompareWithZeros) {
    Four zero("0");
    Four manyZeros("0000");
    Four one("1");
    Four oneWithZeros("0001");
    
    EXPECT_TRUE(zero.equals(manyZeros));
    EXPECT_TRUE(one.equals(oneWithZeros));
    EXPECT_TRUE(zero.less_than(one));
    EXPECT_TRUE(one.greater_than(zero));
}

// ==================== ТЕСТЫ TO_STRING ====================
TEST(FourTest, ToStringCorrectFormat) {
    Four a("1230");
    EXPECT_EQ(a.to_string(), "1230");
    
    Four b("0");
    EXPECT_EQ(b.to_string(), "0");
    
    Four c("333");
    EXPECT_EQ(c.to_string(), "333");
}

// ==================== ТЕСТЫ SIZE ====================
TEST(FourTest, SizeMethod) {
    Four a;
    EXPECT_EQ(a.size(), 1);
    
    Four b("123");
    EXPECT_EQ(b.size(), 3);
    
    Four c(5, 2);
    EXPECT_EQ(c.size(), 5);
}

// ==================== ТЕСТЫ ЦЕПОЧЕК ОПЕРАЦИЙ ====================
TEST(FourTest, ChainOperations) {
    Four a("123");
    Four b("321");
    Four c("111");
    Four d("3");
    
    Four result1 = a.add(b);
    Four result2 = result1.copy().subtract(c);
    Four result3 = result2.copy().add(d);
    
    EXPECT_EQ(result3.to_string(), "1002");
}

TEST(FourTest, IdentityOperations) {
    Four a("1230");
    Four zero("0");
    
    Four sum = a.add(zero);
    EXPECT_TRUE(sum.equals(a));
    
    Four diff = a.subtract(zero);
    EXPECT_TRUE(diff.equals(a));
    
    Four zeroResult = a.subtract(a.copy());
    EXPECT_TRUE(zeroResult.equals(zero));
}

// ==================== ТЕСТЫ ГРАНИЧНЫХ ЗНАЧЕНИЙ ====================
TEST(FourTest, MaximumDigit) {
    Four maxDigit("3");
    EXPECT_EQ(maxDigit.to_string(), "3");
    
    Four threeDigits("333");
    EXPECT_EQ(threeDigits.to_string(), "333");
}

TEST(FourTest, LargeNumbers) {
    std::string largeStr(50, '1');
    Four large(largeStr);
    EXPECT_EQ(large.to_string(), largeStr);
    
    Four one("1");
    Four result = large.add(one);
    EXPECT_GE(result.size(), largeStr.length());
}

// ==================== ТЕСТЫ ИСКЛЮЧЕНИЙ ====================
TEST(FourTest, ExceptionSafety) {
    EXPECT_THROW(Four("128"), std::invalid_argument);
    EXPECT_THROW(Four({1, 4}), std::invalid_argument);
    EXPECT_THROW(Four(3, 5), std::invalid_argument);
    
    Four small("10");
    Four large("20");
    EXPECT_THROW(small.subtract(large), std::underflow_error);
}

// ==================== ТЕСТЫ НА ИММУТАБЕЛЬНОСТЬ ====================
TEST(FourTest, ImmutabilityCheck) {
    Four original("123");
    std::string originalStr = original.to_string();
    
    Four added = original.add(Four("1"));
    Four subtracted = original.subtract(Four("1"));
    
    EXPECT_EQ(original.to_string(), originalStr);
    EXPECT_EQ(added.to_string(), "130");
    EXPECT_EQ(subtracted.to_string(), "122");
}

// ==================== ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ ====================
TEST(FourTest, PerformanceNoCrash) {
    Four a("1230123012301230");
    Four b("3210321032103210");
    
    EXPECT_NO_THROW({
        Four sum = a.add(b);
        Four diff = a.subtract(Four("1"));
    });
}

// ==================== ТЕСТ СРАВНЕНИЯ ЧИСЕЛ РАЗНОЙ ДЛИНЫ ====================
TEST(FourTest, CompareDifferentLengths) {
    Four shortNum("12");
    Four longNum("1230");
    
    EXPECT_TRUE(shortNum.less_than(longNum));
    EXPECT_TRUE(longNum.greater_than(shortNum));
    EXPECT_FALSE(shortNum.equals(longNum));
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ====================
// ИСПРАВЛЕННЫЙ тест BasicNotEquals
TEST(FourTest, BasicNotEquals) {
    // Проверяем самые базовые случаи
    
    // Случай 1: разные последние цифры
    {
        Four a("1");
        Four b("2");
        EXPECT_FALSE(a.equals(b)) << "1 should not equal 2";
    }
    
    // Случай 2: одинаковые числа
    {
        Four a("123");
        Four b("123");
        EXPECT_TRUE(a.equals(b)) << "123 should equal 123";
    }
    
    // Случай 3: разные числа (ИСПРАВЛЕНО: заменили "124" на "122")
    {
        Four a("123");
        Four b("122");  // Было "124" - ЦИФРА 4 НЕДОПУСТИМА!
        EXPECT_FALSE(a.equals(b)) << "123 should not equal 122";
    }
}

TEST(FourTest, MinimalTest) {
    // Только одно создание
    try {
        Four a("2");
        SUCCEED();
    } catch (const std::exception& e) {
        FAIL() << "Failed: " << e.what();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}