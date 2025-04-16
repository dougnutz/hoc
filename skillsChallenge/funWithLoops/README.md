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
}
```