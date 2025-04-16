using System;

public class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Enter the total amount in cents:");
        int totalCents = int.Parse(Console.ReadLine());

        var change = CalculateChange(totalCents);
        Console.WriteLine($"Dollars: {change.dollars}, Quarters: {change.quarters}, Dimes: {change.dimes}, Nickels: {change.nickels}, Pennies: {change.pennies}");
    }

    public static (int dollars, int quarters, int dimes, int nickels, int pennies) CalculateChange(int totalCents)
    {
        // TODO: Implement logic to calculate change
        return (0, 0, 0, 0, 0);
    }
}
