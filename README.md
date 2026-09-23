
# SimHUB Peugeot 407 CAN-BUS emulator

Projekt powstawał w latach 2021-2023 i jego pierwszą wersją dostępną publicznie był uruchomiony liznik z Peugeota 207. Z czasem udawało mi się coraz bardziej rozumieć komunikację CAN-BUS z licznikiem i oprócz pracy nad nowymi licznikami cały czas dodawałem poprawki do już istniejących kodów.


- [Film na Youtube:](https://youtu.be/9vEeve54U)
## Wymagany sprzęt

- Arduino Nano
- MCP2515
- Zasilacz 12V
- Licznik samochowy Peugeot 407 (wersja z wyświetlaczem LCD)



## Opis instalacji

Wysoce zalecam wgrywać kod na Arduino przez zainstalowaną na komputerze najnowszą wersję programu Arduino IDE. Nie zalecam korzystać z wbudowanego w SimHUB Arduino IDE Portable. 

### 1 Sprawdzenie poprawności połączenia komputera z Arduino
Uprewnij się, że Arduino jest poprawnie wykrywane przez poprzez narzędzie "Menedżer Urządzeń". Rozwiń listę "Porty COM i LPT" i zweryfikuj, czy podłączone przez Ciebie Arduino jest poprawnie wykrywane.

### 2 Wgranie bibliotek niezbędnych do kompilacji
Otwórz folder z bibliotekami Arduino IDE (domyślnie C:\Users\Twoa_Nazwa_Uzytkownika\Documents\Arduino\libraries) i wklej tam wszystkie biblioteki zawarte folderze arduino_liblaries, który znajdziesz w pobranej paczce. 

### 3 Kompilacja kodu i wgranie formuły NCalc
Skompiluj i wgraj kod na Arduino. Następnie uruchom aplikację SimHUB i przejdź do zakładki Arduino -> My Hardware. Przy pierwszym uruchomieniu wybieramy czy chcemy korzystać tylko z jednej płytki Arduino czy nasz projekt będzie oparty o więcej niż jedno arduino. Domyślnie zalecam wybrać opcję Single Arduino. Zweryfikuj czy po kilku/kilkunastu sekundach podłączy się urządzenie o nazwie MattechPC Peugeot 407 V2.0

#### 4 Wszystko gotowe
Możesz uruchomić Twoją ulubioną grę i cieszyć się zabawą wzbogaconą o działający licznik samochodowy.
Uwaga! Niektóre gry wymagają włączenia telemetrii/instalacji dodatków lub innej zaawansowanej konfiguracji. Wszystkie niezbędne informacje odnośnie konfiguracji telemetrii znajdziesz w aplikacji SimHUB. 
