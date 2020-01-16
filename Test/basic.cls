Public Class aClass Of T
    Public Function acTest As T
        print Hello
    End Function
End Class

Public Class aTwoClass Of T
    Inherits aClass(Of T2)

    Public Function a2cTest As String
        Dim a_c As aClass(Of String)
        aClass.do hello, world
    End Function
End Class