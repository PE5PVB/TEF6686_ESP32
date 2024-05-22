#ifndef LANGUAGE_H
#define LANGUAGE_H

#define VERSION "v2.10 RC5"

// [number of languages][number of texts]
// *** means the text is the same as in English
static const char* const myLanguage[18][228] PROGMEM = {
  { "English", // English
    "Rotary direction changed", // 1
    "Please release button", // 2
    "Screen flipped", // 3
    "Calibrate analog meter", // 4
    "Release button when ready", // 5
    "encoder set to optical", // 6
    "encoder set to standard", // 7
    "FM/AM receiver", // 8
    "Tuner: !None!", // 9
    "Volume", // 10
    "Converter", // 11
    "Low band edge", // 12
    "High band edge", // 13
    "FM RF Level offset", // 14
    "Stereo threshold", // 15
    "High Cut corner", // 16
    "Highcut threshold", // 17
    "Low level threshold", // 18
    "Contrast", // 19
    "Set volume", // 20
    "Set converter offset", // 21
    "Set low band edge", // 22
    "Set high band edge", // 23
    "Set level offset", // 24
    "Set Stereo sep. threshold", // 25
    "Set high cut corner frequency", // 26
    "Set High cut threshold", // 27
    "Set low level threshold", // 28
    "Set Display brightness", // 29
    "Off", // 30
    "Screen is muted!", // 31
    "To unmute uncheck RF+ box", // 32
    "OFF", // 33
    "SCANNING...", // 34
    "Tuner not detected", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Show RDS errors", // 38
    "Language", // 39
    "Choose language", // 40
    "PRESS MODE TO EXIT AND STORE", // 41
    "On", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Beep at band edge", // 45
    "Region", // 46
    "Europe", // 47
    "America", // 48
    "Show underscore in RDS", // 49
    "USB mode", // 50
    "Wi-Fi active", // 51
    "Configure Wi-Fi", // 52
    "Connect to: ", // 53
    "to configure Wi-Fi", // 54
    "Trying to connect Wi-Fi", // 55
    "FAILED!", // 56
    "CONNECTED!", // 57
    "Stationlist client IP", // 58
    "Show SW wavelength", // 59
    "RDS filter", // 60
    "Show PI errors", // 61
    "Use squelch", // 62
    "Modulation meter", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "Defaults loaded", // 66
    "Audio output", // 67
    "Allow tuning\nduring screensaver", // 68
    "Invert display", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Screen off", // 76
    "Theme", // 77
    "Skin", // 78
    "Detected applications", // 79
    "Min.", // 80
    "Dynamic SPI speed", // 81
    "Scan sensitivity", // 82
    "NONE", // 83
    "Software version", // 84
    "Frequency font", // 85
    "Auto", // 86
    "No AF available", // 87
    "No EON available", // 88
    "No RT+ available", // 89
    "FM default stepsize", // 90
    "Screensaver", // 91
    "Sec", // 92
    "PRESS BAND TO CLOSE", // 93
    "1% brightness", // 94
    "25% brightness", // 95
    "50% brightness", // 96
    "AM RF Level offset", // 97
    "Signalmeter unit", // 98
    "Use AF", // 99
    "Select FM Band", // 100
    "Select AM Band", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotating while screen off", // 107
    "Model selector", // 108
    "Base (ILI9341)", // 109
    "Portable (ILI9341)", // 110
    "Portable touch (ILI9341)", // 111
    "Title", // 112
    "Album", // 113
    "Track", // 114
    "Artist", // 115
    "Composition", // 116
    "Movement", // 117
    "Conductor", // 118
    "Composer", // 119
    "Band", // 120
    "Comment", // 121
    "Genre", // 122
    "News", // 123
    "Local news", // 124
    "Stockmarket", // 125
    "Sport", // 126
    "Lottery", // 127
    "Horoscope", // 128
    "Daily Diversion", // 129
    "Health", // 130
    "Event", // 131
    "Scene", // 132
    "Cinema", // 133
    "TV", // 134
    "Date/time", // 135
    "Weather", // 136
    "Traffic", // 137
    "Alarm", // 138
    "Advertisement", // 139
    "Website", // 140
    "Other", // 141
    "Short PS", // 142
    "Long PS", // 143
    "Now", // 144
    "Next", // 145
    "Part", // 146
    "Host", // 147
    "Editor", // 148
    "Frequency", // 149
    "Homepage", // 150
    "Subchannel", // 151
    "Hotline", // 152
    "Studio phone", // 153
    "Phone", // 154
    "SMS studio", // 155
    "SMS", // 156
    "Email hotline", // 157
    "Email studio", // 158
    "Email", // 159
    "Chat", // 160
    "Chat centre", // 161
    "Vote question", // 162
    "Vote centre", // 163
    "Place", // 164
    "Appointment", // 165
    "Identifier", // 166
    "Purchase", // 167
    "Get data", // 168
    "MW default stepsize", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Battery options", // 173
    "Show voltage", // 174
    "Show percentage", // 175
    "RT buffering", // 176
    "Main settings", // 177
    "Audio settings", // 178
    "Display settings", // 179
    "RDS settings", // 180
    "FM settings", // 181
    "AM settings", // 182
    "Connectivity", // 183
    "PRESS MODE TO RETURN", // 184
    "CoChannel Detector", // 185
    "CoChannel Detector\nsensitivity", // 186
    "CoChannel Detector\nthreshold", // 187
    "CoChannel Detector\ncounter", // 188
    "MAIN", // 189
    "AUDIO", // 190
    "DISPLAY", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECT", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197
    "AM AGC", // 198
    "FM deemphasis", // 199
    "Small", // 200
    "Large", // 201
    "All", // 202
    "Fast PS", // 203
    "Default", // 204
    "Mute screen on\nXDRGTK connection", // 205
    "FMSI stereo\nimprovement", // 206
    "Function only available\non TEF6687/6689!", // 207
    "Function not available\non selected skin!", // 208
    "Begin scanning\nmemory channels", // 209
    "Stop scanning\nmemory channels", // 210
    "Wait time", // 211
    "Start DX scanning", // 212
    "FM DX Options", // 213
    "Abort! The start channel\nis marked as skipped.", // 214
    "Auto sort AF", // 215
    "Memory channels", // 216
    "Exclude", // 217
    "Only", // 218
    "Auto cancel scan", // 219
    "Correct PI", // 220
    "Signal", // 221
    "Mute audio\nwhile scanning", // 222
    "AIR", // 223
    "5 sec. bandbutton press", // 224
    "Power off", // 225
    "Mute screen", // 226
    "Disabled" // 227
  },

  { "Nederlands", // Dutch
    "Rotary richting aangepast", // 1
    "Laat aub de knop los", // 2
    "Scherm gedraaid", // 3
    "Kalibratie analoge meter", // 4
    "Laat knop los indien gereed", // 5
    "encoder ingesteld als optisch", // 6
    "encoder ingesteld als standaard", // 7
    "FM/AM ontvanger", // 8
    "Tuner: !Geen!", // 9
    "Volume", // 10 ***
    "Converter", // 11 ***
    "Lage bandgrens", // 12
    "Hoge bandgrens", // 13
    "FM RF niveau afwijking", // 14
    "Stereo grens", // 15
    "Hoge tonen afval", // 16
    "Hoog afval grens", // 17
    "Laag signaal grens", // 18
    "Helderheid", // 19
    "Audio volume", // 20
    "Converter offset", // 21
    "Band ondergrens", // 22
    "Band bovengrens", // 23
    "Signaalafwijking", // 24
    "Stereo signaalgrens", // 25
    "Hoge tonen afval frequentie", // 26
    "Hoge tonen afval signaalniveau", // 27
    "Laag signaalgrens", // 28
    "Stel helderheid in", // 29
    "Uit", // 30
    "Scherm is bevroren!", // 31
    "Schakel RF+ uit om weer te activeren", // 32
    "UIT", // 33
    "ZOEKEN...", // 34
    "Tuner niet herkend!", // 35
    "AM antenne versterking", // 36
    "FM AGC", // 37
    "Toon RDS fouten", // 38
    "Taal", // 39
    "Kies taal", // 40
    "DRUK OP MODE OM AF TE SLUITEN", // 41
    "Aan", // 42
    "Softmute FM", // 43 ***
    "Softmute AM", // 44 ***
    "Piep op bandeinde", // 45
    "Regio", // 46
    "Europa", // 47
    "Amerika", // 48 ***
    "Toon underscore in RDS", // 49
    "USB mode", // 50 ***
    "Wi-Fi aktief", // 51
    "Configureer Wi-Fi", // 52
    "Verbind met: ", // 53
    "om Wi-Fi in te stellen", // 54
    "Verbinden met Wi-Fi...", // 55
    "MISLUKT!", // 56
    "VERBONDEN!", // 57
    "Stationlist client IP", // 58 ***
    "Toon SW golflengte", // 59
    "RDS filter", // 60 ***
    "Toon PI fouten", // 61
    "Gebruik squelch", // 62
    "Modulatie meter", // 63
    "AM ruis filter", // 64
    "FM ruis filter", // 65
    "Opnieuw geconfigureerd", // 66
    "Audio uitgang", // 67
    "Afstemmen tijdens\nschermbeveiliging", // 68
    "Inverteer scherm", // 69
    "Over deze software", // 70
    "Basis code:", // 71
    "Bijgedragen:", // 72
    "Onbekend", // 73
    "Screensaver opties", // 74
    "Auto uitschakelen", // 75
    "Scherm uit", // 76
    "Thema", // 77
    "Uiterlijk", // 78 ***
    "Gedetecteerde applicaties", // 79
    "Min.", // 80 ***
    "Dynamische\nSPI snelheid", // 81
    "Zoek gevoeligheid", // 82
    "Geen", // 83
    "Software versie", // 84
    "Frequentie font", // 85
    "Auto", // 86
    "Geen AF data", // 87
    "Geen EON data", // 88
    "Geen RT+ data", // 89
    "FM standaard\nstapgrootte", // 90
    "Schermbeveiliging", // 91
    "sec.", // 92
    "DRUK OP BAND OM AF TE SLUITEN", // 93
    "1% helderheid", // 94
    "25% helderheid", // 95
    "50% helderheid", // 96
    "AM RF Level afwijking", // 97
    "Signaalmeter eenheid", // 98
    "Gebruik AF", // 99
    "Selecteer\nFM banden", // 100
    "Selecteer\nAM banden", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Afstemmen tijdens\nschermbeveiliging", // 107
    "Model keuze", // 108
    "Basis (ILI9341)", // 109
    "Portable (ILI9341)", // 110 ***
    "Portable touch (ILI9341)", // 111 ***
    "Titel", // 112
    "Album", // 113 ***
    "Nummer", // 114
    "Artiest", // 115
    "Compositie", // 116
    "Deel", // 117
    "Dirigent", // 118
    "Componist", // 119
    "Band", // 120 ***
    "Opmerking", // 121
    "Genre", // 122 ***
    "Nieuws", // 123
    "Lokaal nieuws", // 124
    "Financiële beurs", // 125
    "Sport", // 126 ***
    "Loterij", // 127
    "Horoscoop", // 128
    "Dagelijkse grap", // 129
    "Gezondheid", // 130
    "Evenement", // 131
    "Scene", // 132 ***
    "Bioscoop", // 133
    "TV", // 134 ***
    "Datum/tijd", // 135
    "Weer", // 136
    "Verkeer", // 137
    "Alarm", // 138 ***
    "Advertentie", // 139
    "Website", // 140 ***
    "Overige", // 141
    "Korte naam", // 142
    "Lange naam", // 143
    "Nu", // 144
    "Straks", // 145
    "Deel", // 146
    "Host", // 147 ***
    "Regiseur", // 148
    "Frequentie", // 149
    "Homepage", // 150 ***
    "Subkanaal", // 151
    "Hotline", // 152 ***
    "Studio telefoon", // 153
    "Telefoon", // 154
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "Email hotline", // 157 ***
    "Email studio", // 158 ***
    "Email", // 159 ***
    "Chat", // 160 ***
    "Chat centrum", // 161
    "Stemming", // 162
    "Stemcentrum", // 163
    "Plaats", // 164
    "Afspraak", // 165
    "Identificatie", // 166
    "Aankoop", // 167
    "Verkrijg data", // 168
    "MW standaard\nstapgrootte", // 169
    "Tangerine", // 170 ***
    "Ocean", // 171 ***
    "Indigo", // 172 ***
    "Batterij weergave", // 173
    "Toon spanning", // 174
    "Toon percentage", // 175
    "RT buffer", // 176
    "Algemeen", // 177
    "Audio", // 178
    "Weergave", // 179
    "RDS instellingen", // 180
    "FM instellingen", // 181
    "AM instellingen", // 182
    "Connectiviteit", // 183
    "MODE OM TERUG TE GAAN", // 184
    "CoChannel Detectie", // 185
    "CoChannel Detectie\ngevoeligheid", // 186
    "CoChannel Detectie\ndrempel", // 187
    "CoChannel Detectie\nteller", // 188
    "ALGEMEEN", // 189
    "GELUID", // 190
    "SCHERM", // 191
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "VERBIND", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197 ***
    "AM AGC", // 198 ***
    "FM deemphasis", // 199 ***
    "Laag", // 200
    "Middel", // 201
    "Alles", // 202
    "Snelle PS", // 203
    "Standaard", // 204
    "Scherm uit bij\nXDRGTK verbinding", // 205
    "FMSI stereo\nverbetering", // 206
    "Alleen beschikbaar op\nTEF6687/6689!", // 207
    "Niet beschikbaar op\ngekozen uiterlijk!", // 208
    "Begin zoeken\ngeheugenkanaal", // 209
    "Eind zoeken\ngeheugenkanaal", // 210
    "Wachttijd", // 211
    "Start DX zoeken", // 212
    "FM DX Opties", // 213
    "Fout! Startkanaal is\ngemarkeerd als skip", // 214
    "Auto AF sorteren", // 215
    "Geheugenkanalen", // 216
    "Uitsluiten", // 217
    "Enkel", // 218
    "Auto afbreken", // 219
    "Correcte PI", // 220
    "Signaal", // 221
    "Geen geluid\ntijdens scannen", // 222
    "AIR", // 223
    "5 sec.\nbandbutton ingedrukt", // 224
    "Uitschakelen", // 225
    "Scherm uit", // 226
    "Geen functie" // 227
  },

  { "Polski", // Polish
    "Kierunek obrotu zmieniony", // 1
    "Zwolnij przycisk", // 2
    "Obrócono ekran", // 3
    "Kalibracja analogowego miernika", // 4
    "Zwolnij przycisk gdy gotowe", // 5
    "wybrano enkoder optyczny", // 6
    "wybrano standardowy enkoder", // 7
    "Odbiornik FM/AM", // 8
    "Tuner: !Brak!", // 9
    "Głośność:", // 10
    "Konwerter:", // 11
    "Dolna granica pasma:", // 12
    "Górna granica pasma:", // 13
    "FM Odchylenie poziomu RF:", // 14
    "Próg Stereo:", // 15
    "Krawędź dolnoprzep..:", // 16
    "Próg dolnoprzepust.:", // 17
    "Próg niskiego sygnału:", // 18
    "Kontrast:", // 19
    "Ustaw głośność", // 20
    "Ustaw odchylenie konwertera", // 21
    "Ustaw dolną granicę pasma", // 22
    "Ustaw górną granicę pasma", // 23
    "Ustaw odchylenie sygnału", // 24
    "Ustaw próg separacji Stereo", // 25
    "Częst. gran. filtra dolnoprzep.", // 26
    "Ustaw próg dolnoprzep.", // 27
    "Ustaw dolną granicę sygnału", // 28
    "Ustaw jasność wyświetlacza", // 29
    "Wył.", // 30
    "Ekran jest wyciszony!", // 31
    "Aby wył. wyciszenie odznacz RF+", // 32
    "WYŁ.", // 33
    "SKANOWANIE...", // 34
    "Nie wykryto tunera", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Pokaż błędy RDS", // 38
    "Język", // 39
    "Wybierz swój język", // 40
    "WCIŚNIJ MODE ABY ZAMKNĄĆ I ZAPISAĆ", // 41
    "Włącz.", // 42
    "Łagodne wyciszanie FM", // 43
    "Łagodne wyciszanie AM", // 44
    "Beep na krawędzi pasma", // 45
    "Region", // 46 ***
    "Europa", // 47
    "Ameryka", // 48 ***
    "Pokaż podkreślenia w RDS", // 49
    "Tryb USB", // 50
    "Wi-Fi aktywne", // 51
    "Konfiguracja Wi-Fi", // 52
    "Połącz z: ", // 53
    "aby skonfigurować Wi-Fi", // 54
    "Próba połączenia z Wi-Fi", // 55
    "BŁĄD.. WiFi wyłączone", // 56
    "POŁĄCZONO!", // 57
    "IP klienta Stationlist", // 58
    "Pokaż długości fal SW", // 59
    "Filtr RDS", // 60
    "Pokaż błędy PI", // 61
    "Użyj blokady szumów", // 62
    "Wskaźnik modulacji", // 63
    "Reduktor szumów AM", // 64
    "Reduktor szumów FM", // 65
    "Załadowano domyślne", // 66
    "Wyjście dźwięku", // 67
    "Stroj. gdy ekran wył.", // 68
    "Odwróć kolory wyświetlacza", // 69
    "O oprogramowaniu", // 70
    "Główny kod:", // 71
    "Współtwórcy:", // 72
    "Nieznany", // 73
    "Opcje wygaszacza", // 74
    "Wyłącznik czasowy", // 75
    "Wyłącz ekran", // 76
    "Motyw", // 77
    "Skórka", // 78 ***
    "Wykryte aplikacje", // 79
    "Min.", // 80 ***
    "Dynam. prędkość SPI", // 81
    "Czułość skanowania", // 82
    "BRAK", // 83
    "Wersja oprogramowania", // 84
    "Czcionka częstotliwości", // 85
    "Auto", // 86
    "AF niedostępny", // 87
    "EON niedostępny", // 88
    "RT+ niedostępny", // 89
    "Minimalny krok FM", // 90
    "Wygaszacz ekranu", // 91
    "Sek", // 92
    "NACIŚNIJ BAND ABY ZAMKNĄĆ", // 93
    "1% jasności", // 94
    "25% jasności", // 95
    "50% jasności", // 96
    "Odchylenie poziomu RF AM", // 97
    "Jednostka sygnału", // 98
    "Używaj AF", // 99
    "Wybierz pasmo FM", // 100
    "Wybierz pasmo AM", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Stroj. gdy ekran wył.", // 107
    "Wybór modelu", // 108
    "Podstawowy (ILI9341)", // 109
    "Przenośny (ILI9341)", // 110
    "Przenoś. dotyk. (ILI9341)", // 111
    "Tytuł", // 112
    "Album", // 113 ***
    "Ścieżka", // 114
    "Wykonawca", // 115
    "Kompozycja", // 116
    "Ruch", // 117
    "Dyrygent", // 118
    "Kompozytor", // 119
    "Grupa", // 120
    "Komentarz", // 121
    "Gatunek", // 122
    "Wiadomości", // 123
    "Lokalne wiadomości", // 124
    "Giełda", // 125
    "Sport", // 126 ***
    "Loteria", // 127
    "Horoskop", // 128
    "Codzienny zwrot", // 129
    "Zdrowie", // 130
    "Wydarzenie", // 131
    "Scena", // 132
    "Kino", // 133
    "TV", // 134 ***
    "Data/Godzina", // 135
    "Pogoda", // 136
    "Wiadom. drogowe", // 137
    "Alarm", // 138 ***
    "Reklama", // 139
    "Strona internet.", // 140
    "Inne", // 141
    "Krótki PS", // 142
    "Długi PS", // 143
    "Teraz", // 144
    "Następnie", // 145
    "Część", // 146
    "Prowadzący", // 147
    "Wydawca", // 148
    "Częstotliwość", // 149
    "Strona domowa", // 150
    "Podkanał", // 151
    "Gorąca linia", // 152
    "Telefon do studia", // 153
    "Telefon", // 154
    "SMS do studia", // 155
    "SMS", // 156 ***
    "Email do gorącej linii", // 157
    "Email do studia", // 158
    "Email", // 159 ***
    "Czat", // 160
    "Centrum czatu", // 161
    "Pytanie do głosowania", // 162
    "Centrum głosowania", // 163
    "Miejsce", // 164
    "Spotkanie", // 165
    "Identyfikator", // 166
    "Zakup", // 167
    "Pobierz dane", // 168
    "Domyślny krok MW", // 169
    "Mandarynka", // 170 ***
    "Ocean", // 171 ***
    "Indygo", // 172 ***
    "Opcje baterii", // 173
    "Pokaż napięcie", // 174
    "Pokaż procent naład.", // 175
    "Buforowanie RT", // 176
    "Główne ustawienia", // 177
    "Ustawienia dźwięku", // 178
    "Ustawienia wyświetlacza", // 179
    "Ustawienia RDS", // 180
    "Ustawienia FM", // 181
    "Ustawienia AM", // 182
    "Łączność", // 183
    "NACIŚNIJ MODE ABY WRÓCIĆ", // 184
    "Detek. międzykanałowy AM", // 185
    "Czułość detek. międzykanał.", // 186
    "Próg detek. międzykanałowego AM", // 187
    "Licznik detek. międzykanał.", // 188
    "GŁÓWNE", // 189
    "DŹWIĘK", // 190
    "WYŚWIETLACZ", // 191
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "ŁĄCZNOŚĆ", // 195
    "TRYB DX", // 196
    "Identyfikator Stationlist", // 197
    "Tłumik ant. AM", // 198
    "Deemfaza FM", // 199
    "Małe", // 200
    "Duże", // 201
    "Wszystkie", // 202
    "Szybki PS", // 203
    "Domyslny", // 204
    "Wylacz ekran gdy\npołączony z XDR-GTK", // 205
    "Ulepszenie \nstereo FMSI", // 206
    "Funkcja dostępna tylko\nna TEF6687/6689!", // 207
    "Funkcja niedostępna\nz wybranym motywem!", // 208
    "Początkowy kanał", // 209
    "Końcowy kanał", // 210
    "Czas oczekiwania", // 211
    "Rozpocznij skanowanie DX", // 212
    "Opcje FM DX", // 213
    "Błąd! Początkowy kanał\njest pominięty.", // 214
    "Automat. sortowanie AF", // 215
    "Kanały pamięci", // 216
    "Wyklucz", // 217
    "Tylko", // 218
    "Automatyczne\nanulowanie skanowania", // 219
    "Poprawne PI", // 220
    "Sygnał", // 221
    "Wycisz dźwięk\npodczas skanowania", // 222
    "AIR", // 223
    "5 sek. naciśnięcie przyc. BAND", // 224
    "Wyłącz", // 225
    "Wyłącz ekran", // 226
    "Wyłączone" // 227
  },

  { "Hrvatski", // Croatian
    "Smjer enkodera promij.", // 1
    "Otpustite gumb", // 2
    "Zaslon je okrenut", // 3
    "Kalibracija analog. mjerača", // 4
    "Otpustite gumb", // 5
    "Optički enkoder postav.", // 6
    "Standardni enkoder postav.", // 7
    "FM/AM prijemnik", // 8
    "Prijemnik: !Nije pronađen!", // 9
    "Pomak glasnoće:", // 10
    "Pomak konvertera:", // 11
    "Donja granica opsega:", // 12
    "Gornja granica opsega:", // 13
    "FM pomak RF razine:", // 14
    "Razina stereo signala:", // 15
    "Granična frekvencija:", // 16
    "Razina granične frekv.:", // 17
    "Donja granica za signal:", // 18
    "Svjetlina:", // 19
    "Pomak glasnoće", // 20
    "Pomak konvertera", // 21
    "Donja granica frekv. opsega", // 22
    "Gornja granica frekv. opsega", // 23
    "Pomak signala", // 24
    "Razina stereo signala", // 25
    "Granična frekvencija", // 26
    "Razina granične frekv.", // 27
    "Donja granica za signal", // 28
    "Svjetlina zaslona", // 29
    "Isključeno", // 30
    "Zaslon je isključen!", // 31
    "Da biste uključili zaslon poništite kvadratić RF+", // 32
    "ISK.", // 33
    "SKENIRANJE...", // 34
    "Prijemnik nije pronađen", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Prikaži RDS pogreške", // 38
    "Jezik", // 39
    "Odaberite jezik", // 40
    "PRITISNITE MODE ZA IZLAZ I SPREMANJE", // 41
    "Uključeno", // 42
    "Softmute FM", // 43 ***
    "Softmute AM", // 44 ***
    "Beep na rubu frekv. opsega", // 45
    "Regija", // 46
    "Europa", // 47
    "Amerika", // 48
    "Prikaži donju crtu u RDS-u", // 49
    "Način rada USB-a", // 50
    "Wi-Fi", // 51
    "Wi-Fi postavke", // 52
    "Spojite se na: ", // 53
    "kako biste konfigurirali Wi-Fi", // 54
    "Spajanje na Wi-Fi mrežu..", // 55
    "NEUSPJEŠNO.. Wi-Fi onemogućen", // 56
    "SPOJENO!", // 57
    "IP klijenta StationList", // 58
    "Prikaži valnu duljinu KV-a", // 59
    "RDS filter", // 60
    "Prikaži PI greške", // 61
    "Prikaži squelch", // 62
    "Mjerač modulacije", // 63
    "AM prigušivač šuma", // 64
    "FM prigušivač šuma", // 65
    "Zadane postavke učitane", // 66
    "Audio izlaz", // 67
    "Omogući podešavanje\n tijekom čuvara zaslona", // 68
    "Invertiraj boju zaslona", // 69
    "O softveru", // 70
    "Glavni izvorni kod:", // 71
    "Suradnici:", // 72
    "Nepoznato", // 73
    "Opcije čuvara zaslona", // 74
    "Time-out timer", // 75
    "Zaslon isključiti", // 76
    "Tema dizajna", // 77
    "Skin", // 78 ***
    "Otkrivene aplikacije", // 79
    "Min.", // 80
    "Dinamička SPI brzina", // 81
    "Osjetljivost skeniranja", // 82
    "NEMA", // 83
    "Verzija softvera", // 84
    "Font frekvencije", // 85
    "Auto", // 86
    "AF nedostupan", // 87
    "EON nedostupan", // 88
    "RT+ nedostupan", // 89
    "FM min korak", // 90
    "Čuvar zaslona", // 91
    "Sek", // 92
    "PRITISNITE BAND ZA IZLAZ", // 93
    "1% svjetlina", // 94
    "25% svjetlina", // 95
    "50% svjetlina", // 96
    "AM pomak RF razine:", // 97
    "Jedinica mjerača signala:", // 98
    "Koristi AF:", // 99
    "FM opseg:", // 100
    "AM opseg:", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Okretanje dok je zaslon isključen", // 107
    "Selektor modela", // 108
    "Base (ILI9341)", // 109
    "Portable (ILI9341)", // 110
    "Portable touch (ILI9341)", // 111
    "Naslov", // 112
    "Album", // 113
    "Pjesma", // 114
    "Izvođač", // 115
    "Kompozicija", // 116
    "Pokret", // 117
    "Dirigent", // 118
    "Skladatelj", // 119
    "Bend", // 120
    "Komentar", // 121
    "Žanr", // 122
    "Vijesti", // 123
    "Lokalne vijesti", // 124
    "Burza", // 125
    "Sport", // 126
    "Lutrija", // 127
    "Horoskop", // 128
    "Savjet dana", // 129
    "Zdravlje", // 130
    "Događanja", // 131
    "Scena", // 132
    "Kino", // 133
    "TV", // 134
    "Datum/vrijeme", // 135
    "Vremenska prognoza", // 136
    "Promet", // 137
    "Alarm", // 138
    "Reklama", // 139
    "Web stranica", // 140
    "Ostalo", // 141
    "Kratki PS", // 142
    "Dugi PS", // 143
    "Sada", // 144
    "Sljedi", // 145
    "Dio", // 146
    "Voditelj", // 147
    "Urednik", // 148
    "Frekvencija", // 149
    "Web stranica", // 150
    "Potkanal", // 151
    "Hotline", // 152
    "Telefon studija", // 153
    "Telefon", // 154
    "SMS studio", // 155
    "SMS", // 156
    "Email hotline", // 157
    "Email studija", // 158
    "Email", // 159
    "Chat", // 160
    "Chat centar", // 161
    "Pitanje za glasanje", // 162
    "Centar za glasanje", // 163
    "Mjesto", // 164
    "Ugovoreni sastanak", // 165
    "Identifikator", // 166
    "Kupnja", // 167
    "Primi podatke", // 168
    "MW zadana veličina koraka", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Postavke za bateriju", // 173
    "Prikaži napon", // 174
    "Prikaži postotak", // 175
    "RT pufer", // 176
    "Glavno", // 177
    "Zvuk", // 178
    "Zaslon", // 179
    "RDS postavke", // 180
    "FM postavke", // 181
    "AM postavke", // 182
    "Povezivost", // 183
    "PRITISNITE MODE ZA POVRATAK", // 184
    "AM CoChannelDet", // 185
    "CoChannelDet osjetljivost", // 186
    "AM CoChannelDet razina", // 187
    "CoChannelDet brojač", // 188
    "GLAVNO", // 189
    "ZVUK", // 190
    "ZASLON", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "SPOJI", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Malo", // 200
    "Veliko", // 201
    "Sve", // 202
    "Brzi PS", // 203
    "Zadano", // 204
    "Isključi zaslon\ntijekom veze XDRGTK-om", // 205
    "FMSI stereo\nimprovement", // 206
    "Function only available\non TEF6687/6689!", // 207
    "Function not available\non selected skin!", // 208
    "Begin scanning\nmemory channels", // 209
    "Stop scanning\nmemory channels", // 210
    "Wait time", // 211
    "Start DX scanning", // 212
    "FM DX Options", // 213
    "Abort! The start channel\nis marked as skipped.", // 214
    "Autom. sortiranje AF-a", // 215
    "Memory channels", // 216
    "Exclude", // 217
    "Only", // 218
    "Auto cancel scan", // 219
    "Correct PI", // 220
    "Signal", // 221
    "Mute audio\nwhile scanning", // 222
    "AIR", // 223
    "5 sec. bandbutton press", // 224
    "Power off", // 225
    "Mute screen", // 226
    "Disabled" // 227
  },

  { "Ελληνικά", // Greek
    "Η διεύθυνση του ρότορα\nάλλαξε", // 1
    "Ελευθερώστε το πλήκτρο", // 2
    "Η οθόνη αναποδογύρισε", // 3
    "Βαθμονόμηση\nαναλογικού μετρητή", // 4
    "Αφήστε το πλήκτρο\nόταν είστε έτοιμοι", // 5
    "ο κωδικοποιητής ρυθμίστηκε\nσε οπτικός", // 6
    "ο κωδικοποιητής ρυθμίστηκε\nσε στάνταρ", // 7
    "Δέκτης FM/AM", // 8
    "Tuner: !Κανένα!", // 9
    "Ένταση ήχου:", // 10
    "Μετατροπέας:", // 11
    "Κάτω όριο μπάντας:", // 12
    "Άνω όριο μπάντας:", // 13
    "FM Ολίσθηση\nεπιπέδου RF:", // 14
    "Κατώφλι στέρεο:", // 15
    "Όριο υψηλής αποκοπής:", // 16
    "Κατώφλι υψηλής\nαποκοπής:", // 17
    "Κατώφλι χαμηλού\nεπιπέδου:", // 18
    "Αντίθεση:", // 19
    "Ορισμός έντασης ήχου", // 20
    "Ολίσθηση (offset) κωδικοποιητή", // 21
    "Κάτω όριο μπάντας", // 22
    "Άνω όριο μπάντας", // 23
    "Επίπεδο ολίσθησης", // 24
    "Κατώφλι διαχωρισμού\nστέρεο", // 25
    "Συχνότητα υψηλής αποκοπής", // 26
    "Κατώφλι υψηλής\nαποκοπής", // 27
    "Κατώφλι χαμηλού\nεπιπέδου", // 28
    "Φωτεινότητα οθόνης", // 29
    "Ανενεργό", // 30
    "Οθόνη σε σίγαση!", // 31
    "Για επαναφορά ήχου\nτσεκάρετε το RF+", // 32
    "Εκτός", // 33
    "ΑΝΙΧΝΕΥΣΗ...", // 34
    "Το tuner δεν εντοπίστηκε", // 35
    "Κέρδος κεραίας AM", // 36
    "FM AGC", // 37
    "Περιθώριο σφαλμάτων\nRDS", // 38
    "Γλώσσα", // 39
    "Επιλογή γλώσσας", // 40
    "ΠΙΕΣΤΕ MODE ΓΙΑ ΕΞΟΔΟ & ΑΠΟΘΗΚΕΥΣΗ", // 41
    "Ενεργό", // 42
    "Ήπια σίγαση FM", // 43
    "Ήπια σίγαση AM", // 44
    "Ηχητικό σήμα στο όριο\nμπάντας", // 45
    "Περιοχή", // 46
    "Ευρώπη", // 47
    "Αμερική", // 48
    "Εμφάνιση κάτω παύλας\nστο RDS", // 49
    "USB λειτουργία", // 50
    "Wi-Fi ενεργό", // 51
    "Ρύθμιση Wi-Fi", // 52
    "Συνδεθείτε στο: ", // 53
    "για ρύθμιση του WiFi", // 54
    "Προσπάθεια σύνδεσης\nστο WiFi", // 55
    "ΑΠΟΤΥΧΙΑ..\nWiFi ανενεργό", // 56
    "ΣΕ ΣΥΝΔΕΣΗ!", // 57
    "IP πελάτη λίστας σταθμών", // 58
    "Εμφάνιση μήκους\nκύματος SW", // 59
    "Φίλτρο RDS", // 60
    "Εμφάνιση σφαλμάτων PI", // 61
    "Χρήση squelch", // 62
    "Μετρητής διαμόρφωσης", // 63
    "Απαλοιφή θορύβου AM", // 64
    "Απαλοιφή θορύβου FM", // 65
    "Οι προεπιλογές φορτώθηκαν", // 66
    "Έξοδος ήχου", // 67
    "Συντονισμός σε\nπροστασία οθόνης", // 68
    "Αναστροφή χρωμάτων οθόνης", // 69
    "Πληροφορίες λογισμικού", // 70
    "Κύριος κώδικας:", // 71
    "Συνεργάτες:", // 72
    "Άγνωστο", // 73
    "Επιλογές προστασίας\nοθόνης", // 74
    "Χρονοδιακόπτης λήξης", // 75
    "Οθόνη σβηστή", // 76
    "Θέμα", // 77
    "Γραφικό\nπεριβάλλον", // 78 ***
    "Εντοπισμένες εφαρμογές", // 79
    "Λεπτά", // 80
    "Δυναμική ταχύτητα\nSPI", // 81
    "Ευαισθησία\nανίχνευσης", // 82
    "KAMIA", // 83
    "Έκδοση λογισμικού", // 84
    "Γραμματοσειρά\nσυχνότητας", // 85
    "Αυτόματο", // 86
    "Μη διαθέσιμο AF", // 87
    "Μη διαθέσιμο EON", // 88
    "Μη διαθέσιμο RT+", // 89
    "Μέγεθος βήματος FM", // 90
    "Προστασία οθόνης", // 91
    "Δευτ.", // 92
    "ΠΙΕΣΤΕ BAND ΓΙΑ ΚΛΕΙΣΙΜΟ", // 93
    "1% φωτεινή", // 94
    "25% φωτεινή", // 95
    "50% φωτεινή", // 96
    "AM Ολίσθηση\nεπιπέδου RF:", // 97
    "Μονάδα μέτρησης\nσήματος:", // 98
    "Χρήση AF:", // 99
    "Επιλογή μπάντας FM:", // 100
    "Επιλογή μπάντας AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Περιστροφή με οθόνη\nσβηστή", // 107
    "Επιλογή μοντέλου", // 108
    "Βασικό (ILI9341)", // 109
    "Φορητό (ILI9341)", // 110
    "Φορητό αφής (ILI9341)", // 111
    "Τίτλος", // 112
    "Άλμπουμ", // 113
    "Κομμάτι", // 114
    "Καλλιτέχνης", // 115
    "Σύνθεση", // 116
    "Κίνηση", // 117
    "Μαέστρος", // 118
    "Συνθέτης", // 119
    "Μπάντα", // 120
    "Σχόλιο", // 121
    "Είδος", // 122
    "Ειδήσεις", // 123
    "Τοπικές ειδήσεις", // 124
    "Χρηματιστήριο", // 125
    "Αθλητικά", // 126
    "Λοταρία", // 127
    "Ωροσκόπιο", // 128
    "Καθημερινές ασχολίες", // 129
    "Υγεία", // 130
    "Γεγονός", // 131
    "Σκηνή", // 132
    "Σινεμά", // 133
    "TV", // 134 ***
    "Ημερομηνία/ώρα", // 135
    "Καιρός", // 136
    "Κυκλοφορία", // 137
    "Συναγερμός", // 138
    "Διαφήμιση", // 139
    "Ιστότοπος", // 140
    "Άλλο", // 141
    "Σύντομο PS", // 142
    "Μακρύ PS", // 143
    "Τώρα", // 144
    "Στη συνέχεια", // 145
    "Μέρος", // 146
    "Παρουσιαστής", // 147
    "Συντάκτης", // 148
    "Συχνότητα", // 149
    "Ιστοσελίδα", // 150
    "Υποφέρουσα", // 151
    "Τηλ. επικοινωνίας", // 152
    "Τηλ. στούντιο", // 153
    "Τηλέφωνο", // 154
    "SMS στούντιο", // 155
    "SMS", // 156 ***
    "Email επικοινωνίας", // 157
    "Email στούντιο", // 158
    "Email", // 159
    "Chat", // 160
    "Κέντρο chat", // 161
    "Ερώτηση ψηφοφορίας", // 162
    "Κέντρο ψηφοφορίας", // 163
    "Τοποθεσία", // 164
    "Ραντεβού", // 165
    "Αναγνωριστικό", // 166
    "Αγορά", // 167
    "Λήψη δεδομένων", // 168
    "Προεπιλεγμένο μέγεθος\nβήματος ΑΜ", // 169
    "Μανταρινί", // 170
    "Ωκεανός", // 171
    "Ινδικό", // 172
    "Επιλογές μπαταρίας", // 173
    "Εμφάνιση τάσης", // 174
    "Εμφάνιση ποσοστού", // 175
    "RT προφόρτωση", // 176
    "Βασικές ρυθμίσεις", // 177
    "Ρυθμίσεις ήχου", // 178
    "Ρυθμίσεις εμφάνισης", // 179
    "Ρυθμίσεις RDS", // 180
    "Ρυθμίσεις FM", // 181
    "Ρυθμίσεις AM", // 182
    "Συνδεσιμότητα", // 183
    "ΠΙΕΣΤΕ MODE ΓΙΑ ΕΠΙΣΤΡΟΦΗ", // 184
    "Εντοπισμός\nομοκαναλικού AM", // 185
    "Ευαισθησία\nομοκαναλικού AM", // 186
    "Κατώφλι\nομοκαναλικού AM", // 187
    "Μετρητής\nομοκαναλικού AM", // 188
    "ΒΑΣΙΚΕΣ", // 189
    "ΗΧΟΣ", // 190
    "ΕΜΦΑΝΙΣΗ", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "ΣΥΝΔΕΣΗ", // 195
    "DX MODE", // 196
    "ID λίστας σταθμών", // 197
    "AM εξασθένιση", // 198
    "FM αποέμφαση", // 199
    "Μικρό", // 200
    "Μεγάλο", // 201
    "Όλα", // 202
    "Γρήγορο PS", // 203
    "Προεπιλογή", // 204
    "Μαύρη οθόνη σε\nσύνδεση XDRGTK", // 205
    "FMSI βελτίωση\nήχου στέρεο", // 206
    "Λειτουργία διαθέσιμη\nμόνο στα TEF6687/6689!", // 207
    "Λειτουργία μη διαθέσιμη\nσε αυτή την εμφάνιση!", // 208
    "Εκκίνηση ανίχνευσης\nκαναλιών μνήμης", // 209
    "Διακοπή ανίχνευσης\nκαναλιών μνήμης", // 210
    "Χρόνος αναμονής", // 211
    "Εκκίνηση DX ανίχνευσης", // 212
    "Επιλογές FM DX", // 213
    "Ματαίωση! Λείπει\nτο κανάλι εκκίνησης.", // 214
    "Αυτόματη ταξινόμηση\nAF", // 215
    "Κανάλια μνήμης", // 216
    "Εξαίρεση", // 217
    "Μόνο", // 218
    "Αυτόματη ακύρωση\nανίχνευσης", // 219
    "Σωστό PI", // 220
    "Σήμα", // 221
    "Σίγαση ήχου\nκατά την ανίχνευση", // 222
    "AIR", // 223
    "Πιέση πλήκτρου\nμπάντας 5 δευτ.", // 224
    "Σβήσιμο", // 225
    "Σβήσιμο οθόνης", // 226
    "Ανενεργό" // 227
  },

  { "Română", // Romanian
    "Direcția rotirii schimbată", // 1
    "Eliberați butonul", // 2
    "Ecran întors", // 3
    "Calibrați instrumentul analog", // 4
    "Eliberați butonul când este gata", // 5
    "encoderul setat optic", // 6
    "encoderul setat standard", // 7
    "Receptor FM/AM", // 8
    "Lipsă: !Tuner!", // 9
    "Volum", // 10
    "Convertor", // 11
    "Marginea de jos a benzii", // 12
    "Marginea de sus a benzii", // 13
    "Calibrare nivel RF FM", // 14
    "Pragul ptr Stereo", // 15
    "Limită tăiere înalte", // 16
    "Prag tăiere înalte", // 17
    "Prag nivel joase", // 18
    "Contrast", // 19
    "Setare volum", // 20
    "Setare decalaj convertor", // 21
    "Setarea limitei de jos a benzii", // 22
    "Setarea limitei de sus a benzii", // 23
    "Setare nivel decalaj", // 24
    "Setarea pragului sep. Stereo ", // 25
    "Setare tăiere frecv. înalte ", // 26
    "Setare prag tăiere înalte", // 27
    "Setarea pragului la joase", // 28
    "Setare luminozitate ecran", // 29
    "Oprit", // 30
    "Ecran blocat!", // 31
    "ptr deblocare debifati RF+", // 32
    "Oprit", // 33
    "SCANEZ...", // 34
    "Tunerul nu este prezent", // 35
    "Reglare nivel antenă AM", // 36
    "FM AGC", // 37
    "Arată erorile RDS", // 38
    "Limbă", // 39
    "Alegeți Limba", // 40
    "Apasați MODE ptr MEMORARE și ieșire", // 41
    "Pornit", // 42
    "lipsă zgomot FM", // 43
    "lipsă zgomot AM", // 44
    "Beep la capătul benzii", // 45
    "Regiune", // 46
    "Europa", // 47
    "America", // 48
    "Afișează subliniere la RDS", // 49
    "Mod USB", // 50
    "Wi-Fi activ", // 51
    "Configurare Wi-Fi", // 52
    "Conectare la: ", // 53
    "ptr configurare Wi-Fi", // 54
    "Incerc conectarea la Wi-Fi", // 55
    "Fară succes!", // 56
    "Conectat!", // 57
    "Listă adrese IP", // 58
    "Arată lungimea de undă SW", // 59
    "Filtru RDS", // 60
    "Arată erorile PI", // 61
    "folosește squelch", // 62
    "Contor modulație", // 63
    "Eliminator de zgomot AM", // 64
    "Eliminator de zgomot FM", // 65
    "Revenire la setările de fabrică", // 66
    "ieșire Audio", // 67
    "Permite reglarea in timp ce ecranul este oprit", // 68
    "Ecran inversat", // 69
    "Despre software", // 70
    "cod principal:", // 71
    "Contribuitori:", // 72
    "Necunoscut", // 73
    "Opțiuni economizor ecran", // 74
    "Pauză temporizator", // 75
    "Ecran oprit", // 76
    "Temă", // 77
    "Mod vizualizare", // 78
    "Aplicații detectate", // 79
    "Min.", // 80
    "Viteză SPI dinamică", // 81
    "Sensibilitatea scanării", // 82
    "NICI UNUL", // 83
    " versiune Software", // 84
    "Font Frecvență", // 85
    "Auto", // 86
    "AF nu este disponibil", // 87
    "EON nu este disponibil", // 88
    "RT+ nu este disponibil", // 89
    "Mărime pași FM", // 90
    "Screensaver", // 91
    "Sec", // 92
    "Apăsați BAND pentru inchidere", // 93
    "luminozitate 1%", // 94
    "luminozitate 25%", // 95
    "luminozitate 50%", // 96
    "Decalaj de nivel AM RF", // 97
    "unitați S-metru", // 98
    "folosești AF", // 99
    "Selectare banda FM", // 100
    "Selectare banda AM", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotire când ecranul este oprit", // 107
    "selectare Model", // 108
    "Bază (ILI9341)", // 109
    "Portabil (ILI9341)", // 110
    "Portabil touch (ILI9341)", // 111
    "Titlu", // 112
    "Album", // 113
    "Bandă", // 114
    "Artist", // 115
    "Compoziție", // 116
    "Mișcare", // 117
    "Dirijor", // 118
    "Compozitor", // 119
    "Formație", // 120
    "Comentarii", // 121
    "Gen", // 122
    "Știri", // 123
    "Știri Locale", // 124
    "Bursa de Valori", // 125
    "Sport", // 126
    "Loto", // 127
    "Horoscop", // 128
    "Info zilnice", // 129
    "Sănătate", // 130
    "Evenimente", // 131
    "Teatru", // 132
    "Cinema", // 133
    "TV", // 134
    "Data/ora", // 135
    "Meteo", // 136
    "Trafic", // 137
    "Alarmă", // 138
    "Reclame", // 139
    "Website", // 140
    "Altele", // 141
    "PS scurt", // 142
    "PS lung", // 143
    "Acum", // 144
    "Urmează", // 145
    "Parte", // 146
    "Gazdă", // 147
    "Editor", // 148
    "Frecvența", // 149
    "Pagina start", // 150
    "Sub canal", // 151
    "Linia fierbinte", // 152
    "Telefon Studio", // 153
    "Telefon", // 154
    "SMS studio", // 155
    "SMS", // 156
    "Email Linie fierbinte", // 157
    "Email studio", // 158
    "Email", // 159
    "Discuții", // 160
    "Centru discuții", // 161
    "Intrebare la vot", // 162
    "Centru votare", // 163
    "Loc", // 164
    "Intâlnire", // 165
    "Identificare", // 166
    "Cumpără", // 167
    "Preiau date", // 168
    "pași MW impliciți", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Opțiuni Baterie", // 173
    "Arată tensiunea", // 174
    "Arată procente", // 175
    "porțiune RT", // 176
    "Setări de bază", // 177
    "Setări Audio", // 178
    "Setări ecran", // 179
    "Setări RDS", // 180
    "Setări FM", // 181
    "Setări AM ", // 182
    "Conectivitate", // 183
    "Apasă MODE ptr revenire", // 184
    "Detector CoChannel", // 185
    "Detecție sensibilitate CoChannel ", // 186
    "Detecție prag CoChannel", // 187
    "Detector contor CoChannel", // 188
    "PRINCIPAL", // 189
    "AUDIO", // 190
    "ECRAN", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONECTARE", // 195
    "MOD DX", // 196
    "Listă ID posturi", // 197
    "AGC AM", // 198
    "FM deemphasis", // 199
    "Mic", // 200
    "Mare", // 201
    "Tot", // 202
    "PS rapid", // 203
    "Mod implicit", // 204
    "Ecran oprit, conectat la XDRGTK", // 205
    "FMSI stereo îmbunătățit", // 206
    "Funcție activă doar la\nTEF6687/6689!", // 207
    "Funcție indisponibilă\nla acest skin!", // 208
    "Scanare începută\nmemorare posturi", // 209
    "Scanare terminată\nmemorare posturi", // 210
    "Așteaptă", // 211
    "Începe scanarea DX", // 212
    "FM DX Opțiuni", // 213
    "Terminat! Programul de pornire\neste ignorat.", // 214
    "Sortare automată AF", // 215
    "Memorare programe", // 216
    "Exclude", // 217
    "Doar", // 218
    "Auto oprire scanare", // 219
    "PI corect", // 220
    "Semnal", // 221
    "Audio oprit\ncând scanează", // 222
    "AIR", // 223
    "Apasă 5sec. butonul bandă", // 224
    "Oprit", // 225
    "Ecran oprit", // 226
    "Dezactivat" // 227
  },

  { "Deutsch", // German
    "Drehrichtung geändert", // 1
    "Bitte Taste loslassen", // 2
    "Bildschirm gedreht", // 3
    "Analogmeter kalibrieren", // 4
    "Taste loslassen wenn bereit", // 5
    "Drehgeber optisch", // 6
    "Drehgeber standard", // 7
    "UKW/AM Empfänger", // 8
    "!KEIN! Tuner", // 9
    "Lautstärke:", // 10
    "Konverter:", // 11
    "Unteres Bandende:", // 12
    "Oberes Bandende:", // 13
    "FM RF-Pegeloffset:", // 14
    "Stereotrennschwelle:", // 15
    "Tiefpass Eckfrequenz:", // 16
    "Tiefpass Schwelle:", // 17
    "Low-Level-Schwelle:", // 18
    "Kontrast:", // 19
    "Lautstärke", // 20
    "Konverteroffset", // 21
    "Unteres Bandende", // 22
    "Oberes Bandende", // 23
    "Pegeloffset", // 24
    "Stereotrennschwelle", // 25
    "Tiefpass Eckfrequenz", // 26
    "Tiefpass Schwelle", // 27
    "Low-Level-Schwelle", // 28
    "Anzeigehelligkeit", // 29
    "Aus", // 30
    "Bildschirm abgeschaltet!", // 31
    "RF+ abwählen, um einzuschalten", // 32
    "AUS", // 33
    "SCANNE...", // 34
    "Tuner nicht erkannt", // 35
    "AM Antennengewinn", // 36
    "FM AGC", // 37
    "Zeige RDS Fehler", // 38
    "Sprache", // 39
    "Sprache wählen", // 40
    "MODE drücken zum Beenden & Sichern", // 41
    "Ein", // 42
    "Sanfte\nStummschaltung UKW", // 43
    "Sanfte\nStummschaltung AM", // 44
    "Piepston am Bandende", // 45
    "Region", // 46
    "Europa", // 47
    "Amerika", // 48
    "Zeige Unterstrich im RDS", // 49
    "USB-Modus", // 50
    "WLAN aktiv", // 51
    "WLAN konfigurieren", // 52
    "Verbinde mit:", // 53
    "um WLAN einzustellen", // 54
    "Verbindungsversuch", // 55
    "FEHLER!", // 56
    "VERBUNDEN!", // 57
    "Stationlist Rechner IP", // 58
    "KW-Wellenlänge anzeigen", // 59
    "RDS-Filter", // 60
    "Zeige PI Fehler", // 61
    "Verwende Rauschsperre", // 62
    "Modulationspegel", // 63
    "Rauschunterdrückung", // 64
    "Rauschunterdrückung", // 65
    "Werkseinstellungen\nwurden geladen", // 66
    "Audioausgabe", // 67
    "Tunen bei\nBildschirmschoner erlauben", // 68
    "Anzeigefarben umkehren", // 69
    "Über diese Software", // 70
    "Hauptcode:", // 71
    "Mitwirkende:", // 72
    "Unbekannt", // 73
    "Bildschirmschoneroptionen", // 74
    "Abschaltzeit", // 75
    "Bildschirm aus", // 76
    "Thema", // 77
    "Skin", // 78 ***
    "Erkannte Applikationen", // 79
    "Min.", // 80
    "Dynamische \nSPI-Geschwindigkeit", // 81
    "Scanempfindlichkeit", // 82
    "KEINE", // 83
    "Softwareversion", // 84
    "Frequenz-Schriftart", // 85 ***
    "Auto", // 86
    "Keine AF verfügbar", // 87
    "Kein EON verfügbar", // 88
    "Kein RT+ verfügbar", // 89
    "UKW\nStandard-Schrittweite", // 90
    "Bildschirmschoner", // 91
    "Sek", // 92
    "ZUM SCHLIEßEN BAND DRÜCKEN", // 93
    "1% Helligkeit", // 94
    "25% Helligkeit", // 95
    "50% Helligkeit", // 96
    "RF Pegeloffset", // 97
    "Einheit Signalpegel", // 98
    "Verwende AF", // 99
    "Wähle UKW Band", // 100
    "Wähle AM Band", // 101
    "LW", // 102
    "MW", // 103
    "KW", // 104
    "UKW", // 105
    "OIRT", // 106
    "Tunen bei Bildschirm aus", // 107
    "Modell auswählen", // 108
    "Basismodell (ILI9341)", // 109
    "Portabel (ILI9341)", // 110
    "Portabel Touch (ILI9341)", // 111
    "Titel", // 112
    "Album", // 113
    "Track", // 114
    "Künstler", // 115
    "Komposition", // 116
    "Satz", // 117
    "Dirigent", // 118
    "Komponist", // 119
    "Band", // 120
    "Kommentar", // 121
    "Genre", // 122
    "Nachrichten", // 123
    "Lokalnachrichten", // 124
    "Aktienmarkt", // 125
    "Sport", // 126
    "Lotterie", // 127
    "Horoskop", // 128
    "Tagestipp", // 129
    "Gesundheit", // 130
    "Ereignis", // 131
    "Szene", // 132
    "Kino", // 133
    "TV", // 134
    "Tag/Uhrzeit", // 135
    "Wetter", // 136
    "Verkehr", // 137
    "Alarm", // 138
    "Werbung", // 139
    "Website", // 140
    "Info", // 141
    "Kurzes PS", // 142
    "Langes PS", // 143
    "Es läuft", // 144
    "Es folgt", // 145
    "Thema", // 146
    "Am Mikrofon", // 147
    "Redaktion", // 148
    "Frequenz", // 149
    "Homepage", // 150
    "Subchannel", // 151
    "Telefon Hotline", // 152
    "Telefon Studio", // 153
    "Telefon", // 154
    "SMS Studio", // 155
    "SMS", // 156
    "E-Mail Hotline", // 157
    "E-Mail Studio", // 158
    "E-Mail", // 159
    "Chat", // 160
    "Chat-Zentrale", // 161
    "Abstimmung", // 162
    "Abstimmungs-Zentrale", // 163
    "Ort", // 164
    "Termin", // 165
    "Musik-ID", // 166
    "Bezugsquelle", // 167
    "Empfange Daten", // 168
    "MW\nStandardschrittweite", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Akkuoptionen", // 173
    "Spannung anzeigen", // 174
    "Prozente anzeigen", // 175
    "RT puffern", // 176
    "Haupteinstellungen", // 177
    "Audioeinstellungen", // 178
    "Displayeinstellung", // 179
    "RDS Einstellungen", // 180
    "UKW Einstellungen", // 181
    "AM Einstellungen", // 182
    "Netzwerk", // 183
    "DRÜCKE MODE FÜR ZURÜCK", // 184
    "Gleichkanalerkennung", // 185
    "Gleichkanalerkennung\nEmpfindlichkeit", // 186
    "Gleichkanalerkennung\nSchwelle", // 187
    "Gleichkanalerkennung\nZähler", // 188
    "HAUPT", // 189
    "AUDIO", // 190
    "ANZEIGE", // 191
    "RDS", // 192
    "UKW", // 193
    "AM", // 194
    "NETZ", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "Entzerrung auf UKW", // 199
    "Wenig", // 200
    "Viel", // 201
    "Maximal", // 202
    "Schnelles PS", // 203
    "Standard", // 204
    "Display aus bei\nXDRGTK-Verbindung", // 205
    "FMSI Stereo-\nVerbesserung", // 206
    "Funktion nur für\nTEF6687/6689 verfügbar!", // 207
    "Funktion für ausgewählten\nSkin nicht verfügbar!", // 208
    "Starte Scan mit\nSpeicherplatz", // 209
    "Stoppe Scan mit\nSpeicherplatz", // 210
    "Wartezeit", // 211
    "Starte DX Scan", // 212
    "FM DX Optionen", // 213
    "Abbruch! Start-Speicherplatz\nist nicht belegt.", // 214
    "AF Autosortierung", // 215
    "Speicherplätze scannen", // 216
    "Nein", // 217
    "Ja, ausschließlich", // 218
    "Automatisches Scan-Ende", // 219
    "Korrekter PI-Code", // 220
    "Signal", // 221
    "Stumm beim Scannen", // 222
    "AIR", // 223
    "5 Sek. BAND-Knopf drücken", // 224
    "Ausschalten", // 225
    "Bildschirmschoner", // 226
    "Deaktiviert" // 227
  },

  { "Český", // Czech
    "Směr enkodéru byl změněn", // 1
    "Prosím, pusťte tlačítko", // 2
    "Obrazovka otočena", // 3
    "Kalibrace analog. měřiče", // 4
    "Po dokončení pusťte tlačítko", // 5
    "enkodér nastaven na optický", // 6
    "enkodér nastaven na standardní", // 7
    "FM/AM přijímač", // 8
    "Tuner: !ŽÁDNÝ!", // 9
    "Hlasitost:", // 10
    "Konvertor:", // 11
    "Spodek pásma:", // 12
    "Vrch pásma:", // 13
    "FM Offset signálu:", // 14
    "Práh pro stereo:", // 15
    "Práh frekvence zvuku\nk utlumení:", // 16
    "Práh signálu pro utlumení\nvysokých tónů:", // 17
    "Práh nízkého signálu:", // 18
    "Jas:", // 19
    "Hlasitost", // 20
    "Offset frekvence", // 21
    "Spodek pásma", // 22
    "Vrch pásma", // 23
    "Offset signálu", // 24
    "Práh pro stereo", // 25
    "Práh frekvence zvuku k utlumení", // 26
    "Práh signálu pro utlumení výšek", // 27
    "Práh nízkého signálu", // 28
    "Jas", // 29
    "Vyp.", // 30
    "Obrazovka je ztlumena!", // 31
    "Pro spuštění zrušte RF+", // 32
    "VYP.", // 33
    "SKENUJI...", // 34
    "Tuner nedetekován", // 35
    "Zisk AM antény", // 36
    "FM AGC", // 37
    "Zobrazit chyby v RDS", // 38
    "Jazyk", // 39
    "Vyberte jazyk", // 40
    "ZMÁČKNĚTE MODE PRO ULOŽENÍ", // 41
    "Zap.", // 42
    "Softmute FM", // 43 ***
    "Softmute AM", // 44 ***
    "Pípnout na konci pásma", // 45
    "Region", // 46 ***
    "Evropa", // 47
    "Amerika", // 48 ***
    "Zobrazit podtržítka v RDS", // 49
    "Režim USB", // 50
    "Wi-Fi aktivní", // 51 ***
    "Konfigurace Wi-Fi", // 52
    "Připojte se k: ", // 53
    "pro nakonfigurování Wi-Fi", // 54
    "Wi-Fi připojení probíhá...", // 55
    "NEPŘIPOJENO!", // 56
    "PŘIPOJENO!", // 57
    "Stationlist IP", // 58
    "Zobrazit SW pásmo", // 59
    "RDS filtr", // 60 ***
    "Zobrazit chyby v PI", // 61
    "Použít squelch", // 62
    "Graf modulace", // 63
    "Tlumič šumu (AM)", // 64
    "Tlumič šumu (FM)", // 65
    "Výchozí hodnoty načteny", // 66
    "Zvukový výstup", // 67
    "Povolit ladění přes spořič", // 68
    "Invertování barev", // 69
    "O softwaru", // 70
    "Hlavní kód:", // 71
    "Přispěli:", // 72
    "Neznámý", // 73
    "Nastavení\nspořiče obrazovky", // 74
    "Časovač vypnutí", // 75
    "Vypnutí obrazovky", // 76
    "Vzhled", // 77
    "Skin", // 78 ***
    "Detekované aplikace", // 79
    "minut", // 80 ***
    "Dynamická rychlost SPI", // 81 ***
    "Citlivost skenu", // 82
    "žádné", // 83
    "Verze softwaru", // 84
    "Font frekvence", // 85 ***
    "Auto", // 86
    "AF nedostupné", // 87
    "EON nedostupný", // 88
    "RT+ nedostupný", // 89
    "Výchozí krok ladění FM", // 90
    "Spořič obrazovky", // 91
    "sec.", // 92
    "ZMÁČKNĚTE BAND PRO ZAVŘENÍ", // 93
    "1% jas", // 94
    "25% jas", // 95
    "50% jas", // 96
    "AM offset signálu:", // 97
    "Jednotka signálu:", // 98
    "AF:", // 99
    "Zvolte FM pásmo:", // 100
    "Zvolte AM pásmo:", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Ladění při vypnuté obrazovce", // 107 ***
    "Volba modelu", // 108
    "Základní (ILI9341)", // 109
    "Přenosný (ILI9341)", // 110
    "Přenosný-dotykový(ILI9341)", // 111
    "Title", // 112 ***
    "Album", // 113 ***
    "Track", // 114 ***
    "Artist", // 115 ***
    "Composition", // 116 ***
    "Movement", // 117 ***
    "Conductor", // 118 ***
    "Composer", // 119 ***
    "Band", // 120 ***
    "Comment", // 121 ***
    "Genre", // 122 ***
    "News", // 123 ***
    "Local news", // 124 ***
    "Stockmarket", // 125 ***
    "Sport", // 126 ***
    "Lottery", // 127 ***
    "Horoscope", // 128 ***
    "Daily Diversion", // 129 ***
    "Health", // 130 ***
    "Event", // 131 ***
    "Scene", // 132 ***
    "Cinema", // 133 ***
    "TV", // 134 ***
    "Date/time", // 135 ***
    "Weather", // 136 ***
    "Traffic", // 137 ***
    "Alarm", // 138 ***
    "Advertisement", // 139 ***
    "Website", // 140 ***
    "Other", // 141 ***
    "Short PS", // 142 ***
    "Long PS", // 143 ***
    "Now", // 144 ***
    "Next", // 145 ***
    "Part", // 146 ***
    "Host", // 147 ***
    "Editor", // 148 ***
    "Frequency", // 149 ***
    "Homepage", // 150 ***
    "Subchannel", // 151 ***
    "Hotline", // 152 ***
    "Studio phone", // 153 ***
    "Phone", // 154 ***
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "Email hotline", // 157 ***
    "Email studio", // 158 ***
    "Email", // 159 ***
    "Chat", // 160 ***
    "Chat centre", // 161 ***
    "Vote question", // 162 ***
    "Vote centre", // 163 ***
    "Place", // 164 ***
    "Appointment", // 165 ***
    "Identifier", // 166 ***
    "Purchase", // 167 ***
    "Get data", // 168 ***
    "Výchozí krok ladění MW", // 169 ***
    "Tangerine", // 170 ***
    "Ocean", // 171 ***
    "Indigo", // 172 ***
    "Úroveň nabití baterie", // 173
    "Zobrazit napětí", // 174
    "Zobrazit procenta", // 175
    "RT buffering", // 176
    "Hlavní nastavení", // 177
    "Nastavení zvuku", // 178
    "Nastavení displeje", // 179
    "Nastavení RDS", // 180
    "Nastavení FM pásma", // 181
    "Nastavení AM pásma", // 182
    "Konektivita", // 183
    "ZMÁČKNĚTE MODE PRO NÁVRAT", // 184
    "AM CoChannelDet", // 185
    "Citlivost CoChannelDet", // 186
    "Práh AM CoChannelDet", // 187
    "CoChannelDet počítadlo", // 188
    "HLAVNÍ", // 189
    "ZVUK", // 190
    "DISPLEJ", // 191
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "KONEKTIVITA", // 195
    "DX REŽIM", // 196
    "Stationlist ID", // 197 ***
    "AM ATT", // 198
    "FM deemfáze", // 199 ***
    "Malé", // 200
    "Velké", // 201
    "Vše", // 202
    "Rychlé načtení PS", // 203
    "Výchozí", // 204
    "Vypnout displej při\nXDRGTK připojení", // 205
    "FMSI stereo\nvylepšení", // 206
    "Funkce dostupná pouze\nu TEF6687/6689!", // 207
    "Funkce není dostupná\nu zvoleného skinu!", // 208
    "Začít skenování\nod předvolby č.", // 209
    "Skončit skenování\nu předvolby č.", // 210
    "Doba čekání", // 211
    "Spustit DX skenování", // 212
    "Nastavení FM DX", // 213
    "Přerušeno! Začáteční předvolba\nje označena jako prázdná.", // 214
    "Auto řazení AF", // 215
    "Předvolby paměti", // 216
    "Vyloučit", // 217
    "Pouze", // 218
    "Automaticky zastavit\nskenování", // 219
    "po načtení PI", // 220
    "při signálu", // 221
    "Ztlumit zvuk\nběhem skenování", // 222
    "AIR", // 223
    "Po 5 sec. stisknutí\ntl. BAND", // 224
    "Vypnout", // 225
    "Vypnout displej", // 226
    "Zakázáno" // 227
  },

  { "Slovenský", // Slovak
    "Smer enkóderu bol zmenený", // 1
    "Prosím, pusťte tlačidlo", // 2
    "Obrazovka otočená", // 3
    "Kalibrácia analog. merača", // 4
    "Po dokončení pusťte tlačidlo", // 5
    "enkóder nastavený na optický", // 6
    "enkóder nastavený na štandardný", // 7
    "FM/AM prijímač", // 8
    "Tuner: !ŽIADNY!", // 9
    "Hlasitosť:", // 10
    "Konvertor:", // 11
    "Spodok pásma:", // 12
    "Vrch pásma:", // 13
    "FM Offset frekvencie:", // 14
    "Prah pre stereo:", // 15
    "Prah utlmenia:", // 16
    "Prah zvuku:", // 17
    "Prah nizkeho signálu:", // 18
    "Kontrast:", // 19
    "Hlasitost", // 20
    "Offset frekvencie", // 21
    "Spodok pásma", // 22
    "Vrch pásma", // 23
    "Offset signálu", // 24
    "Prah pro stereo", // 25
    "Prah utlmenia", // 26
    "Prah signálu pre utlmenie", // 27
    "Prah nízkého signálu", // 28
    "Jas", // 29
    "Vyp", // 30
    "Obrazovka je stlmená!", // 31
    "Pre spustenie odčiarknite RF+", // 32
    "VYP", // 33
    "SKENUJEM...", // 34
    "Tuner nedetekovaný", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Zobraziť chyby v RDS", // 38
    "Jazyk", // 39
    "Vyberte jazyk", // 40
    "STLAČTE MODE PRE ULOŽENIE", // 41
    "Zap", // 42
    "Softmute FM", // 43 ***
    "Softmute AM", // 44 ***
    "Pípnutie na konci pásma", // 45
    "Region", // 46 ***
    "Európa", // 47
    "America", // 48 ***
    "Zobraziť podtržítka v RDS", // 49
    "USB mód", // 50
    "Wi-Fi active", // 51 ***
    "Konfigurace Wi-Fi", // 52
    "Pripojte sa k: ", // 53
    "pre nakonfigurovánie Wi-Fi", // 54
    "Wi-Fi pripojenie prebieha...", // 55
    "NEPRIPOJENÉ!", // 56
    "PRIPOJENÉ!", // 57
    "Stationlist IP", // 58
    "Zobraziť SW pásmo", // 59
    "RDS filter", // 60 ***
    "Zobraziť chyby v PI", // 61
    "Zobraziť squelch", // 62 NEEDS NEW TRANSLATION, ENGLISH: USE SQUELCH
    "Graf modulácie", // 63
    "Utlmenie šumu (AM)", // 64
    "Utlmenie šumu (FM)", // 65
    "Východzie hodnoty načítané", // 66
    "Zvukový výstup", // 67
    "Povolit ladenie počas šetriča", // 68
    "Invertovanie farieb", // 69
    "O softvéri", // 70
    "Hlavný kód:", // 71
    "Prispeli:", // 72
    "Neznámy", // 73
    "Nastavenia šetriča obrazovky", // 74
    "Čas", // 75
    "Vypnutie obrazovky", // 76
    "Vzhľad", // 77
    "Skin", // 78 ***
    "Detegované aplikácie", // 79
    "Min.", // 80 ***
    "Dynamic SPI speed", // 81 ***
    "Scan sensitivity", // 82
    "NONE", // 83 represents: AM/FM bands unavailable(please delete this note after translation）
    "Software version", // 84
    "Frequency font", // 85 ***
    "Auto", // 86
    "AF nedostupné", // 87
    "EON nedostupný", // 88
    "RT+ nedostupný", // 89
    "Krokovanie FM", // 90
    "Šetrič obrazovky", // 91
    "Sekúnd", // 92
    "STLAČTE BAND PRE UZAVRETIE", // 93
    "1% jas", // 94
    "25% jas", // 95
    "50% jas", // 96
    "AM Offset signálu:", // 97
    "Jednotka signálu:", // 98
    "AF:", // 99
    "Zvoľte FM pásmo:", // 100
    "Zvoľte AM pásmo:", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Rotating while screen off", // 107 ***
    "Voľba modelu", // 108
    "Základ (ILI9341)", // 109
    "Prenosný (ILI9341)", // 110
    "Prenosný - dotykový (ILI9341)", // 111
    "Title", // 112 ***
    "Album", // 113 ***
    "Track", // 114 ***
    "Artist", // 115 ***
    "Composition", // 116 ***
    "Movement", // 117 ***
    "Conductor", // 118 ***
    "Composer", // 119 ***
    "Band", // 120 ***
    "Comment", // 121 ***
    "Genre", // 122 ***
    "News", // 123 ***
    "Local news", // 124 ***
    "Stockmarket", // 125 ***
    "Sport", // 126 ***
    "Lottery", // 127 ***
    "Horoscope", // 128 ***
    "Daily Diversion", // 129 ***
    "Health", // 130 ***
    "Event", // 131 ***
    "Scene", // 132 ***
    "Cinema", // 133 ***
    "TV", // 134 ***
    "Date/time", // 135 ***
    "Weather", // 136 ***
    "Traffic", // 137 ***
    "Alarm", // 138 ***
    "Advertisement", // 139 ***
    "Website", // 140 ***
    "Other", // 141 ***
    "Short PS", // 142 ***
    "Long PS", // 143 ***
    "Now", // 144 ***
    "Next", // 145 ***
    "Part", // 146 ***
    "Host", // 147 ***
    "Editor", // 148 ***
    "Frequency", // 149 ***
    "Homepage", // 150 ***
    "Subchannel", // 151 ***
    "Hotline", // 152 ***
    "Studio phone", // 153 ***
    "Phone", // 154 ***
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "Email hotline", // 157 ***
    "Email studio", // 158 ***
    "Email", // 159 ***
    "Chat", // 160 ***
    "Chat centre", // 161 ***
    "Vote question", // 162 ***
    "Vote centre", // 163 ***
    "Place", // 164 ***
    "Appointment", // 165 ***
    "Identifier", // 166 ***
    "Purchase", // 167 ***
    "Get data", // 168 ***
    "MW default stepsize", // 169 ***
    "Tangerine", // 170 ***
    "Ocean", // 171 ***
    "Indigo", // 172 ***
    "Nastavenia batérie", // 173
    "Zobraziť napätie", // 174
    "Zobraziť percentá", // 175
    "RT načítanie", // 176
    "Hlavné nastavenia", // 177
    "Nastavenia zvuku", // 178
    "Nastavenia displeja", // 179
    "Nastavenia RDS", // 180
    "Nastavenia FM pásma", // 181
    "Nastavenia AM pásma", // 182
    "Konektivita", // 183
    "STĽACTE MODE PRE NÁVRAT", // 184
    "AM CoChannelDet", // 185
    "Citlivosť CoChannelDet", // 186
    "Prah AM CoChannelDet", // 187
    "CoChannelDet počítadlo", // 188
    "HLAVNÝ", // 189
    "ZVUK", // 190
    "DISPLEJ", // 191
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "PRIPOJENIE", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197 ***
    "AM ATT", // 198
    "FM deemphasis", // 199 ***
    "Malý", // 200
    "Veľký", // 201
    "Všetko", // 202
    "Rýchle načítanie PS", // 203
    "Default", // 204
    "Mute screen on\nXDRGTK connection", // 205
    "FMSI stereo\nimprovement", // 206
    "Function only available\non TEF6687/6689!", // 207
    "Function not available\non selected skin!", // 208
    "Begin scanning\nmemory channels", // 209
    "Stop scanning\nmemory channels", // 210
    "Wait time", // 211
    "Start DX scanning", // 212
    "FM DX Options", // 213
    "Abort! The start channel\nis marked as skipped.", // 214
    "Auto radenie AF", // 215
    "Memory channels", // 216
    "Exclude", // 217
    "Only", // 218
    "Auto cancel scan", // 219
    "Correct PI", // 220
    "Signal", // 221
    "Mute audio\nwhile scanning", // 222
    "AIR", // 223
    "5 sec. bandbutton press", // 224
    "Power off", // 225
    "Mute screen", // 226
    "Disabled" // 227
  },

  { "Français", // French
    "Sens de rotation modifié", // 1
    "Veuillez relâcher\nle bouton", // 2
    "Écran inversé", // 3
    "Calibrer le compteur\nanalogique", // 4
    "Relâchez le bouton\nlorsque prêt", // 5
    "Codeur réglé\nsur optique", // 6
    "Codeur réglé\nsur standard", // 7
    "Récepteur FM/AM", // 8
    "Tuner: Aucun!", // 9
    "Volume:", // 10
    "Convertisseur:", // 11
    "Limite de bande basse:", // 12
    "Limite de bande haute:", // 13
    "FM décalage du niveau RF:", // 14
    "Stéréo seuil minimum:", // 15
    "Angle du filtre\nà coupe haute:", // 16
    "Seuil du filtre\nà coupe haute:", // 17
    "Seuil minimum de\nniveau bas:", // 18
    "Contraste:", // 19
    "Réglage du volume", // 20
    "Décalage du convertisseur", // 21
    "Limite de bande basse", // 22
    "Limite de bande haute", // 23
    "Décalage du niveau", // 24
    "Seuil de séparation\nstéréo", // 25
    "Fréquence de coupe\nélevée", // 26
    "Seuil de coupe élevée", // 27
    "Seuil de niveau bas", // 28
    "Luminosité de l'affichage", // 29
    "Éteint", // 30
    "L'écran est désactivé!", // 31
    "Pour le réactiver,\ndécochez la case RF+", // 32
    "FERMÉ", // 33
    "RECHERCHE...", // 34
    "Tuner non détecté", // 35
    "Gain de l'antenne AM", // 36
    "FM AGC", // 37
    "Montrer les erreurs\nde décodage RDS", // 38
    "Langage", // 39
    "Choix de la langue", // 40
    "APPUYEZ MODE POUR SORTIE & STOCKAGE", // 41
    "Allumé", // 42
    "Sourdine douce FM", // 43
    "Sourdine douce AM", // 44
    "Bip à la limite\nde bande", // 45
    "Région", // 46
    "Europe", // 47
    "Amérique", // 48
    "Montre les tirets du\nbas du PS", // 49
    "Mode USB", // 50
    "Wi-Fi actif", // 51
    "Configuration du Wi-Fi", // 52
    "Se connecter au réseau:", // 53
    "pour configurer\nle Wi-Fi", // 54
    "Tentative de connexion\nen mode Wi-Fi", // 55
    "CONNEXION IMPOSSIBLE...\nDésactivation du Wi-Fi", // 56
    "CONNECTÉ!", // 57
    "Stationlist client IP", // 58
    "Afficher la longueur\nd'onde SW", // 59
    "Filtre RDS", // 60
    "Afficher les erreurs\nde décodage PI", // 61
    "Utiliser le squelch", // 62
    "Compteur de modulation", // 63
    "Réducteur de bruit AM", // 64
    "Réducteur de bruit FM", // 65
    "Paramètres par défaut\nchargés", // 66
    "Sortie audio", // 67
    "Réglage pendant\nl'économiseur d'écran", // 68
    "Inverser l'affichage", // 69
    "À propos du logiciel", // 70
    "Code principal :", // 71
    "Contributeurs :", // 72
    "Inconnu", // 73
    "Options d'économiseur\nd'écran", // 74
    "Temporisateur", // 75
    "Affichage éteint", // 76
    "Thème", // 77
    "Skin", // 78 ***
    "Applications détectées", // 79
    "Min.", // 80
    "Vitesse SPI\ndynamique", // 81
    "Sensibilité\ndu scanne ", // 82
    "AUCUNE", // 83
    "Version de logiciel", // 84
    "Police de fréquence", // 85 ***
    "Auto", // 86
    "AF indisponible", // 87
    "EON indisponible", // 88
    "RT+ indisponible", // 89
    "Valeur du pas FM\npar défaut", // 90
    "Économiseur d'affichage", // 91
    "Sec", // 92 ***
    "APPUYEZ SUR BAND POUR FERMER", // 93
    "1% luminosité", // 94
    "25% luminosité", // 95
    "50% luminosité", // 96
    "AM décalage du\nniveau RF:", // 97
    "Unité de mesure\ndu signal:", // 98
    "Utilisez le AF:", // 99
    "Sélectionner la\nbande FM:", // 100
    "Sélectionner la\nbande AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotation lorsque\nl'écran est éteint", // 107
    "Sélecteur de modèle", // 108
    "Base (ILI9341)", // 109
    "Portable (ILI9341)", // 110
    "Portable touche (ILI9341)", // 111
    "Titre", // 112
    "Album", // 113
    "Piste", // 114
    "Artiste", // 115
    "Composition", // 116
    "Mouvement", // 117
    "Chef d'orchestre", // 118
    "Compositeur", // 119
    "Groupe", // 120
    "Commentaire", // 121
    "Genre", // 122
    "Actualités", // 123
    "Actualités locales", // 124
    "Bourse", // 125
    "Sport", // 126
    "Loterie", // 127
    "Horoscope", // 128
    "Divertissement quotidien", // 129
    "Santé", // 130
    "Événement", // 131
    "Scène", // 132
    "Cinéma", // 133
    "TV", // 134
    "Date/heure", // 135
    "Météo", // 136
    "Trafic", // 137
    "Alarme", // 138
    "Publicité", // 139
    "Site web", // 140
    "Autre", // 141
    "PS court", // 142
    "PS long", // 143
    "Maintenant", // 144
    "Suivant", // 145
    "Partie", // 146
    "Hôte", // 147
    "Rédacteur", // 148
    "Fréquence", // 149
    "Page d'accueil", // 150
    "Sous-canal", // 151
    "Hotline", // 152
    "Téléphone du studio", // 153
    "Téléphone", // 154
    "SMS au studio", // 155
    "SMS", // 156
    "Hotline par email", // 157
    "Email du studio", // 158
    "Email", // 159
    "Chat", // 160
    "Centre de discussion", // 161
    "Question de vote", // 162
    "Centre de vote", // 163
    "Lieu", // 164
    "Rendez-vous", // 165
    "Identifiant", // 166
    "Achat", // 167
    "Obtenir des données", // 168
    "AM taille de pas\npar défaut", // 169
    "Mandarine", // 170
    "Océan", // 171
    "Indigo", // 172
    "Options de batterie", // 173
    "Montrer la tension", // 174
    "Montrer le pourcentage", // 175
    "RT buffering", // 176
    "Paramètres principaux", // 177
    "Paramètres audio", // 178
    "Paramètres d'affichage", // 179
    "Paramètres RDS", // 180
    "Paramètres FM", // 181
    "Paramètres AM", // 182
    "Connectivité", // 183
    "APPUYEZ MODE POUR RETOURNER", // 184
    "AM CoChannelDet", // 185
    "CoChannelDet\nsensibilité", // 186
    "AM CoChannelDet\nsueil", // 187
    "CoChannelDet\ncompteur", // 188
    "PRINCIPAUX", // 189
    "AUDIO", // 190
    "AFFICHAGE", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECTER", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM déemphasie", // 199
    "Petites", // 200
    "Grosses", // 201
    "Toutes", // 202
    "PS rapide", // 203
    "Défaut", // 204
    "Écran muet sur\nla connexion XDRGTK", // 205
    "FMSI amélioration\ndu son stéréo", // 206
    "Fonction disponible seulement\nsur TEF6687/6689!", // 207
    "Fonction non disponible\nsur le skin sélectionné!", // 208
    "Commencez la scanne\ndes canaux de mémoire", // 209
    "Arrêt de la scanne\ndes canaux de mémoire", // 210
    "Temps d'attente", // 211
    "Démarrer la scanne DX", // 212
    "Options FM DX", // 213
    "Avorter! Le canal de\ndémarrage est sauté.", // 214
    "Tri AF automatique", // 215
    "Canaux de mémoire", // 216
    "Exclure", // 217
    "Seleument", // 218
    "Annuler automatiquement", // 219
    "PI Correct", // 220
    "Signal", // 221
    "Audio muet lors\nde la numérisation", // 222
    "AIR", // 223
    "Appui sur le bouton\nband 5 sec.", // 224
    "Éteindre", // 225
    "Écran muet", // 226
    "Inactif" // 227
  },

  { "Български", // Bulgarian
    "Посоката е променена", // 1
    "Моля, пуснете бутона", // 2
    "Екранът бе обърнат", // 3
    "Калибрация на аналоговото измерване", // 4
    "Пуснете бутона, когато сте готови", // 5
    "Енкодерът е настр. в оптич. р-м", // 6
    "Енкодерът е настр. в станд. р-м", // 7
    "FM/AM приемник", // 8
    "Не е открит тунер!", // 9
    "Сила на звука:", // 10
    "Отместване на конв.:", // 11
    "Нисък край:", // 12
    "Висок край:", // 13
    "FM Отместване на RF:", // 14
    "Стерео праг:", // 15
    "Мин. честота на изряз.:", // 16
    "Мин. сигнал за изряз.:", // 17
    "Праг на слаб сигнал:", // 18
    "Яркост:", // 19
    "Сила на звука", // 20
    "Отместване на конвертора:", // 21
    "Нисък край на честотната лента", // 22
    "Висок край на честотната лента", // 23
    "Отместване на RF ниво", // 24
    "Праг за отделянето на Stereo", // 25
    "Праг за изрязване на ниските честоти", // 26
    "Праг за изрязване на високите честоти", // 27
    "Праг за слаб сигнал", // 28
    "Яркост на дисплея", // 29
    "Изкл.", // 30
    "Дисплеят е деактивиран!", // 31
    "За активация, изкл. RF+ опцията", // 32
    "ИЗКЛ.", // 33
    "СКАНИРАНЕ", // 34
    "Тунерът не е разпознат!", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Показване на RDS грешки", // 38
    "Език", // 39
    "Изберете език", // 40
    "НАТИСНЕТЕ MODE ЗА ИЗХОД И ЗАПАМЕТ.", // 41
    "Вкл.", // 42
    "Затихване при слаб сигнал FM", // 43
    "Затихване при слаб сигнал AM", // 44
    "Звук при край на чест. лента", // 45
    "Регион", // 46
    "Европа", // 47
    "Америка", // 48
    "Показване на долни черти в RDS", // 49
    "USB режим", // 50
    "Активиране на Wi-Fi", // 51
    "Конфигурация на Wi-Fi", // 52
    "Свържете се към: ", // 53
    "За конфигурирация на Wi-Fi", // 54
    "Установява се връзка...", // 55
    "Грешка! Wi-Fi е изкл.", // 56
    "Установена е връзка", // 57
    "IP адрес на клиента за Stationlist", // 58
    "Показв. на дълж. на вълната при КВ", // 59
    "RDS филтър", // 60
    "Показване на PI грешки", // 61
    "Показване на squelch индикатор", // 62 NEEDS NEW TRANSLATION, ENGLISH: USE SQUELCH
    "Индикатор за модулация", // 63
    "AM заглушител на шума", // 64
    "FM заглушител на шума", // 65
    "Фабр. настройки бяха зададени", // 66
    "Аудио Изход", // 67
    "Allow tuning during screensaver", // 68
    "Обръщане на дисплея", // 69
    "Относно софтуера", // 70
    "Главен код:", // 71
    "Сътрудници:", // 72
    "Неизвестно", // 73
    "Screensaver options", // 74 ***
    "Time-out timer", // 75 ***
    "Изключен дисплей", // 76
    "Тема", // 77
    "Skin", // 78 ***
    "Detected applications", // 79 ***
    "Мин.", // 80
    "Dynamic SPI speed", // 81 ***
    "Scan sensitivity", // 82
    "NONE", // 83 represents: AM/FM bands unavailable(please delete this note after translation）
    "Software version", // 84
    "Frequency font", // 85 ***
    "Auto", // 86
    "AF опцията не е налична", // 87
    "EON опцията не е налична", // 88
    "RT+ опцията не е налична", // 89
    "Размер на стъпката на FM", // 90
    "Скрийнсейвър", // 91
    "сек.", // 92
    "НАТИСНЕТЕ BAND ЗА ИЗХОД", // 93
    "1% яркост", // 94
    "25% яркост", // 95
    "50% яркост", // 96
    "AM RF Level offset:", // 97
    "Сигнал-мерна единица:", // 98
    "Use AF:", // 99
    "Изберете УКВ диапазон:", // 100
    "Изберете СВ диапазон:", // 101
    "ДВ (LW)", // 102
    "СВ (MW)", // 103
    "КВ (SW)", // 104
    "УКВ (FM)", // 105
    "ОИРТ", // 106
    "Ротация при затъмнен екран", // 107
    "Избор на модел", // 108
    "База (ILI9341)", // 109
    "Портативен (ILI9341)", // 110
    "Портативен сенз. екран (ILI9341)", // 111
    "Заглавие", // 112
    "Албум", // 113
    "Песен", // 114
    "Изпълнител", // 115
    "Composition", // 116 ***
    "Действие", // 117
    "Диригент", // 118
    "Композитор", // 119
    "Група", // 120
    "Коментар", // 121
    "Жанр", // 122
    "Новини", // 123
    "Местни новини", // 124
    "Фин борса", // 125
    "Спорт", // 126
    "Лото", // 127
    "Хороскоп", // 128
    "Daily Diversion", // 129 ***
    "Здраве", // 130
    "Event", // 131 ***
    "Сцена", // 132
    "Кино", // 133
    "ТВ", // 134
    "Дата/време", // 135
    "Времето", // 136
    "Трафик", // 137
    "Аларма", // 138
    "Реклама", // 139
    "Уеб страница", // 140
    "Other", // 141 ***
    "Short PS", // 142 ***
    "Long PS", // 143 ***
    "Now", // 144 ***
    "Следващ", // 145
    "Part", // 146 ***
    "Host", // 147 ***
    "Editor", // 148 ***
    "Честота", // 149
    "Начална страница", // 150
    "Subchannel", // 151 ***
    "Гореща линия", // 152
    "Студиен тел", // 153
    "Телефон", // 154
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "Имейл гореща линия", // 157
    "Имейл до студиото", // 158
    "Имейл", // 159
    "Чат", // 160
    "Чат център", // 161
    "Vote question", // 162 ***
    "Vote centre", // 163 ***
    "Place", // 164 ***
    "Appointment", // 165 ***
    "Идентификатор", // 166
    "Покупка", // 167
    "Получи данни", // 168
    "MW default stepsize", // 169 ***
    "Tangerine", // 170 ***
    "Океан", // 171
    "Индиго", // 172
    "Battery options", // 173 ***
    "Show voltage", // 174 ***
    "Show percentage", // 175 ***
    "RT buffering", // 176 ***
    "Главни настройки", // 177
    "Аудио-настройка", // 178
    "Екран-настроийка", // 179
    "RDS настройки", // 180
    "FM настройки", // 181
    "AM/СВ настройки", // 182
    "Connectivity", // 183 ***
    "PRESS MODE TO RETURN", // 184 ***
    "AM CoChannelDet", // 185
    "CoChannelDet sensitivity", // 186
    "AM CoChannelDet threshold", // 187
    "CoChannelDet counter", // 188
    "ГЛАВНО МЕНЮ", // 189
    "АУДИО", // 190
    "ЕКРАН", // 191
    "RDS", // 192 ***
    "УКВ (FM)", // 193
    "СВ (AM)", // 194
    "ВРЪЗКА", // 195
    "DX MODE", // 196
    "Stationlist Идентификатор", // 197
    "СВ атенюатор", // 198
    "FM deemphasis", // 199 ***
    "Small", // 200 ***
    "Large", // 201 ***
    "Всички", // 202
    "Fast PS", // 203 ***
    "Default", // 204
    "Mute screen on\nXDRGTK connection", // 205
    "FMSI stereo\nimprovement", // 206
    "Function only available\non TEF6687/6689!", // 207
    "Function not available\non selected skin!", // 208
    "Begin scanning\nmemory channels", // 209
    "Stop scanning\nmemory channels", // 210
    "Wait time", // 211
    "Start DX scanning", // 212
    "FM DX Options", // 213
    "Abort! The start channel\nis marked as skipped.", // 214
    "Auto sort AF", // 215 ***
    "Memory channels", // 216
    "Exclude", // 217
    "Only", // 218
    "Auto cancel scan", // 219
    "Correct PI", // 220
    "Signal", // 221
    "Mute audio\nwhile scanning", // 222
    "AIR", // 223
    "5 sec. bandbutton press", // 224
    "Power off", // 225
    "Mute screen", // 226
    "Disabled" // 227
  },

  { "Русский", // Russian
    "Изменено направление", // 1
    "Теперь отпустите кнопку", // 2
    "Экран перевёрнут", // 3
    "Калибровка S-метра", // 4
    "Готово? Отпустите кнопку", // 5
    "энкодер: оптический", // 6
    "энкодер: стандартный", // 7
    "AM/FM РАДИОПРИЁМНИК", // 8
    "Тюнер: !Нет!", // 9
    "Линейная громкость:", // 10
    "Сдвиг конвертера:", // 11
    "Нижняя граница FM:", // 12
    "Верхняя граница FM:", // 13
    "Калибровка уровня:", // 14
    "Порог открытия стерео:", // 15
    "Срез ВЧ:", // 16
    "Порог среза ВЧ:", // 17
    "Порог качества сигнала:", // 18
    "Яркость:", // 19
    "Линейная громкость", // 20
    "Сдвиг конвертера", // 21
    "Нижняя граница FM", // 22
    "Верхняя граница FM", // 23
    "Калибровка уровня", // 24
    "Порог открытия стереодекодера", // 25
    "Срез ВЧ при слабом сигнале", // 26
    "Порог высокочастотного среза", // 27
    "Порог качества сигнала", // 28
    "Яркость дисплея", // 29
    "Выкл.", // 30
    "Экран отключен!", // 31
    "Чтобы включить звук, снимите флажок RF+", // 32
    "ВЫКЛ.", // 33
    "СКАНИРОВАНИЕ...", // 34
    "Тюнер не обнаружен", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Уровень ошибок RDS", // 38
    "Язык меню", // 39
    "Язык меню: ", // 40
    "НАЖМИТЕ MODE ДЛЯ СОХРАНЕНИЯ", // 41
    "Вкл.", // 42
    "FM Soft Mute", // 43
    "AM Soft Mute", // 44
    "Край диапазона (звук): ", // 45
    "Регион", // 46
    "Европа", // 47
    "Америка", // 48
    "Показывать _ в RDS", // 49
    "Режим USB", // 50
    "Wi-Fi активен", // 51
    "Настройка Wi-Fi", // 52
    "Подключиться к: ", // 53
    "для настройки Wi-Fi", // 54
    "Попытка подключения Wi-Fi", // 55
    "НЕ УДАЛОСЬ... Wi-Fi отключен", // 56
    "Подключено!", // 57
    "IP stationlist-клиента", // 58
    "Отображать длину волны", // 59
    "Фильтр RDS-данных", // 60
    "Ошибки PI-кода", // 61
    "Отображать шумодав", // 62 NEEDS NEW TRANSLATION, ENGLISH: USE SQUELCH
    "Уровень модуляции", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "Загружены настройки по умолчанию", // 66
    "Режим вывода аудио", // 67
    "При погашенном экране", // 68 for translation reference to computer Touch Typing
    "Инвертировать дисплей", // 69
    "О программе", // 70
    "Основной код:", // 71
    "Соавторы:", // 72
    "Неизвестно", // 73
    "Действие по таймеру", // 74
    "Глубокий сон", // 75
    "Погасить экран", // 76
    "Тема", // 77
    "Вид (Skin)", // 78 ***
    "Обнаруженные приложения", // 79
    "мин.", // 80
    "Частота шины дисплея SPI", // 81 ***
    "Чувствительность сканирования", // 82
    "Не использовать AM", // 83
    "Версия прошивки -", // 84
    "Шрифт индикации частоты", // 85 ***
    "Auto", // 86
    "Нет данных", // 87
    "Нет данных", // 88
    "Нет данных", // 89
    "Шаг FM по умолчанию", // 90
    "Таймер", // 91
    "сек", // 92
    "НАЖМИТЕ BAND ДЛЯ ЗАКРЫТИЯ", // 93
    "1% яркости", // 94
    "25% яркости", // 95
    "50% яркости", // 96
    "Калибровка уровня:", // 97
    "Измерять сигнал в:", // 98
    "Переключаться по AF:", // 99
    "Активные диапазоны:", // 100
    "Активные диапазоны:", // 101
    " ДВ", // 102
    " СВ", // 103
    " КВ", // 104
    " FM", // 105
    " УКВ", // 106
    "Настройка при погашенном экране: ", // 107
    "Выбор модели", // 108
    "Стандартный (ILI9341)", // 109
    "Портативный (ILI9341)", // 110
    "Сенсорный (ILI9341)", // 111
    "Название", // 112
    "Альбом", // 113
    "Трек", // 114
    "Исполнитель", // 115
    "Композиция", // 116
    "Движение", // 117
    "Дирижер", // 118
    "Композитор", // 119
    "Группа", // 120
    "Комментарий", // 121
    "Жанр", // 122
    "Новости", // 123
    "Местные новости", // 124
    "Фондовый рынок", // 125
    "Спорт", // 126
    "Лотерея", // 127
    "Гороскоп", // 128
    "Развлечения", // 129
    "Здоровье", // 130
    "Событие", // 131
    "Сцена", // 132
    "Кинотеатр", // 133
    "Телевидение", // 134
    "Дата/время", // 135
    "Погода", // 136
    "Движение", // 137
    "Будильник", // 138
    "Реклама", // 139
    "Веб-сайт", // 140
    "Другое", // 141
    "Краткое PS", // 142
    "Длинное PS", // 143
    "Сейчас", // 144
    "Следующий", // 145
    "Часть", // 146
    "Ведущий", // 147
    "Редактор", // 148
    "Частота", // 149
    "Домашняя страница", // 150
    "Субканал", // 151
    "Горячая линия", // 152
    "Телефон студии", // 153
    "Телефон", // 154
    "SMS студии", // 155
    "SMS", // 156
    "Email горячей линии", // 157
    "Email студии", // 158
    "Email", // 159
    "Чат", // 160
    "Чат-центр", // 161
    "Вопрос голосования", // 162
    "Голосовой центр", // 163
    "Место", // 164
    "Встреча", // 165
    "Идентификатор", // 166
    "Покупка", // 167
    "Получить данные", // 168
    "Шаг по умолчанию на СВ", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Индикатор батареи", // 173
    "Вольтаж", // 174
    "Процент заряда", // 175
    "Буфер RT", // 176
    "Основные настройки", // 177
    "Звуковые настройки", // 178
    "Настройки отображения", // 179
    "RDS", // 180
    "Настройки FM", // 181
    "Настройки AM", // 182
    "Настройки подключения", // 183
    "НАЖМИТЕ MODE ДЛЯ ВОЗВРАТА", // 184
    "CoChannelDet чувствительность", // 185
    "AM CoChannelDet", // 186
    "CoChannelDet количество", // 187
    "Порог AM CoChannelDet", // 188
    "ОСНОВНЫЕ", // 189
    "ЗВУКОВЫЕ", // 190
    "ДИСПЛЕЙ", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "КОННЕКТ", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197
    "AM аттеньюатор", // 198
    "FM deemphasis", // 199
    "Мало", // 200
    "Больше", // 201
    "Все", // 202
    "Быстрый PS", // 203
    "По умолчанию", // 204
    "Гасить дисплей при\nработе с XDRGTK", // 205
    "FMSI стерео\nулучшение", // 206
    "Доступно только\nна TEF6687/6689", // 207
    "Функция недоступна\nна этом оформлении", // 208
    "Стартовый канал\nпамяти", // 209
    "Конечный канал\nпамяти", // 210
    "Время ожидания", // 211
    "Начать DX-сканирование", // 212
    "Настройки FM DX сканера", // 213
    "Прервано! Стартовый канал\nпомечен для пропуска.", // 214
    "Сортировка AF-частот", // 215
    "Логика работы с \nканалами памяти", // 216
    "Кроме", // 217
    "Только", // 218
    "Автоматическая отмена \nсканирования", // 219
    "При корректном PI", // 220
    "При наличии сигнала", // 221
    "Отключать аудио\nпри сканировании", // 222
    "Эфир", // 223
    "5 сек. зажатия кнопки диапазона", // 224
    "Приемник выключен", // 225
    "Экран выключен", // 226
    "Выключено" // 227
  },

  { "Українська", // Ukranian
    "Змінено напрямок обертання", // 1
    "Будь ласка, відпустіть кнопку", // 2
    "Екран перевернуто", // 3
    "Калібрувати аналоговий метр", // 4
    "Відпустіть кнопку, коли будете готові", // 5
    "енкодер установлено на оптичний", // 6
    "енкодер установлено на стандартний", // 7
    "FM / AM приймач", // 8
    "Тюнер: !Відсутній!", // 9
    "Гучність:", // 10
    "Конвертер:", // 11
    "Нижня межа діапазону:", // 12
    "Верхня межа діапазону:", // 13
    "FM Зміщення рівня RF:", // 14
    "Поріг стерео:", // 15
    "Верхній край відсіку Високих частот:", // 16
    "Поріг відсіку Високих частот:", // 17
    "Поріг низького рівня:", // 18
    "Контрастність:", // 19
    "Встановити гучність", // 20
    "Встановити зміщення конвертера", // 21
    "Встановити нижню діапазону", // 22
    "Встановити верхню діапазону", // 23
    "Встановити зміщення рівня", // 24
    "Встановити поріг стерео", // 25
    "Встановити част. верх. відсіку", // 26
    "Встановити поріг Вис. част.", // 27
    "Встановити поріг низького рівня", // 28
    "Встановити яскравість дисплея", // 29
    "Вимкнено", // 30
    "Екран приглушено!", // 31
    "Щоб відключити приглушення, зніміть прапорець RF+", // 32
    "ВИМКН.", // 33
    "СКАНУВАННЯ...", // 34
    "Тюнер не виявлено", // 35
    "AM Antenna gain", // 36
    "FM AGC", // 37
    "Показувати помилки RDS", // 38
    "Мова", // 39
    "Виберіть мову", // 40
    "НАТИСНІТЬ MODE ДЛЯ ВИХОДУ І ЗБЕРЕЖ.", // 41
    "Увімкнено", // 42
    "Приглушення FM", // 43
    "Приглушення AM", // 44
    "Сигнал звуку на межі діапазону", // 45
    "Регіон", // 46
    "Європа", // 47
    "америка", // 48
    "Показувати підкреслення в RDS", // 49
    "Режим USB", // 50
    "Wi-Fi активний", // 51
    "Налаштувати Wi-Fi", // 52
    "Підключитися до: ", // 53
    "для налаштування Wi-Fi", // 54
    "Намагається підключитися до Wi-Fi", // 55
    "НЕ ВДАЛОСЬ... Wi-Fi вимкнено", // 56
    "ПІДКЛЮЧЕНО!", // 57
    "IP клієнта станційного списку", // 58
    "Показувати довжину хвилі КВ", // 59
    "Фільтр RDS", // 60
    "Показувати помилки PI", // 61
    "Показувати шумоподавлення", // 62 NEEDS NEW TRANSLATION, ENGLISH: USE SQUELCH
    "Метр модуляції", // 63
    "Помпи засліплення шуму AM", // 64
    "Помпи засліплення шуму FM", // 65
    "Завантажено параметри за замовчуванням", // 66
    "Аудіо вихід", // 67
    "Дозволити налаштування під час живлення", // 68
    "Перевернути дисплей", // 69
    "Про програмне забезпечення", // 70
    "Основний код:", // 71
    "Учасники:", // 72
    "Невідомо", // 73
    "Налаштування живлення", // 74
    "Таймер тайм-ауту", // 75
    "Екран вимкнено", // 76
    "Тема", // 77
    "Skin", // 78 ***
    "Виявлені програми", // 79
    "мін.", // 80
    "Швидкість шини дисплея (SPI)", // 81 ***
    "Чутливість сканування", // 82
    "NONE", // 83 represents: AM/FM bands unavailable(please delete this note after translation）
    "Версія ПО", // 84
    "Frequency font", // 85 ***
    "Auto", // 86
    "Немає доступних AF", // 87
    "Немає доступного EON", // 88
    "Немає доступного RT+", // 89
    "FM кроки за замовчуванням", // 90
    "Живлення вимк. через", // 91
    "с", // 92
    "НАТИСНІТЬ BAND ДЛЯ ЗАКРИТТЯ", // 93
    "1% яскравості", // 94
    "25% яскравості", // 95
    "50% яскравості", // 96
    "Зміщення рівня AM RF:", // 97
    "Вимірник сигналу:", // 98
    "Режим AF:", // 99
    "Виберіть FM-діапазон:", // 100
    "Виберіть AM-діапазон:", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Обертання, коли екран вимкнено", // 107
    "Вибір моделі", // 108
    "Стандартний (ILI9341)", // 109
    "Портативний (ILI9341)", // 110
    "Портатив. сенсорний (ILI9341)", // 111
    "Назва", // 112
    "Альбом", // 113
    "Трек", // 114
    "Виконавець", // 115
    "Композиція", // 116
    "Рух", // 117
    "Диригент", // 118
    "Композитор", // 119
    "Група", // 120
    "Коментар", // 121
    "Жанр", // 122
    "Новини", // 123
    "Місцеві новини", // 124
    "Фондовий ринок", // 125
    "Спорт", // 126
    "Лотерея", // 127
    "Гороскоп", // 128
    "Щоденне розваги", // 129
    "Здоров'я", // 130
    "Подія", // 131
    "Сцена", // 132
    "Кіно", // 133
    "ТБ", // 134
    "Дата/час", // 135
    "Погода", // 136
    "Трафік", // 137
    "Будильник", // 138
    "Реклама", // 139
    "Веб-сайт", // 140
    "Інше", // 141
    "Короткий PS", // 142
    "Довгий PS", // 143
    "Зараз", // 144
    "Далі", // 145
    "Частина", // 146
    "Ведучий", // 147
    "Редактор", // 148
    "Частота", // 149
    "Домашня сторінка", // 150
    "Субканал", // 151
    "Гаряча лінія", // 152
    "Телефон студії", // 153
    "Телефон", // 154
    "SMS студії", // 155
    "SMS", // 156 ***
    "Email гарячої лінії", // 157
    "Email студії", // 158
    "Email", // 159 ***
    "Чат", // 160
    "Чат-центр", // 161
    "Питання голосування", // 162
    "Центр голосування", // 163
    "Місце", // 164
    "Зустріч", // 165
    "Ідентифікатор", // 166
    "Покупка", // 167
    "Отримати дані", // 168
    "MW default stepsize", // 169 ***
    "Мандариновий", // 170
    "Океан", // 171
    "Індиго", // 172
    "Варіанти батареї", // 173
    "Показати заряд", // 174
    "Показати відсотки", // 175
    "Буферизація RT", // 176
    "Основні налаштування", // 177
    "Налаштування аудіо", // 178
    "Налаштування дисплея", // 179
    "Налаштування RDS", // 180
    "Налаштування FM", // 181
    "Налаштування AM", // 182
    "Підключення", // 183
    "НАТИСНІТЬ MODE ДЛЯ ПОВЕР.", // 184
    "AM CoChannelDet", // 185
    "Чутливість CoChannelDet", // 186
    "Поріг AM CoChannelDet", // 187
    "CoChannelDet кількість", // 188
    "ОСНОВНОЇ", // 189
    "АУДІО", // 190
    "ДИСПЛЕЙ", // 191
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "ПІДКЛЮЧЕННЯ", // 195
    "DX MODE", // 196
    "Stationlist ID", // 197 ***
    "AM ATT", // 198
    "FM deemphasis", // 199 ***
    "Мало", // 200
    "Багато", // 201
    "Усе", // 202
    "Швидкий PS", // 203
    "За замовчуванням", // 204
    "Вимкнути екран під час підключення\nXDRGTK", // 205
    "Покращення стерео\nFMSI", // 206
    "Функція доступна лише\nдля TEF6687/6689!", // 207
    "Функція недоступна\nдля вибраної шкіри!", // 208
    "Почати сканування\nканалів пам'яті", // 209
    "Зупинити сканування\nканалів пам'яті", // 210
    "Час очікування", // 211
    "Почати сканування DX", // 212
    "Параметри FM DX", // 213
    "Припинити! Початковий канал\позначено як пропущений.", // 214
    "Авто сорт. AF", // 215
    "Канали пам'яті", // 216
    "Виключити", // 217
    "ільки", // 218
    "Автоматичне скасування сканування", // 219
    "Правильний ПІ", // 220
    "Сигнал", // 221
    "Вимкнути звук\nпід час сканування", // 222
    "Ефір", // 223
    "5 сек. затискання кнопки діапазону", // 224
    "Приймач вимкнений", // 225
    "Екран вимкнено", // 226
    "Вимкнено" // 227
  },

  { "Italiano", // Italian
    "Senso rotaz. cambiato", // 1
    "Rilascia il pulsante", // 2
    "Schermo capovolto", // 3
    "Calibraz. meter analogico", // 4
    "Al termine, rilasciare pulsante", // 5
    "Sintonia di freq: ottica", // 6
    "Sintonia di freq: standard", // 7
    "Ricevitore FM/AM", // 8
    "Ricevitore: !Nessuno!", // 9
    "Volume: ", // 10
    "Convertitore: ", // 11
    "Limite di banda inf.:", // 12
    "Limite di banda sup.:", // 13
    "Offset livello RF FM: ", // 14
    "Soglia stereo: ", // 15
    "Angolo di taglio alti: ", // 16
    "Soglia di taglio alti:", // 17
    "Soglia di basso livello: ", // 18
    "Contrasto: ", // 19
    "Imposta volume", // 20
    "Offset conversione", // 21
    "Limite di banda inferiore", // 22
    "Limite di banda superiore", // 23
    "Offset di livello", // 24
    "Soglia separazione stereo", // 25
    "Frequenza taglio alti", // 26
    "Soglia taglio alti", // 27
    "Soglia di livello basso", // 28
    "Luminosità schermo", // 29
    "Off", // 30 ***
    "Schermo disattivato!", // 31
    "Deseleziona box RF+ per audio", // 32
    "OFF", // 33 ***
    "SCANSIONE...", // 34
    "Ricevitore non rilevato", // 35
    "Guadagno antenna AM", // 36
    "AGC FM", // 37
    "Mostra errori RDS", // 38
    "Lingua", // 39
    "Scegli la lingua", // 40
    "SALVA E ESCI: PREMI MODO", // 41
    "On", // 42 ***
    "Softmute FM", // 43 ***
    "Softmute AM", // 44 ***
    "Beep sul limite di banda", // 45
    "Regione", // 46
    "Europa", // 47
    "America", // 48 ***
    "Mostra trattino basso in RDS", // 49
    "Modalità USB", // 50
    "Wi-Fi attivo", // 51
    "Configura Wi-Fi", // 52
    "Connetti a: ", // 53
    "per configurare il Wi-Fi", // 54
    "Connessione al Wi-Fi", // 55
    "NON RIUSCITA!", // 56
    "CONNESSO!", // 57
    "IP per StationList", // 58
    "Mostra banda SW in m.", // 59
    "Filtro RDS", // 60
    "Mostra errori PI", // 61
    "Utilizzare squelch", // 62
    "Scala di modulazione", // 63
    "Soppressione rumore AM", // 64
    "Soppressione rumore FM", // 65
    "Predefiniti caricati", // 66
    "Uscita audio", // 67
    "Consenti sintonia\ncon salvaschermo", // 68
    "Inversione schermo", // 69
    "Info sul software", // 70
    "Codice principale:", // 71
    "Collaboratori: ", // 72
    "Sconosciuto", // 73
    "Opzioni salvaschermo", // 74 ***
    "Tempo di time-out", // 75 ***
    "Schermo spento", // 76
    "Motivo schermo", // 77
    "Skin", // 78 ***
    "Applicazioni rilevate", // 79 ***
    "Min.", // 80 ***
    "Velocità SPI Dinamico", // 81 ***
    "Sensibilità scansione", // 82
    "ASSENTE", // 83
    "Versione Software", // 84
    "Font frequenza", // 85 ***
    "Auto", // 86
    "AF non disponibile", // 87
    "EON non disponibile", // 88
    "RT + non disponibile", // 89
    "Passo di sintonia predef. FM", // 90
    "Salvaschermo", // 91
    "Sec.", // 92
    "PREMI BANDA PER CHIUDERE", // 93
    "1% luminosità", // 94
    "25% di luminosità", // 95
    "50% di luminosità", // 96
    "Offset livello RF AM: ", // 97
    "Unità S-meter: ", // 98
    "Utilizzare AF:", // 99
    "Selezionare banda FM:", // 100
    "Selezionare banda AM:", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Rotazione con schermo spento", // 107 ***
    "Selezionare modello", // 108 ***
    "Base (ILI9341)", // 109 ***
    "Portatile (ILI9341)", // 110 ***
    "Portatile touch (ILI9341)", // 111 ***
    "Titolo", // 112 ***
    "Album", // 113 ***
    "Traccia", // 114 ***
    "Artista", // 115 ***
    "Composizione", // 116 ***
    "Movimento", // 117 ***
    "Direttore", // 118 ***
    "Compositore", // 119 ***
    "Band", // 120 ***
    "Commento", // 121 ***
    "Genere", // 122 ***
    "Notizie", // 123 ***
    "Notizie locali", // 124 ***
    "Borsa", // 125 ***
    "Sport", // 126 ***
    "Lotterie", // 127 ***
    "Oroscopo", // 128 ***
    "Svago quotidiano", // 129 ***
    "Salute", // 130 ***
    "Eventi", // 131 ***
    "Scena", // 132 ***
    "Cinema", // 133 ***
    "TV", // 134 ***
    "Data/ora", // 135 ***
    "Meteo", // 136 ***
    "Traffico", // 137 ***
    "Allerta", // 138 ***
    "Pubblicità", // 139 ***
    "Sito Web", // 140 ***
    "Altro", // 141 ***
    "PS breve", // 142 ***
    "PS lungo", // 143 ***
    "Adesso", // 144 ***
    "Prossimo", // 145 ***
    "Parte", // 146 ***
    "Conduttore", // 147 ***
    "Redattore", // 148 ***
    "Frequenza", // 149 ***
    "Homepage", // 150 ***
    "Sottocanale", // 151 ***
    "Telefono emergenze", // 152 ***
    "Telefono studio", // 153 ***
    "Telefono", // 154 ***
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "Email emergenze", // 157 ***
    "Email studio", // 158 ***
    "Email", // 159 ***
    "Chat", // 160 ***
    "Centro Chat", // 161 ***
    "Domanda votazione", // 162 ***
    "Centro votazione", // 163 ***
    "Luogo", // 164 ***
    "Appuntamento", // 165 ***
    "Identificatore", // 166 ***
    "Acquisto", // 167 ***
    "Ottieni dati", // 168 ***
    "Passo di sintonia\nMW predefinito", // 169 ***
    "Tangerine", // 170 ***
    "Ocean", // 171 ***
    "Indigo", // 172 ***
    "Opzioni batteria", // 173 ***
    "Mostra tensione", // 174 ***
    "Mostra percentuale", // 175 ***
    "Buffering RT", // 176 ***
    "Impostazioni principali", // 177 ***
    "Impostazioni audio", // 178 ***
    "Impostazioni schermo", // 179 ***
    "Impostazioni RDS", // 180 ***
    "Impostazioni FM", // 181 ***
    "Impostazioni AM", // 182 ***
    "Connettività", // 183 ***
    "PREMI MODO PER CHIUDERE", // 184 ***
    "CoChannelDet AM", // 185
    "Sensibilità CoChannelDet", // 186
    "Soglia CoChannelDet AM", // 187
    "Contatore CoChannelDet", // 188
    "PRINCIPALE", // 189 ***
    "AUDIO", // 190 ***
    "SCHERMO", // 191 ***
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "CONNETTI", // 195 ***
    "MODO DX", // 196
    "ID Stationlist", // 197 ***
    "ATT AM", // 198
    "Deenfasi FM", // 199 ***
    "Piccolo", // 200 ***
    "Grande", // 201 ***
    "Tutto", // 202 ***
    "PS rapido", // 203 ***
    "Default", // 204
    "Spegni schermo se\nconnesso a XDRGTK", // 205
    "FMSI audio stereofonico ottimizzato", // 206
    "Funzione disponibile\nsolo su TEF6687/6689!", // 207
    "Funzione non disponibile\nsu skin selezionata!", // 208
    "Avvio scansione = canale in memoria", // 209
    "Fine scansione =  canale in memoria", // 210
    "Tempo di attesa", // 211
    "Avvio scansione DX", // 212
    "Opzioni FM DX", // 213
    "Stop! Canale di avvio\nimpost. su ignora", // 214
    "Autoordinamento AF", // 215
    "Canali in memoria", // 216
    "Esclusi", // 217
    "Solamente", // 218
    "Uscita automatica scansione", // 219
    "PI corretto", // 220
    "Segnale", // 221
    "Audio silenziato durante scansione", // 222
    "AIR", // 223
    "Premi BANDA x 5 sec.", // 224
    "Spegni radio", // 225
    "Spegni schermo", // 226
    "Non abilitata" // 227
  },

  { "Simplified Chinese", // Simplified Chinese
    "飞梭方向改变了", // 1
    "请释放按钮", // 2
    "屏幕翻转了", // 3
    "校准模拟S表", // 4
    "校准成功后请放开按钮", // 5
    "设置为光学编码器", // 6
    "设置为标准编码器", // 7
    "FM/AM TEF6686收音机", // 8
    "没有收音芯片 ！", // 9
    "音量", // 10
    "偏移量", // 11
    "FM 最低频率", // 12
    "FM 最高频率", // 13
    "FM信号偏移量", // 14
    "立体声阈值", // 15
    "高切角", // 16
    "高切门限", // 17
    "弱信号门限", // 18
    "屏幕亮度", // 19
    "设置音量", // 20
    "设置频率偏移量", // 21
    "设置 FM 最低频率", // 22
    "设置 FM 最高频率", // 23
    "设置信号值偏移量", // 24
    "设置立体声门限", // 25
    "设置高切角频率", // 26
    "设置高切门限", // 27
    "设置弱信号门限", // 28
    "屏幕亮度", // 29
    "关闭", // 30
    "屏幕静音!", // 31
    "点击RF+按钮解除静音", // 32
    "OFF", // 33 ***
    "搜索中...", // 34
    "未检测到收音芯片", // 35
    "AM 天线增益", // 36
    "FM AGC", // 37
    "显示 RDS errors", // 38
    "语言", // 39
    "选择语言", // 40
    "按 MODE 键退出并保存", // 41
    "打开", // 42
    "FM软静噪", // 43
    "AM软静噪", // 44
    "频率边界嘟声提醒", // 45
    "国家与地区", // 46
    "欧洲", // 47
    "美国", // 48
    "RDS中显示下划线", // 49
    "USB 连机模式选择", // 50
    "打开Wifi", // 51
    "Wi-Fi 配置", // 52
    "连接到: ", // 53
    "配置 Wi-Fi", // 54
    "尝试连接Wifi到", // 55
    "失败.. 关闭WiFi", // 56
    "连接成功!", // 57
    "Stationlist 客户端 IP", // 58
    "显示短波米波段", // 59
    "RDS 过滤器", // 60
    "显示 PI errors", // 61
    "SQ静噪等级", // 62
    "主画面显示M表", // 63
    "AM 噪声消除", // 64
    "FM 噪声消除", // 65
    "恢复出厂设置", // 66
    "音频输出选择", // 67
    "盲操", // 68
    "LCD颜色反转", // 69
    "关于(About)", // 70
    "主程序", // 71
    "贡献者", // 72
    "未知", // 73
    "屏保选项", // 74
    "倒计时关机", // 75
    "关闭屏幕", // 76
    "主题&颜色", // 77
    "布局", // 78 ***
    "Detected applications", // 79 ***
    "分钟", // 80
    "调整SPI通讯速率", // 81
    "搜索灵敏度", // 82
    "不可用", // 83
    "固件版本", // 84
    "频率字体", // 85 ***
    "自动", // 86
    "AF 不可用", // 87
    "EON 不可用", // 88
    "RT+ 不可用", // 89
    "FM 默认步进", // 90
    "屏保", // 91
    "秒", // 92
    "按下波段键关闭", // 93
    "屏幕 1% 亮度", // 94
    "屏幕 25% 亮度", // 95
    "屏幕 50% 亮度", // 96
    "AM 高频信号偏移", // 97
    "信号单位", // 98
    "使用 AF", // 99
    "选择FM波段", // 100
    "选择AM波段", // 101
    "LW", // 102 ***
    "MW", // 103 ***
    "SW", // 104 ***
    "FM", // 105 ***
    "OIRT", // 106 ***
    "熄屏操作飞梭", // 107
    "硬件型号选择", // 108
    "原版(ILI9341)", // 109
    "便携版(ILI9341)", // 110
    "便携电阻触摸版(ILI9341)", // 111
    "Title", // 112 ***
    "Album", // 113 ***
    "Track", // 114 ***
    "Artist", // 115 ***
    "Composition", // 116 ***
    "Movement", // 117 ***
    "Conductor", // 118 ***
    "Composer", // 119 ***
    "Band", // 120 ***
    "Comment", // 121 ***
    "Genre", // 122 ***
    "News", // 123 ***
    "Local news", // 124 ***
    "Stockmarket", // 125 ***
    "Sport", // 126 ***
    "Lottery", // 127 ***
    "Horoscope", // 128 ***
    "Daily Diversion", // 129 ***
    "Health", // 130 ***
    "Event", // 131 ***
    "Scene", // 132 ***
    "Cinema", // 133 ***
    "TV", // 134 ***
    "Date/time", // 135 ***
    "Weather", // 136 ***
    "Traffic", // 137 ***
    "Alarm", // 138 ***
    "Advertisement", // 139 ***
    "Website", // 140 ***
    "Other", // 141 ***
    "Short PS", // 142 ***
    "Long PS", // 143 ***
    "Now", // 144 ***
    "Next", // 145 ***
    "Part", // 146 ***
    "Host", // 147 ***
    "Editor", // 148 ***
    "Frequency", // 149 ***
    "Homepage", // 150 ***
    "Subchannel", // 151 ***
    "Hotline", // 152 ***
    "Studio phone", // 153 ***
    "Phone", // 154 ***
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "Email hotline", // 157 ***
    "Email studio", // 158 ***
    "Email", // 159 ***
    "Chat", // 160 ***
    "Chat centre", // 161 ***
    "Vote question", // 162 ***
    "Vote centre", // 163 ***
    "Place", // 164 ***
    "Appointment", // 165 ***
    "Identifier", // 166 ***
    "Purchase", // 167 ***
    "Get data", // 168 ***
    "中波默认步进", // 169 ***
    "桔红", // 170
    "海之蓝", // 171
    "靛青", // 172
    "显示电池", // 173
    "电压值", // 174
    "电池百分比", // 175
    "RT 缓存", // 176
    "主要设置", // 177
    "音频设置", // 178
    "显示设置", // 179
    "RDS设置", // 180
    "FM 设置", // 181
    "AM 设置", // 182
    "连机模式", // 183
    "按 MODE 键返回", // 184
    "AM载波跟踪", // 185
    "设置跟踪灵敏度", // 186
    "AM载波跟踪层级", // 187
    "设置跟踪层级", // 188
    "主要设置", // 189
    "音频设置", // 190
    "显示设置", // 191
    "RDS 设置", // 192
    "FM 设置", // 193
    "AM 设置", // 194
    "连机模式", // 195
    "FMDX 选项", // 196
    "Stationlist ID", // 197 ***
    "AM天线衰减", // 198
    "FM去加重", // 199
    "少量", // 200
    "大量", // 201
    "全部", // 202
    "快速 PS", // 203
    "默认", // 204
    "XDRGTK连接时锁屏", // 205
    "FMSI\n立体声增强", // 206
    "此功能仅限\nTEF6687/6689!", // 207
    "此皮肤不支持该功能!", // 208
    "开始信道号", // 209
    "结尾信道号", // 210
    "扫描间隔", // 211
    "立即开始DX扫描", // 212
    "FMDX 选项", // 213
    "终止!开始信道无电台!", // 214
    "自动排列AF", // 215
    "信道扫描方式", // 216
    "信道外频率", // 217
    "仅信道", // 218
    "扫频停台条件", // 219
    "节目识别码正确", // 220
    "信号超阈值", // 221
    "扫描时静音", // 222
    "AIR", // 223
    "5 sec. bandbutton press", // 224
    "Power off", // 225
    "Mute screen", // 226
    "Disabled" // 227
  },

  { "Norsk", // Norwegian
    "Rotasjonsretning endret", // 1
    "Vennligst slipp knappen", // 2
    "Skjermen ble snudd", // 3
    "Kalibrer analog meter", // 4
    "Slipp knappen når du er klar", // 5
    "encoder satt til optisk", // 6
    "encoder satt til standard", // 7
    "FM/AM Radio", // 8
    "Tuner: !Ingen!", // 9
    "Lydstyrke:", // 10
    "Omformer:", // 11
    "Lav bånd grense:", // 12
    "Høy bånd grense:", // 13
    "FM RF-nivåforskyvning:", // 14
    "Stereo terskel:", // 15
    "Høyeste grense:", // 16
    "Høyeste grense:", // 17
    "Laveste grense:", // 18
    "Kontrast:", // 19
    "Sett lyd", // 20
    "Sett omformeroffset", // 21
    "Sett lav bånd grense", // 22
    "Sett høy bånd grense", // 23
    "Sett nivåoffset", // 24
    "Sett Stereo sep. terskel", // 25
    "Sett høy grense frekvens", // 26
    "Still inn høy grense terskel", // 27
    "Sett lav grense terskel", // 28
    "Sett displayets lysstyrke", // 29
    "Av", // 30
    "Skjermen er dempet!", // 31
    "Oppheve demping, fjern RF+-boksen", // 32
    "AV", // 33
    "SKANNER...", // 34
    "Tuner ikke oppdaget", // 35
    "AM-antenneforsterkning", // 36
    "FM AGC", // 37
    "Vis RDS-feil", // 38
    "Språk", // 39
    "Velg språk", // 40
    "TRYKK MODE FOR Å LAGRE & AVSLUTTE", // 41
    "På", // 42
    "Softmute FM", // 43 ***
    "Softmute AM", // 44 ***
    "Pip ved båndkant", // 45
    "Region", // 46 ***
    "Europa", // 47
    "Amerika", // 48
    "Vis understrek i RDS", // 49
    "USB modus", // 50
    "Wi-Fi aktiv", // 51
    "Sett opp Wi-Fi", // 52
    "Koblet til: ", // 53
    "for å sette opp Wi-Fi", // 54
    "Prøver å koble til Wi-Fi", // 55
    "MISLYKKET!", // 56
    "TILKOBLET!", // 57
    "Stationlist klient IP", // 58
    "Vis SW-bånd", // 59
    "RDS filter", // 60 ***
    "Vis PI feil", // 61
    "Bruk squelch", // 62
    "Modulasjonsmåler", // 63
    "AM Støydemper", // 64
    "FM Støydemper", // 65
    "Standarder lastet", // 66
    "Lydutgang modus", // 67
    "Tillat tuning når\nskjerm avslått", // 68
    "Inverter displayet", // 69
    "Om programvaren", // 70
    "Hovedkode:", // 71
    "Bidragsytere:", // 72
    "Ukjent", // 73
    "Skjermspareralternativer", // 74
    "Tidsavbruddstimer", // 75
    "Skjerm av", // 76
    "Tema", // 77
    "Skin", // 78 ***
    "Oppdaget applikasjoner", // 79
    "Min.", // 80 ***
    "Dynamisk SPI hastighet", // 81
    "Skannefølsomhet", // 82
    "INGEN", // 83
    "Programvareversjon", // 84
    "Frekvens skrifttype", // 85
    "Auto", // 86
    "Ingen AF", // 87
    "Ingen EON", // 88
    "Ingen RT+", // 89
    "FM standard\ntrinnstørrelse", // 90
    "Skjermsparer", // 91
    "sek", // 92
    "TRYKK BAND FOR Å LUKKE", // 93
    "1% lysstyrke", // 94
    "25% lysstyrke", // 95
    "50% lysstyrke", // 96
    "AM RF Nivå offset:", // 97
    "Signalmeter måleenhet:", // 98
    "Bruk AF:", // 99
    "Velg FM Band:", // 100
    "Velg AM Band:", // 101
    "LB", // 102
    "MB", // 103
    "KB", // 104
    "FM", // 105 ***
    "OIRT", // 106 ***
    "Tune når skjerm av", // 107
    "Velg Modell", // 108
    "Base (ILI9341)", // 109 ***
    "Bærbar (ILI9341)", // 110
    "Bærbar touch (ILI9341)", // 111
    "Titel", // 112
    "Album", // 113 ***
    "Spor", // 114
    "Artist", // 115 ***
    "Komposisjon", // 116
    "Bevegelse", // 117
    "Dirigent", // 118
    "Komponist", // 119
    "Band", // 120 ***
    "Kommentar", // 121
    "Sjanger", // 122
    "Nyheter", // 123
    "Lokale nyheter", // 124
    "Aksjemarked", // 125
    "Sport", // 126 ***
    "Lotteri", // 127
    "Horoskop", // 128
    "Daglig avledning", // 129
    "Helse", // 130
    "Begivenhet", // 131
    "Scene", // 132 ***
    "Kino", // 133
    "TV", // 134 ***
    "Dato/tid", // 135
    "Vær", // 136
    "Trafikk", // 137
    "Alarm", // 138 ***
    "Annonse", // 139
    "Nettsted", // 140
    "Annet", // 141
    "Kort PS", // 142
    "Lang PS", // 143
    "Nå", // 144
    "Neste", // 145
    "Del", // 146
    "Vert", // 147
    "Redaktør", // 148
    "Frekvens", // 149
    "Hjemmeside", // 150
    "Underkanal", // 151
    "Hotline", // 152 ***
    "Studio telefon", // 153
    "Telefon", // 154
    "SMS studio", // 155 ***
    "SMS", // 156 ***
    "E-post hotline", // 157
    "E-post studio", // 158
    "E-post", // 159
    "Chat", // 160 ***
    "Chattesenter", // 161
    "Stem spørsmål", // 162
    "Stemmesenter", // 163
    "Sted", // 164
    "Avtale", // 165
    "Identifikator", // 166
    "Kjøp", // 167
    "Få data", // 168
    "MB std. trinnstørrelse", // 169
    "Tangerine", // 170 ***
    "Ocean", // 171 ***
    "Indigo", // 172 ***
    "Batterialternativer", // 173
    "Vis batterispenning", // 174
    "Vis batteriprosent", // 175
    "RT buffering", // 176 ***
    "Hovedinnstillinger", // 177
    "Lydinnstillinger", // 178
    "Skjerminnstillinger", // 179
    "RDS Innstillinger", // 180
    "FM Innstillinger", // 181
    "AM Innstillinger", // 182
    "Tilkobling", // 183
    "TRYKK MODE FOR Å RETUNERE", // 184
    "AM CoChannelDet", // 185
    "CoChannelDet\nfølsomhet", // 186
    "AM CoChannelDet teller", // 187
    "CoChannelDet teller", // 188
    "HOVED", // 189
    "LYD", // 190
    "SKJERM", // 191
    "RDS", // 192 ***
    "FM", // 193 ***
    "AM", // 194 ***
    "TILKOBLE", // 195
    "DX MODUS", // 196
    "Stationlist ID", // 197 ***
    "AM AGC", // 198
    "FM ettertrykkelse", // 199
    "Lite", // 200
    "Mye", // 201
    "Alt", // 202
    "Rask PS", // 203
    "Standard", // 204
    "Dempet skjerm på\nXDRGTK tilkobling", // 205
    "FMSI stereo forbedring", // 206
    "Kun tilgjengelig\npå TEF6687/6689!", // 207
    "Funksjon ikke tilgjengelig\npå valgt skin!", // 208
    "Begynn å skanne\nminnekanaler", // 209
    "Stopp skanning\nminnekanaler", // 210
    "Ventetid", // 211
    "Start DX-skanning", // 212
    "FM DX-alternativer", // 213
    "Avbryt! Startkanalen er\nmerket som hoppet over.", // 214
    "Auto sorterings AF", // 215
    "Minnekanaler", // 216
    "Utelukke", // 217
    "Kun", // 218
    "Avbryt skanning automatisk", // 219
    "Korrekt PI", // 220
    "Signal", // 221
    "Demp lyden\nmens du skanner", // 222
    "Flybånd", // 223
    "Hold båndknappen\n i 5 sek", // 224
    "Slå av radio", // 225
    "Slå av skjerm", // 226
    "Deaktivert" // 227
  },

  { "Español", // Spanish
    "La dirección rotativa\ncambió", // 1
    "Por favor,\nsuelte el botón", // 2
    "Pantalla girada", // 3
    "Calibrar el medidor\nanalógico", // 4
    "Suelte el botón\ncuando esté listo", // 5
    "Codificador configurado\ncomo óptico", // 6
    "Codificador configurado\ncomo estándar", // 7
    "Receptor FM/AM", // 8
    "Sintonizador: ¡Ninguno!", // 9
    "Volumen:", // 10
    "Convertidor:", // 11
    "Banda baja:", // 12
    "Banda alta:", // 13
    "Desplazamiento de\nnivel RF de FM:", // 14
    "Umbral estéreo:", // 15
    "Esquina de corte alta:", // 16
    "Umbral de corte alto:", // 17
    "Umbral de nivel bajo:", // 18
    "Contraste:", // 19
    "Ajustar volumen", // 20
    "Ajustar desplazamiento\ndel convertidor", // 21
    "Ajustar banda baja", // 22
    "Ajustar banda alta", // 23
    "Ajustar desplazamiento de nivel", // 24
    "Ajustar umbral de\nseparación estéreo", // 25
    "Ajustar frecuencia de corte alta", // 26
    "Ajustar umbral de corte alto", // 27
    "Ajustar umbral de nivel bajo", // 28
    "Ajustar brillo de la pantalla", // 29
    "Apagar", // 30
    "¡La pantalla está en silencio!", // 31
    "Para desactivar,\ndesmarque la casilla RF+", // 32
    "APAG.", // 33
    "ESCANEANDO...", // 34
    "Sintonizador no detectado", // 35
    "AM Ganancia de antena", // 36
    "FM AGC", // 37
    "Mostrar errores RDS", // 38
    "Idioma", // 39
    "Elegir idioma", // 40
    "PRESIONE MODE PARA SALIR Y GUARDAR", // 41
    "Encendido", // 42
    "Silencio FM", // 43
    "Silencio AM", // 44
    "Pitido en el borde\nde la banda", // 45
    "Región", // 46
    "Europa", // 47
    "America", // 48
    "Mostrar guion bajo\nen RDS", // 49
    "Modo USB", // 50
    "Wi-Fi activado", // 51
    "Configurar Wi-Fi", // 52
    "Conectar a: ", // 53
    "para configurar\nWi-Fi", // 54
    "Intentando conectar\na Wi-Fi", // 55
    "¡FALLIDO!", // 56
    "¡CONECTADO!", // 57
    "IP del cliente de la\nlista de estaciones", // 58
    "Mostrar longitud de\nonda de SW", // 59
    "Filtro RDS", // 60
    "Mostrar errores de PI", // 61
    "Usar squelch", // 62
    "Medidor de modulación", // 63
    "Atenuador de\nruido AM", // 64
    "Atenuador de\nruido FM", // 65
    "Carga de configuración\npredeterminada", // 66
    "Salida de audio", // 67
    "Sintonización durante\nel protector", // 68
    "Invertir pantalla", // 69
    "Acerca del software", // 70
    "Código principal:", // 71
    "Colaboradores:", // 72
    "Desconocido", // 73
    "Opciones de protector\nde pantalla", // 74
    "Temporizador de\ntiempo muerto", // 75
    "Apagar pantalla", // 76
    "Tema", // 77
    "Skin", // 78 ***
    "Aplicaciones detectadas", // 79
    "Min.", // 80
    "Velocidad de SPI", // 81
    "Sensibilidad\ndel escaneo", // 82
    "NINGUNA", // 83
    "Versión del software", // 84
    "Fundición de frecuencia", // 85 ***
    "Auto", // 86
    "No AF disponible", // 87
    "No EON disponible", // 88
    "No RT+ disponible", // 89
    "Paso predeterminado\nde FM", // 90
    "Protector de pantalla", // 91
    "seg.", // 92
    "PRESIONE BAND PARA CERRAR", // 93
    "1% de brillo", // 94
    "25% de brillo", // 95
    "50% de brillo", // 96
    "Desplazamiento de\nnivel RF de AM:", // 97
    "Unidad de medidor\nde señal:", // 98
    "Usar AF:", // 99
    "Seleccionar banda de FM:", // 100
    "Seleccionar banda de AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotación con\npantalla apagada", // 107
    "Selector de modelo", // 108
    "Base (ILI9341)", // 109
    "Portátil (ILI9341)", // 110
    "Táctil portátil (ILI9341)", // 111
    "Título", // 112
    "Álbum", // 113
    "Pista", // 114
    "Artista", // 115
    "Composición", // 116
    "Movimiento", // 117
    "Director", // 118
    "Compositor", // 119
    "Banda", // 120
    "Comentario", // 121
    "Género", // 122
    "Noticias", // 123
    "Noticias locales", // 124
    "Mercado de valores", // 125
    "Deportes", // 126
    "Lotería", // 127
    "Horóscopo", // 128
    "Diversión diaria", // 129
    "Salud", // 130
    "Evento", // 131
    "Escena", // 132
    "Cine", // 133
    "TV", // 134
    "Fecha/hora", // 135
    "Clima", // 136
    "Tráfico", // 137
    "Alarma", // 138
    "Anuncio", // 139
    "Sitio web", // 140
    "Otro", // 141
    "PS corto", // 142
    "PS largo", // 143
    "Ahora", // 144
    "Siguiente", // 145
    "Parte", // 146
    "Anfitrión", // 147
    "Editor", // 148
    "Frecuencia", // 149
    "Página de inicio", // 150
    "Subcanal", // 151
    "Línea directa", // 152
    "Teléfono del estudio", // 153
    "Teléfono", // 154
    "SMS al estudio", // 155
    "SMS", // 156
    "Correo electrónico\nde la línea directa", // 157
    "Correo electrónico\ndel estudio", // 158
    "Correo electrónico", // 159
    "Chat", // 160
    "Centro de chat", // 161
    "Pregunta de votación", // 162
    "Centro de votación", // 163
    "Lugar", // 164
    "Cita", // 165
    "Identificador", // 166
    "Compra", // 167
    "Obtener datos", // 168
    "Tamaño de paso\nAM predeterminado", // 169 ***
    "Mandarina", // 170
    "Océano", // 171
    "Índigo", // 172
    "Opciones de batería", // 173
    "Mostrar voltaje", // 174
    "Mostrar porcentaje", // 175
    "Buffering de RT", // 176
    "Configuración principal", // 177
    "Configuración de audio", // 178
    "Configuración de visualización", // 179
    "Configuración de RDS", // 180
    "Configuración de FM", // 181
    "Configuración de AM", // 182
    "Conectividad", // 183
    "PRESIONE MODE PARA VOLVER", // 184
    "Detección de\nco-canal AM", // 185
    "Sensibilidad de\ndetección de co-canal", // 186
    "Umbral de detección\nde co-canal", // 187
    "Contador de detección\nde co-canal", // 188
    "PRINCIPAL", // 189
    "AUDIO", // 190
    "VISUALIZACIÓN", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONECTAR", // 195
    "DX MODE", // 196
    "ID de lista de estaciones", // 197
    "Atenuación de AM", // 198
    "Despreocupación\nde FM", // 199
    "Pequeño", // 200
    "Grande", // 201
    "Todo", // 202
    "PS rápido", // 203
    "Por defecto", // 204
    "Pantalla de mudo\nen la conexión XDRGTK", // 205
    "FMSI mejora del\nsonido estéreo", // 206
    "Función disponible solo\nen TEF6687/6689!", // 207
    "Función no disponible\nsobre el skin seleccionado!", // 208
    "Empiece a buscar\ncanales de memoria", // 209
    "Deja de buscar\ncanales de memoria", // 210
    "Tiempo de espera", // 211
    "Comience a buscar DX", // 212
    "Opciones FM DX", // 213
    "¡Abortar! Se omite\nel canal de inicio.", // 214
    "Orden automático de AF", // 215
    "Canales memorizados", // 216
    "Excluir", // 217
    "Solo", // 218
    "Cancelar automáticamente\nla búsqueda", // 219
    "PI correcto", // 220
    "Señal", // 221
    "Audio mudo\nmientras busca", // 222
    "AIR", // 223
    "Presione el botón\nband durante 5 seg.", // 224
    "Apagado", // 225
    "Pantalla silenciosa", // 226
    "Inactivo" // 227
  },

  { "Português", // Portuguese
    "Direção rotativa\nalterada", // 1
    "Solte o botão,\npor favor", // 2
    "Tela invertida", // 3
    "Calibrar o medidor\nanalógico", // 4
    "Solte o botão quando\nestiver pronto", // 5
    "codificador definido\ncomo óptico", // 6
    "codificador definido\ncomo padrão", // 7
    "Receptor FM/AM", // 8
    "Sintonizador: !Nenhum!", // 9
    "Volume:", // 10
    "Conversor:", // 11
    "Borda da faixa baixa:", // 12
    "Borda da faixa alta:", // 13
    "Deslocamento do nível\nde RF FM:", // 14
    "Limiar estéreo:", // 15
    "Canto de corte alto:", // 16
    "Limiar de corte alto:", // 17
    "Limiar de nível baixo:", // 18
    "Contraste:", // 19
    "Definir volume", // 20
    "Definir deslocamento\ndo conversor", // 21
    "Definir borda\nda faixa baixa", // 22
    "Definir borda\nda faixa alta", // 23
    "Definir deslocamento\nde nível", // 24
    "Limiar de separação\nestéreo", // 25
    "Frequência do canto\nde corte alto", // 26
    "Definir limiar\nde corte alto", // 27
    "Definir limiar\nde nível baixo", // 28
    "Definir brilho\nda tela", // 29
    "Desligado", // 30
    "A tela está silenciada!", // 31
    "Para desativar o silenciamento,\ndesmarque a caixa RF+", // 32
    "DESAT.", // 33
    "ANALISANDO...", // 34
    "Sintonizador não detectado", // 35
    "AM Ganho da antena", // 36
    "FM AGC", // 37
    "Mostrar erros RDS", // 38
    "Idioma", // 39
    "Escolha o idioma", // 40
    "PRESSIONE O MODE PARA SAIR E SALVAR", // 41
    "Ligado", // 42
    "Silenciamento suave FM", // 43
    "Silenciamento suave AM", // 44
    "Bipe na borda da faixa", // 45
    "Região", // 46
    "Europa", // 47
    "América", // 48
    "Mostrar sublinhado\nno RDS", // 49
    "Modo USB", // 50
    "Wi-Fi ativo", // 51
    "Configurar Wi-Fi", // 52
    "Conectar a: ", // 53
    "para configurar\no Wi-Fi", // 54
    "Tentando conectar\nao Wi-Fi", // 55
    "FALHA!", // 56
    "CONECTADO!", // 57
    "IP do cliente da lista\nde estações", // 58
    "Mostrar comprimento\nde onda SW", // 59
    "Filtro RDS", // 60
    "Mostrar erros PI", // 61
    "Usar squelch", // 62
    "Medidor de modulação", // 63
    "Supressor de ruído AM", // 64
    "Supressor de ruído FM", // 65
    "Padrões carregados", // 66
    "Saída de áudio", // 67
    "Sintonização com\nproteção de tela", // 68
    "Inverter a tela", // 69
    "Sobre o software", // 70
    "Código principal:", // 71
    "Contribuidores:", // 72
    "Desconhecido", // 73
    "Opções de proteção\nde tela", // 74
    "Temporizador de\ndesligamento", // 75
    "Desligar a tela", // 76
    "Tema", // 77
    "Skin", // 78
    "Aplicativos detectados", // 79
    "Min.", // 80
    "Velocidade dinâmica\nde SPI", // 81
    "Sensibilidade\nda varredura", // 82
    "NENHUM", // 83
    "Versão do software", // 84
    "Fonte de frequência", // 85 ***
    "Auto", // 86
    "AF não disponível", // 87
    "EON não disponível", // 88
    "RT+ não disponível", // 89
    "Passo padrão FM", // 90
    "Proteção de tela", // 91
    "Segundos", // 92
    "PRESSIONE BAND PARA FECHAR", // 93
    "1% de brilho", // 94
    "25% de brilho", // 95
    "50% de brilho", // 96
    "Deslocamento de nível\nde RF AM:", // 97
    "Unidade de medidor\nde sinal:", // 98
    "Usar AF:", // 99
    "Selecionar faixa FM:", // 100
    "Selecionar faixa AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotativo enquanto a tela\nestá desligada", // 107
    "Seletor de modelo", // 108
    "Básico (ILI9341)", // 109
    "Portátil (ILI9341)", // 110
    "Toque portátil (ILI9341)", // 111
    "Título", // 112
    "Álbum", // 113
    "Faixa", // 114
    "Artista", // 115
    "Composição", // 116
    "Movimento", // 117
    "Maestro", // 118
    "Compositor", // 119
    "Banda", // 120
    "Comentário", // 121
    "Gênero", // 122
    "Notícias", // 123
    "Notícias locais", // 124
    "Mercado de ações", // 125
    "Esportes", // 126
    "Loteria", // 127
    "Horóscopo", // 128
    "Diversão diária", // 129
    "Saúde", // 130
    "Evento", // 131
    "Cena", // 132
    "Cinema", // 133
    "TV", // 134
    "Data/hora", // 135
    "Clima", // 136
    "Tráfego", // 137
    "Alarme", // 138
    "Anúncio", // 139
    "Website", // 140
    "Outros", // 141
    "PS curto", // 142
    "PS longo", // 143
    "Agora", // 144
    "Próximo", // 145
    "Parte", // 146
    "Apresentador", // 147
    "Editor", // 148
    "Frequência", // 149
    "Página inicial", // 150
    "Subcanal", // 151
    "Hotline", // 152
    "Telefone do estúdio", // 153
    "Telefone", // 154
    "SMS do estúdio", // 155
    "SMS", // 156
    "E-mail da hotline", // 157
    "E-mail do estúdio", // 158
    "E-mail", // 159
    "Chat", // 160
    "Centro de chat", // 161
    "Pergunta de votação", // 162
    "Centro de votação", // 163
    "Local", // 164
    "Compromisso", // 165
    "Identificador", // 166
    "Compra", // 167
    "Obter dados", // 168
    "Tamanho padrão\nda etapa AM", // 169
    "Tangerina", // 170
    "Oceano", // 171
    "Índigo", // 172
    "Opções de bateria", // 173
    "Mostrar voltagem", // 174
    "Mostrar porcentagem", // 175
    "Buffering RT", // 176
    "Configurações principais", // 177
    "Configurações de áudio", // 178
    "Configurações de exibição", // 179
    "Configurações RDS", // 180
    "Configurações FM", // 181
    "Configurações AM", // 182
    "Conectividade", // 183
    "PRESSIONE MODO PARA VOLTAR", // 184
    "AM CoChannelDet", // 185
    "Sensibilidade do\nCoChannel Det", // 186
    "Limiar do\nCoChannel Det", // 187
    "Contador do\nCoChannel Det", // 188
    "PRINCIPAL", // 189
    "ÁUDIO", // 190
    "EXIBIÇÃO", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONECTAR", // 195
    "DX MODE", // 196
    "ID da lista de estações", // 197
    "Atenuação AM", // 198
    "Desênfase FM", // 199
    "Pequeno", // 200
    "Grande", // 201
    "Tudo", // 202
    "PS rápido", // 203
    "Predefinição", // 204
    "Tela mudo na\nconexão XDRGTK", // 205
    "FMSI melhoria\ndo som estéreo", // 206
    "Function only available\non TEF6687/6689!", // 207
    "Função não disponível\nno skin selecionado!", // 208
    "Comece a pesquisar\ncanais de memória", // 209
    "Pare de pesquisar\ncanais de memória", // 210
    "Tempo de espera", // 211
    "Comece a pesquisar DX", // 212
    "Opções FM DX", // 213
    "Abortar! O canal\ninicial é ignorado.", // 214
    "Classificar AF\nautomaticamente", // 215
    "Canais memorizados", // 216
    "Excluir", // 217
    "Apenas", // 218
    "Cancelar automatic.\na pesquisa", // 219
    "PI correto", // 220
    "Sinal", // 221
    "Mudo áudio\nenquanto procura", // 222
    "AIR", // 223
    "Pressione o botão\nbanda por 5 seg.", // 224
    "Desligar", // 225
    "Silenciar tela", // 226
    "Inativo" // 227
  }
};
#endif
