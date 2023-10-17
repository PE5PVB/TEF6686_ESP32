// [number of languages][number of texts]

static const char* const myLanguage[17][206] = {
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
    "Volume:", // 10
    "Converter:", // 11
    "Low band edge:", // 12
    "High band edge:", // 13
    "FM RF Level offset:", // 14
    "Stereo threshold:", // 15
    "High Cut corner:", // 16
    "Highcut threshold:", // 17
    "Low level threshold:", // 18
    "Contrast:", // 19
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
    "Tuner version set: v", // 36
    "Please restart tuner", // 37
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
    "USA", // 48
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
    "Show squelch", // 62
    "Modulation meter", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "Defaults loaded", // 66
    "Audio output", // 67
    "Allow tuning during screensaver", // 68
    "Invert display", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Screen off", // 76
    "Theme", // 77
    "Default", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NOT POSSIBLE", // 86
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
    "AM RF Level offset:", // 97
    "Signalmeter unit:", // 98
    "Use AF:", // 99
    "Select FM Band:", // 100
    "Select AM Band:", // 101
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
    " ", // 169
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
    "AM CoChannelDet", // 185
    "CoChannel Det sensitivity", // 186
    "CoChannel Det threshold", // 187
    "CoChannel Det counter", // 188
    "MAIN", // 189
    "AUDIO", // 190
    "DISPLAY", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECT", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Small", // 200
    "Large", // 201
    "All", // 202
    "Fast PS", // 203
    "Detected applications", // 204
    "Min." // 205
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
    "Volume:", // 10
    "Converter:", // 11
    "Lage bandgrens:", // 12
    "Hoge bandgrens:", // 13
    "FM RF niveau afwijking:", // 14
    "Stereo grens:", // 15
    "Hoge tonen afval:", // 16
    "Hoog afval grens:", // 17
    "Laag signaal grens:", // 18
    "Helderheid:", // 19
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
    "Tuner ingesteld: v", // 36
    "Herstart de tuner", // 37
    "Toon RDS fouten", // 38
    "Taal", // 39
    "Kies taal", // 40
    "DRUK OP MODE OM AF TE SLUITEN", // 41
    "Aan", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Piep op bandeinde", // 45
    "Regio", // 46
    "Europa", // 47
    "USA", // 48
    "Toon underscore in RDS", // 49
    "USB mode", // 50
    "Wi-Fi aktief", // 51
    "Configureer Wi-Fi", // 52
    "Verbind met: ", // 53
    "om Wi-Fi in te stellen", // 54
    "Verbinden met Wi-Fi...", // 55
    "MISLUKT!", // 56
    "VERBONDEN!", // 57
    "Stationlist client IP", // 58
    "Toon SW golflengte", // 59
    "RDS filter", // 60
    "Toon PI fouten", // 61
    "Toon squelch", // 62
    "Modulatie meter", // 63
    "AM ruis filter", // 64
    "FM ruis filter", // 65
    "Opnieuw geconfigureerd", // 66
    "Audio uitgang", // 67
    "Afstemmen tijdens schermbeveiliging", // 68
    "Inverteer scherm", // 69
    "Over deze software", // 70
    "Basis code:", // 71
    "Bijgedragen:", // 72
    "Onbekend", // 73
    "Screensaver opties", // 74
    "Auto uitschakelen", // 75
    "Scherm uit", // 76
    "Thema", // 77
    "Default", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NIET MOGELIJK", // 86
    "Geen AF data", // 87
    "Geen EON data", // 88
    "Geen RT+ data", // 89
    "FM stapgrootte", // 90
    "Schermbeveiliging", // 91
    "sec.", // 92
    "DRUK OP BAND OM AF TE SLUITEN", // 93
    "1% helderheid", // 94
    "25% helderheid", // 95
    "50% helderheid", // 96
    "AM RF Level afwijking:", // 97
    "Signaalmeter eenheid:", // 98
    "Gebruik AF:", // 99
    "Select FM Band:", // 100
    "Select AM Band:", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotating while screen off", // 107
    "Model keuze", // 108
    "Basis (ILI9341)", // 109
    "Portable (ILI9341)", // 110
    "Portable touch (ILI9341)", // 111
    "Titel", // 112
    "Album", // 113
    "Nummer", // 114
    "Artiest", // 115
    "Compositie", // 116
    "Deel", // 117
    "Dirigent", // 118
    "Componist", // 119
    "Band", // 120
    "Opmerking", // 121
    "Genre", // 122
    "Nieuws", // 123
    "Lokaal nieuws", // 124
    "Financiële beurs", // 125
    "Sport", // 126
    "Loterij", // 127
    "Horoscoop", // 128
    "Dagelijkse grap", // 129
    "Gezondheid", // 130
    "Evenement", // 131
    "Scene", // 132
    "Bioscoop", // 133
    "TV", // 134
    "Datum/tijd", // 135
    "Weer", // 136
    "Verkeer", // 137
    "Alarm", // 138
    "Advertentie", // 139
    "Website", // 140
    "Overige", // 141
    "Korte naam", // 142
    "Lange naam", // 143
    "Nu", // 144
    "Straks", // 145
    "Deel", // 146
    "Host", // 147
    "Regiseur", // 148
    "Frequentie", // 149
    "Homepage", // 150
    "Subkanaal", // 151
    "Hotline", // 152
    "Studio telefoon", // 153
    "Telefoon", // 154
    "SMS studio", // 155
    "SMS", // 156
    "Email hotline", // 157
    "Email studio", // 158
    "Email", // 159
    "Chat", // 160
    "Chat centrum", // 161
    "Stemming", // 162
    "Stemcentrum", // 163
    "Plaats", // 164
    "Afspraak", // 165
    "Identificatie", // 166
    "Aankoop", // 167
    "Verkrijg data", // 168
    " ", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
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
    "AM CoChannel detectie", // 185
    "CoChannel det. gevoeligheid", // 186
    "CoChannel det. kantelpunt", // 187
    "CoChannel det. teller", // 188
    "ALGEMEEN", // 189
    "GELUID", // 190
    "SCHERM", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "VERBIND", // 195
    "Auto AF sorteren", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Laag", // 200
    "Middel", // 201
    "Alles", // 202
    "Snelle PS", // 203
    "Gedetecteerde applicaties", // 204
    "Min." // 205
  },

  { "Polski", // Polish
    "Kierunek obrotu zmieniony", // 1
    "Zwolnij przycisk", // 2
    "Obrocono ekran", // 3
    "Kalibracja analogowego miernika", // 4
    "Zwolnij przycisk gdy gotowe", // 5
    "wybrano enkoder optyczny", // 6
    "wybrano standardowy enkoder", // 7
    "Odbiornik FM/AM", // 8
    "Tuner: !Brak!", // 9
    "Glosnosc:", // 10
    "Konwerter:", // 11
    "Dolna granica pasma:", // 12
    "Gorna granica pasma:", // 13
    "FM Odchylenie poziomu RF:", // 14
    "Prog Stereo:", // 15
    "Krawedz dolnoprzep..:", // 16
    "Prog dolnoprzepust.:", // 17
    "Prog niskiego sygnalu:", // 18
    "Kontrast:", // 19
    "Ustaw glosnosc", // 20
    "Ustaw odchylenie konwertera", // 21
    "Ustaw dolna granice pasma", // 22
    "Ustaw gorna granice pasma", // 23
    "Ustaw odchylenie sygnalu", // 24
    "Ustaw prog separacji Stereo", // 25
    "Czest. gran. filtra dolnoprzep.", // 26
    "Ustaw prog dolnoprzep.", // 27
    "Ustaw dolna granice sygnalu", // 28
    "Ustaw jasnosc wyswietlacza", // 29
    "Wyl.", // 30
    "Ekran jest wyciszony!", // 31
    "Aby wyl. wyciszenie odznacz RF+", // 32
    "WYL.", // 33
    "SKANOWANIE...", // 34
    "Nie wykryto tunera", // 35
    "Ustawiono wersje tunera: v", // 36
    "Prosze uruchomic pon. tuner", // 37
    "Pokaz bledy RDS", // 38
    "Jezyk", // 39
    "Wybierz swoj jezyk", // 40
    "WCISNIJ MODE ABY ZAMKNAC I ZAPISAC", // 41
    "Wlacz.", // 42
    "Lagodne wyciszanie FM", // 43
    "Lagodne wyciszanie AM", // 44
    "Beep na krawedzi pasma", // 45
    "Region", // 46
    "Europa", // 47
    "USA", // 48
    "Pokaz podkreslenia w RDS", // 49
    "Tryb USB", // 50
    "Wi-Fi aktywne", // 51
    "Konfiguracja Wi-Fi", // 52
    "Polacz z: ", // 53
    "aby skonfigurowac Wi-Fi", // 54
    "Proba polaczenia z Wi-Fi", // 55
    "BLAD.. WiFi wylaczone", // 56
    "POLACZONO!", // 57
    "IP klienta Stationlist", // 58
    "Pokaz dlugosci fal SW", // 59
    "Filtr RDS", // 60
    "Pokaz bledy PI", // 61
    "Pokaz blokade szumow", // 62
    "Wskaznik modulacji", // 63
    "Reduktor szumow AM", // 64
    "Reduktor szumow FM", // 65
    "Zaladowano domyslne", // 66
    "Wyjscie dzwieku", // 67
    "Allow tuning during screensaver", // 68
    "Odwroc kolory wyswietlacza", // 69
    "O oprogramowaniu", // 70
    "Glowny kod:", // 71
    "Wspoltworcy:", // 72
    "Nieznany", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Wylacz ekran", // 76
    "Motyw", // 77
    "Domyslny", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NIEMOZLIWE", // 86
    "AF niedostepny", // 87
    "EON niedostepny", // 88
    "RT+ niedostepny", // 89
    "Minimalny krok FM", // 90
    "Wygaszacz ekranu", // 91
    "Sek", // 92
    "NACISNIJ BAND ABY ZAMKNAC", // 93
    "1% jasnosci", // 94
    "25% jasnosci", // 95
    "50% jasnosci", // 96
    "Odchylenie poziomu RF AM", // 97
    "Jednostka sygnalu", // 98
    "Uzywaj AF", // 99
    "Wybierz pasmo FM", // 100
    "Wybierz pasmo AM", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Stroj. gdy ekran wyl.", // 107
    "Wybor modelu", // 108
    "Podstawowy (ILI9341)", // 109
    "Przenosny (ILI9341)", // 110
    "Przenos. dotyk. (ILI9341)", // 111
    "Tytul", // 112
    "Album", // 113
    "Sciezka", // 114
    "Wykonawca", // 115
    "Kompozycja", // 116
    "Ruch", // 117
    "Dyrygent", // 118
    "Kompozytor", // 119
    "Grupa", // 120
    "Komentarz", // 121
    "Gatunek", // 122
    "Wiadomosci", // 123
    "Lokalne wiadomosci", // 124
    "Gielda", // 125
    "Sport", // 126
    "Loteria", // 127
    "Horoskop", // 128
    "Codzienny zwrot", // 129
    "Zdrowie", // 130
    "Wydarzenie", // 131
    "Scena", // 132
    "Kino", // 133
    "TV", // 134
    "Data/Godzina", // 135
    "Pogoda", // 136
    "Wiadom. drogowe", // 137
    "Alarm", // 138
    "Reklama", // 139
    "Strona internet.", // 140
    "Inne", // 141
    "Krotki PS", // 142
    "Dlugi PS", // 143
    "Teraz", // 144
    "Nastepnie", // 145
    "Czesc", // 146
    "Prowadzacy", // 147
    "Wydawca", // 148
    "Czestotliwosc", // 149
    "Strona domowa", // 150
    "Podkanal", // 151
    "Goraca linia", // 152
    "Telefon do studia", // 153
    "Telefon", // 154
    "SMS do studia", // 155
    "SMS", // 156
    "Email do goracej linii", // 157
    "Email do studia", // 158
    "Email", // 159
    "Czat", // 160
    "Centrum czatu", // 161
    "Pytanie do glosowania", // 162
    "Centrum glosowania", // 163
    "Miejsce", // 164
    "Spotkanie", // 165
    "Identyfikator", // 166
    "Zakup", // 167
    "Pobierz dane", // 168
    " ", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Opcje baterii", // 173
    "Pokaz napiecie", // 174
    "Pokaz procent nalad.", // 175
    "Buforowanie RT", // 176
    "Glowne ustawienia", // 177
    "Ustawienia dzwieku", // 178
    "Ustawienia wyswietlacza", // 179
    "Ustawienia RDS", // 180
    "Ustawienia FM", // 181
    "Ustawienia AM", // 182
    "Lacznosc", // 183
    "NACISNIJ MODE ABY WROCIC", // 184
    "Detek. miedzykanalowy AM", // 185
    "Czulosc detek. miedzykanal.", // 186
    "Prog detek. miedzykanalowego AM", // 187
    "Licznik detek. miedzykanal.", // 188
    "GLOWNE", // 189
    "DZWIEK", // 190
    "WYSWIETLACZ", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "LACZNOSC", // 195
    "Automat. sortowanie AF", // 196
    "Identyfikator Stationlist", // 197
    "Tlumik ant. AM", // 198
    "Deemfaza FM", // 199
    "Male", // 200
    "Duze", // 201
    "Wszystkie", // 202
    "Szybki PS", // 203
    "Wykryte aplikacje", // 204
    "Min." // 205
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
    "Da biste uključili zaslon, poništite kvadratić RF+", // 32
    "ISK.", // 33
    "SKENIRANJE...", // 34
    "Prijemnik nije pronađen", // 35
    "Postavljena verzija prijemnika: v", // 36
    "Molim, ponovno pokrenite prijemnik", // 37
    "Prikaži RDS pogreške", // 38
    "Jezik", // 39
    "Odaberite jezik", // 40
    "PRITISNITE MODE ZA IZLAZ I SPREMANJE", // 41
    "Uključeno", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Beep na rubu frekv. opsega", // 45
    "Regija", // 46
    "Europa", // 47
    "SAD", // 48
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
    "Show PI errors", // 61
    "Prikaži squelch", // 62
    "Mjerač modulacije", // 63
    "AM prigušivač šuma", // 64
    "FM prigušivač šuma", // 65
    "Zadane postavke učitane", // 66
    "Audio izlaz", // 67
    "Allow tuning during screensaver", // 68
    "Invertiraj boju zaslona", // 69
    "O softveru", // 70
    "Glavni izvorni kod:", // 71
    "Suradnici:", // 72
    "Nepoznato", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Zaslon isključiti", // 76
    "Tema dizajna", // 77
    "Zadano", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NIJE MOGUĆE", // 86
    "AF nedostupan", // 87
    "EON nedostupan", // 88
    "RT+ nedostupan", // 89
    "FM min korak", // 90
    "Screensaver", // 91
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
    "Rotating while screen off", // 107
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
    "Get data", // 168
    " ", // 169
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
    "Autom. sortiranje AF-a", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Malo", // 200
    "Veliko", // 201
    "Sve", // 202
    "Brzi PS", // 203
    "Otkrivene aplikacije", // 204
    "Min." // 205
  },

  { "Ελληνικά", // Greek
    "Η διεύθυνση του ρότορα άλλαξε", // 1
    "Ελευθερώστε το πλήκτρο", // 2
    "Η οθόνη αναποδογύρισε", // 3
    "Βαθμονόμηση αναλογικού μετρητή", // 4
    "Αφήστε το πλήκτρο όταν είστε έτοιμοι", // 5
    "ο κωδικοποιητής ρυθμίστηκε σε οπτικός", // 6
    "ο κωδικοποιητής ρυθμίστηκε σε στάνταρ", // 7
    "Δέκτης FM/AM", // 8
    "Tuner: !Κανένα!", // 9
    "Ένταση ήχου:", // 10
    "Μετατροπέας:", // 11
    "Κάτω όριο μπάντας:", // 12
    "Άνω όριο μπάντας:", // 13
    "FM Ολίσθηση επιπέδου RF:", // 14
    "Κατώφλι στέρεο:", // 15
    "Όριο υψηλής αποκοπής:", // 16
    "Κατώφλι υψηλής αποκοπής:", // 17
    "Κατώφλι χαμηλού επιπέδου:", // 18
    "Αντίθεση:", // 19
    "Ορισμός έντασης ήχου", // 20
    "Ολίσθηση (offset) κωδικοποιητή", // 21
    "Κάτω όριο μπάντας", // 22
    "Άνω όριο μπάντας", // 23
    "Επίπεδο ολίσθησης", // 24
    "Κατώφλι διαχωρισμού στέρεο", // 25
    "Συχνότητα υψηλής αποκοπής", // 26
    "Κατώφλι υψηλής αποκοπής", // 27
    "Κατώφλι χαμηλού επιπέδου", // 28
    "Φωτεινότητα οθόνης", // 29
    "Ανενεργό", // 30
    "Οθόνη σε σίγαση!", // 31
    "Για επαναφορά ήχου τσεκάρετε το RF+", // 32
    "ΑΝΕΝ.", // 33
    "ΑΝΙΧΝΕΥΣΗ...", // 34
    "Το tuner δεν εντοπίστηκε", // 35
    "Η έκδοση tuner ορίστηκε σε: v", // 36
    "Παρακαλώ επανεκκινήστε το tuner", // 37
    "Περιθώριο σφαλμάτων RDS", // 38
    "Γλώσσα", // 39
    "Επιλογή γλώσσας", // 40
    "ΠΙΕΣΤΕ MODE ΓΙΑ ΕΞΟΔΟ & ΑΠΟΘΗΚΕΥΣΗ", // 41
    "Ενεργό", // 42
    "Ήπια σίγαση FM", // 43
    "Ήπια σίγαση AM", // 44
    "Ηχητικό σήμα στο όριο μπάντας", // 45
    "Περιοχή", // 46
    "Ευρώπη", // 47
    "Η.Π.Α.", // 48
    "Εμφάνιση κάτω παύλας στο RDS", // 49
    "USB λειτουργία", // 50
    "Wi-Fi ενεργό", // 51
    "Ρύθμιση Wi-Fi", // 52
    "Συνδεθείτε στο: ", // 53
    "για ρύθμιση του WiFi", // 54
    "Προσπάθεια σύνδεσης στο WiFi", // 55
    "ΑΠΟΤΥΧΙΑ.. WiFi ανενεργό", // 56
    "ΣΕ ΣΥΝΔΕΣΗ!", // 57
    "IP πελάτη λίστας σταθμών", // 58
    "Εμφάνιση μήκους κύματος SW", // 59
    "Φίλτρο RDS", // 60
    "Εμφάνιση σφαλμάτων PI", // 61
    "Εμφάνιση squelch", // 62
    "Μετρητής διαμόρφωσης", // 63
    "Απαλοιφή θορύβου AM", // 64
    "Απαλοιφή θορύβου FM", // 65
    "Οι προεπιλογές φορτώθηκαν", // 66
    "Έξοδος ήχου", // 67
    "Allow tuning during screensaver", // 68
    "Αναστροφή χρωμάτων οθόνης", // 69
    "Πληροφορίες λογισμικού", // 70
    "Κύριος κώδικας:", // 71
    "Συνεργάτες:", // 72
    "Άγνωστο", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Οθόνη σβηστή", // 76
    "Θέμα", // 77
    "Προεπιλογή", // 78
    "Κυανό", // 79
    "Βυσσινί", // 80
    "Μονόχρωμο", // 81
    "Ηφαίστειο", // 82
    "Δένδρο", // 83
    "Σάκουρα", // 84
    "Λευκό τοπίο", // 85
    "ΜΗ ΔΥΝΑΤΟ", // 86
    "Μη διαθέσιμο AF", // 87
    "Μη διαθέσιμο EON", // 88
    "Μη διαθέσιμο RT+", // 89
    "Μέγεθος βήματος FM", // 90
    "Φύλαξη οθόνης", // 91
    "Δευτ.", // 92
    "ΠΙΕΣΤΕ BAND ΓΙΑ ΚΛΕΙΣΙΜΟ", // 93
    "1% φωτεινότητα", // 94
    "25% φωτεινότητα", // 95
    "50% φωτεινότητα", // 96
    "AM Ολίσθηση επιπέδου RF:", // 97
    "Μονάδα μέτρησης σήματος:", // 98
    "Χρήση AF:", // 99
    "Επιλογή μπάντας FM:", // 100
    "Επιλογή μπάντας AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Περιστροφή με οθόνη σβηστή", // 107
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
    "TV", // 134
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
    "SMS", // 156
    "Email επικοινωνία", // 157
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
    " ", // 169
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
    "Εντοπισμός ομοκαναλικού AM", // 185
    "Ευαισθησία ομοκαναλικού AM", // 186
    "Κατώφλι ομοκαναλικού AM", // 187
    "Μετρητής ομοκαναλικού AM", // 188
    "ΒΑΣΙΚΕΣ", // 189
    "ΗΧΟΣ", // 190
    "ΕΜΦΑΝΙΣΗ", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "ΣΥΝΔΕΣΗ", // 195
    "Αυτόματη ταξινόμηση AF", // 196
    "ID λίστας σταθμών", // 197
    "AM εξασθένιση", // 198
    "FM αποέμφαση", // 199
    "Μικρό", // 200
    "Μεγάλο", // 201
    "Όλα", // 202
    "Γρήγορο PS", // 203
    "Εντοπισμένες εφαρμογές", // 204
    "Min." // 205
  },

  { "Română", // Romanian
    "Sens rotire schimbat", // 1
    "Eliberaţi butonul", // 2
    "Ecran inversat", // 3
    "Calibraţi S-metrul analog", // 4
    "Eliberaţi butonul cand terminaţi", // 5
    "Encoderul setat pe Optic", // 6
    "Encoderul setat pe Standard", // 7
    "Receptor FM/AM ", // 8
    "Nu există Tuner !", // 9
    "Volum:", // 10
    "Convertor:", // 11
    "Limita inferioară a benzii:", // 12
    "Limita superioară a benzii:", // 13
    "FM offset ptr. nivel RF:", // 14
    "Prag ptr. Stereo :", // 15
    "Limită tăiere inalte:", // 16
    "Prag tăiere inalte:", // 17
    "Prag tăiere joase:", // 18
    "Contrast:", // 19
    "Setează volum", // 20
    "Setează offset ptr convertor ", // 21
    "Setează marginea de jos a benzii", // 22
    "Setează marginea de sus a benzii", // 23
    "Setează nivel offset", // 24
    "Setează prag separare Stereo", // 25
    "Setează limita de sus inalte", // 26
    "Setează prag taiere inalte", // 27
    "Setează pragul nivelului de jos", // 28
    "Setează luminozitatea ptr. ecran", // 29
    "Oprit", // 30
    "Ecran oprit", // 31
    "Ptr a porni debifați RF+ box", // 32
    "OPRIT", // 33
    "Scanare...", // 34
    "Tunerul nu este detectat", // 35
    "Versiune Tuner: v", // 36
    "Vă rog restartați tuner", // 37
    "Arată erorile RDS", // 38
    "Limbă", // 39
    "Alege Limba", // 40
    "Apasa MODE ptr salvare și ieșire", // 41
    "Pornit", // 42
    "FM fără sonor", // 43
    "AM fără sonor", // 44
    "Sunet la marginea benzii", // 45
    "Regiune", // 46
    "Europa", // 47
    "SUA", // 48
    "Arată evidențiat in RDS", // 49
    "Mod USB", // 50
    "Wi-Fi activ", // 51
    "Configurare Wi-Fi", // 52
    "Conectare la: ", // 53
    "Către configurare Wi-Fi", // 54
    "Se conectează Wi-Fi", // 55
    "EȘUAT!", // 56
    "CONECTARE!", // 57
    "Listă rețele IP", // 58
    "Arată lungimea de undă SW", // 59
    "Filtru RDS", // 60
    "Arată erorile PI", // 61
    "Arată limitatorul", // 62
    "Măsurare modulație", // 63
    "Eliminare zgomot AM", // 64
    "Eliminare zgomot FM", // 65
    "Incărcare valori implicite", // 66
    "Ieșire audio ", // 67
    "Allow tuning during screensaver", // 68
    "Arată culorile inversate", // 69
    "Despre soft", // 70
    "Despre cod:", // 71
    "Contribuitori:", // 72
    "Necunoscut", // 73
    "Opțiuni economizor ecran", // 74
    "Intervalul de timp", // 75
    "Ecran oprit", // 76
    "Teme", // 77
    "Implicit", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "Nu este posibil", // 86
    "Fără AF disponibil", // 87
    "Fără EON disponibil", // 88
    "Fără RT+ disponibil", // 89
    "Pasul FM minim", // 90
    "Economizor ecran", // 91
    "Sec", // 92
    "APASĂ BAND PENTRU IEȘIRE", // 93
    "1% luminozitate", // 94
    "25% luminozitate", // 95
    "50% luminozitate", // 96
    "AM compensare nivel RF:", // 97
    "Unitate masură semnal:", // 98
    "Folosește AF:", // 99
    "Alege banda FM:", // 100
    "Alege banda AM:", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotire cand ecranul este oprit", // 107
    "Model selector", // 108
    "Bază (ILI9341)", // 109
    "Portabil (ILI9341)", // 110
    "Portabil tactil (ILI9341)", // 111
    "Titlu", // 112
    "Album", // 113
    "Piesă", // 114
    "Artist", // 115
    "Compozitie", // 116
    "Deplasare", // 117
    "Dirijor", // 118
    "Compozitor", // 119
    "Banda", // 120
    "Comentariu", // 121
    "Genuri", // 122
    "Stiri", // 123
    "Stiri locale", // 124
    "PiataBursiera", // 125
    "Sport", // 126
    "Loterie", // 127
    "Horoscop", // 128
    "Cotidian", // 129
    "Sanatate", // 130
    "Concurs", // 131
    "Scene", // 132
    "Cinema", // 133
    "TV", // 134
    "Data/timp", // 135
    "Meteo", // 136
    "Trafic", // 137
    "Alarma", // 138
    "Avertisment", // 139
    "Website", // 140
    "Other", // 141
    "Scurt PS", // 142
    "Lung PS", // 143
    "Acum", // 144
    "Urmatorul", // 145
    "Part", // 146
    "Host", // 147
    "Editor", // 148
    "Frecventa", // 149
    "Prima pagina", // 150
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
    " ", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Optiuni baterie", // 173
    "Arată voltajul", // 174
    "Arată procentele", // 175
    "Stocare RT", // 176
    "Setarile principale", // 177
    "Setări audio", // 178
    "Setări ecran", // 179
    "Setări RDS", // 180
    "Setări FM", // 181
    "Setări AM", // 182
    "Conectivitate", // 183
    "Apasă MODE pentru ieșire", // 184
    "AM CoChannelDet", // 185
    "Sensibilitate CoChannelDet", // 186
    "Pragul AM CoChannelDet", // 187
    "CoChannelDet counter", // 188
    "PRINCIPAL", // 189
    "AUDIO", // 190
    "ECRAN", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONECTARE", // 195
    "Sortare auto AF", // 196
    "Listă rețele ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Mic", // 200
    "Mare", // 201
    "Toate", // 202
    "PS rapid", // 203
    "Identificare aplicații", // 204
    "Min." // 205
  },

  { "Deutsch", // German
    "Drehrichtung geändert", // 1
    "Bitte Taste loslassen", // 2
    "Bildschirm gedreht", // 3
    "Analogmeter kalibrieren", // 4
    "Taste loslassen wenn bereit", // 5
    "Enkoder auf optisch", // 6
    "Enkoder auf Standard", // 7
    "UKW/AM Empfänger", // 8
    "!KEIN! Tuner", // 9
    "Lautstärke:", // 10
    "Konverter:", // 11
    "Unteres Bandende:", // 12
    "Oberes Bandende:", // 13
    "FM RF-Pegeloffset:", // 14
    "Stereoschwelle:", // 15
    "High-Cut-Ende:", // 16
    "High-Cut-Schwelle:", // 17
    "Low-Level-Schwelle:", // 18
    "Kontrast:", // 19
    "Lautstärke", // 20
    "Konverteroffset", // 21
    "Unteres Bandende", // 22
    "Oberes Bandende", // 23
    "Pegeloffset", // 24
    "Stereotrennschwelle", // 25
    "High-Cut-Eckfrequenz", // 26
    "High-Cut-Schwelle", // 27
    "Low-Level-Schwelle", // 28
    "Anzeigehelligkeit", // 29
    "Aus", // 30
    "Bildschirm abgeschaltet!", // 31
    "RF+ abwählen, um einzuschalten", // 32
    "AUS", // 33
    "SCANNE...", // 34
    "Tuner nicht erkannt", // 35
    "Tunerversion: v", // 36
    "Bitte Tuner neustarten", // 37
    "Zeige RDS Fehler", // 38
    "Sprache", // 39
    "Sprache wählen", // 40
    "MODE drücken zum Beenden & Sichern", // 41
    "Ein", // 42
    "Softmute UKW", // 43
    "Softmute AM", // 44
    "Piepston am Bandende", // 45
    "Region", // 46
    "Europa", // 47
    "USA", // 48
    "Zeige Unterstrich im RDS", // 49
    "USB-Modus", // 50
    "WLAN aktiv", // 51
    "WLAN konfigurieren", // 52
    "Verbinde mit:", // 53
    "um WLAN einzustellen", // 54
    "Verb.versuch zu WLAN", // 55
    "FEHLER! WLAN deaktiviert", // 56
    "VERBUNDEN!", // 57
    "Stationlist Rechner IP", // 58
    "Zeige KW-Wellenlänge", // 59
    "RDS-Filter", // 60
    "Zeige PI Fehler", // 61
    "Zeige Rauschsperre", // 62
    "Modulationspegel", // 63
    "AM Rauschunterdrückung", // 64
    "UKW Rauschunterdrückung", // 65
    "Werkseinstellung geladen", // 66
    "Audioausgabe", // 67
    "Allow tuning during screensaver", // 68
    "Anzeigefarben umkehren", // 69
    "Über diese Software", // 70
    "Hauptcode:", // 71
    "Mitwirkende:", // 72
    "Unbekannt", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Bildschirm aus", // 76
    "Thema", // 77
    "Standard", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NICHT MÖGLICH", // 86
    "Keine AF verfügbar", // 87
    "Kein EON verfügbar", // 88
    "Kein RT+ verfügbar", // 89
    "UKW min. Schrittweite", // 90
    "Bildschirmschoner", // 91
    "Sek", // 92
    "ZUM SCHLIEßEN BAND DRÜCKEN", // 93
    "1% Helligkeit", // 94
    "25% Helligkeit", // 95
    "50% Helligkeit", // 96
    "AM RF Pegeloffset:", // 97
    "Einheit Signalpegel:", // 98
    "Verwende AF:", // 99
    "Wähle UKW Band:", // 100
    "Wähle AM Band:", // 101
    "LW", // 102
    "MW", // 103
    "KW", // 104
    "UKW", // 105
    "OIRT", // 106
    "Rotieren bei Bildschirm aus", // 107
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
    "Kurzer PS", // 142
    "Langer PS", // 143
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
    "E-mail", // 159
    "Chat", // 160
    "Chat-Zentrale", // 161
    "Abstimmung", // 162
    "Abstimmungs-Zentrale", // 163
    "Ort", // 164
    "Termin", // 165
    "Musik-ID", // 166
    "Bezugsquelle", // 167
    "Empfange Daten", // 168
    " ", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Akkuoptionen", // 173
    "Zeige Spannung", // 174
    "Zeige Prozente", // 175
    "RT puffern", // 176
    "Haupteinstellungen", // 177
    "Audioeinstellungen", // 178
    "Displayeinstellung", // 179
    "RDS Einstellungen", // 180
    "UKW Einstellungen", // 181
    "AM Einstellungen", // 182
    "Netzwerk", // 183
    "DRÜCKE MODE FÜR ZURÜCK", // 184
    "AM CoChannelDet", // 185
    "CoChannelDet Empfindlichkeit", // 186
    "AM CoChannelDet Threshold", // 187
    "CoChannelDet counter", // 188
    "HAUPT", // 189
    "AUDIO", // 190
    "ANZEIGE", // 191
    "RDS", // 192
    "UKW", // 193
    "AM", // 194
    "NETZ", // 195
    "AF Autosortierung", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "UKW Deemphasis", // 199
    "Gering", // 200
    "Groß", // 201
    "Alles", // 202
    "Schnelles PS", // 203
    "Erkenne Applikationen", // 204
    "Min." // 205
  },

  { "Czech", // Czech
    "Směr enkóderu byl změněn", // 1
    "Prosím, pusťte tlačítko", // 2
    "Obrazovka otočena", // 3
    "Kalibrace analog. měřiče", // 4
    "Po dokončení pusťte tlačítko", // 5
    "enkóder nastaven na optický", // 6
    "enkóder nastaven na standardní", // 7
    "FM/AM přijímač", // 8
    "Tuner: !ŽÁDNÝ!", // 9
    "Hlasitost:", // 10
    "Konvertor:", // 11
    "Spodek pásma:", // 12
    "Vrch pásma:", // 13
    "FM Offset frekvence:", // 14
    "Práh pro stereo:", // 15
    "Práh utlumeni:", // 16
    "Práh zvuku:", // 17
    "Práh nizkého signálu:", // 18
    "Kontrast:", // 19
    "Hlasitost", // 20
    "Offset frekvence", // 21
    "Spodek pásma", // 22
    "Vrch pásma", // 23
    "Offset signálu", // 24
    "Práh pro stereo", // 25
    "Práh utlumení", // 26
    "Práh signálu pro utlumení", // 27
    "Práh nízkého signálu", // 28
    "Jas", // 29
    "Vyp", // 30
    "Obrazovka je ztlumena!", // 31
    "Pro spuštění zrušte RF+", // 32
    "VYP", // 33
    "SKENUJI...", // 34
    "Tuner nedetekován", // 35
    "Verze tuneru nastavena: v", // 36
    "Prosím, restartujte tuner", // 37
    "Zobrazit chyby v RDS", // 38
    "Jazyk", // 39
    "Vyberte jazyk", // 40
    "ZMÁČKNĚTE MODE PRO ULOŽENÍ", // 41
    "Zap", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Pípnutí na konci pásma", // 45
    "Region", // 46
    "Evropa", // 47
    "USA", // 48
    "Zobrazit podtržítka v RDS", // 49
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
    "Show squelch", // 62
    "Modulation meter", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "Defaults loaded", // 66
    "Audio output", // 67
    "Allow tuning during screensaver", // 68
    "Display color invert", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Screen off", // 76
    "Theme", // 77
    "Default", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NOT POSSIBLE", // 86
    "No AF available", // 87
    "No EON available", // 88
    "No RT+ available", // 89
    "FM min stepsize", // 90
    "Screensaver", // 91
    "Sec", // 92
    "PRESS BAND TO CLOSE", // 93
    "1% brightness", // 94
    "25% brightness", // 95
    "50% brightness", // 96
    "AM RF Level offset:", // 97
    "Signalmeter unit:", // 98
    "Use AF:", // 99
    "Select FM Band:", // 100
    "Select AM Band:", // 101
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
    " ", // 169
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
    "AM CoChannelDet", // 185
    "CoChannelDet sensitivity", // 186
    "AM CoChannelDet threshold", // 187
    "CoChannelDet counter", // 188
    "MAIN", // 189
    "AUDIO", // 190
    "DISPLAY", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECT", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Small", // 200
    "Large", // 201
    "All", // 202
    "Fast PS", // 203
    "Detected applications", // 204
    "Min." // 205
  },

  { "Slovak", // Slovak
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
    "Verzia tuneru nastavená: v", // 36
    "Prosím, reštartujte tuner", // 37
    "Zobraziť chyby v RDS", // 38
    "Jazyk", // 39
    "Vyberte jazyk", // 40
    "STLAČTE MODE PRE ULOŽENIE", // 41
    "Zap", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Pípnutie na konci pásma", // 45
    "Region", // 46
    "Európa", // 47
    "USA", // 48
    "Zobraziť podtržítka v RDS", // 49
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
    "Show squelch", // 62
    "Modulation meter", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "Defaults loaded", // 66
    "Audio output", // 67
    "Allow tuning during screensaver", // 68
    "Display color invert", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Screen off", // 76
    "Theme", // 77
    "Default", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "NOT POSSIBLE", // 86
    "No AF available", // 87
    "No EON available", // 88
    "No RT+ available", // 89
    "FM min stepsize", // 90
    "Screensaver", // 91
    "Sec", // 92
    "PRESS BAND TO CLOSE", // 93
    "1% brightness", // 94
    "25% brightness", // 95
    "50% brightness", // 96
    "AM RF Level offset:", // 97
    "Signalmeter unit:", // 98
    "Use AF:", // 99
    "Select FM Band:", // 100
    "Select AM Band:", // 101
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
    " ", // 169
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
    "AM CoChannelDet", // 185
    "CoChannelDet sensitivity", // 186
    "AM CoChannelDet threshold", // 187
    "CoChannelDet counter", // 188
    "MAIN", // 189
    "AUDIO", // 190
    "DISPLAY", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECT", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Small", // 200
    "Large", // 201
    "All", // 202
    "Fast PS", // 203
    "Detected applications", // 204
    "Min." // 205
  },

  { "Français", // French
    "Sens de rotation modifié", // 1
    "Veuillez relâcher le bouton", // 2
    "Écran inversé", // 3
    "Calibrer le compteur analogique", // 4
    "Relâchez le bouton lorsque prêt", // 5
    "Codeur réglé sur optique", // 6
    "Codeur réglé sur standard", // 7
    "Récepteur FM/AM", // 8
    "Tuner: Aucun!", // 9
    "Volume:", // 10
    "Convertisseur:", // 11
    "Limite de bande basse:", // 12
    "Limite de bande haute:", // 13
    "FM décalage du niveau RF:", // 14
    "Stéréo seuil minimum:", // 15
    "Angle du filtre à coupe haute:", // 16
    "Seuil du filtre à coupe haute:", // 17
    "Seuil minimum de niveau bas:", // 18
    "Contraste:", // 19
    "Réglage du volume", // 20
    "Décalage du convertisseur", // 21
    "Limite de bande basse", // 22
    "Limite de bande haute", // 23
    "Décalage du niveau", // 24
    "Seuil de séparation stéréo", // 25
    "Fréquence de coupe élevée", // 26
    "Seuil de coupe élevée", // 27
    "Seuil de niveau bas", // 28
    "Luminosité de l'affichage", // 29
    "Éteint", // 30
    "L'écran est désactivé!", // 31
    "Pour le réactiver, décochez la case RF+", // 32
    "FERMÉ", // 33
    "RECHERCHE...", // 34
    "Tuner non détecté", // 35
    "Version du récepteur: v", // 36
    "Veuillez redémarrer le récepteur", // 37
    "Montrer les erreurs de décodage RDS", // 38
    "Langage", // 39
    "Choix de la langue", // 40
    "APPUYEZ MODE POUR SORTIE & STOCKAGE", // 41
    "Allumé", // 42
    "Sourdine douce FM", // 43
    "Sourdine douce AM", // 44
    "Bip à la limite de bande", // 45
    "Région", // 46
    "Europe", // 47
    "États-Unis", // 48
    "Montre les tirets du bas du PS", // 49
    "Mode USB", // 50
    "Wi-Fi actif", // 51
    "Configuration du Wi-Fi", // 52
    "Se connecter au réseau:", // 53
    "pour configurer le Wi-Fi", // 54
    "Tentative de connexion en mode Wi-Fi", // 55
    "CONNEXION IMPOSSIBLE... Désactivation du Wi-Fi", // 56
    "CONNECTÉ!", // 57
    "Stationlist client IP", // 58
    "Affihcer la longueur d'onde SW", // 59
    "Filtre RDS", // 60
    "Afficher les erreurs de décodage PI", // 61
    "Afficher le squelch", // 62
    "Compteur de modulation", // 63
    "Réducteur de bruit AM", // 64
    "Réducteur de bruit FM", // 65
    "Paramètres par défaut chargés", // 66
    "Sortie audio", // 67
    "Allow tuning during screensaver", // 68
    "Inverser l'affichage", // 69
    "À propos du logiciel", // 70
    "Code principal :", // 71
    "Contributeurs :", // 72
    "Inconnu", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Affichage éteint", // 76
    "Thème", // 77
    "Défaut", // 78
    "Cyan", // 79
    "Cramoisi", // 80
    "Monochrome", // 81
    "Volcan", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Voile blanc", // 85
    "IMPOSSIBLE", // 86
    "AF indisponible", // 87
    "EON indisponible", // 88
    "RT+ indisponible", // 89
    "Valeur du pas FM par défaut", // 90
    "Screensaver", // 91
    "Sec", // 92
    "APPUYEZ SUR BAND POUR FERMER", // 93
    "1% luminosité", // 94
    "25% luminosité", // 95
    "50% luminosité", // 96
    "AM décalage du niveau RF:", // 97
    "Unité de mesure du signal:", // 98
    "Utilisez le AF:", // 99
    "Sélectionner la bande FM:", // 100
    "Sélectionner la bande AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotation lorsque l'écran est éteint", // 107
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
    " ", // 169
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
    "CoChannelDet sensibilité", // 186
    "AM CoChannelDet sueil", // 187
    "CoChannelDet compteur", // 188
    "PRINCIPAUX", // 189
    "AUDIO", // 190
    "AFFICHAGE", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECTER", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM déemphasie", // 199
    "Petites", // 200
    "Grosses", // 201
    "Toutes", // 202
    "PS rapide", // 203
    "Applications détectées", // 204
    "Min." // 205
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
    "Stereo праг:", // 15
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
    "Версията на тунера е зададена: v", // 36
    "Моля рестартирайте приемника!", // 37
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
    "САЩ", // 48
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
    "Показване на squelch индикатор", // 62
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
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Изключен дисплей", // 76
    "Тема", // 77
    "По подразбиране", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "НЕ Е ВЪЗМОЖНО", // 86
    "AF опцията не е налична", // 87
    "EON опцията не е налична", // 88
    "RT+ опцията не е налична", // 89
    "Размер на стъпката на FM", // 90
    "Авт. заспиване", // 91
    "сек.", // 92
    "НАТИСНЕТЕ BAND ЗА ИЗХОД", // 93
    "1% brightness", // 94
    "25% brightness", // 95
    "50% brightness", // 96
    "AM RF Level offset:", // 97
    "Signalmeter unit:", // 98
    "Use AF:", // 99
    "Select FM Band:", // 100
    "Select AM Band:", // 101
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
    " ", // 169
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
    "AM CoChannelDet", // 185
    "CoChannelDet sensitivity", // 186
    "AM CoChannelDet threshold", // 187
    "CoChannelDet counter", // 188
    "MAIN", // 189
    "AUDIO", // 190
    "DISPLAY", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECT", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Small", // 200
    "Large", // 201
    "All", // 202
    "Fast PS", // 203
    "Detected applications", // 204
    "Min." // 205
  },

  { "Русский", // Russian
    "Изменено направление вращения", // 1
    "Пожалуйста, отпустите кнопку", // 2
    "Экран перевернут", // 3
    "Откалибровать аналоговый метр", // 4
    "Отпустите кнопку, когда будете готовы", // 5
    "энкодер установлен в оптический режим", // 6
    "энкодер установлен в стандартный режим", // 7
    "FM/AM приемник", // 8
    "Тюнер: !Нет!", // 9
    "Громкость:", // 10
    "Конвертер:", // 11
    "Нижняя граница диапазона:", // 12
    "Верхняя граница диапазона:", // 13
    "FM Смещение уровня RF:", // 14
    "Порог стерео:", // 15
    "Угол среза высоких частот:", // 16
    "Порог высокого среза:", // 17
    "Нижний порог уровня:", // 18
    "Контрастность:", // 19
    "Установить громкость", // 20
    "Установить смещение конвертера", // 21
    "Установить низ. диапазона", // 22
    "Установить верх. диапазона", // 23
    "Установить смещение уровня", // 24
    "Установить порог стерео", // 25
    "Установить частоту верх. среза", // 26
    "Установить порог выс. среза", // 27
    "Установить нижний порог уровня", // 28
    "Установить яркость дисплея", // 29
    "Выкл.", // 30
    "Экран отключен!", // 31
    "Чтобы включить звук, снимите флажок RF+", // 32
    "ВЫКЛ.", // 33
    "СКАНИРОВАНИЕ...", // 34
    "Тюнер не обнаружен", // 35
    "Установлена версия тюнера: v", // 36
    "Пожалуйста, перезагрузите тюнер", // 37
    "Показать ошибки RDS", // 38
    "Язык", // 39
    "Выбрать язык", // 40
    "НАЖМИТЕ MODE ДЛЯ ВЫХОДА И СОХР.", // 41
    "Вкл.", // 42
    "Тихий режим FM", // 43
    "Тихий режим AM", // 44
    "Сигнал при достиж. границы диап.", // 45
    "Регион", // 46
    "Европа", // 47
    "США", // 48
    "Показать символ подчерк. в RDS", // 49
    "Режим USB", // 50
    "Wi-Fi активен", // 51
    "Настройка Wi-Fi", // 52
    "Подключиться к: ", // 53
    "для настройки Wi-Fi", // 54
    "Попытка подключения Wi-Fi", // 55
    "НЕ УДАЛОСЬ... Wi-Fi отключен", // 56
    "Подключено!", // 57
    "IP клиента списка станций", // 58
    "Показать длину волны SW", // 59
    "Фильтр RDS", // 60
    "Показать ошибки PI", // 61
    "Показать шумоподавитель", // 62
    "Модуляционный метр", // 63
    "Шумоподавитель AM", // 64
    "Шумоподавитель FM", // 65
    "Загрузка настроек по умолчанию", // 66
    "Аудиовыход", // 67
    "Allow tuning during screensaver", // 68
    "Инвертировать дисплей", // 69
    "О программе", // 70
    "Основной код:", // 71
    "Соавторы:", // 72
    "Неизвестно", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Экран выключен", // 76
    "Тема", // 77
    "По умолчанию", // 78
    "Циан", // 79
    "Малиновый", // 80
    "Монохром", // 81
    "Вулкан", // 82
    "Дендро", // 83
    "Сакура", // 84
    "Белый", // 85
    "НЕВОЗМОЖНО", // 86
    "Нет доступного AF", // 87
    "Нет доступного EON", // 88
    "Нет доступного RT+", // 89
    "Шаг FM по умолчанию", // 90
    "Питание выкл. через", // 91
    "сек", // 92
    "НАЖМИТЕ BAND ДЛЯ ЗАКРЫТИЯ", // 93
    "1% яркости", // 94
    "25% яркости", // 95
    "50% яркости", // 96
    "Смещение уровня AM RF:", // 97
    "Измеритель сигнала:", // 98
    "Режим AF:", // 99
    "Выберите FM-диапазон:", // 100
    "Выберите AM-диапазон:", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Вращение при выкл. экране", // 107
    "Выбор модели", // 108
    "Стандартный (ILI9341)", // 109
    "Портативный (ILI9341)", // 110
    "Портатив. сенсорный (ILI9341)", // 111
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
    "Ежедневные развлечения", // 129
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
    " ", // 169
    "Мандариновый", // 170
    "Океан", // 171
    "Индиго", // 172
    "Варианты батареи", // 173
    "Показать значение батареи", // 174
    "Показать процент батареи", // 175
    "Буферизация RT", // 176
    "Основные настройки", // 177
    "Настройки звука", // 178
    "Настройки отображения", // 179
    "Настройки RDS", // 180
    "Настройки FM", // 181
    "Настройки AM", // 182
    "Соединение", // 183
    "НАЖМИТЕ MODE, ДЛЯ ВОЗВР.", // 184
    "AM CoChannelDet", // 185
    "CoChannelDet чувствительность", // 186
    "Порог AM CoChannelDet", // 187
    "CoChannelDet количество", // 188
    "ОСНОВНОЙ", // 189
    "АУДИО", // 190
    "ДИСПЛЕЙ", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "ПОДКЛЮЧЕНИЕ", // 195
    "Авто сорт. AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Мало", // 200
    "Много", // 201
    "Все", // 202
    "Быстрый PS", // 203
    "Обнаруженные приложения", // 204
    "Min." // 205
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
    "Версія тюнера встановлена: v", // 36
    "Будь ласка, перезавантажте тюнер", // 37
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
    "США", // 48
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
    "Показувати шумоподавлення", // 62
    "Метр модуляції", // 63
    "Помпи засліплення шуму AM", // 64
    "Помпи засліплення шуму FM", // 65
    "Завантажено параметри за замовчуванням", // 66
    "Аудіо вихід", // 67
    "Allow tuning during screensaver", // 68
    "Перевернути дисплей", // 69
    "Про програмне забезпечення", // 70
    "Основний код:", // 71
    "Учасники:", // 72
    "Невідомо", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Екран вимкнено", // 76
    "Тема", // 77
    "За замовчуванням", // 78
    "Ціан", // 79
    "Малиновий", // 80
    "Монохромний", // 81
    "Вулкан", // 82
    "Дендро", // 83
    "Сакура", // 84
    "Білесенький", // 85
    "НЕ МОЖЛИВО", // 86
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
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
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
    "SMS", // 156
    "Email гарячої лінії", // 157
    "Email студії", // 158
    "Email", // 159
    "Чат", // 160
    "Чат-центр", // 161
    "Питання голосування", // 162
    "Центр голосування", // 163
    "Місце", // 164
    "Зустріч", // 165
    "Ідентифікатор", // 166
    "Покупка", // 167
    "Отримати дані", // 168
    " ", // 169
    "Мандариновий", // 170
    "Океан", // 171
    "Індиго", // 172
    "Варіанти батареї", // 173
    "Показати заряд батареї", // 174
    "Показати відсоток батареї", // 175
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
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "ПІДКЛЮЧЕННЯ", // 195
    "Авто сорт. AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Мало", // 200
    "Багато", // 201
    "Усе", // 202
    "Швидкий PS", // 203
    "Виявлені програми", // 204
    "Min." // 205
  },

  { "Italiano", // Italian
    "Senso rotaz. cambiato", // 1
    "Rilascia il pulsante", // 2
    "Schermo capovolto", // 3
    "Calibraz. meter analogico", // 4
    "Se pronto, rilasciare pulsante", // 5
    "Codifica di freq: ottica", // 6
    "Ccodifica di freq: standard", // 7
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
    "Imp. offset conversione", // 21
    "Imp. limite di banda inf.", // 22
    "Imp. limite di banda sup.", // 23
    "Imp. offset di livello", // 24
    "Imp. soglia separaz. stereo", // 25
    "Imp. frequenza taglio alti", // 26
    "Imp. soglia taglio alti", // 27
    "Imp. soglia di livello basso", // 28
    "Imp. la luminosità del display", // 29
    "Off", // 30
    "Schermo disattivato!", // 31
    "Deseleziona box RF+ per audio", // 32
    "OFF", // 33
    "SCANSIONE...", // 34
    "Ricevitore non rilevato", // 35
    "Versione ricevitore impostata: v", // 36
    "Riavvia il ricevitore", // 37
    "Mostra errori RDS", // 38
    "Lingua", // 39
    "Scegli la lingua", // 40
    "SALVA E ESCI: PREMI MODE", // 41
    "On", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Beep sul limite di banda", // 45
    "Regione", // 46
    "Europa", // 47
    "USA", // 48
    "Mostra trattino basso in RDS", // 49
    "Modalità USB", // 50
    "Wi - Fi attivo", // 51
    "Configura Wi - Fi", // 52
    "Connetti a: ", // 53
    "per configurare il Wi - Fi", // 54
    "Connessione al Wi-Fi", // 55
    "NON RIUSCITA. WiFi inattivo", // 56
    "CONNESSO!", // 57
    "IP per StationList", // 58
    "Mostra banda SW in m.", // 59
    "Filtro RDS", // 60
    "Mostra errori PI", // 61
    "Mostra squelch", // 62
    "Meter di modulazione", // 63
    "Soppressione rumore AM", // 64
    "Soppressione rumore FM", // 65
    "Predefiniti caricati", // 66
    "Uscita audio", // 67
    "Allow tuning during screensaver", // 68
    "Inversione schermo", // 69
    "Info sul software", // 70
    "Codice principale:", // 71
    "Collaboratori: ", // 72
    "Sconosciuto", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Schermo spento", // 76
    "Motivo display", // 77
    "Predefinito", // 78
    "Ciano", // 79
    "Cremisi", // 80
    "Monocromatico", // 81
    "Vulcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Sbiancato", // 85
    "IMPOSSIBILE", // 86
    "AF non disponibile", // 87
    "EON non disponibile", // 88
    "RT + non disponibile", // 89
    "Passo di sintonia predef. FM", // 90
    "Salvaschermo", // 91
    "Secondi", // 92
    "PREMI BAND PER CHIUDERE", // 93
    "1 % luminosità", // 94
    "25 % di luminosità", // 95
    "50 % di luminosità", // 96
    "Offset livello RF AM: ", // 97
    "Unità S - meter: ", // 98
    "Use AF:", // 99
    "Select FM Band:", // 100
    "Select AM Band:", // 101
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
    " ", // 169
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
    "AM CoChannelDet", // 185
    "CoChannelDet sensitivity", // 186
    "AM CoChannelDet threshold", // 187
    "CoChannelDet counter", // 188
    "MAIN", // 189
    "AUDIO", // 190
    "DISPLAY", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONNECT", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM deemphasis", // 199
    "Small", // 200
    "Large", // 201
    "All", // 202
    "Fast PS", // 203
    "Detected applications", // 204
    "Min." // 205
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
    "音量:", // 10
    "偏移量:", // 11
    "FM 最低频率:", // 12
    "FM 最高频率:", // 13
    "FM信号偏移量:", // 14
    "立体声阈值:", // 15
    "高切角:", // 16
    "高切门限:", // 17
    "弱信号门限:", // 18
    "屏幕亮度:", // 19
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
    "OFF", // 33
    "搜索中...", // 34
    "未检测到收音芯片", // 35
    "收音芯片版本: v", // 36
    "请重启收音机", // 37
    "显示 RDS errors", // 38
    "语言", // 39
    "选择语言", // 40
    "按 MODE 键退出并保存", // 41
    "打开", // 42
    "FM软静噪", // 43
    "AM软静噪", // 44
    "频率边界嘟声提醒", // 45
    "国家与地区", // 46
    "欧洲(中波9K)", // 47
    "美洲(中波10K)", // 48
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
    "主画面显示SQ", // 62
    "主画面显示M表", // 63
    "AM 噪声消除", // 64
    "FM 噪声消除", // 65
    "恢复出厂设置", // 66
    "音频输出选择", // 67
    "盲操", // 68
    "LCD颜色反转", // 69
    "关于(About)", // 70
    "主程序:", // 71
    "贡献者:", // 72
    "未知", // 73
    "屏保选项", // 74
    "倒计时关机", // 75
    "关闭屏幕", // 76
    "主题&颜色", // 77
    "默认", // 78
    "青色", // 79
    "西瓜红", // 80
    "珍珠白", // 81
    "湖蓝", // 82
    "草绿", // 83
    "樱花紫", // 84
    "纯白", // 85
    "不可用", // 86
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
    "AM 高频信号偏移:", // 97
    "信号单位:", // 98
    "使用 AF:", // 99
    "选择FM波段:", // 100
    "选择AM波段:", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "熄屏操作飞梭", // 107
    "硬件型号选择", // 108
    "原版(ILI9341)", // 109
    "便携版(ILI9341)", // 110
    "便携电阻触摸版(ILI9341)", // 111
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
    " ", // 169
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
    "自动排列AF", // 196
    "Stationlist ID", // 197
    "AM天线衰减", // 198
    "FM去加重", // 199
    "少量", // 200
    "大量", // 201
    "全部", // 202
    "快速 PS", // 203
    "Detected applications", // 204
    "分钟" // 205
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
    "High Cut corner:", // 16
    "Highcut grense:", // 17
    "Low level grense:", // 18
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
    "Tuner versjon sett: v", // 36
    "Start tuneren på nytt", // 37
    "Vis RDS-feil", // 38
    "Språk", // 39
    "Velg språk", // 40
    "TRYKK MODE FOR Å LAGRE & AVSLUTTE", // 41
    "På", // 42
    "Softmute FM", // 43
    "Softmute AM", // 44
    "Pip ved båndkant", // 45
    "Region", // 46
    "Europa", // 47
    "USA", // 48
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
    "RDS filter", // 60
    "Vis PI feil", // 61
    "Vis squelch", // 62
    "Modulasjonsmåler", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "Standarder lastet", // 66
    "Lydutgang modus", // 67
    "Tune når skjermsparer på", // 68
    "Inverter displayet", // 69
    "Om programvaren", // 70
    "Hovedkode:", // 71
    "Bidragsytere:", // 72
    "Ukjent", // 73
    "Skjermspareralternativer", // 74
    "Tidsavbruddstimer", // 75
    "Skjerm av", // 76
    "Tema", // 77
    "Standard", // 78
    "Cyan", // 79
    "Crimson", // 80
    "Monochrome", // 81
    "Volcano", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Whiteout", // 85
    "IKKE MULIG", // 86
    "Ingen AF", // 87
    "Ingen EON", // 88
    "Ingen RT+", // 89
    "FM standard trinnstørrelse", // 90
    "Skjermsparer", // 91
    "sek", // 92
    "TRYKK BAND FOR Å LUKKE", // 93
    "1% lysstyrke", // 94
    "25% lysstyrke", // 95
    "50% lysstyrke", // 96
    "AM RF Nivå offset:", // 97
    "Signalmeter måleenhet:", // 98
    "Bruk AF:", // 99
    "Velg FM Bånd:", // 100
    "Velg AM Bånd:", // 101
    "LW", // 102
    "MW", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Tune når skjerm av", // 107
    "Velg Modell", // 108
    "Base (ILI9341)", // 109
    "Bærbar (ILI9341)", // 110
    "Bærbar touch (ILI9341)", // 111
    "Titel", // 112
    "Album", // 113
    "Spor", // 114
    "Artist", // 115
    "Komposisjon", // 116
    "Bevegelse", // 117
    "Dirigent", // 118
    "Komponist", // 119
    "Band", // 120
    "Kommentar", // 121
    "Sjanger", // 122
    "Nyheter", // 123
    "Lokale nyheter", // 124
    "Aksjemarked", // 125
    "Sport", // 126
    "Lotteri", // 127
    "Horoskop", // 128
    "Daglig avledning", // 129
    "Helse", // 130
    "Begivenhet", // 131
    "Scene", // 132
    "Kino", // 133
    "TV", // 134
    "Dato/tid", // 135
    "Vær", // 136
    "Trafikk", // 137
    "Alarm", // 138
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
    "Hotline", // 152
    "Studio telefon", // 153
    "Telefon", // 154
    "SMS studio", // 155
    "SMS", // 156
    "E-post hotline", // 157
    "E-post studio", // 158
    "E-post", // 159
    "Chat", // 160
    "Chattesenter", // 161
    "Stem spørsmål", // 162
    "Stemmesenter", // 163
    "Sted", // 164
    "Avtale", // 165
    "Identifikator", // 166
    "Kjøp", // 167
    "Få data", // 168
    " ", // 169
    "Tangerine", // 170
    "Ocean", // 171
    "Indigo", // 172
    "Batterialternativer", // 173
    "Vis batteriverdi", // 174
    "Vis batteriprosent", // 175
    "RT buffering", // 176
    "Hovedinnstillinger", // 177
    "Lydinnstillinger", // 178
    "Skjerminnstillinger", // 179
    "RDS Innstillinger", // 180
    "FM Innstillinger", // 181
    "AM Innstillinger", // 182
    "Tilkobling", // 183
    "TRYKK MODE FOR Å RETUNERE", // 184
    "AM CoChannelDet", // 185
    "CoChannelDet sensitivity", // 186
    "AM CoChannelDet threshold", // 187
    "CoChannelDet counter", // 188
    "HOVED", // 189
    "LYD", // 190
    "SKJERM", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "TILKOBLE", // 195
    "Auto sort AF", // 196
    "Stationlist ID", // 197
    "AM ATT", // 198
    "FM ettertrykkelse", // 199
    "Lite", // 200
    "Mye", // 201
    "Alt", // 202
    "Rask PS", // 203
    "Oppdaget applikasjoner", // 204
    "Min." // 205
  },

  { "Español", // Spanish
    "La dirección rotativa cambió", // 1
    "Por favor, suelte el botón", // 2
    "Pantalla girada", // 3
    "Calibrar el medidor analógico", // 4
    "Suelte el botón cuando esté listo", // 5
    "Codificador configurado como óptico", // 6
    "Codificador configurado como estándar", // 7
    "Receptor FM/AM", // 8
    "Sintonizador: ¡Ninguno!", // 9
    "Volumen:", // 10
    "Convertidor:", // 11
    "Banda baja:", // 12
    "Banda alta:", // 13
    "Desplazamiento de nivel RF de FM:", // 14
    "Umbral estéreo:", // 15
    "Esquina de corte alta:", // 16
    "Umbral de corte alto:", // 17
    "Umbral de nivel bajo:", // 18
    "Contraste:", // 19
    "Ajustar volumen", // 20
    "Ajustar desplazamiento del convertidor", // 21
    "Ajustar banda baja", // 22
    "Ajustar banda alta", // 23
    "Ajustar desplazamiento de nivel", // 24
    "Ajustar umbral de separación estéreo", // 25
    "Ajustar frecuencia de corte alta", // 26
    "Ajustar umbral de corte alto", // 27
    "Ajustar umbral de nivel bajo", // 28
    "Ajustar brillo de la pantalla", // 29
    "Apagar", // 30
    "¡La pantalla está en silencio!", // 31
    "Para desactivar, desmarque la casilla RF+", // 32
    "APAGADO", // 33
    "ESCANEANDO...", // 34
    "Sintonizador no detectado", // 35
    "Versión del sintonizador establecida: v", // 36
    "Por favor, reinicie el sintonizador", // 37
    "Mostrar errores RDS", // 38
    "Idioma", // 39
    "Elegir idioma", // 40
    "PRESIONE MODE PARA SALIR Y GUARDAR", // 41
    "Encendido", // 42
    "Silencio FM", // 43
    "Silencio AM", // 44
    "Pitido en el borde de la banda", // 45
    "Región", // 46
    "Europa", // 47
    "EE. UU.", // 48
    "Mostrar guion bajo en RDS", // 49
    "Modo USB", // 50
    "Wi-Fi activado", // 51
    "Configurar Wi-Fi", // 52
    "Conectar a: ", // 53
    "para configurar Wi-Fi", // 54
    "Intentando conectar a Wi-Fi", // 55
    "¡FALLIDO!", // 56
    "¡CONECTADO!", // 57
    "IP del cliente de la lista de estaciones", // 58
    "Mostrar longitud de onda de SW", // 59
    "Filtro RDS", // 60
    "Mostrar errores de PI", // 61
    "Mostrar squelch", // 62
    "Medidor de modulación", // 63
    "Atenuador de ruido AM", // 64
    "Atenuador de ruido FM", // 65
    "Carga de configuración predeterminada", // 66
    "Salida de audio", // 67
    "Allow tuning during screensaver", // 68
    "Invertir pantalla", // 69
    "Acerca del software", // 70
    "Código principal:", // 71
    "Colaboradores:", // 72
    "Desconocido", // 73
    "Screensaver options", // 74
    "Time-out timer", // 75
    "Apagar pantalla", // 76
    "Tema", // 77
    "Predeterminado", // 78
    "Cian", // 79
    "Carmesí", // 80
    "Monocromo", // 81
    "Volcán", // 82
    "Dendro", // 83
    "Sakura", // 84
    "Blanqueo total", // 85
    "NO ES POSIBLE", // 86
    "No hay AF disponible", // 87
    "No hay EON disponible", // 88
    "No hay RT+ disponible", // 89
    "Paso predeterminado de FM", // 90
    "Protector de pantalla", // 91
    "seg.", // 92
    "PRESIONE BAND PARA CERRAR", // 93
    "1% de brillo", // 94
    "25% de brillo", // 95
    "50% de brillo", // 96
    "Desplazamiento de nivel RF de AM:", // 97
    "Unidad de medidor de señal:", // 98
    "Usar AF:", // 99
    "Seleccionar banda de FM:", // 100
    "Seleccionar banda de AM:", // 101
    "LW", // 102
    "AM", // 103
    "SW", // 104
    "FM", // 105
    "OIRT", // 106
    "Rotación con pantalla apagada", // 107
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
    "Correo electrónico de la línea directa", // 157
    "Correo electrónico del estudio", // 158
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
    " ", // 169
    "Mandarina", // 170
    "Océano", // 171
    "Índigo", // 172
    "Opciones de batería", // 173
    "Mostrar voltaje", // 174
    "Mostrar porcentaje", // 175
    "Buffering de RT", // 176
    "Configuración principal", // 177
    "Configuración de audio", // 178
    "Configuración de pantalla", // 179
    "Configuración de RDS", // 180
    "Configuración de FM", // 181
    "Configuración de AM", // 182
    "Conectividad", // 183
    "PRESIONE MODE PARA VOLVER", // 184
    "Detección de co-canal AM", // 185
    "Sensibilidad de detección de co-canal", // 186
    "Umbral de detección de co-canal", // 187
    "Contador de detección de co-canal", // 188
    "PRINCIPAL", // 189
    "AUDIO", // 190
    "PANTALLA", // 191
    "RDS", // 192
    "FM", // 193
    "AM", // 194
    "CONECTAR", // 195
    "Orden automático de AF", // 196
    "ID de lista de estaciones", // 197
    "Atenuación de AM", // 198
    "Despreocupación de FM", // 199
    "Pequeño", // 200
    "Grande", // 201
    "Todo", // 202
    "PS rápido", // 203
    "Aplicaciones detectadas", // 204
    "Min." // 205
  }
};
