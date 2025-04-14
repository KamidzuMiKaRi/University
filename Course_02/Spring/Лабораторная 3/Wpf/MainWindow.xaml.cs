using System;
using System.Windows;
using RightTriangleApp;

namespace RightTriangleAppWPF
{
    public partial class MainWindow : Window
    {
        private RightTriangle _triangle;

        private void CreateTriangle_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double a = Convert.ToDouble(TextboxA.Text);
                double b = Convert.ToDouble(TextboxB.Text);
                _triangle = new RightTriangle(a, b);
                TriangleInfo.Text = _triangle.ToString();
            }
            catch (FormatException)
            {
                MessageBox.Show("Пожалуйста, введите корректные числовые значения для катетов.", "Ошибка ввода", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show(ex.Message, "Ошибка ввода", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }

        private void IncreaseTriangle_Click(object sender, RoutedEventArgs e)
        {
            if (_triangle == null)
            {
                MessageBox.Show("Сначала создайте треугольник.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            _triangle++;
            TriangleInfo.Text = _triangle.ToString();
        }

        private void DecreaseTriangle_Click(object sender, RoutedEventArgs e)
        {
            if (_triangle == null)
            {

                MessageBox.Show("Сначала создайте треугольник.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            _triangle--;
            TriangleInfo.Text = _triangle.ToString();
        }

        private void ShowArea_Click(object sender, RoutedEventArgs e)
        {
            if (_triangle == null)
            {
                MessageBox.Show("Сначала создайте треугольник.", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            double area = (double)_triangle;
            MessageBox.Show($"Площадь треугольника: {area}", "Площадь треугольника", MessageBoxButton.OK, MessageBoxImage.Information);
        }
    }
}
