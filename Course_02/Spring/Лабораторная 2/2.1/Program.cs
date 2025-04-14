using System;
using System.Linq;

// Основной класс с тремя целочисленными полями
public class MyClass
{
    // Приватные поля класса
    protected int field1;
    protected int field2;
    protected int field3;

    // Конструктор с параметрами
    public MyClass(int field1, int field2, int field3)
    {
        this.field1 = field1;
        this.field2 = field2;
        this.field3 = field3;
    }

    // Конструктор копирования
    public MyClass(MyClass other)
    {
        this.field1 = other.field1;
        this.field2 = other.field2;
        this.field3 = other.field3;
    }

    // Метод для поиска минимального значения среди полей
    public int MinField()
    {
        return Math.Min(field1, Math.Min(field2, field3));
    }

    // Переопределение метода ToString для удобного вывода значений полей
    public override string ToString()
    {
        return $"Поле1: {field1}, Поле2: {field2}, Поле3: {field3}";
    }
}

// Дочерний класс с дополнительными функциональностями
public class ExtendedClass : MyClass
{
    private string extraInfo;

    // Конструктор с параметрами
    public ExtendedClass(int field1, int field2, int field3, string extraInfo)
        : base(field1, field2, field3)
    {
        this.extraInfo = extraInfo;
    }

    // Конструктор копирования
    public ExtendedClass(ExtendedClass other)
        : base(other)
    {
        this.extraInfo = other.extraInfo;
    }

    // Метод для объединения трех полей в одну строку по возрастанию значений
    public string ConcatenateFields()
    {
        int[] fields = { field1, field2, field3 };
        Array.Sort(fields);
        return string.Join(",", fields);
    }

    // Метод для объединения трех полей в одну строку в порядке убывания значений
    public string ConcatenateFieldsReversed()
    {
        int[] fields = { field1, field2, field3 };
        Array.Sort(fields);
        Array.Reverse(fields);
        return string.Join(",", fields);
    }

    // Переопределение метода ToString, чтобы включить дополнительную информацию
    public override string ToString()
    {
        return base.ToString() + $", Дополнительная информация: {extraInfo}";
    }
}

// Тестирование классов
public class Program
{
    public static void Main()
    {
        // Тест базового класса MyClass
        MyClass obj1 = new MyClass(20, 15, 30);
        Console.WriteLine("Объект MyClass:");
        Console.WriteLine(obj1);
        Console.WriteLine($"Минимальное значение поля: {obj1.MinField()}");

        MyClass obj2 = new MyClass(obj1);
        Console.WriteLine("Скопированный объект MyClass:");
        Console.WriteLine(obj2);

        // Тест дочернего класса ExtendedClass
        ExtendedClass extObj1 = new ExtendedClass(30, 25, 40, "Это дочерний класс");
        Console.WriteLine("\nОбъект ExtendedClass:");
        Console.WriteLine(extObj1);
        Console.WriteLine("Объединенные поля по возрастанию: " + extObj1.ConcatenateFields());
        Console.WriteLine("Объединенные поля по убыванию: " + extObj1.ConcatenateFieldsReversed());

        ExtendedClass extObj2 = new ExtendedClass(extObj1);
        Console.WriteLine("Скопированный объект ExtendedClass:");
        Console.WriteLine(extObj2);

        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }
}