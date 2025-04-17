using Xunit;
using funWithLoops.ConsoleApp;

namespace funWithLoops.Tests
{
    public class LoopTests
    {
        [Fact]
        public void ForLoopExample_ReturnsCorrectResult()
        {
            // Act
            var result = Program.ForLoopExample();

            // Assert
            Assert.Equal("0 1 2 3 4", result);
        }
        
        [Fact]
        public void ForLoopBy7s_ReturnsCorrectResult()
        {
            // Act
            var result = Program.ForLoopBy7s();

            // Assert
            Assert.Equal("0, 7, 14, 21, 28, 35, 42, 49, 56, 63, 70", result);
        }

        [Fact]
        public void WhileLoopExample_ReturnsCorrectResult()
        {
            // Act
            var result = Program.WhileLoopExample();

            // Assert
            Assert.Equal("0 1 2 3 4", result);
        }

        [Fact]
        public void DoWhileLoopExample_ReturnsCorrectResult()
        {
            // Act
            var result = Program.DoWhileLoopExample();

            // Assert
            Assert.Equal("0 1 2 3 4", result);
        }

        [Fact]
        public void ForeachLoopExample_ReturnsCorrectResult()
        {
            // Act
            var result = Program.ForeachLoopExample();

            // Assert
            Assert.Equal("0 1 2 3 4", result);
        }

        [Fact]
        public void RecursiveSum_ReturnsCorrectResult()
        {
            // Act
            var result = Program.RecursiveSum(5);

            // Assert
            Assert.Equal(15, result); // 5 + 4 + 3 + 2 + 1 + 0 = 15
        }
    }
}