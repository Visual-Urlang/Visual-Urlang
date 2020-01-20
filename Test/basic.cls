Public Class Set Of T
    Public Function GetEntry(ByVal i As Integer) As T
        print i
    End Function
End Class

Public Class Association Of K, V
End Class

Public Class Dictionary Of K, V
    Inherits Set(Of K, V)

    Public Function a2cTest As T (Of Y)
        Dim a_c As aClass(Of String)
        aClass.do hello, world
    End Function
End Class