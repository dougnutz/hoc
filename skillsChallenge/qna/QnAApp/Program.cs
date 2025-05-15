using System;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;

class Program
{
    static async Task<string> GetRandomQuestionAsync()
    {
        var assembly = Assembly.GetExecutingAssembly();
        var resourceName = "QnAApp.questions.txt";

        using (Stream stream = assembly.GetManifestResourceStream(resourceName))
        using (StreamReader reader = new StreamReader(stream))
        {
            string[] questions = (await reader.ReadToEndAsync()).Split(new[] { '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);
            Random random = new Random();
            int randomIndex = random.Next(questions.Length);

            Console.WriteLine("Your question is:");
            Console.WriteLine(questions[randomIndex]);

            Console.WriteLine("Press Enter to continue...");
            await Task.Run(() => Console.ReadLine());

            return questions[randomIndex];
        }
    }

    static async Task Main(string[] args)
    {
        try
        {
            await GetRandomQuestionAsync();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error occurred: {ex.Message}");
        }
    }
}
