open System
// Функция, которая генерирует последовательность слов
let generateWords () =
    seq {
        while true do
            let word = Console.ReadLine()
            yield word
    }
// Собираем последовательность слов в список
Console.WriteLine("Введите слова. Для подтверждения ввода слова нажмите Enter. Для завершения нажмите Enter в пустом поле")
let wordList = generateWords() |> Seq.takeWhile (fun word -> not (String.IsNullOrWhiteSpace word)) |> List.ofSeq
// Выводим результат
printfn "Список введенных слов:"
wordList |> List.iter (fun word -> printfn "%s" word)