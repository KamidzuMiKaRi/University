using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Serialization;

[Serializable]
public struct BaggageItem
{
    public string Name { get; set; }
    public double Weight { get; set; }
}

[Serializable]
public class Passenger
{
    public BaggageItem[] Baggage { get; set; }
}

public class Program
{
    public static void Main(string[] args)
    {
        string filePath = "baggage.xml";

        // Заполняем XML файл данными о багаже
        FillBaggageFile(filePath);

        // Вычисляем разницу между максимальной и минимальной массой багажа
        double difference = CalculateMaxMinDifference(filePath);

        Console.WriteLine($"Разница между самым тяжелым и самым легким багажом составляет: {difference} кг");

        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }

    public static void FillBaggageFile(string filePath)
    {
        // Создаем примерный список пассажиров с багажом
        var passengers = new List<Passenger>
        {
            new Passenger
            {
                Baggage = new BaggageItem[]
                {
                    new BaggageItem { Name = "Чемодан", Weight = 23.5 },
                    new BaggageItem { Name = "Сумка", Weight = 10.2 }
                }
            },
            new Passenger
            {
                Baggage = new BaggageItem[]
                {
                    new BaggageItem { Name = "Коробка", Weight = 12.3 },
                    new BaggageItem { Name = "Рюкзак", Weight = 8.1 }
                }
            },
            // Добавьте больше пассажиров при необходимости
        };

        // Сериализация списка пассажиров в XML файл
        XmlSerializer serializer = new XmlSerializer(typeof(List<Passenger>));
        using (TextWriter writer = new StreamWriter(filePath))
        {
            serializer.Serialize(writer, passengers);
        }
    }

    public static double CalculateMaxMinDifference(string filePath)
    {
        // Десериализация данных из XML файла
        List<Passenger> passengers;
        XmlSerializer serializer = new XmlSerializer(typeof(List<Passenger>));
        using (FileStream fs = new FileStream(filePath, FileMode.Open))
        {
            passengers = (List<Passenger>)serializer.Deserialize(fs);
        }

        // Список всех масс багажа, собранных у всех пассажиров
        var allWeights = passengers.SelectMany(p => p.Baggage).Select(b => b.Weight).ToList();

        // Вычисляем максимальную и минимальную массу багажа
        double maxWeight = allWeights.Max();
        double minWeight = allWeights.Min();

        // Возвращаем разницу между максимальной и минимальной массой
        return maxWeight - minWeight;
    }
}
