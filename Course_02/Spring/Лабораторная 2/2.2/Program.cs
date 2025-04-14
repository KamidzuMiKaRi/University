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
    }

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // Тестирование конструкторов и методов
                Console.WriteLine("Создание треугольника с помощью конструктора без параметров...");
                RightTriangle triangle1 = new RightTriangle();
                Console.WriteLine(triangle1.ToString());

                Console.WriteLine("\nСоздание треугольника с помощью конструктора с параметрами (3, 4)...");
                RightTriangle triangle2 = new RightTriangle(3, 4);
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

                RightTriangle triangle3 = new RightTriangle(a, b);
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