# 📐 Kalkulator do Analizy Matematycznej

Aplikacja webowa z backendem napisanym w **C++**, służąca do obliczania oraz wizualizacji podstawowych zagadnień analizy matematycznej, takich jak:

* całki oznaczone,
* całki nieoznaczone,
* pochodne,
* pole między krzywymi,
* objętość brył obrotowych.

Wizualizacja wykresów funkcji realizowana jest przy użyciu biblioteki **Chart.js**.

---

# Link do programu
https://mega.nz/file/DmxFFLaL#Jr62PhLOD8Id-jkg6Goq_OiDjD4Sx_DRShQBkRNaO9k

# 🛠️ Struktura projektu

```text
KalkulatorAnalizy/
├── frontend/
│   ├── index.html       # Interfejs użytkownika (UI)
│   ├── script.js        # Obsługa wykresów, historii i komunikacji HTTP
│   └── style.css        # Stylowanie aplikacji
│
└── backend/
    ├── main.cpp         # Serwer HTTP i logika matematyczna
    └── httplib.h        # Biblioteka HTTP dla C++
```

---

# 🧰 Wymagania systemowe

Do uruchomienia aplikacji potrzebujesz:

* **Windows 10/11**, Linux lub macOS
* Nowoczesnej przeglądarki internetowej (Chrome, Edge, Firefox)
* Skompilowanego backendu C++ lub kompilatora C++ (GCC/MinGW)
* Lokalnego serwera HTTP dla frontendu (Live Server, Python lub Node.js)

---

# 🚀 Uruchomienie aplikacji

Aplikacja składa się z dwóch części:

1. **Backend (C++)**
2. **Frontend (HTML/CSS/JavaScript)**

Obie części muszą być uruchomione jednocześnie.

> **Uwaga:** Nie otwieraj pliku `index.html` bezpośrednio z dysku (`file:///`). Komunikacja z backendem zostanie zablokowana przez politykę bezpieczeństwa przeglądarki (CORS).

---

## 1️⃣ Uruchomienie backendu

Przejdź do folderu `backend`.

Uruchom plik wykonywalny:

```bash
backend.exe
```

lub

```bash
main.exe
```

Po uruchomieniu pojawi się okno konsoli.

Nie zamykaj go — serwer będzie nasłuchiwał na:

```text
http://localhost:8080
```

### Kompilacja kodu źródłowego

Jeżeli chcesz samodzielnie skompilować projekt:

```bash
g++ main.cpp -o backend.exe -lws2_32
```

---

## 2️⃣ Uruchomienie frontendu

### Metoda A — Visual Studio Code (zalecana)

1. Otwórz folder `frontend` w VS Code.
2. Zainstaluj rozszerzenie **Live Server**.
3. Kliknij prawym przyciskiem myszy na `index.html`.
4. Wybierz **Open with Live Server**.

Aplikacja zostanie uruchomiona pod adresem:

```text
http://127.0.0.1:5500
```

---

### Metoda B — Python

W folderze `frontend` uruchom terminal i wpisz:

```bash
python -m http.server 3000
```

Następnie otwórz:

```text
http://localhost:3000
```

---

### Metoda C — Node.js

W folderze `frontend` uruchom:

```bash
npx serve
```

Następnie przejdź pod adres wyświetlony w terminalu.

---

# 📈 Korzystanie z aplikacji

### 1. Wybór funkcji

Wprowadź funkcję matematyczną, np.:

```text
x^2
sin(x)
cos(x)
e^x
ln(x)
```

Możesz również skorzystać z panelu **Gotowe funkcje**.

---

### 2. Wybór operacji

Z rozwijanej listy wybierz operację:

* Pochodna
* Całka oznaczona
* Całka nieoznaczona
* Pole między krzywymi
* Objętość bryły obrotowej

---

### 3. Podanie granic

Dla operacji wymagających przedziału podaj:

* Dolną granicę
* Górną granicę

---

### 4. Obliczenie wyniku

Kliknij przycisk:

```text
Oblicz
```

Wynik zostanie wyświetlony poniżej formularza.

---

### 5. Wizualizacja

Po wykonaniu obliczeń:

* wyświetlony zostanie wynik matematyczny,
* wygenerowany zostanie wykres funkcji,
* zapytanie zostanie zapisane w historii.

Kliknięcie pozycji w historii automatycznie przywróci wybraną funkcję.

---

# 🔍 Obsługiwane funkcje matematyczne

### Wielomiany

```text
x
x²
x³
```

### Funkcje trygonometryczne

```text
sin(x)
cos(x)
```

### Funkcja wykładnicza

```text
e^x
```

### Logarytm naturalny

```text
ln(x)
```

---

# 🛠️ Rozwiązywanie problemów

## Brak reakcji po kliknięciu „Oblicz”

Jeżeli pojawia się błąd:

```text
Unsafe attempt to load URL...
```

oznacza to, że plik `index.html` został otwarty bezpośrednio z dysku.

Uruchom frontend przez lokalny serwer HTTP.

---

## Błąd bibliotek DLL

Jeżeli aplikacja C++ nie uruchamia się na Windowsie z powodu brakujących bibliotek:

Zainstaluj pakiet:

**Microsoft Visual C++ Redistributable**

---

## Problemy z wykresem

### Reset widoku

Podwójne kliknięcie na wykres resetuje jego widok do domyślnego zakresu:

```text
-5 do 5
```

### Powiększanie

Przytrzymaj klawisz:

```text
Shift
```

i użyj scrolla myszy.

---

# 💻 Technologie wykorzystane w projekcie

### Backend

* C++
* HTTP Server (cpp-httplib)

### Frontend

* HTML5
* CSS3
* JavaScript (ES6)

### Biblioteki

* Chart.js
* MathJax


