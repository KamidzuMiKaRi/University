/*

using System;

class RightTriangle
{
    private double a; // Длина первого катета
    private double b; // Длина второго катета

    // Свойства для доступа к длине катетов
    public double A
    {
        get { return a; }
        set
        {
            if (value <= 0)
            {
                throw new ArgumentException("Длина катета должна быть положительным числом.");
            }
            a = value;
        }
    }

    public double B
    {
        get { return b; }
        set
        {
            if (value <= 0)
            {
                throw new ArgumentException("Длина катета должна быть положительным числом.");
            }
            b = value;
        }
    }

    // Конструктор без параметров (по умолчанию)
    public RightTriangle()
    {
        a = 1;
        b = 1;
    }

    // Конструктор с параметрами
    public RightTriangle(double a, double b)
    {
        A = a; // Используем свойство для проверки значения
        B = b; // Используем свойство для проверки значения
    }

    // Метод для вычисления площади треугольника
    public double CalculateArea()
    {
        return 0.5 * a * b;
    }

    // Перегрузка метода ToString() для вывода информации о треугольнике
    public override string ToString()
    {
        return $"Катет a: {a}, Катет b: {b}, Площадь: {CalculateArea()}";
    }

    // Унарные операции
    // Увеличение сторон треугольника в 2 раза
    public static RightTriangle operator ++(RightTriangle triangle)
    {
        return new RightTriangle(triangle.a * 2, triangle.b * 2);
    }

    // Уменьшение сторон треугольника в 2 раза
    public static RightTriangle operator --(RightTriangle triangle)
    {
        return new RightTriangle(triangle.a / 2, triangle.b / 2);
    }

    // Явное приведение типа к double (возвращает площадь треугольника)
    public static explicit operator double(RightTriangle triangle)
    {
        if (triangle)
        {
            return triangle.CalculateArea(); // Если треугольник существует
        }
        else
        {
            return -1; // Возвращаем отрицательное число, если треугольник не существует
        }
    }

    // Неявное приведение типа к bool (проверяет существование треугольника)
    public static implicit operator bool(RightTriangle triangle)
    {
        return triangle.a > 0 && triangle.b > 0; // Треугольник существует, если оба катета > 0
    }

    // Бинарные операции
    // Сравнение площадей треугольников (<=)
    public static bool operator <=(RightTriangle t1, RightTriangle t2)
    {
        return t1.CalculateArea() <= t2.CalculateArea();
    }

    // Сравнение площадей треугольников (>=)
    public static bool operator >=(RightTriangle t1, RightTriangle t2)
    {
        return t1.CalculateArea() >= t2.CalculateArea();
    }
}
class Program
{
    static void Main(string[] args)
    {
        try
        {
            // Тестирование унарных операций (++ и --)
            Console.WriteLine("Создание треугольника с помощью конструктора без параметров...");
            RightTriangle triangle1 = new RightTriangle();
            Console.WriteLine(triangle1.ToString());

            // Увеличение сторон треугольника в 2 раза
            Console.WriteLine("Увеличение сторон треугольника в 2 раза (++):");
            triangle1++;
            Console.WriteLine(triangle1.ToString());

            // Уменьшение сторон треугольника в 2 раза
            Console.WriteLine("Уменьшение сторон треугольника в 2 раза (--):");
            triangle1--;
            Console.WriteLine(triangle1.ToString());

            // Тестирование операций приведения типа (double и bool)
            Console.WriteLine("Создание треугольника с помощью конструктора с параметрами (3, 4)...");
            RightTriangle triangle2 = new RightTriangle(3, 4);
            Console.WriteLine(triangle2.ToString());
            // Явное приведение к double возвращает площадь треугольника
            double area = (double)triangle2;
            Console.WriteLine($"Площадь треугольника (double): {area}");

            // Неявное приведение к bool проверяет существование треугольника
            bool exists = triangle2;
            Console.WriteLine($"Треугольник существует (bool): {exists}");

            // Тестирование бинарных операций (<= и >=)
            Console.WriteLine("Создание треугольника с помощью конструктора с параметрами (2, 3)...");
            RightTriangle triangle3 = new RightTriangle(2, 3);
            Console.WriteLine(triangle3.ToString());

            // Сравнение площадей треугольников
            bool lessThanOrEqual = triangle3 <= triangle2;
            bool greaterThanOrEqual = triangle3 >= triangle2;
            Console.WriteLine($"Площадь первого треугольника <= Площади второго треугольника: {lessThanOrEqual}");
            Console.WriteLine($"Площадь первого треугольника >= Площади второго треугольника: {greaterThanOrEqual}");
        }
        catch (Exception ex)
        {
            // Обработка исключений
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        // Ожидание ввода для предотвращения мгновенного закрытия консоли
        Console.WriteLine("\nНажмите любую клавишу для завершения...");
        Console.ReadKey();
    }
}

*/

using System;

namespace RightTriangleApp
{
    // Класс RightTriangle, представляющий прямоугольный треугольник
    class RightTriangle
    {
        // Поля для сторон (катетов)
        private double a;
        private double b;

        // Свойства для доступа к сторонам (катетам)
        public double A
        {
            get { return a; }
            set
            {
                // Проверка на корректность введенных данных
                if (value <= 0)
                {
                    throw new ArgumentException("Длина катета должна быть положительным числом.");
                }
                a = value;
            }
        }

        public double B
        {
            get { return b; }
            set
            {
                // Проверка на корректность введенных данных
                if (value <= 0)
                {
                    throw new ArgumentException("Длина катета должна быть положительным числом.");
                }
                b = value;
            }
        }

        // Конструктор без параметров. Значения по умолчанию
        public RightTriangle()
        {
            a = 1;
            b = 1;
        }

        // Конструктор с параметрами
        public RightTriangle(double a, double b)
        {
            A = a;
            B = b;
        }

        // Метод для вычисления площади треугольника
        public double CalculateArea()
        {
            return 0.5 * a * b;
        }

        // Переопределение метода ToString() для вывода информации о треугольнике
        public override string ToString()
        {
            return $"Катет a: {a}, Катет b: {b}, Площадь: {CalculateArea()}";
        }


        // Унарные операции
        // Увеличение сторон треугольника в 2 раза
        public static RightTriangle operator ++(RightTriangle triangle)
        {
            return new RightTriangle(triangle.a * 2, triangle.b * 2);
        }

        // Уменьшение сторон треугольника в 2 раза
        public static RightTriangle operator --(RightTriangle triangle)
        {
            return new RightTriangle(triangle.a / 2, triangle.b / 2);
        }

        // Явное приведение типа к double (возвращает площадь треугольника)
        public static explicit operator double(RightTriangle triangle)
        {
            if (triangle)
            {
                return triangle.CalculateArea(); // Если треугольник существует
            }
            else
            {
                return -1; // Возвращаем отрицательное число, если треугольник не существует
            }
        }

        // Неявное приведение типа к bool (проверяет существование треугольника)
        public static implicit operator bool(RightTriangle triangle)
        {
            return triangle.a > 0 && triangle.b > 0; // Треугольник существует, если оба катета > 0
        }

        // Бинарные операции
        // Сравнение площадей треугольников (<=)
        public static bool operator <=(RightTriangle t1, RightTriangle t2)
        {
            return t1.CalculateArea() <= t2.CalculateArea();
        }

        // Сравнение площадей треугольников (>=)
        public static bool operator >=(RightTriangle t1, RightTriangle t2)
        {
            return t1.CalculateArea() >= t2.CalculateArea();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // Тестирование унарных операций (++ и --)
                Console.WriteLine("Создание треугольника с помощью конструктора без параметров...");
                RightTriangle triangle1 = new RightTriangle();
                Console.WriteLine(triangle1.ToString());

                // Увеличение сторон треугольника в 2 раза
                Console.WriteLine("Увеличение сторон треугольника в 2 раза (++):");
                triangle1++;
                Console.WriteLine(triangle1.ToString());

                // Уменьшение сторон треугольника в 2 раза
                Console.WriteLine("Уменьшение сторон треугольника в 2 раза (--):");
                triangle1--;
                Console.WriteLine(triangle1.ToString());

                // Тестирование операций приведения типа (double и bool)
                Console.WriteLine("Создание треугольника с помощью конструктора с параметрами (3, 4)...");
                RightTriangle triangle2 = new RightTriangle(3, 4);
                Console.WriteLine(triangle2.ToString());

                // Явное приведение к double возвращает площадь треугольника
                double area = (double)triangle2;
                Console.WriteLine($"Площадь треугольника (double): {area}");

                // Неявное приведение к bool проверяет существование треугольника
                bool exists = triangle2;
                Console.WriteLine($"Треугольник существует (bool): {exists}");

                // Тестирование бинарных операций (<= и >=)
                Console.WriteLine("Создание треугольника с помощью конструктора с параметрами (2, 3)...");
                RightTriangle triangle3 = new RightTriangle(2, 3);
                Console.WriteLine(triangle3.ToString());

                // Сравнение площадей треугольников
                bool lessThanOrEqual = triangle3 <= triangle2;
                bool greaterThanOrEqual = triangle3 >= triangle2;
                Console.WriteLine($"Площадь первого треугольника <= Площади второго треугольника: {lessThanOrEqual}");
                Console.WriteLine($"Площадь первого треугольника >= Площади второго треугольника: {greaterThanOrEqual}");



                // Тестирование конструкторов и методов
                Console.WriteLine("Создание треугольника с помощью конструктора без параметров...");
                RightTriangle triangle4 = new RightTriangle();
                Console.WriteLine(triangle1.ToString());

                Console.WriteLine("\nСоздание треугольника с помощью конструктора с параметрами (3, 4)...");
                RightTriangle triangle5 = new RightTriangle(3, 4);
                Console.WriteLine(triangle2.ToString());

                double a = 0;
                double b = 0;

                // Цикл для повторного запроса ввода при некорректных значениях
                while (true)
                {
                    try
                    {
                        Console.WriteLine("\nВведите длину катета a:");
                        a = Convert.ToDouble(Console.ReadLine());
                        if (a <= 0)
                        {
                            throw new ArgumentException("Длина катета должна быть положительным числом.");
                        }
                        break;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Ошибка: {ex.Message}. Попробуйте еще раз.");
                    }
                }

                while (true)
                {
                    try
                    {
                        Console.WriteLine("Введите длину катета b:");
                        b = Convert.ToDouble(Console.ReadLine());
                        if (b <= 0)
                        {
                            throw new ArgumentException("Длина катета должна быть положительным числом.");
                        }
                        break;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Ошибка: {ex.Message}. Попробуйте еще раз.");
                    }
                }

                RightTriangle triangle6 = new RightTriangle(a, b);
                Console.WriteLine(triangle3.ToString());
            }
            catch (Exception ex)
            {
                // Обработка исключений и вывод сообщения об ошибке
                Console.WriteLine($"Ошибка: {ex.Message}");
            }
            // Ожидание ввода для предотвращения мгновенного закрытия консоли
            Console.WriteLine("\nНажмите любую клавишу для завершения...");
            Console.ReadKey();
        }
    }
}