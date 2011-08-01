Attribute VB_Name = "registry"
Option Explicit
   
   Public Const REG_SZ As Long = 1
   Public Const REG_DWORD As Long = 4

   Public Const HKCR = &H80000000
   Public Const HKCU = &H80000001
   Public Const HKLM = &H80000002
   Public Const HKU = &H80000003

   Public Const ERROR_NONE = 0
   Public Const ERROR_BADDB = 1
   Public Const ERROR_BADKEY = 2
   Public Const ERROR_CANTOPEN = 3
   Public Const ERROR_CANTREAD = 4
   Public Const ERROR_CANTWRITE = 5
   Public Const ERROR_OUTOFMEMORY = 6
   Public Const ERROR_ARENA_TRASHED = 7
   Public Const ERROR_ACCESS_DENIED = 8
   Public Const ERROR_INVALID_PARAMETERS = 87
   Public Const ERROR_NO_MORE_ITEMS = 259

   Public Const KEY_ALL_ACCESS = &H3F
   Public Const KEY_QUERY_VALUE = &H1

   Public Const REG_OPTION_NON_VOLATILE = 0
   
    Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
    'Declare Function fCreateShellLink Lib "STKIT432.DLL" (ByVal lpstrFolderName As String, ByVal lpstrLinkName As String, ByVal lpstrLinkPath As String, ByVal lpstrLinkArgs As String) As Long


   Declare Function RegCloseKey Lib "advapi32.dll" _
    (ByVal hKey As Long) As Long
   Declare Function RegCreateKeyEx Lib "advapi32.dll" Alias _
    "RegCreateKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, _
    ByVal Reserved As Long, ByVal lpClass As String, ByVal dwOptions _
    As Long, ByVal samDesired As Long, ByVal lpSecurityAttributes _
    As Long, phkResult As Long, lpdwDisposition As Long) As Long
   Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias _
    "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, _
    ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As _
    Long) As Long
    Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" _
      (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, _
      lpData As Any, lpcbData As Long) As Long
   Declare Function RegQueryValueExString Lib "advapi32.dll" Alias _
    "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As _
    String, ByVal lpReserved As Long, lpType As Long, ByVal lpData _
    As String, lpcbData As Long) As Long
   Declare Function RegQueryValueExLong Lib "advapi32.dll" Alias _
    "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As _
    String, ByVal lpReserved As Long, lpType As Long, lpData As _
    Long, lpcbData As Long) As Long
   Declare Function RegQueryValueExNULL Lib "advapi32.dll" Alias _
    "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As _
    String, ByVal lpReserved As Long, lpType As Long, ByVal lpData _
    As Long, lpcbData As Long) As Long
   Declare Function RegSetValueExString Lib "advapi32.dll" Alias _
    "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, _
    ByVal Reserved As Long, ByVal dwType As Long, ByVal lpValue As _
    String, ByVal cbData As Long) As Long
   Declare Function RegSetValueExLong Lib "advapi32.dll" Alias _
    "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, _
    ByVal Reserved As Long, ByVal dwType As Long, lpValue As Long, _
    ByVal cbData As Long) As Long
    Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String) As Long
    Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long

   Public Function SetValueEx(ByVal hKey As Long, sValueName As String, _
   lType As Long, vValue As Variant) As Long
       Dim lValue As Long
       Dim SValue As String
       Select Case lType
           Case REG_SZ
               SValue = vValue & Chr$(0)
               SetValueEx = RegSetValueExString(hKey, sValueName, 0&, _
                                              lType, SValue, Len(SValue))
           Case REG_DWORD
               lValue = vValue
               SetValueEx = RegSetValueExLong(hKey, sValueName, 0&, _
   lType, lValue, 4)
           End Select
   End Function
   Public Sub SetStringValue(lRootKey As Long, sKeyName As String, sValueName As String, SValue As String)
    Dim lRetVal As Long         'result of the API functions
    Dim hKey As Long         'handle of opened key
    Dim vValue As Variant      'setting of queried value

    lRetVal = RegOpenKeyEx(lRootKey, sKeyName, 0, KEY_ALL_ACCESS, hKey)
    lRetVal = SetValueEx(hKey, sValueName, REG_SZ, SValue)
    RegCloseKey (hKey)
End Sub

   Public Function QueryValue(lngRootKey As Long, sKeyName As String, sValueName As String) As Variant
       Dim lRetVal As Long         'result of the API functions
       Dim hKey As Long         'handle of opened key
       Dim vValue As Variant      'setting of queried value

       lRetVal = RegOpenKeyEx(lngRootKey, sKeyName, 0, KEY_QUERY_VALUE, hKey)
       lRetVal = QueryValueEx(hKey, sValueName, vValue)
       QueryValue = vValue
       RegCloseKey (hKey)
   End Function

Public Sub DeleteKey(lRootKey As Long, sKeyName As String)
    Dim Result As Long
    RegOpenKeyEx lRootKey, sKeyName, 0, KEY_ALL_ACCESS, Result
    'If the key doesn't exist, we create it
    'Delete the key
    RegDeleteKey Result, ""
    'close the handle
    RegCloseKey Result

End Sub

Public Sub DeleteValue(lngRootKey As Long, sKeyName As String, sValueName As String)
    Dim Result As Long
    RegOpenKeyEx lngRootKey, sKeyName, 0, KEY_ALL_ACCESS, Result
    RegDeleteValue Result, sValueName
    RegCloseKey Result
End Sub



Private Function QueryValueEx(ByVal lhKey As Long, ByVal szValueName As String, vValue As Variant) As Long
  
    Dim cch As Long
    Dim lrc As Long
    Dim lType As Long
    Dim lValue As Long
    Dim SValue As String

    On Error GoTo QueryValueExError

    ' Determine the size and type of data to be read
    lrc = RegQueryValueExNULL(lhKey, szValueName, 0&, lType, 0&, cch)
    If lrc <> ERROR_NONE Then Error 5

    Select Case lType
      ' For strings
      Case REG_SZ:
        SValue = String(cch, 0)
        lrc = RegQueryValueExString(lhKey, szValueName, 0&, lType, SValue, cch)
        If lrc = ERROR_NONE Then
          vValue = Left$(SValue, cch - 1)
        Else
          vValue = Empty
          End If
      ' For DWORDS
      Case REG_DWORD:
        lrc = RegQueryValueExLong(lhKey, szValueName, 0&, lType, lValue, cch)
        If lrc = ERROR_NONE Then vValue = lValue
      Case Else
        'all other data types not supported
        lrc = -1
    End Select

QueryValueExExit:
      QueryValueEx = lrc
      Exit Function
QueryValueExError:
      Resume QueryValueExExit
End Function



