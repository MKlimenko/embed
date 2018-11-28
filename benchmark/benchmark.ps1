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
    $pure = Measure-Command { &$msbuild $script_location\..\..\make\vs141\test\test.vcxproj /p:PreBuildEventUseInBuild=false /t:Rebuild /p:Configuration=Release /p:Platform="x64" /m }
    If($LastExitCode -gt 0){
        throw
    }
    $str = "No data: " + $pure.TotalSeconds
    echo $str

    $test_file_src = $script_location + "\\..\\test\\test_";
    $size = 1; # 1 kB
    For ($number_of_files = 1; $number_of_files -le 1024; $number_of_files = $number_of_files * 2) {
        $data = new-object byte[] $size;

        For ($i = 1; $i -le $number_of_files; $i += 1){
            $cur_file = $test_file_src + "$i" + ".bin";
            [io.file]::WriteAllBytes($cur_file, $data);
        }

        $current_time = Measure-Command { &$msbuild $script_location\..\..\make\vs141\test\test.vcxproj /t:Rebuild /p:Configuration=Release /p:Platform="x64" /m }
        If($LastExitCode -gt 0){
            throw
        }
        
        $str = "$number_of_files" + " files: " + $current_time.TotalSeconds
        echo $str
    }
}
Catch {
    echo "Error while running the benchmark"
    throw
}