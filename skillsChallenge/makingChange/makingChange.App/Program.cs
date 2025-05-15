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
        int dollars = 0;
        int quarters = 0;
        int dimes = 0;
        int nickels = 0;
        int pennies = 0;
        dollars = totalCents / 100;
        totalCents %= 100;

        quarters = totalCents / 25;
        totalCents %= 25;

        dimes = totalCents / 10;
        totalCents %= 10;

        nickels = totalCents / 5;
        totalCents %= 5;

        pennies = totalCents;

       return (dollars, quarters, dimes, nickels, pennies);
    }
}
