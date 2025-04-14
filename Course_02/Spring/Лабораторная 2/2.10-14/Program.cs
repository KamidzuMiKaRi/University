using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public static class Tasks
{
    // Метод для задачи 10
    // Удаляет из списка элемент, следующий за каждым вхождением элемента E, если он отличен от E
    public static void RemoveAfterEachE(List<int> list, int E)
    {
        for (int i = 0; i < list.Count - 1; i++)
        {
            if (list[i] == E && list[i + 1] != E)
            {
                list.RemoveAt(i + 1);
            }
        }
    }

    // Метод для задачи 11
    // Определяет, есть ли в связанном списке элементы, которые равны следующему за ними элементу по кругу
    public static bool HasEqualAdjacentElements(LinkedList<int> list)
    {
        if (list.Count == 0)
            return false;

        LinkedListNode<int> current = list.First;
        do
        {
            // Следующий элемент - либо следующий узел, либо первый узел в случае последнего элемента списка
            LinkedListNode<int> next = (current.Next != null) ? current.Next : list.First;
            if (current.Value == next.Value)
            {
                return true;
            }
            current = current.Next;
        }
        while (current != null);

        return false;
    }

    // Метод для задачи 12
    // Анализирует перечень стран, которые посещаются туристами, и определяет, какие страны были посещены всеми, некоторыми или никем
    public static void AnalyzeTouristCountries(List<HashSet<string>> touristsCountries, HashSet<string> comparisonCountries)
    {
        var allCountries = new HashSet<string>(comparisonCountries); // Используем только страны из comparisonCountries

        var visitedByAll = new HashSet<string>(allCountries); // Изначально содержит все страны из comparisonCountries
        var visitedBySome = new HashSet<string>();
        var visitedByNone = new HashSet<string>(allCountries); // Изначально содержит все страны из comparisonCountries

        foreach (var country in allCountries)
        {
            int count = touristsCountries.Count(tc => tc.Contains(country));
            if (count == touristsCountries.Count)
            {
                // Посещены всеми туристами
                visitedByAll.Add(country);
                // Удаляем из не посещенных, так как если страна посещена всеми, то она не может быть не посещенной
                visitedByNone.Remove(country);
            }
            else if (count > 0)
            {
                // Посещены некоторыми туристами
                visitedByAll.Remove(country); // Убираем из посещенных всеми, т.к. она не посещена всеми
                visitedBySome.Add(country);
                // Удаляем из не посещенных, так как если страна посещена хотя бы одним, то она не может быть не посещенной
                visitedByNone.Remove(country);
            }
            else
            {
                // Страна не была посещена никем, она остается в visitedByNone
                visitedByAll.Remove(country); // Убираем из посещенных всеми, т.к. она не посещена никем
            }
        }

        Console.WriteLine("Посещены всеми туристами:");
        Console.WriteLine(string.Join(", ", visitedByAll));

        Console.WriteLine("Посещены некоторыми туристами:");
        Console.WriteLine(string.Join(", ", visitedBySome));

        Console.WriteLine("Никем не посещены:");
        Console.WriteLine(string.Join(", ", visitedByNone));
    }


    // Метод для задачи 13
    // Обрабатывает текстовый файл и печатает все глухие согласные, которые не входят ровно в одно слово
    public static void PrintDeafConsonantsInTextFile(string filePath)
    {
        try
        {
            // Множество глухих согласных
            var deafConsonants = new HashSet<char> { 'п', 'ф', 'к', 'т', 'ш', 'с', 'х', 'ц', 'ч' };
            var usedDeafConsonants = new HashSet<char>(); // Все глухие согласные, которые появляются в тексте
            var wordsDeafConsonants = new HashSet<char>(); // Глухие согласные, которые встречаются в словах и являются единственными глухими согласными в этих словах

            // Чтение строк из файла
            var lines = File.ReadLines(filePath);
            foreach (var line in lines)
            {
                // Разделение строки на слова
                var words = line.Split(new[] { ' ', '\t', ',', '.', '!', '?' }, StringSplitOptions.RemoveEmptyEntries);

                foreach (var word in words)
                {
                    var encounteredConsonants = new HashSet<char>();
                    foreach (var ch in word)
                    {
                        if (deafConsonants.Contains(ch))
                        {
                            usedDeafConsonants.Add(ch);
                            encounteredConsonants.Add(ch);
                        }
                    }

                    if (encounteredConsonants.Count == 1)
                    {
                        foreach (var consonant in encounteredConsonants)
                        {
                            wordsDeafConsonants.Add(consonant);
                        }
                    }
                }
            }

            var result = new HashSet<char>(usedDeafConsonants);
            result.ExceptWith(wordsDeafConsonants);
            Console.WriteLine("Глухие согласные, которые не входят ровно в одно слово: " + string.Join(", ", result.OrderBy(c => c)));
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
        }
    }

    // Метод для задачи 14
    // Считывает данные о результатах тестирования и выводит список абитуриентов, не допущенных к сдаче экзаменов, в алфавитном порядке
    public static void ListUnqualifiedApplicants(string filePath)
    {
        try
        {
            // Чтение строк из файла. Первая строка содержит количество участников.
            var lines = File.ReadLines(filePath).ToList();
            // Парсим первую строку и узнаем количество участвующих
            int numApplicants = int.Parse(lines.First());

            // Инициализируем словарь для неквалифицированных участников
            var unqualifiedApplicants = new SortedDictionary<string, string>();

            // Обрабатываем каждую строку, содержащую информацию об участниках
            for (int i = 1; i <= numApplicants; i++)
            {
                // Разделяем строку на части: фамилия, имя и баллы
                var parts = lines[i].Split(' ');
                var lastName = parts[0];
                var firstName = parts[1];
                // Преобразуем оставшиеся части в массив баллов
                var scores = parts.Skip(2).Select(int.Parse).ToArray();

                // Проверка баллов на минимальные значения
                if (scores[0] < 30 || scores[1] < 30)
                {
                    // Добавляем неквалифицированного участника в словарь
                    unqualifiedApplicants[lastName] = firstName;
                }
            }

            // Вывод списка неквалифицированных участников в алфавитном порядке
            foreach (var applicant in unqualifiedApplicants)
            {
                Console.WriteLine($"{applicant.Key} {applicant.Value}");
            }
        }
        catch (Exception ex)
        {
            // Обработка ошибок, если они возникнут при чтении файла или другой операции
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        // Пример вызова метода для задачи 1
        Console.WriteLine("Задача 10");
        var list = new List<int> { 1, 2, 3, 2, 4, 2, 5, 6, 2, 1, 5, 3, 7, 1, 2, 4 };
        Tasks.RemoveAfterEachE(list, 2);
        Console.WriteLine("Результат задачи 10: " + string.Join(", ", list));

        // Пример вызова метода для задачи 2
        Console.WriteLine("\nЗадача 11");
        var linkedList = new LinkedList<int>(new[] { 1, 2, 2, 3, 1, 5 });
        bool hasEqual = Tasks.HasEqualAdjacentElements(linkedList);
        Console.WriteLine($"Результат задачи 11: {(hasEqual ? "Есть совпадающие элементы" : "Нет совпадающих элементов")}");

        // Пример вызова метода для задачи 3
        Console.WriteLine("\nЗадача 12");

        var comparisonCountries = new HashSet<string>
        {
            "Россия", "Франция", "Германия", "Бразилия", "Чехия"
        };

        var touristsCountries = new List<HashSet<string>>
        {
            new HashSet<string> {"Россия", "Франция", "Германия", "Чехия"},
            new HashSet<string> {"Россия", "Италия", "Германия"},
            new HashSet<string> {"Россия", "Франция", "Италия"}
        };

        Tasks.AnalyzeTouristCountries(touristsCountries, comparisonCountries);

        // Пример вызова метода для задачи 4
        Console.WriteLine("\nЗадача 13");
        string filePathTask4 = "E:\\TEST\\last\\gluh.txt"; // Укажите путь к файлу
        Tasks.PrintDeafConsonantsInTextFile(filePathTask4);

        // Пример вызова метода для задачи 5
        Console.WriteLine("\nЗадача 14");
        string filePathTask5 = "E:\\TEST\\last\\abit.txt"; // Укажите путь к файлу
        Tasks.ListUnqualifiedApplicants(filePathTask5);

        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }
}
