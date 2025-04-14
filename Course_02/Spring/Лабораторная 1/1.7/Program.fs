open System
open System.IO

// Функция для получения самого длинного названия файла в указанном каталоге
let getLongestFileName directoryPath =
    // Получаем последовательность всех файлов в указанном каталоге и его подкаталогах
    let files =
        Directory.EnumerateFiles(directoryPath, "*", SearchOption.AllDirectories)
    
    // Находим файл с самым длинным названием
    files
    |> Seq.maxBy (fun file -> file.Length)

[<EntryPoint>]
let main argv =
    // Функция для получения корректного пути к каталогу от пользователя
    let rec getValidDirectoryPath () =
        Console.WriteLine("Введите путь к каталогу:")
        let directoryPath = Console.ReadLine().Trim()
        
        if String.IsNullOrWhiteSpace(directoryPath) then
            Console.WriteLine("Путь к каталогу не может быть пустым. Попробуйте снова.")
            getValidDirectoryPath ()
        elif not (Directory.Exists(directoryPath)) then
            Console.WriteLine("Указанный каталог не существует. Попробуйте снова.")
            getValidDirectoryPath ()
        else
            directoryPath
    
    // Получаем корректный путь к каталогу от пользователя
    let validDirectoryPath = getValidDirectoryPath ()
    
    // Проверка, существует ли указанный каталог
    if Directory.Exists(validDirectoryPath) then
        try
            // Получаем самое длинное название файла
            let longestFileName = getLongestFileName validDirectoryPath
            Console.WriteLine($"Самое длинное название файла: {Path.GetFileName(longestFileName)}")
        with
        | :? UnauthorizedAccessException ->
            Console.WriteLine("Ошибка: недостаточно прав для доступа к некоторым файлам или каталогам.")
        | :? IOException as ex ->
            Console.WriteLine($"Ошибка ввода/вывода: {ex.Message}")
    else
        Console.WriteLine("Указанный каталог не существует.")
    
    // Код завершения
    0