
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
Otwórz folder z bibliotekami Arduino IDE (domyślnie C:\Users\Twoa_Nazwa_Uzytkownika\Documents\Arduino\libraries) i wklej tam wszystkie biblioteki zawarte folderze arduino_libraries, który znajdziesz w pobranej paczce. 

### 3 Kompilacja kodu i wgranie formuły NCalc
Skompiluj i wgraj kod na Arduino. Następnie uruchom aplikację SimHUB i przejdź do zakładki Arduino -> My Hardware. Przy pierwszym uruchomieniu wybieramy czy chcemy korzystać tylko z jednej płytki Arduino czy nasz projekt będzie oparty o więcej niż jedno arduino. Domyślnie zalecam wybrać opcję Single Arduino. Zweryfikuj czy po kilku/kilkunastu sekundach podłączy się urządzenie o nazwie MattechPC Peugeot 407 V2.0

#### 4 Wszystko gotowe
Możesz uruchomić Twoją ulubioną grę i cieszyć się zabawą wzbogaconą o działający licznik samochodowy.
Uwaga! Niektóre gry wymagają włączenia telemetrii/instalacji dodatków lub innej zaawansowanej konfiguracji. Wszystkie niezbędne informacje odnośnie konfiguracji telemetrii znajdziesz w aplikacji SimHUB. 
## Debuging
Kod domyślnie wyposażony jest w mechanizm debugujący, do wyjść A0-A2 należy podpiąć anody (+) diod LED. Wyjścia odpowiadają za:
- A0 - Połączenie projektu z licznikiem 
- A1 - Połączenie Arduino z SimHUB
- A2 - Połączenie Arduino z MCP2515

W przypadku błędu stan wyjść zmienia się na niski - dioda gaśnie. Wszytskie diody zapalone = wsyztsko OK. 
## PCB i druk 3D

Projekt posiada dedykowaną płytkę PCB oraz obudowę wykonaną na drukarce 3D, jej użycie jest opcjonalne. Pliki STL do obudowy znajdują się w pobranej paczce.
PCB posiada dedykowane miejsca na diody debugujące oraz dodatkową diodę na linii zasilania 12/24V informującą o poprawnym działaniu zasilacza. Za wtykiem zasilającym znajdują się miejsca na 2 rezystory 1KΩ. Za rezystorami znajdują się 2 zworki, zalutowując zworkę przy wybranej wartości napięcia definiujemy czy dioda ma współpracować z 12V czy z 24V. 
<img width="1062" height="1191" alt="PCB" src="https://github.com/user-attachments/assets/e14ff84d-7959-4088-9c38-ed9fc2073470" />
<img width="1754" height="892" alt="CLUSTER_PCB" src="https://github.com/user-attachments/assets/9b8d436d-fa08-4dec-85b5-90e58b471b15" />


#### ❗UWAGA❗ Niepoprawne skonfigurowanie zworki może powodować nieprawidłowe działanie diody lub nawet trwałe uszkodzenie LED'a. 

W przyszłości będzie można zamówić dedykowaną płytkę PCB (zlutowaną lub do zlutowania) oraz obudowę. Na ten moment: work in progress. 
## Poradniki YouTube
Stworzyłem cały poradnik jak podączyć i skonfugurować licznik. Sprawdź najnowsze materiały:
