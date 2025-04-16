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
    }
}