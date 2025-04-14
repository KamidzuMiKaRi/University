open System

// Функция, которая проверяет, содержит ли число заданную цифру
let containsDigit (digit: int) (number: int) =
    // Преобразуем цифру и число в строки для последующего сравнения символов
    let digitAsString = string digit
    let numberAsString = string number
    // Проверяем, содержит ли строковое представление числа символ, соответствующий цифре
    numberAsString |> List.ofSeq |> List.exists (fun c -> c = digitAsString.[0])

// Функция для суммирования элементов списка, в которых встречается заданная цифра
let sumNumbersWithDigit (digit: int) (numbers: int list) =
    numbers
    // Фильтруем только те числа, которые содержат заданную цифру
    |> List.filter (containsDigit digit)
    // Суммируем отфильтрованные числа с начальным значением 0
    |> List.fold (+) 0

// Функция для ввода списка целых чисел от пользователя
let inputNumbers () =
    printfn "Введите список целых чисел (разделяя пробелами):"
    // Читаем строку, введенную пользователем
    let input = System.Console.ReadLine()
    // Разбиваем строку ввода на подстроки, используя пробелы в качестве разделителей
    input.Split(' ', StringSplitOptions.RemoveEmptyEntries)
    // Преобразуем каждую подстроку в число, отбрасывая некорректные значения
    |> Array.choose (fun x ->
        match Int32.TryParse(x) with
        | true, num -> Some num // Корректно сконвертированное число добавляется в результат
        | false, _ -> None      // Некорректные строки отбрасываются
    )
    // Преобразуем массив чисел в список
    |> List.ofArray

// Функция для получения корректного ввода цифры от пользователя
let rec getValidDigit () =
    printfn "Введите цифру:"
    let digitInput = System.Console.ReadLine()
    match Int32.TryParse(digitInput) with
    | true, digit when digit >= 0 && digit <= 9 ->
        digit
    | _ ->
        printfn "Ошибка: введите целую цифру от 0 до 9. Попытайтесь снова."
        getValidDigit () // Рекурсивный вызов для повторного ввода

let digit = getValidDigit()
let numbers = inputNumbers()
let sum = sumNumbersWithDigit digit numbers
printfn "Сумма чисел, в которых содержится цифра %d: %d" digit sum