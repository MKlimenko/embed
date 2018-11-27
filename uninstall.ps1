Try{                                        
	Remove-Item "$env:programfiles\Module\embed\embed.exe" -Force -Recurse -ErrorAction SilentlyContinue
	If((Get-ChildItem "$env:programfiles\Module\embed" | Measure-Object).count -eq 0){
		Remove-Item "$env:programfiles\Module\embed"  -ErrorAction SilentlyContinue
	}
	$env:EMBED = ""
	Remove-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" -Name EMBED -ErrorAction SilentlyContinue
}
Catch{
    return;
}
echo "embed.exe has been uninstalled"
