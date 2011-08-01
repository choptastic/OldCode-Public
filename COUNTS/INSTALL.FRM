VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Whoa! Productions"
   ClientHeight    =   5760
   ClientLeft      =   2400
   ClientTop       =   885
   ClientWidth     =   2625
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Icon            =   "INSTALL.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5760
   ScaleWidth      =   2625
   Begin VB.CommandButton help 
      Caption         =   "Help"
      Enabled         =   0   'False
      Height          =   375
      Left            =   960
      TabIndex        =   5
      Top             =   4680
      Width           =   1455
   End
   Begin VB.TextBox Text2 
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      MaxLength       =   1
      TabIndex        =   4
      Top             =   4680
      Width           =   495
   End
   Begin VB.CommandButton install 
      Appearance      =   0  'Flat
      Caption         =   "Install Counts Calculator"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   495
      Left            =   120
      TabIndex        =   6
      Top             =   5160
      Width           =   2415
   End
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      Caption         =   "Read This First"
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   960
      Width           =   2415
   End
   Begin VB.TextBox Text1 
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   3
      Text            =   "c:\counts"
      Top             =   3120
      Width           =   2415
   End
   Begin VB.DirListBox Dir1 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   990
      Left            =   120
      TabIndex        =   2
      Top             =   1800
      Width           =   2415
   End
   Begin VB.DriveListBox Drive1 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   315
      Left            =   120
      TabIndex        =   1
      Top             =   1440
      Width           =   2415
   End
   Begin VB.Label Label4 
      BackStyle       =   0  'Transparent
      Caption         =   "Perceived Drive"
      Height          =   375
      Left            =   480
      TabIndex        =   10
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label Label3 
      Caption         =   "What is the drive letter of the install directory from the perspective of the vending stand?"
      Height          =   855
      Left            =   120
      TabIndex        =   9
      Top             =   3840
      Width           =   2415
   End
   Begin VB.Label Label2 
      Caption         =   "Install Directory"
      Height          =   255
      Left            =   480
      TabIndex        =   8
      Top             =   2880
      Width           =   1455
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Counts Calculator v2.0 Installation program."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   120
      TabIndex        =   7
      Top             =   0
      Width           =   2175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim fromdir, todir, fromdrive, todrive As String
Dim typed As Integer
Sub status(out As String)
    Form3.Label2.Caption = out
    Form3.Label3.Caption = CurDir
End Sub

Sub increment()
    DoEvents
    Form3.ind.Width = Form3.ind.Width + 135
    DoEvents
End Sub
Private Sub Command1_Click()
    Dim yesno As Integer
    yesno = MsgBox("Please choose a path to install this program to.  This is very important that you understand where to install this program.  The drive you choose must be a drive that the vending stand computers have access to, otherwise they will not be able to run Counts Calculator.  For instance, Blah Cinemas' Vending Stand has two drives on it: The C drive, the drive from which they boot, and the D drive, which is the C drive on the computer running Windows NT in the office.  Also in the office of Blah Cinemas, there is are two computers, the one we already mentioned and the other one.  This 'Other One' has a C drive, the main boot drive, and the M drive, the C drive of the Main computer (the one running NT). If You would want to install this to the C drive of the NT computer or the M drive of the 'Other Computer' (of course they are technically the same hard drive).. I apologize for the complexity of this." + vbCrLf + "This program is Copyright 2000 by Jesse Gumm", 1)
    If yesno = 1 Then
        Dir1.Enabled = True
        Drive1.Enabled = True
        Text1.Enabled = True
        install.Enabled = True
        help.Enabled = True
        Text2.Enabled = True
        Form1.Height = 6150
    End If
End Sub



Private Sub Dir1_Change()
     If (typed = False) Then
        Text1.Text = Dir1.Path
    End If
End Sub

Private Sub Drive1_Change()
    'On Error Resume Next
    Dir1.Path = Drive1.Drive

    
End Sub

Private Sub Form_Load()
    Label1.Caption = "Counts Calculator " & GetVersion & " Installation Program"
    fromdir = CurDir
    Text1.Text = Dir1.Path
    Form1.Height = 1755
End Sub

Private Sub help_Click()
    MsgBox "For Example: The vending stand apparently has two hard drives, C and D.  The C drive is a normal hard drive, but the D drive is actually the C drive of the back office computer.  So if you are installing to the Back office computer's C drive, then choose the D drive for this text box."

End Sub

Private Sub install_Click()
    Dim cd As String
    Dim Dirs
    cd = CurDir
    Dim yesno As Integer
    todrive = Drive1.Drive
    
    Text1 = Trim(Text1)
    If Right(Text1, 1) = "\" Then
        Text1 = Left(Text1, Len(Text1) - 1)
    End If
    
    If Text2.Text < "C" Or Text2.Text > "Z" Then
        MsgBox "Please enter a value into the perceived drive"
        Exit Sub
    End If
    
    On Error GoTo baddrive
    Drive1.Drive = Text1.Text
    GoTo gooddrive
baddrive:
    MsgBox "Invalid Install Drive or Directory"
    Exit Sub
gooddrive:
    
    
    
    
    yesno = MsgBox("Are you sure you are ready to install to directory: " + Text1.Text + "?", 1)
    On Error GoTo problems
    If (yesno = 1) Then
            Form3.Show
            status "Creating " + Text1.Text
            
            Dirs = Split(Text1, "\")
            ChDrive Drive1
            ChDir "\"
            On Error Resume Next
            For i = LBound(Dirs) + 1 To UBound(Dirs)
                MkDir Dirs(i)
                ChDir Dirs(i)
            Next i
            On Error GoTo problems
                
            MkDir Text1.Text
            
            ChDrive (Drive1.Drive)
            ChDir Text1.Text
            todir = CurDir
            
            increment
            status "Creating \temp"
            MkDir "temp"
            increment
            status "Creating \daily"
            MkDir "daily"
            increment
            status "Creating \disk"
            MkDir "disk"
          
            status "Changing Directory"
            ChDrive fromdir
            ChDir fromdir
            
            status "Copying counts.exe"
            FileCopy "counts.exe", todir & "\counts.exe"
            increment
            status "Copying office.exe"
            FileCopy "office.exe", todir & "\office.exe"
            increment
            status "Copying setup.exe"
            FileCopy "setup.exe", todir & "\setup.exe"
            increment
            status "Copying vendtest.exe"
            FileCopy "vendtest.exe", todir & "\vendtest.exe"
            increment
            status "Copying autofix.exe"
            FileCopy "autofix.exe", todir & "\autofix.exe"
            increment
            status "Copying trip.chr"
            FileCopy "trip.chr", todir & "\trip.chr"
            increment
            status "Copying egavga.bgi"
            FileCopy "egavga.bgi", todir & "\egavga.bgi"
            increment
            status "Copying Documentation"
            Dim d
            d = Dir("Counts Calculator*.doc")
            FileCopy d, todir & "\" & d
            FileCopy "version.cts", todir & "\version.cts"
            increment
            
            
            status "Preparing Startup disk"
            
            Open todir & "\disk\autoexec.bat" For Output As #1
                Print #1, "autofix.exe"
            Close #1
            
            Open todir & "\disk\autoexec.nfo" For Output As #1
                Print #1, todir
                Print #1, Text2.Text
            Close #1
                
            increment
            
            ChDrive todir
            ChDir todir
                           
            increment
            MsgBox "Please enter the disk labeled 'Vending Startup Diskette'"
            status "Startup disk: Autoexec.bat"
            ChDir todir
            ChDrive todrive
            FileCopy "disk\autoexec.bat", "a:\autoexec.bat"
            increment
            status "Startup disk: autofix.exe"
            FileCopy "autofix.exe", "a:\autofix.exe"
            increment
            status "Startup disk: autoexec.nfo"
            FileCopy "disk\autoexec.nfo", "a:\autoexec.nfo"
            increment
            status "Complete"
            'MsgBox "size = " & Form3.ind.Width
            Form3.Hide
            MsgBox "Now remove the disk, insert it into a vending terminal, and restart that vending terminal with the disk in the drive. Then follow the onscreen instructions"
            Form2.Show
            Form1.Hide
            Form2.Timer1.Enabled = True
            Form2.Timer2.Enabled = True
            While Form2.Visible = False
                DoEvents
            Wend
            While Form2.Visible = True
                DoEvents
            Wend
    End If
    ChDir todir
    CreateProgramGroup (todir)
    yesno = MsgBox("Installation successful . . . would you like to run the setup program now?", 1)
    If yesno = 1 Then d = Shell("setup.exe", vbNormalFocus)
    End
    
    
problems:
    If Err.Number = 53 Then
        MsgBox "Program being installed from an incomplete directory", vbCritical
        
        End
    ElseIf Err.Number = 71 Then
        MsgBox "Please insert a disk into the A: drive", vbExclamation
        Resume
    ElseIf Err.Number = 75 Then
        Resume Next
    Else
        Number = Err.Number
        Err.Raise (Number)
    End If
    
End Sub

Private Sub Text1_Change()
    On Error Resume Next
    typed = True
    Dir1.Path = Text1.Text
    Drive1.Drive = Dir1.Path
    typed = False
    
    
    
End Sub

Private Sub Text2_Change()
    Text2.Text = UCase(Text2.Text)
    If Text2.Text < "C" Or Text2.Text > "Z" Then
        Text2.Text = ""
    End If
End Sub
