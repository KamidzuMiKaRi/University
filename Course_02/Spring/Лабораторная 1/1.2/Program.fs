open System

// Функция для проверки, является ли введенное значение числом и натуральным числом, путем перегонки его из строки в int32. Проверка, что оно и перегналось и больше 0
let isNaturalNumber (input: string) =
    let parsed, number = Int32.TryParse(input)
    parsed && number > 0

// Рекурсивная функция для нахождения максимальной цифры в числе
let rec findMaxDigit (n: int) =
    if n < 10 then 
        n // Если число состоит из одной цифры, возвращаем эту цифру
    else 
        let digit = n % 10 // Извлекаем последнюю цифру из числа
        let remainingNumber = n / 10 // Уменьшаем число, отбрасывая последнюю цифру
        let maxOfRes = findMaxDigit remainingNumber // Рекурсивно находим максимальную цифру в оставшемся числе
        if digit > maxOfRes then digit else maxOfRes // Сравниваем текущую цифру и максимальную цифру во "хвосте" числа

// Основная функция
let rec main () =
   Console.WriteLine ("Введите натуральное число: ")
   let userInput = Console.ReadLine()

   if isNaturalNumber userInput then // Проверяем, является ли введенное значение натуральным числом
        let number = Int32.Parse(userInput) // Преобразуем строку в число
        let maxDigit = findMaxDigit number // Найдем максимальную цифру в числе
        Console.WriteLine ("Максимальная цифра в числе {0}: {1}", number, maxDigit)
   else
      Console.WriteLine ("Введено некорректное значение или число не является натуральным. Попытайтесь ещё")
      main()

// Вызов основной функции
main ()