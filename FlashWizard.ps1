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

    Append-Log -LogBox $LogBox -Text ("Sprawdzam release: $Owner/$Repo")
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
        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (polaczenie...)") -Indeterminate $true

        $response = $client.GetAsync($Url, [System.Net.Http.HttpCompletionOption]::ResponseHeadersRead).Result
        $response.EnsureSuccessStatusCode()

        $totalBytes = $response.Content.Headers.ContentLength
        $stream = $response.Content.ReadAsStreamAsync().Result
        $fileStream = [System.IO.File]::Open($DestinationPath, [System.IO.FileMode]::Create, [System.IO.FileAccess]::Write, [System.IO.FileShare]::None)

        $buffer = New-Object byte[] 65536
        $downloaded = 0L
        $lastPercent = -1

        if ($totalBytes -gt 0) {
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (0%)") -Percent 0
        }
        else {
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (pobieranie...)") -Indeterminate $true
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
                    Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (" + $percent + "%)") -Percent $percent
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
        throw "Brak paczki ZIP w release na GitHub."
    }

    $tempRoot = Join-Path ([System.IO.Path]::GetTempPath()) ("tef_update_" + [Guid]::NewGuid().ToString("N"))
    $zipPath = Join-Path $tempRoot ([string]$asset.name)
    $extractDir = Join-Path $tempRoot "extracted"
    $backupDir = Join-Path $scriptDir ("backup_update_" + (Get-Date -Format "yyyyMMdd_HHmmss"))

    $updatedFiles = New-Object System.Collections.Generic.List[string]
    $firmwareReplaced = $false

    New-Item -Path $tempRoot -ItemType Directory -Force | Out-Null

    try {
        Append-Log -LogBox $LogBox -Text ("Pobieram paczke: " + $asset.name)
        Download-FileWithProgress `
            -Url ([string]$asset.browser_download_url) `
            -DestinationPath $zipPath `
            -ProgressBar $ProgressBar `
            -ProgressLabel $ProgressLabel `
            -StageName "Pobieranie aktualizacji"

        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text "Postep: Rozpakowywanie paczki..." -Indeterminate $true
        Expand-Archive -Path $zipPath -DestinationPath $extractDir -Force
        Append-Log -LogBox $LogBox -Text "Paczka rozpakowana."

        New-Item -Path $backupDir -ItemType Directory -Force | Out-Null
        Append-Log -LogBox $LogBox -Text ("Backup plikow: " + $backupDir)

        $baseTargets = @(
            @{ Target = "bootloader.bin"; Exact = @("bootloader.bin"); Patterns = @("*bootloader*.bin") },
            @{ Target = "partitions.bin"; Exact = @("partitions.bin"); Patterns = @("*partition*.bin") },
            @{ Target = "boot_app0.bin"; Exact = @("boot_app0.bin"); Patterns = @("*boot_app0*.bin") },
            @{ Target = "format_Spiffs.ino.bin"; Exact = @("format_Spiffs.ino.bin"); Patterns = @("*format*spiffs*.bin", "*format*.bin") }
        )

        foreach ($target in $baseTargets) {
            $source = Find-ExtractedFile -Root $extractDir -ExactNames $target.Exact -Patterns $target.Patterns
            if (-not $source) {
                Append-Log -LogBox $LogBox -Text ("Pominieto " + $target.Target + " (brak w paczce).")
                continue
            }

            $destination = Join-Path $scriptDir $target.Target
            if (Test-Path $destination) {
                Copy-Item -Path $destination -Destination (Join-Path $backupDir $target.Target) -Force
            }

            Copy-Item -Path $source.FullName -Destination $destination -Force
            $updatedFiles.Add($target.Target)
            Append-Log -LogBox $LogBox -Text ("Zaktualizowano " + $target.Target + ".")
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
                Append-Log -LogBox $LogBox -Text "Firmware zostal podmieniony (wykryto markery accessibility)."
            }
            else {
                Append-Log -LogBox $LogBox -Text "Firmware z release pominiety, aby nie nadpisac wersji accessibility."
            }
        }
        else {
            Append-Log -LogBox $LogBox -Text "Nie znaleziono firmware w paczce release."
        }

        if ($updatedFiles.Count -eq 0) {
            throw "Nie znaleziono zadnych pasujacych plikow do aktualizacji."
        }

        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text "Postep: Aktualizacja zakonczona (100%)" -Percent 100
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
        Append-Log -LogBox $LogBox -Text ("Uruchamiam: esptool.exe " + ($Arguments -join " "))
        Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (inicjalizacja...)") -Indeterminate $true

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

        Append-Log -LogBox $LogBox -Text ("Kod wyjscia: " + $process.ExitCode)

        if ($process.ExitCode -eq 0) {
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (100%)") -Percent 100
        }
        else {
            $finalPercent = $highestPercent
            if ($finalPercent -lt 0) { $finalPercent = 0 }
            Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (blad)") -Percent $finalPercent
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
    Set-ProgressUi -ProgressBar $ProgressBar -ProgressLabel $ProgressLabel -Text ("Postep: " + $StageName + " (" + $percent + "%)") -Percent $percent
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

$btnUpdate = New-Object System.Windows.Forms.Button
$btnUpdate.Text = "3) Aktualizuj (PE5PVB)"
$btnUpdate.Location = New-Object System.Drawing.Point(422, 54)
$btnUpdate.Size = New-Object System.Drawing.Size(190, 34)
$form.Controls.Add($btnUpdate)

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

$lblProgress = New-Object System.Windows.Forms.Label
$lblProgress.Text = "Postep: oczekiwanie"
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

        $code = Invoke-Esptool `
            -Arguments $args `
            -LogBox $txtLog `
            -ProgressBar $progressFlash `
            -ProgressLabel $lblProgress `
            -StageName "Formatowanie"
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

        $code = Invoke-Esptool `
            -Arguments $args `
            -LogBox $txtLog `
            -ProgressBar $progressFlash `
            -ProgressLabel $lblProgress `
            -StageName "Wgrywanie softu"
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

$btnUpdate.Add_Click({
    Set-BusyState -Busy $true
    try {
        Append-Log -LogBox $txtLog -Text "Rozpoczynam sprawdzanie aktualizacji z PE5PVB..."

        $release = Get-LatestGitHubRelease -Owner $updateRepoOwner -Repo $updateRepoName -LogBox $txtLog
        $asset = Select-PreferredReleaseZipAsset -Release $release
        if (-not $asset) {
            throw "Release nie zawiera paczki ZIP."
        }

        $publishedText = "brak daty"
        if ($release.published_at) {
            try {
                $publishedText = ([DateTime]::Parse($release.published_at)).ToLocalTime().ToString("yyyy-MM-dd HH:mm")
            }
            catch { }
        }

        Append-Log -LogBox $txtLog -Text ("Najnowszy release: " + $release.tag_name + " (" + $publishedText + ")")
        Append-Log -LogBox $txtLog -Text ("Wybrana paczka: " + $asset.name)

        $msg = "Wykryto release " + $release.tag_name + " z PE5PVB.`n`n" +
            "Kreator pobierze paczke i zaktualizuje pliki bazowe.`n" +
            "Plik TEF6686_ESP32.ino.bin zostanie podmieniony tylko jesli wykryte beda markery accessibility (Accessibility + Voice Lite).`n`n" +
            "Kontynuowac aktualizacje?"

        $confirm = [System.Windows.Forms.MessageBox]::Show(
            $msg,
            "Aktualizacja z PE5PVB",
            [System.Windows.Forms.MessageBoxButtons]::YesNo,
            [System.Windows.Forms.MessageBoxIcon]::Question
        )

        if ($confirm -ne [System.Windows.Forms.DialogResult]::Yes) {
            Append-Log -LogBox $txtLog -Text "Anulowano aktualizacje."
            Set-ProgressUi -ProgressBar $progressFlash -ProgressLabel $lblProgress -Text "Postep: oczekiwanie" -Percent 0
            return
        }

        $result = Invoke-SafeReleaseUpdate `
            -Release $release `
            -LogBox $txtLog `
            -ProgressBar $progressFlash `
            -ProgressLabel $lblProgress

        Append-Log -LogBox $txtLog -Text ("Zakonczono aktualizacje. Zmienione pliki: " + $result.UpdatedFiles)
        if ($result.FirmwareReplaced) {
            Append-Log -LogBox $txtLog -Text "Firmware accessibility zostal zaktualizowany z paczki release."
        }
        else {
            Append-Log -LogBox $txtLog -Text "Firmware accessibility pozostawiono bez zmian."
        }

        [System.Windows.Forms.MessageBox]::Show(
            "Aktualizacja zakonczona.`n`nTag: " + $result.TagName + "`nBackup: " + $result.BackupDir + "`n`nFirmware accessibility " + ($(if ($result.FirmwareReplaced) { "zostal podmieniony." } else { "pozostal bez zmian." })),
            "Aktualizacja zakonczona",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        ) | Out-Null
    }
    catch {
        Set-ProgressUi -ProgressBar $progressFlash -ProgressLabel $lblProgress -Text "Postep: blad aktualizacji" -Percent 0
        Append-Log -LogBox $txtLog -Text ("Blad aktualizacji: " + $_.Exception.Message)
        [System.Windows.Forms.MessageBox]::Show(
            "Nie udalo sie wykonac aktualizacji.`n$($_.Exception.Message)",
            "Blad",
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
Append-Log -LogBox $txtLog -Text "Kreator gotowy."
Append-Log -LogBox $txtLog -Text "Wybierz COM, potem: Formatuj -> Wgraj soft."
Append-Log -LogBox $txtLog -Text "Opcja Aktualizuj (PE5PVB) aktualizuje pliki bazowe i chroni firmware accessibility."

[void]$form.ShowDialog()
