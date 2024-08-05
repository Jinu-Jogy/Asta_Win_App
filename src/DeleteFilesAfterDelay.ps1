param (
    [string]$folderPath
)

function Delete-FilesInFolder {
    param (
        [string]$path
    )
    Start-Sleep -Seconds 1

    if (Test-Path -Path $path -PathType Container) {
        Get-ChildItem -Path $path -File | ForEach-Object {
            try {
                Remove-Item -Path $_.FullName -Force -ErrorAction Stop
                Write-Host "Deleted file:" $_.Name
            } catch {
                Write-Host "Failed to delete file:" $_.Name "Error:" $_.Exception.Message
            }
        }
    } else {
        Write-Host "The directory does not exist:" $path
    }
}

Delete-FilesInFolder -path $folderPath
