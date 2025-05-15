using System;
using System.IO;
using Xunit;

namespace QnAApp.Tests;

public class QnAAppTests
{
    [Fact]
    public void TestQuestionsFileExists()
    {
        string questionsFilePath = Path.Combine(Directory.GetParent(AppContext.BaseDirectory).Parent.Parent.FullName, "QnAApp", "questions.txt");
        Assert.True(File.Exists(questionsFilePath), "Questions file should exist.");
    }

    [Fact]
    public void TestRandomQuestionSelection()
    {
        string questionsFilePath = Path.Combine(Directory.GetParent(AppContext.BaseDirectory).Parent.Parent.FullName, "QnAApp", "questions.txt");
        string[] questions = File.ReadAllLines(questionsFilePath);

        Assert.NotEmpty(questions);

        Random random = new Random();
        int randomIndex = random.Next(questions.Length);

        Assert.InRange(randomIndex, 0, questions.Length - 1);
        Assert.False(string.IsNullOrWhiteSpace(questions[randomIndex]), "Selected question should not be null or whitespace.");
    }
}