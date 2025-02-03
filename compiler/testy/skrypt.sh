#!/bin/bash

# Sprawdzenie, czy plik kompilatora istnieje
if [[ ! -f "./kompilator" ]]; then
    echo "Błąd: Plik 'kompilator' nie istnieje w bieżącym katalogu!"
    exit 1
fi

# Przejście przez wszystkie pliki *.imp we wszystkich podfolderach
find . -type f -name "*.imp" | while read file; do
    # Pobranie nazwy pliku bez ścieżki i rozszerzenia
    filename=$(basename -- "$file")
    name="${filename%.*}"  # Usunięcie rozszerzenia .imp

    # Pobranie katalogu, w którym znajduje się plik
    dir=$(dirname "$file")

    # Uruchomienie kompilatora w katalogu z plikiem
    echo "--------------Przetwarzanie pliku: $file----------------------"
    (cd "$dir" && ./kompilator "$filename" "$name.mr")

    # Sprawdzenie, czy kompilacja zakończyła się sukcesem
    if [[ $? -eq 0 ]]; then
        echo "✅ Sukces: $name.gbl -> $name.mr"
    else
        echo "❌ Błąd: Nie udało się skompilować $name.imp"
    fi
done

