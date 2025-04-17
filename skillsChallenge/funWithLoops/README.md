# funWithLoops

This solution demonstrates the use of various loops in C# through a console application and includes a test project to verify the functionality of each loop.

## Projects

### 1. funWithLoops.ConsoleApp
This is the main console application that contains functions demonstrating different types of loops, such as:
- For loop
- While loop
- Do-while loop
- Foreach loop

Each function returns a string showing the output of the loop.

### 2. funWithLoops.Tests
This is the test project that uses xUnit to test the output of each loop function in the console app. It ensures that the loops behave as expected.

## How to Run

1. Build the solution:
   ```bash
   dotnet build
   ```

2. Run the console app:
   ```bash
   dotnet run --project funWithLoops.ConsoleApp
   ```

3. Run the tests:
   ```bash
   dotnet test
   ```

## Requirements
- .NET 6.0 SDK or later

## License
This project is licensed under the MIT License.

# Lesson: Understanding Loops in C#

This lesson demonstrates how to use different types of loops in C#. Below are examples of each loop type that were previously implemented in the `funWithLoops.ConsoleApp` project.

## For Loop
```csharp
public static string ForLoopExample()
{
    string result = "";
    for (int i = 0; i < 5; i++)
    {
        result += i + " ";
    }
    return result.Trim();
}
```

## While Loop
```csharp
public static string WhileLoopExample()
{
    string result = "";
    int i = 0;
    while (i < 5)
    {
        result += i + " ";
        i++;
    }
    return result.Trim();
}
```

## Do-While Loop
```csharp
public static string DoWhileLoopExample()
{
    string result = "";
    int i = 0;
    do
    {
        result += i + " ";
        i++;
    } while (i < 5);
    return result.Trim();
}
```

## Foreach Loop
```csharp
public static string ForeachLoopExample()
{
    string result = "";
    int[] numbers = { 0, 1, 2, 3, 4 };
    foreach (int number in numbers)
    {
        result += number + " ";
    }
    return result.Trim();
}
```

## For Loop by 7s
```csharp
public static string ForLoopBy7s()
{
    string result = "";
    for (int i = 0; i <= 70; i += 7)
    {
        result += i + " ";
    }
    return result.TrimEnd();
}
```

## Recursive Loop Example
```csharp
public static int RecursiveSum(int n)
{
    if (n <= 0)
        return 0;
    return n + RecursiveSum(n - 1);
}
```

## Explanation of Recursive Call
The `RecursiveSum` function demonstrates a recursive loop by repeatedly calling itself with a decremented value of `n` until the base case is reached. Here's how it works:

1. **Base Case**: The function checks if `n` is less than or equal to 0. If true, it returns 0, which stops the recursion.
2. **Recursive Case**: If `n` is greater than 0, the function adds `n` to the result of calling itself with `n - 1`.

This process continues until the base case is reached, at which point the recursion unwinds, summing up all the values from `n` down to 0.

### Example Walkthrough
For `RecursiveSum(5)`, the function executes as follows:
- `RecursiveSum(5)` returns `5 + RecursiveSum(4)`
- `RecursiveSum(4)` returns `4 + RecursiveSum(3)`
- `RecursiveSum(3)` returns `3 + RecursiveSum(2)`
- `RecursiveSum(2)` returns `2 + RecursiveSum(1)`
- `RecursiveSum(1)` returns `1 + RecursiveSum(0)`
- `RecursiveSum(0)` returns `0` (base case)

The final result is `5 + 4 + 3 + 2 + 1 + 0 = 15`.