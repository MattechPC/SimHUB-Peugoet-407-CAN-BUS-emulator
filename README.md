

# SimHUB Peugeot 407 CAN-BUS emulator

Projekt powstawał w latach 2021-2023 i jego pierwszą wersją dostępną publicznie był uruchomiony liznik z Peugeota 207. Z czasem udawało mi się coraz bardziej rozumieć komunikację CAN-BUS z licznikiem i oprócz pracy nad nowymi licznikami cały czas dodawałem poprawki do już istniejących kodów.

<img width="600" height="338" alt="407_gif" src="https://github.com/user-attachments/assets/dd0b0cab-c7f0-4a87-bc22-da506cbfcffb" />


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
Otwórz folder z bibliotekami Arduino IDE (domyślnie C:\Users\Twoa_Nazwa_Uzytkownika\Documents\Arduino\libraries) i wklej tam wszystkie biblioteki zawarte folderze ZIP arduino_libraries, który znajdziesz w pobranej paczce. 

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
<img width="500"  alt="PCB" src="https://github.com/user-attachments/assets/d57e5b0a-54e0-4246-9746-a880db800608" />

<img width="500"  alt="CLUSTER_PCB" src="https://github.com/user-attachments/assets/ca604e5d-b2c8-4450-81bf-3bca33a66298" />

#### ❗UWAGA❗ Niepoprawne skonfigurowanie zworki może powodować nieprawidłowe działanie diody lub nawet trwałe uszkodzenie LED'a. 

W przyszłości będzie można zamówić dedykowaną płytkę PCB (zlutowaną lub do zlutowania) oraz obudowę. Na ten moment: work in progress. 
## Poradniki YouTube
Stworzyłem cały poradnik jak podączyć i skonfugurować licznik. Sprawdź najnowsze materiały:
<a href ="https://youtu.be/D8mY-5T7rYY"> <img width="640" alt="407_thumbnail" src="https://github.com/user-attachments/assets/d5760a96-43df-492e-a6d7-094b196952c6" /> </a>
<a href ="https://youtu.be/9vEeve54UiU"> <img width="640"  alt="207_thumbnail" src="https://github.com/user-attachments/assets/ae437022-710f-490d-be79-7bb75a509cc9" /> </a>
<a href ="https://youtu.be/mzjBLN_IS14"> <img width="640"  alt="207_update_thumbnail" src="https://github.com/user-attachments/assets/d4c24841-b09a-44ea-9b86-4edff9dcee9b" /> </a>
<a href ="https://youtu.be/c1_7InaBueM"> <img width="640"  alt="C3_thumbnail" src="https://github.com/user-attachments/assets/c591e6a1-2948-490f-bd2a-58c332c13f18" /> </a>
<a href ="https://youtu.be/rEvpyTjFMHs"> <img width="640"  alt="C3_update_thumbnail" src="https://github.com/user-attachments/assets/c0eb79a0-2e41-480e-ab2f-0a3e07f83af9" /> </a>


