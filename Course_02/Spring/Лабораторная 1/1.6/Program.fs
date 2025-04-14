open System

// Функция, которая рекурсивно запрашивает у пользователя слова и формирует из них последовательность
let rec inputWordsToSeq () =
    // Запрашиваем у пользователя ввод слова
    Console.WriteLine("Введите слово (для завершения нажмите Enter в пустой строке): ")
    let userInput = Console.ReadLine()
    // Проверяем, если пользователь ввел '', возвращаем пустую последовательность
    if userInput.ToLower() = "" then
        Seq.empty
    else
        // Иначе рекурсивно вызываем функцию для ввода оставшихся слов и добавляем введенное слово в начало последовательности
        Seq.append (seq { yield userInput }) (inputWordsToSeq())

// Вызываем функцию для формирования последовательности слов
let wordsSeq = inputWordsToSeq()
// Создание новой последовательности из длин путем преобразования оригинальной
let stringLengthsSeq = wordsSeq |> Seq.map String.length

// Выводим оригинальную последовательность слов
Console.WriteLine("Оригинальный список:")
wordsSeq |> Seq.iter Console.WriteLine

// Выводим новую последовательность длин
Console.WriteLine("Новый список:")
stringLengthsSeq |> Seq.iter Console.WriteLine