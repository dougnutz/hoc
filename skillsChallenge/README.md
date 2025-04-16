# Skills Challenge Solution

This solution contains a console application (`skillsChallenge.App`) and a test library (`skillsChallenge.Tests`) to help you get started with C# development and testing.

## Prerequisites

## Installing the .NET SDK

To develop and run the application, you need to have the .NET SDK installed on your system. Follow these steps to install it:


2. **Install the SDK**:
   - Use the following command in a terminal to install the .NET SDK on Windows:
     ```
     winget install Microsoft.DotNet.SDK.6
     ```
   - Replace `6` with the desired version if needed.

3. **Verify the Installation**:
   - Open a terminal or command prompt.
   - Run the following command to check the installed version of the .NET SDK:
     ```
     dotnet --list-sdks
     ```
   - Ensure that the SDK version is listed and matches the required version for this project (e.g., .NET 6.0).

Once the .NET SDK is installed, you can proceed with building, running, and testing the application as described in the sections above.

## Installing the .NET Runtime

To run the application and tests, you need to have the .NET runtime installed on your system. Follow these steps to install it:

1. **Download the .NET Runtime**:
   - Visit the official .NET download page: [https://dotnet.microsoft.com/download](https://dotnet.microsoft.com/download).
   - Select the appropriate version of the .NET runtime for your operating system (e.g., Windows).

2. **Install the Runtime**:
   - Use the following command in a terminal to install the .NET runtime on Windows:
     ```
     winget install Microsoft.DotNet.Runtime.6
     ```
   - Replace `6` with the desired version if needed.

3. **Verify the Installation**:
   - Open a terminal or command prompt.
   - Run the following command to check the installed version of the .NET runtime:
     ```
     dotnet --list-runtimes
     ```
   - Ensure that the runtime version is listed and matches the required version for this project (e.g., .NET 6.0).

Once the .NET runtime is installed, you can proceed with running the application and tests as described in the sections above.

## Running the Console Application

1. Navigate to the `skillsChallenge.App` directory in the terminal:
   ```
   cd skillsChallenge.App
   ```
2. Run the console application:
   ```
   dotnet run
   ```
3. You should see the output `Hello, World!` in the terminal.

## Opening the Terminal in Visual Studio Code

To run commands like `dotnet run` or `dotnet test`, you need to open the terminal in Visual Studio Code. Follow these steps:

1. **Keyboard Shortcut**:
   - Press `Ctrl + `` (backtick)` on your keyboard. This is the quickest way to toggle the terminal.

2. **Menu Option**:
   - Click on the `View` menu at the top of the Visual Studio Code window.
   - Select `Terminal` from the dropdown menu.

3. **Command Palette**:
   - Press `Ctrl + Shift + P` to open the Command Palette.
   - Type `Terminal: Create New Integrated Terminal` and select it from the list.

The terminal will open at the bottom of the Visual Studio Code window. From there, you can run commands to build, run, and test the application.

## Running the Tests

1. Navigate to the root directory of the solution (where `skillsChallenge.sln` is located).
2. Run the tests using the following command:
   ```
   dotnet test
   ```
3. Ensure all tests pass successfully.

## Lesson: Making Change for a Dollar

In this lesson, you will modify the console application to calculate and display the change for a given amount in cents. The change should be broken down into dollars, quarters, dimes, nickels, and pennies.

### Steps to Complete the Lesson

1. **Open the Project**:
   - Open the `skillsChallenge.App` project in Visual Studio Code.
   - Navigate to the `Program.cs` file.

2. **Modify the Code**:
   - Locate the `Main` method in `Program.cs`.
   - Add a new method named `CalculateChange` that takes an integer (total cents) as input and returns the number of dollars, quarters, dimes, nickels, and pennies.

   Example method signature:
   ```csharp
   public static (int dollars, int quarters, int dimes, int nickels, int pennies) CalculateChange(int totalCents)
   ```

   - Implement the logic to calculate the change. For example:
     - 1 dollar = 100 cents
     - 1 quarter = 25 cents
     - 1 dime = 10 cents
     - 1 nickel = 5 cents
     - 1 penny = 1 cent

3. **Update the Main Method**:
   - Call the `CalculateChange` method from the `Main` method.
   - Display the results in the console.

   Example:
   ```csharp
   Console.WriteLine("Enter the total amount in cents:");
   int totalCents = int.Parse(Console.ReadLine());

   var change = CalculateChange(totalCents);
   Console.WriteLine($"Dollars: {change.dollars}, Quarters: {change.quarters}, Dimes: {change.dimes}, Nickels: {change.nickels}, Pennies: {change.pennies}");
   ```

4. **Test Your Changes**:
   - Run the application by navigating to the `skillsChallenge.App` directory and executing:
     ```
     dotnet run
     ```
   - Enter a value in cents (e.g., 187) and verify that the output correctly displays the change.

5. **Verify with Unit Tests**:
   - Add or modify unit tests in the `skillsChallenge.Tests` project to validate the `CalculateChange` method.
   - Run the tests using:
     ```
     dotnet test
     ```
   - Ensure all tests pass successfully.

### Learning Objectives
- Understand how to break down a problem into smaller components.
- Learn how to implement and test a method in C#.
- Gain experience in debugging and verifying code functionality.

## Troubleshooting

- If you encounter any issues, ensure that the .NET SDK is correctly installed and added to your system's PATH.
- Make sure you are running the commands from the correct directories as specified above.