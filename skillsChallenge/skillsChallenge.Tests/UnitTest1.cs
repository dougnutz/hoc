using Xunit;

namespace skillsChallenge.Tests;

public class ChangeCalculatorTests
{
    [Fact]
    public void TestNoChange()
    {
        var result = Program.CalculateChange(0);
        Assert.Equal((0, 0, 0, 0, 0), result);
    }

    [Fact]
    public void TestExactDollar()
    {
        var result = Program.CalculateChange(100);
        Assert.Equal((1, 0, 0, 0, 0), result);
    }

    [Fact]
    public void TestMixedChange()
    {
        var result = Program.CalculateChange(187);
        Assert.Equal((1, 3, 1, 0, 2), result);
    }

    [Fact]
    public void TestOnlyCents()
    {
        var result = Program.CalculateChange(4);
        Assert.Equal((0, 0, 0, 0, 4), result);
    }

    [Fact]
    public void TestOnlyQuarters()
    {
        var result = Program.CalculateChange(75);
        Assert.Equal((0, 3, 0, 0, 0), result);
    }

    [Fact]
    public void TestOnlyDimes()
    {
        var result = Program.CalculateChange(20);
        Assert.Equal((0, 0, 2, 0, 0), result);
    }

    [Fact]
    public void TestOnlyNickels()
    {
        var result = Program.CalculateChange(5);
        Assert.Equal((0, 0, 0, 1, 0), result);
    }

    [Fact]
    public void TestOnlyPennies()
    {
        var result = Program.CalculateChange(3);
        Assert.Equal((0, 0, 0, 0, 3), result);
    }
}