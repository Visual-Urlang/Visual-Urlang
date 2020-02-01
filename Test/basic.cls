Public Class Object
End Class

Public Class Set Of T
    Inherits Object
    Public Function Get(ByVal i As Integer) As T
        print i
    End Function
End Class

Public Class Dictionary Of TKey, TValue
    Inherits Set(Of Association(Of TKey, TValue))

    Public Function new(ByVal i As Integer) As Integer
        Return i
    End Function

    Public Function SetKey(ByVal key As TKey, ByVal value As TValue) As TValue
        Return key
    End Function
End Class

Public Class Association Of TA, TB
End Class

Public Class Main
    Public Function FMain 
        Dim aDict As Dictionary(Of Integer, Dictionary (Of Integer, Integer))
        Return aDict.SetKey(i, i)
    End Function
End Class