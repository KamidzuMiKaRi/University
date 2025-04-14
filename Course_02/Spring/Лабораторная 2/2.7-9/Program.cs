using System;
using System.IO;
using System.Linq;

// Класс TextFileOperations содержит статические методы для выполнения задач
public static class TextFileOperations
{
    // Метод для проверки наличия нуля в файле
    public static bool CheckIfFileContainsZero(string filePath)
    {
        try
        {
            // Считывание всех строк из файла
            var lines = File.ReadAllLines(filePath);

            // Проход по каждой строке и проверка наличия нуля
            foreach (var line in lines)
            {
                if (int.TryParse(line, out int number) && number == 0)
                {
                    return false; // Если найден ноль, возвращаем false
                }
            }

            return true; // Если ноль не найден, возвращаем true
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
            return false;
        }
    }

    // Метод для поиска максимального элемента в файле, содержащем целые числа по несколько в строке
    public static int FindMaxElementInFile(string filePath)
    {
        try
        {
            // Считывание всех строк из файла
            var lines = File.ReadAllLines(filePath);

            // Преобразование строк в массив целых чисел и нахождение максимального значения
            int maxElement = lines
                .SelectMany(line => line.Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries))
                .Select(int.Parse)
                .Max();

            return maxElement;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
            return int.MinValue;
        }
    }

    // Метод для переписывания строк, оканчивающихся на заданный символ, в другой файл
    public static void CopyLinesEndingWithChar(string inputFilePath, string outputFilePath, char endingChar)
    {
        try
        {
            // Считывание всех строк из входного файла
            var lines = File.ReadAllLines(inputFilePath);

            // Фильтрация строк, оканчивающихся на заданный символ
            var filteredLines = lines.Where(line => line.EndsWith(endingChar.ToString()));

            // Запись отфильтрованных строк в выходной файл
            File.WriteAllLines(outputFilePath, filteredLines);

            Console.WriteLine("Переписывание завершено успешно.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
        }
    }

    // Основной метод программы для демонстрации работы вышеописанных методов
    public static void Main(string[] args)
    {
        // Ввод пути к файлу с числами по одному в строке и проверка на наличие нуля
        Console.WriteLine("Введите путь к файлу с числами по одному в строке:");
        string singleNumbersFilePath = Console.ReadLine();
        bool containsZero = CheckIfFileContainsZero(singleNumbersFilePath);
        Console.WriteLine($"Файл {(containsZero ? "не содержит" : "содержит")} ноль.");

        // Ввод пути к файлу с числами по несколько в строке и нахождение максимального элемента
        Console.WriteLine("Введите путь к файлу с числами по несколько в строке:");
        string multiNumbersFilePath = Console.ReadLine();
        int maxElement = FindMaxElementInFile(multiNumbersFilePath);
        Console.WriteLine($"Максимальный элемент в файле: {maxElement}");

        // Ввод пути к входному файлу, выходному файлу и символу для переписывания строк
        Console.WriteLine("Введите путь к входному файлу с текстом:");
        string inputFilePath = Console.ReadLine();
        Console.WriteLine("Введите путь к выходному файлу:");
        string outputFilePath = Console.ReadLine();
        Console.WriteLine("Введите символ, на который должны оканчиваться строки:");
        char endingChar = Console.ReadKey().KeyChar;
        Console.WriteLine();

        // Переписывание строк, оканчивающихся на заданный символ, в другой файл
        CopyLinesEndingWithChar(inputFilePath, outputFilePath, endingChar);
        
        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }
}
