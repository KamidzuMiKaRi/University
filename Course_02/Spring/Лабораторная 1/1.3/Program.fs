open System

// Функция, которая рекурсивно запрашивает у пользователя слова и формирует из них список
let rec inputWordsToList () =
    // Запрашиваем у пользователя ввод слова
    Console.WriteLine("Введите слово (для завершения введите '!!!'): ")
    let userInput = Console.ReadLine()
    // Проверяем, если пользователь ввел '!!!', возвращаем пустой список
    if userInput.ToLower() = "!!!" then
        []
    else
        // Иначе рекурсивно вызываем функцию для ввода оставшихся слов
        let OneWord = inputWordsToList()
        // Добавляем введенное слово к остальным словам в списке
        userInput :: OneWord

// Вызываем функцию для формирования списка слов
let wordsList = inputWordsToList()
// Создание нового списка из длин путем преобразования оригинального
let stringLengths = List.map (fun str -> String.length str) wordsList
Console.WriteLine("Оригинальный список:")
// Выводим каждое слово из списка
wordsList |> List.iter (fun words -> Console.WriteLine(words))
Console.WriteLine("Новый список:")
// Выводим каждое слово из списка
stringLengths |> List.iter (fun word -> Console.WriteLine(word))