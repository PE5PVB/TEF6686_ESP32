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

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $scriptDir

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
            "Brak pliku: $file`n`nUmiesc FlashWizard.ps1 w folderze z plikami firmware.",
            "Blad",
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

function Invoke-Esptool {
    param(
        [Parameter(Mandatory = $true)][string[]]$Arguments,
        [Parameter(Mandatory = $true)][System.Windows.Forms.TextBox]$LogBox
    )

    $exe = Join-Path $scriptDir "esptool.exe"
    $stdOutFile = [System.IO.Path]::GetTempFileName()
    $stdErrFile = [System.IO.Path]::GetTempFileName()

    try {
        Append-Log -LogBox $LogBox -Text ("Uruchamiam: esptool.exe " + ($Arguments -join " "))

        $process = Start-Process -FilePath $exe `
            -ArgumentList $Arguments `
            -WorkingDirectory $scriptDir `
            -NoNewWindow `
            -Wait `
            -PassThru `
            -RedirectStandardOutput $stdOutFile `
            -RedirectStandardError $stdErrFile

        $stdout = ""
        $stderr = ""
        if (Test-Path $stdOutFile) { $stdout = Get-Content -Raw $stdOutFile }
        if (Test-Path $stdErrFile) { $stderr = Get-Content -Raw $stdErrFile }

        if ($stdout) { Append-Log -LogBox $LogBox -Text $stdout.TrimEnd() }
        if ($stderr) { Append-Log -LogBox $LogBox -Text $stderr.TrimEnd() }
        Append-Log -LogBox $LogBox -Text ("Kod wyjscia: " + $process.ExitCode)

        return [int]$process.ExitCode
    }
    finally {
        if (Test-Path $stdOutFile) { Remove-Item $stdOutFile -Force -ErrorAction SilentlyContinue }
        if (Test-Path $stdErrFile) { Remove-Item $stdErrFile -Force -ErrorAction SilentlyContinue }
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
$form.Text = "TEF6686 Flash Wizard"
$form.StartPosition = "CenterScreen"
$form.Size = New-Object System.Drawing.Size(760, 560)
$form.MinimumSize = New-Object System.Drawing.Size(760, 560)
$form.MaximizeBox = $false

$lblCom = New-Object System.Windows.Forms.Label
$lblCom.Text = "Port COM:"
$lblCom.Location = New-Object System.Drawing.Point(18, 18)
$lblCom.Size = New-Object System.Drawing.Size(90, 24)
$form.Controls.Add($lblCom)

$cmbCom = New-Object System.Windows.Forms.ComboBox
$cmbCom.DropDownStyle = "DropDownList"
$cmbCom.Location = New-Object System.Drawing.Point(92, 14)
$cmbCom.Size = New-Object System.Drawing.Size(120, 24)
$form.Controls.Add($cmbCom)

$btnRefresh = New-Object System.Windows.Forms.Button
$btnRefresh.Text = "Odswiez"
$btnRefresh.Location = New-Object System.Drawing.Point(220, 13)
$btnRefresh.Size = New-Object System.Drawing.Size(85, 27)
$form.Controls.Add($btnRefresh)

$chkBoot = New-Object System.Windows.Forms.CheckBox
$chkBoot.Text = "Radio ma przycisk BOOT (zalecane)"
$chkBoot.Checked = $true
$chkBoot.Location = New-Object System.Drawing.Point(320, 16)
$chkBoot.Size = New-Object System.Drawing.Size(270, 24)
$form.Controls.Add($chkBoot)

$btnFormat = New-Object System.Windows.Forms.Button
$btnFormat.Text = "1) Formatuj"
$btnFormat.Location = New-Object System.Drawing.Point(18, 54)
$btnFormat.Size = New-Object System.Drawing.Size(120, 34)
$form.Controls.Add($btnFormat)

$btnFlash = New-Object System.Windows.Forms.Button
$btnFlash.Text = "2) Wgraj soft"
$btnFlash.Location = New-Object System.Drawing.Point(146, 54)
$btnFlash.Size = New-Object System.Drawing.Size(120, 34)
$form.Controls.Add($btnFlash)

$btnAll = New-Object System.Windows.Forms.Button
$btnAll.Text = "Format + wgranie"
$btnAll.Location = New-Object System.Drawing.Point(274, 54)
$btnAll.Size = New-Object System.Drawing.Size(140, 34)
$form.Controls.Add($btnAll)

$btnClose = New-Object System.Windows.Forms.Button
$btnClose.Text = "Zamknij"
$btnClose.Location = New-Object System.Drawing.Point(622, 54)
$btnClose.Size = New-Object System.Drawing.Size(110, 34)
$form.Controls.Add($btnClose)

$lblHint = New-Object System.Windows.Forms.Label
$lblHint.Text = "Tryb BOOT: POWER OFF -> przytrzymaj BOOT -> POWER ON -> pusc BOOT po ~2 s."
$lblHint.Location = New-Object System.Drawing.Point(18, 98)
$lblHint.Size = New-Object System.Drawing.Size(714, 20)
$form.Controls.Add($lblHint)

$txtLog = New-Object System.Windows.Forms.TextBox
$txtLog.Location = New-Object System.Drawing.Point(18, 125)
$txtLog.Size = New-Object System.Drawing.Size(714, 390)
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
    $btnRefresh.Enabled = -not $Busy
    $cmbCom.Enabled = -not $Busy
}

function Get-SelectedComOrWarn {
    if ($cmbCom.SelectedItem -eq $null) {
        [System.Windows.Forms.MessageBox]::Show(
            "Wybierz port COM.",
            "Brak portu",
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

    if (-not (Confirm-BootMode -BootCheckBox $chkBoot -Title "Przygotowanie" -Message "Wprowadz radio w tryb BOOT i kliknij OK.`n`nPOWER OFF -> BOOT + POWER ON -> pusc BOOT po ~2 s.")) {
        Append-Log -LogBox $txtLog -Text "Anulowano format."
        return $false
    }

    Set-BusyState -Busy $true
    try {
        Append-Log -LogBox $txtLog -Text "Start formatowania..."
        $args = Build-BaseArgs -ComPort $comPort
        $args += @(
            "0x1000", "bootloader.bin",
            "0x8000", "partitions.bin",
            "0xe000", "boot_app0.bin",
            "0x10000", "format_Spiffs.ino.bin"
        )

        $code = Invoke-Esptool -Arguments $args -LogBox $txtLog
        if ($code -ne 0) {
            [System.Windows.Forms.MessageBox]::Show(
                "Formatowanie nieudane. Sprawdz port COM i tryb BOOT.",
                "Blad",
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Error
            ) | Out-Null
            return $false
        }

        Append-Log -LogBox $txtLog -Text "Formatowanie zakonczone."

        if ($chkBoot.Checked) {
            [System.Windows.Forms.MessageBox]::Show(
                "Teraz uruchom radio normalnie i poczekaj na komunikat formatowania.`nNastepnie wylacz radio i ponownie wejdz w tryb BOOT przed wgrywaniem softu.",
                "Krok po formacie",
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

    if (-not (Confirm-BootMode -BootCheckBox $chkBoot -Title "Przygotowanie" -Message "Wprowadz radio w tryb BOOT i kliknij OK.`n`nPOWER OFF -> BOOT + POWER ON -> pusc BOOT po ~2 s.")) {
        Append-Log -LogBox $txtLog -Text "Anulowano wgrywanie."
        return $false
    }

    Set-BusyState -Busy $true
    try {
        Append-Log -LogBox $txtLog -Text "Start wgrywania firmware..."

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
                Append-Log -LogBox $txtLog -Text "SPIFFS bedzie wgrany."
            }
            else {
                Append-Log -LogBox $txtLog -Text "SPIFFS pominiety (za duzy plik)."
            }
        }
        else {
            Append-Log -LogBox $txtLog -Text "SPIFFS pominiety (brak pliku)."
        }

        $code = Invoke-Esptool -Arguments $args -LogBox $txtLog
        if ($code -ne 0) {
            [System.Windows.Forms.MessageBox]::Show(
                "Wgrywanie nieudane. Sprawdz port COM i tryb BOOT.",
                "Blad",
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Error
            ) | Out-Null
            return $false
        }

        Append-Log -LogBox $txtLog -Text "Wgrywanie zakonczone pomyslnie."
        [System.Windows.Forms.MessageBox]::Show(
            "Gotowe. Firmware zostal wgrany.",
            "Sukces",
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
        Append-Log -LogBox $txtLog -Text "Odswiezono liste portow COM."
    }
    catch {
        [System.Windows.Forms.MessageBox]::Show(
            "Nie udalo sie odswiezyc portow COM.`n$($_.Exception.Message)",
            "Blad",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Error
        ) | Out-Null
    }
})

$btnFormat.Add_Click({
    try { [void](Run-FormatStep) }
    catch {
        Append-Log -LogBox $txtLog -Text ("Blad: " + $_.Exception.Message)
    }
})

$btnFlash.Add_Click({
    try { [void](Run-FlashStep) }
    catch {
        Append-Log -LogBox $txtLog -Text ("Blad: " + $_.Exception.Message)
    }
})

$btnAll.Add_Click({
    try {
        if (Run-FormatStep) {
            [void](Run-FlashStep)
        }
    }
    catch {
        Append-Log -LogBox $txtLog -Text ("Blad: " + $_.Exception.Message)
    }
})

$btnClose.Add_Click({ $form.Close() })

Refresh-ComUI
Append-Log -LogBox $txtLog -Text "Kreator gotowy."
Append-Log -LogBox $txtLog -Text "Wybierz COM, potem: Formatuj -> Wgraj soft."

[void]$form.ShowDialog()
