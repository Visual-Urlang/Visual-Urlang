Public Class Object
End Class

Public Class Set Of T
    Public Function GetEntry(ByVal i As Integer) As T
        print i
    End Function
End Class

Public Class Association Of K, V
End Class

Public Class Dictionary Of K, V
    Inherits Set(Of Association(Of K, V))

    Public Function test As K (Of Y)
        print i
    End Function
End Class

Public Class Main
    Public Function FMain 
        Dim aDict As Dictionary(Of String, Integer)
    End Function
End Class