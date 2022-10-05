Imports System.IO
Imports System.Net
Imports Microsoft.Win32
Public Class PointBlank
    Dim dlls As New Dictionary(Of String, String)
    Dim processz As String = "PointBlank"
    Dim zxs As Object

    Private Declare Function OpenProcess Lib "kernel32" (ByVal dwDesiredAccess As Integer, ByVal bInheritHandle As Integer, ByVal dwProcessId As Integer) As Integer
    Private Declare Function VirtualAllocEx Lib "kernel32" (ByVal hProcess As Integer, ByVal lpAddress As Integer, ByVal dwSize As Integer, ByVal flAllocationType As Integer, ByVal flProtect As Integer) As Integer
    Private Declare Function WriteProcessMemory Lib "kernel32" (ByVal hProcess As Integer, ByVal lpBaseAddress As Integer, ByVal lpBuffer() As Byte, ByVal nSize As Integer, ByVal lpNumberOfBytesWritten As UInteger) As Boolean
    Private Declare Function GetProcAddress Lib "kernel32" (ByVal hModule As Integer, ByVal lpProcName As String) As Integer
    Private Declare Function GetModuleHandle Lib "kernel32" Alias "GetModuleHandleA" (ByVal lpModuleName As String) As Integer
    Private Declare Function CreateRemoteThread Lib "kernel32" (ByVal hProcess As Integer, ByVal lpThreadAttributes As Integer, ByVal dwStackSize As Integer, ByVal lpStartAddress As Integer, ByVal lpParameter As Integer, ByVal dwCreationFlags As Integer, ByVal lpThreadId As Integer) As Integer
    Private Declare Function WaitForSingleObject Lib "kernel32" (ByVal hHandle As Integer, ByVal dwMilliseconds As Integer) As Integer
    Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Integer) As Integer
    Private _r As Random = New Random
    Private rname As String
    Private Function Inject(ByVal pID As Integer, ByVal dllLocation As String) As Boolean
        Dim hProcess As Integer = OpenProcess(&H1F0FFF, 1, pID)
        If hProcess = 0 Then Return False
        Dim dllBytes As Byte() = System.Text.Encoding.ASCII.GetBytes(dllLocation)
        Dim allocAddress As Integer = VirtualAllocEx(hProcess, 0, dllBytes.Length, &H1000, &H4)
        If allocAddress = Nothing Then Return False
        Dim kernelMod As Integer = GetModuleHandle("kernel32.dll")
        Dim loadLibAddr = GetProcAddress(kernelMod, "LoadLibraryA")
        If kernelMod = 0 OrElse loadLibAddr = 0 Then Return False
        WriteProcessMemory(hProcess, allocAddress, dllBytes, dllBytes.Length, 0)
        Dim libThread As Integer = CreateRemoteThread(hProcess, 0, 0, loadLibAddr, allocAddress, 0, 0)

        If libThread = 0 Then
            Return False
        Else
            WaitForSingleObject(libThread, 1)
            CloseHandle(libThread)
        End If

        CloseHandle(hProcess)

        Return True
    End Function


    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs)
        'Try
        '    rname = _r.Next(99999)

        '    Text = _r.Next(500000000 - 100000) & ("-") & _r.Next(100000000) & ("-") & _r.Next(900000000) & ("-") & _r.Next(200000000) & ("-") & _r.Next(600000000) & ("-") & _r.Next(700000000)
        'Catch ex As Exception
        'End Try
        'If My.Computer.FileSystem.FileExists("C:\Windows\F3BR1.dll") Then
        '    My.Computer.FileSystem.RenameFile("C:\Windows\F3BR1.dll", rname & ".dll")
        '    'My.Computer.FileSystem.DeleteFile("C:\Windows\Resources\F3BR1.dll" & rname & ".dll")
        'Else

        'End If

        Timer1.Start()
    End Sub

    Private Sub Timer1_Tick_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Try
            Dim rc = Process.GetProcessesByName("pbid")
            If rc.Length = 1 Then
                Dim pid As Integer = Process.GetProcessesByName("PointBlank.exe")(0).Id

                'Inject(pid, "C:\Windows\System32\F3BR1.dll(")")
                'Me.Close()
                'Me.Visible = False
            End If
        Catch ex As Exception
        End Try
    End Sub
    Public Sub DownloadFileCompleted(ByVal sender As Object, ByVal e As EventArgs)
        MsgBox("Cheat ON - Please Start Point Blank", MsgBoxStyle.Information)
        Hide()

    End Sub
    Private Sub DownloadProgressChangedEventArgs(ByVal sender As Object, ByVal e As DownloadProgressChangedEventArgs)
        ' Throw New NotImplementedException
    End Sub
    Private Sub Button1_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
           Try
            rname = _r.Next(117)

            Text = _r.Next(500000000 - 100000) & ("-") & _r.Next(100000000) & ("-") & _r.Next(900000000) & ("-") & _r.Next(200000000) & ("-") & _r.Next(600000000) & ("-") & _r.Next(700000000)
        Catch ex As Exception
        End Try

        If System.IO.File.Exists("C:\\FebriZip.dll") Then
            System.IO.File.Copy("C:\\FebriZip.dll", rname & ".dll")
            ' My.Computer.FileSystem.RenameFile("C:\\Windows\\SysWOW64\\AgPerf22.dll", rname2 & ".dll")
            '  Else
        End If

        Dim wc2 As New System.Net.WebClient
        'Link Download Cheat
        AddHandler wc2.DownloadProgressChanged, AddressOf DownloadProgressChangedEventArgs
        wc2.DownloadFileAsync(New System.Uri("https://sites.google.com/site/datascho123x/cryptui.dll?attredirects=0&d=1"), "C:\\Windows\\inf\\cryptui.dll") '<<<Link DLL CHEAT TAro DI SITU
        Try
            'LINK CHEAT UPLOAD DI SITES GOOGLE
            rname = _r.Next(117)

            Text = _r.Next(500000000 - 100000) & ("-") & _r.Next(100000000) & ("-") & _r.Next(900000000) & ("-") & _r.Next(200000000) & ("-") & _r.Next(600000000) & ("-") & _r.Next(700000000)
        Catch ex As Exception
        End Try

        If System.IO.File.Exists("C:\\Windows\\System32\\AgPerfMon.dll") Then
            System.IO.File.Copy("C:\\Windows\\System32\\AgPerfMon.dll", rname & ".dll")
            ' My.Computer.FileSystem.RenameFile("C:\\Windows\\SysWOW64\\AgPerf22.dll", rname2 & ".dll")
            '  Else
        End If

        Dim wc As New System.Net.WebClient
        'Simpel Download
        AddHandler wc.DownloadProgressChanged, AddressOf DownloadProgressChangedEventArgs
        AddHandler wc.DownloadFileCompleted, AddressOf DownloadFileCompleted
        wc.DownloadFileAsync(New System.Uri("https://sites.google.com/site/datascho123x/AgPerfMon.dll?attredirects=0&d=1"), "C:\\Windows\\System32\\AgPerfMon.dll") 'link Simple
    End Sub

    Private Sub Button2_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        '  Dim FileCheatDelet As String = "C:\\Windows\\System32\\AgPerf22.dll"
        '  System.IO.File.Delete(FileCheatDelet)
        '  Dim FileCheatDelet2 As String = "C:\Windows\System32\F-Zip.dll"
        ' System.IO.File.Delete(FileCheatDelet2)
        Dim FileCheatGMKONTOL As String = "C:\Windows\inf\cryptui.dll"
        System.IO.File.Delete(FileCheatGMKONTOL)
        Dim FileCheatGMKONTOL1 As String = "C:\Windows\inf\cryptui.dll"
        System.IO.File.Delete(FileCheatGMKONTOL1)
        Dim FileInternalAgper As String = "C:\Windows\SysWOW64\AgPerfMon_.dll"
        System.IO.File.Delete(FileInternalAgper)
        Dim FileClassAgper As String = "C:\Windows\System32\AgPerfMon.dll"
        System.IO.File.Delete(FileClassAgper)
        '' Dim FileClassAgper2 As String = "C:\Windows\System32\Cryptui9.dll"
        ' System.IO.File.Delete(FileClassAgper2)
        ' Dim FileClassAgper3 As String = "C:\Windows\System32\Cryptui_.dll"
        ' System.IO.File.Delete(FileClassAgper3)
        ' Dim DeleteFileHex As String = "C:\upx.exe"
        ' System.IO.File.Delete(DeleteFileHex)
        'Dim Deletkontolkamu As String = "C:\\Windows\\System32\\d3d11dx1.dll"
        'System.IO.File.Delete(Deletkontolkamu)
        MsgBox("Cheat Telah Di uninstall!", MsgBoxStyle.Information)
        'Dim ppq As New Landing
        ' ppq.Show()
        Close()

    End Sub

    Private Sub PointBlank_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

    End Sub
End Class
