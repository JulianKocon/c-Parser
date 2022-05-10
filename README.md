# C++ Parser
## Opis

Narzędzie służące do wykonywania przeróżnych operacji na zawartościach plików tekstowych zapisanych w formacie ANSI.


### Uruchamianie programu

* Aplikacja uruchamiana z poziomu linii poleceń bazując na przekazanych flagach, produkuje odpowiedni tekst zawierający zgodne z wymaganiami informacje.
Przykładowo:
```
-f input.txt -n -c -o output.txt -l -s -dd -d -c -w -p ala ma kota
```
### Opis flag

Flaga -f oczekuje, że następnym argumentem będzie ścieżka do **pliku źródłowego**.

Flaga -n wyświetla liczbę linii z pliku źródłowego.

Flaga -d wyświetla liczbę cyfr z pliku źródłowego. Cyfra nie musi być osobnym słowem
(czyli oddzielona białymi znakami lub początkiem / końcem pliku).

Flaga -dd wyświetla liczbę liczb z pliku źródłowego.


Flaga -c wyświetla liczbę znaków z pliku źródłowego.

Flaga -w wyświetla liczbę słów z pliku źródłowego. Słowo to dowolny ciąg niebiałych
znaków. Liczby również traktowane są jako słowo.

Flaga -s wyświetla wszystkie słowa z pliku wejściowego w kolejności alfabetycznej.

Flaga -rs wyświetla wszystkie słowa z pliku wejściowego w kolejności odwrotnej od
alfabetycznej.

Flaga -l modyfikuje działanie następującej po niej fladze -s lub -rs tak, aby
zamiast brać pod uwagę kolejność alfabetyczną, flagi te biorą pod uwagę kolejność
precyzowaną przez długość poszczególnych słów.

Flaga -a powinna być ostatnią sprecyzowaną flagą, po której nastąpi nieokreślona liczba słów. Program z tak podaną flagą wyświetla wszystkie słowa z pliku
 źródłowego, które są anagramami słów podanych tuż po tej fladze. Tak wyświetlane
 słowa nie powtarzają się.

Flaga -p powinna być ostatnią sprecyzowaną flagą, po której nastąpi nieokreślona liczba słów. Program z tak podaną flagą wyświetla wszystkie podane po fladze
słowa, które są palindromami oraz występują w pliku źródłowym. Tak
 wyświetlane słowa nie powtarzają się.

Flaga -o, po której oczekuje się ścieżki do pliku, modyfikuje działanie programu w
 taki sposób, że zamiast wyświetlać informacje na konsoli, w której uruchamiana jest
 aplikacja, efekt działania programu w postaci tekstu zostaje zapisany do pliku o
 sprecyzowanej ścieżce.

Flaga -i, po której oczekuje się ścieżki do pliku wejściowego, modyfikuje
    działanie programu w taki sposób, że zamiast precyzować resztę flag jako argumenty
    wywołania, aplikacja pobiera flagi i dane ich dotyczące z wymienionego wcześniej
    pliku wejściowego. Flaga ta powinna być jedyną podaną podczas uruchamiania aplikacji
    (reszta flag znajduje się w pliku wejściowym).
## Autor

Julian Kocon

### Data utworzenia: czerwiec 2021
