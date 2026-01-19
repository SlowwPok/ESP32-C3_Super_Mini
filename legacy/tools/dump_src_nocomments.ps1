<#
.SYNOPSIS
  Dump all C/C++ source files from the project src folder into a single text file.

.DESCRIPTION
  This script:
  - Collects all .h and .cpp files from the project's src directory
  - Excludes files under src/res/fonts (except ui_fonts.cpp / ui_fonts.h)
  - Removes C/C++ comments (// and /* */)
  - Writes all source code into one text file
  - Each file is preceded by its full path
  - Output is written to legacy/tools/src_dumps

  The script intentionally avoids changing the working directory
  to prevent PowerShell path resolution issues.

  FAST COMAND TO RUN SCIPT MANUALLY: 
  cd "D:\DIY\ESP32-C3 Super Mini [VS CODE]\ESP32-C3 Super Mini Main"
  .\legacy\tools\dump_src_nocomments.ps1
    OR
  & "D:\DIY\ESP32-C3 Super Mini [VS CODE]\ESP32-C3 Super Mini Main\legacy\tools\dump_src_nocomments.ps1"
#>

# --- configuration ---
$allowFonts = @('ui_fonts.cpp', 'ui_fonts.h')

# --- resolve absolute paths safely ---
$toolsDir  = $PSScriptRoot
$rootDir   = [System.IO.Path]::GetFullPath(
                (Join-Path $toolsDir '..\..')
            )
$srcDir    = Join-Path $rootDir 'src'
$outputDir = Join-Path $toolsDir 'src_dumps'

# --- sanity checks ---
if (-not (Test-Path -LiteralPath $srcDir)) {
    Write-Error "SRC directory not found: $srcDir"
    exit 1
}

if (-not (Test-Path -LiteralPath $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}

$timestamp  = Get-Date -Format 'yyyy-MM-dd_HH-mm-ss'
$outputFile = Join-Path $outputDir "src_dump_nocomments_$timestamp.txt"

# create / clear output file
'' | Out-File -LiteralPath $outputFile -Encoding UTF8

Write-Host "SRC directory:" $srcDir
Write-Host "Output file :" $outputFile

# --- collect files (this matches your WORKING manual command) ---
$files = Get-ChildItem -LiteralPath $srcDir -Recurse -File |
    Where-Object {
        ($_.Extension -in '.h', '.cpp') -and
        (
            $_.FullName -notmatch '\\src\\res\\fonts\\' -or
            $_.Name -in $allowFonts
        )
    } |
    Sort-Object FullName

Write-Host "Files found:" $files.Count

# --- dump ---
foreach ($file in $files) {

    Add-Content -LiteralPath $outputFile "===== $($file.FullName) ====="

    $code = Get-Content -LiteralPath $file.FullName -Raw

    # remove /* ... */ comments
    $code = [regex]::Replace($code, '/\*.*?\*/', '', 'Singleline')

    # remove // comments
    $code = [regex]::Replace($code, '//.*$', '', 'Multiline')

    Add-Content -LiteralPath $outputFile $code.Trim()
    Add-Content -LiteralPath $outputFile ''
}

Write-Host "Dump completed successfully."
