using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public static class DataGenerator
{
    // Пример списка фамилий
    static readonly string[] LastNames = {
        "Иванов", "Смирнов", "Кузнецов", "Попов", "Васильев",
        "Петров", "Соколов", "Михайлов", "Новиков", "Федоров",
        "Морозов", "Волков", "Алексеев", "Лебедев", "Семенов"
    };

    // Пример списка имен
    static readonly string[] FirstNames = {
        "Александр", "Максим", "Иван", "Артем", "Дмитрий",
        "Никита", "Михаил", "Кирилл", "Андрей", "Алексей",
        "Сергей", "Илья", "Егор", "Владислав", "Роман"
    };

    public static List<string> GenerateList(int count)
    {
        var random = new Random();
        var list = new List<string>();

        for (int i = 0; i < count; i++)
        {
            // Генерация случайной фамилии и имени
            var lastName = LastNames[random.Next(LastNames.Length)];
            var firstName = FirstNames[random.Next(FirstNames.Length)];

            // Генерация случайных баллов от 0 до 100
            var score1 = random.Next(101);
            var score2 = random.Next(101);

            // Форматирование строки
            var line = $"{lastName} {firstName} {score1} {score2}";
            list.Add(line);
        }

        return list;
    }

    public static void WriteToFile(string filePath, List<string> list)
    {
        // Записываем данные в файл
        File.WriteAllLines(filePath, list);
    }

    public static void Main()
    {
        // Генерируем список из 500 строк
        var generatedList = GenerateList(500);

        // Записываем список в файл (укажите ваш путь)
        string filePath = "E:\\TEST\\last\\abit.txt";
        WriteToFile(filePath, generatedList);

        // Выводим первые 10 строк для проверки
        foreach (var line in generatedList.Take(10))
        {
            Console.WriteLine(line);
        }

    }
}