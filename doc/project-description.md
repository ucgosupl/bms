# Project Description

Nasza firma oferuje usługi zarządzania systemami HVAC budynków. Instalujemy sterowniki budynkowe, dodajemy integracje do istniejących sterowników i wykonujemy prace serwisowe na obiektach u klienta. Potrzebujemy systemu zbierającego dane ze wszystkich naszych budynków i umożliwiającego zarządzanie nimi, aby ułatwić pracę serwisantom.

Sterowniki na obiektach są od różnych producentów, mają różne interfejsy i nie da się podłączyć ich bezpośrednio do serwera. Ale każdy sterownik obsługuje protokół Modbus RTU. Dlatego na każdym obiekcie (budynku) zamontujemy konwerter (bramkę, Gateway) zbierający dane jako Modbus Master podłączony do jednego lub więcej urządzeń Modbus Slave (sterowników budynkowych). Dane z każdego sterownika są pobierane cyklicznie co 1 min, a następnie archiwizowane na centralnym serwerze. Zapisane dane powinny posiadać timestamp w celu późniejszej prezentacji wyników.

Podczas integracji z naszym systemem minimalizujemy zmiany po stronie sterownika - ograniczamy się do ustawienia parametrów komunikacji Modbus. Zakładamy, że konfiguracja sterownika wymagana do działania systemu HVAC w budynku została wykonana wcześniej, a my dodajemy tylko połączenie z naszym systemem.

Serwer obsługuje dwie klasy użytkowników:
- Serwisant - pracownik naszej firmy, który ma dostęp do wszystkich budynków i widoków z prawami do edycji
- Zarządca Budynku - nasz klient, ma dostęp read only jedynie do wizualizacji i wykresów dla swoich budynków

Widoki:
- Dashboard - status wszystkich budynków
- Wizualizacja z naniesionymi aktualnymi wartościami - Temperatura zewnętrzna, Temperatura zadana, Stan otwarcia przepustnic, Poziom mocy nagrzewnic i wentylatorów, wilgotność (szczegóły wizualizacji i danych na bazie konfiguracji)
- Wykresy zmian danych parametrów w czasie
- Historia eventów
- Modyfikacja danych na sterowniku - umożliwia wysłanie żądania zapisu wartości przez Modbus
- Konfiguracja - dodawanie budynków/edycja istniejących

W przypadku wykrycia alarmu system powinien wysyłać powiadomienie SMS do serwisanta odpowiedzialnego za dany budynek.

Możliwe źródła alarmów:
- Wartość bitowa danego rejestru Modbus
- Wartość rejestru Modbus przekracza próg
- Brak komunikacji ze sterownikiem/gatewayem
Mapowanie rejestrów Modbus na alarmy odbywa się podczas konfiguracji.

Podczas konfiguracji budynku w systemie mamy do dyspozycji dokumenty od instalatorów systemu HVAC. Nie mają one ustandaryzowanej formy, ale zawsze zawierają tabelę z opisem poszczególnych rejestrów Modbus. Te dokumenty są wykorzystywane przez serwisanta do konfiguracji naszego systemu.

Dane konfiguracyjne wprowadzane przez serwisanta:
- Adresy wykorzystywanych rejestrów Modbus i typy danych
- Mapowanie rejestrów na fizyczne wartości (temperatury, alarmy itp.)
- Rozmieszczenie fizycznych wartości na wizualizacji
- Autor konfiguracji
- Data modyfikacji

Popularne typy danych Modbus:
- Pola bitowe
- Stałoprzecinkowe (uint16/32 int16/32)
- Zmiennoprzecinkowe (float32/64)
- String (Max 128 znaków)

Po zakończeniu konfiguracji mamy do niej dostęp na serwerze razem z historią zmian. Po zaakceptowaniu nowej konfiguracji zostaje ona wysłana do Gatewaya. Następnie Gateway zapisuje swoją konfigurację w pamięci nieulotnej i wczytuje ją po resecie. Serwer ma możliwość odpytania Gatewaya o konfigurację i sprawdzenia, czy jest zgodna.

Gateway montowany w szafie sterowniczej na szynie DIN i zasilane z 12V. Wszystkie IO muszą być wyprowadzone jako złącza śrubowe lub standardowe złącza np. ETH. Komponenty muszą pracować w zakresie temperatur -20 - 80 *C.

Panel przedni powinien udostępniać podstawowe informacje ułatwiające instalacje:
- LED Power
- LED Tx/Rx (może być z drivera RS485)
- LED Status - miga co 1s w przypadku błędu




# Słowniczek

- BMS - Building Management System
- HVAC - Heating, Ventilation, Air Conditioning - klimatyzacja
- Controller (pl. Sterownik budynkowy) - urządzenie zarządzające systemem HVAC budynku, z którego nasz system zbiera dane
- Gateway - (pl. Bramka, Konwerter) - część naszego systemu odpowiedzialna za komunikację Modbus ze sterownikiem i wysyłanie na serwer
- Serwer - część naszego systemu odpowiedzialna za konfigurację oraz składowanie i prezentację danych
