// [number of languages][number of texts][max. length of text]

static const char* const myLanguage[15][100] = {
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
    "Trying to connect with Wi-Fi", // 55
    "FAILED.. WiFi disabled", // 56
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
    "FM OIRT 30 kHz steps", // 68
    "Invert display", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Power options", // 74
    "Deep sleep", // 75
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
	"Use AF:" // 99
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
    "MISLUKT! WiFi uitgeschakeld", // 56
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
    "FM OIRT 30 kHz steps", // 68
    "Inverteer scherm", // 69
    "Over deze software", // 70
    "Basis code:", // 71
    "Bijgedragen:", // 72
    "Onbekend", // 73
    "Bespaar opties", // 74
    "Volledig uit", // 75
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
	"Gebruik AF:" // 99
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
    "WYL", // 33
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
    "Kroki co 30 kHz na OIRT", // 68
    "Odwroc kolory wyswietlacza", // 69
    "O oprogramowaniu", // 70
    "Glowny kod:", // 71
    "Wspoltworcy:", // 72
    "Nieznany", // 73
    "Opcje zasilania", // 74
    "Glebokie uspienie", // 75
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
    "Odchylenie poziomu RF AM:", // 97
    "Jednostka sygnalu:", // 98
    "Uzywaj AF:" // 99
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
    "FM OIRT 30 kHz koraci", // 68
    "Invertiraj boju zaslona", // 69
    "O softveru", // 70
    "Glavni izvorni kod:", // 71
    "Suradnici:", // 72
    "Nepoznato", // 73
    "Power options", // 74
    "Deep sleep", // 75
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
	"Use AF:" // 99
  },

  { "Ελληνικά", // Greek
    "Η διεύθυνση του ρότορα άλλαξε", // 1
    "Ελευθερώστε το πλήκτρο", // 2
    "Η οθόνη αναποδογύρισε", // 3
    "Βαθμονόμηση αναλογικού μετρητή", // 4
    "Αφήστε το πλήκτρο όταν είστε έτοιμοι", // 5
    "ο κωδικοποιητής ρυθμίστηκε σε οπτικός", // 6
    "ο κωδικοποιητής ρυθμίστηκε σε στάνταρ", // 7
    "FM/AM δέκτης", // 8
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
    "Εμφάνιση σφαλμάτων RDS", // 38
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
    "για ρύθμιση του Wi-Fi", // 54
    "Προσπάθεια σύνδεσης με το Wi-Fi", // 55
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
    "FM OIRT βήματα 30 kHz", // 68
    "Αναστροφή χρωμάτων οθόνης", // 69
    "Πληροφορίες λογισμικού", // 70
    "Κύριος κώδικας:", // 71
    "Συνεργάτες:", // 72
    "Άγνωστο", // 73
    "Επιλογές ενέργειας", // 74
    "Βαθιά αναμονή", // 75
    "Οθόνη κλειστή", // 76
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
	"Χρήση AF:" // 99
  },

  { "Romana", // Romanian
    "Sens rotire schimbat", // 1
    "Eliberati butonul", // 2
    "Ecran inversat", // 3
    "Calibrati S-metrul analog", // 4
    "Eliberati butonul cand terminati", // 5
    "Encoderul setat pe Optic", // 6
    "Encoderul setat pe Standard", // 7
    "Receptor FM/AM ", // 8
    "Nu exista Tuner !", // 9
    "Volum:", // 10
    "Convertor:", // 11
    "Limita inferioara a benzii:", // 12
    "Limita superioara a benzii:", // 13
    "FM offset ptr. nivel RF:", // 14
    "Prag ptr. Stereo :", // 15
    "Limita taiere inalte:", // 16
    "Prag taiere inalte:", // 17
    "Prag taiere joase:", // 18
    "Contrast:", // 19
    "Seteaza volum", // 20
    "Seteaza offset ptr convertor ", // 21
    "Seteaza marginea de jos a benzii", // 22
    "Seteaza marginea de sus a benzii", // 23
    "Seteaza nivel offset", // 24
    "Seteaza prag separare Stereo", // 25
    "Seteaza limita de sus inalte", // 26
    "Seteaza prag taiere inalte", // 27
    "Seteaza pragul nivelului de jos", // 28
    "Seteaza luminozitatea ptr. Display ", // 29
    "Oprit", // 30
    "Ecran oprit", // 31
    "Ptr a porni debifati RF+ box", // 32
    "Oprit", // 33
    "Scanare...", // 34
    "Tunerul nu este detectat", // 35
    "Versiune Tuner: v", // 36
    "Va rog restartati tuner", // 37
    "Arata erorile RDS", // 38
    "Limba", // 39
    "Alege Limba", // 40
    "Apasa MODE pentru a salva si iesi", // 41
    "Pornit", // 42
    "FM fara sonor", // 43
    "AM fara sonor", // 44
    "Sunet la marginea Benzii", // 45
    "Regiune", // 46
    "Europa", // 47
    "SUA", // 48
    "Arata evidentiat in RDS", // 49
    "USB mode", // 50
    "Wi-Fi active", // 51
    "Configure Wi-Fi", // 52
    "Connect to: ", // 53
    "to configure Wi-Fi", // 54
    "Trying to connect with Wi-Fi", // 55
    "FAILED.. WiFi disabled", // 56
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
    "FM OIRT 30 kHz steps", // 68
    "Display color invert", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Power options", // 74
    "Deep sleep", // 75
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
	"Use AF:" // 99
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
    "Stereotrennerschwelle", // 25
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
    "MODE DRÜCKEN ZUM BEENDEN UND SICHERN", // 41
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
    "Versuche WLAN zu verbinden", // 55
    "FEHLER.. WLAN deaktiviert", // 56
    "VERBUNDEN!", // 57
    "Stationlist Client IP", // 58
    "Zeige KW-Wellenlänge", // 59
    "RDS-Filter", // 60
    "Zeige PI Fehler", // 61
    "Zeige Rauschsperre", // 62
    "Modulationspegel", // 63
    "AM Rauschunterdrückung", // 64
    "UKW Rauschunterdrückung", // 65
    "Werkseinstellung geladen", // 66
    "Audioausgabe", // 67
    "30 kHz Schritte auf OIRT", // 68
    "Anzeigefarben umkehren", // 69
    "Über diese Software", // 70
    "Hauptcode:", // 71
    "Mitwirkende:", // 72
    "Unbekannt", // 73
    "Energieeinstellungen", // 74
    "Komplett aus", // 75
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
    "AM RF Level offset:", // 97
    "Signalmeter unit:", // 98
	"Use AF:" // 99
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
    "ZMÁČKNĚTE MODE PRO VYPNUTÍ A ULOŽENÍ", // 41
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
    "Trying to connect with Wi-Fi", // 55
    "FAILED.. WiFi disabled", // 56
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
    "FM OIRT 30 kHz steps", // 68
    "Display color invert", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Power options", // 74
    "Deep sleep", // 75
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
	"Use AF:" // 99
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
    "STLAČTE MODE PRE VYPNUTIE A ULOŽENIE", // 41
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
    "Trying to connect with Wi-Fi", // 55
    "FAILED.. WiFi disabled", // 56
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
    "FM OIRT 30 kHz steps", // 68
    "Display color invert", // 69
    "About software", // 70
    "Main code:", // 71
    "Contributors:", // 72
    "Unknown", // 73
    "Power options", // 74
    "Deep sleep", // 75
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
	"Use AF:" // 99
  },

  { "Français", // French
    "Sens de rotation modifié", // 1
    "Veuillez relâcher le bouton", // 2
    "Écran inversé", // 3
    "Calibrer le compteur analogique", // 4
    "Relâchez le bouton lorsque vous êtes prêt", // 5
    "Codeur réglé sur \"Optical\"", // 6
    "Codeur réglé sur \"Standard\"", // 7
    "Récepteur FM/AM", // 8
    "Récepteur: Aucun !", // 9
    "Volume :", // 10
    "Convertisseur :", // 11
    "Limite de bande basse:", // 12
    "Limite de bande haute:", // 13
    "FM Décalage du niveau RF:", // 14
    "Seuil minimum pour la Stéréo :", // 15
    "Angle du filtre High Cut :", // 16
    "Seuil minimum pour le filtre High Cut :", // 17
    "Seuil minimum de niveau bas :", // 18
    "Contraste:", // 19
    "Réglage du volume", // 20
    "Réglage du décalage du convertisseur", // 21
    "Réglage de la limite de bande basse", // 22
    "Réglage de la limite de bande haute", // 23
    "Réglage du décalage du niveau", // 24
    "Réglage du seuil minimum pour la séparation de la Stéréo", // 25
    "Réglage de la fréquence pour l'angle du filtre High Cut", // 26
    "Réglage du seuil minimum pour le filtre High Cut", // 27
    "Réglage du seuil minimum de niveau bas", // 28
    "Réglage de la luminosité de l'affichage", // 29
    "Éteint", // 30
    "L'écran est désactivé !", // 31
    "Pour le réactiver, décochez la case RF+", // 32
    "ÉTEINT", // 33
    "RECHERCHE...", // 34
    "Récepteur non détecté", // 35
    "Version du récepteur : v", // 36
    "Veuillez redémarrer le récepteur", // 37
    "Montrer les erreurs de décodage RDS", // 38
    "Langage", // 39
    "Choix de la langue", // 40
    "APPUYEZ SUR MODE POUR SORTIR ET SAUVEGARDER", // 41
    "Allumé", // 42
    "Sourdine douce FM", // 43
    "Sourdine douce AM", // 44
    "Émettre un bip lorsque la limite de bande est atteinte", // 45
    "Région", // 46
    "Europe", // 47
    "États-Unis", // 48
    "Remplacer les espaces du PS (RDS) par des tirets du bas", // 49
    "Mode USB", // 50
    "Wi-Fi actif", // 51
    "Configuration du Wi-Fi", // 52
    "Se connecter au réseau :", // 53
    "pour configurer le Wi-Fi", // 54
    "Tentative de connexion en mode Wi-Fi", // 55
    "CONNEXION IMPOSSIBLE... Désactivation du Wi-Fi", // 56
    "CONNECTÉ !", // 57
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
    "Pas de 30 kHz pour la bande OIRT", // 68
    "Inverser l'affichage", // 69
    "À propos du logiciel", // 70
    "Code principal :", // 71
    "Contributeurs :", // 72
    "Inconnu", // 73
    "Options d'énergie", // 74
    "Veille profonde", // 75
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
    "PRESS BAND TO CLOSE", // 93
    "1% brightness", // 94
    "25% brightness", // 95
    "50% brightness", // 96
    "AM RF Level offset:", // 97
    "Signalmeter unit:", // 98
	"Use AF:" // 99
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
    "FM OIRT 30 kHz стъпки", // 68
    "Обръщане на дисплея", // 69
    "Относно софтуера", // 70
    "Главен код:", // 71
    "Сътрудници:", // 72
    "Неизвестно", // 73
    "Опции при заспиване", // 74
    "Режим дълбок сън", // 75
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
	"Use AF:" // 99
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
    "Установить низ. границу диапазона", // 22
    "Установить верх. границу диапазона", // 23
    "Установить смещение уровня", // 24
    "Установить порог стерео", // 25
    "Установить частоту верхнего среза", // 26
    "Установить порог высокого среза", // 27
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
    "Сигнал при достижении границы диапазона", // 45
    "Регион", // 46
    "Европа", // 47
    "США", // 48
    "Показать символ подчеркивания в RDS", // 49
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
    "FM OIRT с шагом 30 кГц", // 68
    "Инвертировать дисплей", // 69
    "О программе", // 70
    "Основной код:", // 71
    "Соавторы:", // 72
    "Неизвестно", // 73
    "Параметры питания", // 74
    "Глубокий сон", // 75
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
    "Экран выкл. через", // 91
    "сек", // 92
    "НАЖМИТЕ BAND ДЛЯ ЗАКРЫТИЯ", // 93
    "1% яркости", // 94
    "25% яркости", // 95
    "50% яркости", // 96
    "Смещение уровня AM RF:", // 97
    "Измеритель сигнала:", // 98
	"Режим AF:" // 99
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
    "Встановити нижню межу діапазону", // 22
    "Встановити верхню межу діапазону", // 23
    "Встановити зміщення рівня", // 24
    "Встановити поріг стерео", // 25
    "Встановити частоту верх. відсіку", // 26
    "Встановити поріг Вис. частот", // 27
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
    "FM OIRT 30 кГц кроки", // 68
    "Перевернути дисплей", // 69
    "Про програмне забезпечення", // 70
    "Основний код:", // 71
    "Учасники:", // 72
    "Невідомо", // 73
    "Опції живлення", // 74
    "Глибокий сон", // 75
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
    "Заставка", // 91
    "с", // 92
    "НАТИСНІТЬ BAND ДЛЯ ЗАКРИТТЯ", // 93
    "1% яскравості", // 94
    "25% яскравості", // 95
    "50% яскравості", // 96
    "Зміщення рівня AM RF:", // 97
    "Вимірник сигналу:", // 98
	"Режим AF:" // 99
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
    "Passo 30 kHz per FM OIRT", // 68
    "Inversione schermo", // 69
    "Info sul software", // 70
    "Codice principale:", // 71
    "Collaboratori: ", // 72
    "Sconosciuto", // 73
    "Opzioni risparmio energia", // 74
    "Deep sleep", // 75
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
	"Use AF:" // 99
  },

  { "Simplified Chinese", // Simplified Chinese
    "飞梭方向改变了", // 1
    "请释放按钮", // 2
    "屏幕翻转了", // 3
    "校准模拟S表", // 4
    "校准成功后请放开按钮", // 5
    "设置为光学编码器", // 6
    "设置为标准编码器", // 7
    "FM/AM 收音机", // 8
    "没有收音芯片 ！", // 9
    "音量:", // 10
    "偏移量:", // 11
    "FM 最低频率:", // 12
    "FM 最高频率:", // 13
    "FM信号偏移量:", // 14
    "立体声阈值:", // 15
    "High Cut corner:", // 16
    "Highcut threshold:", // 17
    "弱信号门限:", // 18
    "对比度:", // 19
    "设置音量", // 20
    "设置频率偏移量", // 21
    "设置 FM 最低频率", // 22
    "设置 FM 最高频率", // 23
    "Set level offset", // 24
    "设置立体声门限", // 25
    "Set high cut corner frequency", // 26
    "Set High cut threshold", // 27
    "设置弱信号门限", // 28
    "设置屏幕显示亮度", // 29
    "Off", // 30
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
    "On", // 42
    "FM软静噪", // 43
    "AM软静噪", // 44
    "频率边界嘟一声", // 45
    "国家与地区", // 46
    "欧洲", // 47
    "美洲", // 48
    "Show underscore in RDS", // 49
    "USB 模式", // 50
    "打开Wifi", // 51
    "Wi-Fi 配置", // 52
    "连接到: ", // 53
    "配置 Wi-Fi", // 54
    "尝试连接Wifi到", // 55
    "失败.. 关闭WiFi", // 56
    "连接成功!", // 57
    "Stationlist 客户端 IP", // 58
    "显示短波米波段", // 59
    "RDS filter", // 60
    "显示 PI errors", // 61
    "显示软静音", // 62
    "M表", // 63
    "AM Noise blanker", // 64
    "FM Noise blanker", // 65
    "恢复出厂设置", // 66
    "音频输出", // 67
    "FM OIRT 30 kHz steps", // 68
    "LCD颜色反转", // 69
    "关于(About)", // 70
    "主程序:", // 71
    "贡献列表:", // 72
    "未知", // 73
    "电源选项", // 74
    "深度睡眠", // 75
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
    "屏幕1% 亮度", // 94
    "屏幕25% 亮度", // 95
    "屏幕50% 亮度", // 96
    "AM 高频信号偏移:", // 97
    "信号单位:", // 98
	"Use AF:" // 99
  }
};

static const char* const myCountries[] {
  "Germany", // 0
  "Greece", // 1
  "Marocco", // 2
  "Moldova", // 3
  "Algeria", // 4
  "Cyprus", // 5
  "Czech R.", // 6
  "Ireland", // 7
  "Estonia", // 8
  "Andorra", // 9
  "SanMarino", // 10
  "Poland", // 11
  "Turkey", // 12
  "Israel", // 13
  "Switzerl.", // 14
  "Vatican", // 15
  "Macedonia", // 16
  "Italy", // 17
  "Jordan", // 18
  "Slovakia", // 19
  "Belgium", // 20
  "Finland", // 21
  "Syria", // 22
  "Serbia", // 23
  "Ukraine", // 24
  "Russia", // 25
  "Luxemb.", // 26
  "Tunisia", // 27
  "Azores", // 28
  "Bulgaria", // 29
  "Madeira", // 30
  "Netherl.", // 31
  "Portugal", // 32
  "Albania", // 33
  "Denmark", // 34
  "Liechtst.", // 35
  "Latvia", // 36
  "Slovenia", // 37
  "Austria", // 38
  "Gibraltar", // 39
  "Iceland", // 40
  "Lebanon", // 41
  "Hungary", // 42
  "Iraq", // 43
  "Monaco", // 44
  "Malta", // 45
  "U.K.", // 46
  "Lithunia", // 47
  "Croatia", // 48
  "Libya", // 49
  "Canaries", // 50
  "Romania", // 51
  "Spain", // 52
  "Sweden", // 53
  "Egypt", // 54
  "France", // 55
  "Norway", // 56
  "Belarus", // 57
  "Bosnia" // 58
};

static const char* const myLanguages[] {
  "Unknown", // 0
  "Albanian", // 1
  "Breton", // 2
  "Catalan", // 3
  "Croatian", // 4
  "Welsh", // 5
  "Czech", // 6
  "Danish", // 7
  "German", // 8
  "English", // 9
  "Spanish", // 10
  "Esperanto", // 11
  "Estonian", // 12
  "Basque", // 13
  "Faroese", // 14
  "French", // 15
  "Frisian", // 16
  "Irish", // 17
  "Gaelic", // 18
  "Galician", // 19
  "Icelandic", // 20
  "Italian", // 21
  "Lappish", // 22
  "Latin", // 23
  "Latvian", // 24
  "Luxemb.", // 25
  "Lithuan.", // 26
  "Hungarian", // 27
  "Maltese", // 28
  "Dutch", // 29
  "Norwegian", // 30
  "Occitan", // 31
  "Polish", // 32
  "Portug.", // 33
  "Romanian", // 34
  "Romansh", // 35
  "Serbian", // 36
  "Slovak", // 37
  "Slovene", // 38
  "Finnish", // 39
  "Swedish", // 40
  "Turkish", // 41
  "Flemish", // 42
  "Walloon", // 43
  "Ukranian", // 44
  "Russian", // 45
  "Moldavian", // 46
  "Macedon.", // 47
  "Hebrew", // 48
  "Greek", // 49
  "Georgian", // 50
  "Bulgarian", // 51
  "Armenian", // 52
  "Arabic" // 53
};
