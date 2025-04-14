open System

// Функция для ввода элементов списка от пользователя с проверкой на соответствие числу
let rec inputNumbers (acc: int list) =
    Console.WriteLine("Введите целое натуральное число (или пустую строку для завершения ввода):")
    let input = Console.ReadLine()
    
    match input.Trim() with
    | "" -> acc  // Если введена пустая строка, возвращаем накопленный список
    | str ->
        match Int32.TryParse(str) with
        | (true, number) -> 
            // Если успешно распарсили число, добавляем его к накопленному списку и рекурсивно продолжаем ввод
            inputNumbers (number :: acc)
        | (false, _) ->
            Console.WriteLine("Некорректный ввод. Пожалуйста, введите целое натрульное число.")
            inputNumbers acc  // Продолжаем ввод, не изменяя накопленный список

// Функция для проверки, содержит ли число заданную цифру
let containsDigit n digit =
    n.ToString().Contains(digit.ToString())

// Функция для нахождения суммы чисел, содержащих заданную цифру
let sumOfNumbersWithDigit numbers digit =
    numbers
    |> Seq.fold (fun acc x -> if containsDigit x digit then acc + x else acc) 0


// Функция для ввода корректной цифры
let rec inputDigit () =
    Console.WriteLine("Введите цифру для поиска (от 0 до 9):")
    let digitInput = Console.ReadLine()
    match Int32.TryParse(digitInput) with
    | (true, digit) when digit >= 0 && digit <= 9 -> digit
    | _ ->
        Console.WriteLine("Некорректный ввод цифры. Попробуйте снова.")
        inputDigit()

// Основная точка входа в программу
[<EntryPoint>]
let main argv =
    // Ввод последовательности чисел
    let numbers = inputNumbers []
    
    // Ввод цифры для поиска
    let digit = inputDigit()
    
    // Вычисление суммы чисел, содержащих введенную цифру
    let sum = sumOfNumbersWithDigit numbers digit
    Console.WriteLine($"Сумма чисел, содержащих цифру {digit}, составляет: {sum}")
    
    // Код завершения
    0