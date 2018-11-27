Try {
    $programFiles = ${env:PROGRAMFILES(X86)}
    $results = New-Object System.Collections.ArrayList
    $vswhere = "$programFiles\Microsoft Visual Studio\Installer\vswhere.exe"
    $vs_path = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
    $msbuild = join-path $vs_path 'MSBuild\15.0\Bin\MSBuild.exe'

    if(-Not (test-path $msbuild)) {
        throw "Unable to find MSBuild.exe"
    }

    [Console]::OutputEncoding = [System.Text.Encoding]::GetEncoding("utf-8")
    $script_location = $MyInvocation.MyCommand.Definition
    &$msbuild $script_location\..\make\vs141\embed\embed.vcxproj /t:Rebuild /p:Configuration=Release /p:Platform="x64" /m
    If($LastExitCode -gt 0){
        throw
    }

    New-Item "$env:programfiles\Module\embed" -type directory -ErrorAction SilentlyContinue
    setx EMBED -m "$env:programfiles\Module\embed"
    copy $script_location\..\make\vs141\embed\x64\Release\embed.exe "$env:programfiles\Module\embed\"
}
Catch {
    echo "Error installing embed.exe"
    throw
}
echo "embed.exe has been installed"