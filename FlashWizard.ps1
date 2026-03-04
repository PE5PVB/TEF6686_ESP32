param(
    [switch]$SelfTest
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

if ($SelfTest) {
    Write-Host "FlashWizard.ps1 syntax OK"
    exit 0
}

Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Net.Http

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $scriptDir

function Get-UiLanguage {
    $supported = @("pl", "en", "de", "es", "fr", "it")

    $forcedLang = $env:FLASHWIZARD_LANG
    if (-not [string]::IsNullOrWhiteSpace($forcedLang)) {
        $code = $forcedLang.Trim().ToLowerInvariant()
        if ($code.Length -ge 2) {
            $code = $code.Substring(0, 2)
        }
        if ($supported -contains $code) { return $code }
        return "en"
    }

    $culture = [System.Globalization.CultureInfo]::CurrentUICulture
    if ($null -eq $culture) { return "en" }

    $langCode = $culture.TwoLetterISOLanguageName
    if ([string]::IsNullOrWhiteSpace($langCode)) { return "en" }

    $langCode = $langCode.ToLowerInvariant()
    if ($supported -contains $langCode) { return $langCode }
    return "en"
}

$script:Translations = @{
    pl = @{
        app_title = 'TEF6686 Flash Wizard'
        label_com = 'Port COM:'
        btn_refresh = 'Odswiez'
        chk_boot = 'Radio ma przycisk BOOT (zalecane)'
        btn_format = '1) Formatuj'
        btn_flash = '2) Wgraj soft'
        btn_all = 'Format + wgranie'
        btn_update = '3) Aktualizuj (PE5PVB)'
        btn_close = 'Zamknij'
        hint_boot = 'Tryb BOOT: POWER OFF -> przytrzymaj BOOT -> POWER ON -> pusc BOOT po ~2 s.'
        progress_idle = 'Postep: oczekiwanie'
        progress_update_failed = 'Postep: blad aktualizacji'
        progress_done = 'Postep: {0} (100%)'
        progress_error = 'Postep: {0} (blad)'
        progress_init = 'Postep: {0} (inicjalizacja...)'
        progress_connecting = 'Postep: {0} (polaczenie...)'
        progress_downloading = 'Postep: {0} (pobieranie...)'
        progress_percent = 'Postep: {0} ({1}%)'
        progress_extracting = 'Postep: Rozpakowywanie paczki...'
        progress_update_done = 'Postep: Aktualizacja zakonczona (100%)'
        stage_update_download = 'Pobieranie aktualizacji'
        stage_format = 'Formatowanie'
        stage_flash = 'Wgrywanie softu'
        title_error = 'Blad'
        title_no_port = 'Brak portu'
        title_prepare = 'Przygotowanie'
        title_after_format = 'Krok po formacie'
        title_success = 'Sukces'
        title_update = 'Aktualizacja z PE5PVB'
        title_update_done = 'Aktualizacja zakonczona'
        msg_missing_file = 'Brak pliku: {0}`n`nUmiesc FlashWizard.ps1 w folderze z plikami firmware.'
        msg_select_com = 'Wybierz port COM.'
        msg_boot_prompt = 'Wprowadz radio w tryb BOOT i kliknij OK.`n`nPOWER OFF -> BOOT + POWER ON -> pusc BOOT po ~2 s.'
        msg_format_failed = 'Formatowanie nieudane. Sprawdz port COM i tryb BOOT.'
        msg_after_format = 'Teraz uruchom radio normalnie i poczekaj na komunikat formatowania.`nNastepnie wylacz radio i ponownie wejdz w tryb BOOT przed wgrywaniem softu.'
        msg_flash_failed = 'Wgrywanie nieudane. Sprawdz port COM i tryb BOOT.'
        msg_flash_success = 'Gotowe. Firmware zostal wgrany.'
        msg_refresh_failed = 'Nie udalo sie odswiezyc portow COM.`n{0}'
        msg_update_confirm = 'Wykryto release {0} z PE5PVB.`n`nKreator pobierze paczke i zaktualizuje pliki bazowe.`nPlik TEF6686_ESP32.ino.bin zostanie podmieniony tylko jesli wykryte beda markery accessibility (Accessibility + Voice Lite).`n`nKontynuowac aktualizacje?'
        msg_update_done = 'Aktualizacja zakonczona.`n`nTag: {0}`nBackup: {1}`n`nFirmware accessibility {2}'
        msg_update_failed = 'Nie udalo sie wykonac aktualizacji.`n{0}'
        log_check_release = 'Sprawdzam release: {0}/{1}'
        log_download_package = 'Pobieram paczke: {0}'
        log_package_extracted = 'Paczka rozpakowana.'
        log_backup_dir = 'Backup plikow: {0}'
        log_target_skipped = 'Pominieto {0} (brak w paczce).'
        log_target_updated = 'Zaktualizowano {0}.'
        log_fw_replaced_markers = 'Firmware zostal podmieniony (wykryto markery accessibility).'
        log_fw_skipped_protect = 'Firmware z release pominiety, aby nie nadpisac wersji accessibility.'
        log_fw_not_found = 'Nie znaleziono firmware w paczce release.'
        log_running = 'Uruchamiam: esptool.exe {0}'
        log_exit_code = 'Kod wyjscia: {0}'
        log_format_cancelled = 'Anulowano format.'
        log_format_start = 'Start formatowania...'
        log_format_done = 'Formatowanie zakonczone.'
        log_flash_cancelled = 'Anulowano wgrywanie.'
        log_flash_start = 'Start wgrywania firmware...'
        log_spiffs_yes = 'SPIFFS bedzie wgrany.'
        log_spiffs_large = 'SPIFFS pominiety (za duzy plik).'
        log_spiffs_missing = 'SPIFFS pominiety (brak pliku).'
        log_flash_done = 'Wgrywanie zakonczone pomyslnie.'
        log_ports_refreshed = 'Odswiezono liste portow COM.'
        log_error = 'Blad: {0}'
        log_update_start = 'Rozpoczynam sprawdzanie aktualizacji z PE5PVB...'
        log_latest_release = 'Najnowszy release: {0} ({1})'
        log_selected_package = 'Wybrana paczka: {0}'
        log_update_cancelled = 'Anulowano aktualizacje.'
        log_update_completed = 'Zakonczono aktualizacje. Zmienione pliki: {0}'
        log_update_fw_replaced = 'Firmware accessibility zostal zaktualizowany z paczki release.'
        log_update_fw_kept = 'Firmware accessibility pozostawiono bez zmian.'
        log_update_error = 'Blad aktualizacji: {0}'
        log_wizard_ready = 'Kreator gotowy.'
        log_instruction = 'Wybierz COM, potem: Formatuj -> Wgraj soft.'
        log_update_option = 'Opcja Aktualizuj (PE5PVB) aktualizuje pliki bazowe i chroni firmware accessibility.'
        log_ui_language = 'Jezyk interfejsu: {0}'
        text_no_date = 'brak daty'
        status_fw_replaced = 'zostal podmieniony.'
        status_fw_kept = 'pozostal bez zmian.'
        err_no_zip = 'Brak paczki ZIP w release na GitHub.'
        err_no_match_files = 'Nie znaleziono zadnych pasujacych plikow do aktualizacji.'
        err_release_no_zip = 'Release nie zawiera paczki ZIP.'
    }
    en = @{
        app_title = 'TEF6686 Flash Wizard'
        label_com = 'COM Port:'
        btn_refresh = 'Refresh'
        chk_boot = 'Radio has BOOT button (recommended)'
        btn_format = '1) Format'
        btn_flash = '2) Flash firmware'
        btn_all = 'Format + flash'
        btn_update = '3) Update (PE5PVB)'
        btn_close = 'Close'
        hint_boot = 'BOOT mode: POWER OFF -> hold BOOT -> POWER ON -> release BOOT after ~2 s.'
        progress_idle = 'Progress: waiting'
        progress_update_failed = 'Progress: update failed'
        progress_done = 'Progress: {0} (100%)'
        progress_error = 'Progress: {0} (error)'
        progress_init = 'Progress: {0} (initializing...)'
        progress_connecting = 'Progress: {0} (connecting...)'
        progress_downloading = 'Progress: {0} (downloading...)'
        progress_percent = 'Progress: {0} ({1}%)'
        progress_extracting = 'Progress: Extracting package...'
        progress_update_done = 'Progress: Update completed (100%)'
        stage_update_download = 'Downloading update'
        stage_format = 'Formatting'
        stage_flash = 'Flashing firmware'
        title_error = 'Error'
        title_no_port = 'No port'
        title_prepare = 'Preparation'
        title_after_format = 'After format'
        title_success = 'Success'
        title_update = 'Update from PE5PVB'
        title_update_done = 'Update completed'
        msg_missing_file = 'Missing file: {0}`n`nPlace FlashWizard.ps1 in the firmware folder.'
        msg_select_com = 'Select a COM port.'
        msg_boot_prompt = 'Put the radio into BOOT mode and click OK.`n`nPOWER OFF -> BOOT + POWER ON -> release BOOT after ~2 s.'
        msg_format_failed = 'Formatting failed. Check COM port and BOOT mode.'
        msg_after_format = 'Now start the radio normally and wait for the format message.`nThen power it off and enter BOOT mode again before flashing.'
        msg_flash_failed = 'Flashing failed. Check COM port and BOOT mode.'
        msg_flash_success = 'Done. Firmware was flashed.'
        msg_refresh_failed = 'Failed to refresh COM ports.`n{0}'
        msg_update_confirm = 'Release {0} detected on PE5PVB.`n`nWizard will download the package and update base files.`nTEF6686_ESP32.ino.bin will be replaced only if accessibility markers are detected (Accessibility + Voice Lite).`n`nContinue update?'
        msg_update_done = 'Update completed.`n`nTag: {0}`nBackup: {1}`n`nAccessibility firmware {2}'
        msg_update_failed = 'Could not complete update.`n{0}'
        log_check_release = 'Checking release: {0}/{1}'
        log_download_package = 'Downloading package: {0}'
        log_package_extracted = 'Package extracted.'
        log_backup_dir = 'Backup files: {0}'
        log_target_skipped = 'Skipped {0} (not found in package).'
        log_target_updated = 'Updated {0}.'
        log_fw_replaced_markers = 'Firmware replaced (accessibility markers detected).'
        log_fw_skipped_protect = 'Release firmware skipped to avoid overwriting accessibility build.'
        log_fw_not_found = 'Firmware not found in release package.'
        log_running = 'Running: esptool.exe {0}'
        log_exit_code = 'Exit code: {0}'
        log_format_cancelled = 'Formatting cancelled.'
        log_format_start = 'Formatting started...'
        log_format_done = 'Formatting completed.'
        log_flash_cancelled = 'Flashing cancelled.'
        log_flash_start = 'Firmware flashing started...'
        log_spiffs_yes = 'SPIFFS will be flashed.'
        log_spiffs_large = 'SPIFFS skipped (file too large).'
        log_spiffs_missing = 'SPIFFS skipped (file missing).'
        log_flash_done = 'Flashing completed successfully.'
        log_ports_refreshed = 'COM port list refreshed.'
        log_error = 'Error: {0}'
        log_update_start = 'Starting update check from PE5PVB...'
        log_latest_release = 'Latest release: {0} ({1})'
        log_selected_package = 'Selected package: {0}'
        log_update_cancelled = 'Update cancelled.'
        log_update_completed = 'Update completed. Changed files: {0}'
        log_update_fw_replaced = 'Accessibility firmware was updated from release package.'
        log_update_fw_kept = 'Accessibility firmware left unchanged.'
        log_update_error = 'Update error: {0}'
        log_wizard_ready = 'Wizard ready.'
        log_instruction = 'Select COM, then: Format -> Flash firmware.'
        log_update_option = 'Update (PE5PVB) updates base files and protects accessibility firmware.'
        log_ui_language = 'UI language: {0}'
        text_no_date = 'no date'
        status_fw_replaced = 'was replaced.'
        status_fw_kept = 'remained unchanged.'
        err_no_zip = 'No ZIP package found in GitHub release.'
        err_no_match_files = 'No matching files were found for update.'
        err_release_no_zip = 'Release does not include a ZIP package.'
    }
    de = @{
        app_title = 'TEF6686 Flash Wizard'
        label_com = 'COM-Port:'
        btn_refresh = 'Aktualisieren'
        chk_boot = 'Radio hat BOOT-Taste (empfohlen)'
        btn_format = '1) Formatieren'
        btn_flash = '2) Firmware flashen'
        btn_all = 'Formatieren + flashen'
        btn_update = '3) Update (PE5PVB)'
        btn_close = 'Schliessen'
        hint_boot = 'BOOT-Modus: POWER OFF -> BOOT halten -> POWER ON -> BOOT nach ~2 s loslassen.'
        progress_idle = 'Fortschritt: warten'
        progress_update_failed = 'Fortschritt: Update fehlgeschlagen'
        progress_done = 'Fortschritt: {0} (100%)'
        progress_error = 'Fortschritt: {0} (Fehler)'
        progress_init = 'Fortschritt: {0} (Initialisierung...)'
        progress_connecting = 'Fortschritt: {0} (Verbinden...)'
        progress_downloading = 'Fortschritt: {0} (Download...)'
        progress_percent = 'Fortschritt: {0} ({1}%)'
        progress_extracting = 'Fortschritt: Paket wird entpackt...'
        progress_update_done = 'Fortschritt: Update abgeschlossen (100%)'
        stage_update_download = 'Update herunterladen'
        stage_format = 'Formatieren'
        stage_flash = 'Firmware flashen'
        title_error = 'Fehler'
        title_no_port = 'Kein Port'
        title_prepare = 'Vorbereitung'
        title_after_format = 'Nach dem Formatieren'
        title_success = 'Erfolg'
        title_update = 'Update von PE5PVB'
        title_update_done = 'Update abgeschlossen'
        msg_missing_file = 'Datei fehlt: {0}`n`nLege FlashWizard.ps1 in den Firmware-Ordner.'
        msg_select_com = 'Waehle einen COM-Port.'
        msg_boot_prompt = 'Versetze das Radio in den BOOT-Modus und klicke OK.`n`nPOWER OFF -> BOOT + POWER ON -> BOOT nach ~2 s loslassen.'
        msg_format_failed = 'Formatieren fehlgeschlagen. COM-Port und BOOT-Modus pruefen.'
        msg_after_format = 'Starte das Radio jetzt normal und warte auf die Formatmeldung.`nDann ausschalten und vor dem Flashen erneut in den BOOT-Modus wechseln.'
        msg_flash_failed = 'Flashen fehlgeschlagen. COM-Port und BOOT-Modus pruefen.'
        msg_flash_success = 'Fertig. Firmware wurde geflasht.'
        msg_refresh_failed = 'COM-Ports konnten nicht aktualisiert werden.`n{0}'
        msg_update_confirm = 'Release {0} auf PE5PVB gefunden.`n`nDer Wizard laedt das Paket herunter und aktualisiert Basisdateien.`nTEF6686_ESP32.ino.bin wird nur ersetzt, wenn Accessibility-Marker erkannt werden (Accessibility + Voice Lite).`n`nUpdate fortsetzen?'
        msg_update_done = 'Update abgeschlossen.`n`nTag: {0}`nBackup: {1}`n`nAccessibility-Firmware {2}'
        msg_update_failed = 'Update konnte nicht ausgefuehrt werden.`n{0}'
        log_check_release = 'Pruefe Release: {0}/{1}'
        log_download_package = 'Paket wird heruntergeladen: {0}'
        log_package_extracted = 'Paket entpackt.'
        log_backup_dir = 'Backup-Dateien: {0}'
        log_target_skipped = '{0} uebersprungen (nicht im Paket gefunden).'
        log_target_updated = '{0} aktualisiert.'
        log_fw_replaced_markers = 'Firmware ersetzt (Accessibility-Marker erkannt).'
        log_fw_skipped_protect = 'Release-Firmware uebersprungen, um Accessibility-Build nicht zu ueberschreiben.'
        log_fw_not_found = 'Firmware nicht im Release-Paket gefunden.'
        log_running = 'Starte: esptool.exe {0}'
        log_exit_code = 'Exit-Code: {0}'
        log_format_cancelled = 'Formatieren abgebrochen.'
        log_format_start = 'Formatieren gestartet...'
        log_format_done = 'Formatieren abgeschlossen.'
        log_flash_cancelled = 'Flashen abgebrochen.'
        log_flash_start = 'Firmware-Flashen gestartet...'
        log_spiffs_yes = 'SPIFFS wird geflasht.'
        log_spiffs_large = 'SPIFFS uebersprungen (Datei zu gross).'
        log_spiffs_missing = 'SPIFFS uebersprungen (Datei fehlt).'
        log_flash_done = 'Flashen erfolgreich abgeschlossen.'
        log_ports_refreshed = 'COM-Port-Liste aktualisiert.'
        log_error = 'Fehler: {0}'
        log_update_start = 'Starte Update-Pruefung von PE5PVB...'
        log_latest_release = 'Neuestes Release: {0} ({1})'
        log_selected_package = 'Ausgewaehltes Paket: {0}'
        log_update_cancelled = 'Update abgebrochen.'
        log_update_completed = 'Update abgeschlossen. Geaenderte Dateien: {0}'
        log_update_fw_replaced = 'Accessibility-Firmware wurde aus dem Release-Paket aktualisiert.'
        log_update_fw_kept = 'Accessibility-Firmware blieb unveraendert.'
        log_update_error = 'Update-Fehler: {0}'
        log_wizard_ready = 'Wizard bereit.'
        log_instruction = 'COM waehlen, dann: Formatieren -> Firmware flashen.'
        log_update_option = 'Update (PE5PVB) aktualisiert Basisdateien und schuetzt Accessibility-Firmware.'
        log_ui_language = 'UI-Sprache: {0}'
        text_no_date = 'kein Datum'
        status_fw_replaced = 'wurde ersetzt.'
        status_fw_kept = 'blieb unveraendert.'
        err_no_zip = 'Kein ZIP-Paket im GitHub-Release gefunden.'
        err_no_match_files = 'Keine passenden Dateien fuer das Update gefunden.'
        err_release_no_zip = 'Release enthaelt kein ZIP-Paket.'
    }
    es = @{
        app_title = 'TEF6686 Flash Wizard'
        label_com = 'Puerto COM:'
        btn_refresh = 'Actualizar'
        chk_boot = 'La radio tiene boton BOOT (recomendado)'
        btn_format = '1) Formatear'
        btn_flash = '2) Flashear firmware'
        btn_all = 'Formatear + flashear'
        btn_update = '3) Actualizar (PE5PVB)'
        btn_close = 'Cerrar'
        hint_boot = 'Modo BOOT: POWER OFF -> mantener BOOT -> POWER ON -> soltar BOOT tras ~2 s.'
        progress_idle = 'Progreso: en espera'
        progress_update_failed = 'Progreso: actualizacion fallida'
        progress_done = 'Progreso: {0} (100%)'
        progress_error = 'Progreso: {0} (error)'
        progress_init = 'Progreso: {0} (inicializando...)'
        progress_connecting = 'Progreso: {0} (conectando...)'
        progress_downloading = 'Progreso: {0} (descargando...)'
        progress_percent = 'Progreso: {0} ({1}%)'
        progress_extracting = 'Progreso: Extrayendo paquete...'
        progress_update_done = 'Progreso: Actualizacion completada (100%)'
        stage_update_download = 'Descargando actualizacion'
        stage_format = 'Formateando'
        stage_flash = 'Flasheando firmware'
        title_error = 'Error'
        title_no_port = 'Sin puerto'
        title_prepare = 'Preparacion'
        title_after_format = 'Despues del formateo'
        title_success = 'Exito'
        title_update = 'Actualizacion desde PE5PVB'
        title_update_done = 'Actualizacion completada'
        msg_missing_file = 'Falta el archivo: {0}`n`nColoca FlashWizard.ps1 en la carpeta de firmware.'
        msg_select_com = 'Selecciona un puerto COM.'
        msg_boot_prompt = 'Pon la radio en modo BOOT y pulsa OK.`n`nPOWER OFF -> BOOT + POWER ON -> suelta BOOT tras ~2 s.'
        msg_format_failed = 'Fallo al formatear. Revisa el puerto COM y el modo BOOT.'
        msg_after_format = 'Ahora enciende la radio normalmente y espera el mensaje de formateo.`nDespues apagala y vuelve a entrar en modo BOOT antes de flashear.'
        msg_flash_failed = 'Fallo al flashear. Revisa el puerto COM y el modo BOOT.'
        msg_flash_success = 'Listo. El firmware se flasheo.'
        msg_refresh_failed = 'No se pudieron actualizar los puertos COM.`n{0}'
        msg_update_confirm = 'Se detecto el release {0} en PE5PVB.`n`nEl asistente descargara el paquete y actualizara los archivos base.`nTEF6686_ESP32.ino.bin se reemplazara solo si se detectan marcadores de accesibilidad (Accessibility + Voice Lite).`n`nContinuar con la actualizacion?'
        msg_update_done = 'Actualizacion completada.`n`nTag: {0}`nBackup: {1}`n`nFirmware de accesibilidad {2}'
        msg_update_failed = 'No se pudo completar la actualizacion.`n{0}'
        log_check_release = 'Comprobando release: {0}/{1}'
        log_download_package = 'Descargando paquete: {0}'
        log_package_extracted = 'Paquete extraido.'
        log_backup_dir = 'Archivos de backup: {0}'
        log_target_skipped = 'Se omite {0} (no encontrado en el paquete).'
        log_target_updated = '{0} actualizado.'
        log_fw_replaced_markers = 'Firmware reemplazado (marcadores de accesibilidad detectados).'
        log_fw_skipped_protect = 'Se omitio el firmware del release para no sobrescribir la version de accesibilidad.'
        log_fw_not_found = 'No se encontro firmware en el paquete del release.'
        log_running = 'Ejecutando: esptool.exe {0}'
        log_exit_code = 'Codigo de salida: {0}'
        log_format_cancelled = 'Formateo cancelado.'
        log_format_start = 'Iniciando formateo...'
        log_format_done = 'Formateo completado.'
        log_flash_cancelled = 'Flasheo cancelado.'
        log_flash_start = 'Iniciando flasheo de firmware...'
        log_spiffs_yes = 'SPIFFS se flasheara.'
        log_spiffs_large = 'SPIFFS omitido (archivo demasiado grande).'
        log_spiffs_missing = 'SPIFFS omitido (archivo ausente).'
        log_flash_done = 'Flasheo completado correctamente.'
        log_ports_refreshed = 'Lista de puertos COM actualizada.'
        log_error = 'Error: {0}'
        log_update_start = 'Iniciando comprobacion de actualizaciones desde PE5PVB...'
        log_latest_release = 'Release mas reciente: {0} ({1})'
        log_selected_package = 'Paquete seleccionado: {0}'
        log_update_cancelled = 'Actualizacion cancelada.'
        log_update_completed = 'Actualizacion completada. Archivos cambiados: {0}'
        log_update_fw_replaced = 'El firmware de accesibilidad se actualizo desde el paquete release.'
        log_update_fw_kept = 'El firmware de accesibilidad se dejo sin cambios.'
        log_update_error = 'Error de actualizacion: {0}'
        log_wizard_ready = 'Asistente listo.'
        log_instruction = 'Selecciona COM y luego: Formatear -> Flashear firmware.'
        log_update_option = 'Actualizar (PE5PVB) actualiza archivos base y protege el firmware de accesibilidad.'
        log_ui_language = 'Idioma de UI: {0}'
        text_no_date = 'sin fecha'
        status_fw_replaced = 'fue reemplazado.'
        status_fw_kept = 'quedo sin cambios.'
        err_no_zip = 'No se encontro paquete ZIP en el release de GitHub.'
        err_no_match_files = 'No se encontraron archivos coincidentes para actualizar.'
        err_release_no_zip = 'El release no contiene paquete ZIP.'
    }
    fr = @{
        app_title = 'TEF6686 Flash Wizard'
        label_com = 'Port COM:'
        btn_refresh = 'Actualiser'
        chk_boot = 'La radio a un bouton BOOT (recommande)'
        btn_format = '1) Formater'
        btn_flash = '2) Flasher le firmware'
        btn_all = 'Formater + flasher'
        btn_update = '3) Mettre a jour (PE5PVB)'
        btn_close = 'Fermer'
        hint_boot = 'Mode BOOT: POWER OFF -> maintenir BOOT -> POWER ON -> relacher BOOT apres ~2 s.'
        progress_idle = 'Progression: en attente'
        progress_update_failed = 'Progression: echec de mise a jour'
        progress_done = 'Progression: {0} (100%)'
        progress_error = 'Progression: {0} (erreur)'
        progress_init = 'Progression: {0} (initialisation...)'
        progress_connecting = 'Progression: {0} (connexion...)'
        progress_downloading = 'Progression: {0} (telechargement...)'
        progress_percent = 'Progression: {0} ({1}%)'
        progress_extracting = 'Progression: extraction du paquet...'
        progress_update_done = 'Progression: mise a jour terminee (100%)'
        stage_update_download = 'Telechargement de la mise a jour'
        stage_format = 'Formatage'
        stage_flash = 'Flash du firmware'
        title_error = 'Erreur'
        title_no_port = 'Aucun port'
        title_prepare = 'Preparation'
        title_after_format = 'Apres formatage'
        title_success = 'Succes'
        title_update = 'Mise a jour depuis PE5PVB'
        title_update_done = 'Mise a jour terminee'
        msg_missing_file = 'Fichier manquant: {0}`n`nPlace FlashWizard.ps1 dans le dossier firmware.'
        msg_select_com = 'Selectionne un port COM.'
        msg_boot_prompt = 'Mets la radio en mode BOOT puis clique sur OK.`n`nPOWER OFF -> BOOT + POWER ON -> relacher BOOT apres ~2 s.'
        msg_format_failed = 'Le formatage a echoue. Verifie le port COM et le mode BOOT.'
        msg_after_format = 'Demarre la radio normalement et attends le message de formatage.`nEnsuite eteins-la et repasse en mode BOOT avant le flash.'
        msg_flash_failed = 'Le flash a echoue. Verifie le port COM et le mode BOOT.'
        msg_flash_success = 'Termine. Le firmware a ete flashe.'
        msg_refresh_failed = 'Impossible de mettre a jour les ports COM.`n{0}'
        msg_update_confirm = 'Release {0} detecte sur PE5PVB.`n`nL assistant telechargera le paquet et mettra a jour les fichiers de base.`nTEF6686_ESP32.ino.bin sera remplace uniquement si des marqueurs d accessibilite sont detectes (Accessibility + Voice Lite).`n`nContinuer la mise a jour?'
        msg_update_done = 'Mise a jour terminee.`n`nTag: {0}`nBackup: {1}`n`nFirmware accessibilite {2}'
        msg_update_failed = 'Impossible de terminer la mise a jour.`n{0}'
        log_check_release = 'Verification du release: {0}/{1}'
        log_download_package = 'Telechargement du paquet: {0}'
        log_package_extracted = 'Paquet extrait.'
        log_backup_dir = 'Fichiers de sauvegarde: {0}'
        log_target_skipped = '{0} ignore (introuvable dans le paquet).'
        log_target_updated = '{0} mis a jour.'
        log_fw_replaced_markers = 'Firmware remplace (marqueurs d accessibilite detectes).'
        log_fw_skipped_protect = 'Firmware du release ignore pour eviter d ecraser la version accessibilite.'
        log_fw_not_found = 'Firmware introuvable dans le paquet release.'
        log_running = 'Execution: esptool.exe {0}'
        log_exit_code = 'Code de sortie: {0}'
        log_format_cancelled = 'Formatage annule.'
        log_format_start = 'Demarrage du formatage...'
        log_format_done = 'Formatage termine.'
        log_flash_cancelled = 'Flash annule.'
        log_flash_start = 'Demarrage du flash firmware...'
        log_spiffs_yes = 'SPIFFS sera flashe.'
        log_spiffs_large = 'SPIFFS ignore (fichier trop volumineux).'
        log_spiffs_missing = 'SPIFFS ignore (fichier absent).'
        log_flash_done = 'Flash termine avec succes.'
        log_ports_refreshed = 'Liste des ports COM actualisee.'
        log_error = 'Erreur: {0}'
        log_update_start = 'Demarrage de la verification des mises a jour depuis PE5PVB...'
        log_latest_release = 'Dernier release: {0} ({1})'
        log_selected_package = 'Paquet selectionne: {0}'
        log_update_cancelled = 'Mise a jour annulee.'
        log_update_completed = 'Mise a jour terminee. Fichiers modifies: {0}'
        log_update_fw_replaced = 'Le firmware accessibilite a ete mis a jour depuis le paquet release.'
        log_update_fw_kept = 'Le firmware accessibilite est reste inchange.'
        log_update_error = 'Erreur de mise a jour: {0}'
        log_wizard_ready = 'Assistant pret.'
        log_instruction = 'Selectionne COM puis: Formater -> Flasher le firmware.'
        log_update_option = 'Mettre a jour (PE5PVB) met a jour les fichiers de base et protege le firmware accessibilite.'
        log_ui_language = 'Langue UI: {0}'
        text_no_date = 'pas de date'
        status_fw_replaced = 'a ete remplace.'
        status_fw_kept = 'est reste inchange.'
        err_no_zip = 'Aucun paquet ZIP trouve dans le release GitHub.'
        err_no_match_files = 'Aucun fichier correspondant trouve pour la mise a jour.'
        err_release_no_zip = 'Le release ne contient pas de paquet ZIP.'
    }
    it = @{
        app_title = 'TEF6686 Flash Wizard'
        label_com = 'Porta COM:'
        btn_refresh = 'Aggiorna'
        chk_boot = 'La radio ha il pulsante BOOT (consigliato)'
        btn_format = '1) Formatta'
        btn_flash = '2) Flasha firmware'
        btn_all = 'Formatta + flasha'
        btn_update = '3) Aggiorna (PE5PVB)'
        btn_close = 'Chiudi'
        hint_boot = 'Modalita BOOT: POWER OFF -> tieni premuto BOOT -> POWER ON -> rilascia BOOT dopo ~2 s.'
        progress_idle = 'Progresso: in attesa'
        progress_update_failed = 'Progresso: aggiornamento fallito'
        progress_done = 'Progresso: {0} (100%)'
        progress_error = 'Progresso: {0} (errore)'
        progress_init = 'Progresso: {0} (inizializzazione...)'
        progress_connecting = 'Progresso: {0} (connessione...)'
        progress_downloading = 'Progresso: {0} (download...)'
        progress_percent = 'Progresso: {0} ({1}%)'
        progress_extracting = 'Progresso: Estrazione pacchetto...'
        progress_update_done = 'Progresso: Aggiornamento completato (100%)'
        stage_update_download = 'Download aggiornamento'
        stage_format = 'Formattazione'
        stage_flash = 'Flash firmware'
        title_error = 'Errore'
        title_no_port = 'Nessuna porta'
        title_prepare = 'Preparazione'
        title_after_format = 'Dopo la formattazione'
        title_success = 'Successo'
        title_update = 'Aggiornamento da PE5PVB'
        title_update_done = 'Aggiornamento completato'
        msg_missing_file = 'File mancante: {0}`n`nMetti FlashWizard.ps1 nella cartella firmware.'
        msg_select_com = 'Seleziona una porta COM.'
        msg_boot_prompt = 'Metti la radio in modalita BOOT e premi OK.`n`nPOWER OFF -> BOOT + POWER ON -> rilascia BOOT dopo ~2 s.'
        msg_format_failed = 'Formattazione non riuscita. Controlla porta COM e modalita BOOT.'
        msg_after_format = 'Ora avvia la radio normalmente e attendi il messaggio di formattazione.`nPoi spegnila ed entra di nuovo in modalita BOOT prima del flash.'
        msg_flash_failed = 'Flash non riuscito. Controlla porta COM e modalita BOOT.'
        msg_flash_success = 'Fatto. Firmware flashato.'
        msg_refresh_failed = 'Impossibile aggiornare le porte COM.`n{0}'
        msg_update_confirm = 'Release {0} rilevata su PE5PVB.`n`nIl wizard scarichera il pacchetto e aggiornera i file base.`nTEF6686_ESP32.ino.bin verra sostituito solo se vengono rilevati i marker di accessibilita (Accessibility + Voice Lite).`n`nContinuare con l aggiornamento?'
        msg_update_done = 'Aggiornamento completato.`n`nTag: {0}`nBackup: {1}`n`nFirmware accessibilita {2}'
        msg_update_failed = 'Impossibile completare l aggiornamento.`n{0}'
        log_check_release = 'Controllo release: {0}/{1}'
        log_download_package = 'Download pacchetto: {0}'
        log_package_extracted = 'Pacchetto estratto.'
        log_backup_dir = 'File di backup: {0}'
        log_target_skipped = '{0} saltato (non trovato nel pacchetto).'
        log_target_updated = '{0} aggiornato.'
        log_fw_replaced_markers = 'Firmware sostituito (marker accessibilita rilevati).'
        log_fw_skipped_protect = 'Firmware release saltato per evitare sovrascrittura della build accessibilita.'
        log_fw_not_found = 'Firmware non trovato nel pacchetto release.'
        log_running = 'Esecuzione: esptool.exe {0}'
        log_exit_code = 'Codice uscita: {0}'
        log_format_cancelled = 'Formattazione annullata.'
        log_format_start = 'Avvio formattazione...'
        log_format_done = 'Formattazione completata.'
        log_flash_cancelled = 'Flash annullato.'
        log_flash_start = 'Avvio flash firmware...'
        log_spiffs_yes = 'SPIFFS verra flashato.'
        log_spiffs_large = 'SPIFFS saltato (file troppo grande).'
        log_spiffs_missing = 'SPIFFS saltato (file mancante).'
        log_flash_done = 'Flash completato con successo.'
        log_ports_refreshed = 'Elenco porte COM aggiornato.'
        log_error = 'Errore: {0}'
        log_update_start = 'Avvio controllo aggiornamenti da PE5PVB...'
        log_latest_release = 'Ultimo release: {0} ({1})'
        log_selected_package = 'Pacchetto selezionato: {0}'
        log_update_cancelled = 'Aggiornamento annullato.'
        log_update_completed = 'Aggiornamento completato. File modificati: {0}'
        log_update_fw_replaced = 'Il firmware accessibilita e stato aggiornato dal pacchetto release.'
        log_update_fw_kept = 'Il firmware accessibilita e rimasto invariato.'
        log_update_error = 'Errore aggiornamento: {0}'
        log_wizard_ready = 'Wizard pronto.'
        log_instruction = 'Seleziona COM, poi: Formatta -> Flasha firmware.'
        log_update_option = 'Aggiorna (PE5PVB) aggiorna i file base e protegge il firmware accessibilita.'
        log_ui_language = 'Lingua UI: {0}'
        text_no_date = 'nessuna data'
        status_fw_replaced = 'e stato sostituito.'
        status_fw_kept = 'e rimasto invariato.'
        err_no_zip = 'Nessun pacchetto ZIP trovato nel release GitHub.'
        err_no_match_files = 'Nessun file corrispondente trovato per l aggiornamento.'
        err_release_no_zip = 'Il release non contiene un pacchetto ZIP.'
    }
}

function T {
    param(
        [Parameter(Mandatory = $true)][string]$Key,
        [object[]]$Args = @()
    )

    $lang = $script:UiLanguage
    if (-not $script:Translations.ContainsKey($lang)) { $lang = "en" }
    $dict = $script:Translations[$lang]

    if (-not $dict.ContainsKey($Key)) {
        $dict = $script:Translations["en"]
        if (-not $dict.ContainsKey($Key)) { return $Key }
    }

    $template = [string]$dict[$Key]
    if ($null -eq $Args -or $Args.Count -eq 0) { return $template }
    return [string]::Format($template, $Args)
}

$script:UiLanguage = Get-UiLanguage
$updateRepoOwner = "PE5PVB"
$updateRepoName = "TEF6686_ESP32"

$requiredFiles = @(
    "esptool.exe",
    "bootloader.bin",
    "partitions.bin",
    "boot_app0.bin",
    "format_Spiffs.ino.bin",
    "TEF6686_ESP32.ino.bin"
)

foreach ($file in $requiredFiles) {
    if (-not (Test-Path (Join-Path $scriptDir $file))) {
        [System.Windows.Forms.MessageBox]::Show(
            (T "msg_missing_file" @($file)),
            (T "title_error"),
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Error
        ) | Out-Null
        exit 1
    }
}

function Append-Log {
    param(
        [Parameter(Mandatory = $true)][System.Windows.Forms.TextBox]$LogBox,
        [Parameter(Mandatory = $true)][string]$Text
    )

    $time = Get-Date -Format "HH:mm:ss"
    $LogBox.AppendText("[$time] $Text`r`n")
    $LogBox.SelectionStart = $LogBox.TextLength
    $LogBox.ScrollToCaret()
    [System.Windows.Forms.Application]::DoEvents()
}

function Get-SortedComPorts {
    $ports = [System.IO.Ports.SerialPort]::GetPortNames()
    return $ports | Sort-Object {
        $n = ($_ -replace "[^\d]", "")
        if ([string]::IsNullOrWhiteSpace($n)) { 0 } else { [int]$n }
    }
}

function Get-LatestGitHubRelease {
    param(
        [Parameter(Mandatory = $true)][string]$Owner,
        [Parameter(Mandatory = $true)][string]$Repo,
        [Parameter(Mandatory = $true)][System.Windows.Forms.TextBox]$LogBox
    )

    $uri = "https://api.github.com/repos/$Owner/$Repo/releases/latest"
    $headers = @{
        "User-Agent" = "TEF6686-FlashWizard"
        "Accept" = "application/vnd.github+json"
    }

    Append-Log -LogBox $LogBox -Text (T "log_check_release" @($Owner, $Repo))
    return Invoke-RestMethod -Method Get -Uri $uri -Headers $headers -TimeoutSec 25
}

function Select-PreferredReleaseZipAsset {
    param([Parameter(Mandatory = $true)]$Release)

    $assets = @()
    if ($Release.PSObject.Properties.Name -contains "assets" -and $Release.assets) {
        $assets = @($Release.assets)
    }
    if ($assets.Count -eq 0) { return $null }

    $primary = $assets | Where-Object {
        $_.name -match '\.zip$' -and $_.name -notmatch '(?i)_ARS|_DP666'
    } | Select-Object -First 1
    if ($primary) { return $primary }

    return $assets | Where-Object { $_.name -match '\.zip$' } | Select-Object -First 1
}

function Find-ExtractedFile {
    param(
        [Parameter(Mandatory = $true)][string]$Root,
        [string[]]$ExactNames = @(),
        [string[]]$Patterns = @()
    )

    if (-not (Test-Path $Root)) { return $null }
    $files = @(Get-ChildItem -Path $Root -Recurse -File -ErrorAction SilentlyContinue)
    if ($files.Count -eq 0) { return $null }

    foreach ($name in $ExactNames) {
        $hit = $files | Where-Object { $_.Name -ieq $name } | Select-Object -First 1
        if ($hit) { return $hit }
    }

    foreach ($pattern in $Patterns) {
        $hit = $files | Where-Object { $_.Name -like $pattern } | Select-Object -First 1
        if ($hit) { return $hit }
    }

    return $null
}

function Test-AccessibilityFirmwareCandidate {
    param([Parameter(Mandatory = $true)][string]$Path)

    try {
        $bytes = [System.IO.File]::ReadAllBytes($Path)
        if ($bytes.Length -eq 0) { return $false }
        $text = [System.Text.Encoding]::ASCII.GetString($bytes)
        $hasAccessibility = ($text -match '(?i)Accessibility|Dostepnosc')
        $hasVoiceLite = ($text -match '(?i)Voice[ _-]?Lite')
        return ($hasAccessibility -and $hasVoiceLite)
    }
    catch {
        return $false
    }
}

function Download-FileWithProgress {
    param(
        [Parameter(Mandatory = $true)][string]$Url,
        [Parameter(Mandatory = $true)][string]$DestinationPath,
        [Parameter(Mandatory = $true)][System.Windows.Forms.ProgressBar]$ProgressBar,
        [Parameter(Mandatory = $true)][System.Windows.Forms.Label]$ProgressLabel,
        [Parameter(Mandatory = $true)][string]$StageName
    )

    $client = New-Object System.Net.Http.HttpClient
    $response = $null
    $stream = $null
    $fileStream = $null

    try {
        $client.Timeout = [TimeSpan]::FromMinutes(10)
        [void]$client.DefaultRequestHeaders.UserAgent.ParseAdd("TEF6686-FlashWizard")
        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_connecting" @($StageName)) -Indeterminate $true

        $response = $client.GetAsync($Url, [System.Net.Http.HttpCompletionOption]::ResponseHeadersRead).Result
        $response.EnsureSuccessStatusCode()

        $totalBytes = $response.Content.Headers.ContentLength
        $stream = $response.Content.ReadAsStreamAsync().Result
        $fileStream = [System.IO.File]::Open($DestinationPath, [System.IO.FileMode]::Create, [System.IO.FileAccess]::Write, [System.IO.FileShare]::None)

        $buffer = New-Object byte[] 65536
        $downloaded = 0L
        $lastPercent = -1

        if ($totalBytes -gt 0) {
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_percent" @($StageName, 0)) -Percent 0
        }
        else {
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_downloading" @($StageName)) -Indeterminate $true
        }

        while ($true) {
            $read = $stream.Read($buffer, 0, $buffer.Length)
            if ($read -le 0) { break }

            $fileStream.Write($buffer, 0, $read)
            $downloaded += $read

            if ($totalBytes -gt 0) {
                $percent = [int][Math]::Floor(($downloaded * 100.0) / $totalBytes)
                if ($percent -gt 100) { $percent = 100 }
                if ($percent -gt $lastPercent) {
                    $lastPercent = $percent
                    Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_percent" @($StageName, $percent)) -Percent $percent
                }
            }

            [System.Windows.Forms.Application]::DoEvents()
        }
    }
    finally {
        if ($fileStream) { $fileStream.Dispose() }
        if ($stream) { $stream.Dispose() }
        if ($response) { $response.Dispose() }
        if ($client) { $client.Dispose() }
    }
}

function Invoke-SafeReleaseUpdate {
    param(
        [Parameter(Mandatory = $true)]$Release,
        [Parameter(Mandatory = $true)][System.Windows.Forms.TextBox]$LogBox,
        [Parameter(Mandatory = $true)][System.Windows.Forms.ProgressBar]$ProgressBar,
        [Parameter(Mandatory = $true)][System.Windows.Forms.Label]$ProgressLabel
    )

    $asset = Select-PreferredReleaseZipAsset -Release $Release
    if (-not $asset) {
        throw (T "err_no_zip")
    }

    $tempRoot = Join-Path ([System.IO.Path]::GetTempPath()) ("tef_update_" + [Guid]::NewGuid().ToString("N"))
    $zipPath = Join-Path $tempRoot ([string]$asset.name)
    $extractDir = Join-Path $tempRoot "extracted"
    $backupDir = Join-Path $scriptDir ("backup_update_" + (Get-Date -Format "yyyyMMdd_HHmmss"))

    $updatedFiles = New-Object System.Collections.Generic.List[string]
    $firmwareReplaced = $false

    New-Item -Path $tempRoot -ItemType Directory -Force | Out-Null

    try {
        Append-Log -LogBox $LogBox -Text (T "log_download_package" @([string]$asset.name))
        Download-FileWithProgress `
            -Url ([string]$asset.browser_download_url) `
            -DestinationPath $zipPath `
            -ProgressBar $ProgressBar `
            -ProgressLabel $ProgressLabel `
            -StageName (T "stage_update_download")

        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_extracting") -Indeterminate $true
        Expand-Archive -Path $zipPath -DestinationPath $extractDir -Force
        Append-Log -LogBox $LogBox -Text (T "log_package_extracted")

        New-Item -Path $backupDir -ItemType Directory -Force | Out-Null
        Append-Log -LogBox $LogBox -Text (T "log_backup_dir" @($backupDir))

        $baseTargets = @(
            @{ Target = "bootloader.bin"; Exact = @("bootloader.bin"); Patterns = @("*bootloader*.bin") },
            @{ Target = "partitions.bin"; Exact = @("partitions.bin"); Patterns = @("*partition*.bin") },
            @{ Target = "boot_app0.bin"; Exact = @("boot_app0.bin"); Patterns = @("*boot_app0*.bin") },
            @{ Target = "format_Spiffs.ino.bin"; Exact = @("format_Spiffs.ino.bin"); Patterns = @("*format*spiffs*.bin", "*format*.bin") }
        )

        foreach ($target in $baseTargets) {
            $source = Find-ExtractedFile -Root $extractDir -ExactNames $target.Exact -Patterns $target.Patterns
            if (-not $source) {
                Append-Log -LogBox $LogBox -Text (T "log_target_skipped" @($target.Target))
                continue
            }

            $destination = Join-Path $scriptDir $target.Target
            if (Test-Path $destination) {
                Copy-Item -Path $destination -Destination (Join-Path $backupDir $target.Target) -Force
            }

            Copy-Item -Path $source.FullName -Destination $destination -Force
            $updatedFiles.Add($target.Target)
            Append-Log -LogBox $LogBox -Text (T "log_target_updated" @($target.Target))
        }

        $firmwareSource = Find-ExtractedFile `
            -Root $extractDir `
            -ExactNames @("TEF6686_ESP32.ino.bin") `
            -Patterns @("TEF6686_ESP32*.ino.bin", "TEF6686*.bin")

        if ($firmwareSource) {
            if (Test-AccessibilityFirmwareCandidate -Path $firmwareSource.FullName) {
                $firmwareDest = Join-Path $scriptDir "TEF6686_ESP32.ino.bin"
                if (Test-Path $firmwareDest) {
                    Copy-Item -Path $firmwareDest -Destination (Join-Path $backupDir "TEF6686_ESP32.ino.bin") -Force
                }

                Copy-Item -Path $firmwareSource.FullName -Destination $firmwareDest -Force
                $firmwareReplaced = $true
                $updatedFiles.Add("TEF6686_ESP32.ino.bin")
                Append-Log -LogBox $LogBox -Text (T "log_fw_replaced_markers")
            }
            else {
                Append-Log -LogBox $LogBox -Text (T "log_fw_skipped_protect")
            }
        }
        else {
            Append-Log -LogBox $LogBox -Text (T "log_fw_not_found")
        }

        if ($updatedFiles.Count -eq 0) {
            throw (T "err_no_match_files")
        }

        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_update_done") -Percent 100
        return [PSCustomObject]@{
            TagName = [string]$Release.tag_name
            UpdatedFiles = ($updatedFiles -join ", ")
            FirmwareReplaced = $firmwareReplaced
            BackupDir = $backupDir
        }
    }
    finally {
        if (Test-Path $tempRoot) {
            Remove-Item -Path $tempRoot -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
}

function Invoke-Esptool {
    param(
        [Parameter(Mandatory = $true)][string[]]$Arguments,
        [Parameter(Mandatory = $true)][System.Windows.Forms.TextBox]$LogBox,
        [Parameter(Mandatory = $true)][System.Windows.Forms.ProgressBar]$ProgressBar,
        [Parameter(Mandatory = $true)][System.Windows.Forms.Label]$ProgressLabel,
        [Parameter(Mandatory = $true)][string]$StageName
    )

    $exe = Join-Path $scriptDir "esptool.exe"
    $stdOutFile = [System.IO.Path]::GetTempFileName()
    $stdErrFile = [System.IO.Path]::GetTempFileName()
    $stdOutPos = 0
    $stdErrPos = 0
    $stdOutRemainder = ""
    $stdErrRemainder = ""
    $highestPercent = 0

    try {
        Append-Log -LogBox $LogBox -Text (T "log_running" @(($Arguments -join " ")))
        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_init" @($StageName)) -Indeterminate $true

        $process = Start-Process -FilePath $exe `
            -ArgumentList $Arguments `
            -WorkingDirectory $scriptDir `
            -NoNewWindow `
            -PassThru `
            -RedirectStandardOutput $stdOutFile `
            -RedirectStandardError $stdErrFile

        while (-not $process.HasExited) {
            Consume-EsptoolOutput `
                -Path $stdOutFile `
                -LastLength ([ref]$stdOutPos) `
                -Remainder ([ref]$stdOutRemainder) `
                -LogBox $LogBox `
                -ProgressBar $ProgressBar `
                -ProgressLabel $ProgressLabel `
                -StageName $StageName `
                -HighestPercent ([ref]$highestPercent)

            Consume-EsptoolOutput `
                -Path $stdErrFile `
                -LastLength ([ref]$stdErrPos) `
                -Remainder ([ref]$stdErrRemainder) `
                -LogBox $LogBox `
                -ProgressBar $ProgressBar `
                -ProgressLabel $ProgressLabel `
                -StageName $StageName `
                -HighestPercent ([ref]$highestPercent)

            [System.Windows.Forms.Application]::DoEvents()
            Start-Sleep -Milliseconds 70
        }

        $process.WaitForExit()

        Consume-EsptoolOutput `
            -Path $stdOutFile `
            -LastLength ([ref]$stdOutPos) `
            -Remainder ([ref]$stdOutRemainder) `
            -LogBox $LogBox `
            -ProgressBar $ProgressBar `
            -ProgressLabel $ProgressLabel `
            -StageName $StageName `
            -HighestPercent ([ref]$highestPercent) `
            -FlushRemainder

        Consume-EsptoolOutput `
            -Path $stdErrFile `
            -LastLength ([ref]$stdErrPos) `
            -Remainder ([ref]$stdErrRemainder) `
            -LogBox $LogBox `
            -ProgressBar $ProgressBar `
            -ProgressLabel $ProgressLabel `
            -StageName $StageName `
            -HighestPercent ([ref]$highestPercent) `
            -FlushRemainder

        Append-Log -LogBox $LogBox -Text (T "log_exit_code" @($process.ExitCode))

        if ($process.ExitCode -eq 0) {
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_done" @($StageName)) -Percent 100
        }
        else {
            $finalPercent = $highestPercent
            if ($finalPercent -lt 0) { $finalPercent = 0 }
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_error" @($StageName)) -Percent $finalPercent
        }

        return [int]$process.ExitCode
    }
    finally {
        if (Test-Path $stdOutFile) { Remove-Item $stdOutFile -Force -ErrorAction SilentlyContinue }
        if (Test-Path $stdErrFile) { Remove-Item $stdErrFile -Force -ErrorAction SilentlyContinue }
    }
}

function Set-ProgressUi {
    param(
        [Parameter(Mandatory = $true)][System.Windows.Forms.ProgressBar]$ProgressBar,
        [Parameter(Mandatory = $true)][System.Windows.Forms.Label]$ProgressLabel,
        [Parameter(Mandatory = $true)][string]$Text,
        [int]$Percent = 0,
        [bool]$Indeterminate = $false
    )

    if ($Indeterminate) {
        $ProgressBar.Style = [System.Windows.Forms.ProgressBarStyle]::Marquee
        $ProgressBar.MarqueeAnimationSpeed = 25
    }
    else {
        $ProgressBar.Style = [System.Windows.Forms.ProgressBarStyle]::Continuous
        $ProgressBar.MarqueeAnimationSpeed = 0
        $value = [Math]::Min([Math]::Max($Percent, 0), 100)
        $ProgressBar.Value = $value
    }

    $ProgressLabel.Text = $Text
    [System.Windows.Forms.Application]::DoEvents()
}

function Update-ProgressFromLine {
    param(
        [Parameter(Mandatory = $true)][string]$Line,
        [Parameter(Mandatory = $true)][System.Windows.Forms.ProgressBar]$ProgressBar,
        [Parameter(Mandatory = $true)][System.Windows.Forms.Label]$ProgressLabel,
        [Parameter(Mandatory = $true)][string]$StageName,
        [Parameter(Mandatory = $true)][ref]$HighestPercent
    )

    if ($Line -notmatch '\((\d{1,3})\s*%\)') { return }
    $percent = [Math]::Min([Math]::Max([int]$Matches[1], 0), 100)
    if ($percent -le $HighestPercent.Value) { return }

    $HighestPercent.Value = $percent
    Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text (T "progress_percent" @($StageName, $percent)) -Percent $percent
}

function Consume-EsptoolOutput {
    param(
        [Parameter(Mandatory = $true)][string]$Path,
        [Parameter(Mandatory = $true)][ref]$LastLength,
        [Parameter(Mandatory = $true)][ref]$Remainder,
        [Parameter(Mandatory = $true)][System.Windows.Forms.TextBox]$LogBox,
        [Parameter(Mandatory = $true)][System.Windows.Forms.ProgressBar]$ProgressBar,
        [Parameter(Mandatory = $true)][System.Windows.Forms.Label]$ProgressLabel,
        [Parameter(Mandatory = $true)][string]$StageName,
        [Parameter(Mandatory = $true)][ref]$HighestPercent,
        [switch]$FlushRemainder
    )

    if (-not (Test-Path $Path)) { return }

    $content = Get-Content -Raw -Path $Path -ErrorAction SilentlyContinue
    if ($null -eq $content) { return }
    if ($content.Length -le $LastLength.Value -and -not $FlushRemainder) { return }

    $newText = ""
    if ($content.Length -gt $LastLength.Value) {
        $newText = $content.Substring($LastLength.Value)
        $LastLength.Value = $content.Length
    }

    $combined = $Remainder.Value + $newText
    if ([string]::IsNullOrEmpty($combined)) { return }

    $parts = $combined -split "`r`n|`n|`r"
    $endsWithNewline = ($combined -match "(`r`n|`n|`r)$")
    $lines = @()

    if ($endsWithNewline -or $FlushRemainder) {
        $lines = $parts
        $Remainder.Value = ""
    }
    else {
        if ($parts.Count -gt 0) { $Remainder.Value = $parts[-1] } else { $Remainder.Value = "" }
        if ($parts.Count -gt 1) { $lines = $parts[0..($parts.Count - 2)] }
    }

    foreach ($line in $lines) {
        if ([string]::IsNullOrWhiteSpace($line)) { continue }
        Append-Log -LogBox $LogBox -Text $line
        Update-ProgressFromLine `
            -Line $line `
            -ProgressBar $ProgressBar `
            -ProgressLabel $ProgressLabel `
            -StageName $StageName `
            -HighestPercent $HighestPercent
    }
}

function Confirm-BootMode {
    param(
        [Parameter(Mandatory = $true)][System.Windows.Forms.CheckBox]$BootCheckBox,
        [Parameter(Mandatory = $true)][string]$Title,
        [Parameter(Mandatory = $true)][string]$Message
    )

    if (-not $BootCheckBox.Checked) {
        return $true
    }

    $result = [System.Windows.Forms.MessageBox]::Show(
        $Message,
        $Title,
        [System.Windows.Forms.MessageBoxButtons]::OKCancel,
        [System.Windows.Forms.MessageBoxIcon]::Information
    )

    return ($result -eq [System.Windows.Forms.DialogResult]::OK)
}

function Build-BaseArgs {
    param([Parameter(Mandatory = $true)][string]$ComPort)

    return @(
        "--chip", "esp32",
        "--port", $ComPort,
        "--baud", "921600",
        "--before", "default_reset",
        "--after", "hard_reset",
        "write_flash", "-z",
        "--flash_mode", "dio",
        "--flash_freq", "80m",
        "--flash_size", "4MB"
    )
}

$form = New-Object System.Windows.Forms.Form
$form.Text = T "app_title"
$form.StartPosition = "CenterScreen"
$form.Size = New-Object System.Drawing.Size(760, 560)
$form.MinimumSize = New-Object System.Drawing.Size(760, 560)
$form.MaximizeBox = $false

$lblCom = New-Object System.Windows.Forms.Label
$lblCom.Text = T "label_com"
$lblCom.Location = New-Object System.Drawing.Point(18, 18)
$lblCom.Size = New-Object System.Drawing.Size(90, 24)
$form.Controls.Add($lblCom)

$cmbCom = New-Object System.Windows.Forms.ComboBox
$cmbCom.DropDownStyle = "DropDownList"
$cmbCom.Location = New-Object System.Drawing.Point(92, 14)
$cmbCom.Size = New-Object System.Drawing.Size(120, 24)
$form.Controls.Add($cmbCom)

$btnRefresh = New-Object System.Windows.Forms.Button
$btnRefresh.Text = T "btn_refresh"
$btnRefresh.Location = New-Object System.Drawing.Point(220, 13)
$btnRefresh.Size = New-Object System.Drawing.Size(85, 27)
$form.Controls.Add($btnRefresh)

$chkBoot = New-Object System.Windows.Forms.CheckBox
$chkBoot.Text = T "chk_boot"
$chkBoot.Checked = $true
$chkBoot.Location = New-Object System.Drawing.Point(320, 16)
$chkBoot.Size = New-Object System.Drawing.Size(270, 24)
$form.Controls.Add($chkBoot)

$btnFormat = New-Object System.Windows.Forms.Button
$btnFormat.Text = T "btn_format"
$btnFormat.Location = New-Object System.Drawing.Point(18, 54)
$btnFormat.Size = New-Object System.Drawing.Size(120, 34)
$form.Controls.Add($btnFormat)

$btnFlash = New-Object System.Windows.Forms.Button
$btnFlash.Text = T "btn_flash"
$btnFlash.Location = New-Object System.Drawing.Point(146, 54)
$btnFlash.Size = New-Object System.Drawing.Size(120, 34)
$form.Controls.Add($btnFlash)

$btnAll = New-Object System.Windows.Forms.Button
$btnAll.Text = T "btn_all"
$btnAll.Location = New-Object System.Drawing.Point(274, 54)
$btnAll.Size = New-Object System.Drawing.Size(140, 34)
$form.Controls.Add($btnAll)

$btnUpdate = New-Object System.Windows.Forms.Button
$btnUpdate.Text = T "btn_update"
$btnUpdate.Location = New-Object System.Drawing.Point(422, 54)
$btnUpdate.Size = New-Object System.Drawing.Size(190, 34)
$form.Controls.Add($btnUpdate)

$btnClose = New-Object System.Windows.Forms.Button
$btnClose.Text = T "btn_close"
$btnClose.Location = New-Object System.Drawing.Point(622, 54)
$btnClose.Size = New-Object System.Drawing.Size(110, 34)
$form.Controls.Add($btnClose)

$lblHint = New-Object System.Windows.Forms.Label
$lblHint.Text = T "hint_boot"
$lblHint.Location = New-Object System.Drawing.Point(18, 98)
$lblHint.Size = New-Object System.Drawing.Size(714, 20)
$form.Controls.Add($lblHint)

$lblProgress = New-Object System.Windows.Forms.Label
$lblProgress.Text = T "progress_idle"
$lblProgress.Location = New-Object System.Drawing.Point(18, 121)
$lblProgress.Size = New-Object System.Drawing.Size(240, 20)
$form.Controls.Add($lblProgress)

$progressFlash = New-Object System.Windows.Forms.ProgressBar
$progressFlash.Location = New-Object System.Drawing.Point(260, 118)
$progressFlash.Size = New-Object System.Drawing.Size(472, 23)
$progressFlash.Minimum = 0
$progressFlash.Maximum = 100
$progressFlash.Style = [System.Windows.Forms.ProgressBarStyle]::Continuous
$progressFlash.Value = 0
$form.Controls.Add($progressFlash)

$txtLog = New-Object System.Windows.Forms.TextBox
$txtLog.Location = New-Object System.Drawing.Point(18, 150)
$txtLog.Size = New-Object System.Drawing.Size(714, 365)
$txtLog.Multiline = $true
$txtLog.ScrollBars = "Vertical"
$txtLog.ReadOnly = $true
$txtLog.Font = New-Object System.Drawing.Font("Consolas", 9)
$form.Controls.Add($txtLog)

function Refresh-ComUI {
    $cmbCom.Items.Clear()
    $ports = Get-SortedComPorts
    foreach ($p in $ports) { [void]$cmbCom.Items.Add($p) }
    if ($cmbCom.Items.Count -gt 0) { $cmbCom.SelectedIndex = 0 }
}

function Set-BusyState {
    param([bool]$Busy)
    $btnFormat.Enabled = -not $Busy
    $btnFlash.Enabled = -not $Busy
    $btnAll.Enabled = -not $Busy
    $btnUpdate.Enabled = -not $Busy
    $btnRefresh.Enabled = -not $Busy
    $cmbCom.Enabled = -not $Busy
}

function Get-SelectedComOrWarn {
    if ($cmbCom.SelectedItem -eq $null) {
        [System.Windows.Forms.MessageBox]::Show(
            (T "msg_select_com"),
            (T "title_no_port"),
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Warning
        ) | Out-Null
        return $null
    }
    return [string]$cmbCom.SelectedItem
}

function Run-FormatStep {
    $comPort = Get-SelectedComOrWarn
    if (-not $comPort) { return $false }

    if (-not (Confirm-BootMode -BootCheckBox $chkBoot -Title (T "title_prepare") -Message (T "msg_boot_prompt"))) {
        Append-Log -LogBox $txtLog -Text (T "log_format_cancelled")
        return $false
    }

    Set-BusyState -Busy $true
    try {
        Append-Log -LogBox $txtLog -Text (T "log_format_start")
        $args = Build-BaseArgs -ComPort $comPort
        $args += @(
            "0x1000", "bootloader.bin",
            "0x8000", "partitions.bin",
            "0xe000", "boot_app0.bin",
            "0x10000", "format_Spiffs.ino.bin"
        )

        $code = Invoke-Esptool `
            -Arguments $args `
            -LogBox $txtLog `
            -ProgressBar $progressFlash `
            -ProgressLabel $lblProgress `
            -StageName (T "stage_format")
        if ($code -ne 0) {
            [System.Windows.Forms.MessageBox]::Show(
                (T "msg_format_failed"),
                (T "title_error"),
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Error
            ) | Out-Null
            return $false
        }

        Append-Log -LogBox $txtLog -Text (T "log_format_done")

        if ($chkBoot.Checked) {
            [System.Windows.Forms.MessageBox]::Show(
                (T "msg_after_format"),
                (T "title_after_format"),
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Information
            ) | Out-Null
        }

        return $true
    }
    finally {
        Set-BusyState -Busy $false
    }
}

function Run-FlashStep {
    $comPort = Get-SelectedComOrWarn
    if (-not $comPort) { return $false }

    if (-not (Confirm-BootMode -BootCheckBox $chkBoot -Title (T "title_prepare") -Message (T "msg_boot_prompt"))) {
        Append-Log -LogBox $txtLog -Text (T "log_flash_cancelled")
        return $false
    }

    Set-BusyState -Busy $true
    try {
        Append-Log -LogBox $txtLog -Text (T "log_flash_start")

        $args = Build-BaseArgs -ComPort $comPort
        $args += @(
            "0x1000", "bootloader.bin",
            "0x8000", "partitions.bin",
            "0xe000", "boot_app0.bin",
            "0x10000", "TEF6686_ESP32.ino.bin"
        )

        $spiffsFile = Join-Path $scriptDir "TEF6686_ESP32.spiffs.bin"
        $spiffsMax = 196608
        if (Test-Path $spiffsFile) {
            $spiffsSize = (Get-Item $spiffsFile).Length
            if ($spiffsSize -le $spiffsMax) {
                $args += @("0x003D0000", "TEF6686_ESP32.spiffs.bin")
                Append-Log -LogBox $txtLog -Text (T "log_spiffs_yes")
            }
            else {
                Append-Log -LogBox $txtLog -Text (T "log_spiffs_large")
            }
        }
        else {
            Append-Log -LogBox $txtLog -Text (T "log_spiffs_missing")
        }

        $code = Invoke-Esptool `
            -Arguments $args `
            -LogBox $txtLog `
            -ProgressBar $progressFlash `
            -ProgressLabel $lblProgress `
            -StageName (T "stage_flash")
        if ($code -ne 0) {
            [System.Windows.Forms.MessageBox]::Show(
                (T "msg_flash_failed"),
                (T "title_error"),
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Error
            ) | Out-Null
            return $false
        }

        Append-Log -LogBox $txtLog -Text (T "log_flash_done")
        [System.Windows.Forms.MessageBox]::Show(
            (T "msg_flash_success"),
            (T "title_success"),
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        ) | Out-Null
        return $true
    }
    finally {
        Set-BusyState -Busy $false
    }
}

$btnRefresh.Add_Click({
    try {
        Refresh-ComUI
        Append-Log -LogBox $txtLog -Text (T "log_ports_refreshed")
    }
    catch {
        [System.Windows.Forms.MessageBox]::Show(
            (T "msg_refresh_failed" @($_.Exception.Message)),
            (T "title_error"),
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Error
        ) | Out-Null
    }
})

$btnFormat.Add_Click({
    try { [void](Run-FormatStep) }
    catch {
        Append-Log -LogBox $txtLog -Text (T "log_error" @($_.Exception.Message))
    }
})

$btnFlash.Add_Click({
    try { [void](Run-FlashStep) }
    catch {
        Append-Log -LogBox $txtLog -Text (T "log_error" @($_.Exception.Message))
    }
})

$btnAll.Add_Click({
    try {
        if (Run-FormatStep) {
            [void](Run-FlashStep)
        }
    }
    catch {
        Append-Log -LogBox $txtLog -Text (T "log_error" @($_.Exception.Message))
    }
})

$btnUpdate.Add_Click({
    Set-BusyState -Busy $true
    try {
        Append-Log -LogBox $txtLog -Text (T "log_update_start")

        $release = Get-LatestGitHubRelease -Owner $updateRepoOwner -Repo $updateRepoName -LogBox $txtLog
        $asset = Select-PreferredReleaseZipAsset -Release $release
        if (-not $asset) {
            throw (T "err_release_no_zip")
        }

        $publishedText = T "text_no_date"
        if ($release.published_at) {
            try {
                $publishedText = ([DateTime]::Parse($release.published_at)).ToLocalTime().ToString("yyyy-MM-dd HH:mm")
            }
            catch { }
        }

        Append-Log -LogBox $txtLog -Text (T "log_latest_release" @([string]$release.tag_name, $publishedText))
        Append-Log -LogBox $txtLog -Text (T "log_selected_package" @([string]$asset.name))

        $msg = T "msg_update_confirm" @([string]$release.tag_name)

        $confirm = [System.Windows.Forms.MessageBox]::Show(
            $msg,
            (T "title_update"),
            [System.Windows.Forms.MessageBoxButtons]::YesNo,
            [System.Windows.Forms.MessageBoxIcon]::Question
        )

        if ($confirm -ne [System.Windows.Forms.DialogResult]::Yes) {
            Append-Log -LogBox $txtLog -Text (T "log_update_cancelled")
            Set-ProgressUi -ProgressBar $progressFlash -ProgressLabel $lblProgress -Text (T "progress_idle") -Percent 0
            return
        }

        $result = Invoke-SafeReleaseUpdate `
            -Release $release `
            -LogBox $txtLog `
            -ProgressBar $progressFlash `
            -ProgressLabel $lblProgress

        Append-Log -LogBox $txtLog -Text (T "log_update_completed" @($result.UpdatedFiles))
        if ($result.FirmwareReplaced) {
            Append-Log -LogBox $txtLog -Text (T "log_update_fw_replaced")
        }
        else {
            Append-Log -LogBox $txtLog -Text (T "log_update_fw_kept")
        }

        [System.Windows.Forms.MessageBox]::Show(
            (T "msg_update_done" @($result.TagName, $result.BackupDir, $(if ($result.FirmwareReplaced) { T "status_fw_replaced" } else { T "status_fw_kept" }))),
            (T "title_update_done"),
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        ) | Out-Null
    }
    catch {
        Set-ProgressUi -ProgressBar $progressFlash -ProgressLabel $lblProgress -Text (T "progress_update_failed") -Percent 0
        Append-Log -LogBox $txtLog -Text (T "log_update_error" @($_.Exception.Message))
        [System.Windows.Forms.MessageBox]::Show(
            (T "msg_update_failed" @($_.Exception.Message)),
            (T "title_error"),
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Error
        ) | Out-Null
    }
    finally {
        Set-BusyState -Busy $false
    }
})

$btnClose.Add_Click({ $form.Close() })

Refresh-ComUI
Append-Log -LogBox $txtLog -Text (T "log_ui_language" @($script:UiLanguage))
Append-Log -LogBox $txtLog -Text (T "log_wizard_ready")
Append-Log -LogBox $txtLog -Text (T "log_instruction")
Append-Log -LogBox $txtLog -Text (T "log_update_option")

[void]$form.ShowDialog()
