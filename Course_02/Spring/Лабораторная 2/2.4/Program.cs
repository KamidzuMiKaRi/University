/*
using System;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        string filePath = "data.bin";

        int numberOfElements;
        int n;

        while (true)
        {
            Console.Write("Введите количество случайных чисел для генерации (должно быть полным квадратом): ");
            while (!int.TryParse(Console.ReadLine(), out numberOfElements) || numberOfElements <= 0)
            {
                Console.Write("Пожалуйста, введите положительное целое число: ");
            }

            // Придание размеру решетки матрицы значения равного квадратному корню из числа введенных элементов
            n = (int)Math.Sqrt(numberOfElements);

            if (n * n < numberOfElements)
            {
                n++;
                break;
            }
            else if (n * n <= numberOfElements)
                    {
                        break;
                    }
            else
            {
                Console.WriteLine("Количество элементов должно быть полным квадратом. Попробуйте снова.");
            }
        }

        // Заполнение файла случайными данными
        FillFileWithRandomData(filePath, numberOfElements);

        // Подсчет пар противоположных чисел
        int oppositePairsCount = CountOppositePairs(filePath);
        Console.WriteLine($"Количество пар противоположных чисел: {oppositePairsCount}");

        int[,] matrix = new int[n, n];

        // Копирование данных из файла в квадратную матрицу и модификация матрицы
        CopyDataToMatrix(filePath, matrix, n);
        // Печать итоговой матрицы
        Console.WriteLine($"Оригинальная матрица:\t");
        PrintMatrix(matrix, n);

        Console.WriteLine($"Обновленная матрица:\t");
        ReplaceColumnWithMax(matrix, n);
        PrintMatrix(matrix, n);

        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }

    // Метод заполнения файла случайными данными
    static void FillFileWithRandomData(string filePath, int count)
    {
        Random random = new Random();
        using (BinaryWriter writer = new BinaryWriter(File.Open(filePath, FileMode.Create)))
        {
            for (int i = 0; i < count; i++)
            {
                writer.Write(random.Next(-100, 101)); // Записывает случайное число от -100 до 100
            }
        }
    }

    // Метод подсчета количества пар противоположных чисел в файле
    static int CountOppositePairs(string filePath)
    {
        int count = 0;
        int[] data;
        using (BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open)))
        {
            int dataSize = (int)reader.BaseStream.Length / sizeof(int);
            data = new int[dataSize];
            for (int i = 0; i < dataSize; i++)
            {
                data[i] = reader.ReadInt32();
            }
        }

        for (int i = 0; i < data.Length; i++)
        {
            for (int j = i + 1; j < data.Length; j++)
            {
                if (data[i] == -data[j])
                {
                    count++;
                }
            }
        }
        return count;
    }

    // Метод копирования данных из файла в квадратную матрицу
    static void CopyDataToMatrix(string filePath, int[,] matrix, int n)
    {
        using (BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open)))
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (reader.BaseStream.Position < reader.BaseStream.Length)
                    {
                        matrix[i, j] = reader.ReadInt32();
                    }
                    else
                    {
                        matrix[i, j] = 0; // Заполняем нулями, если данных не хватает
                    }
                }
            }
        }
    }

    // Метод замены элементов столбцов на максимальные значения в столбцах
    static void ReplaceColumnWithMax(int[,] matrix, int n)
    {
        for (int j = 0; j < n; j++)
        {

            int max = matrix[0, j];
            for (int i = 1; i < n; i++)
            {
                if (matrix[i, j] > max)
                {
                    max = matrix[i, j];
                }
            }
            for (int i = 0; i < n; i++)
            {
                matrix[i, j] = max;
            }
        }
    }

    // Метод печати матрицы
    static void PrintMatrix(int[,] matrix, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Console.Write(matrix[i, j] + "\t");
            }
            Console.WriteLine();
        }
    }
}
*/

using System;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        string filePath = "data.bin";
        int numberOfElements;
        int n;

        // Цикл создания матрицы под набор чисел
        while (true)
        {
            Console.Write("Введите количество случайных чисел для генерации (должно быть полным квадратом): ");
            while (!int.TryParse(Console.ReadLine(), out numberOfElements) || numberOfElements <= 0)
            {
                Console.Write("Пожалуйста, введите положительное целое число: ");
            }

            n = (int)Math.Sqrt(numberOfElements);

            if (n * n < numberOfElements)
            {
                n++;
            }
            if (n * n >= numberOfElements)
            {
                break;
            }
        }

        // Заполнение файла случайными данными
        FillFileWithRandomData(filePath, numberOfElements);

        // Подсчет пар противоположных чисел
        int oppositePairsCount = CountOppositePairs(filePath);
        Console.WriteLine($"Количество пар противоположных чисел: {oppositePairsCount}");

        int[,] matrix = new int[n, n];

        // Копирование данных из файла в квадратную матрицу
        CopyDataToMatrix(filePath, matrix, n);
        // Печать стартовой матрицы
        Console.WriteLine($"Оригинальная матрица:\t");
        PrintMatrix(matrix, n);
        // Модификация матрицы
        ReplaceColumnWithMax(matrix, n);
        // Печать итоговой матрицы
        Console.WriteLine($"Обновленная матрица:\t");
        PrintMatrix(matrix, n);
        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }

    // Метод заполнения файла случайными данными
    private static void FillFileWithRandomData(string filePath, int count)
    {
        Random random = new Random();
        using (BinaryWriter writer = new BinaryWriter(File.Open(filePath, FileMode.Create)))
        {
            for (int i = 0; i < count; i++)
            {
                writer.Write(random.Next(-100, 101)); // Записывает случайное число от -100 до 100
            }
        }
    }

    // Метод подсчета количества пар противоположных чисел в файле
    private static int CountOppositePairs(string filePath)
    {
        int count = 0;
        int[] data;
        using (BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open)))
        {
            int dataSize = (int)reader.BaseStream.Length / sizeof(int);
            data = new int[dataSize];
            for (int i = 0; i < dataSize; i++)
            {
                data[i] = reader.ReadInt32();
            }
        }

        for (int i = 0; i < data.Length; i++)
        {
            for (int j = i + 1; j < data.Length; j++)
            {
                if (data[i] == -data[j])
                {
                    count++;
                }
            }
        }
        return count;
    }

    // Метод копирования данных из файла в квадратную матрицу
    private static void CopyDataToMatrix(string filePath, int[,] matrix, int n)
    {
        using (BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open)))
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (reader.BaseStream.Position < reader.BaseStream.Length)
                    {
                        matrix[i, j] = reader.ReadInt32();
                    }
                    else
                    {
                        matrix[i, j] = 0; // Заполняем нулями, если данных не хватает
                    }
                }
            }
        }
    }

    // Метод замены элементов столбцов на максимальные значения в столбцах
    private static void ReplaceColumnWithMax(int[,] matrix, int n)
    {
        for (int j = 0; j < n; j++)
        {
            int max = matrix[0, j];
            for (int i = 1; i < n; i++)
            {
                if (matrix[i, j] > max)
                {
                    max = matrix[i, j];
                }
            }
            for (int i = 0; i < n; i++)
            {
                matrix[i, j] = max;
            }
        }
    }

    // Метод печати матрицы
    private static void PrintMatrix(int[,] matrix, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Console.Write(matrix[i, j] + "\t");
            }
            Console.WriteLine();
        }
    }
}