# Event Storming - Raport

## Cel

Punktem wyjścia do Event Stormingu jest [Definicja systemu](project-description.md).

Celem sesji Big Picture Event Storming jest eksploracja systemu, czyli:
- Określenie zdarzeń występujących w systemie
- Identyfikacja aktorów, podsystemów i systemów zewnętrznych
- Identyfikacja procesów realizowanych przez system i powiązań między nimi
- Stworzenie modelu działania systemu
- Poznanie domeny problemu
- Identyfikacja języka domenowego
- Synchronizacja wiedzy między członkami zespołu
- Identyfikacja potencjalnych problemów i możliwych usprawnień

Kolejnym krokiem będzie określenie wymagań systemu i architektury, co po poznaniu systemu podczas sesji Event Stormingu powinno być dużo łatwiejsze.


## Przebieg Event Stormingu

Zaczęliśmy od identyfikacji zdarzeń i uszeregowania ich chronologicznie.

![](img/event-storming/1/1.jpg)

Widok szczegółowy poszczególnych elementów:
![](img/event-storming/1/2.jpg)
Tutaj wyłaniają się procesy dotyczące odczytu danych ze sterownika i wprowadzania nowych wartości.
![](img/event-storming/1/3.jpg)
Tutaj mamy zdarzenia dotyczące konfiguracji systemu.
![](img/event-storming/1/4.jpg)
A tutaj kwestie autoryzacji użytkowników i prezentacji danych. Niektóre widoki np. konfiguracja są częścią większych procesów. Natomiast pozostałe to tylko generowanie widoków z posiadanych danych i nie ma sensu ich na razie dalej eksplorować.

Następnie doszli aktorzy i podsystemy. Tak wygląda cały board:
![](img/event-storming/2/1.jpg)

A tak zidentyfikowane elementy:
![](img/event-storming/2/9.jpg)

Do poszczególnych procesów dodaliśmy elementy biorące udział w danych krokach.
![](img/event-storming/2/2.jpg)
![](img/event-storming/2/3.jpg)
![](img/event-storming/2/4.jpg)
![](img/event-storming/2/5.jpg)
![](img/event-storming/2/6.jpg)
![](img/event-storming/2/7.jpg)
![](img/event-storming/2/8.jpg)

Kolejnym krokiem było uszczegółowienie i nazwanie poszczególnych procesów.
Tak wygląda efekt końcowy.
![](img/event-storming/3/1.jpg)

W trakcie sesji pojawiło się również kilka pytań, możliwych nieuwzględnionych scenariuszy i zagrożeń. Zostały spisane na oddzielnych karteczkach.
![](img/event-storming/3/9.jpg)

## Efekt końcowy

W efekcie sesji Event Stormingu udało się zidentyfikować najważniejsze elementy systemu oraz procesy, jakie wykonuje. Początkowa definicja systemu została zmapowana na procesy, w niektórych miejscach udało się rozszerzyć ją o dodatkowe informacje.

### Elementy systemu

![](img/event-storming/2/9.jpg)

Nasz system składa się z dwóch podsystemów:
- Serwer
- Konwerter

Wchodzi w interakcje z dwoma systemami zewnętrznymi:
- Sterowniki budynkowe
- Bramka SMS

A ludziom wchodzącym w interakcje z systemem możemy przypisać role:
- Serwisant - ma prawa do wyświetlania i modyfikacji wszystkich widoków dla wszystkich budynków.
- Zarządca budynku - ma prawa do wyświetlania danych dla swoich budynków.

### Odczyt danych ze sterownika

![](img/event-storming/3/2.jpg)

Fakty o procesie:
- Odbywa się cyklicznie co 1 minutę
- Do komunikacji ze sterownikiem wykorzystujemy Modbus RTU
- Konwerter jest masterem, który odpytuje 1 lub więcej sterowników budynkowych będących slave'ami
- Konwerter zna dane modbus do odpytania z konfiguracji
- Na koniec każdego cyklu odczytu do zbioru danych dodawany jest timestamp
- Dane Modbus + Timestamp tworzą pakiet danych wysyłanych na serwer za pomocą TCPIP
- Szczegóły protokołu do komunikacji z serwerem nie są narzucone z góry
- Dane na serwerze są zapisywane do bazy danych

Dane Modbus:
- Slave ID
- Fun
- Register
- Length (od tego parametru zależy rozmiar pola value)
- Value (odczytywana ze sterownika, nie potrzebna w konfiguracji)

Format timestampu:
- Do ustalenia

Dane wysyłane na serwer:
- Timestamp
- Dane modbus wraz z odczytanymi wartościami
- Format ramki do ustalenia

### Modyfikacja danych na sterowniku

![](img/event-storming/3/3.jpg)

Fakty o procesie:
- Proces jest inicjowany przez serwisanta za pomocą odpowiedniego widoku na serwerze.
- Konfiguracja sterownika narzuca ograniczenia na modyfikowane dane (RW/ReadOnly, typy danych, mapowanie adresów Modbus na realne wartości)
- Konfiguracja sterownika zapewnia mapowanie wartości na rejestry Modbus
- Pozostałe ograniczenia musi znać serwisant po zapoznaniu z dokumentacją konkretnego sterownika i konfiguracji budynku
- Nie ma zewnętrznych wymagań dotyczących komunikacji Serwer - Konwerter
- Nie ma polityki retransmisji i błędnych odpowiedzi sterownika
- Nie ma potwierdzenia o poprawnej modyfikacji na sterowniku
- Skutki modyfikacji można zobaczyć po kolejnym odczycie danych

Dane wysyłane na konwerter:
- Dane Modbus (slave, fun, reg, len, val)
- Dla każdej wartości sterownika oddzielne rządanie
- Format ramki do ustalenia

### Wgrywanie konfiguracji

![](img/event-storming/3/4.jpg)

Fakty o procesie:
- Proces jest inicjowany przez serwisanta za pomocą odpowiedniego widoku na serwerze
- Konfiguracja sterownika budynkowego zakończyła się wcześniej i została opisana w odpowiednim dokumencie
- Procesy dodawania nowego budynku i edycji istniejącego budynku nie różnią się w dalszych krokach
- Konfiguracja na serwerze jest tworzona na bazie istniejącej konfiguracji sterownika budynkowego
- Konfiguracja jest archiwizowana i składowana na serwerze wraz z historią konfiguracji dla każdego budynku
- Proces zakłada, że konwerter dla tego budynku został wcześniej wykryty
- Serwer przesyła do konwertera tylko niezbędne dane

Konfiguracja na serwerze zawiera:
- Parametry komunikacji Modbus ze sterownikiem
- Rejestry Modbus sterowników w budynku
- Mapowanie rejestrów Modbus na fizyczne wartości
- Typy danych
- Status Read/Write, Read Only
- Tworzenie graficznej wizualizacji budynku i mapowanie wartości fizycznych
- Mapowanie wartości Modbus na alarmy
- Autor konfiguracji
- Data modyfikacji

Konfiguracja na konwerterze zawiera:
- Dane Modbus
- Autor konfiguracji
- Data modyfikacji

Komunikacja Serwer - Konwerter:
- Format ramki do ustalenia

Format konfiguracji zapisanej w pamięci konwertera:
- Do ustalenia

### Sprawdzenie konfiguracji

![](img/event-storming/3/5.jpg)

Fakty o procesie:
- Proces jest inicjowany przez serwisanta za pomocą odpowiedniego widoku na serwerze
- Wynik żądania jest prezentowany w odpowiednim panelu

Komunikacja Serwer - Konwerter:
- Format ramek do ustalenia

### Alarmy

![](img/event-storming/3/6.jpg)

Fakty o procesie:
- Proces jest triggerowany po odczytaniu danych ze sterownika
- Proces jest triggerowany przez timeout komunikacji z konwerterem
- Proces jest triggerowany przez powiadomienie od konwertera o braku komunikacji ze sterownikiem
- Mapowanie danych Modbus na alarmy odbywa się w konfiguracji

Możliwe źródła alarmów:
- Wartość bitowa Modbus
- Wartość danej Modbus przekracza próg
- Brak komunikacji ze sterownikiem
- Brak komunikacji z konwerterem

Warunki braku komunikacji z konwerterem:
- Brak nowych odczytów przez 5 minut

Warunki braku komunikacji ze sterownikiem:
- Brak komunikacji/błędy odczytów przez 5 minut

Komunikacja Serwer - Konwerter:
- Format ramki do ustalenia

### Logowanie i widoki

![](img/event-storming/3/7.jpg)

To są dwa procesy realizowane w 100% na serwerze. To są standardowe zadania autoryzacji i komunikacji z bazą danych, dlatego nie musimy ich w tym momencie dalej eksplorować.

### Sygnalizacja błędu

![](img/event-storming/3/8.jpg)

Fakty o procesie:
- Proces może być triggerowany podczas odczytu konfiguracji
- Proces może być triggerowany podczas odczytów ze sterownika
- Proces może być triggerowany przez błąd na konwerterze

Możliwe przyczyny błędów:
- Brak konfiguracji/Bład odczytu konfiguracji z pamięci
- Brak komunikacji ze sterownikiem przez 5 minut
- Błędy wszystkich odczytów ze sterownika przez 5 minut

Błędy odczytów ze sterownika:
- Są sygnalizowane za pomocą odpowiedzi Modbus 0x8X
- Nie robimy dalszego rozróżnienia klas błędów

### Wątpliwości i ryzyka

W trakcie sesji zidentyfikowaliśmy również obszary, które nie zostały uwzględnione w modelu. Zostały zapisane w formie pytań i możliwych scenariuszy.

![](img/event-storming/3/9.jpg)

Nie są to ryzyka stawiające pod znakiem zapytania cały projekt, wymagają jedynie doprecyzowania. Dlatego zostaną zaadresowane w dalszej części prac nad projektem.
